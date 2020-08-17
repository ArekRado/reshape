let create =
    (~src: string, ~entity: Belt.Map.String.key, ~state: Type.state)
    : Type.state => {
  ...state,
  sprite: Belt.Map.String.set(state.sprite, entity, {src: src}),
};

let remove = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  sprite: Belt.Map.String.remove(state.sprite, entity),
};

let setSrc = (~state: Type.state, ~entity: Type.entity, ~src: Type.spriteSrc) => {
  ...state,
  sprite:
    Belt.Map.String.update(state.sprite, entity, sprite =>
      switch (sprite) {
      | Some(_) =>
        let newSprite: Type.sprite = {src: src};

        Some(newSprite);
      | None => sprite
      }
    ),
};


let get = (~entity: Type.entity, ~state: Type.state) => 
  Belt.Map.String.get(state.sprite, entity)