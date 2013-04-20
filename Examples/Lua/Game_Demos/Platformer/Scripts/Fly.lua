
class "Fly"

function Fly:Fly(flyBody)
	self.startPosition = Vector3(flyBody.position.x, flyBody.position.y, flyBody.position.z)
	self.body = flyBody
	self.direction = -1.0
end

function Fly:Update(elapsed)
	self.body:Translate(self.direction * elapsed * 150.0, 0.0, 0.0)
	if self.startPosition:distance(self.body.position) > 100 then
		if self.body.position.x < self.startPosition.x then
			self.direction = 1.0
		else
			self.direction = -1.0
		end
	end

	self.body.scale.x = self.direction * -1.0
end

