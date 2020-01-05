let humanImage: string = [%raw {|require('../assets/human.png').default|}];

let create = (state: Type.state, ~position: Type.vector) => {
  let entity = Util.Uuid.v4();

  {
    ...state,
    entity: Belt.List.add(state.entity, entity),
    position: Belt.Map.String.set(state.position, entity, position),
    image:
      Belt.Map.String.set(
        state.image,
        entity,
        Component.Image.create(humanImage),
      ),
  };
};