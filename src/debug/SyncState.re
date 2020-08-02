type syncDirection = 
  | Game
  | Editor;

type t = {
  mutable stateForGame: option(Type.state),
  mutable stateForEditor: option(Type.state),
};

let mutableState:t = {
  stateForGame: Some(Type.initialState),
  stateForEditor: Some(Type.initialState),
};

let set = (state: Type.state, direction: syncDirection): unit => {
  switch direction {
  | Game => mutableState.stateForGame = Some(state);
  | Editor => mutableState.stateForEditor = Some(state);
  };

  ();
}

let get = (direction: syncDirection): option(Type.state) => {
  switch direction {
  | Game => {
    switch mutableState.stateForGame {
    | Some(data) => {
      mutableState.stateForGame = None;
      Some(data);
    }
    | None => None;
    };
  };
  | Editor => {
    switch mutableState.stateForEditor {
    | Some(data) => {
      mutableState.stateForEditor = None;
      Some(data);
    }
    | None => None;
    };
  };
  };
};

let getStateFromLocalStorage = (initialState: Type.state) => {
  let item = Dom.Storage.getItem("state", Dom.Storage.localStorage);

  switch(item) {
  | Some(item) => 
    let save = item
    ->Js.Json.parseExn
    ->Json_Util.Parse.state;

    {
      ...save,
      asset: initialState.asset
    }
  | None => Type.initialState
  }
};

let saveStateInLocalStorage = (state: Type.state) => {
  Dom.Storage.setItem(
    "state",
    Json_Util.Stringify.state(state),
    Dom.Storage.localStorage
  );

  ();
};