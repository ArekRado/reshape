let create = (~value=0.0, maxValue) : Type.timer => {
  value,
  maxValue,
  isDone: false,
};
