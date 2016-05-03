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
		self.__ptr = Polycore.Data(unpack(arg))
	end
end

function Data:loadFromFile(fileName)
	local retVal = Polycore.Data_loadFromFile(self.__ptr, fileName)
	return retVal
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
	if retVal == nil then return nil end
	local __c = _G["char"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Data:__delete()
	if self then Polycore.delete_Data(self.__ptr) end
end
