require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)







function CoreServices.getInstance()
	local retVal =  Polycore.CoreServices_getInstance()
	if retVal == nil then return nil end
	local __c = _G["CoreServices"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices.setInstance(_instance)
	local retVal = Polycore.CoreServices_setInstance(_instance.__ptr)
end

function CoreServices.getRenderMutex()
	local retVal =  Polycore.CoreServices_getRenderMutex()
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices.createInstance()
	local retVal =  Polycore.CoreServices_createInstance()
end

function CoreServices:setRenderer(r_enderer)
	local retVal = Polycore.CoreServices_setRenderer(self.__ptr, r_enderer.__ptr)
end

function CoreServices:getRenderer()
	local retVal =  Polycore.CoreServices_getRenderer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Renderer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:Update(elapsed)
	local retVal = Polycore.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:fixedUpdate()
	local retVal =  Polycore.CoreServices_fixedUpdate(self.__ptr)
end

function CoreServices:Render(viewport)
	local retVal = Polycore.CoreServices_Render(self.__ptr, viewport.__ptr)
end

function CoreServices:setCore(core)
	local retVal = Polycore.CoreServices_setCore(self.__ptr, core.__ptr)
end

function CoreServices:getCore()
	local retVal =  Polycore.CoreServices_getCore(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Core"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getInput()
	local retVal =  Polycore.CoreServices_getInput(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreInput"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getMaterialManager()
	local retVal =  Polycore.CoreServices_getMaterialManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["MaterialManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSceneManager()
	local retVal =  Polycore.CoreServices_getSceneManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTimerManager()
	local retVal =  Polycore.CoreServices_getTimerManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TimerManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTweenManager()
	local retVal =  Polycore.CoreServices_getTweenManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TweenManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getResourceManager()
	local retVal =  Polycore.CoreServices_getResourceManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ResourceManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSoundManager()
	local retVal =  Polycore.CoreServices_getSoundManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SoundManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getLogger()
	local retVal =  Polycore.CoreServices_getLogger(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Logger"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getConfig()
	local retVal =  Polycore.CoreServices_getConfig(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Config"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:__delete()
	if self then Polycore.delete_CoreServices(self.__ptr) end
end
