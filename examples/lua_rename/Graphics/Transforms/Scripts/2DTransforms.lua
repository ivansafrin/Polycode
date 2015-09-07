
-- Simple example showing how to move, scale and rotate 2d entities

scene = Scene(Scene.SCENE_2D)
scene:getActiveCamera():setOrthoSize(640, 480)

for i=0,9 do
        image = SceneImage("Resources/polycode_logo.png")
        scene:addChild(image)

		-- Set the image position
		image:setPosition((30*i), 0)

		-- Rotate the image. You can alternatively call image:setPosition(45 * i)
        image:setRoll(45 * i)

		-- Set the image scale.
		image:setScale(1.0-(0.1*i),1.0-(0.1*i))
end
