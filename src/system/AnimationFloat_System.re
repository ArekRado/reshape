let getProgress =
    (
      currentTime: float,
      duration: float,
      timingFunction: Type.timingFunction,
    )
    : float => {
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

let rec getActiveKeyframe = (animation: Type.animation(float), secondLoop: bool) => {
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

let update = (~state: Type.state): Type.state => {
  ...state,
  animationFloat:
    Belt.Map.String.map(state.animationFloat, animation =>
      if (animation.isPlaying) {
        let { keyframeCurrentTime, keyframeIndex, timeExceeded } =
          getActiveKeyframe(animation, false);

        if (timeExceeded === true && animation.wrapMode === Once) {
          {
            ...animation,
            currentTime: 0.0,
            value: 0.0,
            isPlaying: false,
            isFinished: true,
          };
        } else {
          switch (Belt.List.get(animation.keyframes, keyframeIndex)) {
          | None => animation
          | Some(keyframe) =>
            let progress =
              getProgress(
                keyframeCurrentTime,
                keyframe.duration,
                keyframe.timingFunction,
              );

            // x - progress%
            // (v2 - v1) - 100%
            let (v1, v2) = keyframe.valueRange;
            let normalizedMax = v2 -. v1;
            let newValue = progress *. normalizedMax /. 100.0;

            let isNegative = v2 > v1;

            {
              ...animation,
              currentTime: timeExceeded 
                ? keyframeCurrentTime +. state.time.delta
                : animation.currentTime +. state.time.delta,
              isFinished: timeExceeded,
              value:
                isNegative
                  ? newValue > v2 ? v2 : newValue
                  : newValue < v2 ? v2 : newValue,
            };
          };
        };
      } else {
        animation;
      }
    ),
};