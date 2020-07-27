[@react.component]
let make = (~transform: option(Type.transform)) => 
  switch (transform) {
  | Some(transform) => 
    <div className="grid grid-cols-12 gap-1 mt-3">
      <div className="text-white mb-3 col-span-12">
        {React.string("Transform")}
      </div>
      <div className="col-span-4">{React.string("position")}</div>
      <div className="col-span-8">
        <Vector_Debug 
          value={transform.position} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("localPosition")}</div>
      <div className="col-span-8">
        <Vector_Debug 
          value={transform.localPosition} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("rotation")}</div>
      <div className="col-span-8">
        <Input_UI 
          type_="number" 
          value={Belt.Float.toString(transform.rotation)} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("localRotation")}</div>
      <div className="col-span-8">
        <Input_UI 
          type_="number" 
          value={Belt.Float.toString(transform.localRotation)} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("scale")}</div>
      <div className="col-span-8">
        <Vector_Debug 
          value={transform.scale} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("localScale")}</div>
      <div className="col-span-8">
        <Vector_Debug 
          value={transform.localScale} 
          onChange={(_) => {()}}
        />
      </div>
      <div className="col-span-4">{React.string("parent")}</div>
      <div className="col-span-8">
        {switch (transform.parent) {
        | Some(parent) => React.string(Uuid_Util.humanFriendlyEntity(parent))
        | None => React.string("None")
        };}
      </div>
    </div>
  | None => React.null
  };