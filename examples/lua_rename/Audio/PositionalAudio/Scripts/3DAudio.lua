
-- Simple positional audio example.

scene = Scene(Scene.SCENE_3D)

sourceEntity = Entity()
testSound = SceneSound("Resources/test.wav", 20, 50)
testSound:getSound():Play(true)

sourceEntity:addChild(testSound)
soundShape = ScenePrimitive(ScenePrimitive.TYPE_BOX, 1,1,1)
sourceEntity:addChild(soundShape)
scene:addEntity(sourceEntity)

positionValue = 0


function Update(elapsed)
        positionValue = positionValue + elapsed

        sourceEntity:setPosition((sin(positionValue) * 20), 0, cos(positionValue) * 50)
        sourceEntity:Roll(elapsed * 120)
        sourceEntity:Pitch(elapsed * 120)
end
