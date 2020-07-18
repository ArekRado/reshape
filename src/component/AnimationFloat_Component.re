let mapParamToKeyframes = (keyframes: Belt.List.t(Type.keyframe(float))) => 
  Belt.List.map(keyframes, (keyframe):Type.keyframe(float) => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
  });

let create =
  (
    ~name: string,
    ~isPlaying=?,
    ~keyframes: Belt.List.t(Type.keyframe(float)),
    ~entity: string,
    ~state: Type.state,
    ~wrapMode=?,
    (),
  ) : Type.state => {
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

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  animationFloat: Belt.Map.String.remove(state.animationFloat, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  animationFloat: Belt.Map.String.keep(
    state.animationFloat,
    (_, animationFloat) => animationFloat.entity !== entity
  ),
};