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

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  collideCircle: Belt.Map.String.remove(state.collideCircle, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  collideCircle: Belt.Map.String.keep(
    state.collideCircle,
    (_, collideCircle) => collideCircle.entity !== entity
  ),
};