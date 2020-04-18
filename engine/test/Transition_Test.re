let runTests = () => {
  Test_Util.it("Linear transition should change value in proper way", () => {
    // let getKeyframeValue = (transition: Shared.transition(float)) =>
    //   switch (Belt.Map.Int.get(transition.keyframes, 0)) {
    //   | Some(keyframe) => keyframe.value
    //   | None => 0.0
    //   };

    let keyframe: Shared.keyframe(float) = {
      duration: 2.0,
      currentTime: 0.0,
      timingFunction: Linear,
      valueRange: (0.0, 1.0),
      value: 0.0,
    };

    let entity = Engine.Entity.generate("test");

    let state =
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.TransitionFloat.create(
          ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
          ~entity,
          ~state=_,
          (),
        )
      ->Engine.runOneFrame(
          ~state=_,
          ~enableDraw=false,
          ~performanceNow=0.0,
          (),
        );

    switch (Belt.Map.String.get(state.transitionFloat, entity)) {
    | Some(transition) =>
      switch (Belt.Map.Int.get(transition.keyframes, 0)) {
      | Some(keyframe) => keyframe.value === 0.0
      | None => false
      }
    | None => false
    };
  });
};