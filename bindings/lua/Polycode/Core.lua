require "Polycode/EventDispatcher"

class "Core" (EventDispatcher)

Core.EVENTBASE_CORE = 0x200
Core.EVENT_CORE_RESIZE = Core.EVENTBASE_CORE + 0
Core.EVENT_LOST_FOCUS = Core.EVENTBASE_CORE + 1
Core.EVENT_GAINED_FOCUS = Core.EVENTBASE_CORE + 2
Core.EVENT_UNDO = Core.EVENTBASE_CORE + 3
Core.EVENT_REDO = Core.EVENTBASE_CORE + 4
Core.EVENT_COPY = Core.EVENTBASE_CORE + 5
Core.EVENT_CUT = Core.EVENTBASE_CORE + 6
Core.EVENT_SELECT_ALL = Core.EVENTBASE_CORE + 7
Core.EVENT_PASTE = Core.EVENTBASE_CORE + 8
Core.EVENT_GYRO_ROTATION = Core.EVENTBASE_CORE + 9
Core.EVENT_ACCELEROMETER_MOTION = Core.EVENTBASE_CORE + 10
Core.CURSOR_ARROW = 0
Core.CURSOR_TEXT = 1
Core.CURSOR_POINTER = 2
Core.CURSOR_CROSSHAIR = 3
Core.CURSOR_RESIZE_LEFT_RIGHT = 4
Core.CURSOR_RESIZE_UP_DOWN = 5
Core.CURSOR_OPEN_HAND = 6

