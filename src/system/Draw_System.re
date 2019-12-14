type drawObject = {
  entity: string,
  position: Type.vector,
};

[@bs.module "../utils/pixiDraw"] external pixiDraw : list(drawObject) => unit = "default";

let update = (state: Type.state) => {
  let drawState: list(drawObject) = Belt.List.reduce(state.entity, [], (images, entity) => {
    let image = Belt.Map.String.get(state.image, entity);

    switch (image) {
      | None => images
      | Some(image) => {
          Belt.List.add(images, {
            entity: entity,
            position: Belt.Map.String.getWithDefault(state.position, entity, Vector.create(0.0, 0.0))
          })
        }
      };
  });

  pixiDraw(drawState);
};