class "PolycodeViewBase"


function PolycodeViewBase:__getvar(name)
	if name == "resizable" then
		return Polycode.PolycodeViewBase_get_resizable(self.__ptr)
	end
end

function PolycodeViewBase:__setvar(name,value)
	if name == "resizable" then
		Polycode.PolycodeViewBase_set_resizable(self.__ptr, value)
		return true
	end
	return false
end
function PolycodeViewBase:PolycodeViewBase(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.PolycodeViewBase(unpack(arg))
	end
end

function PolycodeViewBase:__delete()
	if self then Polycode.delete_PolycodeViewBase(self.__ptr) end
end
