let create = (
  ~state: Shared.state,
  ~name,
  ~entity,
  ~size,
  ~position=Vector_Util.zero,
  ()
) : Shared.state => {
  ...state,
  collideBox: Belt.Map.String.set(state.collideBox, name, {
    size,
    position,
    entity,
    collisions: [],
  }),
};