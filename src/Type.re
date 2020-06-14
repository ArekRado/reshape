type areaType =
  | Empty
  | City
  | Tower
  | Baracks
  | Farm;

type area = {
  areaType,
  size: float
};

type city = {
  // areaType,
  size: float
};

type humanPorter = {
  target: Engine.Util.Vector.t
};

type scenes =
  | TestMap;

type gameState = {
    // area: Belt.Map.String.t(area),
    city: Belt.Map.String.t(city),
    humanPorter: Belt.Map.String.t(humanPorter),
    scene: scenes,
    isSceneInicialized: bool,
}  

type state = {
  game: gameState,
  engine: Engine.Shared.state
};