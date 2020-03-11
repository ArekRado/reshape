open Belt;

let cityImageUrl: string = [%raw {|require('../assets/city.png').default|}];
let circleImageUrl: string = [%raw {|require('../assets/circle.png').default|}] /* let createCircle = (entity, engine, state: Type.state) : Type.state => {
  let newEngine =
    Engine.Entity.create(engine, entity)
    |> (
      engine =>
        Engine.Transform.create(engine, entity)
        |> (engine => Engine.Component.Image.create(engine, entity))
    );

  (state, engine);
} /* {
  ...state,
  entity: List.add(state.entity, entity),
  image:
    Map.String.set(state.image, entity, Component.Image.create(circleImage)),
  transform: Map.String.set(state.transform, entity),
}; */; */;

let create =
    ((state: Type.state, engine: Engine.Shared.state), ~position: Type.vector)
    : (Type.state, Engine.Shared.state) => {
  let entity = Engine.Entity.generate();
  let circleEntity = Engine.Entity.generate() /* ->Engine.Component.Image.create(
        entity,
         ~src=cityImageUrl
         )
      ->Engine.Component.Transform.create(entity, ~position=position, ~children=[circleEntity])
      /* circle */
      ->Engine.Entity.create(entity)
      ->Engine.Component.Image.create(entity, ~src=circleImageUrl)
      ->Engine.Component.Transform.create(entity) */ /* Engine.Entity.create(entity, engine) */ /* city */;

  ({
    ...state /* entity: List.add(state.entity, entity),
      position: Map.String.set(state.position, entity, position),
      image:
        Map.String.set(
          state.image,
          entity,
          Component.Image.create(cityImage),
        ), */,
    area: Map.String.set(state.area, entity, {areaType: City}) /* children: Map.String.set(state.children, entity, [circleEntity]), */ /* timer:
        Map.String.set(state.timer, entity, Component.Timer.create(20.0)), */,
  }, engine)
};