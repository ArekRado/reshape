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

let getValue = (timingFunction: Type.timingFunction, value) =>
  switch (timingFunction) {
  | Linear => linear(value)
  | EaseInQuad => easeInQuad(value)
  | EaseOutQuad => easeOutQuad(value)
  | EaseInOutQuad => easeInOutQuad(value)
  | EaseInCubic => easeInCubic(value)
  | EaseOutCubic => easeOutCubic(value)
  | EaseInOutCubic => easeInOutCubic(value)
  | EaseInQuart => easeInQuart(value)
  | EaseOutQuart => easeOutQuart(value)
  | EaseInOutQuart => easeInOutQuart(value)
  | EaseInQuint => easeInQuint(value)
  | EaseOutQuint => easeOutQuint(value)
  | EaseInOutQuint => easeInOutQuint(value)
  | CubicBezier(_, _, _, _) => linear(value)
  };
