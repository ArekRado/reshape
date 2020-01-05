type context;

let humanImage:string = [%raw {|require('./assets/human.png').default|}];

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
  entity: [],
  position: Belt.Map.String.empty,
  image: Belt.Map.String.empty,
  timer: Belt.Map.String.empty,
  area: Belt.Map.String.empty,
  timeNow: 0.0,
  delta: 0.0,
  scene: TestMap,
  isSceneInicialized: false,
};

let rec logic = (state: Type.state) => {
  /* let io = System.IO.update() */

  let newState = state 
    |> System.Time.update
    |> System.Timer.update
    |> System.Scene.update
    |> System.Move.update
    |> System.Area.update
    |> System.Draw.update

  requestAnimationFrame(() => logic(newState));
};

let entity = "xD";

logic(initialState);

/* 
logic({
  ...initialState,
  entity: [entity],
  position: Belt.Map.String.set(initialState.position, entity, Vector.create(0.0, 1.0)),
  image: Belt.Map.String.set(initialState.image, entity, Component.Image.create(humanImage)),
}); */
