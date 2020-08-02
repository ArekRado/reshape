[@react.component]
let make = (~items: Belt.Map.String.t(Type.collideBox)) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  items
    ->Belt.Map.String.toArray
    ->Belt.Array.map(((key, collideBox)) =>
      <React.Fragment key>
        <div className="flex justify-between mt-3">
          <div className="text-white">
            {React.string("Collide box")}
          </div>

          <Button_UI
            onClick={(_) => {
              modalDispatch(OpenModal(key, None))
            }}
          >
            {React.string("x")}
          </Button_UI>

          <ConfirmModal_Debug 
            name={key}
            title={React.string("Are you sure you want to remove collide box?")}
            onAccept={(_) => appDispatch(RemoveCollideBox(key))}
          />
        </div>

        <div className="grid grid-cols-12 gap-1 mb-3">
          <div className="col-span-4">{React.string("size")}</div>
          <div className="col-span-8">
            <Vector_Debug value={collideBox.size} onChange={(_) => {()}}/>
          </div>

          <div className="col-span-4">{React.string("position")}</div>
          <div className="col-span-8">
            <Vector_Debug value={collideBox.position} onChange={(_) => {()}}/>
          </div>

          {Belt.List.length(collideBox.collisions) > 0 
          ? <div>{React.string("Collisions:")}</div> 
          : React.null}

          {Belt.List.map(collideBox.collisions, (collisionType: Type.collideType) =>
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
      </React.Fragment >
    )
    ->React.array
}