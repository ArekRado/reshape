let wrapModeToString = (wrapMode: Type.wrapMode) =>
  switch (wrapMode) {
  | Type.Once => "Once"
  | Type.Loop => "Loop"
  | Type.PingPong => "PingPong"
  | Type.ClampForever => "ClampForever"
  };

let timingFunctionToString = (timingFunction: Type.timingFunction) =>
  switch (timingFunction) {
  | Type.Linear => "Linear"
  | Type.EaseInQuad => "EaseInQuad"
  | Type.EaseOutQuad => "EaseOutQuad"
  | Type.EaseInOutQuad => "EaseInOutQuad"
  | Type.EaseInCubic => "EaseInCubic"
  | Type.EaseOutCubic => "EaseOutCubic"
  | Type.EaseInOutCubic => "EaseInOutCubic"
  | Type.EaseInQuart => "EaseInQuart"
  | Type.EaseOutQuart => "EaseOutQuart"
  | Type.EaseInOutQuart => "EaseInOutQuart"
  | Type.EaseInQuint => "EaseInQuint"
  | Type.EaseOutQuint => "EaseOutQuint"
  | Type.EaseInOutQuint => "EaseInOutQuint"
  | Type.CubicBezier(_, _, _, _) => "CubicBezier"
  };

let componentList: Belt.List.t(Select_UI.selectOption) = [
  {value: "FieldFloat", text: "Field Float", disabled: false},
  {value: "FieldVector", text: "Field Vector", disabled: false},
  {
    value: "TransformLocalPosition",
    text: "Transform.localPosition",
    disabled: false,
  },
];

let componentEntitiesList =
    (appState: Type.state, component: Type.animatedComponent)
    : Belt.List.t(Select_UI.selectOption) => {
  let selectOption =
    switch (component) {
    | FieldFloat(_) =>
      Belt.Map.String.mapWithKey(appState.fieldFloat, (key, _) =>
        (
          {
            value: key,
            text: Uuid_Util.humanFriendlyEntity(key),
            disabled: false,
          }: Select_UI.selectOption
        )
      )
    | FieldVector(_) =>
      Belt.Map.String.mapWithKey(appState.fieldVector, (key, _) =>
        (
          {
            value: key,
            text: Uuid_Util.humanFriendlyEntity(key),
            disabled: false,
          }: Select_UI.selectOption
        )
      )
    | TransformLocalPosition(_) =>
      Belt.Map.String.mapWithKey(appState.transform, (key, _) =>
        (
          {
            value: key,
            text: Uuid_Util.humanFriendlyEntity(key),
            disabled: false,
          }: Select_UI.selectOption
        )
      )
    // | _ => {
    //   Js.log("Wrong switch option");
    //   Belt.Map.String.empty
    // }
    };

  selectOption->Belt.Map.String.valuesToArray->Belt.List.fromArray;
};

let getComponentEntity = (component: Type.animatedComponent): string =>
  switch (component) {
  | FieldFloat(entity, _) => entity
  | FieldVector(entity, _) => entity
  | TransformLocalPosition(entity) => entity
  };

let mapTextToComponent = (component: string): Type.animatedComponent =>
  switch (component) {
  | "FieldFloat" => FieldFloat("", "")
  | "FieldVector" => FieldVector("", "")
  | "TransformLocalPosition" => TransformLocalPosition("")
  | _ =>
    Js.log("Wrong switch option");
    FieldFloat("", "");
  };

let mapComponentToText = (component: Type.animatedComponent): string =>
  switch (component) {
  | FieldFloat(_) => "FieldFloat"
  | FieldVector(_) => "FieldVector"
  | TransformLocalPosition(_) => "TransformLocalPosition"
  };

let setAnimationComponent =
    (
      ~selectedEntity,
      ~appDispatch,
      ~component,
      ~componentEntity,
      ~animationName,
    ) => {
  let animatedComponent =
    switch (component) {
    | Type.FieldFloat(_, name) => Type.FieldFloat(componentEntity, name)
    | Type.FieldVector(_, name) => Type.FieldVector(componentEntity, name)
    | Type.TransformLocalPosition(_) =>
      Type.TransformLocalPosition(componentEntity)
    };

  appDispatch(
    App_Context.SetAnimationComponent(
      selectedEntity,
      animationName,
      animatedComponent,
    ),
  );

  ();
};

let msToTime = ms => {
  let seconds = mod_float(ms /. 1000.0, 60.0);
  let minutes = mod_float(ms /. (1000.0 *. 60.0), 60.0);

  let formattedMinutes =
    minutes < 10.0
      ? "0" ++ Js.Float.toFixed(minutes) : Js.Float.toFixed(minutes);

  let formattedSeconds =
    seconds < 10.0
      ? "0" ++ Js.Float.toFixed(seconds) : Js.Float.toFixed(seconds);

  formattedMinutes ++ ":" ++ formattedSeconds;
};

