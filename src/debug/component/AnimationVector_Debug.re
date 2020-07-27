[@react.component]
let make = (~items: Belt.Map.String.t(Type.animation(Vector_Util.t))) => {
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
            <div className="text-white col-span-12">
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
              onAccept={(_) => appDispatch(RemoveAnimationVector(name))}
            />
          </div>

          <div className="grid grid-cols-12 gap-1 mb-3 my-1">
            <div className="col-span-4">{React.string("name")}</div>
            <div className="col-span-8">
              <Input_UI 
                value={name} 
                onChange={(_) => {()}}
              />
            </div>
            <div className="col-span-4">{React.string("isPlaying")}</div>
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
              <Vector_Debug 
                value={animation.value} 
                onChange={(_) => {()}}
              />
            </div>
            <div className="col-span-4">{React.string("isFinished")}</div>
            <div className="col-span-8">{React.string(animation.isFinished ? "true" : "false")}</div>
            <div className="col-span-4">{React.string("wrapMode")}</div>
            <div className="col-span-8">{React.string(AnimationFloat_Debug.wrapModeToString(animation.wrapMode))}</div>
          </div>

          <div className="flex border-solid border border-black h-20 bg-gray-700 bg-opacity-75 relative overflow-hidden">
            {Belt.List.mapWithIndex(animation.keyframes, (index, keyframe) => {
              let (from, to_) = keyframe.valueRange;

              <div 
                key={Belt.Int.toString(index)}
                className="flex flex-wrap items-center justify-center border-r border-black overflow-hidden"
                style={ReactDOMRe.Style.make(
                  ~flex=Belt.Float.toString(keyframe.duration *. animationLength /. 100.0),
                   ()
                )}
              >
                {React.string(AnimationFloat_Debug.timingFunctionToString(keyframe.timingFunction))}
                <br/>
                <Vector_Debug value={from} onChange={(_) => {()}}/>
                {React.string(" - ")}
                <Vector_Debug value={to_} onChange={(_) => {()}}/>
              </div>
            })
            ->Array.of_list
            ->React.array
            }

            <div
              className="absolute w-full h-full flex flex-col justify-between"
              style={ReactDOMRe.Style.make(
                  ~transform="translate(" ++ Belt.Float.toString(animation.currentTime *. 100.0 /. animationLength) ++ "%)",
                  ()
              )}
            >
                <div className="ml-1 overflow-hidden w-10">{React.string(AnimationFloat_Debug.msToTime(animation.currentTime))}</div>
                <div className="absolute border-l border-red-500 h-full"/>

                <div className="ml-1 overflow-hidden w-10">
                  <Vector_Debug value={animation.value} onChange={(_) => {()}}/>
                </div>
            </div>
          </div>
        </div>
      }
    )
    ->React.array;
};