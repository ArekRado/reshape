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

let getActiveKeyframe = (transition: Shared.transition(Vector_Util.t)) => {
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
  transitionVector:
    Belt.Map.String.map(state.transitionVector, transition =>
      if (transition.isPlaying) {
        let {keyframeCurrentTime, keyframeIndex, timeExceeded} =
          getActiveKeyframe(transition);

        if (timeExceeded === true) {
          {
            ...transition,
            currentTime: 0.0,
            value: Vector_Util.zero,
            isPlaying: false,
          };
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

            let (v1, v2) = keyframe.valueRange;
            let normalizedMax = Vector_Util.sub(v2, v1);
            let newValue =
              Vector_Util.scale(
                1.0 /. 100.0,
                Vector_Util.scale(progress, normalizedMax),
              );

            let isNegative = Vector_Util.isLesser(v1, v2);

            {
              ...transition,
              currentTime: transition.currentTime +. state.time.delta,
              value:
                isNegative
                  ? Vector_Util.isGreater(newValue, v2) ? v2 : newValue
                  : Vector_Util.isLesser(newValue, v2) ? v2 : newValue,
            };
          };
        };
      } else {
        transition;
      }
    ),
};