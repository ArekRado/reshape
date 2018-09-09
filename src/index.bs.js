

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as DocumentRe from "bs-webapi/src/dom/nodes/DocumentRe.js";
import * as Js_primitive from "bs-platform/lib/es6/js_primitive.js";

var state = /* record */[
  /* x */20.0,
  /* y */20.0
];

function map(f, param) {
  if (param !== undefined) {
    return Js_primitive.some(Curry._1(f, Js_primitive.valFromOption(param)));
  }
  
}

function andThen(f, param) {
  if (param !== undefined) {
    return Curry._1(f, Js_primitive.valFromOption(param));
  }
  
}

var canvasEl = document.createElement("canvas");

map((function (param) {
        param.appendChild(canvasEl);
        return /* () */0;
      }), andThen((function (prim) {
            return Js_primitive.nullable_to_opt(prim.body);
          }), DocumentRe.asHtmlDocument(document)));

document.createElement("div").addEventListener("mousemove", (function (e) {
        console.log(/* tuple */[
              e.screenX,
              e.screenY
            ]);
        return /* () */0;
      }));

var ctx = canvasEl.getContext("2d");

function draw(state, delta) {
  ctx.clearRect(0.0, 0.0, 1000.0, 1000.0);
  ctx.beginPath();
  ctx.arc(state[/* x */0] * delta * 0.001, state[/* y */1] * delta * 0.001, 10.0, 0.0, 10.0, false);
  ctx.stroke();
  return /* () */0;
}

function update(state, delta) {
  return /* record */[
          /* x */state[/* x */0] + 0.1 * delta,
          /* y */state[/* y */1] + 0.1 * delta
        ];
}

function mainLoop(state, start) {
  var dateNow = Date.now();
  var delta = dateNow - start;
  var newState = update(state, delta);
  draw(newState, delta);
  requestAnimationFrame((function () {
          return mainLoop(newState, dateNow);
        }));
  return /* () */0;
}

mainLoop(state, Date.now());

var mouse = /* record */[
  /* x */0.0,
  /* y */0.0
];

var windowWidth = 1000.0;

var windowHeight = 1000.0;

export {
  state ,
  mouse ,
  map ,
  andThen ,
  windowWidth ,
  windowHeight ,
  canvasEl ,
  ctx ,
  draw ,
  update ,
  mainLoop ,
  
}
/* canvasEl Not a pure module */
