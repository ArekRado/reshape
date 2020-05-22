
let update = (~state: Shared.state, ~debug:bool): Shared.state => {
  if(debug) {
    if(!state.isDebugInitialized) {
      Debug.initialize(state);

      {
        ...state,
        isDebugInitialized: true,
      };
    } else {
      SyncState.set(state);
      state;
    }
  } else {
    state;
  }
};