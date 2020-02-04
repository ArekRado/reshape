open Belt;

let update = (state: Shared.state): Shared.state => {
  {
    ...state,
    rigidbody: Map.String.mapWithKey(state.rigidbody, (entity, rigidbody) => {
      let position = Map.String.get(state.position, entity);
  
      switch (position) {
        | (None) => rigidbody
        | (Some(position)) => {
          let isLeftButtonClicked = state.mouseButtons != 0;
          let isHovered = Vector.isBetween( 
            position,
            Vector.add(position, rigidbody.size),
            state.mousePosition
          );

          {
            ...rigidbody,
            isClicked: isHovered && isLeftButtonClicked,
            isHovered: isHovered,
          };
        }
      };
    })
  }
}

