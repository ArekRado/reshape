let update = (~state: Type.state, ~debug: bool): Type.state =>
  if (debug) {
    if (!state.isDebugInitialized) {
      SyncState.set(state, Editor);
      Debug.initialize();

      {...state, isDebugInitialized: true};
    } else {
      switch (SyncState.get(Game)) {
      | Some(editorState) => {...editorState, isDebugInitialized: true}
      | None => state
      // SyncState.set(state, Editor);
      };
    };
  } else {
    state;
  };
