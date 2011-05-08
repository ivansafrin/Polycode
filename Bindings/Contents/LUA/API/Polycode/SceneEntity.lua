require "Polycode/Entity"

class "SceneEntity" (Entity)







function SceneEntity:SceneEntity(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Entity" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneEntity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneEntity:testMouseCollision(x, y)
	local retVal = Polycore.SceneEntity_testMouseCollision(self.__ptr, x, y)
	return retVal
end



function SceneEntity:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneEntity(self.__ptr)
end
