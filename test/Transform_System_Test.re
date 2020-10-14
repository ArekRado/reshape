let runTests = () => {
  Test_Util.describe("Transform_System", it => {
    let tick = (performanceNow, state) =>
      Util.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let defaultTransform: Type.transform = {
      rotation: 0.0,
      localRotation: 0.0,
      scale: (0.0, 0.0),
      localScale: (0.0, 0.0),
      position: (0.0, 0.0),
      localPosition: (0.0, 0.0),
      parent: None,
    };

    let getTransform = (state: Type.state, id: string) =>
      switch (Belt.Map.String.get(state.transform, id)) {
      | Some(transform) => transform
      | None => defaultTransform
      };

    it(
      "should set proper position using localPosition and parent.position",
      _assert => {
      let entity1 = Entity.generate("e1");
      let entity2 = Entity.generate("e2");
      let entity3 = Entity.generate("e3");
      let entity4 = Entity.generate("e4");

      Type.initialState
      ->Entity.create(~entity=entity1, ~state=_)
      ->Entity.create(~entity=entity2, ~state=_)
      ->Entity.create(~entity=entity3, ~state=_)
      ->Entity.create(~entity=entity4, ~state=_)
      ->Transform_Component.create(
          ~entity=entity3,
          ~localPosition=((-10.0), (-10.0)),
          ~parent=Some(entity2),
          ~state=_,
          (),
        )
      ->Transform_Component.create(
          ~entity=entity2,
          ~localPosition=(1.0, 1.0),
          ~parent=Some(entity1),
          ~state=_,
          (),
        )
      ->Transform_Component.create(
          ~entity=entity4,
          ~localPosition=(10.0, 10.0),
          ~parent=Some(entity2),
          ~state=_,
          (),
        )
      ->Transform_Component.create(
          ~entity=entity1,
          ~localPosition=(1.0, 1.0),
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(
              getTransform(newState, entity1).position
              ->Vector_Util.isEqual((1.0, 1.0)),
            );
            _assert(
              getTransform(newState, entity2).position
              ->Vector_Util.isEqual((2.0, 2.0)),
            );
            _assert(
              getTransform(newState, entity3).position
              ->Vector_Util.isEqual(((-8.0), (-8.0))),
            );
            _assert(
              getTransform(newState, entity4).position
              ->Vector_Util.isEqual((12.0, 12.0)),
            );

            newState;
          }
        );
    });
  });
};
