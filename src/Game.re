/* open Webapi.Canvas;
open Webapi.Canvas.CanvasElement;
open Webapi.Dom; */
open Reprocessing;

let setup = (env) => {
  Env.size(~width=200, ~height=200, env);
};

let draw = (_state, env) => {
  Draw.background(Constants.black, env);
  Draw.fill(Constants.red, env);
  Draw.rect(~pos=(50, 50), ~width=100, ~height=100, env)
};

run(~setup, ~draw, ());

/* 
type stateType = {
  x: float,
  y: float,
};

let state: stateType = {x: 20.0, y: 20.0};

let map = f =>
  fun
  | Some(v) => Some(f(v))
  | None => None;

let andThen = (f: 'a => option('b)) =>
  fun
  | Some(v) => f(v)
  | None => None;

let windowWidth = 1000.0;
let windowHeight = 1000.0;

let canvasEl = Document.createElement("canvas", document);

document
|> Document.asHtmlDocument
|> andThen(HtmlDocument.body)
|> map(Element.appendChild(canvasEl));

let ctx = getContext2d(canvasEl);

let draw = (state: stateType, delta) => {
  ctx |> Canvas2d.clearRect(~x=0.0, ~y=0.0, ~w=windowWidth, ~h=windowHeight);
  ctx |> Canvas2d.beginPath;
  ctx
  |> Canvas2d.arc(
       ~x=state.x *. delta *. 0.001,
       ~y=state.y *. delta *. 0.001,
       ~r=10.0,
       ~startAngle=0.0,
       ~endAngle=10.0,
       ~anticw=false,
     );
  ctx |> Canvas2d.stroke;
};

let update = (state: stateType, delta) : stateType => {
  x: state.x +. 0.1 *. delta,
  y: state.y +. 0.1 *. delta,
};

let rec mainLoop = (state: stateType, start) => {
  let dateNow = Js.Date.now();
  let delta = dateNow -. start;
  let newState = update(state, delta);
  draw(newState, delta);

  Webapi.requestAnimationFrame(_ => mainLoop(newState, dateNow));
};

mainLoop(state, Js.Date.now()); */