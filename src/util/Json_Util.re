// module Parse = {
//   let validator = (correctTest, map, json) => map(correctTest(json))

//   let maybeString = validator((json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONString(value) => Some(value)
//       | _ => None
//     },
//   );

//   let maybeFloat = validator((json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONNumber(value) => Some(value)
//       | _ => None
//     },
//   );

//   let maybeBool = validator((json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONTrue => Some(true)
//       | Js.Json.JSONFalse => Some(false)
//       | _ => None
//     },
//   );

//   let maybeArray = (map, json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONArray(value) => map(value)
//       | _ => failwith("Expected an array")
//     };

//   let maybeProperty = (property, obj) =>
//     switch (Js.Dict.get(obj, property)) {
//     | Some(value) => value
//     | _ => failwith("Property: " ++ property ++ " doesn't exist")
//   };

//   let maybeObject = (map, json) => 
//     switch (Js.Json.classify(json)) {
//     | Js.Json.JSONObject(value) => map(Some(value))
//     | _ => None
//     };

//   // UTILS

//   let stringWithDefault = default => maybeString((maybeValue) => 
//     switch (maybeValue) {
//     | Some(value) => value
//     | None => default
//     }
//   );

//   let floatWithDefault = default => maybeFloat((maybeValue) => 
//     switch (maybeValue) {
//     | Some(value) => value
//     | None => default
//     }
//   );

//   let boolWithDefault = default => maybeBool((maybeValue) => 
//     switch (maybeValue) {
//     | Some(value) => value
//     | None => default
//     }
//   );

//   // let vectorWithDefault = default => maybeVector((maybeValue) => 
//   //   switch (maybeValue) {
//   //   | Some(value) => value
//   //   | None => default
//   //   }
//   // );

//   let getArrayWithDefault = (default, array, index) => 
//     switch (Belt.Array.get(array, index)) {
//     | Some(value) => value
//     | None => default
//     };

//   let maybeVector = maybeArray(array => {
//     let floatArray = Belt.Array.map(array, item => floatWithDefault(0.0, item));
    
//     (
//       getArrayWithDefault(0.0, floatArray, 0),
//       getArrayWithDefault(0.0, floatArray, 1)
//     );
//   });
// };
