function CoreServices() {
}

CoreServices.prototype.setRenderer = function(renderer) {
	Polycode.CoreServices_setRenderer(this.__ptr, renderer)
}

CoreServices.prototype.getRenderer = function() {
	Polycode.CoreServices_getRenderer(this.__ptr)
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
	Polycode.CoreServices_getCore(this.__ptr)
}

CoreServices.prototype.getInput = function() {
	Polycode.CoreServices_getInput(this.__ptr)
}

CoreServices.prototype.getMaterialManager = function() {
	Polycode.CoreServices_getMaterialManager(this.__ptr)
}

CoreServices.prototype.getSceneManager = function() {
	Polycode.CoreServices_getSceneManager(this.__ptr)
}

CoreServices.prototype.getTimerManager = function() {
	Polycode.CoreServices_getTimerManager(this.__ptr)
}

CoreServices.prototype.getTweenManager = function() {
	Polycode.CoreServices_getTweenManager(this.__ptr)
}

CoreServices.prototype.getResourceManager = function() {
	Polycode.CoreServices_getResourceManager(this.__ptr)
}

CoreServices.prototype.getSoundManager = function() {
	Polycode.CoreServices_getSoundManager(this.__ptr)
}

CoreServices.prototype.getLogger = function() {
	Polycode.CoreServices_getLogger(this.__ptr)
}

CoreServices.prototype.getConfig = function() {
	Polycode.CoreServices_getConfig(this.__ptr)
}
