let humanImage: string = [%raw {|require('../assets/human.png').default|}];

let create = (state: Type.state, ~transform: Engine.Shared.transform) => {
  let entity = Engine.Util.Uuid.v4();

  {
    ...state,
    entity: Belt.List.add(state.entity, entity),
    transform: Belt.Map.String.set(state.transform, entity, transform),
    image:
      Belt.Map.String.set(
        state.image,
        entity,
        Component.Image.create(humanImage),
      ),
  };
};