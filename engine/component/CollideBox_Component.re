let create = (
  ~state: Shared.state,
  ~id,
  ~entity,
  ~size,
  ~position=Vector_Util.zero,
  ()
) : Shared.state => {
  ...state,
  collideBox: Belt.Map.String.set(state.collideBox, id, {
    size,
    position,
    entity,
    collisions: [],
  }),
};