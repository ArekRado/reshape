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

[@react.component]
let make = (~gameState: Type.state) => {
  let (_, dispatch) = React.useContext(Modal_Context.context);

  <>
    <Button_UI 
      onClick={(_) => dispatch(OpenModal("SaveState"))} 
    >
      {React.string("Save")}
    </Button_UI>
  </>
}