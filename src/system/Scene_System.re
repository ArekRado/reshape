[@bs.scope "performance"] [@bs.val]
external performanceNow : unit => float = "now";

let update = (state: Type.state) : Type.state =>
  if (! state.isSceneInicialized) {
    let newState =
      switch (state.scene) {
      | TestMap => Blueprint.TestMap.create(state)
      };

    newState;
  } else {
    state;
  };