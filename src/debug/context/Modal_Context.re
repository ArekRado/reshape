type modal = {
  name: string,
  isOpen: bool,
}

let initialState = Belt.Map.String.empty;

type action = 
  | OpenModal(string)
  | CloseModal(string);

let reducer = (state, action) => {
  Js.log2(state, action)
  
  switch(action) {
    | OpenModal(name) => {
        let modal = Belt.Map.String.get(state, name);

        switch modal {
        | Some(modal) => Belt.Map.String.set(state, name, {
            ...modal,
            isOpen: true,
          })
        | None => Belt.Map.String.set(state, name, {
          name,
          isOpen: true,
        })
      };
    }
    | CloseModal(name) => 
      switch (Belt.Map.String.get(state, name)) {
        | Some(modal) => Belt.Map.String.set(state, name, {
            ...modal,
            isOpen: false,
          })
        | None => state
      }
    | _ => state
  }
};

type dispatch = action => unit;
type contextType = (Belt.Map.String.t(modal), dispatch);

let contextValue: contextType = (initialState, _ => ignore());
let context = React.createContext(contextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}

  let make = React.Context.provider(context);
};