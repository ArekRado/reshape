[@bs.module "../util/pixiDraw"]
external pixiDraw: list(string) => unit = "default";

let update = (~state: Shared.state, ~debug:bool): Shared.state => {
  if(debug) {
    if(!state.isDebugInitialized) {
      Debug.initialize(state);

      {
        ...state,
        isDebugInitialized: true,
      };
    } else {
      state;
    }
  } else {
    state;
  }
};