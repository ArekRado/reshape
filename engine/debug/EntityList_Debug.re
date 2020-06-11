[@react.component]
let make = (~initialState: Shared.state) => {
  let (state, setState) = React.useState(_ => initialState);
  let (entity, setEntity) = React.useState(_ => "");

  React.useEffect0(() => {
    let id = Js.Global.setInterval(() => {
      setState((_) => SyncState.get());
    }, 50);
    
    Some(() => {
      Js.Global.clearInterval(id);
    });
  });

  let fps = 1000.0 /. state.time.delta;
  let components = Debug_Util.getComponents(entity, state);

  <div className="absolute text-gray-500 bg-gray-900 bg-opacity-75 p-2 top-0 right-0 max-w-xs w-full h-full flex flex-col">
    <div className="text-white">
      {React.string("FPS: ")}
      {fps->int_of_float->Js.Int.toString->React.string}
    </div>
    <div className="flex flex-col flex-1 overflow-y-scroll mt-3">
       <div className="text-white mb-3">
          {React.string("Entity")}
        </div>
        {
        state.entity
        ->Belt.List.map(entity =>
            <button 
              key={entity} 
              className="hover:text-gray-800 hover:bg-gray-400 text-left"
              onClick={(_) => setEntity((_) => entity)}  
            >
              {entity->Uuid_Util.humanFriendlyEntity->React.string}
            </button>
          )
        ->(items => React.array(Array.of_list(items)))
      }
    </div>
    <div className="flex flex-col flex-1 overflow-y-scroll">
      <div className="text-white mb-3">
        {React.string("Components")}
      </div>
        <Debug_Transform_Component transform={components.transform}/>
        <Debug_Sprite_Component sprite={components.sprite}/>
        <Debug_AnimationFloat_Component items={components.animationFloat}/>
    </div>
  </div>;
}