module Parse = {
  let maybeString = (map, json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONString(value) => map(Some(value))
      | _ => map(None)
    };

  let maybeFloat = (map, json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONNumber(value) => map(Some(value))
      | _ => map(None)
    };

  let maybeBool = (map, json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONTrue => map(Some(true))
      | Js.Json.JSONFalse => map(Some(false))
      | _ => map(None)
    };

  let maybeArray = (map, json) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONArray(value) => map(value)
      | _ => failwith("Expected an array")
    };

  let maybeProperty = (property, obj) =>
    switch (Js.Dict.get(obj, property)) {
    | Some(value) => value
    | _ => failwith("Property: " ++ property ++ " doesn't exist")
  };

  let maybeObject = (map, json) => 
    switch (Js.Json.classify(json)) {
    | Js.Json.JSONObject(value) => map(Some(value))
    | _ => map(None)
    };

  // UTILS

  let stringWithDefault = default => maybeString((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let floatWithDefault = default => maybeFloat((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let boolWithDefault = default => maybeBool((maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  // let vectorWithDefault = default => maybeVector((maybeValue) => 
  //   switch (maybeValue) {
  //   | Some(value) => value
  //   | None => default
  //   }
  // );

  let getArrayWithDefault = (default, array, index) => 
    switch (Belt.Array.get(array, index)) {
    | Some(value) => value
    | None => default
    };

  let maybeVector = maybeArray(array => {
    let floatArray = Belt.Array.map(array, floatWithDefault(0.0));
    
    (
      getArrayWithDefault(0.0, floatArray, 0),
      getArrayWithDefault(0.0, floatArray, 1)
    );
  });

  let collisions = maybeArray(array =>
    array
      ->Belt.List.fromArray
      ->Belt.List.map(value =>
        maybeArray(collision => {

          let collisionType = switch (Belt.Array.get(collision, 0)) {
          | Some(value) => stringWithDefault("Circle", value)
          | None => "Circle"
          };

          let collisionValue = switch (Belt.Array.get(collision, 1)) {
          | Some(value) => stringWithDefault("", value)
          | None => ""
          };

          switch(collisionType) {
          | "Box" => Type.Box(collisionValue)
          | "Circle" => Type.Circle(collisionValue)
          | _ => Type.Circle(collisionValue)
          };
        }, value)
      )
    );
  
  let wrapMode = wrapMode => 
    switch(wrapMode) {
    | "Once" => Type.Once;
    | "Loop" => Type.Loop;
    | "PingPong" => Type.PingPong;
    | "ClampForever" => Type.ClampForever;
    | _ => Type.Once;
    }
  
  let timingFunction = timingFunction => 
    switch(timingFunction) {
    | "Linear" => Type.Linear;
    | "EaseInQuad" => Type.EaseInQuad;
    | "EaseOutQuad" => Type.EaseOutQuad;
    | "EaseInOutQuad" => Type.EaseInOutQuad;
    | "EaseInCubic" => Type.EaseInCubic;
    | "EaseOutCubic" => Type.EaseOutCubic;
    | "EaseInOutCubic" => Type.EaseInOutCubic;
    | "EaseInQuart" => Type.EaseInQuart;
    | "EaseOutQuart" => Type.EaseOutQuart;
    | "EaseInOutQuart" => Type.EaseInOutQuart;
    | "EaseInQuint" => Type.EaseInQuint;
    | "EaseOutQuint" => Type.EaseOutQuint;
    | "EaseInOutQuint" => Type.EaseInOutQuint;
    | "CubicBezier" => Type.CubicBezier(0.0, 0.0, 0.0, 0.0); // todo
    | _ => Type.Linear;
    }

  let dictToMapString = (map, dict) =>
    dict
      |> maybeObject(dict => 
        switch(dict) {
        | Some(dict) =>
          dict
          ->Js.Dict.entries
          ->Belt.Map.String.fromArray
          ->Belt.Map.String.reduce(
            Belt.Map.String.empty,
            (acc, key, value) => {
              let maybeItem = maybeObject(value => 
                switch (value) {
                | Some(value) => Some(map(value));
                | None => None;
              }, value);

              switch(maybeItem) {
              | Some(item) => Belt.Map.String.set(acc, key, item);
              | None => acc;
              }
            }
          )
        | None => Belt.Map.String.empty
        }
      );

    let someState = (stateObj): Type.state => {
      entity: stateObj
        |> maybeProperty("entity")
        |> maybeArray(array => 
          array
            ->Belt.List.fromArray
            ->Belt.List.map(stringWithDefault("", _))
        ),
      mouseButtons: stateObj
        |> maybeProperty("mouseButtons")
        |> floatWithDefault(0.0)
        |> Belt.Float.toInt,
      mousePosition: stateObj
        |> maybeProperty("mousePosition")
        |> maybeVector,
      time: stateObj 
        |> maybeProperty("time")
        |> maybeObject(timeObj: Type.time =>
          switch (timeObj) {
          | Some(timeObj) => {
              timeNow: timeObj
                |> maybeProperty("timeNow") 
                |> floatWithDefault(0.0),
              delta: timeObj
                |> maybeProperty("delta") 
                |> floatWithDefault(0.0),
            }
          | None => Type.initialState.time;
        }),
      isDebugInitialized: stateObj
        |> maybeProperty("isDebugInitialized")
        |> boolWithDefault(false),
      transform: stateObj
        |> maybeProperty("transform")
        |> dictToMapString((transform): Type.transform => {
          rotation: transform
            |> maybeProperty("rotation")
            |> floatWithDefault(0.0),
          localRotation: transform
            |> maybeProperty("localRotation")
            |> floatWithDefault(0.0),
          scale: transform
            |> maybeProperty("scale")
            |> maybeVector,
          localScale: transform
            |> maybeProperty("localScale")
            |> maybeVector,
          position: transform
            |> maybeProperty("position")
            |> maybeVector,
          localPosition: transform
            |> maybeProperty("localPosition")
            |> maybeVector,
          parent: transform
            |> maybeProperty("parent")
            |> maybeString(parent =>
              switch(parent) {
                | Some(parent) => Some(parent)
                | None => None
              }
            ),
        }),
      sprite: stateObj
        |> maybeProperty("sprite")
        |> dictToMapString((sprite): Type.sprite => {
          src: sprite
            |> maybeProperty("parent")
            |> stringWithDefault(""),
        }),
      animationFloat: stateObj
        |> maybeProperty("animationFloat")
        |> dictToMapString((animationFloat): Type.animation(float) => {
          entity: animationFloat
            |> maybeProperty("entity")
            |> stringWithDefault(""),
          name: animationFloat
            |> maybeProperty("name")
            |> stringWithDefault(""),
          isPlaying: animationFloat
            |> maybeProperty("isPlaying")
            |> boolWithDefault(false),
          isFinished: animationFloat
            |> maybeProperty("isFinished")
            |> boolWithDefault(false),
          currentTime: animationFloat
            |> maybeProperty("currentTime")
            |> floatWithDefault(0.0),
          value: animationFloat
            |> maybeProperty("value")
            |> floatWithDefault(0.0),
          wrapMode: animationFloat
            |> maybeProperty("wrapMode")
            |> maybeString(value =>
              switch(value) {
                | Some(value) => wrapMode(value)
                | None => Type.Once
              }
            ),
          keyframes: animationFloat
            |> maybeProperty("keyframes")
            |> maybeArray(array =>
              array
                ->Belt.List.fromArray
                ->Belt.List.map(
                    maybeObject(keyframe: Type.keyframe(float) =>
                    switch (keyframe) {
                    | Some(keyframe) => {
                      duration: keyframe
                        |> maybeProperty("duration")
                        |> floatWithDefault(0.0),
                      timingFunction: keyframe
                        |> maybeProperty("timingFunction")
                        |> maybeString(value =>
                          switch(value) {
                            | Some(value) => timingFunction(value)
                            | None => Type.Linear
                          }
                        ),
                      valueRange: keyframe
                        |> maybeProperty("valueRange")
                        |> maybeVector,
                      }
                    | None => {
                        duration: 0.0,
                        timingFunction: Type.Linear,
                        valueRange: (0.0, 0.0),
                      };
                    }
                  )
                )
              )
        }),
      animationVector: stateObj
        |> maybeProperty("animationVector")
        |> dictToMapString((animationVector): Type.animation(Vector_Util.t) => {
          entity: animationVector
            |> maybeProperty("entity")
            |> stringWithDefault(""),
          name: animationVector
            |> maybeProperty("name")
            |> stringWithDefault(""),
          isPlaying: animationVector
            |> maybeProperty("isPlaying")
            |> boolWithDefault(false),
          isFinished: animationVector
            |> maybeProperty("isFinished")
            |> boolWithDefault(false),
          currentTime: animationVector
            |> maybeProperty("currentTime")
            |> floatWithDefault(0.0),
          value: animationVector
            |> maybeProperty("value")
            |> maybeVector,
          wrapMode: animationVector
            |> maybeProperty("wrapMode")
            |> maybeString(value =>
              switch(value) {
                | Some(value) => wrapMode(value)
                | None => Type.Once
              }
            ),
          keyframes: animationVector
            |> maybeProperty("keyframes")
            |> maybeArray(array =>
              array
                ->Belt.List.fromArray
                ->Belt.List.map(
                    maybeObject(keyframe: Type.keyframe(Vector_Util.t) =>
                    switch (keyframe) {
                    | Some(keyframe) => {
                      duration: keyframe
                        |> maybeProperty("duration")
                        |> floatWithDefault(0.0),
                      timingFunction: keyframe
                        |> maybeProperty("timingFunction")
                        |> maybeString(value =>
                          switch(value) {
                            | Some(value) => timingFunction(value)
                            | None => Type.Linear
                          }
                        ),
                      valueRange: keyframe
                        |> maybeProperty("valueRange")
                        |> maybeArray(array => {
                          let from = switch (Belt.Array.get(array, 0)) {
                          | Some(value) => maybeVector(value);
                          | None => Vector_Util.zero;
                          };

                          let to_ = switch (Belt.Array.get(array, 1)) {
                          | Some(value) => maybeVector(value);
                          | None => Vector_Util.zero;
                          };

                          (from, to_);
                        }),
                      }
                    | None => {
                        duration: 0.0,
                        timingFunction: Type.Linear,
                        valueRange: (Vector_Util.zero, Vector_Util.zero),
                      };
                    }
                  )
                )
              )
        }),
      collideBox: stateObj
        |> maybeProperty("collideBox")
        |> dictToMapString((collideBox): Type.collideBox => {
          entity: collideBox
            |> maybeProperty("entity")
            |> stringWithDefault(""),
          size: collideBox
            |> maybeProperty("size")
            |> maybeVector,
          position: collideBox
            |> maybeProperty("position")
            |> maybeVector,
          collisions: collideBox
            |> maybeProperty("collisions")
            |> collisions
        }),
      collideCircle: stateObj
        |> maybeProperty("collideBox")
        |> dictToMapString((collideCircle): Type.collideCircle => {
          entity: collideCircle
            |> maybeProperty("entity")
            |> stringWithDefault(""),
          radius: collideCircle
            |> maybeProperty("radius")
            |> floatWithDefault(0.0),
          position: collideCircle
            |> maybeProperty("position")
            |> maybeVector,
          collisions: collideCircle
            |> maybeProperty("collisions")
            |> collisions
        }),
  };

  let state =
    maybeObject((stateObj): Type.state => 
      switch (stateObj) {
      | Some(stateObj) => someState(stateObj)
      | None => Type.initialState
    })
};

module Stringify = {
  let vector = ((x, y)) => Js.Json.numberArray([| x, y |]);

  let collisions = (collisions: Belt.List.t(Type.collideType)) => 
    Belt.List.map(collisions, collision => switch(collision) {
      | Box(entity) => Js.Json.stringArray([| "Box", entity |])
      | Circle(entity) => Js.Json.stringArray([| "Circle", entity |])
    })
    ->Array.of_list
    ->Js.Json.array;

  let timingFunction = (timingFunction: Type.timingFunction) => {
    let x = switch(timingFunction) {
    | Linear => "Linear"
    | EaseInQuad => "EaseInQuad"
    | EaseOutQuad => "EaseOutQuad"
    | EaseInOutQuad => "EaseInOutQuad"
    | EaseInCubic => "EaseInCubic"
    | EaseOutCubic => "EaseOutCubic"
    | EaseInOutCubic => "EaseInOutCubic"
    | EaseInQuart => "EaseInQuart"
    | EaseOutQuart => "EaseOutQuart"
    | EaseInOutQuart => "EaseInOutQuart"
    | EaseInQuint => "EaseInQuint"
    | EaseOutQuint => "EaseOutQuint"
    | EaseInOutQuint => "EaseInOutQuint"
    | CubicBezier(_, _, _, _) => "CubicBezier" // todo
    };

    Js.Json.string(x);
  }

  let entity = entity =>
    entity
      ->Belt.List.toArray
      ->Js.Json.stringArray

  let transform = transform => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(transform, (entity, (x: Type.transform)) => {
        let transformDict = Js.Dict.empty();

        Js.Dict.set(transformDict, "rotation", Js.Json.number(x.rotation));
        Js.Dict.set(transformDict, "localRotation", Js.Json.number(x.localRotation));
        Js.Dict.set(transformDict, "scale", vector(x.scale));
        Js.Dict.set(transformDict, "localScale", vector(x.localScale));
        Js.Dict.set(transformDict, "position", vector(x.position));
        Js.Dict.set(transformDict, "localPosition", vector(x.localPosition));

        switch(x.parent) {
          | Some(parent) => Js.Dict.set(transformDict, "parent", Js.Json.string(parent));
          | None =>  Js.Dict.set(transformDict, "parent", Js.Json.null);
        }

        Js.Dict.set(dict, entity, Js.Json.object_(transformDict));
      })
    );

    Js.Json.object_(dict)
  };

  let animationFloat = animationFloat => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(animationFloat, (entity, x: Type.animation(float)) => {
        let animationDict = Js.Dict.empty();

        Js.Dict.set(animationDict, "entity", Js.Json.string(x.entity));
        Js.Dict.set(animationDict, "name", Js.Json.string(x.name));
        Js.Dict.set(animationDict, "isPlaying", Js.Json.boolean(x.isPlaying));
        Js.Dict.set(animationDict, "isFinished", Js.Json.boolean(x.isFinished));
        Js.Dict.set(animationDict, "currentTime", Js.Json.number(x.currentTime));
        Js.Dict.set(animationDict, "value", Js.Json.number(x.value));
        Js.Dict.set(
          animationDict, 
          "wrapMode", 
          Js.Json.string(switch(x.wrapMode) {
          | Once => "Once"
          | Loop => "Loop"
          | PingPong => "PingPong"
          | ClampForever => "ClampForever"
          })
        );

        Js.Dict.set(animationDict, "keyframes", Js.Json.objectArray(
          Belt.List.map(x.keyframes, keyframe => {
            let keyframeDict = Js.Dict.empty();

            Js.Dict.set(keyframeDict, "duration", Js.Json.number(keyframe.duration));
            Js.Dict.set(keyframeDict, "timingFunction", timingFunction(keyframe.timingFunction));
            Js.Dict.set(keyframeDict, "valueRange", vector(keyframe.valueRange));

            keyframeDict;
          })
          ->Array.of_list
        ));

        Js.Dict.set(dict, entity, Js.Json.object_(animationDict));
      })
    );

    Js.Json.object_(dict)
  };

  let animationVector = animationVector => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(animationVector, (entity, x: Type.animation(Type.vector)) => {
        let animationDict = Js.Dict.empty();

        Js.Dict.set(animationDict, "entity", Js.Json.string(x.entity));
        Js.Dict.set(animationDict, "name", Js.Json.string(x.name));
        Js.Dict.set(animationDict, "isPlaying", Js.Json.boolean(x.isPlaying));
        Js.Dict.set(animationDict, "isFinished", Js.Json.boolean(x.isFinished));
        Js.Dict.set(animationDict, "currentTime", Js.Json.number(x.currentTime));
        Js.Dict.set(animationDict, "value", vector(x.value));
        Js.Dict.set(
          animationDict, 
          "wrapMode", 
          Js.Json.string(switch(x.wrapMode) {
          | Once => "Once"
          | Loop => "Loop"
          | PingPong => "PingPong"
          | ClampForever => "ClampForever"
          })
        );

        Js.Dict.set(animationDict, "keyframes", Js.Json.objectArray(
          Belt.List.map(x.keyframes, keyframe => {
            let (v1, v2) = keyframe.valueRange;
            let keyframeDict = Js.Dict.empty();

            Js.Dict.set(keyframeDict, "duration", Js.Json.number(keyframe.duration));
            Js.Dict.set(keyframeDict, "timingFunction", timingFunction(keyframe.timingFunction));
            Js.Dict.set(
              keyframeDict, 
              "valueRange", 
              Js.Json.array([| vector(v1), vector(v2) |])
            );

            keyframeDict;
          })
          ->Array.of_list
        ));

        Js.Dict.set(dict, entity, Js.Json.object_(animationDict));
      })
    );

    Js.Json.object_(dict)
  };

  let sprite = (sprite) => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(sprite, (entity, x: Type.sprite) => {
        let spriteDict = Js.Dict.empty();

        Js.Dict.set(dict, "entity", Js.Json.string(x.src));

        Js.Dict.set(dict, entity, Js.Json.object_(spriteDict));
      })
    );

    Js.Json.object_(dict)
  };

  let collideBox = (collideBox) => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(collideBox, (entity, x: Type.collideBox) => {
        let collideDict = Js.Dict.empty();

        Js.Dict.set(collideDict, "entity", Js.Json.string(x.entity));
        Js.Dict.set(collideDict, "size", vector(x.size));
        Js.Dict.set(collideDict, "position", vector(x.position));
        Js.Dict.set(collideDict, "collisions", collisions(x.collisions));

        Js.Dict.set(dict, entity, Js.Json.object_(collideDict));
      })
    );

    Js.Json.object_(dict)
  };

  let collideCircle = (collideCircle) => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(collideCircle, (entity, x: Type.collideCircle) => {
        let collideDict = Js.Dict.empty();

        Js.Dict.set(collideDict, "entity", Js.Json.string(x.entity));
        Js.Dict.set(collideDict, "radius", Js.Json.number(x.radius));
        Js.Dict.set(collideDict, "position", vector(x.position));
        Js.Dict.set(collideDict, "collisions", collisions(x.collisions));

        Js.Dict.set(dict, entity, Js.Json.object_(collideDict));
      })
    );

    Js.Json.object_(dict)
  };

  let time = (time: Type.time) => {
    let dict = Js.Dict.empty();

    Js.Dict.set(dict, "timeNow", Js.Json.number(time.timeNow));
    Js.Dict.set(dict, "delta", Js.Json.number(time.delta));

    Js.Json.object_(dict);
  };

  let state = (state: Type.state): string => {
    let dict = Js.Dict.empty();

    Js.Dict.set(dict, "entity", entity(state.entity));
    Js.Dict.set(dict, "transform", transform(state.transform));
    Js.Dict.set(dict, "sprite", sprite(state.sprite));
    Js.Dict.set(dict, "animationFloat", animationFloat(state.animationFloat));
    Js.Dict.set(dict, "animationVector", animationVector(state.animationVector));
    Js.Dict.set(dict, "collideBox", collideBox(state.collideBox));
    Js.Dict.set(dict, "collideCircle", collideCircle(state.collideCircle));
    Js.Dict.set(dict, "time", time(state.time));

    Js.Dict.set(dict, "mouseButtons", Js.Json.number(Belt.Int.toFloat(state.mouseButtons)));
    Js.Dict.set(dict, "mousePosition", vector(state.mousePosition));
    Js.Dict.set(dict, "isDebugInitialized", Js.Json.boolean(state.isDebugInitialized));

    dict
      ->Js.Json.object_
      ->Js.Json.stringifyWithSpace(2)  
  }
};
