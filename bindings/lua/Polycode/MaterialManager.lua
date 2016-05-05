class "MaterialManager"


function MaterialManager:__getvar(name)
	if name == "premultiplyAlphaOnLoad" then
		return Polycode.MaterialManager_get_premultiplyAlphaOnLoad(self.__ptr)
	elseif name == "clampDefault" then
		return Polycode.MaterialManager_get_clampDefault(self.__ptr)
	elseif name == "mipmapsDefault" then
		return Polycode.MaterialManager_get_mipmapsDefault(self.__ptr)
	elseif name == "keepTextureData" then
		return Polycode.MaterialManager_get_keepTextureData(self.__ptr)
	end
end

function MaterialManager:__setvar(name,value)
	if name == "premultiplyAlphaOnLoad" then
		Polycode.MaterialManager_set_premultiplyAlphaOnLoad(self.__ptr, value)
		return true
	elseif name == "clampDefault" then
		Polycode.MaterialManager_set_clampDefault(self.__ptr, value)
		return true
	elseif name == "mipmapsDefault" then
		Polycode.MaterialManager_set_mipmapsDefault(self.__ptr, value)
		return true
	elseif name == "keepTextureData" then
		Polycode.MaterialManager_set_keepTextureData(self.__ptr, value)
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
		self.__ptr = Polycode.MaterialManager(unpack(arg))
	end
end

function MaterialManager:Update(elapsed)
	local retVal = Polycode.MaterialManager_Update(self.__ptr, elapsed)
end

function MaterialManager:createTexture(width, height, imageData, clamp, createMipmaps, type)
	local retVal = Polycode.MaterialManager_createTexture(self.__ptr, width, height, imageData.__ptr, clamp, createMipmaps, type)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createNewTexture(width, height, clamp, createMipmaps, type)
	local retVal = Polycode.MaterialManager_createNewTexture(self.__ptr, width, height, clamp, createMipmaps, type)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createTextureFromImage(image, clamp, createMipmaps)
	local retVal = Polycode.MaterialManager_createTextureFromImage(self.__ptr, image.__ptr, clamp, createMipmaps)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createTextureFromFile(fileName, clamp, createMipmaps, resourcePool)
	local retVal = Polycode.MaterialManager_createTextureFromFile(self.__ptr, fileName, clamp, createMipmaps, resourcePool.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:deleteTexture(texture)
	local retVal = Polycode.MaterialManager_deleteTexture(self.__ptr, texture.__ptr)
end

function MaterialManager:reloadTextures()
	local retVal =  Polycode.MaterialManager_reloadTextures(self.__ptr)
end

function MaterialManager:reloadProgramsAndTextures()
	local retVal =  Polycode.MaterialManager_reloadProgramsAndTextures(self.__ptr)
end

function MaterialManager:reloadPrograms()
	local retVal =  Polycode.MaterialManager_reloadPrograms(self.__ptr)
end

function MaterialManager:getTextureByResourcePath(resourcePath)
	local retVal = Polycode.MaterialManager_getTextureByResourcePath(self.__ptr, resourcePath)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createProgramFromFile(programPath)
	local retVal = Polycode.MaterialManager_createProgramFromFile(self.__ptr, programPath)
	if retVal == nil then return nil end
	local __c = _G["ShaderProgram"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:loadMaterialLibraryIntoPool(pool, materialFile)
	local retVal = Polycode.MaterialManager_loadMaterialLibraryIntoPool(self.__ptr, pool.__ptr, materialFile)
end

function MaterialManager:cubemapFromXMLNode(node)
	local retVal = Polycode.MaterialManager_cubemapFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Cubemap"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:materialFromXMLNode(resourcePool, node)
	local retVal = Polycode.MaterialManager_materialFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createMaterial(resourcePool, materialName, shaderName)
	local retVal = Polycode.MaterialManager_createMaterial(self.__ptr, resourcePool.__ptr, materialName, shaderName)
	if retVal == nil then return nil end
	local __c = _G["Material"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:setShaderFromXMLNode(resourcePool, node)
	local retVal = Polycode.MaterialManager_setShaderFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createShaderFromXMLNode(resourcePool, node)
	local retVal = Polycode.MaterialManager_createShaderFromXMLNode(self.__ptr, resourcePool.__ptr, node.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:createShader(resourcePool, shaderType, name, vpName, fpName, screenShader)
	local retVal = Polycode.MaterialManager_createShader(self.__ptr, resourcePool.__ptr, shaderType, name, vpName, fpName, screenShader)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:loadMaterialsFromFile(resourcePool, fileName)
	local retVal = Polycode.MaterialManager_loadMaterialsFromFile(self.__ptr, resourcePool.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Material"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:loadShadersFromFile(resourcePool, fileName)
	local retVal = Polycode.MaterialManager_loadShadersFromFile(self.__ptr, resourcePool.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Shader"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:loadCubemapsFromFile(fileName)
	local retVal = Polycode.MaterialManager_loadCubemapsFromFile(self.__ptr, fileName)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["Cubemap"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function MaterialManager:setAnisotropyAmount(anisotropy)
	local retVal = Polycode.MaterialManager_setAnisotropyAmount(self.__ptr, anisotropy)
end

function MaterialManager:setTextureFilteringMode(textureFilteringMode)
	local retVal = Polycode.MaterialManager_setTextureFilteringMode(self.__ptr, textureFilteringMode)
end

function MaterialManager:getTextureFilteringMode()
	local retVal =  Polycode.MaterialManager_getTextureFilteringMode(self.__ptr)
	return retVal
end

function MaterialManager:addMaterial(material)
	local retVal = Polycode.MaterialManager_addMaterial(self.__ptr, material.__ptr)
end

function MaterialManager:addShader(shader)
	local retVal = Polycode.MaterialManager_addShader(self.__ptr, shader.__ptr)
end

function MaterialManager:getNumShaders()
	local retVal =  Polycode.MaterialManager_getNumShaders(self.__ptr)
	return retVal
end

function MaterialManager:getShaderByIndex(index)
	local retVal = Polycode.MaterialManager_getShaderByIndex(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function MaterialManager:__delete()
	if self then Polycode.delete_MaterialManager(self.__ptr) end
end
