// TOOD why?
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
      entity ++ name,
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
    (
      ~entity: Type.entity,
      ~name: string,
      ~state: Type.state,
      ~animation: Type.animation,
    ) => {
  ...state,
  animation: Belt.Map.String.set(state.animation, entity ++ name, animation),
};

let get = (~entity: Type.entity, ~state: Type.state, ~name: string) =>
  Belt.Map.String.get(state.animation, entity ++ name);

let unsafeGet =
    (~entity: Type.entity, ~state: Type.state, ~name: string): Type.animation =>
  switch (Belt.Map.String.get(state.animation, entity ++ name)) {
  | Some(x) => x
  | None => failwith("animation (" ++ entity ++ name ++ ") doesnt exist")
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

let setKeyframes =
    (
      ~entity: Type.entity,
      ~name: string,
      ~state: Type.state,
      ~keyframes: Belt.List.t(Type.keyframe),
    )
    : Type.state => {
  switch (get(~entity, ~state, ~name)) {
  | Some(animation) =>
    set(~entity, ~state, ~name, ~animation={...animation, keyframes})
  | None => failwith("animation (" ++ entity ++ name ++ ") doesnt exist")
  };
};

let setKeyframe =
    (
      ~entity: Type.entity,
      ~name: string,
      ~state: Type.state,
      ~index: int,
      ~keyframe: Type.keyframe,
    )
    : Type.state => {
  switch (get(~entity, ~state, ~name)) {
  | Some(animation) =>
    set(
      ~entity,
      ~state,
      ~name,
      ~animation={
        ...animation,
        keyframes:
          Belt.List.mapWithIndex(animation.keyframes, (i, value) =>
            i === index ? keyframe : value
          ),
      },
    )
  | None => failwith("animation (" ++ entity ++ name ++ ") doesnt exist")
  };
};

let emptyKeyframe = (duration): Type.keyframe => {
  duration,
  timingFunction: Linear,
  valueRange: Float((0.0, 0.0)),
};
