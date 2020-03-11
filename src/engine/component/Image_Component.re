let create =
    (~src: string, entity: Belt.Map.String.key, engine: Shared.state)
    : Shared.state => {
  ...engine,
  image: Belt.Map.String.set(engine.image, entity, {src: src}),
};