[@bs.module "../utils/pixiDraw"] external pixiDraw : Types.state => unit = "default";

let update = (state) => {
  pixiDraw(state);
}