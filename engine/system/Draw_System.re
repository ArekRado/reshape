[@bs.module "../util/pixiDraw"]
external pixiDraw: list(string) => unit = "default";

let update = (~state: Shared.state, ~enableDraw:bool): Shared.state => {
  let drawState: Belt.List.t(string) =
    Belt.List.reduce(
      state.entity,
      [],
      (sprites, entity) => {
        let sprite = Belt.Map.String.get(state.sprite, entity);
        let transform = Belt.Map.String.get(state.transform, entity);

        switch (sprite, transform) {
        | (None, None) => sprites
        | (Some(_), None) => sprites
        | (None, Some(_)) => sprites
        | (Some(img), Some(transform)) =>
          let (x, y) = transform.position;
          let src = img.src;

          Belt.List.add(
            sprites,
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