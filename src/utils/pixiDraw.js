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

export default (state, devMode = false) => {
  console.log(state)

  debugGraphics.clear()

  for (let i = 0; i < images.length; i++) {
    const image = images[i]
    const pixiImage = images.find(image => image.id === entity)

    if (pixiImage.src) {
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
}

const drawImage = (pixiImage, image, devMode, debugGraphic) => {
  // if (gameObject.image.stickToRigidbody) {
  //   image.x = gameObject.rigidbody.position.x
  //   image.y = gameObject.rigidbody.position.y
  // } else {
  pixiImage.x = image.position[0]
  pixiImage.y = image.position[1]
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
  impixiImageage.id = image.id
  pixiApp.stage.addChild(pixiImage)
  images.push(pixiImage)

  return pixiImage
}

const changeImage = (pixiImage, image) => {
  pixiImage.texture = PIXI.Texture.from(image.src)
  return image
}
