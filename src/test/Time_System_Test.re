let runTests = () => {
  Test_Util.describe("Time_System", it => {
    it("Should change time - start from 0 case", _assert => {
      let state1 =
        Engine.runOneFrame(
          ~state=Type.initialState,
          ~enableDraw=false,
          ~performanceNow=0.0,
          (),
        );

      _assert(state1.time.timeNow === 0.0);
      _assert(state1.time.delta === 0.0);

      let state2 =
        Engine.runOneFrame(
          ~state=state1,
          ~enableDraw=false,
          ~performanceNow=1000.0,
          (),
        );

      _assert(state2.time.timeNow === 1000.0);
      _assert(state2.time.delta === 1000.0);

      let state3 =
        Engine.runOneFrame(
          ~state=state2,
          ~enableDraw=false,
          ~performanceNow=1002.0,
          (),
        );

      _assert(state3.time.timeNow === 1002.0);
      _assert(state3.time.delta === 2.0);
    });

    it("Should change time - start from non 0 case", _assert => {
      let state1 =
        Engine.runOneFrame(
          ~state=Type.initialState,
          ~enableDraw=false,
          ~performanceNow=10.0,
          (),
        );

      _assert(state1.time.timeNow === 10.0);
      _assert(state1.time.delta === 10.0);

      let state2 =
        Engine.runOneFrame(
          ~state=state1,
          ~enableDraw=false,
          ~performanceNow=1000.0,
          (),
        );

      _assert(state2.time.timeNow === 1000.0);
      _assert(state2.time.delta === 990.0);

      let state3 =
        Engine.runOneFrame(
          ~state=state2,
          ~enableDraw=false,
          ~performanceNow=1002.0,
          (),
        );

      _assert(state3.time.timeNow === 1002.0);
      _assert(state3.time.delta === 2.0);
    });
  });
};