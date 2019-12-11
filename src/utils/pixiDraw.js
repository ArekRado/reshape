import * as PIXI from 'pixi.js'

// export const createDraw = () => {
const pixiApp = new PIXI.Application({
  width: document.body.clientWidth,
  height: document.body.clientHeight,
  backgroundColor: 0x1099bb,
})

!document || !document.body
  ? console.warn("Couldn't find document body")
  : document.body.appendChild(pixiApp.view)

let images = []
const debugGraphics = new PIXI.Graphics()
pixiApp.stage.addChild(debugGraphics)

export default () => {
  return (state, devMode = false) => {
    // debugGraphics.clear()
    // Object.values(app.gameObjects).forEach(gameObject => {
    //   const image = images.find(image => image.id === gameObject.id)
    //   if (gameObject.image.url) {
    //     if (image) {
    //       if (image.texture.baseTexture.imageUrl !== gameObject.image.url) {
    //         changeImage(image, gameObject)
    //       }
    //       drawGameObject(image, gameObject, devMode, debugGraphics)
    //     } else {
    //       drawGameObject(
    //         createImage(images, pixiApp, gameObject),
    //         gameObject,
    //         devMode,
    //         debugGraphics,
    //       )
    //     }
    //   }
    // })
  }
}

const drawGameObject = (image, gameObject, devMode, debugGraphic) => {
  if (gameObject.image.stickToRigidbody) {
    image.x = gameObject.rigidbody.position.x
    image.y = gameObject.rigidbody.position.y
  } else {
    image.x = gameObject.image.position.x
    image.y = gameObject.image.position.y
  }

  image.rotation = gameObject.rigidbody.rotation
  image.anchor.set(0, 0)

  if (devMode) {
    const r = gameObject.rigidbody

    debugGraphic.lineStyle(1, 0x0000ff, 1)
    debugGraphic.drawRect(r.position.x, r.position.y, r.size.x, r.size.y)
  }
}

const createImage = (images, pixiApp, gameObject) => {
  const image = PIXI.Sprite.from(gameObject.image.url)
  image.id = gameObject.id
  pixiApp.stage.addChild(image)
  images.push(image)

  return image
}

const changeImage = (image, gameObject) => {
  image.texture = PIXI.Texture.from(gameObject.image.url)
  return gameObject
}
