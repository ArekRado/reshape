let it = (description, case) => {
  case() === true
    ? Js.log("Passed - " ++ description) : Js.log("Error - " ++ description);
};