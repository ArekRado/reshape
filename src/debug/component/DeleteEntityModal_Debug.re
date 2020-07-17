let getEntity = modalData => 
  switch(modalData) {
  | Modal_Context.Entity(entity) => entity
  | _ => ""
  };

[@react.component]
let make = () => {
  let (_, editorDispatch) = React.useContext(Editor_Context.context);
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  <Modal_UI 
    name="DeleteEntity"
    render={(modal: Modal_Context.modal) => {
      <>
        <div> {React.string("Are you sure you want to remove entity")}</div>
        <div> {React.string("entity")}</div>

        <Button_UI 
          onClick={(_) => modalDispatch(CloseModal("DeleteEntity"))} 
        >
          {React.string("Cancel")}
        </Button_UI>

        <Button_UI 
          onClick={(_) => {
            modalDispatch(CloseModal("DeleteEntity"));
            editorDispatch(SelectEntity(""));
            appDispatch(DeleteEntity(getEntity(modal.data)));
          }} 
        >
          {React.string("Delete")}
        </Button_UI>
      </>
    }}
  />
}