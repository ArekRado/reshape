let create =
    (~src: string, ~entity: Belt.Map.String.key, ~state: Shared.state, ())
    : Shared.state => {
  ...state,
  image: Belt.Map.String.set(state.image, entity, {src: src}),
};