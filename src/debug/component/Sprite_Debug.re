[@react.component]
let make = (~sprite: option(Type.sprite)) => 
  switch (sprite) {
  | Some(sprite) => 
    <div className="grid grid-cols-12 gap-1 mt-3">
      <div className="text-white mb-3 col-span-12">
        {React.string("Sprite")}
      </div>

      <div className="col-span-4">{React.string("src")}</div>
      <div className="col-span-8">
        <Input_UI
          value={sprite.src} 
          onChange={_ => {()}}
        />
      </div>
      <div className="col-span-12"><img src={sprite.src} /></div>
    </div>
  | None => React.null
  };