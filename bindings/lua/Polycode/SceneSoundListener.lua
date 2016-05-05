require "Polycode/Entity"

class "SceneSoundListener" (Entity)


function SceneSoundListener:SceneSoundListener(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
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
		self.__ptr = Polycode.SceneSoundListener(unpack(arg))
	end
end

function SceneSoundListener:Update()
	local retVal =  Polycode.SceneSoundListener_Update(self.__ptr)
end

function SceneSoundListener:__delete()
	if self then Polycode.delete_SceneSoundListener(self.__ptr) end
end
