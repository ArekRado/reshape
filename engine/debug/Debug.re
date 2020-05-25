[@bs.val] external nodeEnv : string = "process.env.NODE_ENV";

if(nodeEnv !== "test") {
  [%bs.raw {|require("./tailwind.css")|}];
}

let initialize = (initialState: Shared.state) => {
  ReactDOMRe.renderToElementWithId(<EntityList_Debug initialState={initialState} />, "debug");
}