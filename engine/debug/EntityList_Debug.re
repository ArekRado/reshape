[@react.component]
let make = (~state: Shared.state) =>
  <div>
    <h4>{React.string("entity:")}</h4>
    <ul> 
        {
        state.entity
        ->Belt.List.map(entity =>
            <li key={entity}>{React.string(entity)}</li>
          )
        ->(items => React.array(Array.of_list(items)))
      }
    </ul>
  </div>;