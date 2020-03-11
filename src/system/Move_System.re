let update =
    ((state: Type.state, engine: Engine.Shared.state))
    : (Type.state, Engine.Shared.state) => (
  /* let newState = Belt.Map.String.reduce(state.entity, state, (newState, entity) => {
          newState
           |> System.IO.update(entity)
           |> System.Move.update(entity)

           newState
       }); */
  state,
  engine,
);