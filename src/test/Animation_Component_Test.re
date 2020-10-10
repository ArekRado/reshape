let runTests = () => {
  Test_Util.describe("Animation_Component", it => {
    let tick = (performanceNow, state) =>
      ReShape.runOneFrame(~state, ~enableDraw=false, ~performanceNow, ());

    let entity = "-entity-";
    let animationName = "-animationName-";
    let fieldFloatName = "-fieldFloat-";

    let getAnimation = (state: Type.state) =>
      switch (Animation_Component.get(~state, ~name=animationName, ~entity)) {
      | Some(animation) => animation
      | None => {
        Js.log("Can't find animation " ++ animationName);
        failwith("Can't find animation " ++ animationName);
      }
      };

    it("create", _assert => {
      let newState = Animation_Component.create(
        ~name=animationName,
        ~isPlaying=true,
        ~keyframes=[],
        ~entity,
        ~state=Type.initialState,
        ~component=FieldFloat(entity, fieldFloatName),
        ()
      );

      _assert(getAnimation(newState).entity === entity);
      _assert(getAnimation(newState).name === animationName);
      _assert(getAnimation(newState).isPlaying === true);
      _assert(getAnimation(newState).isFinished === false);
      _assert(getAnimation(newState).currentTime === 0.0);
      // _assert(getAnimation(newState).component === FieldFloat(entity, fieldFloatName));
      _assert(getAnimation(newState).keyframes === []);
      _assert(getAnimation(newState).wrapMode === Once);

      ();
    });

    it("remove", _assert => {
      let stateWithAnimation = Animation_Component.create(
        ~name=animationName,
        ~isPlaying=true,
        ~keyframes=[],
        ~entity,
        ~state=Type.initialState,
        ~component=FieldFloat(entity, fieldFloatName),
        ()
      );

      _assert(Belt.Map.String.size(stateWithAnimation.animation) === 1);

      let stateWithoutAnimation = Animation_Component.remove(
        ~name=animationName,
        ~entity,
        ~state=stateWithAnimation,
      );

      _assert(Belt.Map.String.size(stateWithoutAnimation.animation) === 0);

      ();
    });

    it("removeByEntity", _assert => {
      let stateWithAnimation = Animation_Component.create(
        ~name=animationName,
        ~isPlaying=true,
        ~keyframes=[],
        ~entity,
        ~state=Type.initialState,
        ~component=FieldFloat(entity, fieldFloatName),
        ()
      );

      _assert(Belt.Map.String.size(stateWithAnimation.animation) === 1);

      let stateWithoutAnimation = Animation_Component.removeByEntity(
        ~entity,
        ~state=stateWithAnimation,
      );

      _assert(Belt.Map.String.size(stateWithoutAnimation.animation) === 0);

      ();
    });

    it("set", _assert => {
      let state = Animation_Component.create(
        ~name=animationName,
        ~isPlaying=true,
        ~keyframes=[],
        ~entity,
        ~state=Type.initialState,
        ~component=FieldFloat(entity, fieldFloatName),
        ()
      );

      let newState = Animation_Component.set(
        ~entity,
        ~name=animationName,
        ~state,
        ~animation={
          ...getAnimation(state),
          isPlaying: false,
          isFinished: true,
          currentTime: -99.9,
          wrapMode: Loop,
        },
      );

      _assert(getAnimation(newState).entity === entity);
      _assert(getAnimation(newState).name === animationName);
      _assert(getAnimation(newState).isPlaying === false);
      _assert(getAnimation(newState).isFinished === true);
      _assert(getAnimation(newState).currentTime === -99.9);
      _assert(getAnimation(newState).keyframes === []);
      _assert(getAnimation(newState).wrapMode === Loop);


      // let test = Belt.Map.String.empty
      // ->Belt.Map.String.set(_, "1", "11")
      // ->Belt.Map.String.set(_, "2", "22")
      // ->Belt.Map.String.set(_, "3", "33")
      // ->Belt.Map.String.set(_, "4", "44")
      // ->Belt.Map.String.set(_, "5", "55")
      // ->Belt.Map.String.set(_, "6", "66")
      // ->Belt.Map.String.set(_, "7", "77")
      // ->Belt.Map.String.reduce(_, "", (acc, key, value) => {

      //   acc ++ key ++ value
      // });

      // Js.log(test);

      ();
    });
  });
};
