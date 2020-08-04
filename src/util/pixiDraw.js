let isInitialized = false
let pixiApp = null
let images = null
let debugGraphics = null
let PIXI = null

let getGameContainerDimensions = () => {
  const element = document.querySelector('#engine-game')

  return [element.clientWidth, element.clientHeight]
}

let initialize = () => {
  PIXI = require('pixi.js')

  const [x, y] = getGameContainerDimensions()

  pixiApp = new PIXI.Application({
    width: x,
    height: y,
    backgroundColor: 0x1099bb,
  })

  pixiApp.renderer.autoResize = true

  if (!document || !document.body) {
    console.warn("Couldn't find document body")
  } else {
    const element = document.querySelector('#engine-game')
    element.appendChild(pixiApp.view)
  }

  images = new Map()
  debugGraphics = new PIXI.Graphics()
  pixiApp.stage.addChild(debugGraphics)

  isInitialized = true
}

exports.default = (params, devMode = false) => {
  if(Array.isArray(params) === false) {
    return
  }

  if (!isInitialized) {
    initialize()
  }
  debugGraphics.clear()

  // const state = params.flat(Infinity).slice(0, -1)

  for (let i = 0; i < params.length; i++) {
    const image = JSON.parse(params[i])
    const pixiImage = images.get(image.entity)

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
    debugGraphic.lineStyle(1, 0x0000ff, 1)
    debugGraphic.drawRect(image.x, image.y, 20, 20)
    
    // debugGraphic.drawRect(r.position.x, r.position.y, r.size.x, r.size.y)
  }
}

const createImage = (images, pixiApp, image) => {
  const pixiImage = PIXI.Sprite.from(image.src)
  pixiImage.id = image.entity
  pixiApp.stage.addChild(pixiImage)
  images.set(pixiImage.id, pixiImage)

  return pixiImage
}

const changeImage = (pixiImage, image) => {
  pixiImage.texture = PIXI.Texture.from(image.src)
  return image
}
