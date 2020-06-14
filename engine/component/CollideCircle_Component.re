let create = (
  ~state: Shared.state,
  ~name,
  ~entity,
  ~radius,
  ~position=Vector_Util.zero,
  ()
) : Shared.state => {
  ...state,
  collideCircle: Belt.Map.String.set(state.collideCircle, name, {
    radius,
    position,
    entity,
    collisions: [],
  }),
};