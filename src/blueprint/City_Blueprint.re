let citySpriteUrl: string = [%raw {|require('../assets/city.png').default|}];
let circleSpriteUrl: string = [%raw {|require('../assets/circle.png').default|}] 

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
    ->Engine.Component.Sprite.create(
        ~entity=cityEntity,
        ~src=citySpriteUrl,
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
    ->Engine.Component.Sprite.create(
      ~entity=circleEntity, 
      ~src=circleSpriteUrl, 
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