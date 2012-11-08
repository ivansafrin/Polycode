Services.ResourceManager:addDirResource("Resources", false)

scene = Scene()
ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 5,5)
ground:setMaterialByName("GroundMaterial")
scene:addEntity(ground)

box =  ScenePrimitive(ScenePrimitive.TYPE_TORUS, 0.8,0.3,30,20)
box:setMaterialByName("CubeMaterial")
box:setPosition(0.0, 0.5, 0.0)
scene:addEntity(box)

lightBase = SceneEntity()

light = SceneLight(SceneLight.AREA_LIGHT, scene, 20)
light:setPosition(3,2,7)
light:setLightColor(1,0,0)
scene:addLight(light)
lightBase:addChild(light)

light = SceneLight(SceneLight.AREA_LIGHT, scene, 20)
light:setPosition(-3,2,7)
light:setLightColor(0,1,0)
scene:addLight(light)
lightBase:addChild(light)

light = SceneLight(SceneLight.AREA_LIGHT, scene, 20)
light:setPosition(-3,2,-7)
light:setLightColor(0,0,1)
scene:addLight(light)
lightBase:addChild(light)

light = SceneLight(SceneLight.AREA_LIGHT, scene, 20)
light:setPosition(3,2,-7)
light:setLightColor(1,0,1)
scene:addLight(light)
lightBase:addChild(light)

light = SceneLight(SceneLight.SPOT_LIGHT, scene, 5)
light:setPosition(0,2,2)
light:setSpotlightProperties(30,6)
light:setLightColor(1,1,0)
scene:addLight(light)
lightBase:addChild(light)

light:lookAt(Vector3(0,0,0), Vector3(0,1,0))
light:enableShadows(true)

light = SceneLight(SceneLight.SPOT_LIGHT, scene, 5)
light:setPosition(0,2,-2)
light:setSpotlightProperties(30,6)
light:setLightColor(0,1,1)
scene:addLight(light)
lightBase:addChild(light)
light:lookAt(Vector3(0,0,0), Vector3(0,1,0))
light:enableShadows(true)

scene:getDefaultCamera():setPosition(5,5,5)
scene:getDefaultCamera():lookAt(Vector3(0,0,0), Vector3(0,1,0))

function Update(elapsed)
	lightBase.rotation.yaw = lightBase.rotation.yaw + (elapsed * 10.0)
end

