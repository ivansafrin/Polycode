require "Polycode/EventDispatcher"

class "CoreServices" (EventDispatcher)







function CoreServices:getInstance()
	local retVal =  Polycore.CoreServices_getInstance()
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreServices("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:setInstance(_instance)
	local retVal = Polycore.CoreServices_setInstance(_instance.__ptr)
end

function CoreServices:getRenderMutex()
	local retVal =  Polycore.CoreServices_getRenderMutex()
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreMutex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:setRenderer(r_enderer)
	local retVal = Polycore.CoreServices_setRenderer(self.__ptr, r_enderer.__ptr)
end

function CoreServices:getRenderer()
	local retVal =  Polycore.CoreServices_getRenderer(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Renderer("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:Update(elapsed)
	local retVal = Polycore.CoreServices_Update(self.__ptr, elapsed)
end

function CoreServices:setCore(core)
	local retVal = Polycore.CoreServices_setCore(self.__ptr, core.__ptr)
end

function CoreServices:getCore()
	local retVal =  Polycore.CoreServices_getCore(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Core("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:installModule(module)
	local retVal = Polycore.CoreServices_installModule(self.__ptr, module.__ptr)
end

function CoreServices:getMaterialManager()
	local retVal =  Polycore.CoreServices_getMaterialManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = MaterialManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getScreenManager()
	local retVal =  Polycore.CoreServices_getScreenManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getSceneManager()
	local retVal =  Polycore.CoreServices_getSceneManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getTimerManager()
	local retVal =  Polycore.CoreServices_getTimerManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = TimerManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getTweenManager()
	local retVal =  Polycore.CoreServices_getTweenManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = TweenManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getResourceManager()
	local retVal =  Polycore.CoreServices_getResourceManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ResourceManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getSoundManager()
	local retVal =  Polycore.CoreServices_getSoundManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SoundManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getFontManager()
	local retVal =  Polycore.CoreServices_getFontManager(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = FontManager("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getConfig()
	local retVal =  Polycore.CoreServices_getConfig(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Config("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CoreServices:getScreenInfo(width, height, hz)
	local retVal = Polycore.CoreServices_getScreenInfo(self.__ptr, width.__ptr, height.__ptr, hz.__ptr)
end



function CoreServices:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_CoreServices(self.__ptr)
end
