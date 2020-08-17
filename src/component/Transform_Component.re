let create =
    (
      ~rotation=0.0,
      ~localRotation=0.0,
      ~scale=Vector_Util.zero,
      ~localScale=Vector_Util.zero,
      ~localPosition=Vector_Util.zero,
      ~entity: Belt.Map.String.key,
      ~state: Type.state,
      ~parent=None,
      (),
    )
    : Type.state => {
  ...state,
  transform:
    Belt.Map.String.set(
      state.transform,
      entity,
      {
        rotation,
        localRotation,
        scale,
        localScale,
        position: Vector_Util.zero,
        localPosition,
        parent,
      },
    ),
};

let remove = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  transform: Belt.Map.String.remove(state.transform, entity),
};

let setRotation = (~entity, ~state: Type.state, ~rotation): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, rotation})
      | None => transform
      }
    ),
};

let setLocalRotation =
    (~entity, ~state: Type.state, ~localRotation): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, localRotation})
      | None => transform
      }
    ),
};

let setScale = (~entity, ~state: Type.state, ~scale): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, scale})
      | None => transform
      }
    ),
};

let setLocalScale = (~entity, ~state: Type.state, ~localScale): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, localScale})
      | None => transform
      }
    ),
};

let setPosition = (~entity, ~state: Type.state, ~position): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, position})
      | None => transform
      }
    ),
};

let setLocalPosition =
    (~entity, ~state: Type.state, ~localPosition): Type.state => {
  ...state,
  transform:
    Belt.Map.String.update(state.transform, entity, transform =>
      switch (transform) {
      | Some(transform) => Some({...transform, localPosition})
      | None => transform
      }
    ),
};

let get = (~entity: Type.entity, ~state: Type.state) => 
  Belt.Map.String.get(state.transform, entity)