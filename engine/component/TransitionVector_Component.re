let create =
    (
      ~isPlaying=?,
      ~keyframes: Belt.Map.Int.t(Shared.keyframe(Vector_Util.t)),
      ~entity: Belt.Map.String.key,
      ~state: Shared.state,
      (),
    )
    : Shared.state => {
  ...state,
  transitionVector:
    Belt.Map.String.set(
      state.transitionVector,
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