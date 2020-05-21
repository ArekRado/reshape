let getProgress =
    (
      currentTime: float,
      duration: float,
      timingFunction: Shared.timingFunction,
    )
    : float => {
  let percentageProgress =
    currentTime === 0.0 ? 0.0 : currentTime *. 100.0 /. duration;

  switch (timingFunction) {
  | Linear => BezierFunction_Util.linear(percentageProgress)
  | EaseInQuad => BezierFunction_Util.easeInQuad(percentageProgress)
  | EaseOutQuad => BezierFunction_Util.easeOutQuad(percentageProgress)
  | EaseInOutQuad => BezierFunction_Util.easeInOutQuad(percentageProgress)
  | EaseInCubic => BezierFunction_Util.easeInCubic(percentageProgress)
  | EaseOutCubic => BezierFunction_Util.easeOutCubic(percentageProgress)
  | EaseInOutCubic => BezierFunction_Util.easeInOutCubic(percentageProgress)
  | EaseInQuart => BezierFunction_Util.easeInQuart(percentageProgress)
  | EaseOutQuart => BezierFunction_Util.easeOutQuart(percentageProgress)
  | EaseInOutQuart => BezierFunction_Util.easeInOutQuart(percentageProgress)
  | EaseInQuint => BezierFunction_Util.easeInQuint(percentageProgress)
  | EaseOutQuint => BezierFunction_Util.easeOutQuint(percentageProgress)
  | EaseInOutQuint => BezierFunction_Util.easeInOutQuint(percentageProgress)
  | CubicBezier(_, _, _, _) => BezierFunction_Util.linear(percentageProgress)
  };
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
        let {keyframeCurrentTime, keyframeIndex} =
          getActiveKeyframe(transition);

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
                ? newValue > v2 ? v2 : newValue : newValue < v2 ? v2 : newValue,
          };
        };
      } else {
        transition;
      }
    ),
};