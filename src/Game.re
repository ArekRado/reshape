type context;

let humanImage:string = [%raw {|require('./assets/human.png').default|}];

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
    game: {
      area: Belt.Map.String.empty,
      scene: TestMap,
      isSceneInicialized: false,
    },
    engine: Shared.initialState,
};

let rec logic = (state: Type.state) => {
  let newEngine = Engine.runOneFrame(~state=state.engine, ~debug=true, ());

  let newState = ({game: state.game, engine: newEngine} : Type.state)
    ->System.Scene.update
    ->System.Move.update
    ->System.Area.update

  requestAnimationFrame(() => logic(newState));
};

Engine.System.IO.initialize();
logic(initialState);