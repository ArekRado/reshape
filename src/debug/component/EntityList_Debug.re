[@react.component]
let make = (
  ~gameState: Type.state,
  ~setEntity
) => 
  <>  
    <div className="text-white mb-3">
      {React.string("Entity")}
    </div>
    {
      gameState.entity
      ->Belt.List.map(entity =>
          <button 
            key={entity} 
            className="hover:text-gray-800 hover:bg-gray-400 text-left"
            onClick={(_) => setEntity((_) => entity)}
            title={entity}
          >
            {entity->Uuid_Util.humanFriendlyEntity->React.string}
          </button>
        )
      ->(items => React.array(Array.of_list(items)))
    }
  </>