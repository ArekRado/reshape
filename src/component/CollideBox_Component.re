let create =
    (
      ~state: Type.state,
      ~name,
      ~entity,
      ~size,
      ~position=Vector_Util.zero,
      (),
    )
    : Type.state => {
  ...state,
  collideBox:
    Belt.Map.String.set(
      state.collideBox,
      entity ++ name,
      {size, position, entity, collisions: [], name},
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  collideBox: Belt.Map.String.remove(state.collideBox, entity ++ name),
};

let removeByEntity = (~entity: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  collideBox:
    Belt.Map.String.keep(state.collideBox, (_, collideBox) =>
      collideBox.entity !== entity
    ),
};

let get = (entity: Type.entity, ~state: Type.state, ~name: string) => 
  Belt.Map.String.get(state.collideBox, entity ++ name)
