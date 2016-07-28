class "Data"


function Data:Data(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Data(unpack(arg))
	end
end

function Data:getAsString(encoding)
	local retVal = Polycode.Data_getAsString(self.__ptr, encoding)
	return retVal
end

function Data:setFromString(str, encoding)
	local retVal = Polycode.Data_setFromString(self.__ptr, str, encoding)
end

function Data:__delete()
	if self then Polycode.delete_Data(self.__ptr) end
end
