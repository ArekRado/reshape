let _assert = (assertion: bool) =>
  if (assertion === false) {
    Js.log("");
    Js.log("Assertion failed");
  };

let it = (description, case) => {
  Js.log("- " ++ description);
  case(_assert);
};

let test = (description, case) => {
  /* Js.log("- " ++ description); */
  case(assertion => {});
};