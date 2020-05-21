let runTests = () => {
  // let tick = (performanceNow, state) =>
  //   Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());
  // let entity = Engine.Entity.generate("test");
  // let defaultTransition: Shared.transition(float) = {
  //   keyframes: Belt.Map.Int.empty,
  //   isPlaying: false,
  //   currentTime: 0.0,
  //   value: 0.0,
  // };
  // let getTransition = (state: Shared.state, entity: string) =>
  //   switch (Belt.Map.String.get(state.transitionFloat, entity)) {
  //   | Some(transition) => transition
  //   | None => defaultTransition
  //   };
  // let getKeyframeValue = (state: Shared.state, entity: string) =>
  //   switch (Belt.Map.Int.get(getTransition(state, entity).keyframes, 0)) {
  //   | Some(keyframe) => keyframe.value
  //   | None => (-111.0)
  //   };
  // Test_Util.it("Linear transition should change value in proper way", _assert => {
  //   let keyframe: TransitionFloat_Component.keyframe = {
  //     duration: 10.0,
  //     timingFunction: Linear,
  //     valueRange: (0.0, 1.0),
  //   };
  //   Engine.initialState
  //   ->Engine.Entity.create(~entity, ~state=_)
  //   ->Engine.Component.TransitionFloat.create(
  //       ~isPlaying=true,
  //       ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
  //       ~entity,
  //       ~state=_,
  //       (),
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(0.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(1.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(2.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.1);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(2.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.2);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(10.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.2);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(10.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 1.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(12.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 1.0);
  //       }
  //     );
  //   ();
  // });
  // Test_Util.it("Should not update frame values when time is over", _assert => {
  //   let keyframe: TransitionFloat_Component.keyframe = {
  //     duration: 10.0,
  //     timingFunction: Linear,
  //     valueRange: (0.0, 1.0),
  //   };
  //   Engine.initialState
  //   ->Engine.Entity.create(~entity, ~state=_)
  //   ->Engine.Component.TransitionFloat.create(
  //       ~isPlaying=true,
  //       ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
  //       ~entity,
  //       ~state=_,
  //       (),
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(0.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(20.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(40.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 1.0);
  //       }
  //     );
  //   ();
  // });
  // Test_Util.it("Should works with negative values", _assert => {
  //   let keyframe: TransitionFloat_Component.keyframe = {
  //     duration: 10.0,
  //     timingFunction: Linear,
  //     valueRange: ((-1.0), (-2.0)),
  //   };
  //   Engine.initialState
  //   ->Engine.Entity.create(~entity, ~state=_)
  //   ->Engine.Component.TransitionFloat.create(
  //       ~isPlaying=true,
  //       ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
  //       ~entity,
  //       ~state=_,
  //       (),
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(0.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(1.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(22.0, state);
  //         _assert(getKeyframeValue(newState, entity) === (-0.1));
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(22.0, state);
  //         _assert(getKeyframeValue(newState, entity) === (-2.0));
  //         newState;
  //       }
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(2.0, state);
  //         _assert(getKeyframeValue(newState, entity) === (-2.0));
  //       }
  //     );
  //   ();
  // });
  // Test_Util.it("Should works with multiple frames", _assert => {
  //   let keyframes =
  //     Belt.Map.Int.set(
  //       Belt.Map.Int.empty,
  //       0,
  //       {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: TransitionFloat_Component.keyframe,
  //     )
  //     ->Belt.Map.Int.set(
  //         _,
  //         1,
  //         {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: TransitionFloat_Component.keyframe,
  //       )
  //     ->Belt.Map.Int.set(
  //         _,
  //         2,
  //         {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: TransitionFloat_Component.keyframe,
  //       )
  //     ->Belt.Map.Int.set(
  //         _,
  //         3,
  //         {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: TransitionFloat_Component.keyframe,
  //       );
  //   Engine.initialState
  //   ->Engine.Entity.create(~entity, ~state=_)
  //   ->Engine.Component.TransitionFloat.create(
  //       ~isPlaying=true,
  //       ~keyframes,
  //       ~entity,
  //       ~state=_,
  //       (),
  //     )
  //   ->(
  //       state => {
  //         let newState = tick(0.0, state);
  //         _assert(getKeyframeValue(newState, entity) === 0.0);
  //         /* newState; */
  //       }
  //     );
  //   ();
  // });
  Test_Util.it("getActiveFrame - should return active frame", _assert => {
    let transition: Shared.transition(float) = {
      isPlaying: true,
      currentTime: 0.0,
      value: 0.0,
      keyframes:
        Belt.Map.Int.set(
          Belt.Map.Int.empty,
          0,
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
        ),
    };

    let {keyframeCurrentTime, keyframeIndex}: TransitionFloat_System.activeKeyframe =
      TransitionFloat_System.getActiveKeyframe(transition);

    _assert(keyframeCurrentTime === 0.0);
    _assert(keyframeIndex === 0);
  });

  Test_Util.it("getActiveFrame - should return active frame", _assert => {
    let transition: Shared.transition(float) = {
      isPlaying: true,
      currentTime: 5.0,
      value: 0.0,
      keyframes:
        Belt.Map.Int.set(
          Belt.Map.Int.empty,
          0,
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
        ),
    };

    let {keyframeCurrentTime, keyframeIndex}: TransitionFloat_System.activeKeyframe =
      TransitionFloat_System.getActiveKeyframe(transition);

    _assert(keyframeCurrentTime === 5.0);
    _assert(keyframeIndex === 0);
  });

  Test_Util.it("getActiveFrame - should return active frame", _assert => {
    let transition: Shared.transition(float) = {
      isPlaying: true,
      currentTime: 10.5,
      value: 0.0,
      keyframes:
        Belt.Map.Int.set(
          Belt.Map.Int.empty,
          0,
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
        )
        ->Belt.Map.Int.set(
            _,
            1,
            {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
          ),
    };

    let {keyframeCurrentTime, keyframeIndex}: TransitionFloat_System.activeKeyframe =
      TransitionFloat_System.getActiveKeyframe(transition);

    _assert(keyframeCurrentTime === 0.5);
    _assert(keyframeIndex === 1);
  });

  Test_Util.it("getActiveFrame - should return active frame", _assert => {
    let transition: Shared.transition(float) = {
      isPlaying: true,
      currentTime: 2000.0,
      value: 0.0,
      keyframes:
        Belt.Map.Int.set(
          Belt.Map.Int.empty,
          0,
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
        )
        ->Belt.Map.Int.set(
            _,
            1,
            {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
          )
        ->Belt.Map.Int.set(
            _,
            2,
            {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
          )
        ->Belt.Map.Int.set(
            _,
            3,
            {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:
                                                                    Shared.keyframe(
                                                                    float,
                                                                    ),
          ),
    };

    let {keyframeCurrentTime, keyframeIndex, timeExceeded}: TransitionFloat_System.activeKeyframe =
      TransitionFloat_System.getActiveKeyframe(transition);

    _assert(timeExceeded === true);
    _assert(keyframeIndex === (-1));
  });
};