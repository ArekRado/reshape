let runTests = () => {
  Test_Util.it("Should change time - start from 0 case", expect => {
    let state1 =
      Engine.runOneFrame(
        ~state=Engine.initialState,
        ~enableDraw=false,
        ~performanceNow=0.0,
        (),
      );

    expect(state1.time.timeNow).toBe(0.0);
    expect(state1.time.delta).toBe(0.0);

    let state2 =
      Engine.runOneFrame(
        ~state=state1,
        ~enableDraw=false,
        ~performanceNow=1000.0,
        (),
      );

    expect(state2.time.timeNow).toBe(1000.0);
    expect(state2.time.delta).toBe(1000.0);

    let state3 =
      Engine.runOneFrame(
        ~state=state2,
        ~enableDraw=false,
        ~performanceNow=1002.0,
        (),
      );

    expect(state3.time.timeNow).toBe(1002.0);
    expect(state3.time.delta).toBe(2.0);
  });

  Test_Util.it("Should change time - start from non 0 case", expect => {
    let state1 =
      Engine.runOneFrame(
        ~state=Engine.initialState,
        ~enableDraw=false,
        ~performanceNow=10.0,
        (),
      );

    expect(state1.time.timeNow).toBe(10.0);
    expect(state1.time.delta).toBe(10.0);

    let state2 =
      Engine.runOneFrame(
        ~state=state1,
        ~enableDraw=false,
        ~performanceNow=1000.0,
        (),
      );

    expect(state2.time.timeNow).toBe(1000.0);
    expect(state2.time.delta).toBe(990.0);

    let state3 =
      Engine.runOneFrame(
        ~state=state2,
        ~enableDraw=false,
        ~performanceNow=1002.0,
        (),
      );

    expect(state3.time.timeNow).toBe(1002.0);
    expect(state3.time.delta).toBe(2.0);
  });
};