let mapParamToKeyframes = (keyframes: Belt.Map.Int.t(Shared.keyframe(float))) => 
  Belt.Map.Int.map(keyframes, (keyframe):Shared.keyframe(float) => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
  })

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
        keyframes: mapParamToKeyframes(keyframes),
        isPlaying:
          switch (isPlaying) {
          | None => false
          | Some(v) => v
          },
        currentTime: 0.0,
        value: 0.0,
      },
    ),
};