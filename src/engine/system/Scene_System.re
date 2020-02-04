[@bs.scope "performance"] [@bs.val]
external performanceNow : unit => float = "now";

let update = (state: Shared.state): Shared.state =>
  if (! state.isSceneInicialized) {
    let newState =
      switch (state.scene) {
      | TestMap => Blueprint.TestMap.create(state)
      };

    newState;
  } else {
    state;
  };