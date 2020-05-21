let humanImageUrl: string = [%raw {|require('../assets/human.png').default|}];

let create =
    (
      state: Type.state,
      ~position: Engine.Util.Vector.t,
    ) => {
  let entity = Engine.Entity.generate("HumanPorter");

  {
    ...state,
    engine: Engine.Entity.create(~entity, ~state=state.engine)
    ->Engine.Component.Transform.create(~entity, ~position, ~state=_, ())
    ->Engine.Component.Image.create(~entity, ~src=humanImageUrl, ~state=_, ())
  };
};
