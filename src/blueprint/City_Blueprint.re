open Belt;

let cityImage: string = [%raw {|require('../assets/city.png').default|}];
let circleImage: string = [%raw {|require('../assets/circle.png').default|}];

let createCircle = (entity,state:Type.state):Type.state => {
  ...state,
  entity: List.add(state.entity, entity),
  image:
  Map.String.set(state.image, entity, Component.Image.create(circleImage)),
  position: Map.String.set(state.position, entity, Vector.zero()),
};

let create = (state: Type.state, ~position: Type.vector): Type.state => {
  let entity = Util.Uuid.v4();
  let circleEntity = Util.Uuid.v4();

  state 
    |> createCircle(circleEntity)
    |> (state) => {
        ...state,
        entity: List.add(state.entity, entity),
        position: Map.String.set(state.position, entity, position),
        image:
          Map.String.set(state.image, entity, Component.Image.create(cityImage)),
        area: Map.String.set(state.area, entity, {areaType: City}),
        timer:
          Map.String.set(state.timer, entity, Component.Timer.create(20.0)),
        children: Map.String.set(
          state.children, 
          entity, 
          [circleEntity]
        )
    };
};