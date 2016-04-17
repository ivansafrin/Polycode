-- test script

Rotator = {}
Rotator.__index = Rotator

function Rotator.init(entity)
	local rotator = {}
	rotator.entity = entity
	print(entity)
	return rotator
end

function Rotator:update(elapsed)
	print(self.entity)
end

return Rotator