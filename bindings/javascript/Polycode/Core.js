function Core() {
}

Core.prototype.Update = function() {
	Polycode.Core_Update(this.__ptr)
}

Core.prototype.Render = function() {
	Polycode.Core_Render(this.__ptr)
}

Core.prototype.fixedUpdate = function() {
	Polycode.Core_fixedUpdate(this.__ptr)
}

Core.prototype.systemUpdate = function() {
	Polycode.Core_systemUpdate(this.__ptr)
}

Core.prototype.updateAndRender = function() {
	Polycode.Core_updateAndRender(this.__ptr)
}

Core.prototype.enableMouse = function(newval) {
	Polycode.Core_enableMouse(this.__ptr, newval)
}

Core.prototype.captureMouse = function(newval) {
	Polycode.Core_captureMouse(this.__ptr, newval)
}

Core.prototype.setCursor = function(cursorType) {
	Polycode.Core_setCursor(this.__ptr, cursorType)
}

Core.prototype.warpCursor = function(x,y) {
	Polycode.Core_warpCursor(this.__ptr, x,y)
}

Core.prototype.createThread = function(target) {
	Polycode.Core_createThread(this.__ptr, target)
}

Core.prototype.lockMutex = function(mutex) {
	Polycode.Core_lockMutex(this.__ptr, mutex)
}

Core.prototype.unlockMutex = function(mutex) {
	Polycode.Core_unlockMutex(this.__ptr, mutex)
}

Core.prototype.createMutex = function() {
	Polycode.Core_createMutex(this.__ptr)
}

Core.prototype.copyStringToClipboard = function(str) {
	Polycode.Core_copyStringToClipboard(this.__ptr, str)
}

Core.prototype.getClipboardString = function() {
	Polycode.Core_getClipboardString(this.__ptr)
}

Core.prototype.getServices = function() {
	Polycode.Core_getServices(this.__ptr)
}

Core.prototype.getFPS = function() {
	Polycode.Core_getFPS(this.__ptr)
}

Core.prototype.Shutdown = function() {
	Polycode.Core_Shutdown(this.__ptr)
}

Core.prototype.isFullscreen = function() {
	Polycode.Core_isFullscreen(this.__ptr)
}

Core.prototype.getAALevel = function() {
	Polycode.Core_getAALevel(this.__ptr)
}

Core.prototype.getInput = function() {
	Polycode.Core_getInput(this.__ptr)
}

Core.prototype.getXRes = function() {
	Polycode.Core_getXRes(this.__ptr)
}

Core.prototype.getYRes = function() {
	Polycode.Core_getYRes(this.__ptr)
}

Core.prototype.getBackingXRes = function() {
	Polycode.Core_getBackingXRes(this.__ptr)
}

Core.prototype.getBackingYRes = function() {
	Polycode.Core_getBackingYRes(this.__ptr)
}

Core.prototype.getScreenWidth = function() {
	Polycode.Core_getScreenWidth(this.__ptr)
}

Core.prototype.getScreenHeight = function() {
	Polycode.Core_getScreenHeight(this.__ptr)
}

Core.prototype.createFolder = function(folderPath) {
	Polycode.Core_createFolder(this.__ptr, folderPath)
}

Core.prototype.copyDiskItem = function(itemPath,destItemPath) {
	Polycode.Core_copyDiskItem(this.__ptr, itemPath,destItemPath)
}

Core.prototype.moveDiskItem = function(itemPath,destItemPath) {
	Polycode.Core_moveDiskItem(this.__ptr, itemPath,destItemPath)
}

Core.prototype.removeDiskItem = function(itemPath) {
	Polycode.Core_removeDiskItem(this.__ptr, itemPath)
}

Core.prototype.openFolderPicker = function() {
	Polycode.Core_openFolderPicker(this.__ptr)
}

Core.prototype.setFramerate = function(frameRate,maxFixedCycles) {
	Polycode.Core_setFramerate(this.__ptr, frameRate,maxFixedCycles)
}

