type context;

[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";

let initialState: Type.state = {
  entity: [1],
  position: [2],
  image: [Component.Image.create()]
};

let dd = Component.Position.create();

let rec logic = state => {
  let newState = state;

  System.Draw.update(newState);

  requestAnimationFrame(() => logic(newState));
};

logic(initialState);
