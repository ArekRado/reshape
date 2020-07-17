[@react.component]
let make = (~name, ~render) => {
  let (state, dispatch) = React.useContext(Modal_Context.context);

  switch(Belt.Map.String.get(state, name)) {
  | Some(modal) => {
    if(modal.isOpen) {
      <>
        <div className="absolute inset-0 bg-blue-500 bg-opacity-25 z-modal-backdrop" onClick={(_) => dispatch(CloseModal(name))} />

        <div className="absolute m-auto modal-wrapper top-1/2 transform -translate-y-1/2 -translate-x-1/2 border z-modal">
          {render(modal)}
        </div>
      </>
    } else {
      React.null
    }
  }
  | None => React.null
  };
}