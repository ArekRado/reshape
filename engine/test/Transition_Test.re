let runTests = () => {
  let getKeyframeValue = (state: Shared.state, entity: string) =>
      switch (Belt.Map.String.get(state.transitionFloat, entity)) {
      | Some(transition) =>
        switch (Belt.Map.Int.get(transition.keyframes, 0)) {
        | Some(keyframe) => keyframe.value
        | None => (-1.0)
        }
      | None => (-1.0)
      };

  let getKeyframeValueVector = (state: Shared.state, entity: string) =>
      switch (Belt.Map.String.get(state.transitionVector, entity)) {
      | Some(transition) =>
        switch (Belt.Map.Int.get(transition.keyframes, 0)) {
        | Some(keyframe) => keyframe.value
        | None => Vector_Util.create(-1.0, -1.0)
        }
      | None => Vector_Util.create(-1.0, -1.0)
      };


  Test_Util.it("Float: Linear transition should change value in proper way", expect => {
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
        )
        ->((state) => {
          expect(getKeyframeValue(state, entity)).toBe(0.0);
          state
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow=1.0, ());
        expect(getKeyframeValue(newState, entity)).toBe(0.0);          
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=2.0,
            (),
          );
        expect(getKeyframeValue(newState, entity)).toBe(0.1);     
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=2.0,
            (),
          );
        expect(getKeyframeValue(newState, entity)).toBe(0.2);
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=10.0,
            (),
          );
        expect(getKeyframeValue(newState, entity)).toBe(0.2);
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=10.0,
            (),
          );
        expect(getKeyframeValue(newState, entity)).toBe(1.0);
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=12.0,
            (),
          );
        expect(getKeyframeValue(newState, entity)).toBe(1.0);
        newState
        })
  });

  Test_Util.it("Float: Should not update frame values when time is over", expect => {
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
        )
        ->((state) => {
          expect(getKeyframeValue(state, entity)).toBe(0.0);
          state;
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow=20.0, ());
          expect(getKeyframeValue(newState, entity)).toBe(0.0);

          newState;
        })
        ->((state) => {
          let newState =
            Engine.runOneFrame(
              ~state=state,
              ~enableDraw=false,
              ~performanceNow=40.0,
              (),
            );
          expect(getKeyframeValue(newState, entity)).toBe(1.0);

          newState;
        })
  });

  Test_Util.it("Float: Should works with negative values", expect => {
    let keyframe: Shared.keyframe(float) = {
      duration: 10.0,
      currentTime: 0.0,
      timingFunction: Linear,
      valueRange: (-1.0, -2.0),
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
        )
        ->((state) => {
          expect(getKeyframeValue(state, entity)).toBe(0.0);
          state;
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow=1.0, ());
          expect(getKeyframeValue(newState, entity)).toBe(0.0);

          newState;
        })
        ->((state) => {
          let newState =
            Engine.runOneFrame(
              ~state=state,
              ~enableDraw=false,
              ~performanceNow=22.0,
              (),
            );
          expect(getKeyframeValue(newState, entity)).toBe(-0.1);

          newState;
        })
        ->((state) => {
          // Should not update when time is over
          let newState =
            Engine.runOneFrame(
              ~state=state,
              ~enableDraw=false,
              ~performanceNow=2.0,
              (),
            );
          expect(getKeyframeValue(newState, entity)).toBe(-2.0);

          newState;
        })
  })


  Test_Util.it("Vector: Linear transition should change value in proper way", expect => {
    let keyframe: Shared.keyframe(Vector_Util.t) = {
      duration: 10.0,
      currentTime: 0.0,
      timingFunction: Linear,
      valueRange: (Vector_Util.create(0.0, 0.0), Vector_Util.create(1.0, 1.0)),
      value: Vector_Util.create(0.0, 0.0),
    };

    let entity = Engine.Entity.generate("test");

    let state =
      Engine.initialState
      ->Engine.Entity.create(~entity, ~state=_)
      ->Engine.Component.TransitionVector.create(
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
        )
        ->((state) => {
          expect(getKeyframeValueVector(state, entity)).toBe(Vector_Util.zero());
          state
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow=1.0, ());
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.zero());          
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=2.0,
            (),
          );
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.create(0.1, 0.1));     
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=2.0,
            (),
          );
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.create(0.2, 0.2));
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=10.0,
            (),
          );
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.create(0.2, 0.2));
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=10.0,
            (),
          );
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.create(1.0, 1.0));
        newState
        })
        ->((state) => {
          let newState =
          Engine.runOneFrame(
            ~state=state,
            ~enableDraw=false,
            ~performanceNow=12.0,
            (),
          );
        expect(getKeyframeValueVector(newState, entity)).toBe(Vector_Util.create(0.2, 0.2));
        newState
        })
  })
  Test_Util.it("Vector: Should works with negative values", expect => {})


  Test_Util.it("Should works with multiple frames", expect => {})
};