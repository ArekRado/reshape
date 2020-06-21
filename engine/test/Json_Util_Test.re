let simpleCorrect: string = [%raw {|require('./mock/simpleCorrect.json')|}];

type test = {
  entity: Belt.List.t(string),
  mutable mouseButtons: float,
  mutable mousePosition: Shared.vector,
  time: Shared.time,
  isDebugInitialized: bool,
};

let runTests = () => {
  Test_Util.describe("Json_Util", it => {
    it("Parse", _assert => {
      open Json_Util.Parse;

      let parseState =
        maybeObject((obj): test => {
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

      Js.log(simpleCorrect)

      let data = Js.Json.string(simpleCorrect);

      parseState(data)

      // let parsedData: test = try (parseState(data)) {
      // | _ => failwith("Error parsing JSON string")
      // };

      // Js.log(parsedData);
    });
  });
};