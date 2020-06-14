[@react.component]
let make = (~isPlaying, ~setIsPlaying) => {
  <Button_UI 
    onClick={(_) => setIsPlaying((_) => !isPlaying)}  
  >
    {React.string(isPlaying ? "Stop" : "Play")}
  </Button_UI>
}