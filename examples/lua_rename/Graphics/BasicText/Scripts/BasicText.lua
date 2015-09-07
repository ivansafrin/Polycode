-- Simple text label example.

scene = Scene(Scene.SCENE_2D)
scene:getActiveCamera():setOrthoSize(640, 480)
label = SceneLabel("Hello, Polycode!", 32)
scene:addChild(label)
