module System = {
  module Draw = Draw_System;
  module IO = IO_System;
  module Time = Time_System;
  module Scene = Scene_System;
  module Collide = Collide_System;
}

module Component = {
  module Image = Image_Component;
  module Transform = Transform_Component;
  module Rigidbody = Rigidbody_Component;
}

module Util = {
  module Uuid = Uuid_Util
  module Vector = Vector_Util
}

let initialState: Shared.state = {
  entity: [],
  children: Belt.Map.String.empty,
  transform: Belt.Map.String.empty,
  image: Belt.Map.String.empty,
  rigidbody: Belt.Map.String.empty,
  timeNow: 0.0,
  delta: 0.0,
  scene: TestMap,
  isSceneInicialized: false,
};

let rec runOneFrame = (state: Shared.state): Shared.state => {
  let newState = state 
    |> System.Time.update
    |> System.IO.update
    |> System.Scene.update
    |> System.Collide.update
    |> System.Draw.update

  newState;
};

