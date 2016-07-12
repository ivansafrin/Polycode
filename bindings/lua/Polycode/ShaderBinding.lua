class "ShaderBinding"


function ShaderBinding:ShaderBinding(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.ShaderBinding(unpack(arg))
	end
end

function ShaderBinding:addParam(type, name)
	local retVal = Polycode.ShaderBinding_addParam(self.__ptr, type, name)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addParamFromData(name, data)
	local retVal = Polycode.ShaderBinding_addParamFromData(self.__ptr, name, data)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumLocalParams()
	local retVal =  Polycode.ShaderBinding_getNumLocalParams(self.__ptr)
	return retVal
end

function ShaderBinding:getLocalParam(index)
	local retVal = Polycode.ShaderBinding_getLocalParam(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getLocalParamByName(name)
	local retVal = Polycode.ShaderBinding_getLocalParamByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:removeParam(name)
	local retVal = Polycode.ShaderBinding_removeParam(self.__ptr, name)
end

function ShaderBinding:loadTextureForParam(paramName, fileName)
	local retVal = Polycode.ShaderBinding_loadTextureForParam(self.__ptr, paramName, fileName)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<Texture>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:setTextureForParam(paramName, texture)
	local retVal = Polycode.ShaderBinding_setTextureForParam(self.__ptr, paramName, texture.__ptr)
end

function ShaderBinding:setCubemapForParam(paramName, cubemap)
	local retVal = Polycode.ShaderBinding_setCubemapForParam(self.__ptr, paramName, cubemap.__ptr)
end

function ShaderBinding:getNumAttributeBindings()
	local retVal =  Polycode.ShaderBinding_getNumAttributeBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getNumRenderTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumRenderTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getNumInTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumInTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getNumColorTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumColorTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getNumDepthTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumDepthTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getNumOutTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumOutTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:__delete()
	if self then Polycode.delete_ShaderBinding(self.__ptr) end
end
