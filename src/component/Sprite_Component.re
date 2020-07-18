let create =
    (~src: string, ~entity: Belt.Map.String.key, ~state: Type.state)
    : Type.state => {
  ...state,
  sprite: Belt.Map.String.set(state.sprite, entity, {src: src}),
};

let remove = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  sprite: Belt.Map.String.remove(state.sprite, entity),
};