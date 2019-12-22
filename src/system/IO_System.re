open Webapi.Dom;

module IO {
  type t = {
    mutable mouseButtons: int,
    mutable mousePosition: Type.vector,
  };
}

let io: IO.t = {
  mouseButtons: -1,
  mousePosition: Vector.create(0.0,0.0),
  /* keys */
};

switch (Document.querySelector("body", document)) {
  | Some(el) => Element.addMouseMoveEventListener(e => {
      io.mouseButtons = MouseEvent.buttons(e);
      io.mousePosition = Vector.create(
        float_of_int(MouseEvent.x(e)),
        float_of_int(MouseEvent.y(e))
      );
    }, el);
  | None => ()
  };

let disableContextMenu = [%raw {|
  function() { 
    document.addEventListener("contextmenu", e => {
      e.preventDefault();
    });
  }
|}];

/* disableContextMenu(); */

let update = () => {
  io;
}