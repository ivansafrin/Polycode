screen = Screen()
for i=0,9 do
        image = ScreenImage("polycode_logo.png")
        screen:addChild(image)
        image:setPosition(160+(42*i), 230)
        image:setPositionMode(POSITION_CENTER)
        image:setRotation(45*i)
        image:setScale(1.0-(0.1*i),1.0-(0.1*i))
end
