[@react.component]
let make = (~transform: option(Shared.transform)) => 
  switch (transform) {
  | Some(transform) => 
    <div className="grid grid-cols-12 gap-1 mb-3">
      <div className="text-white mb-3 col-span-12">
        {React.string("Transform")}
      </div>
      <div className="col-span-4">{React.string("position")}</div>
      <div className="col-span-8"><Debug_Vector vector={transform.position}/></div>
      <div className="col-span-4">{React.string("localPosition")}</div>
      <div className="col-span-8"><Debug_Vector vector={transform.localPosition}/></div>
      <div className="col-span-4">{React.string("rotation")}</div>
      <div className="col-span-8">{React.string(Belt.Float.toString(transform.rotation))}</div>
      <div className="col-span-4">{React.string("localRotation")}</div>
      <div className="col-span-8">{React.string(Belt.Float.toString(transform.localRotation))}</div>
      <div className="col-span-4">{React.string("scale")}</div>
      <div className="col-span-8"><Debug_Vector vector={transform.scale}/></div>
      <div className="col-span-4">{React.string("localScale")}</div>
      <div className="col-span-8"><Debug_Vector vector={transform.localScale}/></div>
    </div>
  | None => React.null
  };