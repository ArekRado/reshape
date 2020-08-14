type entity = string;

type vector = (float, float);

type rotation = float;

type collideType = 
  | Box(string)
  | Circle(string);

type collideBox = {
  entity,
  name: string,
  size: vector,
  position: vector,
  collisions: Belt.List.t(collideType),
};

type collideCircle = {
  entity,
  name: string,
  radius: float,
  position: vector,
  collisions: Belt.List.t(collideType),
};

type transform = {
  rotation,
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
  name: string,
}

type animatedComponent = 
  | FieldFloat(entity)
  | FieldVector(entity)
  | TransformLocalPosition(entity)

type animationValueRange = 
  | Float((float, float))
  | Vector((Vector_Util.t, Vector_Util.t))

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

type keyframe = {
  duration: float,
  timingFunction,
  valueRange: animationValueRange,
};

type animation = {
  entity,
  name: string,
  keyframes: Belt.List.t(keyframe),
  isPlaying: bool,
  isFinished: bool,
  currentTime: float,
  component: animatedComponent,
  wrapMode,
};

type spriteSrc = string;

type sprite = {src: spriteSrc};

type time = {
  timeNow: float,
  delta: float,
};

type asset = {
  sprite: Belt.List.t(string),
};

type state = {
  entity: Belt.List.t(string),
  transform: Belt.Map.String.t(transform),
  sprite: Belt.Map.String.t(sprite),

  animation: Belt.Map.String.t(animation),

  collideBox: Belt.Map.String.t(collideBox),
  collideCircle: Belt.Map.String.t(collideCircle),

  fieldFloat: Belt.Map.String.t(field(float)),
  fieldVector: Belt.Map.String.t(field(Vector_Util.t)),

  mutable mouseButtons: int,
  mutable mousePosition: vector,
  time,
  isDebugInitialized: bool,
  asset,
};

let initialState: state = {
  entity: [],
  transform: Belt.Map.String.empty,
  sprite: Belt.Map.String.empty,
  animation: Belt.Map.String.empty,
  collideBox: Belt.Map.String.empty,
  collideCircle: Belt.Map.String.empty,
  fieldFloat: Belt.Map.String.empty,
  fieldVector: Belt.Map.String.empty,
  time: {
    timeNow: 0.0,
    delta: 0.0,
  },
  mouseButtons: 0,
  mousePosition: Vector_Util.zero,
  isDebugInitialized: false,
  asset: {
    sprite: [],
  },

};