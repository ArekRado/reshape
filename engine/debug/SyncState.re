type t = {
  mutable data: Shared.state
}

let syncedState:t = {
  data: {
    entity: [],
    transform: Belt.Map.String.empty,
    image: Belt.Map.String.empty,
    rigidbody: Belt.Map.String.empty,
    transitionFloat: Belt.Map.String.empty,
    transitionVector: Belt.Map.String.empty,
    time: {
      timeNow: 0.0,
      delta: 0.0,
    },
    mouseButtons: 0,
    mousePosition: Vector_Util.zero,
    isDebugInitialized: false,
  }
};

let set = (state: Shared.state) => {
  syncedState.data = state;
};

let get = () => syncedState.data;