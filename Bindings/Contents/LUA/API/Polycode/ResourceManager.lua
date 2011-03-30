class "ResourceManager"

function ResourceManager:ResourceManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.ResourceManager()
	end
end

function ResourceManager:addResource(resource)
	return Polycore.ResourceManager_addResource(self.__ptr, resource.__ptr)
end

function ResourceManager:addDirResource(dirPath, recursive)
	return Polycore.ResourceManager_addDirResource(self.__ptr, dirPath, recursive)
end

function ResourceManager:addArchive(zipPath)
	return Polycore.ResourceManager_addArchive(self.__ptr, zipPath)
end

function ResourceManager:readFile(fileName)
	return Polycore.ResourceManager_readFile(self.__ptr, fileName)
end

function ResourceManager:parseTextures(dirPath, recursive)
	return Polycore.ResourceManager_parseTextures(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseMaterials(dirPath, recursive)
	return Polycore.ResourceManager_parseMaterials(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseShaders(dirPath, recursive)
	return Polycore.ResourceManager_parseShaders(self.__ptr, dirPath, recursive)
end

function ResourceManager:parsePrograms(dirPath, recursive)
	return Polycore.ResourceManager_parsePrograms(self.__ptr, dirPath, recursive)
end

function ResourceManager:parseCubemaps(dirPath, recursive)
	return Polycore.ResourceManager_parseCubemaps(self.__ptr, dirPath, recursive)
end

function ResourceManager:getResource(resourceType, resourceName)
	return Polycore.ResourceManager_getResource(self.__ptr, resourceType, resourceName)
end

function ResourceManager:addShaderModule(module)
	return Polycore.ResourceManager_addShaderModule(self.__ptr, module.__ptr)
end

