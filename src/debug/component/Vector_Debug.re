[@react.component]
let make = (~value: Vector_Util.t, ~onChange) => {
  let (x,y) = value;

  // <div>
  //   {React.string("x: " ++ Belt.Float.toString(x))}
  //   <br/>
  //   {React.string("y: " ++ Belt.Float.toString(y))}
  // </div>


  <div className="flex">
    <Input_UI 
      className="flex-1"
      type_="number"
      value={Belt.Float.toString(x)} 
      onChange={event => onChange((ReactEvent.Form.target(event)##value, y))}
    />
    <Input_UI 
      className="flex-1"
      type_="number"
      value={Belt.Float.toString(y)} 
      onChange={event => onChange((x, ReactEvent.Form.target(event)##value))}
    />
  </div>
}