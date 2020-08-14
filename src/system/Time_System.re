[@bs.scope "performance"] [@bs.val]
external performanceNow: unit => float = "now";

let update = (~state: Type.state, ~performanceNowOverride=?, ()): Type.state => {
  let now: float =
    switch (performanceNowOverride) {
    | Some(performanceNow) => performanceNow
    | None => performanceNow()
    };

  {
    ...state,
    time: {
      delta: now -. state.time.timeNow,
      timeNow: now,
    },
  };
};
