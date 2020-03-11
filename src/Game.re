type context;

let humanImage:string = [%raw {|require('./assets/human.png').default|}];

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
  timer: Belt.Map.String.empty,
  area: Belt.Map.String.empty,
  scene: TestMap,
};

let rec logic = (state: Type.state, engineState: Engine.Shared.state) => {
  let engineState = Engine.runOneFrame(engineState)
  let newState = (state, engine) 
    |> System.Timer.update
    |> System.Scene.update
    |> System.Move.update
    |> System.Area.update

  requestAnimationFrame(() => logic(newState, engineState));
};

logic(initialState, Engine.initialState);

