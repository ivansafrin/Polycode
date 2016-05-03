require "Polycode/EventDispatcher"

class "ResourceManager" (EventDispatcher)







function ResourceManager:ResourceManager(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "EventDispatcher" then
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
		self.__ptr = Polycore.ResourceManager(unpack(arg))
	end
end

function ResourceManager:getGlobalPool()
	local retVal =  Polycore.ResourceManager_getGlobalPool(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ResourcePool"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:getResourcePoolByName(name)
	local retVal = Polycore.ResourceManager_getResourcePoolByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["ResourcePool"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:addResourceLoader(loader)
	local retVal = Polycore.ResourceManager_addResourceLoader(self.__ptr, loader.__ptr)
end

function ResourceManager:getResourceLoaderForExtension(extension)
	local retVal = Polycore.ResourceManager_getResourceLoaderForExtension(self.__ptr, extension)
	if retVal == nil then return nil end
	local __c = _G["ResourceLoader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:removeResourceLoader(loader)
	local retVal = Polycore.ResourceManager_removeResourceLoader(self.__ptr, loader.__ptr)
end

function ResourceManager:getNumResourceLoaders()
	local retVal =  Polycore.ResourceManager_getNumResourceLoaders(self.__ptr)
	return retVal
end

function ResourceManager:getResourceLoaderAtIndex(index)
	local retVal = Polycore.ResourceManager_getResourceLoaderAtIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ResourceLoader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourceManager:addResourcePool(pool)
	local retVal = Polycore.ResourceManager_addResourcePool(self.__ptr, pool.__ptr)
end

function ResourceManager:removeResourcePool(pool)
	local retVal = Polycore.ResourceManager_removeResourcePool(self.__ptr, pool.__ptr)
end

function ResourceManager:getResources(resourceType)
	local retVal = Polycore.ResourceManager_getResources(self.__ptr, resourceType)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Resource"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function ResourceManager:removeResource(resource)
	local retVal = Polycore.ResourceManager_removeResource(self.__ptr, resource.__ptr)
end

function ResourceManager:subscribeToResourcePool(pool)
	local retVal = Polycore.ResourceManager_subscribeToResourcePool(self.__ptr, pool.__ptr)
end

function ResourceManager:unsubscibeFromResourcePool(pool)
	local retVal = Polycore.ResourceManager_unsubscibeFromResourcePool(self.__ptr, pool.__ptr)
end

function ResourceManager:Update(elapsed)
	local retVal = Polycore.ResourceManager_Update(self.__ptr, elapsed)
end

function ResourceManager:__delete()
	if self then Polycore.delete_ResourceManager(self.__ptr) end
end
