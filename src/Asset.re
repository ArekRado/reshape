let addSprite = (~state: Type.state, ~name: string, ~src: string): Type.state => {
  ...state,
  asset: {
    sprite: Belt.List.add(state.asset.sprite, {
      src,
      name,
    }),
  },
};

let removeSprite = (~state: Type.state, ~name: string): Type.state => {
  ...state,
  asset: {
    sprite: Belt.List.keep(state.asset.sprite, item => item.name === name),
  },
};
