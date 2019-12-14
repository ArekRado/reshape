let create = (x:float, y:float):Type.vector => (x,y);

/* export type Vector2D = [number, number]

type Vector = (x: number, y: number) => Vector2D
export const vector: Vector = (x, y) => [x, y]

type VectorZero = () => Vector2D
export const vectorZero: VectorZero = () => [0, 0]

type VectorUp = () => Vector2D
export const vectorUp: VectorUp = () => [0, 1]

type VectorRight = () => Vector2D
export const vectorRight: VectorRight = () => [1, 0]

type VectorDown = () => Vector2D
export const vectorDown: VectorDown = () => [0, -1]

type VectorLeft = () => Vector2D
export const vectorLeft: VectorLeft = () => [-1, 0]

type VectorOne = () => Vector2D
export const vectorOne: VectorOne = () => [1, 1]

type Add = (v1: Vector2D, v2: Vector2D) => Vector2D
export const add: Add = (v1, v2) => [v1[0] + v2[0], v1[1] + v2[1]]

type Sub = (v1: Vector2D, v2: Vector2D) => Vector2D
export const sub: Sub = (v1, v2) => [v1[0] - v2[0], v1[1] - v2[1]]

type Divide = (v1: Vector2D, v2: Vector2D) => Vector2D
export const divide: Divide = (v1, v2) => [v1[0] / v2[1], v1[1] / v2[1]]

type Multiply = (v1: Vector2D, v2: Vector2D) => Vector2D
export const multiply: Multiply = (v1, v2) => [v1[0] * v2[0], v1[1] * v2[1]]

type Scale = (scalar: number, v: Vector2D) => Vector2D
export const scale: Scale = (scalar, v) => [v[0] * scalar, v[1] * scalar]

type Magnitude = (v: Vector2D) => number
export const magnitude: Magnitude = v =>
  Math.sqrt(Math.pow(v[0], 2) + Math.pow(v[1], 2))

type Distance = (v1: Vector2D, v2: Vector2D) => number
export const distance: Distance = (v1, v2) => magnitude(sub(v1, v2))

type Clamp = (v: Vector2D, vMagnitude: number) => Vector2D
export const clamp: Clamp = (v, vMagnitude) => {
  const currentVectorMagnitude = magnitude(v)

  if (currentVectorMagnitude === 0) {
    return vectorZero()
  }

  const ratio = currentVectorMagnitude / vMagnitude
  return [v[0] / ratio, v[1] / ratio]
}

type Equals = (v1: Vector2D, v2: Vector2D) => boolean
export const equals: Equals = (v1, v2) => v1[0] === v2[0] && v1[1] === v2[1]

type Dot = (v1: Vector2D, v2: Vector2D) => number
export const dot: Dot = (v1, v2) => v1[0] * v2[0] + v1[1] * v2[1]

type Angle = (v1: Vector2D, v2: Vector2D) => number
export const angle: Angle = (v1, v2) =>
  Math.acos(dot(normalize(v1), normalize(v2)))

type AngleDeg = (v1: Vector2D, v2: Vector2D) => number
export const angleDeg: AngleDeg = (v1, v2) => angle(v1, v2) * (180 / Math.PI)

type Limit = (v: Vector2D, min: number, max: number) => Vector2D
export const limit: Limit = (v, min, max) => {
  const vMagnitude = magnitude(v)

  if (vMagnitude < min) {
    return clamp(v, min)
  } else if (vMagnitude > max) {
    return clamp(v, max)
  }

  return v
}

type Normalize = (v: Vector2D) => Vector2D
export const normalize: Normalize = (v: Vector2D): Vector2D => clamp(v, 1)

type RadianToVector = (radian: number) => Vector2D
export const radianToVector: RadianToVector = (radian: number): Vector2D => [
  Math.cos(radian),
  Math.sin(radian),
] */
