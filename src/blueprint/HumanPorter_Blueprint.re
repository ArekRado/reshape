let humanImage:string = [%raw {|require('./assets/human.png').default|}];


let create = (state: Type.state) => {
  let entity = Util.Uuid.v4();

  {
    ...state,
    entity: [entity, ...state.entity],
    position: Belt.Map.String.set(state.position, entity, Vector.create(0.0, 1.0)),
    image: Belt.Map.String.set(state.image, entity, Component.Image.create(humanImage)),
  }
}