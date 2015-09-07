
class "Alien"

function Alien:Alien(scene, alienBody ,player)
	self.scene = scene
	self.body = alienBody
	self.physicsBody = scene:trackPhysicsChild(alienBody, PhysicsScene2DEntity.ENTITY_CIRCLE, false, 1.0, 40.0, 0.5, false, true)
	self.dead = false
	self.player = player
	self.timeSinceDead = 0.0
	self.targetPosition = Vector3(0.0, 0.0, 0.0)
end

function Alien:Think(elapsed)

	local direction = Vector3(player.playerBody:getPosition().x - self.targetPosition.x, player.playerBody:getPosition().y - self.targetPosition.y, 0.0)
	direction:Normalize()

	self.targetPosition.x  = self.targetPosition.x + (direction.x * elapsed * 1.5)
	self.targetPosition.y  = self.targetPosition.y + (direction.y * elapsed * 1.5)
	
	if self.targetPosition.y > self.body:getPosition().y then
		self.physicsBody:setVelocityY(5.0)
	else
		self.physicsBody:setVelocityY(0.1)
	end

	if self.targetPosition.x > self.body:getPosition().x then
		self.physicsBody:setVelocityX(5.0)
	else
		self.physicsBody:setVelocityX(-5.0)
	end
end

function Alien:Respawn()
	self.timeSinceDead = 0.0
	self.dead = false

	local respawnAngle = random(pi * 2.0)
	local respawnDistance = 20.0
	self.physicsBody:setTransform(Vector2(cos(respawnAngle) * respawnDistance, sin(respawnAngle) * respawnDistance), 0.0)
end

function Alien:Update(elapsed)
	if self.dead == false then
		self:Think(elapsed)
	else
		self.timeSinceDead = self.timeSinceDead + elapsed
		if self.timeSinceDead > 2.0 then
			self:Respawn()
		end
	end
end