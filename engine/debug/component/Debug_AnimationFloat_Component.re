[@react.component]
let make = (~items: Belt.Map.String.t(Shared.animation(float))) => 
  items
    ->Belt.Map.String.toArray
    ->Belt.Array.map(((id, animation)) =>
      <div key={id}>
        <div className="grid grid-cols-12 gap-1 mb-3">
          <div className="text-white mb-3 col-span-12">
            {React.string("Animation (float)")}
          </div>
          <div className="col-span-4">{React.string("id")}</div>
          <div className="col-span-8">{React.string(Debug_Util.humanFriendlyEntity(id))}</div>
          <div className="col-span-4">{React.string("isPlaying")}</div>
          <div className="col-span-8">{React.string(animation.isPlaying ? "true" : "false")}</div>
          <div className="col-span-4">{React.string("currentTime")}</div>
          <div className="col-span-8">{React.string(Belt.Float.toString(animation.currentTime))}</div>
          <div className="col-span-4">{React.string("value")}</div>
          <div className="col-span-8">{React.string(Belt.Float.toString(animation.value))}</div>
        </div>

        <div className="my-1">
          {React.string("keyframes")}
        </div>
        <div>
          {Belt.List.mapWithIndex(animation.keyframes, (index, keyframe) => {
            let (from, to_) = keyframe.valueRange;

            <div key={Belt.Int.toString(index)} className="grid grid-cols-12 gap-1">
              <div className="col-span-12">{React.string("#" ++ Belt.Int.toString(index))}</div>
              <div className="col-span-4">{React.string("duration")}</div>
              <div className="col-span-8">{React.string(Belt.Float.toString(keyframe.duration))}</div>
              <div className="col-span-4">{React.string("timingFunction")}</div>
              <div className="col-span-8">{React.string("Linear")}</div>
              <div className="col-span-4">{React.string("valueRange")}</div>
              <div className="col-span-8">{React.string( Belt.Float.toString(from) ++ " - " ++ Belt.Float.toString(to_))}</div>
            </div>
          })
          ->Array.of_list
          ->React.array
          }
        </div>
      </div>
    )
    ->React.array;