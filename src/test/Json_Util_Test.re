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
        maybeObject(_, (v) => 
          switch (v) {
          | Some(obj) => {
            let time = maybeObject(
              maybeProperty(obj, "time", emptyObject),
              (timeObj): option(Type.time) =>
                switch (timeObj) {
                | Some(timeObj) =>
                  Some({
                    timeNow: floatWithDefault(maybeProperty(timeObj, "timeNow", emptyObject), 0.0),
                    delta: floatWithDefault(maybeProperty(timeObj, "delta", emptyObject), 0.0)
                  });
                | None => raise(Not_found);
              }, 
            );

            Some({
              entity: [],
              mouseButtons: floatWithDefault(maybeProperty(obj, "mouseButtons", emptyNumber), 0.0),
              mousePosition: maybeVector(maybeProperty(obj, "mousePosition", emptyArray)),
              time: switch (time) {
                | Some(v) => v;
                | None => raise(Not_found);
              },
              isDebugInitialized: boolWithDefault(maybeProperty(obj, "isDebugInitialized", emptyBool(false)), false),
            });
          }
          | None => None;
          }
        );

      let data = Js.Json.string(simpleCorrect);

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
        maybeObject(
          _,
          (v) => 
          switch (v) {
          | Some(obj) => {
            let time = maybeObject(
              maybeProperty(obj, "time", emptyObject),
              (timeObj): option(Type.time) =>
                switch (timeObj) {
                | Some(timeObj) =>
                  Some({
                    timeNow: floatWithDefault(maybeProperty(timeObj, "timeNow", emptyNumber), 0.0),
                    delta: floatWithDefault(maybeProperty(timeObj, "delta", emptyNumber), 0.0)
                  });
                | None => raise(Not_found);
              }, 
            );

            Some({
              entity: [],
              mouseButtons: floatWithDefault(maybeProperty(obj, "mouseButtons", emptyNumber), 0.0),
              mousePosition: maybeVector(maybeProperty(obj, "mousePosition", emptyArray)),
              time: switch (time) {
              | Some(v) => v;
              | None => raise(Not_found);
              },
              isDebugInitialized: boolWithDefault(maybeProperty(obj, "isDebugInitialized", emptyBool(false)), false),
            });
          }
          | None => None
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
      let stateString = Json_Util.Stringify.state(Type.initialState)

      let json =
        try (Js.Json.parseExn(stateString)) {
        | _ => failwith("Error parsing JSON string")
      };

      let stateString2 = json
        ->Json_Util.Parse.state
        ->Json_Util.Stringify.state

      _assert(stateString2 === stateString);
    });
  });
};
