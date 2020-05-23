// let getComponents = (entity, state) => {

// }

[@react.component]
let make = (~initialState: Shared.state) => {
  let (state, setState) = React.useState(_ => initialState);
  let (entity, setEntity) = React.useState(_ => "");

  React.useEffect0(() => {
    let id = Js.Global.setInterval(() => {
      setState((_) => SyncState.get());
    }, 300);
    
    Some(() => {
      Js.Global.clearInterval(id);
    });
  });

  let fps = 1000.0 /. state.time.delta;

  <div className="absolute text-gray-500 bg-gray-900 bg-opacity-75 p-2 top-0 right-0 max-w-xs w-full h-full">
    <div>
      {React.string("FPS: ")}
      {fps->int_of_float->Js.Int.toString->React.string}
    </div>
    <div className="flex flex-col mt-3">
        {
        state.entity
        ->Belt.List.map(entity =>
            <button key={entity} className="hover:text-gray-800 hover:bg-gray-400 text-left">
              {entity->Js.String2.split("###")->(items => React.string(items[0]))}
            </button>
          )
        ->(items => React.array(Array.of_list(items)))
      }
    </div>
    <div>
      {React.string("component")}
    </div>
  </div>;
}