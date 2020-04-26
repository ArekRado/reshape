module System = {
  module Draw = Draw_System;
  module IO = IO_System;
  module Time = Time_System;
  /* module Scene = Scene_System; */
  module Collide = Collide_System;
  module Transition = Transition_System;
};

module Component = {
  module Image = Image_Component;
  module Transform = Transform_Component;
  module Rigidbody = Rigidbody_Component;
  module TransitionFloat = TransitionFloat_Component;
  module TransitionVector = TransitionVector_Component;
};

module Util = {
  module Uuid = Uuid_Util;
  module Vector = Vector_Util;
};

module Entity = Entity;

module Shared = Shared;

let initialState: Shared.state = {
  entity: [],
  transform: Belt.Map.String.empty,
  image: Belt.Map.String.empty,
  rigidbody: Belt.Map.String.empty,
  transitionFloat: Belt.Map.String.empty,
  transitionVector: Belt.Map.String.empty,
  time: {
    timeNow: 0.0,
    delta: 0.0,
  },

  mouseButtons: 0,
  mousePosition: Vector_Util.zero(),
};

let runOneFrame =
    (~state: Shared.state, ~enableDraw=true, ~performanceNow=?, ())
    : Shared.state => {
  let newState =
    state
    ->Time_System.update(~performanceNowOverride=?performanceNow, ~state=_)
    ->IO_System.update(~state=_)
    ->Collide_System.update(~state=_)
    ->Transition_System.update(~state=_)
    ->Draw_System.update(~enableDraw, ~state=_);

  newState;
};