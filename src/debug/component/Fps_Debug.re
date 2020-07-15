[@react.component]
let make = (~gameState: Type.state) => {
  let fps = 1000.0 /. gameState.time.delta;

  <div className="text-white">
    {React.string("FPS: ")}
    {fps->int_of_float->Js.Int.toString->React.string}
  </div>
}