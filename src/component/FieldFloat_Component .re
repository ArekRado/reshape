let create = (~entity, ~name, ~state, ~value) => {
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