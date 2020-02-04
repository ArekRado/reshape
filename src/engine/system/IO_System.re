open Webapi.Dom;

type t = {
  mutable mouseButtons: int,
  mutable mousePosition: Shared.vector,
};

let io: t = {
  mouseButtons: (-1),
  mousePosition: Vector_Util.create(0.0, 0.0) /* keys */,
};

switch (Document.querySelector("body", document)) {
| Some(el) =>
  Element.addMouseMoveEventListener(
    e => {
      io.mouseButtons = MouseEvent.buttons(e);
      io.mousePosition =
        Vector_Util.create(
          float_of_int(MouseEvent.x(e)),
          float_of_int(MouseEvent.y(e)),
        );
    },
    el,
  )
| None => ()
};

let disableContextMenu = [%raw
  {|
  function() {
    document.addEventListener("contextmenu", e => {
      e.preventDefault();
    });
  }
|}
];

disableContextMenu();

let update = (state: Shared.state): Shared.state => {

  {
    ...statem
    mouseButtons: io.mouseButtons,
    mousePosition: io.mousePosition,
  }
};