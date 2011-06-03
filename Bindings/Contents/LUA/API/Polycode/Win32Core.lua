require "Polycode/Core"

class "Win32Core" (Core)







function Win32Core:Win32Core(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Core" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Win32Core(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Win32Core:enableMouse(newval)
	local retVal = Polycore.Win32Core_enableMouse(self.__ptr, newval)
end

function Win32Core:getTicks()
	local retVal =  Polycore.Win32Core_getTicks(self.__ptr)
	return retVal
end

function Win32Core:Update()
	local retVal =  Polycore.Win32Core_Update(self.__ptr)
	return retVal
end

function Win32Core:handleKeyDown(lParam, wParam)
	local retVal = Polycore.Win32Core_handleKeyDown(self.__ptr, lParam.__ptr, wParam.__ptr)
end

function Win32Core:handleKeyUp(lParam, wParam)
	local retVal = Polycore.Win32Core_handleKeyUp(self.__ptr, lParam.__ptr, wParam.__ptr)
end

function Win32Core:handleMouseMove(lParam, wParam)
	local retVal = Polycore.Win32Core_handleMouseMove(self.__ptr, lParam.__ptr, wParam.__ptr)
end

function Win32Core:handleMouseWheel(lParam, wParam)
	local retVal = Polycore.Win32Core_handleMouseWheel(self.__ptr, lParam.__ptr, wParam.__ptr)
end

function Win32Core:handleMouseDown(mouseCode, lParam, wParam)
	local retVal = Polycore.Win32Core_handleMouseDown(self.__ptr, mouseCode, lParam.__ptr, wParam.__ptr)
end

function Win32Core:handleMouseUp(mouseCode, lParam, wParam)
	local retVal = Polycore.Win32Core_handleMouseUp(self.__ptr, mouseCode, lParam.__ptr, wParam.__ptr)
end

function Win32Core:setVideoMode(xRes, yRes, fullScreen, aaLevel)
	local retVal = Polycore.Win32Core_setVideoMode(self.__ptr, xRes, yRes, fullScreen, aaLevel)
end

function Win32Core:initContext(usePixelFormat, pixelFormat)
	local retVal = Polycore.Win32Core_initContext(self.__ptr, usePixelFormat, pixelFormat)
end

function Win32Core:destroyContext()
	local retVal =  Polycore.Win32Core_destroyContext(self.__ptr)
end

function Win32Core:createThread(target)
	local retVal = Polycore.Win32Core_createThread(self.__ptr, target.__ptr)
end

function Win32Core:mapKey(lParam, wParam)
	local retVal = Polycore.Win32Core_mapKey(self.__ptr, lParam.__ptr, wParam.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PolyKEY("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Win32Core:lockMutex(mutex)
	local retVal = Polycore.Win32Core_lockMutex(self.__ptr, mutex.__ptr)
end

function Win32Core:unlockMutex(mutex)
	local retVal = Polycore.Win32Core_unlockMutex(self.__ptr, mutex.__ptr)
end

function Win32Core:createMutex()
	local retVal =  Polycore.Win32Core_createMutex(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreMutex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Win32Core:checkEvents()
	local retVal =  Polycore.Win32Core_checkEvents(self.__ptr)
end

function Win32Core:initKeymap()
	local retVal =  Polycore.Win32Core_initKeymap(self.__ptr)
end

function Win32Core:platformSleep(msecs)
	local retVal = Polycore.Win32Core_platformSleep(self.__ptr, msecs)
end

function Win32Core:setCursor(cursorType)
	local retVal = Polycore.Win32Core_setCursor(self.__ptr, cursorType)
end

function Win32Core:copyStringToClipboard(str)
	local retVal = Polycore.Win32Core_copyStringToClipboard(self.__ptr, str)
end

function Win32Core:getClipboardString()
	local retVal =  Polycore.Win32Core_getClipboardString(self.__ptr)
	return retVal
end

function Win32Core:createFolder(folderPath)
	local retVal = Polycore.Win32Core_createFolder(self.__ptr, folderPath)
end

function Win32Core:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Win32Core_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function Win32Core:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycore.Win32Core_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function Win32Core:openFolderPicker()
	local retVal =  Polycore.Win32Core_openFolderPicker(self.__ptr)
	return retVal
end

function Win32Core:removeDiskItem(itemPath)
	local retVal = Polycore.Win32Core_removeDiskItem(self.__ptr, itemPath)
end

function Win32Core:resizeTo(xRes, yRes)
	local retVal = Polycore.Win32Core_resizeTo(self.__ptr, xRes, yRes)
end



function Win32Core:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Win32Core(self.__ptr)
end
