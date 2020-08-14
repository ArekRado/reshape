let _assert = (description, assertion: bool) =>
  if (assertion === false) {
    failwith("Assertion failed " ++ description);
  };

let it = (description, case) => {
  Js.log("  - " ++ description);
  case(_assert(description));
};

let describe = (description, case) => {
  Js.log("");
  Js.log("- " ++ description);
  Js.log("");

  case(it);
};
