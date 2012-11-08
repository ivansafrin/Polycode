
-- Basic 2D positional sound example

screen = Screen()

sourceEntity = ScreenEntity()
testSound = ScreenSound("Resources/test.wav", 200, 600)
testSound:getSound():Play(true)
sourceEntity:addChild(testSound)
soundShape = ScreenShape(ScreenShape.SHAPE_CIRCLE, 20,20,10)
sourceEntity:addChild(soundShape)
screen:addChild(sourceEntity)

listenerEntity = ScreenEntity()
soundListener = ScreenSoundListener()
listenerEntity:addChild(soundListener)

soundShape = ScreenShape(ScreenShape.SHAPE_CIRCLE, 20,20,10)
soundShape:setColor(0.0, 1.0, 0.0, 1.0)
listenerEntity:addChild(soundShape)
screen:addChild(listenerEntity)

listenerPositionValue = 0
positionValue = 0

function Update(elapsed)
        positionValue = positionValue + elapsed
        listenerPositionValue = listenerPositionValue + elapsed * 0.3
        sourceEntity:setPosition(300 + (sin(positionValue) * 300), 250 + cos(positionValue) * 100)
        listenerEntity:setPosition(300 + (sin(listenerPositionValue) * 300), 250)
end
