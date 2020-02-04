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

type timer = {
  value: float,
  maxValue: float,
  isDone: bool,
};

type areaType = 
  | Empty 
  | City 
  | Tower 
  | Baracks 
  | Farm

type area = {
  areaType: areaType
}

type rigidbodyType = 
  | Circle 
  | Square 

type rigidbody = {
  rigidbodyType: rigidbodyType,
  size: vector,
  isClicked: bool,
  isHovered: bool,
}

type image = {src: string};

type scenes =
  | TestMap;

type state = {
  entity: entity,
  children: Belt.Map.String.t(entity),
  transform: Belt.Map.String.t(transform),
  image: Belt.Map.String.t(image),
  timer: Belt.Map.String.t(timer),
  area: Belt.Map.String.t(area),
  rigidbody: Belt.Map.String.t(rigidbody),

  mutable mouseButtons: int,
  mutable mousePosition: vector,

  timeNow: float,
  delta: float,

  scene: scenes,
  isSceneInicialized: bool,
}
