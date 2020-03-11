let generate = () => Uuid_Util.v4();

let create = (entity: string, engine: Shared.state) : Shared.state => {
  ...engine,
  entity: Belt.List.add(engine.entity, entity),
};