require "Polycode/Resource"

class "Material" (Resource)


function Material:__getvar(name)
	if name == "fp16RenderTargets" then
		return Polycode.Material_get_fp16RenderTargets(self.__ptr)
	elseif name == "blendingMode" then
		return Polycode.Material_get_blendingMode(self.__ptr)
	elseif name == "screenMaterial" then
		return Polycode.Material_get_screenMaterial(self.__ptr)
	end
	if Resource["__getvar"] ~= nil then
		return Resource.__getvar(self, name)
	end
end

function Material:__setvar(name,value)
	if name == "fp16RenderTargets" then
		Polycode.Material_set_fp16RenderTargets(self.__ptr, value)
		return true
	elseif name == "blendingMode" then
		Polycode.Material_set_blendingMode(self.__ptr, value)
		return true
	elseif name == "screenMaterial" then
		Polycode.Material_set_screenMaterial(self.__ptr, value)
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
		self.__ptr = Polycode.Material(unpack(arg))
	end
end

function Material:addShaderPass(pass)
	local retVal = Polycode.Material_addShaderPass(self.__ptr, pass.__ptr)
end

function Material:addShaderPassAtIndex(pass, shaderIndex)
	local retVal = Polycode.Material_addShaderPassAtIndex(self.__ptr, pass.__ptr, shaderIndex)
end

function Material:addShader(shader, shaderBinding)
	local retVal = Polycode.Material_addShader(self.__ptr, shader.__ptr, shaderBinding.__ptr)
end

function Material:addShaderAtIndex(shader, shaderBinding, shaderIndex)
	local retVal = Polycode.Material_addShaderAtIndex(self.__ptr, shader.__ptr, shaderBinding.__ptr, shaderIndex)
end

function Material:getNumShaderPasses()
	local retVal =  Polycode.Material_getNumShaderPasses(self.__ptr)
	return retVal
end

function Material:removeShaderPass(shaderIndex)
	local retVal = Polycode.Material_removeShaderPass(self.__ptr, shaderIndex)
end

function Material:recreateExpectedShaderParams()
	local retVal =  Polycode.Material_recreateExpectedShaderParams(self.__ptr)
end

function Material:addShaderRenderTarget(newTarget)
	local retVal = Polycode.Material_addShaderRenderTarget(self.__ptr, newTarget.__ptr)
end

function Material:getNumShaderRenderTargets()
	local retVal =  Polycode.Material_getNumShaderRenderTargets(self.__ptr)
	return retVal
end

function Material:getShaderRenderTarget(index)
	local retVal = Polycode.Material_getShaderRenderTarget(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderRenderTarget"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:removeShaderRenderTarget(index)
	local retVal = Polycode.Material_removeShaderRenderTarget(self.__ptr, index)
end

function Material:recreateRenderTarget(renderTarget)
	local retVal = Polycode.Material_recreateRenderTarget(self.__ptr, renderTarget.__ptr)
end

function Material:recreateRenderTargets()
	local retVal =  Polycode.Material_recreateRenderTargets(self.__ptr)
end

function Material:getName()
	local retVal =  Polycode.Material_getName(self.__ptr)
	return retVal
end

function Material:getShaderPass(index)
	local retVal = Polycode.Material_getShaderPass(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderPass"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:getShaderBinding(index)
	local retVal = Polycode.Material_getShaderBinding(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["ShaderBinding"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:getShader(index)
	local retVal = Polycode.Material_getShader(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Shader"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Material:loadMaterial(fileName)
	local retVal = Polycode.Material_loadMaterial(self.__ptr, fileName)
end

function Material:setName(name)
	local retVal = Polycode.Material_setName(self.__ptr, name)
end

function Material:clearShaders()
	local retVal =  Polycode.Material_clearShaders(self.__ptr)
end

function Material:__delete()
	if self then Polycode.delete_Material(self.__ptr) end
end
