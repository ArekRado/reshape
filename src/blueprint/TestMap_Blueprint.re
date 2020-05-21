[@bs.scope "Math"] [@bs.val] external random : unit => float = "random";

let create = (state: Type.state) => {
  let newState =
    state
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       )
    -> City_Blueprint.create(
         ~position=
           Engine.Util.Vector.create(random() *. 1200.0, random() *. 700.0),
       );

      
  {
    ...newState,
    game: {
      ...newState.game,
      isSceneInicialized: true
    }
  }
};