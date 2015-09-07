
class "Player"

function Player:Player(scene, playerBody)
	self.scene = scene
	self.playerBody = playerBody
	self.top = safe_cast(playerBody:getEntityById("top", true), SceneSprite)
	self.legs = safe_cast(playerBody:getEntityById("legs", true), SceneSprite)
	self.groundSensor = playerBody:getEntityById("groundSensor", true)
	scene:trackCollisionChild(self.groundSensor, PhysicsScene2DEntity.ENTITY_RECT, -1)
	self.topSinValue = 0.0
	self.physicsBody = scene:trackPhysicsChild(playerBody, PhysicsScene2DEntity.ENTITY_TRIPLE_CIRCLE, false, 0.0, 10, 0, false, true, -1)
	self.legs.backfaceCulled = false
	self.top.backfaceCulled = false
	self.touchingGround = false
	self.jumpsLeft = 1
	self.shootSound = Sound("Resources/sounds/shot.ogg")
	self.jumpSound = Sound("Resources/sounds/jump.ogg")
	self.shootAngle = 0.0
	self.moveDir = 0.0
end

function Player:onKeyDown(key)
	if key == KEY_z and self.jumpsLeft > 0 then
		self.physicsBody:setVelocityY(0.0)
		self.physicsBody:applyImpulse(0.0, 140.0)
		self.jumpsLeft = self.jumpsLeft -1
		self.jumpSound:Play()
	end
end

function Player:Shoot(shot)
	shot:setPosition(self.playerBody:getPosition().x + (0.25  * cos(self.shootAngle * 0.0174532925))-0.1, self.playerBody:getPosition().y + (0.25 * sin(self.shootAngle * 0.0174532925)) + 0.3, self.playerBody:getPosition().z)
	self.shootSound:Play()
	return self.shootAngle
end

function Player:Update(elapsed)
	self.topSinValue = self.topSinValue + elapsed * 20.0
	self.top:setPositionY(0.06090 + sin(self.topSinValue) * 0.025)

	self.moveDir = 0.0

	if Services.Input:getKeyState(KEY_LEFT) then
		self.moveDir = -1.0
		self.playerBody:setScaleX(-1.0)
	elseif Services.Input:getKeyState(KEY_RIGHT) then
		self.moveDir = 1.0
		self.playerBody:setScaleX(1.0)
	end

	if Services.Input:getKeyState(KEY_UP) then
		self.top:setRoll(45)
		if self.playerBody:getScale().x > 0.0 then
			self.shootAngle = 45
		else
			self.shootAngle = 135
			end
	elseif Services.Input:getKeyState(KEY_DOWN) then
		self.top:setRoll(-45)
		if self.playerBody:getScale().x > 0.0 then
			self.shootAngle = -45
		else
			self.shootAngle = -135
		end
	else
		self.top:setRoll(0)
		if self.playerBody:getScale().x > 0.0 then
			self.shootAngle = 0
		else
			self.shootAngle = 180
		end
	end

	if self.scene:isEntityColliding(self.groundSensor) then
		self.touchingGround = true
		self.jumpsLeft = 1
	else
		self.touchingGround = false
		self.legs:setSpriteStateByName("jumping", 0, false)
	end

	if self.touchingGround == true then
		if self.moveDir == 0.0 then
			self.legs:setSpriteStateByName("idle", 0, false)
		else
			self.legs:setSpriteStateByName("running", 0, false)
		end
	end
		
	self.physicsBody:setVelocityX(self.moveDir * 5.0)
end

function Player:fixedUpdate(elapsed)

	if self.playerBody:getPosition().y < -8.0 then
		self.physicsBody:setTransform(Vector2(self.playerBody:getPosition().x, 8.0), 0.0)
	end

	if self.playerBody:getPosition().x < -12.0 then
		self.physicsBody:setTransform(Vector2(12, self.playerBody:getPosition().y), 0.0)
	end

	if self.playerBody:getPosition().x > 12.0 then
		self.physicsBody:setTransform(Vector2(-12, self.playerBody:getPosition().y), 0.0)
	end
end