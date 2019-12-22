let humanImage:string = [%raw {|require('./assets/human.png').default|}];


let create = state => {
  let entity = Util.Uuid.v4();

  {
    ...state,
    entity: [entity],
    position: Belt.Map.String.set(initialState.position, entity, Vector.create(0.0, 1.0)),
    image: Belt.Map.String.set(initialState.image, entity, Component.Image.create(humanImage)),
  }
}