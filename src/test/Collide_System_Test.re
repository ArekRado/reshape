let runTests = () => {
  Test_Util.describe("Collide_System", it => {
    let tick = (performanceNow, state) =>
      ReShape.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let getEntity = collideBox => {
      switch (collideBox) {
      | Some(Type.Box(entity)) => entity
      | Some(Type.Circle(entity)) => entity
      | None => "None"
      };
    };

    let getCollideBox = (state: Type.state, name: string, entity: string) =>
      switch (CollideBox_Component.get(~state, ~name, ~entity)) {
      | Some(collideBox) => collideBox
      | None =>
        Js.log("Can't find collidebox " ++ name);
        failwith("Can't find collidebox " ++ name);
      };

    it("detectAABBcollision", _assert => {
      Collide_System.detectAABBcollision(
        (0.0, 0.0),
        (1.0, 1.0),
        (0.5, 0.5),
        (1.0, 1.0),
      )
      ->_assert;

      Collide_System.detectAABBcollision(
        (0.0, 0.0),
        (1.0, 1.0),
        (1.0, 1.0),
        (1.0, 1.0),
      )
      ->(result => _assert(result === false));

      Collide_System.detectAABBcollision(
        (0.0, 0.0),
        (1.0, 1.0),
        ((-10.0), (-10.0)),
        (20.0, 20.0),
      )
      ->_assert;
    });

    it("detect collisions box-box", _assert => {
      let entity1 = ReShape.Entity.generate("e1");
      let entity2 = ReShape.Entity.generate("e2");
      let entity3 = ReShape.Entity.generate("e3");

      let id1 = ReShape.Entity.generate("id1");
      let id2 = ReShape.Entity.generate("id2");
      let id3 = ReShape.Entity.generate("id3");

      Type.initialState
      ->ReShape.Entity.create(~entity=entity1, ~state=_)
      ->ReShape.Entity.create(~entity=entity2, ~state=_)
      ->ReShape.Entity.create(~entity=entity3, ~state=_)
      ->ReShape.Component.Transform.create(
          ~entity=entity1,
          ~localPosition=(0.0, 0.0),
          ~state=_,
          (),
        )
      ->ReShape.Component.Transform.create(
          ~entity=entity2,
          ~localPosition=(1.0, 1.0),
          ~state=_,
          (),
        )
      ->ReShape.Component.Transform.create(
          ~entity=entity3,
          ~localPosition=(3.5, 3.5),
          ~state=_,
          (),
        )
      ->ReShape.Component.CollideBox.create(
          ~entity=entity1,
          ~name=id1,
          ~size=(1.5, 1.5),
          ~position=(0.0, 0.0),
          ~state=_,
          (),
        )
      ->ReShape.Component.CollideBox.create(
          ~entity=entity2,
          ~name=id2,
          ~size=(1.0, 1.0),
          ~position=(0.0, 0.0),
          ~state=_,
          (),
        )
      ->ReShape.Component.CollideBox.create(
          ~entity=entity3,
          ~name=id3,
          ~size=(1.0, 1.0),
          ~position=((-2.0), (-2.0)),
          ~state=_,
          (),
        )
      ->(
          state => {
            let newState = tick(0.0, state);

            _assert(
              getCollideBox(newState, id1, entity1).collisions
              ->Belt.List.get(0)
              ->getEntity
              === entity2 ++ id2,
            );
            _assert(
              getCollideBox(newState, id1, entity1).collisions
              ->Belt.List.get(1)
              ->getEntity
              === "None",
            );

            _assert(
              getCollideBox(newState, id2, entity2).collisions
              ->Belt.List.get(0)
              ->getEntity
              === entity3 ++ id3,
            );
            _assert(
              getCollideBox(newState, id2, entity2).collisions
              ->Belt.List.get(1)
              ->getEntity
              === entity1 ++ id1,
            );

            _assert(
              getCollideBox(newState, id3, entity3).collisions
              ->Belt.List.get(0)
              ->getEntity
              === entity2 ++ id2,
            );
            _assert(
              getCollideBox(newState, id3, entity3).collisions
              ->Belt.List.get(1)
              ->getEntity
              === "None",
            );
          }
        );
    });
  });
};
