let getPercentageProgress =
    (
      currentTime: float,
      duration: float,
      timingFunction: Type.timingFunction,
    ) : float => {
  let percentageProgress =
    currentTime === 0.0 ? 0.0 : currentTime *. 100.0 /. duration;

  BezierFunction_Util.getValue(timingFunction, percentageProgress);
};

type activeKeyframe = {
  keyframeCurrentTime: float,
  keyframeIndex: int,
  timeExceeded: bool,
};

type acc = {
  sum: float,
  activeIndex: int,
  breakLoop: bool,
}

let rec getActiveKeyframe = (
  animation: Type.newAnimation, 
  secondLoop: bool
): activeKeyframe => {
  let size = Belt.List.size(animation.keyframes);

  if (size === 1 && animation.wrapMode === Once) {
    {
      keyframeCurrentTime: animation.currentTime,
      keyframeIndex: 0,
      timeExceeded: false,
    };
  } else {
    let {sum, activeIndex } =
      Belt.List.reduceWithIndex(
        animation.keyframes,
        {
          sum: 0.0,
          activeIndex: 0,
          breakLoop: false,
        },
        (acc, keyframe, index) =>
        if (acc.breakLoop === true) {
          acc;
        } else if (keyframe.duration +. acc.sum < animation.currentTime) {
          if (size === index + 1) {
            // timeExceeded
            {
              sum: keyframe.duration +. acc.sum,
              activeIndex: -1,
              breakLoop: true
            }
          } else {
            {
              sum: keyframe.duration +. acc.sum,
              activeIndex: index,
              breakLoop: false,
            }
          };
        } else {
          {
            ...acc,
            activeIndex: index,
            breakLoop: true,
          }
        }
      );

    if(activeIndex === -1 && animation.wrapMode === Loop) {
      getActiveKeyframe({
        ...animation,
        // mod_float prevents from unnecessary loops, instantly moves to last loop
        currentTime: mod_float(animation.currentTime, sum),
      }, true)
    } else {
      {
        keyframeCurrentTime: animation.currentTime -. sum,
        keyframeIndex: activeIndex,
        timeExceeded: secondLoop || activeIndex === (-1),
      };
    }
  };
};

type updateFloatAnimationType = (float, Type.newAnimation);

let updateFloatAnimation = (
  ~keyframe: Type.newKeyframe,
  ~time: Type.time,
  ~animation: Type.newAnimation,
  ~progress: float,
  ~keyframeCurrentTime: float,
  ~timeExceeded: bool,
): updateFloatAnimationType => {
  let (v1, v2) = switch (keyframe.valueRange) {
  | Float(v) => v
  | Vector(_) => (0.0, 0.0)
  };
  
  let normalizedMax = v2 -. v1;
  let newValue = progress *. normalizedMax /. 100.0;

  let isNegative = v2 > v1;

  (
    isNegative
      ? newValue > v2 ? v2 : newValue
      : newValue < v2 ? v2 : newValue,
    {
      ...animation,
      currentTime: timeExceeded 
        ? keyframeCurrentTime +. time.delta
        : animation.currentTime +. time.delta,
      isFinished: timeExceeded,
    }
  );
};

type updateVectorAnimationType = (Vector_Util.t, Type.newAnimation);

let updateVectorAnimation = (
  ~keyframe: Type.newKeyframe,
  ~time: Type.time,
  ~animation: Type.newAnimation,
  ~progress: float,
  ~keyframeCurrentTime: float,
  ~timeExceeded: bool,
): updateVectorAnimationType => {
    let (v1, v2) = switch (keyframe.valueRange) {
  | Float(_) => (Vector_Util.zero, Vector_Util.zero)
  | Vector(v) => v
  };

  let normalizedMax = Vector_Util.sub(v2, v1);
  let newValue =
    Vector_Util.scale(
      1.0 /. 100.0,
      Vector_Util.scale(progress, normalizedMax),
    );

  let isNegative = Vector_Util.isLesser(v1, v2);

  (
    isNegative
      ? Vector_Util.isGreater(newValue, v2) ? v2 : newValue
      : Vector_Util.isLesser(newValue, v2) ? v2 : newValue,
    {
      ...animation,
      currentTime: timeExceeded 
        ? keyframeCurrentTime +. time.delta
        : animation.currentTime +. time.delta,
      isFinished: timeExceeded,
    }
  );
};

// animationValue
let update = (~state: Type.state): Type.state =>
  Belt.Map.String.reduce(state.animation, state, (acc, name, animation) =>
    if (animation.isPlaying) {
      let { keyframeCurrentTime, keyframeIndex, timeExceeded } =
        getActiveKeyframe(animation, false);

      if (timeExceeded === true && animation.wrapMode === Once) {
        Animation_Component.set(
          ~state=acc,
          ~name,
          ~animation={
            ...animation,
            currentTime: 0.0,
            // value: 0.0, // todo add option to back to prev value
            isPlaying: false,
            isFinished: true,
          }
        );
      } else {
        switch (Belt.List.get(animation.keyframes, keyframeIndex)) {
        | None => acc
        | Some(keyframe) =>
          let progress =
            getPercentageProgress(
              keyframeCurrentTime,
              keyframe.duration,
              keyframe.timingFunction,
            );

          switch(keyframe.valueRange) {
          | Float(_) =>
            let (value, updatedAnimation) = updateFloatAnimation(
              ~keyframe,
              ~time=state.time,
              ~animation,
              ~progress,
              ~keyframeCurrentTime,
              ~timeExceeded,
            );

            let stateWithNewAnimation = Animation_Component.set(
              ~state=acc,
              ~name,
              ~animation=updatedAnimation,
            );

            switch (animation.value) {
            | FieldFloat(fieldFloatName) =>
              FieldFloat_Component.setValue(
                ~state=stateWithNewAnimation,
                ~name=fieldFloatName,
                ~value,
              );
            | FieldVector(_) => state
            | TransformLocalPosition(_) => state
            };
          | Vector(_) =>
            let (value, updatedAnimation) = updateVectorAnimation(
              ~keyframe, 
              ~time=state.time, 
              ~animation,
              ~progress,
              ~keyframeCurrentTime,
              ~timeExceeded,
            );
            
            let stateWithNewAnimation = Animation_Component.set(
              ~state=acc,
              ~name,
              ~animation=updatedAnimation,
            );

            // Js.log2(value);

            switch (animation.value) {
            | FieldFloat(_) => state
            | FieldVector(fieldVectorName) => 
              FieldVector_Component.setValue(
                ~state=stateWithNewAnimation,
                ~name=fieldVectorName,
                ~value,
              );
            | TransformLocalPosition(entity) =>
              Transform_Component.setLocalPosition(
                ~state=stateWithNewAnimation,
                ~entity,
                ~localPosition=value,
              );
            };
          }
        };
      };
    } else {
      acc;
    }
  );