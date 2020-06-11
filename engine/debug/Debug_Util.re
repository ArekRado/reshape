type entityComponents = {
  transform: option(Shared.transform),
  sprite: option(Shared.sprite),
  animationFloat: Belt.Map.String.t(Shared.animation(float)),
  animationVector: Belt.Map.String.t(Shared.animation(Vector_Util.t)),}

let getComponents = (entity, state: Shared.state):entityComponents => {
  transform: Belt.Map.String.get(state.transform, entity),
  sprite: Belt.Map.String.get(state.sprite, entity),
  animationFloat: 
    Belt.Map.String.reduce(
      state.animationFloat, 
      Belt.Map.String.empty, 
      (items, key, animation) => {
        if(animation.entity === entity) {
          Belt.Map.String.set(items, key, animation);
        } else {
          items
        }
      }
    ),
  animationVector: 
    Belt.Map.String.reduce(
      state.animationVector, 
      Belt.Map.String.empty, 
      (items, key, animation) => {
        if(animation.entity === entity) {
          Belt.Map.String.set(items, key, animation);
        } else {
          items
        }
      }
    ),
};