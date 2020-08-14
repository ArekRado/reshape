[@bs.module "../util/pixiDraw"]
external pixiDraw: (array(string), bool) => unit = "default";

let update = (~state: Type.state, ~enableDraw: bool): Type.state => {
  let drawState: Js.Array2.t(string) = [||];

  Belt.List.forEach(
    state.entity,
    entity => {
      let sprite = Belt.Map.String.get(state.sprite, entity);
      let transform = Belt.Map.String.get(state.transform, entity);

      switch (sprite, transform) {
      | (None, None) => ()
      | (Some(_), None) => ()
      | (None, Some(_)) => ()
      | (Some(img), Some(transform)) =>
        let (x, y) = transform.position;
        let src = img.src;

        let _ =
          Js.Array2.push(
            drawState,
            {j|{
            "entity":"$(entity)",
            "src":"$(src)",
            "x":"$(x)",
            "y":"$(y)"
          }|j},
          );

        ();
      };
    },
  );

  if (enableDraw === true && Js.Array2.length(drawState) > 0) {
    pixiDraw(drawState, state.isDebugInitialized);
  };

  state;
};
