class "TextureResourceLoader"







function TextureResourceLoader:TextureResourceLoader(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.TextureResourceLoader(unpack(arg))
	end
end

function TextureResourceLoader:loadResource(path, targetPool)
	local retVal = Polycore.TextureResourceLoader_loadResource(self.__ptr, path, targetPool.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Resource"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function TextureResourceLoader:__delete()
	if self then Polycore.delete_TextureResourceLoader(self.__ptr) end
end
