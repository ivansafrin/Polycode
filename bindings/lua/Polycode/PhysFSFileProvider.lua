class "PhysFSFileProvider"


function PhysFSFileProvider:PhysFSFileProvider(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.PhysFSFileProvider(unpack(arg))
	end
end

function PhysFSFileProvider:openFile(fileName, opts)
	local retVal = Polycode.PhysFSFileProvider_openFile(self.__ptr, fileName, opts)
	if retVal == nil then return nil end
	local __c = _G["CoreFile"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function PhysFSFileProvider:closeFile(file)
	local retVal = Polycode.PhysFSFileProvider_closeFile(self.__ptr, file.__ptr)
end

function PhysFSFileProvider:parseFolder(pathString, showHidden, targetVector)
	local retVal = Polycode.PhysFSFileProvider_parseFolder(self.__ptr, pathString, showHidden, targetVector.__ptr)
	return retVal
end

function PhysFSFileProvider:addSource(source)
	local retVal = Polycode.PhysFSFileProvider_addSource(self.__ptr, source)
end

function PhysFSFileProvider:removeSource(source)
	local retVal = Polycode.PhysFSFileProvider_removeSource(self.__ptr, source)
end

function PhysFSFileProvider:__delete()
	if self then Polycode.delete_PhysFSFileProvider(self.__ptr) end
end
