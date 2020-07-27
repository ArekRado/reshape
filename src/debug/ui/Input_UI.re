[@react.component]
let make = (~type_="text", ~value, ~onChange, ~label:option(React.element)=?, ~className="") => {

  <label 
    // onClick={onClick}  
    // className={btnSize ++ " border border-gray-600 bg-gray-800 hover:bg-gray-700"}
  >
    {
      switch(label) {
      | Some(label) => label
      | None => React.null
      }
    }
    <input 
      className={className ++ " text-black w-full"}
      type_
      value
      onChange
    />
  </label>
}