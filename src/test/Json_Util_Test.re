let simpleCorrect: string = [%raw {|require('./mock/simpleCorrect.json')|}];

type type1 = {
  isDebugInitialized: bool,
}

type type2 = {
  entity: Belt.List.t(string),
  mutable mouseButtons: float,
  mutable mousePosition: Type.vector,
  time: Type.time,
  isDebugInitialized: bool,
};

let runTests = () => {
  Test_Util.describe("Json_Util", it => {
    it("should parse simple data", _assert => {
      open Json_Util.Parse;

      let parseState =
        maybeObject((v) => 
          switch (v) {
          | Some(obj) => {
            let time = maybeObject(
              (timeObj): option(Type.time) =>
                switch (timeObj) {
                | Some(timeObj) =>
                  Some({
                    timeNow: floatWithDefault(0.0, maybeProperty("timeNow", timeObj)),
                    delta: floatWithDefault(0.0, maybeProperty("delta", timeObj))
                  });
                | None => raise(Not_found);
              }, 
              maybeProperty("time", obj)
            );

            Some({
              entity: [],
              mouseButtons: floatWithDefault(0.0, maybeProperty("mouseButtons", obj)),
              mousePosition: maybeVector(maybeProperty("mousePosition", obj)),
              time: switch (time) {
                | Some(v) => v;
                | None => raise(Not_found);
              },
              isDebugInitialized: boolWithDefault(false, maybeProperty("isDebugInitialized", obj)),
            });
          }
          | None => None;
          }
        );

      let data = Js.Json.string(simpleCorrect);
      // Js.log(simpleCorrect);

      switch(parseState(data)) {
      | Some(_) => _assert(true);
      | None => _assert(false);
      };
    });

    it("should parse dic which has been stringified", _assert => {
      open Json_Util.Parse;

      let dict = Js.Dict.empty();
      let timeDict = Js.Dict.empty();

      Js.Dict.set(timeDict, "timeNow", Js.Json.number(0.0));
      Js.Dict.set(timeDict, "delta", Js.Json.number(0.0));

      Js.Dict.set(dict, "entity", Js.Json.array([| |]));
      Js.Dict.set(dict, "mouseButtons", Js.Json.number(1.0));
      Js.Dict.set(dict, "mousePosition", Js.Json.numberArray([|1.0, 2.0|]));
      Js.Dict.set(dict, "time",  Js.Json.object_(timeDict));
      Js.Dict.set(dict, "isDebugInitialized", Js.Json.boolean(false));

      let parseState =
        maybeObject((v) => 
          switch (v) {
          | Some(obj) => {
            let time = maybeObject(
              (timeObj): option(Type.time) =>
                switch (timeObj) {
                | Some(timeObj) =>
                  Some({
                    timeNow: floatWithDefault(0.0, maybeProperty("timeNow", timeObj)),
                    delta: floatWithDefault(0.0, maybeProperty("delta", timeObj))
                  });
                | None => raise(Not_found);
              }, 
              maybeProperty("time", obj)
            );

            Some({
              entity: [],
              mouseButtons: floatWithDefault(0.0, maybeProperty("mouseButtons", obj)),
              mousePosition: maybeVector(maybeProperty("mousePosition", obj)),
              time: switch (time) {
                | Some(v) => v;
                | None => raise(Not_found);
              },
              isDebugInitialized: boolWithDefault(false, maybeProperty("isDebugInitialized", obj)),
            });
          }
          | None => {
            None
          };
          }
        );

      let dataString = dict
      ->Js.Json.object_
      ->Js.Json.stringifyWithSpace(2)

      let json =
        try (Js.Json.parseExn(dataString)) {
        | _ => failwith("Error parsing JSON string")
      };

      switch(parseState(json)) {
      | Some(_) => _assert(true);
      | None => _assert(false);
      };
    });

    it("should stringify state", _assert => {
      let state = Json_Util.stringifyState(Type.initialState);

      Js.log(state);
    });

  });
};


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