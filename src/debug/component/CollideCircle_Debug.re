[@react.component]
let make = (~items: Belt.Map.String.t(Type.collideCircle)) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);
  
  items
    ->Belt.Map.String.toArray
    ->Belt.Array.map(((key, collideCircle)) =>
      <React.Fragment key>
        <div className="flex justify-between mt-3">
          <div className="text-white col-span-12">
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
            title={React.string("Are you sure you want to remove collide circle?")}
            onAccept={(_) => appDispatch(RemoveCollideCircle(key))}
          />
        </div>

        <div  className="grid grid-cols-12 gap-1 mb-3">
          <div className="col-span-4">{React.string("radius")}</div>
          <div className="col-span-8">
            <Input_UI 
              value={Belt.Float.toString(collideCircle.radius)} 
              onChange={(_) => {()}}
            />
          </div>  
          <div className="col-span-4">{React.string("position")}</div>
          <div className="col-span-8">
            <Vector_Debug 
              value={collideCircle.position}
              onChange={(_) => {()}}
            />
          </div>

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
      </React.Fragment >
    )
    ->React.array
}