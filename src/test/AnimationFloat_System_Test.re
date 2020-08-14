let runTests = () => {
  Test_Util.describe("Animation_System - Float", it => {
    let tick = (performanceNow, state) =>
      ReShape.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let name = "test";
    let fieldFloatName = "testFieldFloat";

    let getAnimation = (state: Type.state, name: Type.entity) =>
      switch (Belt.Map.String.get(state.animation, name)) {
      | Some(animation) => animation
      | None => failwith("Can't find animation " ++ name);
      };

    let getFieldFloat = (state: Type.state, name: Type.entity) =>
      switch (Belt.Map.String.get(state.fieldFloat, name)) {
      | Some(field) => field
      | None => failwith("Can't find fieldFloat " ++ name);
      };

    it("Linear animation should change value in proper way", _assert => {
      let keyframe: Type.keyframe = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: Float((0.0, 1.0)),
      };
      Type.initialState
      ->ReShape.Entity.create(~entity=name, ~state=_)
      ->ReShape.Component.FieldFloat.create(
        ~entity="",
        ~state=_,
        ~name=fieldFloatName, 
        ~value=0.0,
        )
      ->ReShape.Component.Animation.create(
          ~component=FieldFloat(fieldFloatName),
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
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            Js.log(getFieldFloat(newState, fieldFloatName).value === 0.0);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.1);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.2);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 1.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 1.0);
          }
        );
      ();
    });

    it("Should not update frame values when time is over", _assert => {
      let keyframe: Type.keyframe = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: Float((0.0, 1.0)),
      };
      Type.initialState
      ->ReShape.Entity.create(~entity=name, ~state=_)
      ->ReShape.Component.FieldFloat.create(
        ~entity="",
        ~state=_,
        ~name=fieldFloatName, 
        ~value=0.0,
        )
      ->ReShape.Component.Animation.create(
          ~component=FieldFloat(fieldFloatName),
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
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(20.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(40.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 1.0);
          }
        );
      ();
    });

    it("Should works with negative values", _assert => {
      let keyframe: Type.keyframe = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: Float((-1.0, -2.0)),
      };
      Type.initialState
      ->ReShape.Entity.create(~entity="", ~state=_)
      ->ReShape.Component.FieldFloat.create(
        ~entity="",
        ~state=_,
        ~name=fieldFloatName, 
        ~value=0.0,
        )
      ->ReShape.Component.Animation.create(
          ~component=FieldFloat(fieldFloatName),
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
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === (-0.1));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === (-2.0));
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === (-2.0));
          }
        );
      ();
    });

    it("Should works with multiple frames", _assert => {
      let keyframes = [
        {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 1.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 2.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 100.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe
      ]

      Type.initialState
      ->ReShape.Entity.create(~entity=name, ~state=_)
      ->ReShape.Component.FieldFloat.create(
        ~entity="",
        ~state=_,
        ~name=fieldFloatName, 
        ~value=0.0,
        )
      ->ReShape.Component.Animation.create(
          ~component=FieldFloat(fieldFloatName),
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
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(5.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.5, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.5);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(300.0, state);
            _assert(getFieldFloat(newState, fieldFloatName).value === 0.87);
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(100.0, state);
            // _assert(getFieldFloat(newState, fieldFloatName).value === 0.0);
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
        {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 1.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 2.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        {duration: 100.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe
      ]

      let _ = Type.initialState
      ->ReShape.Entity.create(~entity=name, ~state=_)
      ->ReShape.Component.FieldFloat.create(
        ~entity="",
        ~state=_,
        ~name=fieldFloatName, 
        ~value=0.0,
        )
      ->ReShape.Component.Animation.create(
          ~component=FieldFloat(fieldFloatName),
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

            _assert(getFieldFloat(newState, fieldFloatName).value === 0.66);
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
      let animation: Type.animation = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 0.0,
        component: FieldFloat("testFieldFloat"),
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}:  Type.keyframe
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: Animation_System.activeKeyframe =
        Animation_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 0.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 5.0,
        component: FieldFloat("testFieldFloat"),
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: Animation_System.activeKeyframe =
        Animation_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 5.0);
      _assert(keyframeIndex === 0);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 10.5,
        component: FieldFloat("testFieldFloat"),
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 1.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex}: Animation_System.activeKeyframe =
        Animation_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 0.5);
      _assert(keyframeIndex === 1);
    });

    it("getActiveFrame - should return active frame", _assert => {
      let animation: Type.animation = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 2000.0,
        component: FieldFloat("testFieldFloat"),
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 1.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 2.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 100.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        ],
        isFinished: false,
        wrapMode: Once,
      };

      let {keyframeCurrentTime, keyframeIndex, timeExceeded}: Animation_System.activeKeyframe =
        Animation_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 1887.0);
      _assert(timeExceeded === true);
      _assert(keyframeIndex === (-1));
    });

    it("getActiveFrame - should works with Loop animation", _assert => {
      let animation: Type.animation = {
        entity: "",
        name: "",
        isPlaying: true,
        currentTime: 2000.0,
        component: FieldFloat("testFieldFloat"),
        keyframes: [
          {duration: 10.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 1.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 2.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
          {duration: 100.0, timingFunction: Linear, valueRange: Float((0.0, 1.0))}: Type.keyframe,
        ],
        isFinished: false,
        wrapMode: Loop,
      };

      let {keyframeCurrentTime, keyframeIndex, timeExceeded}: Animation_System.activeKeyframe =
        Animation_System.getActiveKeyframe(animation, false);

      _assert(keyframeCurrentTime === 66.0);
      _assert(timeExceeded === true);
      _assert(keyframeIndex === 3);
    });
  });
};