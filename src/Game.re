[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";
[@bs.val] external setTimeout : (unit => unit, int) => float = "setTimeout";

let initialState: Type.state = {
    game: {
      // area: Belt.Map.String.empty,
      city: Belt.Map.String.empty,
      humanPorter: Belt.Map.String.empty,
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
    // ->System.Area.update
    ->System.City.update

  ignore(
    setTimeout(() => {
      requestAnimationFrame(() => logic(newState));
    }, 500)
  );

  ()
};

Engine.initialize();
logic(initialState);