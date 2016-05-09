function Scene() {
	Object.defineProperties(this, {
		'clearColor': { enumerable: true, configurable: true, get: Scene.prototype.__get_clearColor, set: Scene.prototype.__set_clearColor},
		'useClearColor': { enumerable: true, configurable: true, get: Scene.prototype.__get_useClearColor, set: Scene.prototype.__set_useClearColor},
		'useClearDepth': { enumerable: true, configurable: true, get: Scene.prototype.__get_useClearDepth, set: Scene.prototype.__set_useClearDepth},
		'ambientColor': { enumerable: true, configurable: true, get: Scene.prototype.__get_ambientColor, set: Scene.prototype.__set_ambientColor},
		'fogColor': { enumerable: true, configurable: true, get: Scene.prototype.__get_fogColor, set: Scene.prototype.__set_fogColor},
		'enabled': { enumerable: true, configurable: true, get: Scene.prototype.__get_enabled, set: Scene.prototype.__set_enabled},
		'ownsChildren': { enumerable: true, configurable: true, get: Scene.prototype.__get_ownsChildren, set: Scene.prototype.__set_ownsChildren},
		'rootEntity': { enumerable: true, configurable: true, get: Scene.prototype.__get_rootEntity, set: Scene.prototype.__set_rootEntity},
		'sceneMouseRect': { enumerable: true, configurable: true, get: Scene.prototype.__get_sceneMouseRect, set: Scene.prototype.__set_sceneMouseRect},
		'remapMouse': { enumerable: true, configurable: true, get: Scene.prototype.__get_remapMouse, set: Scene.prototype.__set_remapMouse},
		'constrainPickingToViewport': { enumerable: true, configurable: true, get: Scene.prototype.__get_constrainPickingToViewport, set: Scene.prototype.__set_constrainPickingToViewport}
	})
}
Scene.prototype.__get_clearColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.Scene__get_clearColor(this.__ptr)
	return retVal
}

Scene.prototype.__set_clearColor = function(val) {
	Polycode.Scene__set_clearColor(this.__ptr, val.__ptr)
}

Scene.prototype.__get_useClearColor = function() {
	return Polycode.Scene__get_useClearColor(this.__ptr)
}

Scene.prototype.__set_useClearColor = function(val) {
	Polycode.Scene__set_useClearColor(this.__ptr, val)
}

Scene.prototype.__get_useClearDepth = function() {
	return Polycode.Scene__get_useClearDepth(this.__ptr)
}

Scene.prototype.__set_useClearDepth = function(val) {
	Polycode.Scene__set_useClearDepth(this.__ptr, val)
}

Scene.prototype.__get_ambientColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.Scene__get_ambientColor(this.__ptr)
	return retVal
}

Scene.prototype.__set_ambientColor = function(val) {
	Polycode.Scene__set_ambientColor(this.__ptr, val.__ptr)
}

Scene.prototype.__get_fogColor = function() {
	var retVal = new Color()
	retVal.__ptr = 	Polycode.Scene__get_fogColor(this.__ptr)
	return retVal
}

Scene.prototype.__set_fogColor = function(val) {
	Polycode.Scene__set_fogColor(this.__ptr, val.__ptr)
}

Scene.prototype.__get_enabled = function() {
	return Polycode.Scene__get_enabled(this.__ptr)
}

Scene.prototype.__set_enabled = function(val) {
	Polycode.Scene__set_enabled(this.__ptr, val)
}

Scene.prototype.__get_ownsChildren = function() {
	return Polycode.Scene__get_ownsChildren(this.__ptr)
}

Scene.prototype.__set_ownsChildren = function(val) {
	Polycode.Scene__set_ownsChildren(this.__ptr, val)
}

Scene.prototype.__get_rootEntity = function() {
	var retVal = new Entity()
	retVal.__ptr = 	Polycode.Scene__get_rootEntity(this.__ptr)
	return retVal
}

Scene.prototype.__set_rootEntity = function(val) {
	Polycode.Scene__set_rootEntity(this.__ptr, val.__ptr)
}

Scene.prototype.__get_sceneMouseRect = function() {
	var retVal = new Rectangle()
	retVal.__ptr = 	Polycode.Scene__get_sceneMouseRect(this.__ptr)
	return retVal
}

Scene.prototype.__set_sceneMouseRect = function(val) {
	Polycode.Scene__set_sceneMouseRect(this.__ptr, val.__ptr)
}

Scene.prototype.__get_remapMouse = function() {
	return Polycode.Scene__get_remapMouse(this.__ptr)
}

Scene.prototype.__set_remapMouse = function(val) {
	Polycode.Scene__set_remapMouse(this.__ptr, val)
}

Scene.prototype.__get_constrainPickingToViewport = function() {
	return Polycode.Scene__get_constrainPickingToViewport(this.__ptr)
}

Scene.prototype.__set_constrainPickingToViewport = function(val) {
	Polycode.Scene__set_constrainPickingToViewport(this.__ptr, val)
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
	var retVal = new Camera()
	retVal.__ptr = Polycode.Scene_getDefaultCamera(this.__ptr)
	return retVal
}

Scene.prototype.getActiveCamera = function() {
	var retVal = new Camera()
	retVal.__ptr = Polycode.Scene_getActiveCamera(this.__ptr)
	return retVal
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
	return Polycode.Scene_isVirtual(this.__ptr)
}

Scene.prototype.isEnabled = function() {
	return Polycode.Scene_isEnabled(this.__ptr)
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
	var retVal = new Ray()
	retVal.__ptr = Polycode.Scene_projectRayFromCameraAndViewportCoordinate(this.__ptr, camera,coordinate)
	return retVal
}

Scene.prototype.addLight = function(light) {
	Polycode.Scene_addLight(this.__ptr, light)
}

Scene.prototype.removeLight = function(light) {
	Polycode.Scene_removeLight(this.__ptr, light)
}

Scene.prototype.getNumLights = function() {
	return Polycode.Scene_getNumLights(this.__ptr)
}

Scene.prototype.getLight = function(index) {
	var retVal = new SceneLight()
	retVal.__ptr = Polycode.Scene_getLight(this.__ptr, index)
	return retVal
}

Scene.prototype.doVisibilityChecking = function(val) {
	Polycode.Scene_doVisibilityChecking(this.__ptr, val)
}

Scene.prototype.doesVisibilityChecking = function() {
	return Polycode.Scene_doesVisibilityChecking(this.__ptr)
}
