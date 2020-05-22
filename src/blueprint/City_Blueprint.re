let cityImageUrl: string = [%raw {|require('../assets/city.png').default|}];
let circleImageUrl: string = [%raw {|require('../assets/circle.png').default|}] 

let create =
    (state: Type.state, ~position: Type.vector) => {
  let cityEntity = Engine.Entity.generate("City");
  let circleEntity = Engine.Entity.generate("CityCircle")

  let newEngine = state.engine
    // city
    ->Engine.Entity.create(
      ~entity=cityEntity,
      ~state=_,
    )
    ->Engine.Component.Image.create(
        ~entity=cityEntity,
        ~src=cityImageUrl,
        ~state=_, 
        ()
    )
    ->Engine.Component.Transform.create(
      ~entity=cityEntity,
      ~position=position,
      ~state=_, 
      ()
    )
    // circle
    ->Engine.Entity.create(
      ~entity=circleEntity,
      ~state=_,
    )
    ->Engine.Component.Image.create(
      ~entity=circleEntity, 
      ~src=circleImageUrl, 
      ~state=_, 
      ()
    )
    ->Engine.Component.Transform.create(
      ~entity=circleEntity, 
      ~parent=cityEntity,
      ~state=_,
      ()
    );
      
  {
    ...state,
    engine: newEngine,
  }
};