class "MouseImage" (EventHandler)

function MouseImage:MouseImage(image)
        self.image = image
        self:EventHandler()
end

function MouseImage:handleEvent(e)
        if e:getDispatcher() == Services.Core:getInput() then
                local inputEvent = InputEvent(e)
                if e:getEventCode() == EVENT_MOUSEMOVE then
                        local pos = inputEvent:getMousePosition()
                        self.image:setPosition(pos.x, pos.y)
                        delete(pos)
                elseif e:getEventCode() == EVENT_MOUSEDOWN then
                        self.image:setColor(1,0,0,1)
                elseif e:getEventCode() == EVENT_MOUSEUP then
                        self.image:setColor(1,1,1,1)
                end
        end
end

screen = Screen()
image = ScreenImage("polycode_logo.png")
image:setPositionMode(POSITION_CENTER)
screen:addChild(image)

mouseImage = MouseImage(image)


Services.Core:getInput():addEventListener(mouseImage, EVENT_MOUSEMOVE)
Services.Core:getInput():addEventListener(mouseImage, EVENT_MOUSEDOWN)
Services.Core:getInput():addEventListener(mouseImage, EVENT_MOUSEUP)
