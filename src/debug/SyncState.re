type t = {
  mutable data: Type.state
}

let syncedState:t = {
  data: Type.initialState
};

let set = (state: Type.state) => {
  syncedState.data = state;
};

let get = () => syncedState.data;

let getStateFromLocalStorage = () => {
  let item = Dom.Storage.getItem("state", Dom.Storage.localStorage);

  switch(item) {
  | Some(item) => 
    item
    ->Js.Json.parseExn
    ->Json_Util.Parse.state
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