let _assert = (assertion: bool) =>
  if (assertion === false) {
    Js.log("");
    Js.log("--> Assertion failed <--");
  };

let it = (description, case) => {
  Js.log("  - " ++ description);
  case(_assert);
};

let describe = (description, case) => {
  Js.log("");
  Js.log("- " ++ description);
  Js.log("");

  case(it);
};