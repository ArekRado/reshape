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
    | _ => [||]
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

  let stringWithDefault = (json, default) =>
    maybeString(json, maybeValue =>
      switch (maybeValue) {
      | Some(value) => value
      | None => default
      }
    );

  let floatWithDefault = (json, default) =>
    maybeFloat(json, maybeValue =>
      switch (maybeValue) {
      | Some(value) => value
      | None => default
      }
    );

  let boolWithDefault = (json, default) =>
    maybeBool(json, maybeValue =>
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

  let maybeVector = json => {
    let floatArray =
      maybeArray(json, array =>
        Belt.Array.map(array, floatWithDefault(_, 0.0))
      );
    Js.log("maybeVector");
    (
      getArrayWithDefault(0.0, floatArray, 0),
      getArrayWithDefault(0.0, floatArray, 1),
    );
  };

  // let maybeVector = (json) => {
  //   let floatArray = maybeArray(json, array => Belt.Array.map(array, stringWithDefault(_, "0.0")));

  //   (
  //     Js.Float.fromString(getArrayWithDefault("0.0", floatArray, 0)),
  //     Js.Float.fromString(getArrayWithDefault("0.0", floatArray, 1))
  //   );
  // }

  let collisions = json =>
    maybeArray(json, json => json)
    ->Belt.List.fromArray
    ->Belt.List.map(value => {
        let collision = maybeArray(value, collision => collision);

        let collideType =
          switch (Belt.Array.get(collision, 0)) {
          | Some(value) => stringWithDefault(value, "Circle")
          | None => "Circle"
          };

        let collisionValue =
          switch (Belt.Array.get(collision, 1)) {
          | Some(value) => stringWithDefault(value, "")
          | None => ""
          };

        switch (collideType) {
        | "Box" => Type.Box(collisionValue)
        | "Circle" => Type.Circle(collisionValue)
        | _ => Type.Circle(collisionValue)
        };
      });

  let animatedComponent = json => {
    let animatedComponent = maybeArray(json, animation => animation);

    let animationType =
      switch (Belt.Array.get(animatedComponent, 0)) {
      | Some(value) => stringWithDefault(value, "FieldFloat")
      | None => "FieldFloat"
      };

    let animationEntity =
      switch (Belt.Array.get(animatedComponent, 1)) {
      | Some(value) => stringWithDefault(value, "")
      | None => ""
      };

    switch (animationType) {
    | "FieldFloat" => Type.FieldFloat(animationEntity)
    | "FieldVector" => Type.FieldVector(animationEntity)
    | "TransformLocalPosition" => Type.TransformLocalPosition(animationEntity)
    | _ => Type.FieldFloat(animationEntity)
    };
  };

  let wrapMode = wrapMode =>
    switch (wrapMode) {
    | "Once" => Type.Once
    | "Loop" => Type.Loop
    | "PingPong" => Type.PingPong
    | "ClampForever" => Type.ClampForever
    | _ => Type.Once
    };

  let timingFunction = timingFunction =>
    switch (timingFunction) {
    | "Linear" => Type.Linear
    | "EaseInQuad" => Type.EaseInQuad
    | "EaseOutQuad" => Type.EaseOutQuad
    | "EaseInOutQuad" => Type.EaseInOutQuad
    | "EaseInCubic" => Type.EaseInCubic
    | "EaseOutCubic" => Type.EaseOutCubic
    | "EaseInOutCubic" => Type.EaseInOutCubic
    | "EaseInQuart" => Type.EaseInQuart
    | "EaseOutQuart" => Type.EaseOutQuart
    | "EaseInOutQuart" => Type.EaseInOutQuart
    | "EaseInQuint" => Type.EaseInQuint
    | "EaseOutQuint" => Type.EaseOutQuint
    | "EaseInOutQuint" => Type.EaseInOutQuint
    | "CubicBezier" => Type.CubicBezier(0.0, 0.0, 0.0, 0.0) // todo
    | _ => Type.Linear
    };

  let dictToMapString = (dict, map) =>
    dict->maybeObject(dict =>
      switch (dict) {
      | Some(dict) =>
        dict
        ->Js.Dict.entries
        ->Belt.Map.String.fromArray
        ->Belt.Map.String.reduce(
            Belt.Map.String.empty,
            (acc, key, value) => {
              let maybeItem =
                maybeObject(value, value =>
                  switch (value) {
                  | Some(value) => Some(map(value))
                  | None => None
                  }
                );

              switch (maybeItem) {
              | Some(item) => Belt.Map.String.set(acc, key, item)
              | None => acc
              };
            },
          )
      | None => Belt.Map.String.empty
      }
    );

  let someState = (stateObj): Type.state => {
    entity:
      stateObj
      ->maybeProperty("entity", emptyArray)
      ->maybeArray(array => array)
      ->Belt.List.fromArray
      ->Belt.List.map(stringWithDefault(_, "")),
    mouseButtons:
      stateObj
      ->maybeProperty("mouseButtons", emptyNumber)
      ->floatWithDefault(0.0)
      ->Belt.Float.toInt,
    mousePosition:
      stateObj->maybeProperty("mousePosition", emptyArray)->maybeVector,
    time:
      stateObj
      ->maybeProperty("time", emptyObject)
      ->maybeObject((timeObj) =>
          (
            switch (timeObj) {
            | Some(timeObj) => {
                timeNow:
                  timeObj
                  ->maybeProperty("timeNow", emptyNumber)
                  ->floatWithDefault(0.0),
                delta:
                  timeObj
                  ->maybeProperty("delta", emptyNumber)
                  ->floatWithDefault(0.0),
              }
            | None => Type.initialState.time
            }: Type.time
          )
        ),
    isDebugInitialized:
      stateObj
      ->maybeProperty("isDebugInitialized", emptyBool(false))
      ->boolWithDefault(false),
    transform:
      stateObj
      ->maybeProperty("transform", emptyObject)
      ->dictToMapString((transform) =>
          (
            {
              rotation:
                transform
                ->maybeProperty("rotation", emptyNumber)
                ->floatWithDefault(0.0),
              localRotation:
                transform
                ->maybeProperty("localRotation", emptyNumber)
                ->floatWithDefault(0.0),
              scale:
                transform->maybeProperty("scale", emptyArray)->maybeVector,
              localScale:
                transform
                ->maybeProperty("localScale", emptyArray)
                ->maybeVector,
              position:
                transform->maybeProperty("position", emptyArray)->maybeVector,
              localPosition:
                transform
                ->maybeProperty("localPosition", emptyArray)
                ->maybeVector,
              parent:
                transform
                ->maybeProperty("parent", emptyString)
                ->maybeString(parent =>
                    switch (parent) {
                    | Some(parent) => Some(parent)
                    | None => None
                    }
                  ),
            }: Type.transform
          )
        ),
    sprite:
      stateObj
      ->maybeProperty("sprite", emptyObject)
      ->dictToMapString((sprite) =>
          (
            {
              src:
                sprite
                ->maybeProperty("src", emptyString)
                ->stringWithDefault(""),
            }: Type.sprite
          )
        ),
    animation:
      stateObj
      ->maybeProperty("animation", emptyObject)
      ->dictToMapString((animation) =>
          (
            {
              entity:
                animation
                ->maybeProperty("entity", emptyString)
                ->stringWithDefault(""),
              name:
                animation
                ->maybeProperty("name", emptyString)
                ->stringWithDefault(""),
              isPlaying:
                animation
                ->maybeProperty("isPlaying", emptyBool(false))
                ->boolWithDefault(false),
              isFinished:
                animation
                ->maybeProperty("isFinished", emptyBool(false))
                ->boolWithDefault(false),
              currentTime:
                animation
                ->maybeProperty("currentTime", emptyNumber)
                ->floatWithDefault(0.0),
              component:
                animation
                ->maybeProperty("component", emptyArray)
                ->animatedComponent,
              wrapMode:
                animation
                ->maybeProperty("wrapMode", emptyString)
                ->maybeString(value =>
                    switch (value) {
                    | Some(value) => wrapMode(value)
                    | None => Type.Once
                    }
                  ),
              keyframes:
                animation
                ->maybeProperty("keyframes", emptyArray)
                ->maybeArray(array => array)
                ->Belt.List.fromArray
                ->Belt.List.map(
                    maybeObject(_, (keyframe) =>
                      (
                        switch (keyframe) {
                        | Some(keyframe) =>
                          let rangeType =
                            animation
                            ->maybeProperty("rangeType", emptyString)
                            ->stringWithDefault("Float");

                          switch (rangeType) {
                          | "Vector" => {
                              duration:
                                keyframe
                                ->maybeProperty("duration", emptyNumber)
                                ->floatWithDefault(0.0),
                              timingFunction:
                                keyframe
                                ->maybeProperty("timingFunction", emptyString)
                                ->maybeString(value =>
                                    switch (value) {
                                    | Some(value) => timingFunction(value)
                                    | None => Type.Linear
                                    }
                                  ),
                              valueRange:
                                keyframe
                                ->maybeProperty("valueRange", emptyArray)
                                ->maybeArray(array => array)
                                ->(
                                    array => {
                                      let from =
                                        switch (Belt.Array.get(array, 0)) {
                                        | Some(value) => maybeVector(value)
                                        | None => Vector_Util.zero
                                        };

                                      let to_ =
                                        switch (Belt.Array.get(array, 1)) {
                                        | Some(value) => maybeVector(value)
                                        | None => Vector_Util.zero
                                        };

                                      Type.Vector((from, to_));
                                    }
                                  ),
                            }
                          | "Float"
                          | _ => {
                              duration:
                                keyframe
                                ->maybeProperty("duration", emptyNumber)
                                ->floatWithDefault(0.0),
                              timingFunction:
                                keyframe
                                ->maybeProperty("timingFunction", emptyString)
                                ->maybeString(value =>
                                    switch (value) {
                                    | Some(value) => timingFunction(value)
                                    | None => Type.Linear
                                    }
                                  ),
                              valueRange:
                                Type.Float(
                                  keyframe
                                  ->maybeProperty("valueRange", emptyArray)
                                  ->maybeVector,
                                ),
                            }
                          };
                        | None => {
                            duration: 0.0,
                            timingFunction: Type.Linear,
                            valueRange: Type.Float((0.0, 0.0)),
                          }
                        }: Type.keyframe
                      )
                    ),
                  ),
            }: Type.animation
          )
        ),
    collideBox:
      stateObj
      ->maybeProperty("collideBox", emptyObject)
      ->dictToMapString((collideBox) =>
          (
            {
              entity:
                collideBox
                ->maybeProperty("entity", emptyString)
                ->stringWithDefault(""),
              size:
                collideBox->maybeProperty("size", emptyArray)->maybeVector,
              position:
                collideBox
                ->maybeProperty("position", emptyArray)
                ->maybeVector,
              collisions:
                collideBox
                ->maybeProperty("collisions", emptyArray)
                ->collisions,
              name:
                collideBox
                ->maybeProperty("name", emptyString)
                ->stringWithDefault(""),
            }: Type.collideBox
          )
        ),
    collideCircle:
      stateObj
      ->maybeProperty("collideBox", emptyObject)
      ->dictToMapString((collideCircle) =>
          (
            {
              entity:
                collideCircle
                ->maybeProperty("entity", emptyString)
                ->stringWithDefault(""),
              radius:
                collideCircle
                ->maybeProperty("radius", emptyNumber)
                ->floatWithDefault(0.0),
              position:
                collideCircle
                ->maybeProperty("position", emptyArray)
                ->maybeVector,
              collisions:
                collideCircle
                ->maybeProperty("collisions", emptyArray)
                ->collisions,
              name:
                collideCircle
                ->maybeProperty("name", emptyString)
                ->stringWithDefault(""),
            }: Type.collideCircle
          )
        ),
    fieldFloat:
      stateObj
      ->maybeProperty("fieldFloat", emptyObject)
      ->dictToMapString((fieldFloat) =>
          (
            {
              entity:
                fieldFloat
                ->maybeProperty("entity", emptyString)
                ->stringWithDefault(""),
              name:
                fieldFloat
                ->maybeProperty("name", emptyString)
                ->stringWithDefault(""),
              value:
                fieldFloat
                ->maybeProperty("value", emptyNumber)
                ->floatWithDefault(0.0),
            }:
              Type.field(float)
          )
        ),
    fieldVector:
      stateObj
      ->maybeProperty("fieldVector", emptyObject)
      ->dictToMapString((fieldVector) =>
          (
            {
              entity:
                fieldVector
                ->maybeProperty("entity", emptyString)
                ->stringWithDefault(""),
              name:
                fieldVector
                ->maybeProperty("name", emptyString)
                ->stringWithDefault(""),
              value:
                fieldVector->maybeProperty("value", emptyArray)->maybeVector,
            }:
              Type.field(Vector_Util.t)
          )
        ),
    asset:
      stateObj
      ->maybeProperty("asset", emptyObject)
      ->maybeObject((assetObj) =>
          (
            switch (assetObj) {
            | Some(assetObj) => {
                sprite:
                  assetObj
                  ->maybeProperty("sprite", emptyArray)
                  ->maybeArray(array => array)
                  ->Belt.List.fromArray
                  ->Belt.List.map(sprite => stringWithDefault(sprite, "")),
              }
            | None => Type.initialState.asset
            }: Type.asset
            // ->Belt.List.map((sprite): Type.asset => {
            //   src: sprite
            //     ->maybeProperty("src", emptyString)
            //     ->stringWithDefault(""),
            // })
          )
        ),
  };

  let state =
    maybeObject(_, (stateObj) =>
      (
        switch (stateObj) {
        | Some(stateObj) => someState(stateObj)
        | None => Type.initialState
        }: Type.state
      )
    );
};

