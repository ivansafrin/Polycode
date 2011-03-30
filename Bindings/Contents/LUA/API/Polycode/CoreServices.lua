require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)

function CoreServices:getInstance()
	return Polycore.CoreServices_getInstance(self.__ptr)
end

function CoreServices:getRenderMutex()
	return Polycore.CoreServices_getRenderMutex(self.__ptr)
end

function CoreServices:setRenderer(r_enderer)
	return Polycore.CoreServices_setRenderer(self.__ptr, r_enderer.__ptr)
end

function CoreServices:getRenderer()
	return Polycore.CoreServices_getRenderer(self.__ptr)
end

function CoreServices:Update(elapsed)
	return Polycore.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:setCore(core)
	return Polycore.CoreServices_setCore(self.__ptr, core.__ptr)
end

function CoreServices:getCore()
	return Polycore.CoreServices_getCore(self.__ptr)
end

function CoreServices:handleEvent(event)
	return Polycore.CoreServices_handleEvent(self.__ptr, event.__ptr)
end

function CoreServices:installModule(module)
	return Polycore.CoreServices_installModule(self.__ptr, module.__ptr)
end

function CoreServices:getMaterialManager()
	return Polycore.CoreServices_getMaterialManager(self.__ptr)
end

function CoreServices:getScreenManager()
	return Polycore.CoreServices_getScreenManager(self.__ptr)
end

function CoreServices:getSceneManager()
	return Polycore.CoreServices_getSceneManager(self.__ptr)
end

function CoreServices:getTimerManager()
	return Polycore.CoreServices_getTimerManager(self.__ptr)
end

function CoreServices:getTweenManager()
	return Polycore.CoreServices_getTweenManager(self.__ptr)
end

function CoreServices:getResourceManager()
	return Polycore.CoreServices_getResourceManager(self.__ptr)
end

function CoreServices:getSoundManager()
	return Polycore.CoreServices_getSoundManager(self.__ptr)
end

function CoreServices:getFontManager()
	return Polycore.CoreServices_getFontManager(self.__ptr)
end

function CoreServices:getConfig()
	return Polycore.CoreServices_getConfig(self.__ptr)
end

