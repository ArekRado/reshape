[@react.component]
let make = () => {
  let (_, editorDispatch) = React.useContext(Editor_Context.context);
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (entity, setEntity) = React.useState(_ => "");

  <div>
    <Input_UI 
      label={React.string("entity")} 
      value={entity} 
      onChange={event => setEntity(ReactEvent.Form.target(event)##value)}
    />
    <Button_UI 
      
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