let runTests = () => {
  Test_Util.it("Linear transition should change value in proper way", expect => {
    let getKeyframeValue = (state: Shared.state, entity: string) =>
      switch (Belt.Map.String.get(state.transitionFloat, entity)) {
      | Some(transition) =>
        switch (Belt.Map.Int.get(transition.keyframes, 0)) {
        | Some(keyframe) => keyframe.value
        | None => (-1.0)
        }
      | None => (-1.0)
      };

    let keyframe: Shared.keyframe(float) = {
      duration: 10.0,
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

    let result1 = getKeyframeValue(state, entity);
    // expect(result1).toBe(0.0);

    let state2 =
      Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow=1.0, ());
    let result2 = getKeyframeValue(state2, entity);
    // expect(result2).toBe(0.0);

    let state3 =
      Engine.runOneFrame(
        ~state=state2,
        ~enableDraw=false,
        ~performanceNow=2.0,
        (),
      );
    let result3 = getKeyframeValue(state3, entity);
    // expect(result3).toBe(0.0);

    let state4 =
      Engine.runOneFrame(
        ~state=state3,
        ~enableDraw=false,
        ~performanceNow=3.0,
        (),
      );
    let result4 = getKeyframeValue(state4, entity);
    // expect(result4).toBe(0.0);
  });
};