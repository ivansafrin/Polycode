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
		self.__ptr = Polycode.ResourceManager(unpack(arg))
	end
end

function ResourceManager:getNumResourceLoaders()
	local retVal =  Polycode.ResourceManager_getNumResourceLoaders(self.__ptr)
	return retVal
end

function ResourceManager:getResources(resourceType)
	local retVal = Polycode.ResourceManager_getResources(self.__ptr, resourceType)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["shared_ptr<Resource"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function ResourceManager:removeResource(resource)
	local retVal = Polycode.ResourceManager_removeResource(self.__ptr, resource.__ptr)
end

function ResourceManager:Update(elapsed)
	local retVal = Polycode.ResourceManager_Update(self.__ptr, elapsed)
end

function ResourceManager:__delete()
	if self then Polycode.delete_ResourceManager(self.__ptr) end
end