module Stringify = {
  let vector = ((x, y)) => Js.Json.numberArray([|x, y|]);

  let collisions = (collisions: Belt.List.t(Type.collideType)) =>
    Belt.List.map(collisions, collision =>
      switch (collision) {
      | Box(entity) => Js.Json.stringArray([|"Box", entity|])
      | Circle(entity) => Js.Json.stringArray([|"Circle", entity|])
      }
    )
    ->Array.of_list
    ->Js.Json.array;

  let timingFunction = (timingFunction: Type.timingFunction) => {
    let x =
      switch (timingFunction) {
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
  };

  let entity = entity => entity->Belt.List.toArray->Js.Json.stringArray;

  let transform = transform => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        transform,
        (entity, x: Type.transform) => {
          let transformDict = Js.Dict.empty();

          Js.Dict.set(transformDict, "rotation", Js.Json.number(x.rotation));
          Js.Dict.set(
            transformDict,
            "localRotation",
            Js.Json.number(x.localRotation),
          );
          Js.Dict.set(transformDict, "scale", vector(x.scale));
          Js.Dict.set(transformDict, "localScale", vector(x.localScale));
          Js.Dict.set(transformDict, "position", vector(x.position));
          Js.Dict.set(
            transformDict,
            "localPosition",
            vector(x.localPosition),
          );

          switch (x.parent) {
          | Some(parent) =>
            Js.Dict.set(transformDict, "parent", Js.Json.string(parent))
          | None => Js.Dict.set(transformDict, "parent", Js.Json.null)
          };

          Js.Dict.set(dict, entity, Js.Json.object_(transformDict));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let animation = animation => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        animation,
        (entity, x: Type.animation) => {
          let animationDict = Js.Dict.empty();

          Js.Dict.set(animationDict, "entity", Js.Json.string(x.entity));
          Js.Dict.set(animationDict, "name", Js.Json.string(x.name));
          Js.Dict.set(
            animationDict,
            "isPlaying",
            Js.Json.boolean(x.isPlaying),
          );
          Js.Dict.set(
            animationDict,
            "isFinished",
            Js.Json.boolean(x.isFinished),
          );
          Js.Dict.set(
            animationDict,
            "currentTime",
            Js.Json.number(x.currentTime),
          );
          // rangeType
          Js.Dict.set(
            animationDict,
            "component",
            switch (x.component) {
            | FieldFloat(entity) =>
              Js.Json.stringArray([|"FieldFloat", entity|])
            | FieldVector(entity) =>
              Js.Json.stringArray([|"FieldVector", entity|])
            | TransformLocalPosition(entity) =>
              Js.Json.stringArray([|"TransformLocalPosition", entity|])
            },
          );

          Js.Dict.set(
            animationDict,
            "wrapMode",
            Js.Json.string(
              switch (x.wrapMode) {
              | Once => "Once"
              | Loop => "Loop"
              | PingPong => "PingPong"
              | ClampForever => "ClampForever"
              },
            ),
          );

          Js.Dict.set(
            animationDict,
            "keyframes",
            Js.Json.objectArray(
              Belt.List.map(
                x.keyframes,
                keyframe => {
                  let keyframeDict = Js.Dict.empty();

                  Js.Dict.set(
                    keyframeDict,
                    "duration",
                    Js.Json.number(keyframe.duration),
                  );
                  Js.Dict.set(
                    keyframeDict,
                    "timingFunction",
                    timingFunction(keyframe.timingFunction),
                  );

                  switch (keyframe.valueRange) {
                  | Vector((v1, v2)) =>
                    Js.Dict.set(
                      keyframeDict,
                      "valueRange",
                      Js.Json.array([|vector(v1), vector(v2)|]),
                    )
                  | Float(v) =>
                    Js.Dict.set(
                      animationDict,
                      "rangeType",
                      Js.Json.string("Float"),
                    );
                    Js.Dict.set(keyframeDict, "valueRange", vector(v));
                  };

                  keyframeDict;
                },
              )
              ->Array.of_list,
            ),
          );

          Js.Dict.set(dict, entity, Js.Json.object_(animationDict));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let sprite = sprite => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        sprite,
        (entity, x: Type.sprite) => {
          let spriteDict = Js.Dict.empty();

          Js.Dict.set(spriteDict, "src", Js.Json.string(x.src));

          Js.Dict.set(dict, entity, Js.Json.object_(spriteDict));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let collideBox = collideBox => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        collideBox,
        (entity, x: Type.collideBox) => {
          let collideDict = Js.Dict.empty();

          Js.Dict.set(collideDict, "entity", Js.Json.string(x.entity));
          Js.Dict.set(collideDict, "name", Js.Json.string(x.name));
          Js.Dict.set(collideDict, "size", vector(x.size));
          Js.Dict.set(collideDict, "position", vector(x.position));
          Js.Dict.set(collideDict, "collisions", collisions(x.collisions));

          Js.Dict.set(dict, entity, Js.Json.object_(collideDict));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let collideCircle = collideCircle => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        collideCircle,
        (entity, x: Type.collideCircle) => {
          let collideDict = Js.Dict.empty();

          Js.Dict.set(collideDict, "entity", Js.Json.string(x.entity));
          Js.Dict.set(collideDict, "name", Js.Json.string(x.name));
          Js.Dict.set(collideDict, "radius", Js.Json.number(x.radius));
          Js.Dict.set(collideDict, "position", vector(x.position));
          Js.Dict.set(collideDict, "collisions", collisions(x.collisions));

          Js.Dict.set(dict, entity, Js.Json.object_(collideDict));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let fieldFloat = fieldFloat => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        fieldFloat,
        (entity, x: Type.field(float)) => {
          let fieldFloat = Js.Dict.empty();

          Js.Dict.set(fieldFloat, "entity", Js.Json.string(x.entity));
          Js.Dict.set(fieldFloat, "name", Js.Json.string(x.name));
          Js.Dict.set(fieldFloat, "value", Js.Json.number(x.value));

          Js.Dict.set(dict, entity, Js.Json.object_(fieldFloat));
        },
      ),
    );

    Js.Json.object_(dict);
  };

  let fieldVector = fieldVector => {
    let dict = Js.Dict.empty();

    ignore(
      Belt.Map.String.mapWithKey(
        fieldVector,
        (entity, x: Type.field(Vector_Util.t)) => {
          let fieldVector = Js.Dict.empty();

          Js.Dict.set(fieldVector, "entity", Js.Json.string(x.entity));
          Js.Dict.set(fieldVector, "name", Js.Json.string(x.name));
          Js.Dict.set(fieldVector, "value", vector(x.value));

          Js.Dict.set(dict, entity, Js.Json.object_(fieldVector));
        },
      ),
    );

    Js.Json.object_(dict);
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
      asset.sprite->Belt.List.toArray->Js.Json.stringArray,
    );

    Js.Json.object_(dict);
  };

  let state = (state: Type.state): string => {
    let dict = Js.Dict.empty();

    Js.Dict.set(dict, "entity", entity(state.entity));
    Js.Dict.set(dict, "transform", transform(state.transform));
    Js.Dict.set(dict, "sprite", sprite(state.sprite));
    Js.Dict.set(dict, "animation", animation(state.animation));
    Js.Dict.set(dict, "collideBox", collideBox(state.collideBox));
    Js.Dict.set(dict, "collideCircle", collideCircle(state.collideCircle));
    Js.Dict.set(dict, "fieldFloat", fieldFloat(state.fieldFloat));
    Js.Dict.set(dict, "fieldVector", fieldVector(state.fieldVector));
    Js.Dict.set(dict, "time", time(state.time));
    Js.Dict.set(dict, "asset", asset(state.asset));

    Js.Dict.set(
      dict,
      "mouseButtons",
      Js.Json.number(Belt.Int.toFloat(state.mouseButtons)),
    );
    Js.Dict.set(dict, "mousePosition", vector(state.mousePosition));
    Js.Dict.set(
      dict,
      "isDebugInitialized",
      Js.Json.boolean(state.isDebugInitialized),
    );

    dict->Js.Json.object_->Js.Json.stringifyWithSpace(2);
  };
};
