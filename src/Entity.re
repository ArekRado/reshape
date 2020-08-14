let generate = (debugName: string) => debugName ++ "###" ++ Uuid_Util.v4();

let create = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  entity: Belt.List.add(state.entity, entity),
};

let remove = (~entity: string, ~state: Type.state): Type.state => {
  let newState = {
    ...state,
    entity: Belt.List.keep(state.entity, item => item !== entity),
  };

  newState
  ->Transform_Component.remove(~entity, ~state=_)
  ->Sprite_Component.remove(~entity, ~state=_)
  ->Animation_Component.removeByEntity(~entity, ~state=_)
  ->CollideBox_Component.removeByEntity(~entity, ~state=_)
  ->CollideCircle_Component.removeByEntity(~entity, ~state=_);
};
