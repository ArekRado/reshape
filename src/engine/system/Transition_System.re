let linear = t => t;
// accelerating from zero velocity
let easeInQuad = t => t *. t;
// decelerating to zero velocity
let easeOutQuad = t => t *. (2.0 -. t);
// acceleration until halfway, then deceleration
let easeInOutQuad = t =>
  t < 0.5 ? 2.0 *. t *. t : (-1.0) +. (4.0 -. 2.0 *. t) *. t;
// accelerating from zero velocity
let easeInCubic = t => t *. t *. t;
// decelerating to zero velocity
let easeOutCubic = t => (t -. 1.0) *. t *. t +. 1.0;
// acceleration until halfway, then deceleration
let easeInOutCubic = t =>
  t < 0.5
    ? 4.0 *. t *. t *. t
    : (t -. 1.0) *. (2.0 *. t -. 2.0) *. (2.0 *. t -. 2.0) +. 1.0;
// accelerating from zero velocity
let easeInQuart = t => t *. t *. t *. t;
// decelerating to zero velocity
let easeOutQuart = t => 1.0 -. (t -. 1.0) *. t *. t *. t;
// acceleration until halfway, then deceleration
let easeInOutQuart = t =>
  t < 0.5 ? 8.0 *. t *. t *. t *. t : 1.0 -. 8.0 *. (t -. 1.0) *. t *. t *. t;
// accelerating from zero velocity
let easeInQuint = t => t *. t *. t *. t *. t;
// decelerating to zero velocity
let easeOutQuint = t => 1.0 +. (t -. 1.0) *. t *. t *. t *. t;
// acceleration until halfway, then deceleration
let easeInOutQuint = t =>
  t < 0.5
    ? 16.0 *. t *. t *. t *. t *. t
    : 1.0 +. 16.0 *. (t -. 1.0) *. t *. t *. t *. t;

// let Bezier =  p = (1-t)^3 *P0 + 3*t*(1-t)^2*P1 + 3*t^2*(1-t)*P2 + t^3*P3

let getProgress =
    (timingFunction: Shared.timingFunction, percentageProgress: float) => {
  switch (timingFunction) {
  | Linear => linear(percentageProgress)
  | EaseInQuad => easeInQuad(percentageProgress)
  | EaseOutQuad => easeOutQuad(percentageProgress)
  | EaseInOutQuad => easeInOutQuad(percentageProgress)
  | EaseInCubic => easeInCubic(percentageProgress)
  | EaseOutCubic => easeOutCubic(percentageProgress)
  | EaseInOutCubic => easeInOutCubic(percentageProgress)
  | EaseInQuart => easeInQuart(percentageProgress)
  | EaseOutQuart => easeOutQuart(percentageProgress)
  | EaseInOutQuart => easeInOutQuart(percentageProgress)
  | EaseInQuint => easeInQuint(percentageProgress)
  | EaseOutQuint => easeOutQuint(percentageProgress)
  | EaseInOutQuint => easeInOutQuint(percentageProgress)
  | CubicBezier(_, _, _, _) => linear(percentageProgress)
  };
};

let update = (state: Shared.state): Shared.state => {
  ...state,
  transition:
    Belt.Map.String.map(state.transition, (transition) =>
      if (transition.isPlaying) {
        let keyframe =
          Belt.Map.Int.get(transition.keyframes, transition.playingFrameIndex);

        switch (keyframe) {
        | None => transition
        | Some(keyframe) =>
          let percentageProgress =
            keyframe.currentTime *. 100.0 /. keyframe.duration;

          let progress =
            getProgress(keyframe.timingFunction, percentageProgress);

          let newValue: Shared.transitionValue =
            switch (keyframe.valueRange) {
            | (Shared.FloatTransition(v1), Shared.FloatTransition(v2)) =>
              // x - progress%
              // (v2 - v1) - 100%
              let normalizedMax = v2 -. v1;
              Shared.FloatTransition(progress *. normalizedMax /. 100.0);

            | (Shared.VectorTransition(v1), Shared.VectorTransition(v2)) =>
              let normalizedMax = Vector_Util.sub(v2, v1);
              Shared.VectorTransition(
                Vector_Util.scale(
                  1.0 /. 100.0,
                  Vector_Util.scale(progress, normalizedMax),
                ),
              );
            | _ => keyframe.value
            };

          {
            ...transition,
            keyframes:
              Belt.Map.Int.set(
                transition.keyframes,
                transition.playingFrameIndex,
                {
                  ...keyframe,
                  value: newValue,
                  duration: keyframe.currentTime +. state.delta,
                },
              ),
          };
        };
      } else {
        transition;
      }
    ),
};