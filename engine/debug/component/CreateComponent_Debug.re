let options: Belt.List.t(Select_UI.selectOption) = [
  {value: "Transform", text: "Transform", disabled: false},
  {value: "Sprite", text: "Sprite", disabled: false},

  {value: "FieldFloat", text: "Field Float", disabled: false},
  {value: "FieldInt", text: "Field Int", disabled: false},
  {value: "FieldVector", text: "Field Vector", disabled: false},

  {value: "AnimationFloat", text: "Animation Float", disabled: false},
  {value: "AnimationVector", text: "Animation Vector", disabled: false},

  {value: "CollideBox", text: "Collide Box", disabled: false},
  {value: "CollideCircle", text: "Collide Circle", disabled: false},
];

let mapStringToAction = (value, entity) => {
    Js.log(value);

  switch value {
  | "Transform" => Type_Debug.CreateTransform(entity);
  | "Sprite" => Type_Debug.CreateSprite(entity);
  | "FieldFloat" => Type_Debug.CreateFieldFloat(entity);
  | "FieldInt" => Type_Debug.CreateFieldInt(entity);
  | "FieldVector" => Type_Debug.CreateFieldVector(entity);
  | "AnimationFloat" => Type_Debug.CreateAnimationFloat(entity);
  | "AnimationVector" => Type_Debug.CreateAnimationVector(entity);
  | "CollideBox" => Type_Debug.CreateCollideBox(entity);
  | "CollideCircle" => Type_Debug.CreateCollideCircle(entity);
  };
  };

[@react.component]
let make = (~dispatch, ~entity) => {
  <Select_UI
    label="Add component"
    options={options}
    value=""
    onChange={
      event => ReactEvent.Form.target(event)
        ##value
        ->mapStringToAction(entity)
        ->dispatch
    }
  />
}