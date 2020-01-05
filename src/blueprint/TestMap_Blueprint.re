[@bs.scope "Math"] [@bs.val] external random : unit => float = "random";

let create = (state: Type.state):Type.state => {
  let newState = state 
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0))
  |> City_Blueprint.create(~position=Vector.create(random() *. 1200.0, random() *. 700.0));

  {
    ...newState,
    isSceneInicialized: true,
  };
}