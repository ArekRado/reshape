let create =
    (
      ~state: Type.state,
      ~name: string,
      ~entity: Type.entity,
      ~radius,
      ~position=Vector_Util.zero,
      (),
    )
    : Type.state => {
  ...state,
  collideCircle:
    Belt.Map.String.set(
      state.collideCircle,
      entity ++ name,
      {radius, position, entity, collisions: [], name},
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  collideCircle: Belt.Map.String.remove(state.collideCircle, entity ++ name),
};

let removeByEntity = (~entity: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  collideCircle:
    Belt.Map.String.keep(state.collideCircle, (_, collideCircle) =>
      collideCircle.entity !== entity
    ),
};

let get = (~entity: Type.entity, ~state: Type.state, ~name: string) => 
  Belt.Map.String.get(state.collideCircle, entity ++ name);
