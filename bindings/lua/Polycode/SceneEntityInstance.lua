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
function SceneEntityInstance:SceneEntityInstance(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.SceneEntityInstance(unpack(arg))
	end
end

function SceneEntityInstance:BlankSceneEntityInstance(parentScene)
	local retVal = Polycode.SceneEntityInstance_BlankSceneEntityInstance(self.__ptr, parentScene.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneEntityInstance"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:Clone(deepClone, ignoreEditorOnly)
	local retVal = Polycode.SceneEntityInstance_Clone(self.__ptr, deepClone, ignoreEditorOnly)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:applyClone(clone, deepClone, ignoreEditorOnly)
	local retVal = Polycode.SceneEntityInstance_applyClone(self.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
end

function SceneEntityInstance:reloadEntityInstance()
	local retVal =  Polycode.SceneEntityInstance_reloadEntityInstance(self.__ptr)
end

function SceneEntityInstance:clearInstance()
	local retVal =  Polycode.SceneEntityInstance_clearInstance(self.__ptr)
end

function SceneEntityInstance:parseObjectIntoCurve(entry, curve)
	local retVal = Polycode.SceneEntityInstance_parseObjectIntoCurve(self.__ptr, entry.__ptr, curve.__ptr)
end

function SceneEntityInstance:loadObjectEntryIntoEntity(entry, targetEntity, entityFileVersion)
	local retVal = Polycode.SceneEntityInstance_loadObjectEntryIntoEntity(self.__ptr, entry.__ptr, targetEntity.__ptr, entityFileVersion)
	if retVal == nil then return nil end
	local __c = _G["Entity"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:loadFromFile(fileName)
	local retVal = Polycode.SceneEntityInstance_loadFromFile(self.__ptr, fileName)
	return retVal
end

function SceneEntityInstance:applySceneMesh(entry, sceneMesh)
	local retVal = Polycode.SceneEntityInstance_applySceneMesh(self.__ptr, entry.__ptr, sceneMesh.__ptr)
end

function SceneEntityInstance:linkResourcePool(pool)
	local retVal = Polycode.SceneEntityInstance_linkResourcePool(self.__ptr, pool.__ptr)
end

function SceneEntityInstance:getNumLinkedResourePools()
	local retVal =  Polycode.SceneEntityInstance_getNumLinkedResourePools(self.__ptr)
	return retVal
end

function SceneEntityInstance:getLinkedResourcePoolAtIndex(index)
	local retVal = Polycode.SceneEntityInstance_getLinkedResourcePoolAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ResourcePool"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:unlinkResourcePool(pool)
	local retVal = Polycode.SceneEntityInstance_unlinkResourcePool(self.__ptr, pool.__ptr)
end

function SceneEntityInstance:getResourceEntry()
	local retVal =  Polycode.SceneEntityInstance_getResourceEntry(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<SceneEntityInstanceResourceEntry>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:getTopLevelResourcePool()
	local retVal =  Polycode.SceneEntityInstance_getTopLevelResourcePool(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ResourcePool"]("__skip_ptr__")
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

function SceneEntityInstance:getLayerAtIndex(index)
	local retVal = Polycode.SceneEntityInstance_getLayerAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["SceneEntityInstanceLayer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:removeLayer(layer)
	local retVal = Polycode.SceneEntityInstance_removeLayer(self.__ptr, layer.__ptr)
end

function SceneEntityInstance:createNewLayer(name)
	local retVal = Polycode.SceneEntityInstance_createNewLayer(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["SceneEntityInstanceLayer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneEntityInstance:getFileName()
	local retVal =  Polycode.SceneEntityInstance_getFileName(self.__ptr)
	return retVal
end

function SceneEntityInstance:__delete()
	if self then Polycode.delete_SceneEntityInstance(self.__ptr) end
end
