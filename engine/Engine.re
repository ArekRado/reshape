module System = {
  module Draw = Draw_System;
  module IO = IO_System;
  module Time = Time_System;
  /* module Scene = Scene_System; */
  module Collide = Collide_System;
  module AnimationFloat = AnimationFloat_System;
  module AnimationVector = AnimationVector_System;
  module Transform = Transform_System;
};

module Component = {
  module Sprite = Sprite_Component;
  module Transform = Transform_Component;
  module AnimationFloat = AnimationFloat_Component;
  module AnimationVector = AnimationVector_Component;
  module CollideBox = CollideBox_Component;
  module CollideCircle = CollideCircle_Component;
};

module Util = {
  module Uuid = Uuid_Util;
  module Vector = Vector_Util;
  module Test = Test_Util;
};

module Entity = Entity;

module Shared = Shared;

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