let create =
    (
      ~isPlaying=?,
      ~keyframes: Belt.Map.Int.t(Shared.keyframe(float)),
      ~entity: Belt.Map.String.key,
      ~state: Shared.state,
      (),
    )
    : Shared.state => {
  ...state,
  transitionFloat:
    Belt.Map.String.set(
      state.transitionFloat,
      entity,
      {
        keyframes,
        isPlaying:
          switch (isPlaying) {
          | None => true
          | Some(v) => v
          },
        playingFrameIndex: 0,
      },
    ),
};