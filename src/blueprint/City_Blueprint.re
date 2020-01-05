open Belt;

let cityImage: string = [%raw {|require('../assets/city.png').default|}];

let create = (state: Type.state, ~position: Type.vector) => {
  let entity = Util.Uuid.v4();

  {
    ...state,
    entity: List.add(state.entity, entity),
    position: Map.String.set(state.position, entity, position),
    image:
      Map.String.set(state.image, entity, Component.Image.create(cityImage)),
    area: Map.String.set(state.area, entity, {areaType: City}),
    timer:
      Map.String.set(state.timer, entity, Component.Timer.create(20.0)),
  };
};