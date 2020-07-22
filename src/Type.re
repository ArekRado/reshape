type entity = string;

type vector = (float, float);

type collideType = 
  | Box(string)
  | Circle(string);

type collideBox = {
  entity,
  size: vector,
  position: vector,
  collisions: Belt.List.t(collideType),
};

type collideCircle = {
  entity,
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

type field('a) = {
  entity,
  value: 'a,
}

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

type wrapMode = 
  //When time reaches the end of the animation clip, the clip will automatically stop playing and time will be reset to beginning of the clip.
  | Once	
  // When time reaches the end of the animation clip, time will continue at the beginning.
  | Loop	
  // When time reaches the end of the animation clip, time will ping pong back between beginning and end.
  | PingPong	
  // Plays back the animation. When it reaches the end, it will keep playing the last frame and never stop playing.
  | ClampForever	

type keyframe('a) = {
  duration: float,
  timingFunction,
  valueRange: ('a, 'a),
};

type animation('a) = {
  entity,
  name: string,
  keyframes: Belt.List.t(keyframe('a)),
  isPlaying: bool,
  isFinished: bool,
  currentTime: float,
  value: 'a,
  wrapMode,
};

type sprite = {src: string};

type time = {
  timeNow: float,
  delta: float,
};

type state = {
  entity: Belt.List.t(string),
  transform: Belt.Map.String.t(transform),
  sprite: Belt.Map.String.t(sprite),

  animationFloat: Belt.Map.String.t(animation(float)),
  animationVector: Belt.Map.String.t(animation(Vector_Util.t)),

  collideBox: Belt.Map.String.t(collideBox),
  collideCircle: Belt.Map.String.t(collideCircle),

  fieldFloat: Belt.Map.String.t(field(float)),

  mutable mouseButtons: int,
  mutable mousePosition: vector,
  time,
  isDebugInitialized: bool,
};

let initialState: state = {
  entity: [],
  transform: Belt.Map.String.empty,
  sprite: Belt.Map.String.empty,
  animationFloat: Belt.Map.String.empty,
  animationVector: Belt.Map.String.empty,
  collideBox: Belt.Map.String.empty,
  collideCircle: Belt.Map.String.empty,
  fieldFloat: Belt.Map.String.empty,
  time: {
    timeNow: 0.0,
    delta: 0.0,
  },
  mouseButtons: 0,
  mousePosition: Vector_Util.zero,
  isDebugInitialized: false,
};