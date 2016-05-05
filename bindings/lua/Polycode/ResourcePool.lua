require "Polycode/EventDispatcher"

class "ResourcePool" (EventDispatcher)


function ResourcePool:__getvar(name)
	if name == "reloadResourcesOnModify" then
		return Polycode.ResourcePool_get_reloadResourcesOnModify(self.__ptr)
	elseif name == "dispatchChangeEvents" then
		return Polycode.ResourcePool_get_dispatchChangeEvents(self.__ptr)
	elseif name == "resourceSubscribers" then
		return Polycode.ResourcePool_get_resourceSubscribers(self.__ptr)
	elseif name == "deleteOnUnsubscribe" then
		return Polycode.ResourcePool_get_deleteOnUnsubscribe(self.__ptr)
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end

function ResourcePool:__setvar(name,value)
	if name == "reloadResourcesOnModify" then
		Polycode.ResourcePool_set_reloadResourcesOnModify(self.__ptr, value)
		return true
	elseif name == "dispatchChangeEvents" then
		Polycode.ResourcePool_set_dispatchChangeEvents(self.__ptr, value)
		return true
	elseif name == "resourceSubscribers" then
		Polycode.ResourcePool_set_resourceSubscribers(self.__ptr, value)
		return true
	elseif name == "deleteOnUnsubscribe" then
		Polycode.ResourcePool_set_deleteOnUnsubscribe(self.__ptr, value)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end
function ResourcePool:ResourcePool(...)
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
		self.__ptr = Polycode.ResourcePool(unpack(arg))
	end
end

function ResourcePool:setFallbackPool(pool)
	local retVal = Polycode.ResourcePool_setFallbackPool(self.__ptr, pool.__ptr)
end

function ResourcePool:addResource(resource)
	local retVal = Polycode.ResourcePool_addResource(self.__ptr, resource.__ptr)
end

function ResourcePool:removeResource(resource)
	local retVal = Polycode.ResourcePool_removeResource(self.__ptr, resource.__ptr)
end

function ResourcePool:hasResource(resource)
	local retVal = Polycode.ResourcePool_hasResource(self.__ptr, resource.__ptr)
	return retVal
end

function ResourcePool:loadResourcesFromFolder(folder, recursive)
	local retVal = Polycode.ResourcePool_loadResourcesFromFolder(self.__ptr, folder, recursive)
end

function ResourcePool:loadResource(path)
	local retVal = Polycode.ResourcePool_loadResource(self.__ptr, path)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourcePool:loadResourceWithName(path, name)
	local retVal = Polycode.ResourcePool_loadResourceWithName(self.__ptr, path, name)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourcePool:getResource(resourceType, resourceName)
	local retVal = Polycode.ResourcePool_getResource(self.__ptr, resourceType, resourceName)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourcePool:getName()
	local retVal =  Polycode.ResourcePool_getName(self.__ptr)
	return retVal
end

function ResourcePool:setName(name)
	local retVal = Polycode.ResourcePool_setName(self.__ptr, name)
end

function ResourcePool:getResourceByPath(resourcePath)
	local retVal = Polycode.ResourcePool_getResourceByPath(self.__ptr, resourcePath)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ResourcePool:Update(elapsed)
	local retVal = Polycode.ResourcePool_Update(self.__ptr, elapsed)
end

function ResourcePool:getResources(resourceType)
	local retVal = Polycode.ResourcePool_getResources(self.__ptr, resourceType)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Resource"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function ResourcePool:checkForChangedFiles()
	local retVal =  Polycode.ResourcePool_checkForChangedFiles(self.__ptr)
end

function ResourcePool:__delete()
	if self then Polycode.delete_ResourcePool(self.__ptr) end
end