[@react.component]
let make = (~name: Type.entity) => {
  let (appState, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);
  let (editorState, _) = React.useContext(Editor_Context .context);

  let stateAnimation = Belt.Map.String.get(appState.animation, name);

  let (animation, setAnimation) = React.useState(() => stateAnimation);

  let modalBody =
    switch (animation) {
    | None => React.string("Animation doesn't exist")
    | Some(animation) =>
      let animationLength =
        Belt.List.reduce(animation.keyframes, 0.0, (sum, keyframe) =>
          keyframe.duration +. sum
        );

      <>
        <div className="grid grid-cols-12 gap-1 my-1">
          <div className="col-span-6 grid grid-cols-12 gap-1">
            <div className="col-span-4"> {React.string("name")} </div>
            <div className="col-span-8">
              <Input_UI value=name onChange={_ => {()}} />
            </div>
            <div className="col-span-4"> {React.string("isPlaying")} </div>
            <div className="col-span-8">
              {React.string(animation.isPlaying ? "true" : "false")}
            </div>
            <div className="col-span-4"> {React.string("currentTime")} </div>
            <div className="col-span-8">
              <Input_UI
                type_="number"
                value={Belt.Float.toString(animation.currentTime)}
                onChange={_ => {()}}
              />
            </div>
            <div className="col-span-4"> {React.string("component")} </div>
            <div className="col-span-4">
              <Select_UI
                label=""
                options=componentList
                value={mapComponentToText(animation.component)}
                onChange={component =>
                  setAnimationComponent(
                    ~appDispatch,
                    ~component=mapTextToComponent(component),
                    ~componentEntity="",
                    ~animationName=name,
                    ~selectedEntity=editorState.selectedEntity,
                  )
                }
              />
            </div>
            <div className="col-span-4">
              <Select_UI
                label=""
                options={componentEntitiesList(appState, animation.component)}
                value={getComponentEntity(animation.component)}
                onChange={componentEntity =>
                  setAnimationComponent(
                    ~appDispatch,
                    ~component=animation.component,
                    ~componentEntity,
                    ~animationName=name,
                    ~selectedEntity=editorState.selectedEntity,
                  )
                }
              />
            </div>
            <div className="col-span-4"> {React.string("isFinished")} </div>
            <div className="col-span-8">
              {React.string(animation.isFinished ? "true" : "false")}
            </div>
            <div className="col-span-4"> {React.string("wrapMode")} </div>
            <div className="col-span-8">
              {React.string(wrapModeToString(animation.wrapMode))}
            </div>
          </div>
          <div className="col-span-6 grid grid-cols-12 gap-1 my-1">
            {React.string("ssss")}
          </div>
        </div>
        <div
          className="flex border-solid border border-black h-20 bg-gray-700 bg-opacity-75 relative overflow-hidden">

            {Belt.List.mapWithIndex(
               animation.keyframes, (index, keyframe: Type.keyframe) =>
               switch (keyframe.valueRange) {
               | Float((from, to_)) =>
                 <div
                   key={Belt.Int.toString(index)}
                   className="flex flex-wrap items-center justify-center border-r border-black overflow-hidden"
                   style={ReactDOMRe.Style.make(
                     ~flex=
                       Belt.Float.toString(
                         keyframe.duration *. animationLength /. 100.0,
                       ),
                     (),
                   )}>
                   {React.string(
                      timingFunctionToString(keyframe.timingFunction),
                    )}
                   <br />
                   {React.string(Belt.Float.toString(from))}
                   {React.string(" - ")}
                   {React.string(Belt.Float.toString(to_))}
                 </div>
               | Vector((from, to_)) =>
                 <div
                   key={Belt.Int.toString(index)}
                   className="flex flex-wrap items-center justify-center border-r border-black overflow-hidden"
                   style={ReactDOMRe.Style.make(
                     ~flex=
                       Belt.Float.toString(
                         keyframe.duration *. animationLength /. 100.0,
                       ),
                     (),
                   )}>
                   {React.string(
                      timingFunctionToString(keyframe.timingFunction),
                    )}
                   <br />
                   <Vector_Debug value=from onChange={_ => {()}} />
                   {React.string(" - ")}
                   <Vector_Debug value=to_ onChange={_ => {()}} />
                 </div>
               }
             )
             ->Array.of_list
             ->React.array}
            <div
              className="absolute w-full h-full flex flex-col justify-between"
              style={ReactDOMRe.Style.make(
                ~transform=
                  "translate("
                  ++ Belt.Float.toString(
                       animation.currentTime *. 100.0 /. animationLength,
                     )
                  ++ "%)",
                (),
              )}>
              <div className="ml-1 overflow-hidden w-10">
                {React.string(msToTime(animation.currentTime))}
              </div>
              <div className="absolute border-l border-red-500 h-full" />
            </div>
          </div>
          // <div className="ml-1 overflow-hidden w-10">{React.string(Js.Float.toFixedWithPrecision(animation.value, ~digits=2))}</div>
      </>;
    };

  <Modal_UI
    id="animationModal"
    render={(modal: Modal_Context.modal) => modalBody}
  />;
};
