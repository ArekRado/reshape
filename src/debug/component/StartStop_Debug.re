[@react.component]
let make = () => {
  let (editorState, editorDispatch) =
    React.useContext(Editor_Context.context);

  <Button_UI
    onClick={_ => editorDispatch(SetIsPlaying(!editorState.isPlaying))}>
    {React.string(editorState.isPlaying ? "Stop" : "Play")}
  </Button_UI>;
};
