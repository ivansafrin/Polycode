class "ShaderBinding"







function ShaderBinding:ShaderBinding(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ShaderBinding(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function ShaderBinding:clearTexture(name)
	local retVal = Polycore.ShaderBinding_clearTexture(self.__ptr, name.__ptr)
end

function ShaderBinding:addTexture(name, texture)
	local retVal = Polycore.ShaderBinding_addTexture(self.__ptr, name.__ptr, texture.__ptr)
end

function ShaderBinding:addParam(type, name, value)
	local retVal = Polycore.ShaderBinding_addParam(self.__ptr, type.__ptr, name.__ptr, value.__ptr)
end

function ShaderBinding:addCubemap(name, cubemap)
	local retVal = Polycore.ShaderBinding_addCubemap(self.__ptr, name.__ptr, cubemap.__ptr)
end

function ShaderBinding:getNumLocalParams()
	local retVal =  Polycore.ShaderBinding_getNumLocalParams(self.__ptr)
	return retVal
end

function ShaderBinding:getLocalParam(index)
	local retVal = Polycore.ShaderBinding_getLocalParam(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = LocalShaderParam("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ShaderBinding:getLocalParamByName(name)
	local retVal = Polycore.ShaderBinding_getLocalParamByName(self.__ptr, name.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = LocalShaderParam("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ShaderBinding:addRenderTargetBinding(binding)
	local retVal = Polycore.ShaderBinding_addRenderTargetBinding(self.__ptr, binding.__ptr)
end

function ShaderBinding:getNumRenderTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumRenderTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getRenderTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getRenderTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = RenderTargetBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ShaderBinding:getNumInTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumInTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getInTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getInTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = RenderTargetBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ShaderBinding:getNumOutTargetBindings()
	local retVal =  Polycore.ShaderBinding_getNumOutTargetBindings(self.__ptr)
	return retVal
end

function ShaderBinding:getOutTargetBinding(index)
	local retVal = Polycore.ShaderBinding_getOutTargetBinding(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = RenderTargetBinding("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function ShaderBinding:addLocalParam(name, ptr)
	local retVal = Polycore.ShaderBinding_addLocalParam(self.__ptr, name.__ptr, ptr.__ptr)
end



function ShaderBinding:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_ShaderBinding(self.__ptr)
end
