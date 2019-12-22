[@bs.module "../utils/pixiDraw"] external pixiDraw : list(string) => unit = "default";

let update = (state: Type.state) => {
  let drawState: list(string) = Belt.List.reduce(state.entity, [], (images, entity) => {
    let image = Belt.Map.String.get(state.image, entity);

    switch (image) {
      | None => images
      | Some(img) => {
          let (x, y) = Belt.Map.String.getWithDefault(state.position, entity, Vector.create(0.0, 0.0));
          let src = img.src;

          Belt.List.add(images, {j|{
            "entity":"$(entity)",
            "src":"$(src)",
            "x":"$(x)",
            "y":"$(y)"
          }|j})
        }
      };
  });

  pixiDraw(drawState);
  state;
};