type vector = (float, float);

type entity = Belt.List.t(string);

type transform = {
  translation: vector,
  rotation: float,
  scale: vector,
  position: vector,
  localPosition: vector,
};

type io = {
  mutable mouseButtons: int,
  mutable mousePosition: vector,
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
  | Farm;

type area = {areaType};

type rigidbodyType =
  | Circle
  | Square;

type rigidbody = {
  rigidbodyType,
  size: vector,
  isClicked: bool,
  isHovered: bool,
};

type image = {src: string};

type scenes =
  | TestMap;

type state = {
  entity,
  children: Belt.Map.String.t(entity),
  transform: Belt.Map.String.t(vector),
  image: Belt.Map.String.t(image),
  timer: Belt.Map.String.t(timer),
  area: Belt.Map.String.t(area),
  rigidbody: Belt.Map.String.t(rigidbody),
  timeNow: float,
  delta: float,
  scene: scenes,
  isSceneInicialized: bool,
};