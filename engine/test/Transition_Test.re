let testBody = (~result, ~expected) => {};

let test = (description, case) => {
  case() === true
    ? Js.log("Passed - " ++ description) : Js.log("Error - " ++ description);
};

test("XD", () => {
  let entity = Engine.Entity.generate("test");

  let state =
    Engine.initialState
    |> (state => Engine.Entity.create(entity))
    |> (
      state =>
        Engine.Component.Transition.create(
          Belt.Map.Int.set(
            Belt.Map.Int.empty(),
            0,
            {
              duration: 1.0,
              currentTime: 0.0,
              timingFunction,
              valueRange: (0.0, 1.0),
              value: 0.0,
            },
          ),
          Belt.Map.Int.t(Shared.keyframe),
          entity: Belt.Map.String.key,
          engine: Shared.state,
        )
    )
    |> Engine.runOneFrame;

  let transition = Belt.Map.String.get(state.transition, entity);

  return;
  transition.value === 0.0;
});