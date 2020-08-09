let initialState = Type.initialState;

type action = 
  | SetState(Type.state)

  | CreateEntity(Type.entity)
  | CreateTransform(Type.entity)
  | CreateSprite(Type.entity)
  | CreateFieldFloat(Type.entity)
  | CreateFieldInt(Type.entity)
  | CreateFieldVector(Type.entity)
  | CreateAnimation(Type.entity)
  | CreateCollideBox(Type.entity)
  | CreateCollideCircle(Type.entity)

  | RemoveEntity(Type.entity)
  | RemoveAnimation(Type.entity)
  | RemoveCollideBox(Type.entity)
  | RemoveCollideCircle(Type.entity)
  | RemoveFieldFloat(Type.entity)
  | RemoveSprite(Type.entity)
  | RemoveTransform(Type.entity)

  | SetFieldFloatName(Type.entity, Type.entity)
  | SetFieldFloatValue(Type.entity, float)
  // Sprite
  | SetSpriteSrc(Type.entity, Type.spriteSrc)
  // Transform
  | SetTransformRotation(Type.entity, Type.rotation)
  | SetTransformLocalRotation(Type.entity, Type.rotation)
  | SetTransformScale(Type.entity, Vector_Util.t)
  | SetTransformLocalScale(Type.entity, Vector_Util.t)
  | SetTransformPosition(Type.entity, Vector_Util.t)
  | SetTransformLocalPosition(Type.entity, Vector_Util.t)
  | SetAnimationComponent(Type.entity, Type.animatedComponent)
  // | SetTransformParent(Type.entity, Type.entity)

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
  | CreateAnimation(entity) => Animation_Component.create(
      ~component=Type.FieldFloat(""),
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
  | RemoveAnimation(name) => Animation_Component.remove(~name, ~state);
  | RemoveCollideBox(name) => CollideBox_Component.remove(~name, ~state);
  | RemoveCollideCircle(name) => CollideCircle_Component.remove(~name, ~state);
  | RemoveFieldFloat(name) => FieldFloat_Component.remove(~name, ~state);
  | RemoveSprite(entity) => Sprite_Component.remove(~entity, ~state);
  | RemoveTransform(entity) => Transform_Component.remove(~entity, ~state);

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
  | SetSpriteSrc(entity, src) => Sprite_Component.setSrc(~entity, ~src, ~state);

  // Transform

  | SetTransformRotation(entity, rotation) => 
    Transform_Component.setRotation(
      ~entity, 
      ~state, 
      ~rotation
    );
  | SetTransformLocalRotation(entity, localRotation) => 
    Transform_Component.setLocalRotation(
      ~entity, 
      ~state, 
      ~localRotation
    );
  | SetTransformScale(entity, scale) => 
    Transform_Component.setScale(
      ~entity, 
      ~state, 
      ~scale
    );
  | SetTransformLocalScale(entity, localScale) => 
    Transform_Component.setLocalScale(
      ~entity, 
      ~state, 
      ~localScale
    );
  | SetTransformPosition(entity, position) => 
    Transform_Component.setPosition(
      ~entity, 
      ~state, 
      ~position
    );
  | SetTransformLocalPosition(entity, localPosition) => 
    Transform_Component.setLocalPosition(
      ~entity, 
      ~state, 
      ~localPosition
    );
  | SetAnimationComponent(name, component) => 
    Animation_Component.setComponent(
      ~name,
      ~component,
      ~state,
    )
  // | SetTransformParent(entity, parentEntity) => Transform_Component(~entity, ~state, ~rotation);
  };

  SyncState.set(newState, Game);

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