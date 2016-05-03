
class "Rotator"

function Rotator:Rotator(entity)
	self.entity = entity
end

function Rotator:update(elapsed)
    self.entity:Roll(elapsed * 100.0)
end

return Rotator