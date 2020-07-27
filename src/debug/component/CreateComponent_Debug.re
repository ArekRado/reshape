let options: Belt.List.t(Select_UI.selectOption) = [
  {value: "Transform", text: "Transform", disabled: false},
  {value: "Sprite", text: "Sprite", disabled: false},

  {value: "FieldFloat", text: "Field Float", disabled: false},
  // {value: "FieldInt", text: "Field Int", disabled: false},
  {value: "FieldVector", text: "Field Vector", disabled: false},

  {value: "AnimationFloat", text: "Animation Float", disabled: false},
  {value: "AnimationVector", text: "Animation Vector", disabled: false},

  {value: "CollideBox", text: "Collide Box", disabled: false},
  {value: "CollideCircle", text: "Collide Circle", disabled: false},
];

let mapStringToAction = (value, entity) => {
  switch value {
  | "Transform" => App_Context.CreateTransform(entity);
  | "Sprite" => App_Context.CreateSprite(entity);
  | "FieldFloat" => App_Context.CreateFieldFloat(entity);
  // | "FieldInt" => App_Context.CreateFieldInt(entity);
  | "FieldVector" => App_Context.CreateFieldVector(entity);
  | "AnimationFloat" => App_Context.CreateAnimationFloat(entity);
  | "AnimationVector" => App_Context.CreateAnimationVector(entity);
  | "CollideBox" => App_Context.CreateCollideBox(entity);
  | "CollideCircle" => App_Context.CreateCollideCircle(entity);
  | _ => {
      Js.log3("mapStringToAction has been called with wrong arguments", value, entity);
      App_Context.CreateTransform(entity);
    }
  };
};

[@react.component]
let make = () => {
  let (editorState, _) = React.useContext(Editor_Context.context);
  let (_, appDispatch) = React.useContext(App_Context.context);

  <Select_UI
    label="Add component"
    options={options}
    value=""
    onChange={
      event => ReactEvent.Form.target(event)
        ##value
        ->mapStringToAction(editorState.selectedEntity)
        ->appDispatch
    }
  />
}