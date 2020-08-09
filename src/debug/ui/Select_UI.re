type selectOption = {
  value: string,
  text: string,
  disabled: bool,
};

[@react.component]
let make = (~options: Belt.List.t(selectOption), ~value, ~onChange, ~label="") => {
  <label>
    <div>{React.string(label)}</div>
    <select
      className="text-black w-full"
      onChange={event => onChange(ReactEvent.Form.target(event)##value)}
      value
    >
      <option/>
      {Belt.List.mapWithIndex(options, (index, option) => 
        <option 
          key={Belt.Int.toString(index)} 
          value={option.value}
          disabled={option.disabled}
        >
          {React.string(option.text)}
        </option>
      )
      ->Array.of_list
      ->React.array}
    </select>
  </label>
}