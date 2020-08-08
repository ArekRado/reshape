let create = (~entity, ~name, ~state: Type.state, ~value): Type.state => {
  ...state,
  fieldFloat: Belt.Map.String.set(state.fieldFloat, name, {
    entity,
    value,
  }),
}

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  fieldFloat: Belt.Map.String.remove(state.fieldFloat, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  fieldFloat: Belt.Map.String.keep(
    state.fieldFloat,
    (_, fieldFloat) => fieldFloat.entity !== entity
  ),
};


let setValue = (~state: Type.state, ~name: Type.entity, ~value: float) => {
  ...state,
  fieldFloat: Belt.Map.String.update(state.fieldFloat, name, fieldFloat =>
    switch fieldFloat {
    | Some(fieldFloat) =>
      Some({
        ...fieldFloat,
        value,
      });
    | None => fieldFloat
    }
  )
}