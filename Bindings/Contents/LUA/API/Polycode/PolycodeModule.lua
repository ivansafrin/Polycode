class "PolycodeModule"



TYPE_GENERIC = 0
TYPE_SHADER = 0




function PolycodeModule:PolycodeModule(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.PolycodeModule(unpack(arg))
	end
end

function PolycodeModule:getType()
	local retVal =  Polycore.PolycodeModule_getType(self.__ptr)
	return retVal
end

