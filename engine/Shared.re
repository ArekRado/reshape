type entity = Belt.List.t(string);

type vector = (float, float);

type transform = {
  rotation: float,
  localRotation: float,
  scale: vector,
  localScale: vector,
  position: vector,
  localPosition: vector,
  parent: option(string),
};

type rigidbodyType =
  | Circle
  | Square;

type rigidbody = {
  rigidbodyType,
  size: vector,
  isClicked: bool,
  isHovered: bool,
};

type timingFunction =
  | Linear
  | EaseInQuad
  | EaseOutQuad
  | EaseInOutQuad
  | EaseInCubic
  | EaseOutCubic
  | EaseInOutCubic
  | EaseInQuart
  | EaseOutQuart
  | EaseInOutQuart
  | EaseInQuint
  | EaseOutQuint
  | EaseInOutQuint
  | CubicBezier(float, float, float, float);

type keyframe('a) = {
  duration: float,
  timingFunction,
  valueRange: ('a, 'a),
};

type animation('a) = {
  entity: string,
  keyframes: Belt.List.t(keyframe('a)),
  isPlaying: bool,
  currentTime: float,
  value: 'a,
};

type sprite = {src: string};

type time = {
  timeNow: float,
  delta: float,
};

type state = {
  entity,
  transform: Belt.Map.String.t(transform),
  sprite: Belt.Map.String.t(sprite),
  rigidbody: Belt.Map.String.t(rigidbody),
  animationFloat: Belt.Map.String.t(animation(float)),
  animationVector: Belt.Map.String.t(animation(Vector_Util.t)),
  mutable mouseButtons: int,
  mutable mousePosition: vector,
  time,
  isDebugInitialized: bool,
  // event: todo
};