[@bs.module "../util/pixiDraw"]
external pixiDraw: list(string) => unit = "default";

let update = (~state: Shared.state, ~enableDraw:bool): Shared.state => {
  let drawState: Belt.List.t(string) =
    Belt.List.reduce(
      state.entity,
      [],
      (images, entity) => {
        let image = Belt.Map.String.get(state.image, entity);
        let transform = Belt.Map.String.get(state.transform, entity);

        switch (image, transform) {
        | (None, None) => images
        | (Some(_), None) => images
        | (None, Some(_)) => images
        | (Some(img), Some(transform)) =>
          let (x, y) = transform.position;
          let src = img.src;

          Belt.List.add(
            images,
            {j|{
                "entity":"$(entity)",
                "src":"$(src)",
                "x":"$(x)",
                "y":"$(y)"
              }|j},
          );
        };
      },
    );

  if(enableDraw === true && Belt.List.size(drawState) > 0) {
    pixiDraw(drawState);
  }

  state;
};