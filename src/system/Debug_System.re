
let update = (~state: Type.state, ~debug:bool): Type.state => {
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