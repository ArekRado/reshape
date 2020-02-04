type context;

let humanImage:string = [%raw {|require('./assets/human.png').default|}];

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
  timer: Belt.Map.String.empty,
  area: Belt.Map.String.empty,
};

let rec logic = (state: Type.state, engineState: Engine.Shared.state) => {
  let engineState = Engine.runOneFrame(engineState)
  let newState = state 
    |> System.Timer.update(engineState)
    |> System.Scene.update(engineState)
    |> System.Move.update(engineState)
    |> System.Area.update(engineState)

  requestAnimationFrame(() => logic(newState, engineState));
};

logic(initialState, Engine.initialState);

