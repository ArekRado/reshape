let runTests = () => {
  Test_Util.describe("Collide_System", it => {
    let tick = (performanceNow, state) =>
      Engine.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let defaultCollideBox: Shared.collideBox = {
      entity: "",
      size: Vector_Util.zero,
      position: Vector_Util.zero,
      collisions: [],
    };

    let getCollideBox = (state: Shared.state, id: string) =>
      switch (Belt.Map.String.get(state.collideBox, id)) {
      | Some(collideBox) => collideBox
      | None => defaultCollideBox
      };

    it("detect collisions box-box", _assert => {
      let entity1 = Engine.Entity.generate("e1");
      let entity2 = Engine.Entity.generate("e2");
      let entity3 = Engine.Entity.generate("e3");

      let id1 = Engine.Entity.generate("id1");
      let id2 = Engine.Entity.generate("id2");
      let id3 = Engine.Entity.generate("id3");

      Shared.initialState
      ->Engine.Entity.create(~entity=entity1, ~state=_)
      ->Engine.Entity.create(~entity=entity2, ~state=_)
      ->Engine.Entity.create(~entity=entity3, ~state=_)
      ->Engine.Component.Transform.create(
        ~entity=entity1,
        ~localPosition=(0.0, 0.0),
        ~state=_, 
        ()
      )
      ->Engine.Component.Transform.create(
        ~entity=entity2,
        ~localPosition=(1.0, 1.0),
        ~state=_, 
        ()
      )
      ->Engine.Component.Transform.create(
        ~entity=entity3,
        ~localPosition=(3.0, 3.0),
        ~state=_, 
        ()
      )
      ->Engine.Component.CollideBox.create(
        ~entity=entity1,
        ~id=id1,
        ~size=(1.5, 1.5),
        ~position=(0.0, 0.0),
        ~state=_, 
        ()
      )
      ->Engine.Component.CollideBox.create(
        ~entity=entity2,
        ~id=id2,
        ~size=(1.0, 1.0),
        ~position=(0.0, 0.0),
        ~state=_, 
        ()
      )
      ->Engine.Component.CollideBox.create(
        ~entity=entity3,
        ~id=id3,
        ~size=(1.0, 1.0),
        ~position=(-2.0, -2.0),
        ~state=_, 
        ()
      )
      ->(
          state => {
            let newState = tick(0.0, state);
            _assert(getCollideBox(newState, id1).position->Vector_Util.isEqual((1.0, 1.0)));
            _assert(getCollideBox(newState, id2).position->Vector_Util.isEqual((2.0, 2.0)));
            _assert(getCollideBox(newState, id3).position->Vector_Util.isEqual((-8.0, -8.0)));
            
            newState;
          }
        )
    });
  });
};