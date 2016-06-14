require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)


function CoreServices:getInstance()
	local retVal =  Polycode.CoreServices_getInstance(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreServices"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:setInstance(_instance)
	local retVal = Polycode.CoreServices_setInstance(self.__ptr, _instance.__ptr)
end

function CoreServices:getRenderMutex()
	local retVal =  Polycode.CoreServices_getRenderMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:createInstance()
	local retVal =  Polycode.CoreServices_createInstance(self.__ptr)
end

function CoreServices:setRenderer(renderer)
	local retVal = Polycode.CoreServices_setRenderer(self.__ptr, renderer.__ptr)
end

function CoreServices:getRenderer()
	local retVal =  Polycode.CoreServices_getRenderer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Renderer"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:Update(elapsed)
	local retVal = Polycode.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:fixedUpdate()
	local retVal =  Polycode.CoreServices_fixedUpdate(self.__ptr)
end

function CoreServices:Render(viewport)
	local retVal = Polycode.CoreServices_Render(self.__ptr, viewport.__ptr)
end

function CoreServices:setCore(core)
	local retVal = Polycode.CoreServices_setCore(self.__ptr, core.__ptr)
end

function CoreServices:getCore()
	local retVal =  Polycode.CoreServices_getCore(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Core"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getInput()
	local retVal =  Polycode.CoreServices_getInput(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreInput"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSceneManager()
	local retVal =  Polycode.CoreServices_getSceneManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SceneManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTimerManager()
	local retVal =  Polycode.CoreServices_getTimerManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TimerManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getTweenManager()
	local retVal =  Polycode.CoreServices_getTweenManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["TweenManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getResourceManager()
	local retVal =  Polycode.CoreServices_getResourceManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["ResourceManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getSoundManager()
	local retVal =  Polycode.CoreServices_getSoundManager(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["SoundManager"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getLogger()
	local retVal =  Polycode.CoreServices_getLogger(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Logger"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:getConfig()
	local retVal =  Polycode.CoreServices_getConfig(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Config"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function CoreServices:__delete()
	if self then Polycode.delete_CoreServices(self.__ptr) end
end
