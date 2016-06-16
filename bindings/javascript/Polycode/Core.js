require('Polycode/EventDispatcher')

function Core() {
	Object.defineProperties(this, {
		'eventMutex': { enumerable: true, configurable: true, get: Core.prototype.__get_eventMutex, set: Core.prototype.__set_eventMutex},
		'paused': { enumerable: true, configurable: true, get: Core.prototype.__get_paused, set: Core.prototype.__set_paused},
		'pauseOnLoseFocus': { enumerable: true, configurable: true, get: Core.prototype.__get_pauseOnLoseFocus, set: Core.prototype.__set_pauseOnLoseFocus},
		'defaultScreenWidth': { enumerable: true, configurable: true, get: Core.prototype.__get_defaultScreenWidth, set: Core.prototype.__set_defaultScreenWidth},
		'defaultScreenHeight': { enumerable: true, configurable: true, get: Core.prototype.__get_defaultScreenHeight, set: Core.prototype.__set_defaultScreenHeight},
		'deviceAttitude': { enumerable: true, configurable: true, get: Core.prototype.__get_deviceAttitude, set: Core.prototype.__set_deviceAttitude}
	})
}

Core.prototype = Object.create(EventDispatcher.prototype);

Core.prototype.__get_eventMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = 	Polycode.Core__get_eventMutex(this.__ptr)
	return retVal
}

Core.prototype.__set_eventMutex = function(val) {
	Polycode.Core__set_eventMutex(this.__ptr, val.__ptr)
}

Core.prototype.__get_paused = function() {
	return Polycode.Core__get_paused(this.__ptr)
}

Core.prototype.__set_paused = function(val) {
	Polycode.Core__set_paused(this.__ptr, val)
}

Core.prototype.__get_pauseOnLoseFocus = function() {
	return Polycode.Core__get_pauseOnLoseFocus(this.__ptr)
}

Core.prototype.__set_pauseOnLoseFocus = function(val) {
	Polycode.Core__set_pauseOnLoseFocus(this.__ptr, val)
}

Core.prototype.__get_defaultScreenWidth = function() {
	return Polycode.Core__get_defaultScreenWidth(this.__ptr)
}

Core.prototype.__set_defaultScreenWidth = function(val) {
	Polycode.Core__set_defaultScreenWidth(this.__ptr, val)
}

Core.prototype.__get_defaultScreenHeight = function() {
	return Polycode.Core__get_defaultScreenHeight(this.__ptr)
}

Core.prototype.__set_defaultScreenHeight = function(val) {
	Polycode.Core__set_defaultScreenHeight(this.__ptr, val)
}

Core.prototype.__get_deviceAttitude = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.Core__get_deviceAttitude(this.__ptr)
	return retVal
}

Core.prototype.__set_deviceAttitude = function(val) {
	Polycode.Core__set_deviceAttitude(this.__ptr, val.__ptr)
}

Duktape.fin(Core.prototype, function (x) {
	if (x === Core.prototype) {
		return;
	}
	Polycode.Core__delete(x.__ptr)
})

Core.prototype.Update = function() {
	return Polycode.Core_Update(this.__ptr)
}

Core.prototype.Render = function() {
	Polycode.Core_Render(this.__ptr)
}

Core.prototype.fixedUpdate = function() {
	return Polycode.Core_fixedUpdate(this.__ptr)
}

Core.prototype.systemUpdate = function() {
	return Polycode.Core_systemUpdate(this.__ptr)
}

Core.prototype.updateAndRender = function() {
	return Polycode.Core_updateAndRender(this.__ptr)
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
	Polycode.Core_warpCursor(this.__ptr, x, y)
}

Core.prototype.openOnScreenKeyboard = function(open) {
	Polycode.Core_openOnScreenKeyboard(this.__ptr, open)
}

Core.prototype.createThread = function(target) {
	Polycode.Core_createThread(this.__ptr, target.__ptr)
}

Core.prototype.lockMutex = function(mutex) {
	Polycode.Core_lockMutex(this.__ptr, mutex.__ptr)
}

Core.prototype.unlockMutex = function(mutex) {
	Polycode.Core_unlockMutex(this.__ptr, mutex.__ptr)
}

Core.prototype.createMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = Polycode.Core_createMutex(this.__ptr)
	return retVal
}

Core.prototype.copyStringToClipboard = function(str) {
	Polycode.Core_copyStringToClipboard(this.__ptr, str)
}

Core.prototype.getClipboardString = function() {
	return Polycode.Core_getClipboardString(this.__ptr)
}

Core.prototype.getServices = function() {
	var retVal = new CoreServices()
	retVal.__ptr = Polycode.Core_getServices(this.__ptr)
	return retVal
}

Core.prototype.getFPS = function() {
	return Polycode.Core_getFPS(this.__ptr)
}

Core.prototype.Shutdown = function() {
	Polycode.Core_Shutdown(this.__ptr)
}

Core.prototype.isFullscreen = function() {
	return Polycode.Core_isFullscreen(this.__ptr)
}

Core.prototype.getAALevel = function() {
	return Polycode.Core_getAALevel(this.__ptr)
}

Core.prototype.getInput = function() {
	var retVal = new CoreInput()
	retVal.__ptr = Polycode.Core_getInput(this.__ptr)
	return retVal
}

Core.prototype.getXRes = function() {
	return Polycode.Core_getXRes(this.__ptr)
}

Core.prototype.getYRes = function() {
	return Polycode.Core_getYRes(this.__ptr)
}

Core.prototype.getBackingXRes = function() {
	return Polycode.Core_getBackingXRes(this.__ptr)
}

