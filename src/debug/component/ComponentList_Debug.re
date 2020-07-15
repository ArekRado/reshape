type entityComponents = {
  transform: option(Type.transform),
  sprite: option(Type.sprite),
  animationFloat: Belt.Map.String.t(Type.animation(float)),
  animationVector: Belt.Map.String.t(Type.animation(Vector_Util.t)),
}

let getComponents = (entity, state: Type.state):entityComponents => {
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

[@react.component]
let make = (
  ~gameState: Type.state,
  ~entity,
) => {
  let components = getComponents(entity, gameState);

  <>  
    <div className="text-white mb-3">
      {React.string("Components")}
    </div>
    
    <Transform_Debug transform={components.transform}/>
    <Sprite_Debug sprite={components.sprite}/>
    <AnimationFloat_Debug items={components.animationFloat}/>
  </>
}
