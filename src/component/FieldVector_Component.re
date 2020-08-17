let create =
    (~entity: Type.entity, ~name: string, ~state: Type.state, ~value)
    : Type.state => {
  ...state,
  fieldVector:
    Belt.Map.String.set(
      state.fieldVector,
      entity ++ name,
      {entity, value, name},
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  fieldVector: Belt.Map.String.remove(state.fieldVector, entity ++ name),
};

let removeByEntity = (~entity: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  fieldVector:
    Belt.Map.String.keep(state.fieldVector, (_, fieldVector) =>
      fieldVector.entity !== entity
    ),
};

let setValue =
    (~state: Type.state, ~name: string, ~entity: Type.entity, ~value) => {
  ...state,
  fieldVector:
    Belt.Map.String.update(state.fieldVector, entity ++ name, fieldVector =>
      switch (fieldVector) {
      | Some(fieldVector) => Some({...fieldVector, value})
      | None => fieldVector
      }
    ),
};

let get = (~entity: Type.entity, ~state: Type.state, ~name: string) => 
  Belt.Map.String.get(state.fieldVector, entity ++ name)