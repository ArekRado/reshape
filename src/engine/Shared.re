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

type transitionValue =
  | FloatTransition(float, float)
  | VectorTransition(Vector_Util.t, Vector_Util.t);

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

type keyframe = {
  duration: float,
  currentTime: float,
  timingFunction,
  valueRange: (transitionValue,transitionValue),
  currentValue: transitionValue,
};

type transition = {
  keyframes: Belt.List.t(keyframe),
  isPlaying: bool,
  playingFrameIndex: int,
};

type image = {src: string};

type state = {
  entity,
  transform: Belt.Map.String.t(transform),
  image: Belt.Map.String.t(image),
  rigidbody: Belt.Map.String.t(rigidbody),
  transition: Belt.Map.String.t(transition),
  mutable mouseButtons: int,
  mutable mousePosition: vector,
  timeNow: float,
  delta: float,
  // event: todo
};