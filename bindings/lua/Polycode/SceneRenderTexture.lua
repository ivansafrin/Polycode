class "SceneRenderTexture"



function SceneRenderTexture:__getvar(name)
	if name == "enabled" then
		return Polycore.SceneRenderTexture_get_enabled(self.__ptr)
	end
end


function SceneRenderTexture:__setvar(name,value)
	if name == "enabled" then
		Polycore.SceneRenderTexture_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function SceneRenderTexture:SceneRenderTexture(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.SceneRenderTexture(unpack(arg))
	end
end

function SceneRenderTexture:getTargetTexture()
	local retVal =  Polycore.SceneRenderTexture_getTargetTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:getFilterColorBufferTexture()
	local retVal =  Polycore.SceneRenderTexture_getFilterColorBufferTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:getFilterZBufferTexture()
	local retVal =  Polycore.SceneRenderTexture_getFilterZBufferTexture(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Texture"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:Render()
	local retVal =  Polycore.SceneRenderTexture_Render(self.__ptr)
end

function SceneRenderTexture:saveToImage()
	local retVal =  Polycore.SceneRenderTexture_saveToImage(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Image"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:resizeRenderTexture(newWidth, newHeight)
	local retVal = Polycore.SceneRenderTexture_resizeRenderTexture(self.__ptr, newWidth, newHeight)
end

function SceneRenderTexture:getTargetScene()
	local retVal =  Polycore.SceneRenderTexture_getTargetScene(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Scene"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:getTargetCamera()
	local retVal =  Polycore.SceneRenderTexture_getTargetCamera(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Camera"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function SceneRenderTexture:__delete()
	if self then Polycore.delete_SceneRenderTexture(self.__ptr) end
end
