class "RendererPlatformData"

RendererPlatformData.PLATFORM_DATA_NONE = 0
RendererPlatformData.PLATFORM_DATA_TEXTURE = 1
RendererPlatformData.PLATFORM_DATA_RENDER_BUFFER = 2
RendererPlatformData.PLATFORM_DATA_PROGRAM = 3
RendererPlatformData.PLATFORM_DATA_SHADER = 4
RendererPlatformData.PLATFORM_DATA_SUBMESH = 5

function RendererPlatformData:__getvar(name)
	if name == "type" then
		return Polycode.RendererPlatformData_get_type(self.__ptr)
	end
end

function RendererPlatformData:__setvar(name,value)
	if name == "type" then
		Polycode.RendererPlatformData_set_type(self.__ptr, value)
		return true
	end
	return false
end
function RendererPlatformData:RendererPlatformData(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.RendererPlatformData(unpack(arg))
	end
end

function RendererPlatformData:__delete()
	if self then Polycode.delete_RendererPlatformData(self.__ptr) end
end
