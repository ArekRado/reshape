[@react.component]
let make = () => {
  let (editorState, editorDispatch) = React.useContext(Editor_Context.context);
  let (appState, appDispatch) = React.useContext(App_Context.context);

  let (entity, setEntity) = React.useState(_ => "");

  <div>
    <Input_UI 
      label="entity" 
      value={entity} 
      onChange={event => setEntity(ReactEvent.Form.target(event)##value)}
    />
    <Button_UI 
      size={Button_UI.Xs}
      onClick={(_) => {
        setEntity((_) => "");
        appDispatch(CreateEntity(entity));
        editorDispatch(SelectEntity(entity));
      }}
    >
      {React.string("Add entity")}
    </Button_UI>
  </div>
}