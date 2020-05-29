type t = {
  mutable data: Shared.state
}

let syncedState:t = {
  data: Shared.initialState
};

let set = (state: Shared.state) => {
  syncedState.data = state;
};

let get = () => syncedState.data;