let create = (~entity, ~name, ~state: Type.state, ~value): Type.state => {
  ...state,
  fieldVector: Belt.Map.String.set(state.fieldVector, name, {
    entity,
    value,
  }),
}

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  fieldVector: Belt.Map.String.remove(state.fieldVector, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  fieldVector: Belt.Map.String.keep(
    state.fieldVector,
    (_, fieldVector) => fieldVector.entity !== entity
  ),
};


let setValue = (~state: Type.state, ~name: Type.entity, ~value) => {
  ...state,
  fieldVector: Belt.Map.String.update(state.fieldVector, name, fieldVector =>
    switch fieldVector {
    | Some(fieldVector) =>
      Some({
        ...fieldVector,
        value,
      });
    | None => fieldVector
    }
  )
}