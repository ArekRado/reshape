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

type activeKeyframe('a) = {
  keyframeCurrentTime: float,
  keyframeIndex: int,
  keyframe: option(Shared.keyframe('a)),
}

let getActiveKeyframe = (transition: Shared.transition(Vector_Util.t)) => {
  if(Belt.Map.Int.size(transition.keyframes) === 0) {
    {
      keyframeCurrentTime: transition.currentTime,
      keyframeIndex: 0,
      keyframe: Belt.Map.Int.get(transition.keyframes, 0),
    }
  } else {
    let c = Belt.Map.Int.reduce(
      transition.keyframes, 
      (0.0, 0), 
      ((sum, activeIndex), index, keyframe) => {
        if(keyframe.duration +. sum < transition.currentTime) {
          (keyframe.duration +. sum, index);
        } else {
          (sum, activeIndex);
        }
      }
    );

    {
      keyframeCurrentTime: transition.currentTime,
      keyframeIndex: 0,
      keyframe: Belt.Map.Int.get(transition.keyframes, 0),
    }
  }
}

let update = (~state: Shared.state): Shared.state => {
  ...state,
  transitionVector: 
    Belt.Map.String.map(state.transitionVector, transition =>
      if (transition.isPlaying) {
        let {
          keyframeCurrentTime,
          keyframeIndex,
          keyframe
        } = getActiveKeyframe(transition)

        switch (keyframe) {
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
            keyframes:
              Belt.Map.Int.set(
                transition.keyframes,
                keyframeIndex,
                {
                  ...keyframe,
                  value: isNegative
                  ? Vector_Util.isGreater(newValue, v2) ? v2 : newValue
                  : Vector_Util.isLesser(newValue, v2) ? v2 : newValue,
                },
              ),
          };
        };
      } else {
        transition;
      }
    )
};