class "MaterialManager"



function MaterialManager:__getvar(name)
	if name == "premultiplyAlphaOnLoad" then
		return Polycore.MaterialManager_get_premultiplyAlphaOnLoad(self.__ptr)
	elseif name == "clampDefault" then
		return Polycore.MaterialManager_get_clampDefault(self.__ptr)
	elseif name == "mipmapsDefault" then
		return Polycore.MaterialManager_get_mipmapsDefault(self.__ptr)
	elseif name == "keepTextureData" then
		return Polycore.MaterialManager_get_keepTextureData(self.__ptr)
	end
end


function MaterialManager:__setvar(name,value)
	if name == "premultiplyAlphaOnLoad" then
		Polycore.MaterialManager_set_premultiplyAlphaOnLoad(self.__ptr, value)
		return true
	elseif name == "clampDefault" then
		Polycore.MaterialManager_set_clampDefault(self.__ptr, value)
		return true
	elseif name == "mipmapsDefault" then
		Polycore.MaterialManager_set_mipmapsDefault(self.__ptr, value)
		return true
	elseif name == "keepTextureData" then
		Polycore.MaterialManager_set_keepTextureData(self.__ptr, value)
		return true
	end
	return false
end


function MaterialManager:MaterialManager(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.MaterialManager(unpack(arg))
	end
end

function MaterialManager:Update(elapsed)
	local retVal = Polycore.MaterialManager_Update(self.__ptr, elapsed)
end

function MaterialManager:createTexture(width, height, imageData, clamp, createMipmaps, type)
	local retVal = Polycore.MaterialManager_createTexture(self.__ptr, width, height, imageData.__ptr, clamp, createMipmaps, type)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createNewTexture(width, height, clamp, createMipmaps, type)
	local retVal = Polycore.MaterialManager_createNewTexture(self.__ptr, width, height, clamp, createMipmaps, type)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createTextureFromImage(image, clamp, createMipmaps)
	local retVal = Polycore.MaterialManager_createTextureFromImage(self.__ptr, image.__ptr, clamp, createMipmaps)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createTextureFromFile(fileName, clamp, createMipmaps, resourcePool)
	local retVal = Polycore.MaterialManager_createTextureFromFile(self.__ptr, fileName, clamp, createMipmaps, resourcePool.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:deleteTexture(texture)
	local retVal = Polycore.MaterialManager_deleteTexture(self.__ptr, texture.__ptr)
end

function MaterialManager:reloadTextures()
	local retVal =  Polycore.MaterialManager_reloadTextures(self.__ptr)
end

function MaterialManager:reloadProgramsAndTextures()
	local retVal =  Polycore.MaterialManager_reloadProgramsAndTextures(self.__ptr)
end

function MaterialManager:reloadPrograms()
	local retVal =  Polycore.MaterialManager_reloadPrograms(self.__ptr)
end

function MaterialManager:getTextureByResourcePath(resourcePath)
	local retVal = Polycore.MaterialManager_getTextureByResourcePath(self.__ptr, resourcePath)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createProgramFromFile(programPath)
	local retVal = Polycore.MaterialManager_createProgramFromFile(self.__ptr, programPath)
	if retVal == nil then return nil end
	local __c = _G["ShaderProgram"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:loadMaterialLibraryIntoPool(pool, materialFile)
	local retVal = Polycore.MaterialManager_loadMaterialLibraryIntoPool(self.__ptr, pool.__ptr, materialFile)
end

function MaterialManager:cubemapFromXMLNode(node)
	local retVal = Polycore.MaterialManager_cubemapFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:materialFromXMLNode(resourcePool, node)
	local retVal = Polycore.MaterialManager_materialFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createMaterial(resourcePool, materialName, shaderName)
	local retVal = Polycore.MaterialManager_createMaterial(self.__ptr, resourcePool.__ptr, materialName, shaderName)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:setShaderFromXMLNode(resourcePool, node)
	local retVal = Polycore.MaterialManager_setShaderFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createShaderFromXMLNode(resourcePool, node)
	local retVal = Polycore.MaterialManager_createShaderFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createShader(resourcePool, shaderType, name, vpName, fpName, screenShader)
	local retVal = Polycore.MaterialManager_createShader(self.__ptr, resourcePool.__ptr, shaderType, name, vpName, fpName, screenShader)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:loadMaterialsFromFile(resourcePool, fileName)
	local retVal = Polycore.MaterialManager_loadMaterialsFromFile(self.__ptr, resourcePool.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Material"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:loadShadersFromFile(resourcePool, fileName)
	local retVal = Polycore.MaterialManager_loadShadersFromFile(self.__ptr, resourcePool.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Shader"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:loadCubemapsFromFile(fileName)
	local retVal = Polycore.MaterialManager_loadCubemapsFromFile(self.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Cubemap"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:setAnisotropyAmount(anisotropy)
	local retVal = Polycore.MaterialManager_setAnisotropyAmount(self.__ptr, anisotropy)
end

function MaterialManager:setTextureFilteringMode(textureFilteringMode)
	local retVal = Polycore.MaterialManager_setTextureFilteringMode(self.__ptr, textureFilteringMode)
end

function MaterialManager:getTextureFilteringMode()
	local retVal =  Polycore.MaterialManager_getTextureFilteringMode(self.__ptr)
	return retVal
end

function MaterialManager:addMaterial(material)
	local retVal = Polycore.MaterialManager_addMaterial(self.__ptr, material.__ptr)
end

function MaterialManager:addShader(shader)
	local retVal = Polycore.MaterialManager_addShader(self.__ptr, shader.__ptr)
end

function MaterialManager:getNumShaders()
	local retVal =  Polycore.MaterialManager_getNumShaders(self.__ptr)
	return retVal
end

function MaterialManager:getShaderByIndex(index)
	local retVal = Polycore.MaterialManager_getShaderByIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:__delete()
	if self then Polycore.delete_MaterialManager(self.__ptr) end
end
