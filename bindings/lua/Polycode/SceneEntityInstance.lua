require "Polycode/Entity"

class "SceneEntityInstance" (Entity)


function SceneEntityInstance:__getvar(name)
	if name == "cloneUsingReload" then
		return Polycode.SceneEntityInstance_get_cloneUsingReload(self.__ptr)
	elseif name == "fileName" then
		return Polycode.SceneEntityInstance_get_fileName(self.__ptr)
	end
	if Entity["__getvar"] ~= nil then
		return Entity.__getvar(self, name)
	end
end

function SceneEntityInstance:__setvar(name,value)
	if name == "cloneUsingReload" then
		Polycode.SceneEntityInstance_set_cloneUsingReload(self.__ptr, value)
		return true
	elseif name == "fileName" then
		Polycode.SceneEntityInstance_set_fileName(self.__ptr, value)
		return true
	end
	if Entity["__setvar"] ~= nil then
		return Entity.__setvar(self, name, value)
	else
		return false
	end
end
function SceneEntityInstance:reloadEntityInstance()
	local retVal =  Polycode.SceneEntityInstance_reloadEntityInstance(self.__ptr)
end

function SceneEntityInstance:clearInstance()
	local retVal =  Polycode.SceneEntityInstance_clearInstance(self.__ptr)
end

function SceneEntityInstance:loadFromFile(fileName)
	local retVal = Polycode.SceneEntityInstance_loadFromFile(self.__ptr, fileName)
	return retVal
end

function SceneEntityInstance:getNumLinkedResourePools()
	local retVal =  Polycode.SceneEntityInstance_getNumLinkedResourePools(self.__ptr)
	return retVal
end

function SceneEntityInstance:getResourceEntry()
	local retVal =  Polycode.SceneEntityInstance_getResourceEntry(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<SceneEntityInstanceResourceEntry>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:hasLayerID(layerID)
	local retVal = Polycode.SceneEntityInstance_hasLayerID(self.__ptr, layerID.__ptr)
	return retVal
end

function SceneEntityInstance:getNumLayers()
	local retVal =  Polycode.SceneEntityInstance_getNumLayers(self.__ptr)
	return retVal
end

function SceneEntityInstance:getFileName()
	local retVal =  Polycode.SceneEntityInstance_getFileName(self.__ptr)
	return retVal
end

function SceneEntityInstance:__delete()
	if self then Polycode.delete_SceneEntityInstance(self.__ptr) end
end
