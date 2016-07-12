require('Polycode/Core')

function DummyCore() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.DummyCore()
	}
}


DummyCore.prototype = Object.create(Core.prototype)

Duktape.fin(DummyCore.prototype, function (x) {
	if (x === DummyCore.prototype) {
		return;
	}
	Polycode.DummyCore__delete(x.__ptr)
})

DummyCore.prototype.systemUpdate = function() {
	return Polycode.DummyCore_systemUpdate(this.__ptr)
}

DummyCore.prototype.setCursor = function(cursorType) {
	Polycode.DummyCore_setCursor(this.__ptr, cursorType)
}

DummyCore.prototype.copyStringToClipboard = function(str) {
	Polycode.DummyCore_copyStringToClipboard(this.__ptr, str)
}

DummyCore.prototype.getClipboardString = function() {
	return Polycode.DummyCore_getClipboardString(this.__ptr)
}

DummyCore.prototype.createFolder = function(folderPath) {
	Polycode.DummyCore_createFolder(this.__ptr, folderPath)
}

DummyCore.prototype.copyDiskItem = function(itemPath,destItemPath) {
	Polycode.DummyCore_copyDiskItem(this.__ptr, itemPath, destItemPath)
}

DummyCore.prototype.moveDiskItem = function(itemPath,destItemPath) {
	Polycode.DummyCore_moveDiskItem(this.__ptr, itemPath, destItemPath)
}

DummyCore.prototype.removeDiskItem = function(itemPath) {
	Polycode.DummyCore_removeDiskItem(this.__ptr, itemPath)
}

DummyCore.prototype.openFolderPicker = function() {
	return Polycode.DummyCore_openFolderPicker(this.__ptr)
}

DummyCore.prototype.openFilePicker = function(extensions,allowMultiple) {
	Polycode.DummyCore_openFilePicker(this.__ptr, extensions, allowMultiple)
}

DummyCore.prototype.saveFilePicker = function(extensions) {
	return Polycode.DummyCore_saveFilePicker(this.__ptr, extensions)
}

DummyCore.prototype.flushRenderContext = function() {
	Polycode.DummyCore_flushRenderContext(this.__ptr)
}

DummyCore.prototype.openURL = function(url) {
	Polycode.DummyCore_openURL(this.__ptr, url)
}

DummyCore.prototype.getTicks = function() {
	return Polycode.DummyCore_getTicks(this.__ptr)
}

DummyCore.prototype.executeExternalCommand = function(command,args,inDirectory) {
	return Polycode.DummyCore_executeExternalCommand(this.__ptr, command, args, inDirectory)
}

DummyCore.prototype.systemParseFolder = function(pathString,showHidden,targetVector) {
	return Polycode.DummyCore_systemParseFolder(this.__ptr, pathString, showHidden, targetVector)
}
