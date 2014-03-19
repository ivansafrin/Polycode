-- Simple example of displaying an image

scene = Scene(Scene.SCENE_2D)
scene:getActiveCamera():setOrthoSize(640, 480)
image = SceneImage("Resources/polycode_logo.png")
scene:addChild(image)
