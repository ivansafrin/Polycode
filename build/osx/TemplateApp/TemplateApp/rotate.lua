
class "Rotator"

function Rotator:Rotator(entity)
	self.entity = entity
    self.speed = math.random()
end

function Rotator:update(elapsed)
    self.entity:Roll(elapsed * 100.0)
end

return Rotator