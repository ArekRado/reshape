type keyframe = {
  duration: float,
  timingFunction: Shared.timingFunction,
  valueRange: (float, float),
};

let mapParamToKeyframes = (keyframes: Belt.Map.Int.t(keyframe)) => 
  Belt.Map.Int.map(keyframes, (keyframe):Shared.keyframe(float) => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
    value: 0.0,
  })

  let create =
    (
      ~isPlaying=?,
      ~keyframes: Belt.Map.Int.t(keyframe),
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
      },
    ),
};