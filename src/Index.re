[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";
[@bs.val] external setTimeout : (unit => unit, int) => float = "setTimeout";

type gameState = {
    yourState: string,
}

type state = {
  game: gameState,
  engine: Type.state,
}

let initialState: state = {
  game: {
    yourState: "",
  },
  engine: Type.initialState,
};

let rec logic = (state: state) => {
  let newEngine = Engine.runOneFrame(~state=state.engine, ~debug=true, ());

  let newState = ({game: state.game, engine: newEngine} : state)
  // ->System.System1.update
  // ->System.System2.update
  // ->System.System3.update
  // ->System.System4.update

  // ignore(
  //   setTimeout(() => {
  //     requestAnimationFrame(() => logic(newState));
  //   }, 500)
  // );
  // ()
  
  requestAnimationFrame(() => logic(newState));
};

Engine.initialize();
logic(initialState);