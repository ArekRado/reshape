type entity = Belt.List.t(string);

type vector = (float, float);

type transform = {
  rotation: float,
  localRotation: float,
  scale: vector,
  localScale: vector,
  position: vector,
  localPosition: vector,
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
  currentTime: float,
  timingFunction,
  valueRange: ('a, 'a),
  value: 'a,
};

type transition('a) = {
  keyframes: Belt.Map.Int.t(keyframe('a)),
  isPlaying: bool,
  playingFrameIndex: int,
};

type image = {src: string};

type time = {
  timeNow: float,
  delta: float,
};

type state = {
  entity,
  transform: Belt.Map.String.t(transform),
  image: Belt.Map.String.t(image),
  rigidbody: Belt.Map.String.t(rigidbody),
  transitionFloat: Belt.Map.String.t(transition(float)),
  transitionVector: Belt.Map.String.t(transition(Vector_Util.t)),
  mutable mouseButtons: int,
  mutable mousePosition: vector,
  time,
  // event: todo
};