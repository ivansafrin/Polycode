function Scene() {
}

Scene.prototype.addEntity = function(entity) {
	Polycode.Scene_addEntity(this.__ptr, entity)
}

Scene.prototype.addChild = function(entity) {
	Polycode.Scene_addChild(this.__ptr, entity)
}

Scene.prototype.removeEntity = function(entity) {
	Polycode.Scene_removeEntity(this.__ptr, entity)
}

Scene.prototype.getDefaultCamera = function() {
	Polycode.Scene_getDefaultCamera(this.__ptr)
}

Scene.prototype.getActiveCamera = function() {
	Polycode.Scene_getActiveCamera(this.__ptr)
}

Scene.prototype.setActiveCamera = function(camera) {
	Polycode.Scene_setActiveCamera(this.__ptr, camera)
}

Scene.prototype.enableFog = function(enable) {
	Polycode.Scene_enableFog(this.__ptr, enable)
}

Scene.prototype.setFogProperties = function(fogMode,color,density,startDepth,endDepth) {
	Polycode.Scene_setFogProperties(this.__ptr, fogMode,color,density,startDepth,endDepth)
}

Scene.prototype.setSceneType = function(newType) {
	Polycode.Scene_setSceneType(this.__ptr, newType)
}

Scene.prototype.fixedUpdate = function() {
	Polycode.Scene_fixedUpdate(this.__ptr)
}

Scene.prototype.Update = function() {
	Polycode.Scene_Update(this.__ptr)
}

Scene.prototype.setVirtual = function(val) {
	Polycode.Scene_setVirtual(this.__ptr, val)
}

Scene.prototype.isVirtual = function() {
	Polycode.Scene_isVirtual(this.__ptr)
}

Scene.prototype.isEnabled = function() {
	Polycode.Scene_isEnabled(this.__ptr)
}

Scene.prototype.setEnabled = function(enabled) {
	Polycode.Scene_setEnabled(this.__ptr, enabled)
}

Scene.prototype.Render = function(targetCamera,targetFramebuffer,overrideMaterial,sendLights) {
	Polycode.Scene_Render(this.__ptr, targetCamera,targetFramebuffer,overrideMaterial,sendLights)
}

Scene.prototype.setOverrideMaterial = function(material) {
	Polycode.Scene_setOverrideMaterial(this.__ptr, material)
}

Scene.prototype.projectRayFromCameraAndViewportCoordinate = function(camera,coordinate) {
	Polycode.Scene_projectRayFromCameraAndViewportCoordinate(this.__ptr, camera,coordinate)
}

Scene.prototype.addLight = function(light) {
	Polycode.Scene_addLight(this.__ptr, light)
}

Scene.prototype.removeLight = function(light) {
	Polycode.Scene_removeLight(this.__ptr, light)
}

Scene.prototype.getNumLights = function() {
	Polycode.Scene_getNumLights(this.__ptr)
}

Scene.prototype.getLight = function(index) {
	Polycode.Scene_getLight(this.__ptr, index)
}

Scene.prototype.doVisibilityChecking = function(val) {
	Polycode.Scene_doVisibilityChecking(this.__ptr, val)
}

Scene.prototype.doesVisibilityChecking = function() {
	Polycode.Scene_doesVisibilityChecking(this.__ptr)
}
