
require "Scripts/Player"
require "Scripts/Fly"
require "Scripts/HUD"

class "Level"

function Level:Level(levelFile)
	self.loaded = false
	self.levelFile = levelFile

	self.coinSound = Sound("Resources/sounds/coin.wav")
	self.buttonSound = Sound("Resources/sounds/button.wav")

	self:initLevel()
end

function Level:initLevel()

	self.backgroundScreen = Screen()
	self.backgroundScreen:setNormalizedCoordinates(true, 720)
	for i=0,4 do
		self.background = ScreenImage("Resources/images/background.png")
		self.backgroundScreen:addChild(self.background)
		self.background.position.x =  -450 + (1280 * i)
		self.background.position.y = -720/2
	end

	self.screen = PhysicsScreen(40, 60.0)

	self.screen:setGravity(Vector2(0.0, 80))
	self.screen:setNormalizedCoordinates(true, 720)
	self.level = ScreenEntityInstance("Resources/levels/"..self.levelFile..".entity2d")
	self.screen:addChild(self.level)
	self.playerEntity = self.level:getScreenEntityById("player", true)
	self.player = Player(self.screen, self.playerEntity)
	self.screen:trackCollisionChild(self.player.groundSensor, PhysicsScreenEntity.ENTITY_RECT)

	local ground_blocks = self.level:getScreenEntitiesByTag("ground", true)
	for i=1,count(ground_blocks) do
		self.screen:trackPhysicsChild(ground_blocks[i], PhysicsScreenEntity.ENTITY_RECT , true, 2.0, 1, 0, false, false)
	end

	self.coins = self.level:getScreenEntitiesByTag("coin", true)
	for i=1,count(self.coins) do
		self.screen:trackCollisionChild(self.coins[i], PhysicsScreenEntity.ENTITY_CIRCLE)
	end

	self.buttons = self.level:getScreenEntitiesByTag("button", true)
	for i=1,count(self.buttons) do
		self.screen:trackPhysicsChild(self.buttons[i], PhysicsScreenEntity.ENTITY_RECT , true, 2.0, 1, 0, false, false)
	end


	self.enemies = {}
	local flies = self.level:getScreenEntitiesByTag("fly", true)
	for i=1,count(flies) do
		self.screen:trackCollisionChild(flies[i], PhysicsScreenEntity.ENTITY_CIRCLE)
		self.enemies[count(self.enemies)+1] = Fly(flies[i])
	end	
	
	self.screen:addEventListener(self, Level.onNewCollision, PhysicsScreenEvent.EVENT_NEW_SHAPE_COLLISION)
	self.coinSinVal = 0

	self.hud = HUD()

	self.loaded = true
end

function Level:clearLevel()

	self.screen.rootEntity:setOwnsChildrenRecursive(true)
	self.backgroundScreen.rootEntity:setOwnsChildrenRecursive(true)
	self.hud.screen.rootEntity:setOwnsChildrenRecursive(true)

	safe_delete(self.player.jumpSound)
	safe_delete(self.player.dieSound              )

	safe_delete(self.screen)
	safe_delete(self.backgroundScreen)
	safe_delete(self.hud.screen)

	self.loaded = false
end

function Level:reloadLevel()
	self:clearLevel()
	self:initLevel()
end

function Level:onNewCollision(event)
	physicsEvent = safe_cast(event, PhysicsScreenEvent)
	local collidedEntity =  physicsEvent.entity2
	local firstEntity = physicsEvent.entity1

	if firstEntity == self.player.groundSensor then
		if collidedEntity:hasTag("button") then
			local buttonUp = collidedEntity:getEntityById("button_up", true)
			local buttonDown = collidedEntity:getEntityById("button_down", true)
			if buttonUp.visible == true then
				buttonUp.visible = false
				buttonDown.visible = true
				self.screen:stopTrackingChild(collidedEntity)
				collidedEntity.height = 55
				self.screen:trackPhysicsChild(collidedEntity, PhysicsScreenEntity.ENTITY_RECT , true, 2.0, 1, 0, false, false)
				self.buttonSound:Play()
				self:levelButtonPushed(collidedEntity.id)
			end	
		end
	end

	if firstEntity == self.player.playerEntity then
		if collidedEntity:hasTag("coin") and collidedEntity.visible == true then
			collidedEntity.visible = false
			self.player.numCoins = self.player.numCoins + 1
			self.coinSound:Play()
		elseif collidedEntity:hasTag("enemy") and self.player.dead == false then
			self.player:Die()
		end
	end
end

function Level:levelButtonPushed(buttonID)
	if buttonID == "level_end_button" then
		self.hud.winLabel.visible = true 
	end
end

function Level:Update(elapsed)	

	if self.player.deadCounter > 2.0 then
		self:reloadLevel()
	end

	if self.loaded == false then return end

	self.player:Update(elapsed)

	for i=1,count(self.enemies) do
		self.enemies[i]:Update(elapsed)
	end

	self.coinSinVal = self.coinSinVal + elapsed * 5.0
	for i=1,count(self.coins) do
		self.coins[i].scale.x = sin(self.coinSinVal)
	end

	local screenOffset = Vector2(-self.player.playerEntity.position.x, -self.player.playerEntity.position.y)
	if screenOffset.y < 310 then
		screenOffset.y = 310
	end
	if screenOffset.x > -650 then
		screenOffset.x = -650
	end
	self.screen:setScreenOffset(screenOffset.x, 310)
	self.backgroundScreen:setScreenOffset(screenOffset.x/3, 0.0)

	self.hud.coinsLabel:setText("COINS: "..self.player.numCoins)
end