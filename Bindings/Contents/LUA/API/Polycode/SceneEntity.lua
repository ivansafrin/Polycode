require "Polycode/Entity"

class "SceneEntity" (Entity)







function SceneEntity:SceneEntity(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneEntity(unpack(arg))
	end
end

function SceneEntity:testMouseCollision(x, y)
	local retVal = Polycore.SceneEntity_testMouseCollision(self.__ptr, x, y)
	return retVal
end

