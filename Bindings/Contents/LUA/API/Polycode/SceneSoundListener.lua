require "Polycode/SceneEntity"

class "SceneSoundListener" (SceneEntity)







function SceneSoundListener:SceneSoundListener(...)
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
		self.__ptr = Polycore.SceneSoundListener(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SceneSoundListener:Update()
	local retVal =  Polycore.SceneSoundListener_Update(self.__ptr)
end



function SceneSoundListener:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SceneSoundListener(self.__ptr)
end
