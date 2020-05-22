[%bs.raw {|require("./tailwind.css")|}];

let initialize = (initialState: Shared.state) => {
  ReactDOMRe.renderToElementWithId(<EntityList_Debug initialState={initialState} />, "debug");
}