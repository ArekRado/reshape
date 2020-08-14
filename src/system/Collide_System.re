let detectAABBcollision =
    ((x1, y1), (size1x, size1y), (x2, y2), (size2x, size2y)) =>
  x1 < x2
  +. size2x
  && x1
  +. size1x > x2
  && y1 < y2
  +. size2y
  && y1
  +. size1y > y2;

let update = (~state: Type.state): Type.state => {
  ...state,
  collideBox:
    Belt.Map.String.mapWithKey(
      state.collideBox,
      (id1, collideBox1) => {
        let transform =
          Belt.Map.String.get(state.transform, collideBox1.entity);

        switch (transform) {
        | None => collideBox1
        | Some(transform) =>
          let collisionList =
            Belt.Map.String.reduce(
              state.collideBox,
              [],
              (acc, id2, collideBox2) => {
                let transform2 =
                  Belt.Map.String.get(state.transform, collideBox2.entity);

                switch (transform2, id2 === id1) {
                | (None, _) => acc
                | (_, true) => acc
                | (Some(transform2), _) =>
                  let isColliding =
                    detectAABBcollision(
                      Vector_Util.add(
                        transform.position,
                        collideBox1.position,
                      ),
                      collideBox1.size,
                      Vector_Util.add(
                        transform2.position,
                        collideBox2.position,
                      ),
                      collideBox2.size,
                    );

                  if (isColliding) {
                    [Type.Box(id2), ...acc];
                  } else {
                    acc;
                  };
                };
              },
            );

          {...collideBox1, collisions: collisionList};
        };
      },
    ),
};
