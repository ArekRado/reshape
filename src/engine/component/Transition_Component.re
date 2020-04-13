let create =
    (
      ~isPlaying=true,
      keyframes:Belt.Map.Int.t(Shared.keyframe),
      entity: Belt.Map.String.key,
      engine: Shared.state,
    )
    : Shared.state => {
  ...engine,
  transition:
    Belt.Map.String.set(
      engine.transition,
      entity,
      {
        keyframes,
        isPlaying,
        playingFrameIndex: 0,
      },
    ),
};