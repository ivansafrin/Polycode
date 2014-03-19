Services.ResourceManager:addDirResource("Resources", false)

scene = Scene(Scene.SCENE_3D)
ground = ScenePrimitive(ScenePrimitive.TYPE_PLANE, 5,5)
ground:setMaterialByName("GroundMaterial", Services.ResourceManager:getGlobalPool())
scene:addEntity(ground)

box =  ScenePrimitive(ScenePrimitive.TYPE_TORUS, 0.8,0.3,30,20)
box:setMaterialByName("CubeMaterial", Services.ResourceManager:getGlobalPool())
box:setPosition(0.0, 0.5, 0.0)
scene:addEntity(box)

lightBase = Entity()
scene:addChild(lightBase)

light = SceneLight(SceneLight.POINT_LIGHT, scene, 20)
light:setPosition(3,2,7)
light:setLightColor(1,0,0)
scene:addLight(light)

light = SceneLight(SceneLight.POINT_LIGHT, scene, 20)
light:setPosition(-3,2,7)
light:setLightColor(0,1,0)
scene:addLight(light)

light = SceneLight(SceneLight.POINT_LIGHT, scene, 20)
light:setPosition(-3,2,-7)
light:setLightColor(0,0,1)
scene:addLight(light)

light = SceneLight(SceneLight.POINT_LIGHT, scene, 20)
light:setPosition(3,2,-7)
light:setLightColor(1,0,1)
scene:addLight(light)

light = SceneLight(SceneLight.SPOT_LIGHT, scene, 10)
light:setPosition(0,3,1)
light:setLightColor(1,1,0)
scene:addLight(light)
lightBase:addChild(light)
light:lookAt(Vector3(0,0,0), Vector3(0,1,0))
light:enableShadows(true)

light = SceneLight(SceneLight.SPOT_LIGHT, scene, 10)
light:setPosition(0,3,-1)
light:setLightColor(0,1,1)
scene:addLight(light)
lightBase:addChild(light)
light:lookAt(Vector3(0,0,0), Vector3(0,1,0))
light:enableShadows(true)

scene:getDefaultCamera():setPosition(5,5,5)
scene:getDefaultCamera():lookAt(Vector3(0,0,0), Vector3(0,1,0))

function Update(elapsed)
	lightBase:setYaw(lightBase:getYaw()+ (elapsed * 10.0))
end

