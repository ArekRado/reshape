let create = (~entity, ~name, ~state: Type.state, ~value): Type.state => {
  ...state,
  fieldString:
    Belt.Map.String.set(
      state.fieldString,
      entity ++ name,
      {entity, name, value},
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  fieldString: Belt.Map.String.remove(state.fieldString, entity ++ name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  fieldString:
    Belt.Map.String.keep(state.fieldString, (_, fieldString) =>
      fieldString.entity !== entity
    ),
};

let setValue =
    (~entity: Type.entity, ~state: Type.state, ~name: string, ~value: string) => {
  ...state,
  fieldString:
    Belt.Map.String.update(state.fieldString, entity ++ name, fieldString =>
      switch (fieldString) {
      | Some(fieldString) => Some({...fieldString, value})
      | None => fieldString
      }
    ),
};

let get = (~entity: Type.entity, ~state: Type.state, ~name: string) => 
  Belt.Map.String.get(state.fieldString, entity ++ name)