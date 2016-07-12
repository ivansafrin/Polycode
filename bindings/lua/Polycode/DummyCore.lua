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
		self.__ptr = Polycode.DummyCore(unpack(arg))
	end
end

function DummyCore:systemUpdate()
	local retVal =  Polycode.DummyCore_systemUpdate(self.__ptr)
	return retVal
end

function DummyCore:setCursor(cursorType)
	local retVal = Polycode.DummyCore_setCursor(self.__ptr, cursorType)
end

function DummyCore:copyStringToClipboard(str)
	local retVal = Polycode.DummyCore_copyStringToClipboard(self.__ptr, str)
end

function DummyCore:getClipboardString()
	local retVal =  Polycode.DummyCore_getClipboardString(self.__ptr)
	return retVal
end

function DummyCore:createFolder(folderPath)
	local retVal = Polycode.DummyCore_createFolder(self.__ptr, folderPath)
end

function DummyCore:copyDiskItem(itemPath, destItemPath)
	local retVal = Polycode.DummyCore_copyDiskItem(self.__ptr, itemPath, destItemPath)
end

function DummyCore:moveDiskItem(itemPath, destItemPath)
	local retVal = Polycode.DummyCore_moveDiskItem(self.__ptr, itemPath, destItemPath)
end

function DummyCore:removeDiskItem(itemPath)
	local retVal = Polycode.DummyCore_removeDiskItem(self.__ptr, itemPath)
end

function DummyCore:openFolderPicker()
	local retVal =  Polycode.DummyCore_openFolderPicker(self.__ptr)
	return retVal
end

function DummyCore:openFilePicker(extensions, allowMultiple)
	local retVal = Polycode.DummyCore_openFilePicker(self.__ptr, extensions.__ptr, allowMultiple)
	if retVal == nil then return nil end
	for i=1,count(retVal) do
		local __c  = _G["String"]("__skip_ptr__")
		__c.__ptr = retVal[i]
		retVal[i] = __c
	end
	return retVal
end

function DummyCore:saveFilePicker(extensions)
	local retVal = Polycode.DummyCore_saveFilePicker(self.__ptr, extensions.__ptr)
	return retVal
end

function DummyCore:flushRenderContext()
	local retVal =  Polycode.DummyCore_flushRenderContext(self.__ptr)
end

function DummyCore:openURL(url)
	local retVal = Polycode.DummyCore_openURL(self.__ptr, url)
end

function DummyCore:getTicks()
	local retVal =  Polycode.DummyCore_getTicks(self.__ptr)
	return retVal
end

function DummyCore:executeExternalCommand(command, args, inDirectory)
	local retVal = Polycode.DummyCore_executeExternalCommand(self.__ptr, command, args, inDirectory)
	return retVal
end

function DummyCore:systemParseFolder(pathString, showHidden, targetVector)
	local retVal = Polycode.DummyCore_systemParseFolder(self.__ptr, pathString, showHidden, targetVector.__ptr)
	return retVal
end

function DummyCore:__delete()
	if self then Polycode.delete_DummyCore(self.__ptr) end
end
