screen = Screen()
screen:setNormalizedCoordinates(true, 600)

instance = ScreenEntityInstance("Resources/MyScreen.entity2d")
screen:addChild(instance)

logo = instance:getScreenEntityById("logo", true)

function Update(elapsed)
	logo:setRotation(logo:getRotation() + (elapsed * 100.0))
end