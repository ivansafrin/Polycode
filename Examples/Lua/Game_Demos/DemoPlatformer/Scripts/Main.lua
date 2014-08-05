
require "Scripts/Player"
require "Scripts/Alien"

music = Sound("Resources/music/level1.ogg")
music:Play(true)

Services.MaterialManager.premultiplyAlphaOnLoad = true

scene = PhysicsScene2D(1.0, 60)
scene:setGravity(Vector2(0.0, -30.0))

scene:getDefaultCamera():setOrthoSize(0, 14)

level = SceneEntityInstance(scene, "Resources/entities/level.entity")
scene:addChild(level)

playerBody = level:getEntityById("player", true)
player = Player(scene, playerBody)

alienBodies = level:getEntitiesByTag("alien", false)
aliens = {}
for i=1,count(alienBodies) do
	local alien = Alien(scene, alienBodies[i], player)
	aliens[i] = alien	
	alien:Respawn()
end

shootTimer = 0.0


platforms = level:getEntitiesByTag("platform", false)
for i=1,count(platforms) do
		scene:trackPhysicsChild(platforms[i], PhysicsScene2DEntity.ENTITY_RECT, true, 2.0, 1, 0, false, false)
end

shots = level:getEntitiesByTag("shot", false)
shotDirections = {}
for i=1,count(shots) do
	shots[i] = safe_cast(shots[i], SceneSprite)
	scene:trackCollisionChild(shots[i], PhysicsScene2DEntity.ENTITY_RECT, -1)
	shots[i].backfaceCulled = false
	shotDirections[i] = 0.0
end
shotIndex = 1

function onKeyDown(key)
	player:onKeyDown(key)
end

function onCollision(t, event)
	local physicsEvent = safe_cast(event, PhysicsScene2DEvent)

	for i=1,count(shots) do
		if physicsEvent.entity2 == shots[i] or physicsEvent.entity1 == shots[i] then
			for j=1,count(aliens) do
				if aliens[j].body == physicsEvent.entity1 or aliens[j].body == physicsEvent.entity2 then
					aliens[j].dead = true
					if shots[i]:getPosition().x > aliens[j].body:getPosition().x then
						aliens[j].physicsBody:applyImpulse(-230.0, 0.0)
					else
						aliens[j].physicsBody:applyImpulse(230.0, 0.0)
					end
				end
			end
			shots[i]:setPositionX(1000.0)						
		end
	end
end

scene:addEventListener(nil, onCollision, PhysicsScene2DEvent.EVENT_NEW_SHAPE_COLLISION)

function Update(elapsed)

	player:Update(elapsed)

	shootTimer = shootTimer + elapsed
	if Services.Input:getKeyState(KEY_x) then
		if shootTimer > 0.15 then
			shotDirections[shotIndex] = player:Shoot(shots[shotIndex])
			shotIndex = shotIndex +1
			if shotIndex > count(shots) then shotIndex = 1 end
			shootTimer = 0.0
		end
	else
		shootTimer = 100.0
	end
end

function fixedUpdate()
	local elapsed = Services.Core:getFixedTimestep()
	player:fixedUpdate(elapsed)

	for i=1,count(aliens) do
		aliens[i]:Update(elapsed)
	end

	for i=1,count(shots) do
		shots[i]:setRoll(shotDirections[i])
		shots[i]:Translate(elapsed * 18.0 * cos(shotDirections[i] * 0.0174532925), elapsed * 18.0 * sin(shotDirections[i] * 0.0174532925), 0.0)
	end

end