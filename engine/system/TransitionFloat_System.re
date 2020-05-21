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

let getActiveKeyframe = (transition: Shared.transition(float)) => {
  let size = Belt.Map.Int.size(transition.keyframes);

  if (size === 1) {
    {
      keyframeCurrentTime: transition.currentTime,
      keyframeIndex: 0,
      timeExceeded: false,
    };
  } else {
    let (sum, activeIndex, _) =
      Belt.Map.Int.reduce(
        transition.keyframes,
        (0.0, 0, false),
        ((sum, activeIndex, break), index, keyframe) =>
        if (break === true) {
          (sum, activeIndex, true);
        } else if (keyframe.duration +. sum < transition.currentTime) {
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
      keyframeCurrentTime: transition.currentTime -. sum,
      keyframeIndex: activeIndex,
      timeExceeded: activeIndex === (-1),
    };
  };
};

let update = (~state: Shared.state): Shared.state => {
  ...state,
  transitionFloat:
    Belt.Map.String.map(state.transitionFloat, transition =>
      if (transition.isPlaying) {
        let {keyframeCurrentTime, keyframeIndex, timeExceeded} =
          getActiveKeyframe(transition);

        if (timeExceeded === true) {
          {...transition, currentTime: 0.0, value: 0.0, isPlaying: false};
        } else {
          switch (Belt.Map.Int.get(transition.keyframes, keyframeIndex)) {
          | None => transition
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
              ...transition,
              currentTime: transition.currentTime +. state.time.delta,
              value:
                isNegative
                  ? newValue > v2 ? v2 : newValue
                  : newValue < v2 ? v2 : newValue,
            };
          };
        };
      } else {
        transition;
      }
    ),
};