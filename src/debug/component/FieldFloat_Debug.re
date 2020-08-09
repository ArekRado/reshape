[@react.component]
let make = (~items: Belt.Map.String.t(Type.field(float))) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  Belt.Map.String.size(items) === 0
    ? React.null
    : <>
        <div className="text-white mt-3">
          {React.string("Fields")}
        </div>

        {
          items
          ->Belt.Map.String.toArray
          ->Belt.Array.map(((name, field)) =>
            <div key={name} className="grid grid-cols-12 gap-1 mb-3 my-1">
              <div className="col-span-5">
                <Input_UI
                  value={name} 
                  onChange={event => appDispatch(SetFieldFloatName(name, ReactEvent.Form.target(event)##value))}
                />
              </div>
              <div className="col-span-5">
                <Input_UI
                  type_="number"
                  value={Belt.Float.toString(field.value)} 
                  onChange={event => appDispatch(SetFieldFloatValue(name, ReactEvent.Form.target(event)##value))}
                />
              </div>

              <Button_UI
                className="col-span-2"
                onClick={(_) => {
                  modalDispatch(OpenModal(name, None))
                }}
              >
                {React.string("x")}
              </Button_UI>

              <ConfirmModal_Debug 
                id={name}
                title={React.string("Are you sure you want to remove field float?")}
                onAccept={(_) => appDispatch(RemoveFieldFloat(name))}
              />
            </div>
          )
          ->React.array;
        }
      </>
};