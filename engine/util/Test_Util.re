type compareResult('a) = {
  result: bool,
  a: 'a,
  b: 'a,
};

let toBe = (a: 'a, b: 'a) => {
  result: switch(a) {
  | float => a === b
  | int => Vector_Util.isEqual(a,b)
  /* | String.t(xd) => true */
  /* | Vector_Util.t => Vector_Util.isEqual(a,b) */
  },
  a,
  b,
};
let notToBe = (a: 'a, b: 'a) => {result: a !== b, a, b};

let logger = data =>
  if (data.result === false) {
    Js.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    Js.log("Error");
    Js.log("Expected:");
    Js.log(data.b);
    Js.log("Received:");
    Js.log(data.a);
    Js.log("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  };

type compare('a) = {
  toBe: 'a => unit,
  notToBe: 'a => unit,
};

let expect = a => {
  {toBe: b => logger(toBe(a, b)), notToBe: b => logger(notToBe(a, b))};
};

let it = (description, case) => {
  Js.log("- " ++ description);
  case(expect);
};