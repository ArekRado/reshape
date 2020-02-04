let create = (
  ~rotation = 0.0,
  ~localRotation = 0.0,
  ~scale = Vector_Util.zero(),
  ~localScale = Vector_Util.zero(),
  ~position = Vector_Util.zero(),
  ~localPosition = Vector_Util.zero(),
) : Shared.transform => {
  rotation,
  localRotation,
  scale,
  localScale,
  position,
  localPosition,
};