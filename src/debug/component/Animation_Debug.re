let wrapModeToString = (wrapMode: Type.wrapMode) => 
  switch wrapMode {
  | Type.Once => "Once"
  | Type.Loop => "Loop"
  | Type.PingPong => "PingPong"
  | Type.ClampForever => "ClampForever"
  };

let timingFunctionToString = (timingFunction: Type.timingFunction) => 
  switch timingFunction {
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
  | Type.CubicBezier(_, _ ,_ ,_) => "CubicBezier"
  };

let msToTime = (ms) => {
  let seconds = mod_float(ms /. 1000.0, 60.0);
  let minutes = mod_float(ms /. (1000.0 *. 60.0), 60.0);

  let formattedMinutes = (minutes < 10.0) 
    ? "0" ++ Js.Float.toFixed(minutes) 
    : Js.Float.toFixed(minutes);

  let formattedSeconds = (seconds < 10.0) 
    ? "0" ++ Js.Float.toFixed(seconds) 
    : Js.Float.toFixed(seconds);

  formattedMinutes ++ ":" ++ formattedSeconds;
};

[@react.component]
let make = (~items: Belt.Map.String.t(Type.newAnimation)) => {
  let (_, appDispatch) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  items
    ->Belt.Map.String.toArray
    ->Belt.Array.map(((name, animation)) => {
        let animationLength = Belt.List.reduce(
          animation.keyframes, 
          0.0, 
          (sum, keyframe) => keyframe.duration +. sum
        );

        <div key={name} className="mt-3">
          <div className="flex justify-between">
            <div className="text-white">
              {React.string("Animation (float)")}
            </div>

            <Button_UI
              onClick={(_) => {
                modalDispatch(OpenModal(name, None))
              }}
            >
              {React.string("x")}
            </Button_UI>

            <ConfirmModal_Debug
              name={name}
              title={React.string("Are you sure you want to remove animation?")}
              onAccept={(_) => appDispatch(RemoveAnimation(name))}
            />
          </div>

          <div className="grid grid-cols-12 gap-1 my-1">
            <div className="col-span-4">{React.string("name")}</div>
            <div className="col-span-8">
              <Input_UI 
                value={name} 
                onChange={(_) => {()}}
              />
            </div>            <div className="col-span-4">{React.string("isPlaying")}</div>
            <div className="col-span-8">{React.string(animation.isPlaying ? "true" : "false")}</div>
            <div className="col-span-4">{React.string("currentTime")}</div>
            <div className="col-span-8">
              <Input_UI 
                type_="number" 
                value={Belt.Float.toString(animation.currentTime)} 
                onChange={(_) => {()}}
              />
            </div>
            <div className="col-span-4">{React.string("value")}</div>
            <div className="col-span-8">
              // <Input_UI 
              //   type_="number" 
              //   value={Belt.Float.toString(animation.value)} 
              //   onChange={(_) => {()}}
              // />
            </div>
            <div className="col-span-4">{React.string("isFinished")}</div>
            <div className="col-span-8">{React.string(animation.isFinished ? "true" : "false")}</div>
            <div className="col-span-4">{React.string("wrapMode")}</div>
            <div className="col-span-8">{React.string(wrapModeToString(animation.wrapMode))}</div>
          </div>

          <div className="flex border-solid border border-black h-20 bg-gray-700 bg-opacity-75 relative overflow-hidden">
            // {Belt.List.mapWithIndex(animation.keyframes, (index, keyframe) => {
            //   let (from, to_) = keyframe.valueRange;

            //   <div 
            //     key={Belt.Int.toString(index)}
            //     className="flex flex-wrap items-center justify-center border-r border-black overflow-hidden"
            //     style={ReactDOMRe.Style.make(
            //       ~flex=Belt.Float.toString(keyframe.duration *. animationLength /. 100.0),
            //        ()
            //     )}
            //   >
            //     {React.string(timingFunctionToString(keyframe.timingFunction))}
            //     <br/>
            //     {React.string(Belt.Float.toString(from))}
            //     {React.string(" - ")}
            //     {React.string(Belt.Float.toString(to_))}
            //   </div>
            // })
            // ->Array.of_list
            // ->React.array
            // }

            <div
              className="absolute w-full h-full flex flex-col justify-between"
              style={ReactDOMRe.Style.make(
                  ~transform="translate(" ++ Belt.Float.toString(animation.currentTime *. 100.0 /. animationLength) ++ "%)",
                  ()
              )}
            >
                <div className="ml-1 overflow-hidden w-10">{React.string(msToTime(animation.currentTime))}</div>
                <div className="absolute border-l border-red-500 h-full"/>
                // <div className="ml-1 overflow-hidden w-10">{React.string(Js.Float.toFixedWithPrecision(animation.value, ~digits=2))}</div>
            </div>
          </div>
        </div>
      }
    )
    ->React.array;
};