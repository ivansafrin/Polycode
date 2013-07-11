
class "HUD"

function HUD:HUD()
	self.screen = Screen()
	self.screen:setNormalizedCoordinates(true, 720)
	self.coinsLabel = ScreenLabel("COINS: 0", 48, "Sniglet")
	self.screen:addChild(self.coinsLabel)
	self.coinsLabel.position.x = -400
	self.coinsLabel.position.y = (-720/2)+10

	self.winLabel = ScreenLabel("WOW, YOU WON THE GAME!", 72, "Sniglet")
	self.screen:addChild(self.winLabel)
	self.winLabel:setPositionMode(ScreenEntity.POSITION_CENTER)
	self.winLabel.visible = false
end