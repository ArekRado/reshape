let mapParamToKeyframes = (keyframes: Belt.List.t(Shared.keyframe(float))) => 
  Belt.List.map(keyframes, (keyframe):Shared.keyframe(float) => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
  })

  let create =
    (
      ~name: string,
      ~isPlaying=?,
      ~keyframes: Belt.List.t(Shared.keyframe(float)),
      ~entity: string,
      ~state: Shared.state,
      ~wrapMode=?,
      (),
    )
    : Shared.state => {
  ...state,
  animationFloat:
    Belt.Map.String.set(
      state.animationFloat,
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
        value: 0.0,
        isFinished: false,
      },
    ),
};