Core.prototype.getBackingYRes = function() {
	return Polycode.Core_getBackingYRes(this.__ptr)
}

Core.prototype.getScreenInfo = function(width,height,hz) {
	Polycode.Core_getScreenInfo(width.__ptr, height.__ptr, hz.__ptr)
}

Core.prototype.getScreenWidth = function() {
	return Polycode.Core_getScreenWidth(this.__ptr)
}

Core.prototype.getScreenHeight = function() {
	return Polycode.Core_getScreenHeight(this.__ptr)
}

Core.prototype.createFolder = function(folderPath) {
	Polycode.Core_createFolder(this.__ptr, folderPath)
}

Core.prototype.copyDiskItem = function(itemPath,destItemPath) {
	Polycode.Core_copyDiskItem(this.__ptr, itemPath, destItemPath)
}

Core.prototype.moveDiskItem = function(itemPath,destItemPath) {
	Polycode.Core_moveDiskItem(this.__ptr, itemPath, destItemPath)
}

Core.prototype.removeDiskItem = function(itemPath) {
	Polycode.Core_removeDiskItem(this.__ptr, itemPath)
}

Core.prototype.openFolderPicker = function() {
	return Polycode.Core_openFolderPicker(this.__ptr)
}

Core.prototype.setFramerate = function(frameRate,maxFixedCycles) {
	Polycode.Core_setFramerate(this.__ptr, frameRate, maxFixedCycles)
}

Core.prototype.openFilePicker = function(extensions,allowMultiple) {
	Polycode.Core_openFilePicker(this.__ptr, extensions, allowMultiple)
}

Core.prototype.saveFilePicker = function(extensions) {
	return Polycode.Core_saveFilePicker(this.__ptr, extensions)
}

Core.prototype.handleVideoModeChange = function(modeInfo) {
	Polycode.Core_handleVideoModeChange(this.__ptr, modeInfo.__ptr)
}

Core.prototype.flushRenderContext = function() {
	Polycode.Core_flushRenderContext(this.__ptr)
}

Core.prototype.prepareRenderContext = function() {
	Polycode.Core_prepareRenderContext(this.__ptr)
}

Core.prototype.isWindowInitialized = function() {
	return Polycode.Core_isWindowInitialized(this.__ptr)
}

Core.prototype.openFile = function(fileName,opts) {
	var retVal = new CoreFile()
	retVal.__ptr = Polycode.Core_openFile(this.__ptr, fileName, opts)
	return retVal
}

Core.prototype.closeFile = function(file) {
	Polycode.Core_closeFile(this.__ptr, file.__ptr)
}

Core.prototype.addFileSource = function(type,source) {
	Polycode.Core_addFileSource(this.__ptr, type, source)
}

Core.prototype.removeFileSource = function(type,source) {
	Polycode.Core_removeFileSource(this.__ptr, type, source)
}

Core.prototype.parseFolder = function(pathString,showHidden) {
	Polycode.Core_parseFolder(this.__ptr, pathString, showHidden)
}

Core.prototype.systemParseFolder = function(pathString,showHidden,targetVector) {
	return Polycode.Core_systemParseFolder(this.__ptr, pathString, showHidden, targetVector)
}

Core.prototype.getResourcePathForFile = function(fileName) {
	return Polycode.Core_getResourcePathForFile(this.__ptr, fileName)
}

Core.prototype.setVideoMode = function(xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport) {
	Polycode.Core_setVideoMode(this.__ptr, xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport)
}

Core.prototype.resizeTo = function(xRes,yRes) {
	Polycode.Core_resizeTo(this.__ptr, xRes, yRes)
}

Core.prototype.doSleep = function() {
	Polycode.Core_doSleep(this.__ptr)
}

Core.prototype.openURL = function(url) {
	Polycode.Core_openURL(this.__ptr, url)
}

Core.prototype.getElapsed = function() {
	return Polycode.Core_getElapsed(this.__ptr)
}

Core.prototype.getTicks = function() {
	return Polycode.Core_getTicks(this.__ptr)
}

Core.prototype.getRefreshIntervalMs = function() {
	return Polycode.Core_getRefreshIntervalMs(this.__ptr)
}

Core.prototype.getTimeSleptMs = function() {
	return Polycode.Core_getTimeSleptMs(this.__ptr)
}

Core.prototype.getFixedTimestep = function() {
	return Polycode.Core_getFixedTimestep(this.__ptr)
}

Core.prototype.getTicksFloat = function() {
	return Polycode.Core_getTicksFloat(this.__ptr)
}

Core.prototype.setUserPointer = function(ptr) {
	Polycode.Core_setUserPointer(this.__ptr, ptr.__ptr)
}

Core.prototype.getUserPointer = function() {
	Polycode.Core_getUserPointer(this.__ptr)
}

Core.prototype.executeExternalCommand = function(command,args,inDirectory) {
	return Polycode.Core_executeExternalCommand(this.__ptr, command, args, inDirectory)
}

Core.prototype.getDefaultWorkingDirectory = function() {
	return Polycode.Core_getDefaultWorkingDirectory(this.__ptr)
}

Core.prototype.getUserHomeDirectory = function() {
	return Polycode.Core_getUserHomeDirectory(this.__ptr)
}

Core.prototype.makeApplicationMain = function() {
	Polycode.Core_makeApplicationMain(this.__ptr)
}

Core.prototype.getEventMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = Polycode.Core_getEventMutex(this.__ptr)
	return retVal
}

Core.prototype.removeThread = function(thread) {
	Polycode.Core_removeThread(this.__ptr, thread.__ptr)
}
