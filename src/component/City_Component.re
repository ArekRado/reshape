let create =
    (
      ~entity: Belt.Map.String.key,
      ~state: Type.gameState,
      ()
    ) : Type.gameState => {
  ...state,
  city: Belt.Map.String.set(state.city, entity, {
    size: 1.0
  }),
};