[@react.component]
let make =
    (
      ~id,
      ~onAccept,
      ~title,
      ~onCancel=(_: Modal_Context.modal) => {()},
      ~closeOnAction=true,
    ) => {
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  <Modal_UI
    id
    render={(modal: Modal_Context.modal) => {
      <div className="flex flex-col">
        <div className="text-center"> title </div>
        <div className="flex justify-around mt-6">
          <Button_UI
            onClick={_ => {
              onCancel(modal);
              if (closeOnAction === true) {
                modalDispatch(CloseModal(id));
              };
            }}>
            {React.string("Cancel")}
          </Button_UI>
          <Button_UI
            onClick={_ => {
              onAccept(modal);
              if (closeOnAction === true) {
                modalDispatch(CloseModal(id));
              };
            }}>
            {React.string("Accept")}
          </Button_UI>
        </div>
      </div>
    }}
  />;
};
