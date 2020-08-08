let mapParamToKeyframes = (keyframes: Belt.List.t(Type.newKeyframe)) => 
  Belt.List.map(keyframes, (keyframe):Type.newKeyframe => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
  });

let create =
  (
    ~name: string,
    ~isPlaying=?,
    ~keyframes: Belt.List.t(Type.newKeyframe),
    ~entity: string,
    ~state: Type.state,
    ~value: Type.animationValue,
    ~wrapMode=?,
    (),
  ) : Type.state => {
  ...state,
  animation:
    Belt.Map.String.set(
      state.animation,
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
        value,
        isFinished: false,
      },
    ),
};

let remove = (~name: string, ~state: Type.state): Type.state => {
  ...state,
  animation: Belt.Map.String.remove(state.animation, name),
};

let removeByEntity = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  animation: Belt.Map.String.keep(
    state.animation,
    (_, animation) => animation.entity !== entity
  ),
};

let set = (~name: string, ~state: Type.state, ~animation) => {
  ...state,
  animation: Belt.Map.String.set(state.animation, name, animation),
}