Core.prototype.openFilePicker = function(extensions,allowMultiple) {
	Polycode.Core_openFilePicker(this.__ptr, extensions,allowMultiple)
}

Core.prototype.saveFilePicker = function(extensions) {
	Polycode.Core_saveFilePicker(this.__ptr, extensions)
}

Core.prototype.handleVideoModeChange = function(modeInfo) {
	Polycode.Core_handleVideoModeChange(this.__ptr, modeInfo)
}

Core.prototype.flushRenderContext = function() {
	Polycode.Core_flushRenderContext(this.__ptr)
}

Core.prototype.prepareRenderContext = function() {
	Polycode.Core_prepareRenderContext(this.__ptr)
}

Core.prototype.openFile = function(fileName,opts) {
	Polycode.Core_openFile(this.__ptr, fileName,opts)
}

Core.prototype.closeFile = function(file) {
	Polycode.Core_closeFile(this.__ptr, file)
}

Core.prototype.addFileSource = function(type,source) {
	Polycode.Core_addFileSource(this.__ptr, type,source)
}

Core.prototype.removeFileSource = function(type,source) {
	Polycode.Core_removeFileSource(this.__ptr, type,source)
}

Core.prototype.parseFolder = function(pathString,showHidden) {
	Polycode.Core_parseFolder(this.__ptr, pathString,showHidden)
}

Core.prototype.systemParseFolder = function(pathString,showHidden,targetVector) {
	Polycode.Core_systemParseFolder(this.__ptr, pathString,showHidden,targetVector)
}

Core.prototype.getResourcePathForFile = function(fileName) {
	Polycode.Core_getResourcePathForFile(this.__ptr, fileName)
}

Core.prototype.setVideoMode = function(xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport) {
	Polycode.Core_setVideoMode(this.__ptr, xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport)
}

Core.prototype.resizeTo = function(xRes,yRes) {
	Polycode.Core_resizeTo(this.__ptr, xRes,yRes)
}

Core.prototype.doSleep = function() {
	Polycode.Core_doSleep(this.__ptr)
}

Core.prototype.openURL = function(url) {
	Polycode.Core_openURL(this.__ptr, url)
}

Core.prototype.getElapsed = function() {
	Polycode.Core_getElapsed(this.__ptr)
}

Core.prototype.getTicks = function() {
	Polycode.Core_getTicks(this.__ptr)
}

Core.prototype.getRefreshIntervalMs = function() {
	Polycode.Core_getRefreshIntervalMs(this.__ptr)
}

Core.prototype.getTimeSleptMs = function() {
	Polycode.Core_getTimeSleptMs(this.__ptr)
}

Core.prototype.getFixedTimestep = function() {
	Polycode.Core_getFixedTimestep(this.__ptr)
}

Core.prototype.getTicksFloat = function() {
	Polycode.Core_getTicksFloat(this.__ptr)
}

Core.prototype.setUserPointer = function(ptr) {
	Polycode.Core_setUserPointer(this.__ptr, ptr)
}

Core.prototype.getUserPointer = function() {
	Polycode.Core_getUserPointer(this.__ptr)
}

Core.prototype.executeExternalCommand = function(command,args,inDirectory) {
	Polycode.Core_executeExternalCommand(this.__ptr, command,args,inDirectory)
}

Core.prototype.getDefaultWorkingDirectory = function() {
	Polycode.Core_getDefaultWorkingDirectory(this.__ptr)
}

Core.prototype.getUserHomeDirectory = function() {
	Polycode.Core_getUserHomeDirectory(this.__ptr)
}

Core.prototype.makeApplicationMain = function() {
	Polycode.Core_makeApplicationMain(this.__ptr)
}

Core.prototype.getEventMutex = function() {
	Polycode.Core_getEventMutex(this.__ptr)
}

Core.prototype.removeThread = function(thread) {
	Polycode.Core_removeThread(this.__ptr, thread)
}
