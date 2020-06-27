let create = (
  ~state: Type.state,
  ~name,
  ~entity,
  ~radius,
  ~position=Vector_Util.zero,
  ()
) : Type.state => {
  ...state,
  collideCircle: Belt.Map.String.set(state.collideCircle, name, {
    radius,
    position,
    entity,
    collisions: [],
  }),
};