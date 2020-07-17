[@bs.val] external nodeEnv : string = "process.env.NODE_ENV";

if(nodeEnv !== "test") {
  [%bs.raw {|require("./tailwind.css")|}];
}

let initialize = () => {
  switch (Webapi.Dom.Document.querySelector("body", Webapi.Dom.document)) {
    | Some(body) => {
      let container = Webapi.Dom.Document.createElement("div", Webapi.Dom.document);
      Webapi.Dom.Element.setAttribute("id", "engine-debug", container);
      Webapi.Dom.Element.appendChild(container, body);
    }
    | None => ()
  };

  ReactDOMRe.renderToElementWithId(<App_Debug />, "engine-debug");
}
