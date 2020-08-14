type data =
  | None
  | Entity(Type.entity);

type modal = {
  name: string,
  isOpen: bool,
  data,
};

let initialState = Belt.Map.String.empty;

type action =
  | OpenModal(string, data)
  | CloseModal(string);

let reducer = (state, action) =>
  switch (action) {
  | OpenModal(name, data) =>
    let modal = Belt.Map.String.get(state, name);

    switch (modal) {
    | Some(modal) =>
      Belt.Map.String.set(state, name, {...modal, data, isOpen: true})
    | None => Belt.Map.String.set(state, name, {data, name, isOpen: true})
    };
  | CloseModal(name) =>
    switch (Belt.Map.String.get(state, name)) {
    | Some(modal) =>
      Belt.Map.String.set(state, name, {...modal, isOpen: false})
    | None => state
    }
  };

type dispatch = action => unit;
type contextType = (Belt.Map.String.t(modal), dispatch);

let contextValue: contextType = (initialState, _ => ignore());
let context = React.createContext(contextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {
    "value": value,
    "children": children,
  };

  let make = React.Context.provider(context);
};
