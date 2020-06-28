let runTests = () => {
  Test_Util.describe("AnimationFloat_System", it => {
    let tick = (performanceNow, state) =>
      Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let name = "test";

    let defaultAnimation: Type.animation(float) = {
      entity: "",
      name: "",
      keyframes: [],
      isPlaying: false,
      currentTime: 0.0,
      value: (-9999.0),
      isFinished: false,
      wrapMode: Once,
    };

    let getAnimation = (state: Type.state, name: string) =>
      switch (Belt.Map.String.get(state.animationFloat, name)) {
      | Some(animation) => animation
      | None => defaultAnimation
      };

    it("Linear animation should change value in proper way", _assert => {
      let keyframe: Type.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      };
      Type.initialState
      ->Engine.Entity.create(~entity=name, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=[keyframe],
          ~entity="",
          ~name,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, name).value === 0.1);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, name).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getAnimation(newState, name).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getAnimation(newState, name).value === 1.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getAnimation(newState, name).value === 1.0);
          }
        );
      ();
    });

    it("Should not update frame values when time is over", _assert => {
      let keyframe: Type.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (0.0, 1.0),
      };
      Type.initialState
      ->Engine.Entity.create(~entity=name, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=[keyframe],
          ~entity="",
          ~name,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(20.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(40.0, state);
            _assert(getAnimation(newState, name).value === 1.0);
          }
        );
      ();
    });

    it("Should works with negative values", _assert => {
      let keyframe: Type.keyframe(float) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: ((-1.0), (-2.0)),
      };
      Type.initialState
      ->Engine.Entity.create(~entity="", ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes=[keyframe],
          ~entity="",
          ~name,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getAnimation(newState, name).value === (-0.1));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getAnimation(newState, name).value === (-2.0));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getAnimation(newState, name).value === (-2.0));
          }
        );
      ();
    });

    it("Should works with multiple frames", _assert => {
      let keyframes = [
        {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float)
      ]

      Type.initialState
      ->Engine.Entity.create(~entity=name, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes,
          ~entity="",
          ~name,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(5.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.5, state);
            _assert(getAnimation(newState, name).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getAnimation(newState, name).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            _assert(getAnimation(newState, name).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(300.0, state);
            _assert(getAnimation(newState, name).value === 0.87);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            _assert(getAnimation(newState, name).value === 0.0);
            _assert(
              getAnimation(newState, name).isPlaying === false,
            );
            _assert(
              getAnimation(newState, name).currentTime === 0.0,
            );
          }
        );
      ();
    });

    it("Should works with looped animations", _assert => {
      let keyframes = [
        {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float)
      ]

      Type.initialState
      ->Engine.Entity.create(~entity=name, ~state=_)
      ->Engine.Component.AnimationFloat.create(
          ~isPlaying=true,
          ~keyframes,
          ~entity="",
          ~name,
          ~state=_,
          ~wrapMode=Loop,
          (),
        )
      -> tick(2000.0, _)
      ->(
          state => {
            let newState = tick(2000.0, state);

            _assert(getAnimation(newState, name).value === 0.66);
            _assert(getAnimation(newState, name).isFinished === true);
            _assert(
              getAnimation(newState, name).isPlaying === true,
            );
            _assert(
              getAnimation(newState, name).currentTime === 66.0,
            );

            newState;
          })
        ->(
          // Second tick should reset isFinished flag
          state => {
            let newState = tick(2010.0, state);

            _assert(getAnimation(newState, name).isFinished === false);
            _assert(getAnimation(newState, name).currentTime === 76.0);

            newState;
          }
        );
      ();
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation(float) = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 0.0,
        value: 0.0,
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}:  Type.keyframe(float)
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 0.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation(float) = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 5.0,
        value: 0.0,
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 5.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation(float) = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 10.5,
        value: 0.0,
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float)
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 0.5);
      _assert(keyframeIndex === 1);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation(float) = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 2000.0,
        value: 0.0,
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex, timeExceeded}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 1887.0);
      _assert(timeExceeded === true);
      _assert(keyframeIndex === (-1));
    });

    it("getActiveFrame - should works with Loop animation", _assert => {
      let animation: Type.animation(float) = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 2000.0,
        value: 0.0,
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 1.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 2.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
          {duration: 100.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Type.keyframe(float),
        ],
        isFinished: false,
        wrapMode: Loop,
      };

      let {keyframeCurrentTime, keyframeIndex, timeExceeded}: AnimationFloat_System.activeKeyframe =
        AnimationFloat_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 66.0);
      _assert(timeExceeded === true);
      _assert(keyframeIndex === 3);
    });
  });
};