class "Config"

function Config:Config()
	if self.__ptr == nil then
		self.__ptr = Polycore.Config()
	end
end

function Config:loadConfig(configNamespace, fileName)
	return Polycore.Config_loadConfig(self.__ptr, configNamespace, fileName)
end

function Config:saveConfig(configNamespace, fileName)
	return Polycore.Config_saveConfig(self.__ptr, configNamespace, fileName)
end

function Config:getEntry(configNamespace, key)
	return Polycore.Config_getEntry(self.__ptr, configNamespace, key)
end

function Config:setStringValue(configNamespace, key, value)
	return Polycore.Config_setStringValue(self.__ptr, configNamespace, key, value)
end

function Config:setNumericValue(configNamespace, key, value)
	return Polycore.Config_setNumericValue(self.__ptr, configNamespace, key, value)
end

function Config:getNumericValue(configNamespace, key)
	return Polycore.Config_getNumericValue(self.__ptr, configNamespace, key)
end

function Config:getStringValue(configNamespace, key)
	return Polycore.Config_getStringValue(self.__ptr, configNamespace, key)
end

