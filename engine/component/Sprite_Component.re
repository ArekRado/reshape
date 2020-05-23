let create =
    (~src: string, ~entity: Belt.Map.String.key, ~state: Shared.state, ())
    : Shared.state => {
  ...state,
  sprite: Belt.Map.String.set(state.sprite, entity, {src: src}),
};