--
--	This example demonstrates entity hierarchy by simulating a simple solar system.
--	Since entity transformations are always relative to the entity's parent
--	so the moon's rotation takes places around the planet, which is its parent.
--

scene = Scene(Scene.SCENE_2D)

sun = ScenePrimitive(ScenePrimitive.TYPE_CIRCLE, 0.2,0.2, 30)
sun:setColor(0.9, 0.8, 0, 1) 
sun.colorAffectsChildren = false		
scene:addChild(sun)
	
planet = ScenePrimitive(ScenePrimitive.TYPE_CIRCLE, 0.1,0.1, 30)
planet:setPosition(0.3,0)
planet:setColor(0.2, 0.8, 0, 1) 
planet.colorAffectsChildren = false
sun:addChild(planet)

moon = ScenePrimitive(ScenePrimitive.TYPE_CIRCLE, 0.05, 0.05, 30)
moon:setPosition(0.1,0)
moon:setColor(1, 1, 0.6, 1)
planet:addChild(moon)


planetRotation = 0
moonRotation = 0

function Update(elapsed)
        planetRotation = planetRotation + elapsed
        moonRotation = moonRotation + (elapsed * 6)
		planet:setPosition(cos(planetRotation)*0.3, sin(planetRotation)*0.3)
		moon:setPosition(cos(moonRotation)*0.1, sin(moonRotation)*0.1)
end
