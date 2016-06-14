class "ShaderRenderTarget"

ShaderRenderTarget.SIZE_MODE_PIXELS = 0
ShaderRenderTarget.SIZE_MODE_NORMALIZED = 1

function ShaderRenderTarget:__getvar(name)
	if name == "id" then
		return Polycode.ShaderRenderTarget_get_id(self.__ptr)
	elseif name == "width" then
		return Polycode.ShaderRenderTarget_get_width(self.__ptr)
	elseif name == "height" then
		return Polycode.ShaderRenderTarget_get_height(self.__ptr)
	elseif name == "sizeMode" then
		return Polycode.ShaderRenderTarget_get_sizeMode(self.__ptr)
	elseif name == "normalizedWidth" then
		return Polycode.ShaderRenderTarget_get_normalizedWidth(self.__ptr)
	elseif name == "normalizedHeight" then
		return Polycode.ShaderRenderTarget_get_normalizedHeight(self.__ptr)
	end
end

function ShaderRenderTarget:__setvar(name,value)
	if name == "id" then
		Polycode.ShaderRenderTarget_set_id(self.__ptr, value)
		return true
	elseif name == "width" then
		Polycode.ShaderRenderTarget_set_width(self.__ptr, value)
		return true
	elseif name == "height" then
		Polycode.ShaderRenderTarget_set_height(self.__ptr, value)
		return true
	elseif name == "sizeMode" then
		Polycode.ShaderRenderTarget_set_sizeMode(self.__ptr, value)
		return true
	elseif name == "normalizedWidth" then
		Polycode.ShaderRenderTarget_set_normalizedWidth(self.__ptr, value)
		return true
	elseif name == "normalizedHeight" then
		Polycode.ShaderRenderTarget_set_normalizedHeight(self.__ptr, value)
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
		self.__ptr = Polycode.ShaderRenderTarget(unpack(arg))
	end
end

function ShaderRenderTarget:__delete()
	if self then Polycode.delete_ShaderRenderTarget(self.__ptr) end
end
