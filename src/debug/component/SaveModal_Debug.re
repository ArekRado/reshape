// [@react.component]
// let make = (~state: Type.state) => {

//   <>
//     <Button_UI 
//       onClick={(_) => SyncState.saveStateInLocalStorage(state)} 
//     >
//       {React.string("Save")}
//     </Button_UI>
    
//   </>
// }

let getSaveSlots = () => {
  let saveSlots = Dom.Storage.getItem("saveSlots", Dom.Storage.localStorage);

  switch(saveSlots) {
  | Some(saveSlots) => 
    Json_Util.Parse.maybeArray(
      array => Belt.Array.map(array, Json_Util.Parse.stringWithDefault("", _)), 
      Js.Json.parseExn(saveSlots)
    )
  | None => [| |]
  };
};

[@react.component]
let make = () => {
  let (_, modalDispatch) = React.useContext(Modal_Context.context);

  let (saveSlots, _) = React.useState(_ => getSaveSlots());

  <Modal_UI 
    name="SaveState"
    render={(modal) => {
      <div>
        <div> {React.string("e")}</div>

        // {
        //   saveSlots
        //     ->Belt.Array.map(slot => 
        //       <Button_UI 
        //         key={slot}
        //         onClick={(_) => modalDispatch(CloseModal("SaveState"))} 
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