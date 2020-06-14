[@bs.scope "Math"] [@bs.val] external random: unit => float = "random";

type updateAcc = {
  localPosition: Engine.Util.Vector.t,
  target: Engine.Util.Vector.t,
  cityEntity: string,
};

let update = (state: Type.state): Type.state => {
  let humanPortersToCreate = Belt.Map.String.reduce(
    state.game.city,
    []: Belt.List.t(updateAcc),
    (acc, entity, city) => {
      let buildTimer = Belt.Map.String.findFirstBy(
          state.engine.animationFloat,
          (_, animation) => animation.entity === entity && animation.name === "buildTimer"
      );

      switch (buildTimer) {
      | Some((_, buildTimer)) =>
        if (buildTimer.isFinished) {
          let newHumanPorter = {
            localPosition: (random() *. 500.0, random() *. 500.0),
            target: (random() *. 500.0, random() *. 500.0),
            cityEntity: entity,
          };

          [newHumanPorter, ...acc];
        } else {
          acc
        }
        | _ => acc
      };
    });


    Belt.List.reduce(
      humanPortersToCreate,
      state,
      (newState, newHumanPorter) => Blueprint.HumanPorter.create(
        ~state=newState, 
        ~localPosition=newHumanPorter.localPosition
      )
    )
  };