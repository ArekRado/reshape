[@react.component]
let make = () => {
  let (appState, appDispatch) = React.useContext(App_Context.context);

  let fps = 1000.0 /. appState.time.delta;

  <div className="text-white">
    {React.string("FPS: ")}
    {fps->int_of_float->Js.Int.toString->React.string}
  </div>
}