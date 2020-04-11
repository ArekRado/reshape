type context;

let humanImage:string = [%raw {|require('./assets/human.png').default|}];

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
    game: {
      area: Belt.Map.String.empty,
      scene: TestMap,
      isSceneInicialized: false,
    },
    engine: Engine.initialState,
};

let rec logic = (state: Type.state) => {
  let newEngine = Engine.runOneFrame(state.engine);

  let newState = ({game: state.game, engine: newEngine} : Type.state)
    |> System.Timer.update
    |> System.Scene.update
    |> System.Move.update
    |> System.Area.update

  requestAnimationFrame(() => logic(newState));
};

logic(initialState);

