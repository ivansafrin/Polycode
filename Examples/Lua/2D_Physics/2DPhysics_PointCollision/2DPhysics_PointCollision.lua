screen = PhysicsScreen(10, 60)
lastEntity = nil

for i=0,50 do
        shape = ScreenShape(SHAPE_RECT, 30,15)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(480))
        screen:addCollisionChild(shape, ENTITY_RECT)
end

function Update(e)
        if lastEntity ~= nil then lastEntity:setColor(1.0,1.0,1.0,1.0) end
        local mouse = Services.Core:getInput():getMousePosition()
        local entity = screen:getEntityAtPosition(mouse.x, mouse.y)
        if entity ~= nil then
                entity:setColor(1.0, 0.0, 0.0, 1.0)
                lastEntity = entity
        end
        delete(mouse)
end
