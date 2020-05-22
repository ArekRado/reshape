let generate = (debugName:string) => debugName ++ "###" ++ Uuid_Util.v4();

let create = (~entity: string, ~state: Shared.state): Shared.state => {
  ...state,
  entity: Belt.List.add(state.entity, entity),
};