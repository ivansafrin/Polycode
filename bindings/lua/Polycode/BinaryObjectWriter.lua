class "BinaryObjectWriter"


function BinaryObjectWriter:BinaryObjectWriter(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.BinaryObjectWriter(unpack(arg))
	end
end

function BinaryObjectWriter:parseKeysFromObjectEntry(entry)
	local retVal = Polycode.BinaryObjectWriter_parseKeysFromObjectEntry(self.__ptr, entry.__ptr)
end

function BinaryObjectWriter:writeEntryToFile(entry)
	local retVal = Polycode.BinaryObjectWriter_writeEntryToFile(self.__ptr, entry.__ptr)
end

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
