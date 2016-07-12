class "BinaryObjectWriter"


function BinaryObjectWriter:addKey(key)
	local retVal = Polycode.BinaryObjectWriter_addKey(self.__ptr, key)
	return retVal
end

function BinaryObjectWriter:getKeyIndex(key)
	local retVal = Polycode.BinaryObjectWriter_getKeyIndex(self.__ptr, key)
	return retVal
end

function BinaryObjectWriter:writeToFile(fileName)
	local retVal = Polycode.BinaryObjectWriter_writeToFile(self.__ptr, fileName)
	return retVal
end

function BinaryObjectWriter:__delete()
	if self then Polycode.delete_BinaryObjectWriter(self.__ptr) end
end
