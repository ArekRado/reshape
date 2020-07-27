let initialState = Type.initialState;

type action = 
  | SetState(Type.state)

  | CreateEntity(Type.entity)
  | CreateTransform(Type.entity)
  | CreateSprite(Type.entity)
  | CreateFieldFloat(Type.entity)
  | CreateFieldInt(Type.entity)
  | CreateFieldVector(Type.entity)
  | CreateAnimationFloat(Type.entity)
  | CreateAnimationVector(Type.entity)
  | CreateCollideBox(Type.entity)
  | CreateCollideCircle(Type.entity)

  | RemoveEntity(Type.entity)
  | RemoveAnimationFloat(Type.entity)
  | RemoveAnimationVector(Type.entity)
  | RemoveCollideBox(Type.entity)
  | RemoveCollideCircle(Type.entity)
  | RemoveFieldFloat(Type.entity)

  | SetFieldFloatName(Type.entity, Type.entity)
  | SetFieldFloatValue(Type.entity, float)

let reducer = (state, action): Type.state => {
  let newState = switch (action) {
  | SetState(state) => state;
  | CreateEntity(entity) => Entity.create(~entity, ~state);
  | CreateTransform(entity) => Transform_Component.create(~entity, ~state, ());       
  | CreateSprite(entity) => Sprite_Component.create(~entity, ~state, ~src="");
  | CreateFieldFloat(entity) => FieldFloat_Component.create(
      ~entity,
      ~state,
      ~name=Uuid_Util.v4(),
      ~value=0.0
    );
  | CreateFieldInt(_) => state //FieldInt_Component.create(~entity, ~state);
  | CreateFieldVector(_) => state //FieldVector_Component.create(~entity, ~state);
  | CreateAnimationFloat(entity) => AnimationFloat_Component.create(
      ~entity,
      ~state,
      ~name=Uuid_Util.v4(),
      ~keyframes=[],
      ()
    );
  | CreateAnimationVector(entity) => AnimationVector_Component.create(
      ~entity,
      ~state,
      ~name=Uuid_Util.v4(),
      ~keyframes=[],
      ()
    );
  | CreateCollideBox(entity) => CollideBox_Component.create(
      ~entity,
      ~state,
      ~name=Uuid_Util.v4(),
      ~size=Vector_Util.create(1.0, 1.0),
      ()
    );
  | CreateCollideCircle(entity) => CollideCircle_Component.create(
      ~entity,
      ~state,
      ~name=Uuid_Util.v4(),
      ~radius=1.0,
      ()
    );
  | RemoveEntity(entity) => Entity.remove(
      ~entity,
      ~state,
    );
  | RemoveAnimationFloat(name) => AnimationFloat_Component.remove(~name, ~state);
  | RemoveAnimationVector(name) => AnimationVector_Component.remove(~name, ~state);
  | RemoveCollideBox(name) => CollideBox_Component.remove(~name, ~state);
  | RemoveCollideCircle(name) => CollideCircle_Component.remove(~name, ~state);
  | RemoveFieldFloat(name) => FieldFloat_Component.remove(~name, ~state);

  | SetFieldFloatName(name, newName) => {
      ...state,
      fieldFloat: switch(Belt.Map.String.get(state.fieldFloat, name)) {
      | Some(fieldFloat) => 
        Belt.Map.String.set(state.fieldFloat, newName, fieldFloat)
        ->Belt.Map.String.remove(_, name)
      | None => state.fieldFloat
      }
    };
  | SetFieldFloatValue(name, value) => {
      ...state,
      fieldFloat: switch(Belt.Map.String.get(state.fieldFloat, name)) {
      | Some(fieldFloat) => Belt.Map.String.set(state.fieldFloat, name, {
        ...fieldFloat,
        value,
      });
      | None => state.fieldFloat
      }
    };
  };

  SyncState.set(newState);

  newState;
};

type dispatch = action => unit;
type contextType = (Type.state, dispatch);

let contextValue: contextType = (initialState, _ => ignore());
let context = React.createContext(contextValue);

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}

  let make = React.Context.provider(context);
};