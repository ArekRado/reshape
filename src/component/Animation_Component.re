let mapParamToKeyframes = (keyframes: Belt.List.t(Type.keyframe)) =>
  Belt.List.map(keyframes, (keyframe) =>
    (
      {
        duration: keyframe.duration,
        timingFunction: keyframe.timingFunction,
        valueRange: keyframe.valueRange,
      }: Type.keyframe
    )
  );

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
    )
    : Type.state => {
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
        wrapMode:
          switch (wrapMode) {
          | None => Once
          | Some(v) => v
          },
        currentTime: 0.0,
        component,
        isFinished: false,
      },
    ),
};

let remove =
    (~entity: Type.entity, ~name: string, ~state: Type.state): Type.state => {
  ...state,
  animation: Belt.Map.String.remove(state.animation, entity ++ name),
};

let removeByEntity = (~entity: Type.entity, ~state: Type.state): Type.state => {
  ...state,
  animation:
    Belt.Map.String.keep(state.animation, (_, animation) =>
      animation.entity !== entity
    ),
};

let set =
    (~entity: Type.entity, ~name: string, ~state: Type.state, ~animation) => {
  ...state,
  animation: Belt.Map.String.set(state.animation, entity ++ name, animation),
};

let setComponent =
    (~entity: Type.entity, ~name: string, ~state: Type.state, ~component) => {
  ...state,
  animation:
    Belt.Map.String.update(state.animation, entity ++ name, animation =>
      switch (animation) {
      | Some(animation) => Some({...animation, component})
      | None => animation
      }
    ),
};
