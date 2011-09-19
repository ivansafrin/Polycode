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
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Data:loadFromFile(fileName)
	local retVal = Polycore.Data_loadFromFile(self.__ptr, fileName.__ptr)
end

function Data:getAsString(encoding)
	local retVal = Polycore.Data_getAsString(self.__ptr, encoding)
	return retVal
end

function Data:setFromString(str, encoding)
	local retVal = Polycore.Data_setFromString(self.__ptr, str.__ptr, encoding)
end

function Data:saveToFile(fileName)
	local retVal = Polycore.Data_saveToFile(self.__ptr, fileName.__ptr)
	return retVal
end

function Data:getData()
	local retVal =  Polycore.Data_getData(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = char("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Data:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Data(self.__ptr)
end
