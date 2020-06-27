let create = (
  ~state: Type.state,
  ~name,
  ~entity,
  ~size,
  ~position=Vector_Util.zero,
  ()
) : Type.state => {
  ...state,
  collideBox: Belt.Map.String.set(state.collideBox, name, {
    size,
    position,
    entity,
    collisions: [],
  }),
};