type keyframe = {
  duration: float,
  timingFunction: Shared.timingFunction,
  valueRange: (Vector_Util.t, Vector_Util.t),
};

let mapParamToKeyframes = (keyframes: Belt.Map.Int.t(keyframe)) => 
  Belt.Map.Int.map(keyframes, (keyframe):Shared.keyframe(Vector_Util.t) => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
    value: Vector_Util.zero,
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
  transitionVector:
    Belt.Map.String.set(
      state.transitionVector,
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