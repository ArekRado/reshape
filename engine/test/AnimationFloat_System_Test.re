let runTests = () => {
  Test_Util.describe("AnimationFloat_System", it => {
    let tick = (performanceNow, state) =>
      Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let entity = Engine.Entity.generate("test");

    let defaultAnimation: Shared.animation(float) = {
      keyframes: Belt.Map.Int.empty,
      isPlaying: false,
      currentTime: 0.0,
      value: (-9999.0),
    };

    let getAnimation = (state: Shared.state, entity: string) =>
      switch (Belt.Map.String.get(state.animationFloat, entity)) {
      | Some(animation) => animation
      | None => defaultAnimation
      };

    it("Linear animation should change value in proper way", _assert => {
      let keyframe: Shared.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      };
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
          ~entity,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, entity).value === 0.1);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, entity).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getAnimation(newState, entity).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getAnimation(newState, entity).value === 1.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getAnimation(newState, entity).value === 1.0);
          }
        );
      ();
    });

    it("Should not update frame values when time is over", _assert => {
      let keyframe: Shared.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      };
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
          ~entity,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(20.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(40.0, state);
            _assert(getAnimation(newState, entity).value === 1.0);
          }
        );
      ();
    });

    it("Should works with negative values", _assert => {
      let keyframe: Shared.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: ((-1.0), (-2.0)),
      };
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=Belt.Map.Int.set(Belt.Map.Int.empty, 0, keyframe),
          ~entity,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getAnimation(newState, entity).value === (-0.1));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getAnimation(newState, entity).value === (-2.0));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, entity).value === (-2.0));
          }
        );
      ();
    });

    it("Should works with multiple frames", _assert => {
      let keyframes =
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
          );
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes,
          ~entity,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(5.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.5, state);
            _assert(getAnimation(newState, entity).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getAnimation(newState, entity).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            _assert(getAnimation(newState, entity).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(300.0, state);
            _assert(getAnimation(newState, entity).value === 0.87);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            _assert(getAnimation(newState, entity).value === 0.0);
            _assert(
              getAnimation(newState, entity).isPlaying === false,
            );
            _assert(
              getAnimation(newState, entity).currentTime === 0.0,
            );
            newState;
          }
        );
      ();
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Shared.animation(float) = {
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

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation);

      _assert(keyframeCurrentTime === 0.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Shared.animation(float) = {
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

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation);

      _assert(keyframeCurrentTime === 5.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Shared.animation(float) = {
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

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation);

      _assert(keyframeCurrentTime === 0.5);
      _assert(keyframeIndex === 1);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Shared.animation(float) = {
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
              {
                duration: 100.0,
                timingFunction: Linear,
                valueRange: (0.0, 1.0),
              }: Shared.keyframe(float),
            ),
      };

      let {keyframeCurrentTime, keyframeIndex, timeExceeded}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation);

      _assert(keyframeCurrentTime === 2000.0);
      _assert(timeExceeded === true);
      _assert(keyframeIndex === (-1));
    });
  });
};