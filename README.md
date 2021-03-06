# Reshape

```
npm i
```

```js
// run bsb
npm run start1
// run webpack-dev-server
npm run start2
```

```js
// run bsb with test env
npm run test:watch1
// run nodemon
npm run test:watch2
```

If this is your first time using a development container, please follow the [getting started steps](https://aka.ms/vscode-remote/containers/getting-started) to set up your machine.

# ECS

[What is entity component system?](https://en.wikipedia.org/wiki/Entity_component_system)

# Entity

It's just a uniq string - think about it as uniq ID from SQL database.

```reason
let newEntity = Reshape.Entity.generate("human-friendly-name"); // "human-friendly-name###9b1deb4d-3b7d-4bad-9bdd-2b0d7b3dcb6d

let letStateWithNewEntity = Reshape.Entity.create(newEntity, Reshape.initialState);
```

# Component

Component describes game state without logic. It's something like a table record from SQL database.

```reason
Reshape.Component.Sprite;
Reshape.Component.Transform;
Reshape.Component.AnimationFloat;
Reshape.Component.AnimationVector;
Reshape.Component.CollideBox;
Reshape.Component.CollideCircle;
```

Example how to use components in your code:

```reason
let gunSpriteUrl: string = [%raw {|require('../assets/gun.png').default|}];

// blueprint helps you avoid excessive code - It's common pattern used in gamedev
module Gun_Blueprint {
  let create = (state: Reshape.Type.state): Reshape.Type.state => {
    // create new entity
    let gunEntity = Reshape.Entity.generate("gun");

    state.engine
      // push new entity to state
      ->Reshape.Entity.create(
        ~entity=cityEntity,
        ~state=_,
      )
      // create and push gun sprite and connect it with entity
      ->Reshape.Component.Sprite.create(
          ~entity=cityEntity,
          ~src=gunSpriteUrl,
          ~state=_,
          ()
      )
      // do same with transform
      ->Reshape.Component.Transform.create(
        ~entity=cityEntity,
        ~localPosition=localPosition,
        ~state=_,
        ()
      )
      // and animation :)
      ->Reshape.Component.AnimationFloat.create(
        ~entity=gunEntity,
        ~name="shot", // Entity can be connected with multiple animations, name helps you with identify each animation
        ~isPlaying=true,
        ~keyframes=[
          {duration: 2500.0, timingFunction: Linear, valueRange: (0.0, 1.0)}: Shared.keyframe(float),
        ],
        ~wrapMode=Loop,
        ~state=_,
        ()
      );
  };
};
```

# System

Pure logic without state. Every system receives whole state then modifies it and returns new state. Reshape contains several internal systems use `Reshape.runOneFrame` funtion to run them.

# Easy start

```reason
[@bs.val] external requestAnimationFrame : (unit => unit) => unit = "requestAnimationFrame";
[@bs.val] external setTimeout : (unit => unit, int) => float = "setTimeout";

type gameState = {
  yourState: string,
}

// This is example how to connect both states
// Reshape uses only state.engine, your systems should use only state.game
type state = {
  game: gameState,
  engine: Reshape.Type.state,
}

let initialState: state = {
  game: {
    yourState: "",
  },
  engine: Reshape.initialState,
};

let rec logic = (state: state) => {
  let newEngine = Reshape.runOneFrame(
    ~state=state.engine, // Reshape.Type.state
    // ~enableDraw=false, // Usefull to avoid canvas rendering during a unit tests
    // ~performanceNow=1000.0 // Usefull to mock unit tests
    ()
  );

  let newState = ({game: state.game, engine: newEngine} : state)
    ->Game.System.System1.update
    ->Game.System.System2.update
    ->Game.System.System3.update
    ->Game.System.System4.update

  requestAnimationFrame(() => logic(newState));
};

// do side effects - initialize will mount new DOM elements and attach event listeners
Reshape.initialize();
// your game loop
logic(initialState);
```
