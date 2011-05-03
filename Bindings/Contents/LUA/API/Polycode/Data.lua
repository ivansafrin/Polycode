class "Data"







function Data:Data(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Data(unpack(arg))
	end
end

function Data:loadFromFile(fileName)
	local retVal = Polycore.Data_loadFromFile(self.__ptr, fileName)
end

function Data:getAsString(encoding)
	local retVal = Polycore.Data_getAsString(self.__ptr, encoding)
	return retVal
end

function Data:setFromString(str, encoding)
	local retVal = Polycore.Data_setFromString(self.__ptr, str, encoding)
end

function Data:saveToFile(fileName)
	local retVal = Polycore.Data_saveToFile(self.__ptr, fileName)
	return retVal
end

function Data:getData()
	local retVal =  Polycore.Data_getData(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

