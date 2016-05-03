require "Polycode/Resource"

class "Material" (Resource)



function Material:__getvar(name)
	if name == "fp16RenderTargets" then
		return Polycore.Material_get_fp16RenderTargets(self.__ptr)
	elseif name == "shaderModule" then
		local retVal = Polycore.Material_get_shaderModule(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["void"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "blendingMode" then
		return Polycore.Material_get_blendingMode(self.__ptr)
	elseif name == "screenMaterial" then
		return Polycore.Material_get_screenMaterial(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end


function Material:__setvar(name,value)
	if name == "fp16RenderTargets" then
		Polycore.Material_set_fp16RenderTargets(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycore.Material_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "screenMaterial" then
		Polycore.Material_set_screenMaterial(self.__ptr, value)
		return true
	end
	if Resource["__setvar"] ~= nil then
		return Resource.__setvar(self, name, value)
	else
		return false
	end
end


function Material:Material(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Resource" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Material(unpack(arg))
	end
end

function Material:addShaderPass(pass)
	local retVal = Polycore.Material_addShaderPass(self.__ptr, pass.__ptr)
end

function Material:addShaderPassAtIndex(pass, shaderIndex)
	local retVal = Polycore.Material_addShaderPassAtIndex(self.__ptr, pass.__ptr, shaderIndex)
end

function Material:addShader(shader, shaderBinding)
	local retVal = Polycore.Material_addShader(self.__ptr, shader.__ptr, shaderBinding.__ptr)
end

function Material:addShaderAtIndex(shader, shaderBinding, shaderIndex)
	local retVal = Polycore.Material_addShaderAtIndex(self.__ptr, shader.__ptr, shaderBinding.__ptr, shaderIndex)
end

function Material:getNumShaderPasses()
	local retVal =  Polycore.Material_getNumShaderPasses(self.__ptr)
	return retVal
end

function Material:removeShaderPass(shaderIndex)
	local retVal = Polycore.Material_removeShaderPass(self.__ptr, shaderIndex)
end

function Material:recreateExpectedShaderParams()
	local retVal =  Polycore.Material_recreateExpectedShaderParams(self.__ptr)
end

function Material:addShaderRenderTarget(newTarget)
	local retVal = Polycore.Material_addShaderRenderTarget(self.__ptr, newTarget.__ptr)
end

function Material:getNumShaderRenderTargets()
	local retVal =  Polycore.Material_getNumShaderRenderTargets(self.__ptr)
	return retVal
end

function Material:getShaderRenderTarget(index)
	local retVal = Polycore.Material_getShaderRenderTarget(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderRenderTarget"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:removeShaderRenderTarget(index)
	local retVal = Polycore.Material_removeShaderRenderTarget(self.__ptr, index)
end

function Material:recreateRenderTarget(r_enderTarget)
	local retVal = Polycore.Material_recreateRenderTarget(self.__ptr, r_enderTarget.__ptr)
end

function Material:recreateRenderTargets()
	local retVal =  Polycore.Material_recreateRenderTargets(self.__ptr)
end

function Material:getName()
	local retVal =  Polycore.Material_getName(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["String"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:getShaderPass(index)
	local retVal = Polycore.Material_getShaderPass(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderPass"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:getShaderBinding(index)
	local retVal = Polycore.Material_getShaderBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:getShader(index)
	local retVal = Polycore.Material_getShader(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:loadMaterial(fileName)
	local retVal = Polycore.Material_loadMaterial(self.__ptr, fileName)
end

function Material:setName(name)
	local retVal = Polycore.Material_setName(self.__ptr, name)
end

function Material:clearShaders()
	local retVal =  Polycore.Material_clearShaders(self.__ptr)
end

function Material:__delete()
	if self then Polycore.delete_Material(self.__ptr) end
end
