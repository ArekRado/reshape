module Parse = {
  let validator = (correctTest, map, json) => map(correctTest(json))

  let maybeString = validator((json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONString(value) => Some(value)
      | _ => None
    },
  );

  let maybeFloat = validator((json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONNumber(value) => Some(value)
      | _ => None
    },
  );

  let maybeBool = validator((json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONTrue => Some(true)
      | Js.Json.JSONFalse => Some(false)
      | _ => None
    },
  );

  let maybeArray = (map, json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONArray(value) => map(value)
      | _ => failwith("Expected an array")
    };

  let maybeProperty = (property, obj) =>
    switch (Js.Dict.get(obj, property)) {
    | Some(value) => value
    | _ => failwith("Property: " ++ property ++ " doesn't exist")
  };

  let maybeObject = (map, json) => 
    switch (Js.Json.classify(json)) {
    | Js.Json.JSONObject(value) => map(Some(value))
    | _ => None
    };

  // UTILS

  let stringWithDefault = default => maybeString((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let floatWithDefault = default => maybeFloat((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let boolWithDefault = default => maybeBool((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  // let vectorWithDefault = default => maybeVector((maybeValue) => 
  //   switch (maybeValue) {
  //   | Some(value) => value
  //   | None => default
  //   }
  // );

  let getArrayWithDefault = (default, array, index) => 
    switch (Belt.Array.get(array, index)) {
    | Some(value) => value
    | None => default
    };

  let maybeVector = maybeArray(array => {
    let floatArray = Belt.Array.map(array, item => floatWithDefault(0.0, item));
    
    (
      getArrayWithDefault(0.0, floatArray, 0),
      getArrayWithDefault(0.0, floatArray, 1)
    );
  });
};

let stringifyVector = (x, y) => Js.Json.numberArray([| x, y |])

let stringifyEntity = entity =>
  Belt.List.map(entity, Js.Json.string)
  ->Array.of_list
  ->Js.Json.array

let stringifyTransform = transform => {
  let dict = Js.Dict.empty();

  Belt.Map.String.mapWithKey(transform, (entity, x) => {
    let {
      scale: (scaleX, scaleY),
      localScale: (localScaleX, localScaleY),
      position: (positionX, positionY),
      localPosition: (localPositionX, localPositionY),
    }: Type.transform = x;
    let transformDic = Js.Dict.empty();

    Js.Dict.set(dict, "rotation", Js.Json.number(x.rotation));
    Js.Dict.set(dict, "localRotation", Js.Json.number(x.localRotation));
    Js.Dict.set(dict, "scale", stringifyVector(scaleX, scaleY));
    Js.Dict.set(dict, "localScale", stringifyVector(localScaleX, localScaleY));
    Js.Dict.set(dict, "position", stringifyVector(positionX, positionY));
    Js.Dict.set(dict, "localPosition", stringifyVector(localPositionX, localPositionY));

    switch(x.parent) {
      | Some(parent) => Js.Dict.set(dict, "parent", Js.Json.string(parent));
      | None =>  Js.Dict.set(dict, "parent", Js.Json.null);
    }

    Js.Dict.set(dict, entity, Js.Json.object_(transformDic));
  })

  Js.Json.object_(dict)
}


let stringifyTime = (time) => {
  let dict = Js.Dict.empty();

  Js.Dict.set(dict, "timeNow", Js.Json.number(0.0));
  Js.Dict.set(dict, "delta", Js.Json.number(0.0));

  Js.Json.object_(dict);
};

let stringifyState = (state: Type.state): string => {
  let dict = Js.Dict.empty();

  Js.Dict.set(dict, "entity", stringifyEntity(state.entity));
  Js.Dict.set(dict, "transform", stringifyTransform(state.transform));
  // transform: Belt.Map.String.empty,
  // sprite: Belt.Map.String.empty,
  // animationFloat: Belt.Map.String.empty,
  // animationVector: Belt.Map.String.empty,
  // collideBox: Belt.Map.String.empty,
  // collideCircle: Belt.Map.String.empty,
  Js.Dict.set(dict, "time", stringifyTime(state.time));

  // mouseButtons: 0,
  // mousePosition: Vector_Util.zero,
  // isDebugInitialized: false,

  dict
  ->Js.Json.object_
  ->Js.Json.stringifyWithSpace(2)  
}

