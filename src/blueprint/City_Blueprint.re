let citySpriteUrl: string = [%raw {|require('../assets/city.png').default|}];
let circleSpriteUrl: string = [%raw {|require('../assets/circle.png').default|}] 

let create =
    (state: Type.state, ~localPosition: Engine.Util.Vector.t): Type.state => {
  let cityEntity = Engine.Entity.generate("city");
  let circleEntity = Engine.Entity.generate("cityCircle")

  let buildTimer = Engine.Entity.generate("buildTimer")

  let newGameState = state.game
    ->Component.City.create(
      ~entity=cityEntity,
      ~state=_, 
      ()
    );

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
      ~localPosition=localPosition,
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
      ~parent=Some(cityEntity),
      ~state=_,
      ()
    )
    // buildTimer
    ->Engine.Component.AnimationFloat.create(
      ~entity=cityEntity,
      ~name=buildTimer,
      ~isPlaying=true,
      ~keyframes=[
        {duration: 2500.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Shared.keyframe(float),
      ],
      ~wrapMode=Loop,
      ~state=_,
      ()
    );
      
  {
    game: newGameState,
    engine: newEngine,
  }
};