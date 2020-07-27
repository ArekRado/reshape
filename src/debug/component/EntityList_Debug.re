[@react.component]
let make = () => {
  let (_, editorDispatch) = React.useContext(Editor_Context.context);
  let (appState, _) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  <>  
    <div className="text-white mb-3">
      {React.string("Entity")}
    </div>
    {
      appState.entity
      ->Belt.List.map(entity =>
          <div
            key={entity}  
            className="flex justify-between"
            title={entity}
          >
            <Button_UI 
              
              onClick={(_) => editorDispatch(SelectEntity(entity))}
              className="flex-1 text-left"
            >
              {entity->Uuid_Util.humanFriendlyEntity->React.string}
            </Button_UI>

            <Button_UI 
              
              onClick={(_) => {
                modalDispatch(OpenModal("removeEntity", Entity(entity)))
              }}
            >
              {React.string("x")}
            </Button_UI>
          </div>
        )
      ->(items => React.array(Array.of_list(items)))
    }
  </>
};