class "MaterialResourceLoader"


function MaterialResourceLoader:MaterialResourceLoader(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.MaterialResourceLoader(unpack(arg))
	end
end

function MaterialResourceLoader:__delete()
	if self then Polycode.delete_MaterialResourceLoader(self.__ptr) end
end
