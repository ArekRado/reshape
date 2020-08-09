let mapParamToKeyframes = (keyframes: Belt.List.t(Type.keyframe)) => 
  Belt.List.map(keyframes, (keyframe):Type.keyframe => {
    duration: keyframe.duration,
    timingFunction: keyframe.timingFunction,
    valueRange: keyframe.valueRange,
  });

let create =
  (
    ~name: string,
    ~isPlaying=?,
    ~keyframes: Belt.List.t(Type.keyframe),
    ~entity: string,
    ~state: Type.state,
    ~component: Type.animatedComponent,
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
        component,
        isFinished: false,
      },
    ),
};

let remove = (~name: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  animation: Belt.Map.String.remove(state.animation, name),
};

let removeByEntity = (~entity: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  animation: Belt.Map.String.keep(
    state.animation,
    (_, animation) => animation.entity !== entity
  ),
};

let set = (~name: Type.entity, ~state: Type.state, ~animation) => {
  ...state,
  animation: Belt.Map.String.set(state.animation, name, animation),
};

let setComponent = (~name: Type.entity, ~state: Type.state, ~component) => {
  ...state,
  animation: Belt.Map.String.update(state.animation, name, animation =>
    switch animation {
    | Some(animation) => 
      Some({
        ...animation,
        component,
      })
    | None => animation
    }
  )
}