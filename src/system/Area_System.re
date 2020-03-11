open Belt;
[@bs.scope "Math"] [@bs.val] external random : unit => float = "random";

let update =
    ((state: Type.state, engine: Engine.Shared.state))
    : (Type.state, Engine.Shared.state) =>
  List.reduce(
    state.entity,
    state,
    (newState, entity) => {
      let area = Map.String.get(state.area, entity);
      let timer =
        Map.String.getWithDefault(
          state.timer,
          entity,
          Component.Timer.create(1.0),
        );

      switch (area) {
      | None => newState
      | Some(_) =>
        if (timer.isDone) {
          Blueprint.HumanPorter.create(
            (newState, engine),
            ~position=(random() *. 1200.0, random() *. 700.0),
          );
        } else {
          (newState, engine);
        }
      };
    },
  );

  20 x 68 x 52