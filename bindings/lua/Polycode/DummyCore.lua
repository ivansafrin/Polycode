require "Polycode/Core"

class "DummyCore" (Core)







function DummyCore:DummyCore(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Core" then
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
		self.__ptr = Polycore.DummyCore(unpack(arg))
	end
end

function DummyCore:Render()
	local retVal =  Polycore.DummyCore_Render(self.__ptr)
end

function DummyCore:systemUpdate()
	local retVal =  Polycore.DummyCore_systemUpdate(self.__ptr)
	return retVal
end

function DummyCore:setCursor(cursorType)
	local retVal = Polycore.DummyCore_setCursor(self.__ptr, cursorType)
end

function DummyCore:createThread(target)
	local retVal = Polycore.DummyCore_createThread(self.__ptr, target.__ptr)
end

function DummyCore:createMutex()
	local retVal =  Polycore.DummyCore_createMutex(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["CoreMutex"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function DummyCore:copyStringToClipboard(str)
	local retVal = Polycore.DummyCore_copyStringToClipboard(self.__ptr, str)
end

function DummyCore:getClipboardString()
	local retVal =  Polycore.DummyCore_getClipboardString(self.__ptr)
	return retVal
end

function DummyCore:createFolder(folderPath)
	local retVal = Polycore.DummyCore_createFolder(self.__ptr, folderPath)
end

function DummyCore:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycore.DummyCore_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function DummyCore:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycore.DummyCore_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function DummyCore:removeDiskItem(itemPath)
	local retVal = Polycore.DummyCore_removeDiskItem(self.__ptr, itemPath)
end

function DummyCore:openFolderPicker()
	local retVal =  Polycore.DummyCore_openFolderPicker(self.__ptr)
	return retVal
end

function DummyCore:openFilePicker(extensions, allowMultiple)
	local retVal = Polycore.DummyCore_openFilePicker(self.__ptr, extensions.__ptr, allowMultiple)
	if retVal == nil then return nil end
	local __c = _G["std::vector<String>"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function DummyCore:saveFilePicker(extensions)
	local retVal = Polycore.DummyCore_saveFilePicker(self.__ptr, extensions.__ptr)
	return retVal
end

function DummyCore:handleVideoModeChange(modeInfo)
	local retVal = Polycore.DummyCore_handleVideoModeChange(self.__ptr, modeInfo.__ptr)
end

function DummyCore:flushRenderContext()
	local retVal =  Polycore.DummyCore_flushRenderContext(self.__ptr)
end

function DummyCore:openURL(url)
	local retVal = Polycore.DummyCore_openURL(self.__ptr, url)
end

function DummyCore:getTicks()
	local retVal =  Polycore.DummyCore_getTicks(self.__ptr)
	return retVal
end

function DummyCore:executeExternalCommand(command, args, inDirectory)
	local retVal = Polycore.DummyCore_executeExternalCommand(self.__ptr, command, args, inDirectory)
	return retVal
end

function DummyCore:systemParseFolder(pathString, showHidden, targetVector)
	local retVal = Polycore.DummyCore_systemParseFolder(self.__ptr, pathString, showHidden, targetVector.__ptr)
	return retVal
end

function DummyCore:__delete()
	if self then Polycore.delete_DummyCore(self.__ptr) end
end
