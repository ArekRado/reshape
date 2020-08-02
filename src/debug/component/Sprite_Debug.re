[@react.component]
let make = (~sprite: option(Type.sprite)) => {
  let (appState, appDispatch) = React.useContext(App_Context.context);
  let (editorState, _) = React.useContext(Editor_Context.context);

  switch (sprite) {
  | Some(sprite) => 
    <div className="grid grid-cols-12 gap-1 mt-3">
      <div className="text-white mb-3 col-span-12">
        {React.string("Sprite")}
      </div>

      <div className="col-span-4">{React.string("src")}</div>
      <div className="col-span-8">
        <Select_UI
          value={sprite.src}
          onChange={event => appDispatch(SetSpriteSrc(editorState.selectedEntity, ReactEvent.Form.target(event)##value))}
          options={Belt.List.map(
            appState.asset.sprite, 
            (src): Select_UI.selectOption => {
                value: src,
                text: src,
                disabled: false,
            }
          )}
        />
      </div>
      <div className="col-span-12"><img src={sprite.src} /></div>
    </div>
  | None => React.null
  };
};