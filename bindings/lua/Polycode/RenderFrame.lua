class "RenderFrame"


function RenderFrame:__getvar(name)
	if name == "viewport" then
		local retVal = Polycode.RenderFrame_get_viewport(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function RenderFrame:__setvar(name,value)
	if name == "viewport" then
		Polycode.RenderFrame_set_viewport(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function RenderFrame:RenderFrame(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.RenderFrame(unpack(arg))
	end
end

function RenderFrame:__delete()
	if self then Polycode.delete_RenderFrame(self.__ptr) end
end
