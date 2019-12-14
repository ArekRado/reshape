type context;

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
  entity: [],
  position: Belt.Map.String.empty,
  image: Belt.Map.String.empty,
};

/* let dd = Component.Position.create(0.0, 0.0); */

let entity = "xD";

let rec logic = (state: Type.state) => {
  /* Js.log(state); */

  let newState = Belt.List.reduce(state.entity, state, (newState, entity) => {
    System.Move.update(entity, state);
  });

  System.Draw.update(newState);

  requestAnimationFrame(() => logic(newState));
};

logic({
  ...initialState,
  position: Belt.Map.String.set(initialState.position, entity, Vector.create(0.0, 1.0)),
  image: Belt.Map.String.set(initialState.image, entity, Component.Image.create("human.png")),
});
