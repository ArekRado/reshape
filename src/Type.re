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

type scenes =
  | TestMap;

type gameState = {
    // area: Belt.Map.String.t(area),
    city: Belt.Map.String.t(city),
    scene: scenes,
    isSceneInicialized: bool,
}  

type state = {
  game: gameState,
  engine: Engine.Shared.state
};