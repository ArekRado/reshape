let runTests = () => {
  Test_Util.describe("Entity", it => {
    it(
      "should remove entity and all components connected with endity", _assert => {
      let entity = Entity.generate("entity");

      let state =
        Type.initialState
        ->Entity.create(~entity, ~state=_)
        ->Transform_Component.create(
            ~entity,
            ~localPosition=((-10.0), (-10.0)),
            ~parent=Some(entity),
            ~state=_,
            (),
          )
        ->Sprite_Component.create(~entity, ~src="", ~state=_)
        ->Animation_Component.create(
            ~component=Type.FieldFloat(""),
            ~keyframes=[],
            ~entity,
            ~name="AnimationFloat",
            ~state=_,
            (),
          )
        ->CollideBox_Component.create(
            ~entity,
            ~state=_,
            ~name="CollideBox",
            ~size=Vector_Util.create(1.0, 1.0),
            (),
          )
        ->CollideCircle_Component.create(
            ~entity,
            ~state=_,
            ~name="CollideCircle",
            ~radius=1.0,
            (),
          );

      let stateWithoutEntity = Entity.remove(~entity, ~state);

      _assert(Belt.List.length(stateWithoutEntity.entity) === 0);
      _assert(Belt.Map.String.size(stateWithoutEntity.transform) === 0);
      _assert(Belt.Map.String.size(stateWithoutEntity.sprite) === 0);
      _assert(Belt.Map.String.size(stateWithoutEntity.animation) === 0);
      _assert(Belt.Map.String.size(stateWithoutEntity.collideBox) === 0);
      _assert(Belt.Map.String.size(stateWithoutEntity.collideCircle) === 0);

      ();
    })
  });
};
