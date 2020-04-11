let update = (state: Type.state): Type.state =>
  if (!state.game.isSceneInicialized) {
    let newState =
      switch (state.game.scene) {
      | TestMap => Blueprint.TestMap.create(state)
      };

    newState;
  } else {
    state;
  };