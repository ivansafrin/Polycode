-- test script

Rotator = {}
Rotator.__index = Rotator

function Rotator.init(entity)
	local rotator = {}
	rotator.entity = entity
	return rotator
end

function Rotator:update(elapsed)
	Entity.Roll(self.entity, elapsed * 100.0)
end

return Rotator