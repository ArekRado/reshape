[@react.component]
let make = (~id, ~render) => {
  let (state, dispatch) = React.useContext(Modal_Context.context);

  switch (Belt.Map.String.get(state, id)) {
  | Some(modal) =>
    if (modal.isOpen) {
      <>
        <div
          className="absolute inset-0 bg-blue-500 bg-opacity-25 z-modal-backdrop"
          onClick={_ => dispatch(CloseModal(id))}
        />
        <div
          className="absolute m-auto modal-wrapper top-1/2 transform -translate-y-1/2 -translate-x-1/2 z-modal bg-gray-800 p-4">
          {render(modal)}
        </div>
      </>;
    } else {
      React.null;
    }
  | None => React.null
  };
};
