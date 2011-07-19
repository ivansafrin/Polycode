require "Polycode/Core"

class "SDLCore" (Core)







function SDLCore:SDLCore(...)
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
		self.__ptr = Polycore.SDLCore(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function SDLCore:enableMouse(newval)
	local retVal = Polycore.SDLCore_enableMouse(self.__ptr, newval)
end

function SDLCore:getTicks()
	local retVal =  Polycore.SDLCore_getTicks(self.__ptr)
	return retVal
end

function SDLCore:Update()
	local retVal =  Polycore.SDLCore_Update(self.__ptr)
	return retVal
end

function SDLCore:setVideoMode(xRes, yRes, fullScreen, aaLevel)
	local retVal = Polycore.SDLCore_setVideoMode(self.__ptr, xRes, yRes, fullScreen, aaLevel)
end

function SDLCore:createThread(target)
	local retVal = Polycore.SDLCore_createThread(self.__ptr, target.__ptr)
end

function SDLCore:setCursor(cursorType)
	local retVal = Polycore.SDLCore_setCursor(self.__ptr, cursorType)
end

function SDLCore:lockMutex(mutex)
	local retVal = Polycore.SDLCore_lockMutex(self.__ptr, mutex.__ptr)
end

function SDLCore:unlockMutex(mutex)
	local retVal = Polycore.SDLCore_unlockMutex(self.__ptr, mutex.__ptr)
end

function SDLCore:createMutex()
	local retVal =  Polycore.SDLCore_createMutex(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = CoreMutex("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function SDLCore:copyStringToClipboard(str)
	local retVal = Polycore.SDLCore_copyStringToClipboard(self.__ptr, str)
end

function SDLCore:getClipboardString()
	local retVal =  Polycore.SDLCore_getClipboardString(self.__ptr)
	return retVal
end

function SDLCore:createFolder(folderPath)
	local retVal = Polycore.SDLCore_createFolder(self.__ptr, folderPath)
end

function SDLCore:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycore.SDLCore_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function SDLCore:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycore.SDLCore_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function SDLCore:removeDiskItem(itemPath)
	local retVal = Polycore.SDLCore_removeDiskItem(self.__ptr, itemPath)
end

function SDLCore:openFolderPicker()
	local retVal =  Polycore.SDLCore_openFolderPicker(self.__ptr)
	return retVal
end

function SDLCore:resizeTo(xRes, yRes)
	local retVal = Polycore.SDLCore_resizeTo(self.__ptr, xRes, yRes)
end



function SDLCore:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_SDLCore(self.__ptr)
end
