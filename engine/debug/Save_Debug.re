// module Parse = {
//   let jsonFalse = (json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONFalse => false
//       | _ => failwith("Expected an false")
//     };

//   let jsonTrue = (json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONTrue => true
//       | _ => failwith("Expected an true")
//     };

//   // ???
//   // let jsonNull = (json) =>
//   //   switch (Js.Json.classify(json)) {
//   //     | Js.Json.JSONNull(value) => value
//   //     | _ => failwith("Expected an null")
//   //   };

//   let jsonString = (json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONString(value) => value
//       | _ => failwith("Expected an string")
//     };

//   let jsonNumber = (json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONNumber(value) => value
//       | _ => failwith("Expected an number")
//     };

//   type jsonObjectClasifyProperty = {
//     classifyProperty: (Js.Json.t) => bool, 
//     property: string,
//   };
  
//   let jsonObject = (json, classifyProperties) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONObject(object_) => {
//         let clasifyObject = ({classifyProperty, property}) => 
//           switch(Js.Dict.get(object_, property)) {
//             | Some(property) => classifyProperty(property)
//             | None => failwith("Invalid object property")
//           };

//         switch(Belt.List.some(classifyProperties, clasifyObject)) {
//           | false => object_
//           | true => failwith("Invalid object property")
//         };
//       }
//       | _ => failwith("Expected an object")
//     };

//   let jsonArray = (classifyItem, json) =>
//     switch (Js.Json.classify(json)) {
//       | Js.Json.JSONArray(array) => 
//         switch(Js.Array.some(item => classifyItem(item), array)) {
//           | false => array
//           | true => failwith("Item in array is invalid")
//         }
//       | _ => failwith("Expected an array")
//     };
// }


let validator = (correctTest, map=?, defaultValue, someValue) => {
 let (isCorrect, value) = correctTest(someValue, defaultValue);

  (
    isCorrect,
    switch(map) {
      | Some(map) => map(isCorrect, value)
      | None => value
    }
  )
}

let maybeString = validator(
  (json, defaultValue) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONString(value) => (true, value)
      | _ => (false, defaultValue)
    },
  (_, value) => value,
);

let maybeInt = validator();


let parse = (data) => {
  let test = maybeString(data, "nope");

  Js.log(test);
}

let parsee = (data) => {
  let json =
    try (Js.Json.parseExn(data)) {
    | _ => failwith("Error parsing JSON string")
    };

  switch (Js.Json.classify(json)) {
  | Js.Json.JSONObject(value) =>
    /* In this branch, compiler infer value : Js.Json.t Js.Dict.t */
    switch (Js.Dict.get(value, "entity")) {
    | Some(entity) =>
      switch (Js.Json.classify(entity)) {
      | Js.Json.JSONArray(entity) =>
        /* In this branch compiler infer entity : Js.Json.t array */
        entity
      | _ => failwith("Expected an array")
      }
    | None => failwith("Expected an `ids` property")
    }
  | _ => failwith("Expected an object")
  };
};

let stringify = (state:Shared.state) => {}