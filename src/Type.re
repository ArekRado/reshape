type vector = (float, float);

type image = {
  src: string,
  position: vector,
};

type state = {
  entity: list(int),
  position: list(int),
  image: list(image),
};