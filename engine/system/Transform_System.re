let update = (~state: Shared.state): Shared.state => {
  ...state,
  transform:
    Belt.Map.String.map(state.transform, transform =>
      switch (transform.parent) {
        | None => transform
        | Some(parentEntity) => 
          let parent = Belt.Map.String.get(state.transform, parentEntity);
          switch (parent) {
            | None => transform
            | Some(parent) => 
              let position = Vector_Util.add(transform.localPosition, parent.position);
              
              {
                ...transform,
                position
              };
          };
      }
  )
};