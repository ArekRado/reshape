let create = (
  ~state: Shared.state,
  ~id,
  ~entity,
  ~radius,
  ~position=Vector_Util.zero,
  ()
) : Shared.state => {
  ...state,
  collideCircle: Belt.Map.String.set(state.collideCircle, id, {
    radius,
    position,
    entity,
    collisions: [],
  }),
};