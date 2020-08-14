type t = (float, float);

let create = (x: float, y: float): t => (x, y);

let zero: t = (0.0, 0.0);
let up: t = (0.0, 1.0);
let right: t = (1.0, 0.0);
let down: t = (0.0, (-1.0));
let left: t = ((-1.0), 0.0);
let one: t = (1.0, 1.0);

let add = ((x1, y1): t, (x2, y2): t): t => (x1 +. x2, y1 +. y2);
let sub = ((x1, y1): t, (x2, y2): t): t => (x1 -. x2, y1 -. y2);

let multiply = ((x1, y1): t, (x2, y2): t): t => (x1 *. x2, y1 *. y2);
let divide = ((x1, y1): t, (x2, y2): t): t => (x1 /. x2, y1 /. y2);

let scale = (scalar: float, (x1, y1): t): t => (x1 *. scalar, y1 *. scalar);

let magnitude = ((x, y): t): float => sqrt(x ** 2.0 +. y ** 2.0);

let isEqual = ((x1, y1): t, (x2, y2): t): bool => x1 === x2 && y1 === y2;
let isGreater = (v1: t, v2: t): bool => magnitude(v1) > magnitude(v2);
let isLesser = (v1: t, v2: t): bool => magnitude(v1) < magnitude(v2);

/*

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
