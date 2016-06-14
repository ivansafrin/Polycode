class "ShaderBinding"


function ShaderBinding:__getvar(name)
	if name == "accessMutex" then
		local retVal = Polycode.ShaderBinding_get_accessMutex(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["CoreMutex"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function ShaderBinding:__setvar(name,value)
	if name == "accessMutex" then
		Polycode.ShaderBinding_set_accessMutex(self.__ptr, value.__ptr)
		return true
	end
	return false
end
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

function ShaderBinding:copyTo(targetBinding)
	local retVal = Polycode.ShaderBinding_copyTo(self.__ptr, targetBinding.__ptr)
end

function ShaderBinding:addParam(type, name)
	local retVal = Polycode.ShaderBinding_addParam(self.__ptr, type, name)
	if retVal == nil then return nil end
	local __c = _G["shared_ptr<LocalShaderParam>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addParamPointer(type, name, ptr)
	local retVal = Polycode.ShaderBinding_addParamPointer(self.__ptr, type, name, ptr.__ptr)
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

function ShaderBinding:getAttributeBinding(index)
	local retVal = Polycode.ShaderBinding_getAttributeBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["AttributeBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addAttributeBinding(name, dataArray)
	local retVal = Polycode.ShaderBinding_addAttributeBinding(self.__ptr, name, dataArray.__ptr)
	if retVal == nil then return nil end
	local __c = _G["AttributeBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getAttributeBindingByName(name)
	local retVal = Polycode.ShaderBinding_getAttributeBindingByName(self.__ptr, name)
	if retVal == nil then return nil end
	local __c = _G["AttributeBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:addRenderTargetBinding(binding)
	local retVal = Polycode.ShaderBinding_addRenderTargetBinding(self.__ptr, binding.__ptr)
end

function ShaderBinding:removeRenderTargetBinding(binding)
	local retVal = Polycode.ShaderBinding_removeRenderTargetBinding(self.__ptr, binding.__ptr)
end

function ShaderBinding:getNumRenderTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumRenderTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getRenderTargetBinding(index)
	local retVal = Polycode.ShaderBinding_getRenderTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumInTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumInTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getInTargetBinding(index)
	local retVal = Polycode.ShaderBinding_getInTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumColorTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumColorTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getColorTargetBinding(index)
	local retVal = Polycode.ShaderBinding_getColorTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumDepthTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumDepthTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getDepthTargetBinding(index)
	local retVal = Polycode.ShaderBinding_getDepthTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:getNumOutTargetBindings()
	local retVal =  Polycode.ShaderBinding_getNumOutTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getOutTargetBinding(index)
	local retVal = Polycode.ShaderBinding_getOutTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["RenderTargetBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function ShaderBinding:__delete()
	if self then Polycode.delete_ShaderBinding(self.__ptr) end
end
