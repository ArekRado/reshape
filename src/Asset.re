let addSprite = (~state:Type.state, ~sprite: Type.spriteSrc): Type.state => {
   ...state,
   asset: {
     sprite: Belt.List.add(state.asset.sprite, sprite),
   },
 };

 let removeSprite = (~state:Type.state, ~sprite: Type.spriteSrc): Type.state => {
   ...state,
   asset: {
     sprite: Belt.List.keep(state.asset.sprite, (item) => item === sprite),
   },
 };