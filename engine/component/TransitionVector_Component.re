let mapParamToKeyframes =
    (keyframes: Belt.Map.Int.t(Shared.keyframe(Vector_Util.t))) =>
  Belt.Map.Int.map(keyframes, (keyframe) =>
    (
      {
        duration: keyframe.duration,
        timingFunction: keyframe.timingFunction,
        valueRange: keyframe.valueRange,
      }:
        Shared.keyframe(Vector_Util.t)
    )
  );

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
        keyframes: mapParamToKeyframes(keyframes),
        isPlaying:
          switch (isPlaying) {
          | None => false
          | Some(v) => v
          },
        currentTime: 0.0,
        value: Vector_Util.zero,
      },
    ),
};