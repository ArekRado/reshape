type initialState = {
  selectedEntity: string,
  isPlaying: bool,
};

let initialState = {selectedEntity: "", isPlaying: false};

type action =
  | SelectEntity(string)
  | SetIsPlaying(bool);

let reducer = (state, action): initialState =>
  switch (action) {
  | SelectEntity(selectedEntity) => {
      ...state,
      selectedEntity:
        state.selectedEntity === selectedEntity ? "" : selectedEntity,
    }
  | SetIsPlaying(isPlaying) => {...state, isPlaying}
  };

type dispatch = action => unit;
type contextType = (initialState, dispatch);

let contextValue: contextType = (initialState, _ => ignore());
let context = React.createContext(contextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };

  let make = React.Context.provider(context);
};
