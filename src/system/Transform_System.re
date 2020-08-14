let rec getParentPosition =
        (transformMap: Belt.Map.String.t(Type.transform), parentEntity)
        : Vector_Util.t => {
  let parent = Belt.Map.String.get(transformMap, parentEntity);

  switch (parent) {
  | None => (0.0, 0.0)
  | Some(parent) =>
    switch (parent.parent) {
    | None => parent.localPosition
    | Some(parentParent) =>
      Vector_Util.add(
        getParentPosition(transformMap, parentParent),
        parent.localPosition,
      )
    }
  };
};

let update = (~state: Type.state): Type.state => {
  ...state,
  transform:
    Belt.Map.String.map(state.transform, transform =>
      switch (transform.parent) {
      | None => {...transform, position: transform.localPosition}
      | Some(parentEntity) =>
        let position =
          Vector_Util.add(
            transform.localPosition,
            getParentPosition(state.transform, parentEntity),
          );

        {...transform, position};
      }
    ),
};
