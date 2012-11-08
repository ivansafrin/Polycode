
-- Simple example showing how to move, scale and rotate 2d entities

screen = Screen()
for i=0,9 do
        image = ScreenImage("Resources/polycode_logo.png")
        screen:addChild(image)

		-- Set position and position mode. Setting position mode to ScreenEntity.POSITION_CENTER, makes
		-- the entity's anchor point its middle, rather than its top left.
		-- Try commenting out that line and see how it affects the transfomrations
        image.position.x = 160+(42*i)
		image.position.y = 230
        image:setPositionMode(ScreenEntity.POSITION_CENTER)

		-- Rotate the image. You can alternatively call image:setPosition(45 * i)
        image.rotation.roll = 45 * i

		-- Set the image scale. You can alternatively call image:setScale(1.0-(0.1*i), 1.0-(0.1*i))
        image.scale.x = 1.0-(0.1*i)
		image.scale.y = 1.0-(0.1*i)
end
