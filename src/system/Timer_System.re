let update = (state: Type.state): Type.state => {
  let timerState = Belt.Map.String.map(state.timer, (timer) => {
    let newValue = timer.value +. state.delta;

    {
      ...timer,
      value: newValue > timer.maxValue ? 0.0 : newValue,
      isDone: newValue > timer.maxValue,
    }
  });

  {
    ...state,
    timer: timerState
  };
}