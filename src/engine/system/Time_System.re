[@bs.scope "performance"] [@bs.val]
external performanceNow : unit => float = "now";

let update = (state: Shared.state) : Shared.state => {
  let last = state.timeNow;
  let now = performanceNow();

  {...state, delta: (now -. last) /. 1000.0, timeNow: now};
};