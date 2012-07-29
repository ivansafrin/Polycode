class "ImageRotator" (EventHandler)

timer = Timer(true, 1000)

function ImageRotator:ImageRotator(image)
        self.image = image
        self:EventHandler()
end

function ImageRotator:handleEvent(e)
        if e:getDispatcher() == timer and e:getEventCode() == EVENT_TRIGGER then
                self.image:setRotation(self.image:getRotation()+90)
        end
end

screen = Screen()
image = ScreenImage("polycode_logo.png")
screen:addChild(image)

rotator = ImageRotator(image)
timer:addEventListener(rotator, EVENT_TRIGGER)

