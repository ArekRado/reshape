type vector = (float, float);

type transform = {
  translation: vector,
  rotation: float,
  scale: vector,
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

type image = {src: string};

type scenes =
  | TestMap;

type state = {
  entity: Belt.List.t(string),
  position: Belt.Map.String.t(vector),
  image: Belt.Map.String.t(image),
  timer: Belt.Map.String.t(timer),
  area: Belt.Map.String.t(area),
  timeNow: float,
  delta: float,
  scene: scenes,
  isSceneInicialized: bool,
};