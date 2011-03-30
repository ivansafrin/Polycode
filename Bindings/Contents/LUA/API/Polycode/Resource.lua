class "Resource"

function Resource:Resource(type)
	if self.__ptr == nil then
		self.__ptr = Polycore.Resource(type)
	end
end

function Resource:getResourceName()
	return Polycore.Resource_getResourceName(self.__ptr)
end

function Resource:getResourceType()
	return Polycore.Resource_getResourceType(self.__ptr)
end

function Resource:setResourceName(newName)
	return Polycore.Resource_setResourceName(self.__ptr, newName)
end

function Resource:setResourcePath(path)
	return Polycore.Resource_setResourcePath(self.__ptr, path)
end

function Resource:getResourcePath()
	return Polycore.Resource_getResourcePath(self.__ptr)
end

