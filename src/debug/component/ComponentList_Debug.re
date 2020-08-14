type entityComponents = {
  transform: option(Type.transform),
  sprite: option(Type.sprite),
  animation: Belt.Map.String.t(Type.animation),
  collideBox: Belt.Map.String.t(Type.collideBox),
  collideCircle: Belt.Map.String.t(Type.collideCircle),
  fieldFloat: Belt.Map.String.t(Type.field(float)),
};

let getComponents = (entity, state: Type.state): entityComponents => {
  transform: Belt.Map.String.get(state.transform, entity),
  sprite: Belt.Map.String.get(state.sprite, entity),
  animation:
    Belt.Map.String.keep(state.animation, (_, animation) =>
      animation.entity === entity
    ),
  collideBox:
    Belt.Map.String.keep(state.collideBox, (_, collideBox) =>
      collideBox.entity === entity
    ),
  collideCircle:
    Belt.Map.String.keep(state.collideCircle, (_, collideCircle) =>
      collideCircle.entity === entity
    ),
  fieldFloat:
    Belt.Map.String.keep(state.fieldFloat, (_, fieldFloat) =>
      fieldFloat.entity === entity
    ),
};

[@react.component]
let make = () => {
  let (editorState, _) = React.useContext(Editor_Context.context);
  let (appState, _) = React.useContext(App_Context.context);

  let components = getComponents(editorState.selectedEntity, appState);

  <>
    <div className="text-white mb-3"> {React.string("Components")} </div>
    <FieldFloat_Debug items={components.fieldFloat} />
    <Transform_Debug transform={components.transform} />
    <Sprite_Debug sprite={components.sprite} />
    <Animation_Debug items={components.animation} />
    <CollideBox_Debug items={components.collideBox} />
    <CollideCircle_Debug items={components.collideCircle} />
  </>;
};
