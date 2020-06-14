[@react.component]
let make = (~dispatch) => {
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
        dispatch(Type_Debug.CreateEntity(entity));
      }}
    >
      {React.string("Add entity")}
    </Button_UI>
  </div>
}