function Core:__getvar(name)
	if name == "eventMutex" then
		local retVal = Polycode.Core_get_eventMutex(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["CoreMutex"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "paused" then
		return Polycode.Core_get_paused(self.__ptr)
	elseif name == "pauseOnLoseFocus" then
		return Polycode.Core_get_pauseOnLoseFocus(self.__ptr)
	elseif name == "defaultScreenWidth" then
		return Polycode.Core_get_defaultScreenWidth(self.__ptr)
	elseif name == "defaultScreenHeight" then
		return Polycode.Core_get_defaultScreenHeight(self.__ptr)
	elseif name == "deviceAttitude" then
		local retVal = Polycode.Core_get_deviceAttitude(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
	if EventDispatcher["__getvar"] ~= nil then
		return EventDispatcher.__getvar(self, name)
	end
end

function Core:__setvar(name,value)
	if name == "eventMutex" then
		Polycode.Core_set_eventMutex(self.__ptr, value.__ptr)
		return true
	elseif name == "paused" then
		Polycode.Core_set_paused(self.__ptr, value)
		return true
	elseif name == "pauseOnLoseFocus" then
		Polycode.Core_set_pauseOnLoseFocus(self.__ptr, value)
		return true
	elseif name == "defaultScreenWidth" then
		Polycode.Core_set_defaultScreenWidth(self.__ptr, value)
		return true
	elseif name == "defaultScreenHeight" then
		Polycode.Core_set_defaultScreenHeight(self.__ptr, value)
		return true
	elseif name == "deviceAttitude" then
		Polycode.Core_set_deviceAttitude(self.__ptr, value.__ptr)
		return true
	end
	if EventDispatcher["__setvar"] ~= nil then
		return EventDispatcher.__setvar(self, name, value)
	else
		return false
	end
end
function Core:Update()
	local retVal =  Polycode.Core_Update(self.__ptr)
	return retVal
end

function Core:Render()
	local retVal =  Polycode.Core_Render(self.__ptr)
end

function Core:fixedUpdate()
	local retVal =  Polycode.Core_fixedUpdate(self.__ptr)
	return retVal
end

function Core:systemUpdate()
	local retVal =  Polycode.Core_systemUpdate(self.__ptr)
	return retVal
end

function Core:updateAndRender()
	local retVal =  Polycode.Core_updateAndRender(self.__ptr)
	return retVal
end

function Core:enableMouse(newval)
	local retVal = Polycode.Core_enableMouse(self.__ptr, newval)
end

function Core:captureMouse(newval)
	local retVal = Polycode.Core_captureMouse(self.__ptr, newval)
end

function Core:setCursor(cursorType)
	local retVal = Polycode.Core_setCursor(self.__ptr, cursorType)
end

function Core:warpCursor(x, y)
	local retVal = Polycode.Core_warpCursor(self.__ptr, x, y)
end

function Core:openOnScreenKeyboard(open)
	local retVal = Polycode.Core_openOnScreenKeyboard(self.__ptr, open)
end

function Core:createThread(target)
	local retVal = Polycode.Core_createThread(self.__ptr, target.__ptr)
end

function Core:lockMutex(mutex)
	local retVal = Polycode.Core_lockMutex(self.__ptr, mutex.__ptr)
end

function Core:unlockMutex(mutex)
	local retVal = Polycode.Core_unlockMutex(self.__ptr, mutex.__ptr)
end

function Core:createMutex()
	local retVal =  Polycode.Core_createMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:copyStringToClipboard(str)
	local retVal = Polycode.Core_copyStringToClipboard(self.__ptr, str)
end

function Core:getClipboardString()
	local retVal =  Polycode.Core_getClipboardString(self.__ptr)
	return retVal
end

function Core:getServices()
	local retVal =  Polycode.Core_getServices(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreServices"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:getFPS()
	local retVal =  Polycode.Core_getFPS(self.__ptr)
	return retVal
end

function Core:Shutdown()
	local retVal =  Polycode.Core_Shutdown(self.__ptr)
end

function Core:isFullscreen()
	local retVal =  Polycode.Core_isFullscreen(self.__ptr)
	return retVal
end

function Core:getAALevel()
	local retVal =  Polycode.Core_getAALevel(self.__ptr)
	return retVal
end

function Core:getInput()
	local retVal =  Polycode.Core_getInput(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreInput"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:getXRes()
	local retVal =  Polycode.Core_getXRes(self.__ptr)
	return retVal
end

function Core:getYRes()
	local retVal =  Polycode.Core_getYRes(self.__ptr)
	return retVal
end

function Core:getBackingXRes()
	local retVal =  Polycode.Core_getBackingXRes(self.__ptr)
	return retVal
end

function Core:getBackingYRes()
	local retVal =  Polycode.Core_getBackingYRes(self.__ptr)
	return retVal
end

function Core:getScreenInfo(width, height, hz)
	local retVal = Polycode.Core_getScreenInfo(self.__ptr, width.__ptr, height.__ptr, hz.__ptr)
end

function Core:getScreenWidth()
	local retVal =  Polycode.Core_getScreenWidth(self.__ptr)
	return retVal
end

function Core:getScreenHeight()
	local retVal =  Polycode.Core_getScreenHeight(self.__ptr)
	return retVal
end

function Core:createFolder(folderPath)
	local retVal = Polycode.Core_createFolder(self.__ptr, folderPath)
end

function Core:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycode.Core_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycode.Core_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function Core:removeDiskItem(itemPath)
	local retVal = Polycode.Core_removeDiskItem(self.__ptr, itemPath)
end

function Core:openFolderPicker()
	local retVal =  Polycode.Core_openFolderPicker(self.__ptr)
	return retVal
end

function Core:setFramerate(frameRate, maxFixedCycles)
	local retVal = Polycode.Core_setFramerate(self.__ptr, frameRate, maxFixedCycles)
end

function Core:openFilePicker(extensions, allowMultiple)
	local retVal = Polycode.Core_openFilePicker(self.__ptr, extensions.__ptr, allowMultiple)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["String"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Core:saveFilePicker(extensions)
	local retVal = Polycode.Core_saveFilePicker(self.__ptr, extensions.__ptr)
	return retVal
end

function Core:handleVideoModeChange(modeInfo)
	local retVal = Polycode.Core_handleVideoModeChange(self.__ptr, modeInfo.__ptr)
end

function Core:flushRenderContext()
	local retVal =  Polycode.Core_flushRenderContext(self.__ptr)
end

function Core:prepareRenderContext()
	local retVal =  Polycode.Core_prepareRenderContext(self.__ptr)
end

function Core:isWindowInitialized()
	local retVal =  Polycode.Core_isWindowInitialized(self.__ptr)
	return retVal
end

function Core:openFile(fileName, opts)
	local retVal = Polycode.Core_openFile(self.__ptr, fileName, opts)
	if retVal == nil then return nil end
	local __c = _G["CoreFile"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:closeFile(file)
	local retVal = Polycode.Core_closeFile(self.__ptr, file.__ptr)
end

function Core:addFileSource(type, source)
	local retVal = Polycode.Core_addFileSource(self.__ptr, type, source)
end

function Core:removeFileSource(type, source)
	local retVal = Polycode.Core_removeFileSource(self.__ptr, type, source)
end

function Core:parseFolder(pathString, showHidden)
	local retVal = Polycode.Core_parseFolder(self.__ptr, pathString, showHidden)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["OSFileEntry"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function Core:systemParseFolder(pathString, showHidden, targetVector)
	local retVal = Polycode.Core_systemParseFolder(self.__ptr, pathString, showHidden, targetVector.__ptr)
	return retVal
end

function Core:getResourcePathForFile(fileName)
	local retVal = Polycode.Core_getResourcePathForFile(self.__ptr, fileName)
	return retVal
end

function Core:setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport)
	local retVal = Polycode.Core_setVideoMode(self.__ptr, xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport)
end

function Core:resizeTo(xRes, yRes)
	local retVal = Polycode.Core_resizeTo(self.__ptr, xRes, yRes)
end

function Core:doSleep()
	local retVal =  Polycode.Core_doSleep(self.__ptr)
end

function Core:openURL(url)
	local retVal = Polycode.Core_openURL(self.__ptr, url)
end

function Core:getElapsed()
	local retVal =  Polycode.Core_getElapsed(self.__ptr)
	return retVal
end

function Core:getTicks()
	local retVal =  Polycode.Core_getTicks(self.__ptr)
	return retVal
end

function Core:getRefreshIntervalMs()
	local retVal =  Polycode.Core_getRefreshIntervalMs(self.__ptr)
	return retVal
end

function Core:getTimeSleptMs()
	local retVal =  Polycode.Core_getTimeSleptMs(self.__ptr)
	return retVal
end

function Core:getFixedTimestep()
	local retVal =  Polycode.Core_getFixedTimestep(self.__ptr)
	return retVal
end

function Core:getTicksFloat()
	local retVal =  Polycode.Core_getTicksFloat(self.__ptr)
	return retVal
end

function Core:setUserPointer(ptr)
	local retVal = Polycode.Core_setUserPointer(self.__ptr, ptr.__ptr)
end

function Core:getUserPointer()
	local retVal =  Polycode.Core_getUserPointer(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["void"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:executeExternalCommand(command, args, inDirectory)
	local retVal = Polycode.Core_executeExternalCommand(self.__ptr, command, args, inDirectory)
	return retVal
end

function Core:getDefaultWorkingDirectory()
	local retVal =  Polycode.Core_getDefaultWorkingDirectory(self.__ptr)
	return retVal
end

function Core:getUserHomeDirectory()
	local retVal =  Polycode.Core_getUserHomeDirectory(self.__ptr)
	return retVal
end

function Core:makeApplicationMain()
	local retVal =  Polycode.Core_makeApplicationMain(self.__ptr)
end

function Core:getEventMutex()
	local retVal =  Polycode.Core_getEventMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Core:removeThread(thread)
	local retVal = Polycode.Core_removeThread(self.__ptr, thread.__ptr)
end

function Core:__delete()
	if self then Polycode.delete_Core(self.__ptr) end
end
