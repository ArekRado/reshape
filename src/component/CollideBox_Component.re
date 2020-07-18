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

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  collideBox: Belt.Map.String.remove(state.collideBox, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  collideBox: Belt.Map.String.keep(
    state.collideBox,
    (_, collideBox) => collideBox.entity !== entity
  ),
};