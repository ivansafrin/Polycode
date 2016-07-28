class "RenderBuffer"


function RenderBuffer:__getvar(name)
	if name == "platformData" then
		local retVal = Polycode.RenderBuffer_get_platformData(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["RendererPlatformData"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "depthBufferPlatformData" then
		local retVal = Polycode.RenderBuffer_get_depthBufferPlatformData(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["RendererPlatformData"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function RenderBuffer:__setvar(name,value)
	if name == "platformData" then
		Polycode.RenderBuffer_set_platformData(self.__ptr, value.__ptr)
		return true
	elseif name == "depthBufferPlatformData" then
		Polycode.RenderBuffer_set_depthBufferPlatformData(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function RenderBuffer:RenderBuffer(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.RenderBuffer(unpack(arg))
	end
end

function RenderBuffer:getWidth()
	local retVal =  Polycode.RenderBuffer_getWidth(self.__ptr)
	return retVal
end

function RenderBuffer:getHeight()
	local retVal =  Polycode.RenderBuffer_getHeight(self.__ptr)
	return retVal
end

function RenderBuffer:__delete()
	if self then Polycode.delete_RenderBuffer(self.__ptr) end
end
