open Belt;

let update = (state: Shared.state) : Shared.state => {
  ...state,
  rigidbody:
    Map.String.mapWithKey(
      state.rigidbody,
      (entity, rigidbody) => {
        let transform = Map.String.get(state.transform, entity);

        switch (transform) {
        | None => rigidbody
        | Some(transform) =>
          let isLeftButtonClicked = state.mouseButtons != 0;
          let isHovered =
            Vector_Util.isBetween(
              transform.position,
              Vector_Util.add(transform.position, rigidbody.size),
              state.mousePosition,
            );

          {
            ...rigidbody,
            isClicked: isHovered && isLeftButtonClicked,
            isHovered,
          };
        };
      },
    ),
};