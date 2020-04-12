let create =
    (
      ~isPlaying=true,
      keyframes:Belt.List.t(Shared.keyframe),
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