module Uuid = Uuid_Util;
module Vector = Vector_Util;
module Test = Test_Util;

let runOneFrame =
    (~state: Type.state, ~enableDraw=true, ~performanceNow=?, ())
    : Type.state => {
      
  let newState =
    state
    ->Time_System.update(~performanceNowOverride=?performanceNow, ~state=_, ())
    ->IO_System.update(~state=_)
    ->Transform_System.update(~state=_)
    ->Collide_System.update(~state=_)
    ->Animation_System.update(~state=_)
    ->Draw_System.update(~enableDraw, ~state=_);

  newState;
};

let initialize = () => {
    switch (Webapi.Dom.Document.querySelector("body", Webapi.Dom.document)) {
    | Some(body) => {
      let container = Webapi.Dom.Document.createElement("div", Webapi.Dom.document);
      Webapi.Dom.Element.setAttribute("id", "engine-game", container);
      Webapi.Dom.Element.appendChild(container, body);
    }
    | None => ()
  };

  IO_System.initialize();
}