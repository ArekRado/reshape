[@bs.scope "performance"] [@bs.val]
external performanceNow: unit => float = "now";

let update = (~state: Shared.state, ~performanceNowOverride=?): Shared.state => {
  let last = state.timeNow;
  let now: float =
    switch (performanceNowOverride) {
    | Some(performanceNow) => performanceNow
    | None => performanceNow()
    };

  {...state, delta: (now -. last) /. 1000.0, timeNow: now};
};