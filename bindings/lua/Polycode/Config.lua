class "Config"


function Config:Config(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Config(unpack(arg))
	end
end

function Config:loadConfig(configNamespace, fileName)
	local retVal = Polycode.Config_loadConfig(self.__ptr, configNamespace, fileName)
end

function Config:saveConfig(configNamespace, fileName)
	local retVal = Polycode.Config_saveConfig(self.__ptr, configNamespace, fileName)
end

function Config:getEntry(configNamespace, key)
	local retVal = Polycode.Config_getEntry(self.__ptr, configNamespace, key)
	if retVal == nil then return nil end
	local __c = _G["ConfigEntry"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Config:setStringValue(configNamespace, key, value)
	local retVal = Polycode.Config_setStringValue(self.__ptr, configNamespace, key, value)
end

function Config:setNumericValue(configNamespace, key, value)
	local retVal = Polycode.Config_setNumericValue(self.__ptr, configNamespace, key, value)
end

function Config:getNumericValue(configNamespace, key)
	local retVal = Polycode.Config_getNumericValue(self.__ptr, configNamespace, key)
	return retVal
end

function Config:getStringValue(configNamespace, key)
	local retVal = Polycode.Config_getStringValue(self.__ptr, configNamespace, key)
	return retVal
end

function Config:setBoolValue(configNamespace, key, value)
	local retVal = Polycode.Config_setBoolValue(self.__ptr, configNamespace, key, value)
end

function Config:getBoolValue(configNamespace, key)
	local retVal = Polycode.Config_getBoolValue(self.__ptr, configNamespace, key)
	return retVal
end

function Config:__delete()
	if self then Polycode.delete_Config(self.__ptr) end
end
