let create =
    (
      ~rotation=0.0,
      ~localRotation=0.0,
      ~scale=Vector_Util.zero,
      ~localScale=Vector_Util.zero,
      ~position=Vector_Util.zero,
      ~localPosition=Vector_Util.zero,
      ~entity: Belt.Map.String.key,
      ~state: Shared.state,
      ~parent="",
      ()
    )
    : Shared.state => {
  ...state,
  transform:
    Belt.Map.String.set(
      state.transform,
      entity,
      {rotation, localRotation, scale, localScale, position, localPosition, parent},
    ),
};