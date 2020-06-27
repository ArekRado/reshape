// let simpleCorrect: string = [%raw {|require('./mock/simpleCorrect.json')|}];

// type type1 = {
//   isDebugInitialized: bool,
// }

// type type2 = {
//   entity: Belt.List.t(string),
//   mutable mouseButtons: float,
//   mutable mousePosition: Shared.vector,
//   time: Shared.time,
//   isDebugInitialized: bool,
// };

// let runTests = () => {
//   Test_Util.describe("Json_Util", it => {
//     // it("should throw error when data is invalid", _assert => {
//     //   open Json_Util.Parse;

//     //   let data = Js.Json.string("{}");

//     //   let parseState =
//     //     maybeObject((obj): type1 => {
//     //       isDebugInitialized: boolWithDefault(false, maybeProperty("isDebugInitialized", obj)),
//     //   });

//     //   let parsedData: type1 = switch(parseState(data)) {
//     //   | Some(v) => {
//     //       _assert(true);
//     //       v;
//     //     }
//     //   | None => {
//     //     _assert(false);
//     //     {
//     //       isDebugInitialized: false,
//     //     };
//     //   }
//     //   };
//     // });

//     it("should parse simple data", _assert => {
//       open Json_Util.Parse;

//       let parseState =
//         maybeObject((v) => 
//           switch (v) {
//           | Some(obj) => {
//             let time = maybeObject(
//               (timeObj): option(Shared.time) =>
//                 switch (timeObj) {
//                 | Some(timeObj) =>
//                   Some({
//                     timeNow: floatWithDefault(0.0, maybeProperty("timeNow", timeObj)),
//                     delta: floatWithDefault(0.0, maybeProperty("delta", timeObj))
//                   });
//                 | None => raise(Not_found);
//               }, 
//               maybeProperty("time", obj)
//             );

//             Some({
//               entity: [],
//               mouseButtons: floatWithDefault(0.0, maybeProperty("mouseButtons", obj)),
//               mousePosition: maybeVector(maybeProperty("mousePosition", obj)),
//               time: switch (time) {
//                 | Some(v) => v;
//                 | None => raise(Not_found);
//               },
//               isDebugInitialized: boolWithDefault(false, maybeProperty("isDebugInitialized", obj)),
//             });
//           }
//           | None => None;
//           }
//         );

//       let data = Js.Json.string(simpleCorrect);

//       switch(parseState(data)) {
//       | Some(_) => _assert(true);
//       | None => _assert(false);
//       };
//     });
//   });
// };


//               //  maybeArray(
//               //   array => {
//               //     let floatArray = Belt.Array.map(array, item => floatWithDefault(0.0, item));
                  
//               //     (
//               //       getArrayWithDefault(0.0, floatArray, 0),
//               //       getArrayWithDefault(0.0, floatArray, 1)
//               //     );
//               //   },
//               //   maybeProperty("mousePosition", obj)
//               // ),


//                 // maybeArray(maybeValue =>
//                 //   switch (maybeValue) {
//                 //   | Some(value) => (
//                 //     getArrayWithDefault((0.0, 0.0), value, 0),
//                 //     getArrayWithDefault((0.0, 0.0), value, 1)
//                 //   )
//                 //   | None => (0.0, 0.0)
//                 //   }
//                 // ),