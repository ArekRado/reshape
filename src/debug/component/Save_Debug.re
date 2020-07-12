[@react.component]
let make = (~state: Type.state) => {
  <Button_UI 
    onClick={(_) => SyncState.saveStateInLocalStorage(state)} 
  >
    {React.string("Save")}
  </Button_UI>
}