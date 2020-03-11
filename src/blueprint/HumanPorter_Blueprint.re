let humanImageUrl: string = [%raw {|require('../assets/human.png').default|}];

let create =
    (
      (state, engine): (Type.state, Engine.Shared.state),
      ~position: Engine.Util.Vector.t,
    ) => {
  let entity = Engine.Entity.generate();

  let newEngine =
    engine
    |> Engine.Entity.create(entity)
    |> Engine.Component.Transform.create(entity)
    |> Engine.Component.Image.create(entity, ~src=humanImageUrl) /* {
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

  (state, newEngine);
};