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
}

let maybeObject = (map, json) => 
  switch (Js.Json.classify(json)) {
  | Js.Json.JSONObject(value) => map(value)
  | _ => failwith("Expected an object")
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
  })

type test = {
  entity: Belt.List.t(string),
  mutable mouseButtons: float,
  mutable mousePosition: Shared.vector,
  time: Shared.time,
  isDebugInitialized: bool,
};

let parseState =
  maybeObject(
    (obj): test => {
      entity: [],
      mouseButtons: floatWithDefault(0.0, maybeProperty("mouseButtons", obj)),
      mousePosition: maybeVector(maybeProperty("mousePosition", obj)),
      
      
      //  maybeArray(
      //   array => {
      //     let floatArray = Belt.Array.map(array, item => floatWithDefault(0.0, item));
          
      //     (
      //       getArrayWithDefault(0.0, floatArray, 0),
      //       getArrayWithDefault(0.0, floatArray, 1)
      //     );
      //   },
      //   maybeProperty("mousePosition", obj)
      // ),


        // maybeArray(maybeValue =>
        //   switch (maybeValue) {
        //   | Some(value) => (
        //     getArrayWithDefault((0.0, 0.0), value, 0),
        //     getArrayWithDefault((0.0, 0.0), value, 1)
        //   )
        //   | None => (0.0, 0.0)
        //   }
        // ),
      time: maybeObject((timeObj): Shared.time => {
          timeNow: floatWithDefault(0.0, maybeProperty("timeNow", timeObj)),
          delta: floatWithDefault(0.0, maybeProperty("delta", timeObj))
      }, maybeProperty("time", obj)),
      isDebugInitialized: boolWithDefault(false, maybeProperty("isDebugInitialized", obj)),
  });

let parse = (data) => {
  // let test1 = maybeString((_, value) => value, data);
  // let test2 = maybeFloat((_, value) => value, data);
  // let test = Js.Json.decodeString(data)

  let parsedData: test = try (parseState(data)) {
  | _ => failwith("Error parsing JSON string")
  };

  Js.log(parsedData);
  // Js.log(test2);
};

// let parsee = (data) => {
//   let json =
//     try (Js.Json.parseExn(data)) {
//     | _ => failwith("Error parsing JSON string")
//     };

//   switch (Js.Json.classify(json)) {
//   | Js.Json.JSONObject(value) =>
//     /* In this branch, compiler infer value : Js.Json.t Js.Dict.t */
//     switch (Js.Dict.get(value, "entity")) {
//     | Some(entity) =>
//       switch (Js.Json.classify(entity)) {
//       | Js.Json.JSONArray(entity) =>
//         /* In this branch compiler infer entity : Js.Json.t array */
//         entity
//       | _ => failwith("Expected an array")
//       }
//     | None => failwith("Expected an `ids` property")
//     }
//   | _ => failwith("Expected an object")
//   };
// };

// let stringify = (state:Shared.state) => {}