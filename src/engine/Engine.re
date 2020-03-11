module System = {
  module Draw = Draw_System;
  module IO = IO_System;
  module Time = Time_System;
  /* module Scene = Scene_System; */
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

module Entity = Entity

module Shared = Shared

let initialState: Shared.state = {
  entity: [],
  transform: Belt.Map.String.empty,
  image: Belt.Map.String.empty,
  rigidbody: Belt.Map.String.empty,
  timeNow: 0.0,
  delta: 0.0,

  mouseButtons: 0,
  mousePosition: Vector_Util.zero()
};

let rec runOneFrame = (state: Shared.state): Shared.state => {
  let newState = state 
    |> Time_System.update
    |> IO_System.update
    |> Collide_System.update
    |> Draw_System.update

  newState;
};

