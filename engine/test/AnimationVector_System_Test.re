let runTests = () => {
  Test_Util.describe("AnimationVector_System", it => {
    let tick = (performanceNow, state) =>
      Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let id = Engine.Entity.generate("test");

    let defaultAnimation: Shared.animation(Vector_Util.t) = {
      entity: "",
      keyframes: [],
      isPlaying: false,
      currentTime: 0.0,
      value: Vector_Util.zero,
    };

    let getddAnimation = (state: Shared.state, entity: string) =>
      switch (Belt.Map.String.get(state.animationVector, id)) {
      | Some(animation) => animation
      | None => defaultAnimation
      };

    it("Linear animation should change value in proper way", _assert => {
      let keyframe: Shared.keyframe(Vector_Util.t) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (
          Vector_Util.create(0.0, 0.0),
          Vector_Util.create(1.0, 1.0),
        ),
      };

      Engine.initialState
      ->Engine.Entity.create(~entity=id, ~state=_)
      ->Engine.Component.AnimationVector.create(
          ~isPlaying=true,
          ~keyframes=[keyframe],
          ~entity="",
          ~id,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.zero,
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.zero,
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.create(0.1, 0.1),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.create(0.2, 0.2),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.create(0.2, 0.2),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(10.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.create(1.0, 1.0),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(12.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                Vector_Util.create(1.0, 1.0),
              ),
            );
          }
        );
      ();
    });

    it("Should works with negative values", _assert => {
      let keyframe: Shared.keyframe(Vector_Util.t) = {
        duration: 10.0,
        timingFunction: Linear,
        valueRange: (
          Vector_Util.create(-1.0, -1.0),
          Vector_Util.create(-2.0, -2.0),
        ),
      };

      Engine.initialState
      ->Engine.Entity.create(~entity=id, ~state=_)
      ->Engine.Component.AnimationVector.create(
          ~isPlaying=true,
          ~keyframes=[keyframe],
          ~entity="",
          ~id,
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                (0.0, 0.0),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(1.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                (0.0, 0.0),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                ((-0.1), (-0.1)),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(22.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                ((-2.0), (-2.0)),
              ),
            );
            newState;
          }
        )
      ->(
          state => {
            let newState = tick(2.0, state);
            _assert(
              Vector_Util.isEqual(
                getddAnimation(newState, id).value,
                ((-2.0), (-2.0)),
              ),
            );
          }
        );
      ();
    });

    // it("getActiveFrame - should return active frame", _assert =>
    //   {}
    // );
  });
};