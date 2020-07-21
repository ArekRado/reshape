[@react.component]
let make = (~items: Belt.Map.String.t(Type.collideCircle)) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);
  
  items
    ->Belt.Map.String.toArray
    ->Belt.Array.map(((key, collideCircle)) =>
      <>
        <div className="flex justify-between">
          <div className="text-white mb-3 col-span-12">
            {React.string("Collide box")}
          </div>

          <Button_UI
            size={Button_UI.Xs}
            onClick={(_) => {
              modalDispatch(OpenModal(key, None))
            }}
          >
            {React.string("x")}
          </Button_UI>

          <ConfirmModal_Debug 
            name={key}
            title={React.string("Are you sure you want to remove collide circle?")}
            onAccept={(_) => appDispatch(RemoveCollideCircle(key))}
          />
        </div>
        <div key={key} className="grid grid-cols-12 gap-1 mb-3">
          <div className="text-white mb-3 col-span-12">
            {React.string("Collide box")}
          </div>

          <div className="col-span-4">{React.string("radius")}</div>
          <div className="col-span-8">{React.string(Belt.Float.toString(collideCircle.radius))}</div>

          <div className="col-span-4">{React.string("position")}</div>
          <div className="col-span-8"><Vector_Debug vector={collideCircle.position} /></div>

          {Belt.List.length(collideCircle.collisions) > 0 
          ? <div>{React.string("Collisions:")}</div> 
          : React.null}

          {Belt.List.map(collideCircle.collisions, (collisionType: Type.collideType) =>
          switch(collisionType) {
            | Box(entity) => 
              <Entity_Debug 
                key={entity}
                entity={"Box(" ++ Uuid_Util.humanFriendlyEntity(entity) ++ ")"} 
                humanFriendlyEntity={false} 
              />
            | Circle(entity) => 
              <Entity_Debug 
                key={entity}
                entity={"Circle(" ++ Uuid_Util.humanFriendlyEntity(entity) ++ ")"} 
                humanFriendlyEntity={false} 
              />
            }
          )
          ->Array.of_list
          ->React.array
          }
        </div>
      </>
    )
    ->React.array
}