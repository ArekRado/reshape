module Parse = {
  let emptyArray = Js.Json.array([||]);
  let emptyObject = Js.Json.object_(Js.Dict.fromList([]));
  let emptyNumber = Js.Json.number(0.0);
  let emptyString = Js.Json.string("");
  let emptyBool = value => Js.Json.boolean(value);

  let maybeString = (json, map) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONString(value) => map(Some(value))
      | _ => map(None)
    };

  let maybeFloat = (json, map) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONNumber(value) => map(Some(value))
      | _ => map(None)
    };

  let maybeBool = (json, map) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONTrue => map(Some(true))
      | Js.Json.JSONFalse => map(Some(false))
      | _ => map(None)
    };

  let maybeArray = (json, map) =>
    switch (Js.Json.classify(json)) {
      | Js.Json.JSONArray(value) => map(value)
      | _ => [| |]
    };

  let maybeProperty = (obj, property, defaultValue) =>
    switch (Js.Dict.get(obj, property)) {
    | Some(value) => value
    | None => defaultValue
  };

  let maybeObject = (json, map) => 
    switch (Js.Json.classify(json)) {
    | Js.Json.JSONObject(value) => map(Some(value))
    | _ => map(None)
    };

  // UTILS

  let stringWithDefault = (json, default) => maybeString(json, (maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let floatWithDefault = (json, default) => maybeFloat(json, (maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let boolWithDefault = (json, default) => maybeBool(json, (maybeValue) => 
    switch (maybeValue) {
    | Some(value) => value
    | None => default
    }
  );

  let getArrayWithDefault = (default, array, index) => 
    switch (Belt.Array.get(array, index)) {
    | Some(value) => value
    | None => default
    };

  let maybeVector = (json) => {
    let floatArray = maybeArray(json, array => Belt.Array.map(array, floatWithDefault(_, 0.0)));
    
    (
      getArrayWithDefault(0.0, floatArray, 0),
      getArrayWithDefault(0.0, floatArray, 1)
    );
  }

  let collisions = json =>
    maybeArray(json, json => json)
    ->Belt.List.fromArray
    ->Belt.List.map(value => {
      let collision = maybeArray(value, collision => collision);

      let collideType = switch (Belt.Array.get(collision, 0)) {
      | Some(value) => stringWithDefault(value, "Circle")
      | None => "Circle"
      };

      let collisionValue = switch (Belt.Array.get(collision, 1)) {
      | Some(value) => stringWithDefault(value, "")
      | None => ""
      };

      switch(collideType) {
      | "Box" => Type.Box(collisionValue)
      | "Circle" => Type.Circle(collisionValue)
      | _ => Type.Circle(collisionValue)
      };
    });
  
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

  let dictToMapString = (dict, map) =>
    dict
      ->maybeObject(dict => 
        switch(dict) {
        | Some(dict) =>
          dict
          ->Js.Dict.entries
          ->Belt.Map.String.fromArray
          ->Belt.Map.String.reduce(
            Belt.Map.String.empty,
            (acc, key, value) => {
              let maybeItem = maybeObject(value, value => 
                switch (value) {
                | Some(value) => Some(map(value));
                | None => None;
              });

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
        ->maybeProperty("entity", emptyArray)
        ->maybeArray(array => array)
        ->Belt.List.fromArray
        ->Belt.List.map(stringWithDefault(_, "")),
      mouseButtons: stateObj
        ->maybeProperty("mouseButtons", emptyNumber)
        ->floatWithDefault(0.0)
        ->Belt.Float.toInt,
      mousePosition: stateObj
        ->maybeProperty("mousePosition", emptyArray)
        ->maybeVector,
      time: stateObj 
        ->maybeProperty("time", emptyObject)
        ->maybeObject(timeObj: Type.time =>
          switch (timeObj) {
          | Some(timeObj) => {
              timeNow: timeObj
                ->maybeProperty("timeNow", emptyNumber)
                ->floatWithDefault(0.0),
              delta: timeObj
                ->maybeProperty("delta", emptyNumber)
                ->floatWithDefault(0.0),
            }
          | None => Type.initialState.time;
        }),
      isDebugInitialized: stateObj
        ->maybeProperty("isDebugInitialized", emptyBool(false))
        ->boolWithDefault(false),
      transform: stateObj
        ->maybeProperty("transform", emptyObject)
        ->dictToMapString((transform): Type.transform => {
          rotation: transform
            ->maybeProperty("rotation", emptyNumber)
            ->floatWithDefault(0.0),
          localRotation: transform
            ->maybeProperty("localRotation", emptyNumber)
            ->floatWithDefault(0.0),
          scale: transform
            ->maybeProperty("scale", emptyArray)
            ->maybeVector,
          localScale: transform
            ->maybeProperty("localScale", emptyArray)
            ->maybeVector,
          position: transform
            ->maybeProperty("position", emptyArray)
            ->maybeVector,
          localPosition: transform
            ->maybeProperty("localPosition", emptyArray)
            ->maybeVector,
          parent: transform
            ->maybeProperty("parent", emptyString)
            ->maybeString(parent =>
              switch(parent) {
                | Some(parent) => Some(parent)
                | None => None
              }
            ),
        }),
      sprite: stateObj
        ->maybeProperty("sprite", emptyObject)
        ->dictToMapString((sprite): Type.sprite => {
          src: sprite
            ->maybeProperty("src", emptyString)
            ->stringWithDefault(""),
        }),
      animationFloat: stateObj
        ->maybeProperty("animationFloat", emptyObject)
        ->dictToMapString((animationFloat): Type.animation(float) => {
          entity: animationFloat
            ->maybeProperty("entity", emptyString)
            ->stringWithDefault(""),
          name: animationFloat
            ->maybeProperty("name", emptyString)
            ->stringWithDefault(""),
          isPlaying: animationFloat
            ->maybeProperty("isPlaying", emptyBool(false))
            ->boolWithDefault(false),
          isFinished: animationFloat
            ->maybeProperty("isFinished", emptyBool(false))
            ->boolWithDefault(false),
          currentTime: animationFloat
            ->maybeProperty("currentTime", emptyNumber)
            ->floatWithDefault(0.0),
          value: animationFloat
            ->maybeProperty("value", emptyNumber)
            ->floatWithDefault(0.0),
          wrapMode: animationFloat
            ->maybeProperty("wrapMode", emptyString)
            ->maybeString(value =>
              switch(value) {
              | Some(value) => wrapMode(value)
              | None => Type.Once
              }
            ),
          keyframes: animationFloat
            ->maybeProperty("keyframes", emptyArray)
            ->maybeArray(array => array)
            ->Belt.List.fromArray
            ->Belt.List.map(
                maybeObject(_, keyframe: Type.keyframe(float) =>
                switch (keyframe) {
                | Some(keyframe) => {
                  duration: keyframe
                    ->maybeProperty("duration", emptyNumber)
                    ->floatWithDefault(0.0),
                  timingFunction: keyframe
                    ->maybeProperty("timingFunction", emptyString)
                    ->maybeString(value =>
                      switch(value) {
                      | Some(value) => timingFunction(value)
                      | None => Type.Linear
                      }
                    ),
                  valueRange: keyframe
                    ->maybeProperty("valueRange", emptyArray)
                    ->maybeVector,
                  }
                | None => {
                    duration: 0.0,
                    timingFunction: Type.Linear,
                    valueRange: (0.0, 0.0),
                  };
                }
              )
            )
        }),
      animationVector: stateObj
        ->maybeProperty("animationVector", emptyObject)
        ->dictToMapString((animationVector): Type.animation(Vector_Util.t) => {
          entity: animationVector
            ->maybeProperty("entity", emptyString)
            ->stringWithDefault(""),
          name: animationVector
            ->maybeProperty("name", emptyString)
            ->stringWithDefault(""),
          isPlaying: animationVector
            ->maybeProperty("isPlaying", emptyBool(false))
            ->boolWithDefault(false),
          isFinished: animationVector
            ->maybeProperty("isFinished", emptyBool(false))
            ->boolWithDefault(false),
          currentTime: animationVector
            ->maybeProperty("currentTime", emptyNumber)
            ->floatWithDefault(0.0),
          value: animationVector
            ->maybeProperty("value", emptyArray)
            ->maybeVector,
          wrapMode: animationVector
            ->maybeProperty("wrapMode", emptyString)
            ->maybeString(value =>
              switch(value) {
                | Some(value) => wrapMode(value)
                | None => Type.Once
              }
            ),
          keyframes: animationVector
            ->maybeProperty("keyframes", emptyArray)
            ->maybeArray(array => array)
            ->Belt.List.fromArray
            ->Belt.List.map(
                maybeObject(_, keyframe: Type.keyframe(Vector_Util.t) =>
                switch (keyframe) {
                | Some(keyframe) => {
                  duration: keyframe
                    ->maybeProperty("duration", emptyNumber)
                    ->floatWithDefault(0.0),
                  timingFunction: keyframe
                    ->maybeProperty("timingFunction", emptyString)
                    ->maybeString(value =>
                      switch(value) {
                        | Some(value) => timingFunction(value)
                        | None => Type.Linear
                      }
                    ),
                  valueRange: keyframe
                    ->maybeProperty("valueRange", emptyArray)
                    ->maybeArray(array => array) 
                    ->(array => {
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
        }),
      collideBox: stateObj
        ->maybeProperty("collideBox", emptyObject)
        ->dictToMapString((collideBox): Type.collideBox => {
          entity: collideBox
            ->maybeProperty("entity", emptyString)
            ->stringWithDefault(""),
          size: collideBox
            ->maybeProperty("size", emptyArray)
            ->maybeVector,
          position: collideBox
            ->maybeProperty("position", emptyArray)
            ->maybeVector,
          collisions: collideBox
            ->maybeProperty("collisions", emptyArray)
            ->collisions
        }),
      collideCircle: stateObj
        ->maybeProperty("collideBox", emptyObject)
        ->dictToMapString((collideCircle): Type.collideCircle => {
          entity: collideCircle
            ->maybeProperty("entity", emptyString)
            ->stringWithDefault(""),
          radius: collideCircle
            ->maybeProperty("radius", emptyNumber)
            ->floatWithDefault(0.0),
          position: collideCircle
            ->maybeProperty("position", emptyArray)
            ->maybeVector,
          collisions: collideCircle
            ->maybeProperty("collisions", emptyArray)
            ->collisions
        }),
      fieldFloat: stateObj
        ->maybeProperty("fieldFloat", emptyObject)
        ->dictToMapString((fieldFloat): Type.field(float) => {
          entity: fieldFloat
            ->maybeProperty("entity", emptyString)
            ->stringWithDefault(""),
          value: fieldFloat
            ->maybeProperty("value", emptyNumber)
            ->floatWithDefault(0.0),
        }),
      asset: stateObj 
        ->maybeProperty("asset", emptyObject)
        ->maybeObject(assetObj: Type.asset =>
          switch (assetObj) {
          | Some(assetObj) => {
              sprite: assetObj
                ->maybeProperty("sprite", emptyArray)
                ->maybeArray(array => array)
                ->Belt.List.fromArray
                ->Belt.List.map((sprite) => stringWithDefault(sprite, ""))
                // ->Belt.List.map((sprite): Type.asset => {
                //   src: sprite 
                //     ->maybeProperty("src", emptyString)
                //     ->stringWithDefault(""),
                // })
            }
          | None => Type.initialState.asset;
        }),
  };

  let state =
    maybeObject(_, (stateObj): Type.state => 
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

        Js.Dict.set(spriteDict, "src", Js.Json.string(x.src));

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

  let fieldFloat = (fieldFloat) => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(fieldFloat, (entity, x: Type.field(float)) => {
        let fieldFloat = Js.Dict.empty();

        Js.Dict.set(fieldFloat, "entity", Js.Json.string(x.entity));
        Js.Dict.set(fieldFloat, "value", Js.Json.number(x.value));

        Js.Dict.set(dict, entity, Js.Json.object_(fieldFloat));
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

  let asset = (asset: Type.asset) => {
    let dict = Js.Dict.empty();

    Js.Dict.set(
      dict, 
      "sprite", 
      asset.sprite
        ->Belt.List.toArray
        ->Js.Json.stringArray
    );

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
    Js.Dict.set(dict, "fieldFloat", fieldFloat(state.fieldFloat));
    Js.Dict.set(dict, "time", time(state.time));
    Js.Dict.set(dict, "asset", asset(state.asset));

    Js.Dict.set(dict, "mouseButtons", Js.Json.number(Belt.Int.toFloat(state.mouseButtons)));
    Js.Dict.set(dict, "mousePosition", vector(state.mousePosition));
    Js.Dict.set(dict, "isDebugInitialized", Js.Json.boolean(state.isDebugInitialized));

    dict
      ->Js.Json.object_
      ->Js.Json.stringifyWithSpace(2)  
  }
};
