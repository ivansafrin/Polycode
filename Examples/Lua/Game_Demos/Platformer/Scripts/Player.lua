
class "Player"

function Player:Player(screen, playerEntity)
	self.screen = screen
	self.playerEntity = playerEntity
	self.playerPhysics = screen:trackPhysicsChild(playerEntity, PhysicsScreenEntity.ENTITY_TRIPLE_CIRCLE, false, 0.0, 1, 0, false, true, -1)
	self.playerSprite = safe_cast(playerEntity:getEntityById("playerSprite", true), ScreenSprite)
	self.groundSensor = safe_cast(playerEntity:getEntityById("groundSensor", true), ScreenShape)
	self.playerVelocity = 0.0
	self.jumping = true
	self.numCoins = 0
	self.dead = false
	self.deadCounter = 0
	self.jumpSound = Sound("Resources/sounds/jump.wav")
	self.dieSound = Sound("Resources/sounds/die.wav")
end

function Player:Jump()
	if self.jumping == false and self.dead == false then
		self.playerPhysics:applyImpulse(0.0, -80.0)
		self.jumpSound:Play()
	end
end
 
function Player:Die()
	if self.dead == true then return end
	self.playerSprite.rotation.roll = -90
	self.playerSprite.position.y = 10
	self.playerPhysics:applyImpulse(0.0, -80.0)
	self.dead = true
	self.dieSound:Play()
end

function Player:Update(elapsed)

	if self.playerEntity.position.y > 400 then 
		self:Die()
	end

	if self.dead then
		self.deadCounter = self.deadCounter + elapsed
		self.playerSprite:playAnimation("idle", 0, false)
		self.playerPhysics:setVelocityX(0)
		return
	end

	if self.screen:isEntityColliding(self.groundSensor) then
		self.jumping = false
	else
		self.jumping = true
	end

	if Services.Input:getKeyState(KEY_LEFT) then
		self.playerVelocity = -7.2
		self.playerSprite.scale.x = -1
	elseif Services.Input:getKeyState(KEY_RIGHT) then
		self.playerVelocity = 7.2
		self.playerSprite.scale.x = 1
	else
		self.playerVelocity = 0.0
	end

	self.playerPhysics:setVelocityX(self.playerVelocity)

	if self.jumping == true then
		self.playerSprite:playAnimation("jump", 0, false)
	else
		if self.playerVelocity == 0.0 then
			self.playerSprite:playAnimation("idle", 0, false)
		else
			self.playerSprite:playAnimation("walk", 0, false)
		end
	end

end