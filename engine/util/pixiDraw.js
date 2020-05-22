let isInitialized = false
let pixiApp = null
let images = null
let debugGraphics = null
let PIXI = null

let initialize = ( ) => {
  PIXI = require('pixi.js')

  pixiApp = new PIXI.Application({
    width: document.body.clientWidth,
    height: document.body.clientHeight,
    backgroundColor: 0x1099bb,
  })

  !document || !document.body
    ? console.warn("Couldn't find document body")
    : document.body.appendChild(pixiApp.view)

  images = []
  debugGraphics = new PIXI.Graphics()
  pixiApp.stage.addChild(debugGraphics)

  isInitialized = true
}

export default (params, devMode = false) => {
  if (!isInitialized) {
    initialize()
  }
  debugGraphics.clear()

  const state = params.flat(Infinity).slice(0, -1)

  for (let i = 0; i < state.length; i++) {
    const image = JSON.parse(state[i])
    const pixiImage = images.find(img => img.id === image.entity)

    if (pixiImage) {
      if (pixiImage.texture.baseTexture.imageUrl !== image.src) {
        changeImage(pixiImage, image)
      }
      drawImage(pixiImage, image, devMode, debugGraphics)
    } else {
      drawImage(
        createImage(images, pixiApp, image),
        image,
        devMode,
        debugGraphics,
      )
    }
  }
}

const drawImage = (pixiImage, image, devMode, debugGraphic) => {
  // if (gameObject.image.stickToRigidbody) {
  //   image.x = gameObject.rigidbody.position.x
  //   image.y = gameObject.rigidbody.position.y
  // } else {
  pixiImage.x = image.x
  pixiImage.y = image.y
  // }

  // image.rotation = gameObject.rigidbody.rotation
  pixiImage.anchor.set(0, 0)

  if (devMode) {
    const r = gameObject.rigidbody

    debugGraphic.lineStyle(1, 0x0000ff, 1)
    debugGraphic.drawRect(r.position.x, r.position.y, r.size.x, r.size.y)
  }
}

const createImage = (images, pixiApp, image) => {
  const pixiImage = PIXI.Sprite.from(image.src)
  pixiImage.id = image.id
  pixiApp.stage.addChild(pixiImage)
  images.push(pixiImage)

  return pixiImage
}

const changeImage = (pixiImage, image) => {
  pixiImage.texture = PIXI.Texture.from(image.src)
  return image
}
