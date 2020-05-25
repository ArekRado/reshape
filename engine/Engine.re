module System = {
  module Draw = Draw_System;
  module IO = IO_System;
  module Time = Time_System;
  /* module Scene = Scene_System; */
  module Collide = Collide_System;
  module AnimationFloat = AnimationFloat_Component;
  module AnimationVector = AnimationVector_Component;
  module Transform = Transform_Component;
};

module Component = {
  module Sprite = Sprite_Component;
  module Transform = Transform_Component;
  module Rigidbody = Rigidbody_Component;
  module AnimationFloat = AnimationFloat_Component;
  module AnimationVector = AnimationVector_Component;
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
  sprite: Belt.Map.String.empty,
  rigidbody: Belt.Map.String.empty,
  animationFloat: Belt.Map.String.empty,
  animationVector: Belt.Map.String.empty,
  time: {
    timeNow: 0.0,
    delta: 0.0,
  },
  mouseButtons: 0,
  mousePosition: Vector_Util.zero,
  isDebugInitialized: false,
};

let runOneFrame =
    (~state: Shared.state, ~enableDraw=true, ~debug=false, ~performanceNow=?, ())
    : Shared.state => {
      
  let newState =
    state
    ->Debug_System.update(~state=_, ~debug)
    ->Time_System.update(~performanceNowOverride=?performanceNow, ~state=_)
    ->IO_System.update(~state=_)
    ->Transform_System.update(~state=_)
    ->Collide_System.update(~state=_)
    ->AnimationFloat_System.update(~state=_)
    ->AnimationVector_System.update(~state=_)
    ->Draw_System.update(~enableDraw, ~state=_);

  newState;
};