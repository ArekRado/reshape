type size =
  | Xs
  | Sm
  | Md
  | Lg;

[@react.component]
let make = (~onClick, ~children, ~size=Xs, ~className="") => {
  let btnSize =
    switch (size) {
    | Xs => "p-1"
    | Sm => "p-2"
    | Md => "p-3"
    | Lg => "p-4"
    };

  <button
    type_="button"
    onClick
    className={
      btnSize
      ++ " border border-gray-600 bg-gray-800 hover:bg-gray-700"
      ++ " "
      ++ className
    }>
    children
  </button>;
};
