class "MaterialManager"







function MaterialManager:MaterialManager(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.MaterialManager(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function MaterialManager:Update(elapsed)
	local retVal = Polycore.MaterialManager_Update(self.__ptr, elapsed)
end

function MaterialManager:createFramebufferTexture(width, height, type)
	local retVal = Polycore.MaterialManager_createFramebufferTexture(self.__ptr, width, height, type)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:createTexture(width, height, imageData, clamp, type)
	local retVal = Polycore.MaterialManager_createTexture(self.__ptr, width, height, imageData.__ptr, clamp, type)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:createNewTexture(width, height, clamp, type)
	local retVal = Polycore.MaterialManager_createNewTexture(self.__ptr, width, height, clamp, type)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:createTextureFromImage(image, clamp)
	local retVal = Polycore.MaterialManager_createTextureFromImage(self.__ptr, image.__ptr, clamp)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:createTextureFromFile(fileName, clamp)
	local retVal = Polycore.MaterialManager_createTextureFromFile(self.__ptr, fileName.__ptr, clamp)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
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

function MaterialManager:addShaderModule(module)
	local retVal = Polycore.MaterialManager_addShaderModule(self.__ptr, module.__ptr)
end

function MaterialManager:getTextureByResourcePath(resourcePath)
	local retVal = Polycore.MaterialManager_getTextureByResourcePath(self.__ptr, resourcePath.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Texture("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:cubemapFromXMLNode(node)
	local retVal = Polycore.MaterialManager_cubemapFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Cubemap("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:loadMaterialsFromFile(fileName)
	local retVal = Polycore.MaterialManager_loadMaterialsFromFile(self.__ptr, fileName)
end

function MaterialManager:materialFromXMLNode(node)
	local retVal = Polycore.MaterialManager_materialFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Material("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:setShaderFromXMLNode(node)
	local retVal = Polycore.MaterialManager_setShaderFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Shader("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function MaterialManager:createShaderFromXMLNode(node)
	local retVal = Polycore.MaterialManager_createShaderFromXMLNode(self.__ptr, node.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Shader("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function MaterialManager:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_MaterialManager(self.__ptr)
end
