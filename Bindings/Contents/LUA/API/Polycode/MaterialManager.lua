class "MaterialManager"

function MaterialManager:MaterialManager()
	if self.__ptr == nil then
		self.__ptr = Polycore.MaterialManager()
	end
end

function MaterialManager:Update(elapsed)
	return Polycore.MaterialManager_Update(self.__ptr, elapsed)
end

function MaterialManager:createFramebufferTexture(width, height, type)
	return Polycore.MaterialManager_createFramebufferTexture(self.__ptr, width, height, type)
end

function MaterialManager:createTexture(width, height, imageData, clamp, type)
	return Polycore.MaterialManager_createTexture(self.__ptr, width, height, imageData.__ptr, clamp, type)
end

function MaterialManager:createNewTexture(width, height, clamp, type)
	return Polycore.MaterialManager_createNewTexture(self.__ptr, width, height, clamp, type)
end

function MaterialManager:createTextureFromImage(image, clamp)
	return Polycore.MaterialManager_createTextureFromImage(self.__ptr, image.__ptr, clamp)
end

function MaterialManager:createTextureFromFile(fileName, clamp)
	return Polycore.MaterialManager_createTextureFromFile(self.__ptr, fileName, clamp)
end

function MaterialManager:deleteTexture(texture)
	return Polycore.MaterialManager_deleteTexture(self.__ptr, texture.__ptr)
end

function MaterialManager:reloadTextures()
	return Polycore.MaterialManager_reloadTextures(self.__ptr)
end

function MaterialManager:reloadProgramsAndTextures()
	return Polycore.MaterialManager_reloadProgramsAndTextures(self.__ptr)
end

function MaterialManager:reloadPrograms()
	return Polycore.MaterialManager_reloadPrograms(self.__ptr)
end

function MaterialManager:addShaderModule(module)
	return Polycore.MaterialManager_addShaderModule(self.__ptr, module.__ptr)
end

function MaterialManager:getTextureByResourcePath(resourcePath)
	return Polycore.MaterialManager_getTextureByResourcePath(self.__ptr, resourcePath)
end

function MaterialManager:cubemapFromXMLNode(node)
	return Polycore.MaterialManager_cubemapFromXMLNode(self.__ptr, node.__ptr)
end

function MaterialManager:loadMaterialsFromFile(fileName)
	return Polycore.MaterialManager_loadMaterialsFromFile(self.__ptr, fileName)
end

function MaterialManager:materialFromXMLNode(node)
	return Polycore.MaterialManager_materialFromXMLNode(self.__ptr, node.__ptr)
end

function MaterialManager:setShaderFromXMLNode(node)
	return Polycore.MaterialManager_setShaderFromXMLNode(self.__ptr, node.__ptr)
end

function MaterialManager:createShaderFromXMLNode(node)
	return Polycore.MaterialManager_createShaderFromXMLNode(self.__ptr, node.__ptr)
end

