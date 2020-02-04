let create = (engine, entity, image: Shared.image) : Shared.state => {
  {
    ...engine,
    image:
      Belt.Map.String.set(
        state.image,
        entity,
        {src: src}
      ),
  }
};