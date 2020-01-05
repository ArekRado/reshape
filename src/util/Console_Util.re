/* type logData = 
| List(string)
| String(string)
| Int(int);

let log = (data:unit) => 
  switch (data) {
  | List(string) => Js.log(string)
  | _ => Js.log(data)
  } */