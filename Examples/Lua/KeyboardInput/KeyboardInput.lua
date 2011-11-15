
class "ImageRotator" (EventHandler)

function ImageRotator:ImageRotator(image)
        self.image = image
        self.rotationSpeed = 0
        self:EventHandler()
end

function ImageRotator:rotate(e)
        self.image:setRotation(self.image:getRotation() + e * self.rotationSpeed)
end

function ImageRotator:handleEvent(e)
        if e:getDispatcher() == Services.Core:getInput() then
                local inputEvent = InputEvent(e)
                local key = inputEvent:keyCode()
                if e:getEventCode() == EVENT_KEYDOWN then
                        if key == KEY_LEFT then
                                self.rotationSpeed = -200
                        elseif key == KEY_RIGHT then
                                self.rotationSpeed = 200
                        end
                elseif e:getEventCode() == EVENT_KEYUP then
                        if key == KEY_LEFT or key == KEY_RIGHT then
                                self.rotationSpeed = 0
                        end
                end
        end
end

screen = Screen()
image = ScreenImage("polycode_logo.png")
image:setPositionMode(POSITION_CENTER)
image:setPosition(640/2,480/2)
screen:addChild(image)


imageRotator = ImageRotator(image)

Services.Core:getInput():addEventListener(imageRotator, EVENT_KEYDOWN)
Services.Core:getInput():addEventListener(imageRotator, EVENT_KEYUP)

function Update(elapsed)
        imageRotator:rotate(elapsed)
end
