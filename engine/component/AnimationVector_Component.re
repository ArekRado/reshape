let mapParamToKeyframes =
    (keyframes: Belt.List.t(Shared.keyframe(Vector_Util.t))) =>
  Belt.List.map(keyframes, (keyframe) =>
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
      ~id: Belt.Map.String.key,
      ~isPlaying=?,
      ~keyframes: Belt.List.t(Shared.keyframe(Vector_Util.t)),
      ~entity: string,
      ~state: Shared.state,
      (),
    )
    : Shared.state => {
  ...state,
  animationVector:
    Belt.Map.String.set(
      state.animationVector,
      id,
      {
        entity,
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