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

let stringifyVector = ((x, y)) => Js.Json.numberArray([| x, y |]);

let stringifyTimingFunction = (timingFunction: Type.timingFunction) => {
  let x = switch(timingFunction) {
  | Linear => "Linear"
  | EaseInQuad => "EaseInQuad"
  | EaseOutQuad => "EaseOutQuad"
  | EaseInOutQuad => "EaseInOutQuad"
  | EaseInCubic => "EaseInCubic"
  | EaseOutCubic => "EaseOutCubic"
  | EaseInOutCubic => "EaseInOutCubic"
  | EaseInQuart => "EaseInQuart"
  | EaseOutQuart => "EaseOutQuart"
  | EaseInOutQuart => "EaseInOutQuart"
  | EaseInQuint => "EaseInQuint"
  | EaseOutQuint => "EaseOutQuint"
  | EaseInOutQuint => "EaseInOutQuint"
  | CubicBezier(_, _, _, _) => "CubicBezier" // todo
  };

  Js.Json.string(x);
}

let stringifyEntity = entity =>
  Belt.List.map(entity, Js.Json.string)
  ->Array.of_list
  ->Js.Json.array

let stringifyTransform = transform => {
  let dict = Js.Dict.empty();

  ignore(
    Belt.Map.String.mapWithKey(transform, (entity, (x: Type.transform)) => {
      let transformDict = Js.Dict.empty();

      Js.Dict.set(transformDict, "rotation", Js.Json.number(x.rotation));
      Js.Dict.set(transformDict, "localRotation", Js.Json.number(x.localRotation));
      Js.Dict.set(transformDict, "scale", stringifyVector(x.scale));
      Js.Dict.set(transformDict, "localScale", stringifyVector(x.localScale));
      Js.Dict.set(transformDict, "position", stringifyVector(x.position));
      Js.Dict.set(transformDict, "localPosition", stringifyVector(x.localPosition));

      switch(x.parent) {
        | Some(parent) => Js.Dict.set(transformDict, "parent", Js.Json.string(parent));
        | None =>  Js.Dict.set(transformDict, "parent", Js.Json.null);
      }

      Js.Dict.set(dict, entity, Js.Json.object_(transformDict));
    })
  );

  Js.Json.object_(dict)
};

let stringifyAnimationFloat = animationFloat => {
  let dict = Js.Dict.empty();

  ignore(
    Belt.Map.String.mapWithKey(animationFloat, (entity, x: Type.animation(float)) => {
      let animationDict = Js.Dict.empty();

      Js.Dict.set(animationDict, "entity", Js.Json.string(x.entity));
      Js.Dict.set(animationDict, "name", Js.Json.string(x.name));
      Js.Dict.set(animationDict, "isPlaying", Js.Json.boolean(x.isPlaying));
      Js.Dict.set(animationDict, "isFinished", Js.Json.boolean(x.isFinished));
      Js.Dict.set(animationDict, "currentTime", Js.Json.number(x.currentTime));
      Js.Dict.set(animationDict, "value", Js.Json.number(x.value));
      Js.Dict.set(
        animationDict, 
        "wrapMode", 
        Js.Json.string(switch(x.wrapMode) {
        | Once => "Once"
        | Loop => "Loop"
        | PingPong => "PingPong"
        | ClampForever => "ClampForever"
        })
      );

      Js.Dict.set(animationDict, "keyframes", Js.Json.objectArray(
        Belt.List.map(x.keyframes, keyframe => {
          let keyframeDict = Js.Dict.empty();

          Js.Dict.set(keyframeDict, "duration", Js.Json.number(keyframe.duration));
          Js.Dict.set(keyframeDict, "timingFunction", stringifyTimingFunction(keyframe.timingFunction));
          Js.Dict.set(keyframeDict, "valueRange", stringifyVector(keyframe.valueRange));

          keyframeDict;
        })
        ->Array.of_list
      ));

      Js.Dict.set(dict, entity, Js.Json.object_(animationDict));
    })
  );

  Js.Json.object_(dict)
};

let stringifySprite = (sprite) => {
  let dict = Js.Dict.empty();

  ignore(
    Belt.Map.String.mapWithKey(sprite, (entity, x: Type.sprite) => {
      let spriteDict = Js.Dict.empty();

      Js.Dict.set(dict, "src", Js.Json.string(x.src));

      Js.Dict.set(dict, entity, Js.Json.object_(spriteDict));
    })
  );

  Js.Json.object_(dict)
};

let stringifyTime = (time: Type.time) => {
  let dict = Js.Dict.empty();

  Js.Dict.set(dict, "timeNow", Js.Json.number(time.timeNow));
  Js.Dict.set(dict, "delta", Js.Json.number(time.delta));

  Js.Json.object_(dict);
};

let stringifyState = (state: Type.state): string => {
  let dict = Js.Dict.empty();

  Js.Dict.set(dict, "entity", stringifyEntity(state.entity));
  Js.Dict.set(dict, "transform", stringifyTransform(state.transform));
  Js.Dict.set(dict, "sprite", stringifySprite(state.sprite));
  Js.Dict.set(dict, "animationFloat", stringifyAnimationFloat(state.animationFloat));
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

