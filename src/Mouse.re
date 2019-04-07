/* open Webapi.Dom;

let mouse = {
  x: 0.0,
  y: 0.0,
};

document
|> Document.createElement("div")
|> Element.addMouseMoveEventListener(e =>
     (MouseEvent.screenX(e), MouseEvent.screenY(e)) |> Js.log
   ); */