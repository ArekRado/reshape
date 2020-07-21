type entityComponents = {
  transform: option(Type.transform),
  sprite: option(Type.sprite),
  animationFloat: Belt.Map.String.t(Type.animation(float)),
  animationVector: Belt.Map.String.t(Type.animation(Vector_Util.t)),
  collideBox: Belt.Map.String.t(Type.collideBox),
  collideCircle: Belt.Map.String.t(Type.collideCircle),
}

let getComponents = (entity, state: Type.state): entityComponents => {
  transform: Belt.Map.String.get(state.transform, entity),
  sprite: Belt.Map.String.get(state.sprite, entity),
  animationFloat: 
    Belt.Map.String.keep(
      state.animationFloat, 
      (_, animation) => animation.entity === entity
    ),
  animationVector: 
    Belt.Map.String.keep(
      state.animationVector, 
      (_, animation) => animation.entity === entity
    ),
  collideBox: Belt.Map.String.keep(
      state.collideBox, 
      (_, collideBox) => collideBox.entity === entity
    ),
  collideCircle: Belt.Map.String.keep(
      state.collideCircle, 
      (_, collideCircle) => collideCircle.entity === entity
    ),
};

[@react.component]
let make = () => {
  let (editorState, _) = React.useContext(Editor_Context.context);
  let (appState, _) = React.useContext(App_Context.context);

  let components = getComponents(editorState.selectedEntity, appState);

  <>  
    <div className="text-white mb-3">
      {React.string("Components")}
    </div>
    
    <Transform_Debug transform={components.transform}/>
    <Sprite_Debug sprite={components.sprite}/>
    <AnimationFloat_Debug items={components.animationFloat}/>
    <AnimationVector_Debug items={components.animationVector}/>
    <CollideBox_Debug items={components.collideBox}/>
    <CollideCircle_Debug items={components.collideCircle}/>
  </>
}
