[@bs.scope "Math"] [@bs.val] external random: unit => float = "random";

let update = (state: Type.state): Type.state => {
  

  {
    ...state,
    game: {
      ...state.game,
      city: Belt.Map.String.mapWithKey(
        state.game.city,
        (entity, newState) => {
          let city = Belt.Map.String.get(state.game.city, entity);
          let buildTimer = Belt.Map.String.findFirstBy(
              state.engine.animationFloat,
              (_, animation) => animation.entity === entity && animation.name === "buildTimer"
          )


          switch (city, buildTimer) {
          | (Some(city), Some((_, buildTimer))) =>
            if (buildTimer.isFinished) {
              // let (a,b) = Blueprint.HumanPorter.create(
              //   (newState, engine),
              //   ~position=(random() *. 1200.0, random() *. 700.0),
              // );

              city
            } else {
              city
            }
            | _ => newState
          };
        })
      }
    }
  };