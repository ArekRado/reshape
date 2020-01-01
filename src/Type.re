type vector = (float, float);

type transform = {
  translation: vector,
  rotation: float,
  scale: vector,
}

type image = {
  src: string,
};

type state = {
  entity: list(string),
  position: Belt.Map.String.t(vector),
  image: Belt.Map.String.t(image),
  timeNow: float,
  delta: float,
  currentScene: string,
  sceneInicjalized: bool,
};