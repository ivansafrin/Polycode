
-- Simple positional 3D Audio example.

scene = Scene()

sourceEntity = SceneEntity()
testSound = SceneSound("Resources/test.wav", 20, 50)
testSound:getSound():Play(true)
sourceEntity:addChild(testSound)
soundShape = ScenePrimitive(ScenePrimitive.TYPE_BOX, 1,1,1)
soundShape:setMaterialByName("Default")
sourceEntity:addChild(soundShape)
scene:addEntity(sourceEntity)

light = SceneLight(SceneLight.AREA_LIGHT, scene, 300, 0,0)
scene:addLight(light)
soundListener = SceneSoundListener()
scene:addEntity(soundListener)

positionValue = 0


function Update(elapsed)
        positionValue = positionValue + elapsed

        sourceEntity:setPosition((sin(positionValue) * 20), 0, cos(positionValue) * 50)
        sourceEntity:Roll(elapsed * 120)
        sourceEntity:Pitch(elapsed * 120)
end
