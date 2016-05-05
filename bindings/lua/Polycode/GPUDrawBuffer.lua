class "GPUDrawBuffer"


function GPUDrawBuffer:__getvar(name)
	if name == "targetFramebuffer" then
		local retVal = Polycode.GPUDrawBuffer_get_targetFramebuffer(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["RenderBuffer"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "projectionMatrix" then
		local retVal = Polycode.GPUDrawBuffer_get_projectionMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "viewMatrix" then
		local retVal = Polycode.GPUDrawBuffer_get_viewMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "cameraMatrix" then
		local retVal = Polycode.GPUDrawBuffer_get_cameraMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "clearColor" then
		local retVal = Polycode.GPUDrawBuffer_get_clearColor(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Color"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "clearDepthBuffer" then
		return Polycode.GPUDrawBuffer_get_clearDepthBuffer(self.__ptr)
	elseif name == "clearColorBuffer" then
		return Polycode.GPUDrawBuffer_get_clearColorBuffer(self.__ptr)
	elseif name == "backingResolutionScale" then
		local retVal = Polycode.GPUDrawBuffer_get_backingResolutionScale(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector2"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "globalMaterial" then
		local retVal = Polycode.GPUDrawBuffer_get_globalMaterial(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Material"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "viewport" then
		local retVal = Polycode.GPUDrawBuffer_get_viewport(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Rectangle"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end

function GPUDrawBuffer:__setvar(name,value)
	if name == "targetFramebuffer" then
		Polycode.GPUDrawBuffer_set_targetFramebuffer(self.__ptr, value.__ptr)
		return true
	elseif name == "projectionMatrix" then
		Polycode.GPUDrawBuffer_set_projectionMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "viewMatrix" then
		Polycode.GPUDrawBuffer_set_viewMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "cameraMatrix" then
		Polycode.GPUDrawBuffer_set_cameraMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "clearColor" then
		Polycode.GPUDrawBuffer_set_clearColor(self.__ptr, value.__ptr)
		return true
	elseif name == "clearDepthBuffer" then
		Polycode.GPUDrawBuffer_set_clearDepthBuffer(self.__ptr, value)
		return true
	elseif name == "clearColorBuffer" then
		Polycode.GPUDrawBuffer_set_clearColorBuffer(self.__ptr, value)
		return true
	elseif name == "backingResolutionScale" then
		Polycode.GPUDrawBuffer_set_backingResolutionScale(self.__ptr, value.__ptr)
		return true
	elseif name == "globalMaterial" then
		Polycode.GPUDrawBuffer_set_globalMaterial(self.__ptr, value.__ptr)
		return true
	elseif name == "viewport" then
		Polycode.GPUDrawBuffer_set_viewport(self.__ptr, value.__ptr)
		return true
	end
	return false
end
function GPUDrawBuffer:GPUDrawBuffer(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.GPUDrawBuffer(unpack(arg))
	end
end

function GPUDrawBuffer:__delete()
	if self then Polycode.delete_GPUDrawBuffer(self.__ptr) end
end
