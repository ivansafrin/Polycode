class "ResourceManager"







function ResourceManager:ResourceManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ResourceManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ResourceManager:addResource(resource)
	local retVal = Polycore.ResourceManager_addResource(self.__ptr, resource.__ptr)
end

function ResourceManager:addDirResource(dirPath, recursive)
	local retVal = Polycore.ResourceManager_addDirResource(self.__ptr, dirPath, recursive)
end

function ResourceManager:addArchive(zipPath)
	local retVal = Polycore.ResourceManager_addArchive(self.__ptr, zipPath)
end

function ResourceManager:readFile(fileName)
	local retVal = Polycore.ResourceManager_readFile(self.__ptr, fileName)
	return retVal
end

function ResourceManager:parseTextures(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseTextures(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseMaterials(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseMaterials(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseShaders(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseShaders(self.__ptr, dirPath, recursive)
end

function ResourceManager:parsePrograms(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parsePrograms(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseCubemaps(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseCubemaps(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseOthers(dirPath, recursive)
	local retVal = Polycore.ResourceManager_parseOthers(self.__ptr, dirPath, recursive)
end

function ResourceManager:getResource(resourceType, resourceName)
	local retVal = Polycore.ResourceManager_getResource(self.__ptr, resourceType, resourceName)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Resource("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ResourceManager:addShaderModule(module)
	local retVal = Polycore.ResourceManager_addShaderModule(self.__ptr, module.__ptr)
end



function ResourceManager:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ResourceManager(self.__ptr)
end
