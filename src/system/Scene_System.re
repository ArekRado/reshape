let update =
    ((state: Type.state, engine: Engine.Shared.state))
    : (Type.state, Engine.Shared.state) => {
  if (! state.isSceneInicialized) {
    let (newState, newEngine) =
      switch (state.scene) {
      | TestMap => Blueprint.TestMap.create((state, engine))
      };

    (newState, newEngine);
  } else {
    (state, engine);
  };