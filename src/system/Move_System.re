let update = (state: Type.state): Type.state => {
  let newState = Belt.List.reduce(state.entity, state, (newState, entity) => {
    /* newState
      |> System.IO.update(entity) 
      |> System.Move.update(entity) */

      newState
  });

  newState;
    /* {
    ...state,
    position: state.position.Map()
  } */
}