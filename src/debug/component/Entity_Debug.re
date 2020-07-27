[@react.component]
let make = (~entity: Type.entity, ~humanFriendlyEntity=true) => 
  <div title={entity} className="truncate">
    {React.string(humanFriendlyEntity ? Uuid_Util.humanFriendlyEntity(entity) : entity)}
  </div>