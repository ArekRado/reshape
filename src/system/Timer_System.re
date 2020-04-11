let update = (state: Type.state): Type.state => {
  // let timerState =
  //   Belt.Map.String.map(
  //     game.timer,
  //     timer => {
  //       let newValue = timer.value +. game.delta;

  //       {
  //         ...timer,
  //         value: newValue > timer.maxValue ? 0.0 : newValue,
  //         isDone: newValue > timer.maxValue,
  //       };
  //     },
  //   );

    {
      game: state.game,
        // timer: timerState,
      engine: state.engine
    }
};