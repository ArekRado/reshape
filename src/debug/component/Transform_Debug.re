[@react.component]
let make = (~transform: option(Type.transform)) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (editorState, _) = React.useContext(Editor_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);
  let entity = editorState.selectedEntity;
  
  // | SetTransformPosition(Vector_Util.t)
  // | SetTransformLocalPosition(Vector_Util.t)
  // | SetTransformRotation(Type.rotation)
  // | SetTransformLocalRotation(Type.rotation)
  // | SetTransformScale(Vector_Util.t)
  // | SetTransformLocalScale(Vector_Util.t)
  // | SetTransformParent(option(Type.entity))

  switch (transform) {
  | Some(transform) => 
    <>
      <div className="flex justify-between mt-3">
        <div className="text-white">
          {React.string("Transform")}
        </div>

        <Button_UI
          onClick={(_) => {
            modalDispatch(OpenModal(entity ++ "transform", None))
          }}
        >
          {React.string("x")}
        </Button_UI>

        <ConfirmModal_Debug 
          id={entity ++ "transform"}
          title={React.string("Are you sure you want to remove transform?")}
          onAccept={(_) => appDispatch(RemoveTransform(entity ++ "transform"))}
        />
      </div>

      <div className="grid grid-cols-12 gap-1 mt-3">
        <div className="col-span-4">{React.string("position")}</div>
        <div className="col-span-8">
          <Vector_Debug 
            value={transform.position} 
            onChange={value => appDispatch(SetTransformPosition(entity, value))}
          />
        </div>
        <div className="col-span-4">{React.string("localPosition")}</div>
        <div className="col-span-8">
          <Vector_Debug 
            value={transform.localPosition} 
            onChange={value => appDispatch(SetTransformLocalPosition(entity, value))}
          />
        </div>
        <div className="col-span-4">{React.string("rotation")}</div>
        <div className="col-span-8">
          <Input_UI 
            type_="number" 
            value={Belt.Float.toString(transform.rotation)} 
            onChange={event => appDispatch(SetTransformRotation(entity, ReactEvent.Form.target(event)##value))}
          />
        </div>
        <div className="col-span-4">{React.string("localRotation")}</div>
        <div className="col-span-8">
          <Input_UI 
            type_="number" 
            value={Belt.Float.toString(transform.localRotation)} 
            onChange={event => appDispatch(SetTransformLocalRotation(entity, ReactEvent.Form.target(event)##value))}
          />
        </div>
        <div className="col-span-4">{React.string("scale")}</div>
        <div className="col-span-8">
          <Vector_Debug 
            value={transform.scale} 
            onChange={value => appDispatch(SetTransformScale(entity, value))}
          />
        </div>
        <div className="col-span-4">{React.string("localScale")}</div>
        <div className="col-span-8">
          <Vector_Debug 
            value={transform.localScale} 
            onChange={value => appDispatch(SetTransformLocalScale(entity, value))}
          />
        </div>
        <div className="col-span-4">{React.string("parent")}</div>
        <div className="col-span-8">
          {switch (transform.parent) {
          | Some(parent) => React.string(Uuid_Util.humanFriendlyEntity(parent))
          | None => React.string("None")
          };}
        </div>
      </div>
    </>
  | None => React.null
  };
};