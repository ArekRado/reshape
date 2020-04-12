open Belt;

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

let update = (state: Shared.state): Shared.state => {
  ...state,
  transition:
    Map.String.mapWithKey(state.transition, (entity, transition) =>
      if (transition.isPlaying) {
        let keyframe =
          List.get(transition.keyframes, transition.playingFrameIndex);

        switch (keyframe) {
        | None => transition
        | Some(keyframe) =>
          let percentageProgress =
            keyframe.currentTime *. 100.0 /. keyframe.duration;

          let progress =
            switch (keyframe.timingFunction) {
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
            | CubicBezier(v1, v2, v3, v4) => transition
            };

          // switch (keyframe.value) {
          //   | FloatTransition(v1, v2) => transition
          //   | VectorTransition(v1, v2) => transition
          //   | BoolTransition(v1, v2) => transition
          //   }

          transition;
        };
      } else {
        transition;
      }
    ),
};