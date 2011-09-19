class "Resource"



RESOURCE_TEXTURE = 0
RESOURCE_MATERIAL = 1
RESOURCE_SHADER = 2
RESOURCE_PROGRAM = 3
RESOURCE_MESH = 5
RESOURCE_CUBEMAP = 6




function Resource:Resource(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Resource(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Resource:getResourceName()
	local retVal =  Polycore.Resource_getResourceName(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Resource:getResourceType()
	local retVal =  Polycore.Resource_getResourceType(self.__ptr)
	return retVal
end

function Resource:setResourceName(newName)
	local retVal = Polycore.Resource_setResourceName(self.__ptr, newName.__ptr)
end

function Resource:setResourcePath(path)
	local retVal = Polycore.Resource_setResourcePath(self.__ptr, path.__ptr)
end

function Resource:getResourcePath()
	local retVal =  Polycore.Resource_getResourcePath(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Resource:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Resource(self.__ptr)
end
