class "RenderTargetBinding"

RenderTargetBinding.MODE_IN = 0
RenderTargetBinding.MODE_OUT = 1
RenderTargetBinding.MODE_COLOR = 2
RenderTargetBinding.MODE_DEPTH = 3

function RenderTargetBinding:__getvar(name)
	if name == "id" then
		return Polycode.RenderTargetBinding_get_id(self.__ptr)
	elseif name == "name" then
		return Polycode.RenderTargetBinding_get_name(self.__ptr)
	elseif name == "mode" then
		return Polycode.RenderTargetBinding_get_mode(self.__ptr)
	end
end

function RenderTargetBinding:__setvar(name,value)
	if name == "id" then
		Polycode.RenderTargetBinding_set_id(self.__ptr, value)
		return true
	elseif name == "name" then
		Polycode.RenderTargetBinding_set_name(self.__ptr, value)
		return true
	elseif name == "mode" then
		Polycode.RenderTargetBinding_set_mode(self.__ptr, value)
		return true
	end
	return false
end
function RenderTargetBinding:__delete()
	if self then Polycode.delete_RenderTargetBinding(self.__ptr) end
end
