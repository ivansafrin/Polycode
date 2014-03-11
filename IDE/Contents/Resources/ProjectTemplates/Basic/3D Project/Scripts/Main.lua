
scene = Scene(Scene.SCENE_3D)

sceneEntity = SceneEntityInstance(scene, "Resources/scene.entity")
scene:addChild(sceneEntity)

camera = safe_cast(sceneEntity:getEntityById("main_camera", true), Camera)
scene:setActiveCamera(camera)