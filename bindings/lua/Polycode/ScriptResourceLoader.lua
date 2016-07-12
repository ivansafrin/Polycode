class "ScriptResourceLoader"


function ScriptResourceLoader:ScriptResourceLoader(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.ScriptResourceLoader(unpack(arg))
	end
end

function ScriptResourceLoader:__delete()
	if self then Polycode.delete_ScriptResourceLoader(self.__ptr) end
end
