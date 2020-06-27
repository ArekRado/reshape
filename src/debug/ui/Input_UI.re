[@react.component]
let make = (~type_="text", ~value, ~onChange, ~label="") => {

  <label 
    // onClick={onClick}  
    // className={btnSize ++ " border border-gray-600 bg-gray-800 hover:bg-gray-700"}
  >
    <div>{React.string(label)}</div>
    <input 
      className="text-black"
      type_
      value
      onChange
    />
  </label>
}