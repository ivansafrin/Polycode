function CoreServices() {
}

CoreServices.prototype.setRenderer = function(renderer) {
	Polycode.CoreServices_setRenderer(this.__ptr, renderer)
}

CoreServices.prototype.getRenderer = function() {
	var retVal = new Renderer()
	retVal.__ptr = Polycode.CoreServices_getRenderer(this.__ptr)
	return retVal
}

CoreServices.prototype.Update = function(elapsed) {
	Polycode.CoreServices_Update(this.__ptr, elapsed)
}

CoreServices.prototype.fixedUpdate = function() {
	Polycode.CoreServices_fixedUpdate(this.__ptr)
}

CoreServices.prototype.Render = function(viewport) {
	Polycode.CoreServices_Render(this.__ptr, viewport)
}

CoreServices.prototype.setCore = function(core) {
	Polycode.CoreServices_setCore(this.__ptr, core)
}

CoreServices.prototype.getCore = function() {
	var retVal = new Core()
	retVal.__ptr = Polycode.CoreServices_getCore(this.__ptr)
	return retVal
}

CoreServices.prototype.getInput = function() {
	var retVal = new CoreInput()
	retVal.__ptr = Polycode.CoreServices_getInput(this.__ptr)
	return retVal
}

CoreServices.prototype.getMaterialManager = function() {
	var retVal = new MaterialManager()
	retVal.__ptr = Polycode.CoreServices_getMaterialManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getSceneManager = function() {
	var retVal = new SceneManager()
	retVal.__ptr = Polycode.CoreServices_getSceneManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getTimerManager = function() {
	var retVal = new TimerManager()
	retVal.__ptr = Polycode.CoreServices_getTimerManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getTweenManager = function() {
	var retVal = new TweenManager()
	retVal.__ptr = Polycode.CoreServices_getTweenManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getResourceManager = function() {
	var retVal = new ResourceManager()
	retVal.__ptr = Polycode.CoreServices_getResourceManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getSoundManager = function() {
	var retVal = new SoundManager()
	retVal.__ptr = Polycode.CoreServices_getSoundManager(this.__ptr)
	return retVal
}

CoreServices.prototype.getLogger = function() {
	var retVal = new Logger()
	retVal.__ptr = Polycode.CoreServices_getLogger(this.__ptr)
	return retVal
}

CoreServices.prototype.getConfig = function() {
	var retVal = new Config()
	retVal.__ptr = Polycode.CoreServices_getConfig(this.__ptr)
	return retVal
}
