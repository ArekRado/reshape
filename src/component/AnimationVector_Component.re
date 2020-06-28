let mapParamToKeyframes =
    (keyframes: Belt.List.t(Type.keyframe(Vector_Util.t))) =>
  Belt.List.map(keyframes, (keyframe) =>
    (
      {
        duration: keyframe.duration,
        timingFunction: keyframe.timingFunction,
        valueRange: keyframe.valueRange,
      }:
        Type.keyframe(Vector_Util.t)
    )
  );

let create =
    (
      ~name: string,
      ~isPlaying=?,
      ~keyframes: Belt.List.t(Type.keyframe(Vector_Util.t)),
      ~entity: string,
      ~state: Type.state,
      ~wrapMode=?,
      (),
    )
    : Type.state => {
  ...state,
  animationVector:
    Belt.Map.String.set(
      state.animationVector,
      name,
      {
        entity,
        name,
        keyframes: mapParamToKeyframes(keyframes),
        isPlaying:
          switch (isPlaying) {
          | None => false
          | Some(v) => v
          },
        wrapMode: switch (wrapMode) {
          | None => Once
          | Some(v) => v
          },
        currentTime: 0.0,
        value: Vector_Util.zero,
        isFinished: false,
      },
    ),
};