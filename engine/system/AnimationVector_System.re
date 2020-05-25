let getProgress =
    (
      currentTime: float,
      duration: float,
      timingFunction: Shared.timingFunction,
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

let getActiveKeyframe = (animation: Shared.animation(Vector_Util.t)) => {
  let size = Belt.List.size(animation.keyframes);

  if (size === 1) {
    {
      keyframeCurrentTime: animation.currentTime,
      keyframeIndex: 0,
      timeExceeded: false,
    };
  } else {
    let (sum, activeIndex, _) =
      Belt.List.reduceWithIndex(
        animation.keyframes,
        (0.0, 0, false),
        ((sum, activeIndex, break), keyframe, index) =>
        if (break === true) {
          (sum, activeIndex, true);
        } else if (keyframe.duration +. sum < animation.currentTime) {
          if (size === index + 1) {
            (
              // timeExceeded
              0.0,
              (-1),
              true,
            );
          } else {
            (keyframe.duration +. sum, index, false);
          };
        } else {
          (sum, index, true);
        }
      );

    {
      keyframeCurrentTime: animation.currentTime -. sum,
      keyframeIndex: activeIndex,
      timeExceeded: activeIndex === (-1),
    };
  };
};

let update = (~state: Shared.state): Shared.state => {
  ...state,
  animationVector:
    Belt.Map.String.map(state.animationVector, animation =>
      if (animation.isPlaying) {
        let {keyframeCurrentTime, keyframeIndex, timeExceeded} =
          getActiveKeyframe(animation);

        if (timeExceeded === true) {
          {
            ...animation,
            currentTime: 0.0,
            value: Vector_Util.zero,
            isPlaying: false,
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

            let (v1, v2) = keyframe.valueRange;
            let normalizedMax = Vector_Util.sub(v2, v1);
            let newValue =
              Vector_Util.scale(
                1.0 /. 100.0,
                Vector_Util.scale(progress, normalizedMax),
              );

            let isNegative = Vector_Util.isLesser(v1, v2);

            {
              ...animation,
              currentTime: animation.currentTime +. state.time.delta,
              value:
                isNegative
                  ? Vector_Util.isGreater(newValue, v2) ? v2 : newValue
                  : Vector_Util.isLesser(newValue, v2) ? v2 : newValue,
            };
          };
        };
      } else {
        animation;
      }
    ),
};