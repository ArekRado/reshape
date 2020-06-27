[@bs.module] external v4: unit => string = "uuid/v4";

let humanFriendlyEntity = entity => Js.String2.split(entity, "###")[0];
