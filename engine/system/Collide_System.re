let detectAABBcollision = ((x1, y1), (x2, y2), (x3, y3)) =>
  x1 < x3 && x2 > x3 && y1 < y3 && y2 > y3;

let update = (~state: Shared.state): Shared.state => {
  ...state,
  collideBox:
    Belt.Map.String.mapWithKey(
      state.collideBox,
      (entity, collideBox) => {
        let transform = Belt.Map.String.get(state.transform, entity);

        switch (transform) {
        | None => collideBox
        | Some(transform) =>
          let collisionList = Belt.Map.String.reduce(
            state.collideBox,
            [],
            (acc, entity2, collideBox2) => { 
              let isLeftButtonClicked = state.mouseButtons != 0;
              let isHovered =
                detectAABBcollision(
                  transform.position,
                  Vector_Util.add(transform.position, collideBox.size),
                  state.mousePosition,
                );

              if(isHovered) {
                [Shared.Box(entity2), ...acc];
              } else {
                acc
              }
            });

          {
            ...collideBox, 
            collisions: collisionList,
          }
        };
      }
    )
};