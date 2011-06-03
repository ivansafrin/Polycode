require "Polycode/SceneEntity"

class "SceneSound" (SceneEntity)







function SceneSound:SceneSound(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneEntity" then
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
		self.__ptr = Polycore.SceneSound(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneSound:Update()
	local retVal =  Polycore.SceneSound_Update(self.__ptr)
end

function SceneSound:getSound()
	local retVal =  Polycore.SceneSound_getSound(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Sound("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function SceneSound:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneSound(self.__ptr)
end
