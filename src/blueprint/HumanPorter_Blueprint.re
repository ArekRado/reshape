let humanImageUrl: string = [%raw {|require('../assets/human.png').default|}];

let create =
    (
      state: Type.state,
      ~position: Engine.Util.Vector.t,
    ) => {
  let entity = Engine.Entity.generate("HumanPorter");

  let newEngine = Engine.Entity.create(~entity, ~state=state.engine)
    -> Engine.Component.Transform.create(~entity=entity, ~state=_, ())
    -> Engine.Component.Image.create(~entity=entity, ~src=humanImageUrl, ~state=_) /* {
     ...state,
     entity: Belt.List.add(state.entity, entity),
     transform: Engine.Transform.create() Belt.Map.String.set(state.transform, entity, transform),
     image:
       Belt.Map.String.set(
         state.image,
         entity,
         Component.Image.create(humanImage),
       ),
   }; */;

  state
};