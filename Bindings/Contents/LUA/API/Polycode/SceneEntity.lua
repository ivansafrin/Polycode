require "Polycode/Entity"

class "SceneEntity" (Entity)

function SceneEntity:SceneEntity()
	if self.__ptr == nil then
		self.__ptr = Polycore.SceneEntity()
	end
end

function SceneEntity:testMouseCollision(x, y)
	return Polycore.SceneEntity_testMouseCollision(self.__ptr, x, y)
end

