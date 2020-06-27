let generate = (debugName:string) => debugName ++ "###" ++ Uuid_Util.v4();

let create = (~entity: string, ~state: Type.state): Type.state => {
  ...state,
  entity: Belt.List.add(state.entity, entity),
};