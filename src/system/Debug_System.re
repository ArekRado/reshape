let update = (~state: Type.state, ~debug: bool): Type.state =>
  if (debug) {
    if (!state.isDebugInitialized) {
      SyncState.set(state, Editor);
      Debug.initialize();

      {...state, isDebugInitialized: true};
    } else {
      if(state.time.delta !== 0.0) {
        SyncState.set(state, Editor);
        state;
      } else {
        switch (SyncState.get(Game)) {
        | Some(editorState) => {...editorState, isDebugInitialized: true}
        | None => state
        };
      }
    };
  } else {
    state;
  };
