[@react.component]
let make = (~children, ~name) => {
  let (state, dispatch) = React.useContext(Modal_Context.context);

  switch(Belt.Map.String.get(state, name)) {
  | Some(modal) => {
    if(modal.isOpen) {
      <>
        <div className="absolute inset-0 bg-blue-500 bg-opacity-50 z-modal-backdrop" onClick={(_) => dispatch(CloseModal(name))} />

        // <div className="absolute flex items-center justify-center">
          <div className="absolute modal-wrapper top-1/2 transform -translate-y-1/2 border z-modal">
            children
          </div>
        // </div>
      </>
    } else {
      React.null
    }
  }
  | None => React.null
  };
}