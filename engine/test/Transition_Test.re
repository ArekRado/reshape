let runTests = () => {
  let tick = (performanceNow, state) => Engine.runOneFrame(
    ~state,
    ~enableDraw=false,
    ~performanceNow,
    (),
  );

  let entity = Engine.Entity.generate("test");


  // float helpers

  let defaultFloatTransition: Shared.transition(float) = {
    keyframes: Belt.Map.Int.empty,
    isPlaying: false,
    playingFrameIndex: 0,
    value: 0.0,
    currentTime: 0.0,
  }

  let getTransitionFloat = (state: Shared.state, entity: string) =>
    switch (Belt.Map.String.get(state.transitionFloat, entity)) {
    | Some(transition) => transition
    | None => defaultFloatTransition
    };

  let getKeyframeValue = (state: Shared.state, entity: string) =>
    switch (Belt.Map.Int.get(getTransitionFloat(state, entity).keyframes, 0)) {
    | Some(keyframe) => keyframe.value
    | None => -111.0
    };

  // vector helpers

  let defaultVectorTransition: Shared.transition(Vector_Util.t) = {
    keyframes: Belt.Map.Int.empty,
    isPlaying: false,
    playingFrameIndex: 0,
    value: (0.0, 0.0),
    currentTime: 0.0,
  }

  let getTransitionVector = (state: Shared.state, entity: string) =>
    switch (Belt.Map.String.get(state.transitionVector, entity)) {
    | Some(transition) => transition
    | None => defaultVectorTransition
    };

  let getKeyframeValueVector = (state: Shared.state, entity: string) =>
    switch (Belt.Map.Int.get(getTransitionVector(state, entity).keyframes, 0)) {
    | Some(keyframe) => keyframe.value
    | None => (-111.0, -111.0)
    };

  Test_Util.it(
    "Float: Linear transition should change value in proper way", _assert => {
    let keyframe: Shared.keyframe(float) = {
      duration: 10.0,
      timingFunction: Linear,
      valueRange: (0.0, 1.0),
    };

    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionFloat.create(
        ~isPlaying=true,
        ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(1.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.1);
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.2);
        newState;
      })
    ->(state => {
        let newState = tick(10.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.2);
        newState;
      })
    ->(state => {
        let newState = tick(10.0, state);
        _assert(getKeyframeValue(newState, entity) === 1.0);
        newState;
      })
    ->(state => {
        let newState = tick(12.0, state);
        _assert(getKeyframeValue(newState, entity) === 1.0);
        newState;
      });
    ();
  });

  Test_Util.it(
    "Float: Should not update frame values when time is over", _assert => {
    let keyframe: Shared.keyframe(float) = {
      duration: 10.0,
      timingFunction: Linear,
      valueRange: (0.0, 1.0),
    };

    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionFloat.create(
        ~isPlaying=true,
        ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(20.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(40.0, state);
        _assert(getKeyframeValue(newState, entity) === 1.0);
        newState;
      });
    ();
  });

  Test_Util.it("Float: Should works with negative values", _assert => {
    let keyframe: Shared.keyframe(float) = {
      duration: 10.0,
      timingFunction: Linear,
      valueRange: (-1.0, -2.0),
    };

    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionFloat.create(
        ~isPlaying=true,
        ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(1.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      })
    ->(state => {
        let newState = tick(22.0, state);
        _assert(getKeyframeValue(newState, entity) === -0.1);
        newState;
      })
    ->(state => {
        let newState = tick(22.0, state);
        _assert(getKeyframeValue(newState, entity) === -2.0);
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(getKeyframeValue(newState, entity) === -2.0);
        newState;
      });
    ();
  });

  Test_Util.it(
    "Vector: Linear transition should change value in proper way", _assert => {
    let keyframe: Shared.keyframe(Vector_Util.t) = {
      duration: 10.0,
      timingFunction: Linear,
      valueRange: (
        Vector_Util.create(0.0, 0.0),
        Vector_Util.create(1.0, 1.0),
      ),
      value: Vector_Util.create(0.0, 0.0),
    };

    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionVector.create(
        ~isPlaying=true,
        ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.zero
        ));
        newState;
      })
    ->(state => {
        let newState = tick(1.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.zero
        ));
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.create(0.1, 0.1)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.create(0.2, 0.2)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(10.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.create(0.2, 0.2)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(10.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.create(1.0, 1.0)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(12.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          Vector_Util.create(1.0, 1.0)
        ));
        newState;
      });
    ();
  });

  Test_Util.it("Vector: Should works with negative values", _assert => {
    let keyframe: Shared.keyframe(Vector_Util.t) = {
      duration: 10.0,
      timingFunction: Linear,
      valueRange: (
        Vector_Util.create(-1.0, -1.0),
        Vector_Util.create(-2.0, -2.0),
      ),
      value: Vector_Util.create(0.0, 0.0),
    };

    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionVector.create(
        ~isPlaying=true,
        ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          (0.0, 0.0)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(1.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          (0.0, 0.0)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(22.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          (-0.1, -0.1)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(22.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          (-2.0, -2.0)
        ));
        newState;
      })
    ->(state => {
        let newState = tick(2.0, state);
        _assert(Vector_Util.isEqual(
          getKeyframeValueVector(newState, entity),
          (-2.0, -2.0)
        ));
        newState;
      });
    ();
    }
  );

  Test_Util.it("Should works with multiple frames", _assert => {
    let keyframes = 
      Belt.Map.Int.set(Belt.Map.Int.empty, 0, {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      }: Shared.keyframe(float))
      ->Belt.Map.Int.set(_, 1, {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      }: Shared.keyframe(float))
      ->Belt.Map.Int.set(_, 2, {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      }: Shared.keyframe(float))
      ->Belt.Map.Int.set(_, 3, {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      }: Shared.keyframe(float))



    Engine.initialState
    ->Engine.Entity.create(~entity, ~state=_)
    ->Engine.Component.TransitionFloat.create(
        ~isPlaying=true,
        ~keyframes,
        ~entity,
        ~state=_,
        (),
      )
    ->(state => {
        let newState = tick(0.0, state);
        _assert(getKeyframeValue(newState, entity) === 0.0);
        newState;
      });
    ()
  });
};