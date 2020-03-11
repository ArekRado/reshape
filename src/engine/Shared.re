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
  transform: Belt.Map.String.t(transform),
  image: Belt.Map.String.t(image),
  rigidbody: Belt.Map.String.t(rigidbody),
  mutable mouseButtons: int,
  mutable mousePosition: vector,
  timeNow: float,
  delta: float,
};