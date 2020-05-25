[@react.component]
let make = (~vector: Vector_Util.t) => {
  let (x,y) = vector;

  <div>
    {React.string("x: " ++ Belt.Float.toString(x))}
    <br/>
    {React.string("y: " ++ Belt.Float.toString(y))}
  </div>
}