[@react.component]
let make = (~initialState: Type.state) => {
  // let (state, setState) = React.useState(_ => initialState);

  let (gameState, dispatch) =
    React.useReducer(
      (state, action) => {
        let newState = switch (action) {
        | Type_Debug.SetState(state) => state;
        | Type_Debug.CreateEntity(entity) => Entity.create(~entity, ~state);
        | Type_Debug.CreateTransform(entity) => Transform_Component.create(~entity, ~state, ());        | Type_Debug.CreateSprite(entity) => Sprite_Component.create(~entity, ~state, ~src="", ());
        | Type_Debug.CreateFieldFloat(_) => state //FieldFloat_Component.create(~entity, ~state);
        | Type_Debug.CreateFieldInt(_) => state //FieldInt_Component.create(~entity, ~state);
        | Type_Debug.CreateFieldVector(_) => state //FieldVector_Component.create(~entity, ~state);
        | Type_Debug.CreateAnimationFloat(entity) => AnimationFloat_Component.create(
            ~entity,
            ~state,
            ~name=Uuid_Util.v4(),
            ~keyframes=[],
            ()
          );
        | Type_Debug.CreateAnimationVector(entity) => AnimationVector_Component.create(
            ~entity,
            ~state,
            ~name=Uuid_Util.v4(),
            ~keyframes=[],
            ()
          );
        | Type_Debug.CreateCollideBox(entity) => CollideBox_Component.create(
            ~entity,
            ~state,
            ~name=Uuid_Util.v4(),
            ~size=Vector_Util.create(1.0, 1.0),
            ()
          );
        | Type_Debug.CreateCollideCircle(entity) => CollideCircle_Component.create(
            ~entity,
            ~state,
            ~name=Uuid_Util.v4(),
            ~radius=1.0,
            ()
          );
        };

        SyncState.set(newState);

        newState;
      },
      initialState,
    );

  let (modalContext, setModalContext) = React.useReducer(
    Modal_Context.reducer,
    Modal_Context.initialState,
  )

  let (entity, setEntity) = React.useState(_ => "");
  let (isPlaying, setIsPlaying) = React.useState(_ => false);
  let isPlayingRef = React.useRef(false);
  isPlayingRef.current = isPlaying;

  React.useEffect1(() => {
    let id = Js.Global.setInterval(() => {
      if(isPlayingRef.current) {
        dispatch(Type_Debug.SetState(SyncState.get()));
      }
    }, 50);
    
    Some(() => {
      Js.Global.clearInterval(id);
    });
  }, [|isPlaying|]);

  // Sync once at the saart
  React.useEffect0(() => {
    SyncState.getStateFromLocalStorage()
      ->Type_Debug.SetState
      ->dispatch

    Some(() => {()});
  });

  Js.log(modalContext);

  <Modal_Context.Provider value={(modalContext, setModalContext)}>
    <div className="text-gray-500 bg-gray-900 w-full h-full flex">
      <div className="flex flex-col flex-1 justify-between py-2 pl-2 pr-1">
        <Save_Debug gameState />
        <StartStop_Debug isPlaying setIsPlaying />
        <CreateEntity_Debug dispatch/>
        <div className="flex flex-col flex-1 overflow-y-scroll mt-2">
          <EntityList_Debug gameState setEntity />
        </div>
        <Fps_Debug gameState/>
      </div>
      <div className="flex flex-col flex-1 overflow-y-scroll overflow-x-hidden py-2 pr-2 pl-1">
        {entity !== ""
          ? 
          <>
            <CreateComponent_Debug dispatch entity />
            <div className="mt-2"/>
            <ComponentList_Debug gameState entity /> 
          </>
          : React.string("Entity not selected")
        }
      </div>
      <Modal_Container_Debug />
    </div>
  </Modal_Context.Provider>;
}