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
    name="RemoveEntity"
    render={(modal: Modal_Context.modal) => {
      <div className="flex flex-col">
        <div className="text-center">{React.string("Are you sure you want to remove entity")}</div>
        <div className="text-center">{React.string(getEntity(modal.data))}</div>

        <div className="flex justify-around mt-6">
          <Button_UI 
            size={Button_UI.Xs}
            onClick={(_) => modalDispatch(CloseModal("RemoveEntity"))} 
          >
            {React.string("Cancel")}
          </Button_UI>

          <Button_UI 
            size={Button_UI.Xs}
            onClick={(_) => {
              modalDispatch(CloseModal("RemoveEntity"));
              editorDispatch(SelectEntity(""));
              appDispatch(RemoveEntity(getEntity(modal.data)));
            }} 
          >
            {React.string("Remove")}
          </Button_UI>
        </div>
      </div>
    }}
  />
}