class "Data"

function Data:Data()
	if self.__ptr == nil then
		self.__ptr = Polycore.Data()
	end
end

function Data:loadFromFile(fileName)
	return Polycore.Data_loadFromFile(self.__ptr, fileName)
end

function Data:getAsString(encoding)
	return Polycore.Data_getAsString(self.__ptr, encoding)
end

function Data:setFromString(str, encoding)
	return Polycore.Data_setFromString(self.__ptr, str, encoding)
end

function Data:saveToFile(fileName)
	return Polycore.Data_saveToFile(self.__ptr, fileName)
end

function Data:getData()
	return Polycore.Data_getData(self.__ptr)
end

