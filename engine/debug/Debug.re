let initialize = (state: Shared.state) => {
  ReactDOMRe.renderToElementWithId(<EntityList_Debug state={state} />, "debug");
}