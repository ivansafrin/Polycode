class "ColorRange"


function ColorRange:__getvar(name)
	if name == "color" then
		local retVal = Polycode.ColorRange_get_color(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "rangeStart" then
		return Polycode.ColorRange_get_rangeStart(self.__ptr)
	elseif name == "rangeEnd" then
		return Polycode.ColorRange_get_rangeEnd(self.__ptr)
	end
end

function ColorRange:__setvar(name,value)
	if name == "color" then
		Polycode.ColorRange_set_color(self.__ptr, value.__ptr)
		return true
	elseif name == "rangeStart" then
		Polycode.ColorRange_set_rangeStart(self.__ptr, value)
		return true
	elseif name == "rangeEnd" then
		Polycode.ColorRange_set_rangeEnd(self.__ptr, value)
		return true
	end
	return false
end
function ColorRange:ColorRange(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.ColorRange(unpack(arg))
	end
end

function ColorRange:__delete()
	if self then Polycode.delete_ColorRange(self.__ptr) end
end
