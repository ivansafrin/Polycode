class "ShaderRenderTarget"



ShaderRenderTarget.SIZE_MODE_PIXELS = 0
ShaderRenderTarget.SIZE_MODE_NORMALIZED = 1
function ShaderRenderTarget:__getvar(name)
	if name == "id" then
		return Polycore.ShaderRenderTarget_get_id(self.__ptr)
	elseif name == "width" then
		return Polycore.ShaderRenderTarget_get_width(self.__ptr)
	elseif name == "height" then
		return Polycore.ShaderRenderTarget_get_height(self.__ptr)
	elseif name == "sizeMode" then
		return Polycore.ShaderRenderTarget_get_sizeMode(self.__ptr)
	elseif name == "buffer" then
		local retVal = Polycore.ShaderRenderTarget_get_buffer(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["RenderBuffer"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "normalizedWidth" then
		return Polycore.ShaderRenderTarget_get_normalizedWidth(self.__ptr)
	elseif name == "normalizedHeight" then
		return Polycore.ShaderRenderTarget_get_normalizedHeight(self.__ptr)
	end
end


function ShaderRenderTarget:__setvar(name,value)
	if name == "id" then
		Polycore.ShaderRenderTarget_set_id(self.__ptr, value)
		return true
	elseif name == "width" then
		Polycore.ShaderRenderTarget_set_width(self.__ptr, value)
		return true
	elseif name == "height" then
		Polycore.ShaderRenderTarget_set_height(self.__ptr, value)
		return true
	elseif name == "sizeMode" then
		Polycore.ShaderRenderTarget_set_sizeMode(self.__ptr, value)
		return true
	elseif name == "normalizedWidth" then
		Polycore.ShaderRenderTarget_set_normalizedWidth(self.__ptr, value)
		return true
	elseif name == "normalizedHeight" then
		Polycore.ShaderRenderTarget_set_normalizedHeight(self.__ptr, value)
		return true
	end
	return false
end


function ShaderRenderTarget:ShaderRenderTarget(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.ShaderRenderTarget(unpack(arg))
	end
end

function ShaderRenderTarget:__delete()
	if self then Polycore.delete_ShaderRenderTarget(self.__ptr) end
end
