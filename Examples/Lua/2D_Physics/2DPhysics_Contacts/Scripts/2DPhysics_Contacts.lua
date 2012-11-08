class "ImpactNoise" (EventHandler)

function ImpactNoise:ImpactNoise()
        self.collisionSound = Sound("Resources/collision.wav")
        EventHandler.EventHandler(self)
end

function ImpactNoise:handleEvent(e)
        if e:getDispatcher() == screen then
                local pe = PhysicsScreenEvent(e)
                if e:getEventCode() == PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION then
                        if pe.impactStrength > 5 then
                                self.collisionSound:Play()
                        end
                end
        end
end

screen = PhysicsScreen(10, 60)
shape = ScreenShape(ScreenShape.SHAPE_RECT, 600,30)
shape:setColor(0.0,0.0,0.0,1.0)
shape:setPosition(640/2, 400)
screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, true)

for i=0,50 do
        shape = ScreenShape(ScreenShape.SHAPE_RECT, 20,5)
        shape:setRotation(random(360))
        shape:setPosition(random(640), random(300))
        screen:addPhysicsChild(shape, PhysicsScreenEntity.ENTITY_RECT, false)
end


noiseMaker = ImpactNoise()

screen:addEventListener(noiseMaker, PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION)
