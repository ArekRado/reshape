let humanSpriteUrl: string = [%raw {|require('../assets/human.png').default|}];

let create =
    (
      state: Type.state,
      ~localPosition: Engine.Util.Vector.t,
    ) => {
  let entity = Engine.Entity.generate("HumanPorter");

  {
    ...state,
    engine: Engine.Entity.create(~entity, ~state=state.engine)
    ->Engine.Component.Transform.create(~entity, ~localPosition, ~state=_, ())
    ->Engine.Component.Sprite.create(~entity, ~src=humanSpriteUrl, ~state=_, ())
  };
};
