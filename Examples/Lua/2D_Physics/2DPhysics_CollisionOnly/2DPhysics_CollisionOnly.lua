class "Detector" (EventHandler)

function Detector:Detector(shape)
        self.shape = shape
        self:EventHandler()
end

function Detector:handleEvent(e)
        if e:getDispatcher() == screen then
                local pe = PhysicsScreenEvent(e)
                if e:getEventCode() == EVENT_NEW_SHAPE_COLLISION then
                        if pe:getFirstEntity() == self.shape or pe:getSecondEntity() == self.shape then
                                pe:getFirstEntity():setColor(1.0, 0.0, 0.0, 1.0)
                                pe:getSecondEntity():setColor(1.0, 0.0, 0.0, 1.0)
                        end
                elseif e:getEventCode() == EVENT_END_SHAPE_COLLISION then
                        pe:getFirstEntity():setColor(1.0, 1.0, 1.0, 1.0)
                        pe:getSecondEntity():setColor(1.0, 1.0, 1.0, 1.0)
                end
        end
end

screen = PhysicsScreen(10, 60)

checkShape = ScreenShape(SHAPE_RECT, 90,10)
screen:addCollisionChild(checkShape, ENTITY_RECT)

for i=0,50 do
        shape = ScreenShape(SHAPE_RECT, 30,15)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(480))
        screen:addCollisionChild(shape, ENTITY_RECT)
end

detector = Detector(checkShape)
screen:addEventListener(detector, EVENT_NEW_SHAPE_COLLISION)
screen:addEventListener(detector, EVENT_END_SHAPE_COLLISION)

function Update(e)
        local mouse = Services.Core:getInput():getMousePosition()
        checkShape:setPosition(mouse.x, mouse.y)
        checkShape:setRotation(checkShape:getRotation() + (e*100))
        delete(mouse)
end
