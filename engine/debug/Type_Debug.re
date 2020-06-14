type entity = string;

type action = 
  | SetState(Shared.state)
  | CreateEntity(entity)
  | CreateTransform(entity)
  | CreateSprite(entity)
  | CreateFieldFloat(entity)
  | CreateFieldInt(entity)
  | CreateFieldVector(entity)
  | CreateAnimationFloat(entity)
  | CreateAnimationVector(entity)
  | CreateCollideBox(entity)
  | CreateCollideCircle(entity)