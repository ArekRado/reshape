let create = (~entity, ~name, ~state: Type.state, ~value): Type.state => {
  ...state,
  fieldFloat:
    Belt.Map.String.set(
      state.fieldFloat,
      entity ++ name,
      {entity, name, value},
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  fieldFloat: Belt.Map.String.remove(state.fieldFloat, entity ++ name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  fieldFloat:
    Belt.Map.String.keep(state.fieldFloat, (_, fieldFloat) =>
      fieldFloat.entity !== entity
    ),
};

let setValue =
    (~entity: Type.entity, ~state: Type.state, ~name: string, ~value: float) => {
  ...state,
  fieldFloat:
    Belt.Map.String.update(state.fieldFloat, entity ++ name, fieldFloat =>
      switch (fieldFloat) {
      | Some(fieldFloat) => Some({...fieldFloat, value})
      | None => fieldFloat
      }
    ),
};

let get = (~entity: Type.entity, ~state: Type.state, ~name: string) => 
  Belt.Map.String.get(state.fieldFloat, entity ++ name)