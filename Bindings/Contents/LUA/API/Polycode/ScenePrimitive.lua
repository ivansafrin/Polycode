require "Polycode/SceneMesh"

class "ScenePrimitive" (SceneMesh)

function ScenePrimitive:ScenePrimitive(type, v1, v2, v3)
	if self.__ptr == nil then
		self.__ptr = Polycore.ScenePrimitive(type, v1, v2, v3)
	end
end

