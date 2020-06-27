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