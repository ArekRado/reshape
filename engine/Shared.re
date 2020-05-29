type entity = Belt.List.t(string);

type vector = (float, float);

type collideType = 
  | Box(string)
  | Circle(string);

type collideBox = {
  entity: string,
  size: vector,
  position: vector,
  collisions: Belt.List.t(collideType),
};

type collideCircle = {
  entity: string,
  radius: float,
  position: vector,
  collisions: Belt.List.t(collideType),
};

type transform = {
  rotation: float,
  localRotation: float,
  scale: vector,
  localScale: vector,
  position: vector,
  localPosition: vector,
  parent: option(string),
};

// type rigidbody = {
//   rigidbodyType,
//   size: vector,
//   isClicked: bool,
//   isHovered: bool,
// };

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
  // rigidbody: Belt.Map.String.t(rigidbody),
  animationFloat: Belt.Map.String.t(animation(float)),
  animationVector: Belt.Map.String.t(animation(Vector_Util.t)),

  collideBox: Belt.Map.String.t(collideBox),
  collideCircle: Belt.Map.String.t(collideCircle),

  mutable mouseButtons: int,
  mutable mousePosition: vector,
  time,
  isDebugInitialized: bool,
  // event: todo
};

let initialState: state = {
  entity: [],
  transform: Belt.Map.String.empty,
  sprite: Belt.Map.String.empty,
  animationFloat: Belt.Map.String.empty,
  animationVector: Belt.Map.String.empty,
  collideBox: Belt.Map.String.empty,
  collideCircle: Belt.Map.String.empty,
  time: {
    timeNow: 0.0,
    delta: 0.0,
  },
  mouseButtons: 0,
  mousePosition: Vector_Util.zero,
  isDebugInitialized: false,
};