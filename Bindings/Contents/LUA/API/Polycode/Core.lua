require "Polycode/EventDispatcher"

class "Core" (EventDispatcher)



EVENT_CORE_RESIZE = 0




function Core:Update()
	local retVal =  Polycore.Core_Update(self.__ptr)
	return retVal
end

function Core:enableMouse(newval)
	local retVal = Polycore.Core_enableMouse(self.__ptr, newval)
end

function Core:setCursor(cursorType)
	local retVal = Polycore.Core_setCursor(self.__ptr, cursorType)
end

function Core:createThread(target)
	local retVal = Polycore.Core_createThread(self.__ptr, target.__ptr)
end

function Core:lockMutex(mutex)
	local retVal = Polycore.Core_lockMutex(self.__ptr, mutex.__ptr)
end

function Core:unlockMutex(mutex)
	local retVal = Polycore.Core_unlockMutex(self.__ptr, mutex.__ptr)
end

function Core:createMutex()
	local retVal =  Polycore.Core_createMutex(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreMutex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:copyStringToClipboard(str)
	local retVal = Polycore.Core_copyStringToClipboard(self.__ptr, str)
end

function Core:getClipboardString()
	local retVal =  Polycore.Core_getClipboardString(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:getServices()
	local retVal =  Polycore.Core_getServices(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreServices("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:getFPS()
	local retVal =  Polycore.Core_getFPS(self.__ptr)
	return retVal
end

function Core:Shutdown()
	local retVal =  Polycore.Core_Shutdown(self.__ptr)
end

function Core:isFullscreen()
	local retVal =  Polycore.Core_isFullscreen(self.__ptr)
	return retVal
end

function Core:getAALevel()
	local retVal =  Polycore.Core_getAALevel(self.__ptr)
	return retVal
end

function Core:getInput()
	local retVal =  Polycore.Core_getInput(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreInput("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:getXRes()
	local retVal =  Polycore.Core_getXRes(self.__ptr)
	return retVal
end

function Core:getYRes()
	local retVal =  Polycore.Core_getYRes(self.__ptr)
	return retVal
end

function Core:getNumVideoModes()
	local retVal =  Polycore.Core_getNumVideoModes(self.__ptr)
	return retVal
end

function Core:createFolder(folderPath)
	local retVal = Polycore.Core_createFolder(self.__ptr, folderPath)
end

function Core:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Core_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Core_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:removeDiskItem(itemPath)
	local retVal = Polycore.Core_removeDiskItem(self.__ptr, itemPath)
end

function Core:openFolderPicker()
	local retVal =  Polycore.Core_openFolderPicker(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = String("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:setVideoModeIndex(index, fullScreen, aaLevel)
	local retVal = Polycore.Core_setVideoModeIndex(self.__ptr, index, fullScreen, aaLevel)
end

function Core:setVideoMode(xRes, yRes, fullScreen, aaLevel)
	local retVal = Polycore.Core_setVideoMode(self.__ptr, xRes, yRes, fullScreen, aaLevel)
end

function Core:resizeTo(xRes, yRes)
	local retVal = Polycore.Core_resizeTo(self.__ptr, xRes, yRes)
end

function Core:doSleep()
	local retVal =  Polycore.Core_doSleep(self.__ptr)
end

function Core:getElapsed()
	local retVal =  Polycore.Core_getElapsed(self.__ptr)
	return retVal
end

function Core:getTicks()
	local retVal =  Polycore.Core_getTicks(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = unsignedint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Core:getTicksFloat()
	local retVal =  Polycore.Core_getTicksFloat(self.__ptr)
	return retVal
end

function Core:setUserPointer(ptr)
	local retVal = Polycore.Core_setUserPointer(self.__ptr, ptr.__ptr)
end

function Core:getUserPointer()
	local retVal =  Polycore.Core_getUserPointer(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = void("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

