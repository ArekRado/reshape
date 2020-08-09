// let getSaveSlots = () => {
//   let saveSlots = Dom.Storage.getItem("saveSlots", Dom.Storage.localStorage);

//   switch(saveSlots) {
//   | Some(saveSlots) => 
//     Json_Util.Parse.maybeArray(
//       array => Belt.Array.map(array, Json_Util.Parse.stringWithDefault("", _)), 
//       Js.Json.parseExn(saveSlots)
//     )
//   | None => [| |]
//   };
// };

[@react.component]
let make = () => {
  let (appState, _) = React.useContext(App_Context.context);
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  // let (saveSlots, _) = React.useState(_ => getSaveSlots());

  <Modal_UI 
    id="saveState"
    render={(_) => {
      <div>
        <Button_UI
          onClick={(_) => {
            SyncState.saveStateInLocalStorage(appState)
            modalDispatch(CloseModal("saveState"))
          }}
        >
          {React.string("Click to save")}
        </Button_UI>

        // {
        //   saveSlots
        //     ->Belt.Array.map(slot => 
        //       <Button_UI 
        //         key={slot}
        //         onClick={(_) => modalDispatch(CloseModal("saveState"))} 
        //       >
        //         {React.string("Save")}
        //       </Button_UI>
        //     )
        //     ->React.array
        // }
      </div>
    }}
  />
}