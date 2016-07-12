require('Polycode/Entity')

function SceneEntityInstance(fileName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneEntityInstance(fileName)
	}
	Object.defineProperties(this, {
		'cloneUsingReload': { enumerable: true, configurable: true, get: SceneEntityInstance.prototype.__get_cloneUsingReload, set: SceneEntityInstance.prototype.__set_cloneUsingReload},
		'fileName': { enumerable: true, configurable: true, get: SceneEntityInstance.prototype.__get_fileName, set: SceneEntityInstance.prototype.__set_fileName}
	})
}


SceneEntityInstance.prototype = Object.create(Entity.prototype)

SceneEntityInstance.prototype.__get_cloneUsingReload = function() {
	return Polycode.SceneEntityInstance__get_cloneUsingReload(this.__ptr)
}

SceneEntityInstance.prototype.__set_cloneUsingReload = function(val) {
	Polycode.SceneEntityInstance__set_cloneUsingReload(this.__ptr, val)
}

SceneEntityInstance.prototype.__get_fileName = function() {
	return Polycode.SceneEntityInstance__get_fileName(this.__ptr)
}

SceneEntityInstance.prototype.__set_fileName = function(val) {
	Polycode.SceneEntityInstance__set_fileName(this.__ptr, val)
}


SceneEntityInstance.prototype.reloadEntityInstance = function() {
	Polycode.SceneEntityInstance_reloadEntityInstance(this.__ptr)
}

SceneEntityInstance.prototype.clearInstance = function() {
	Polycode.SceneEntityInstance_clearInstance(this.__ptr)
}

SceneEntityInstance.prototype.loadFromFile = function(fileName) {
	return Polycode.SceneEntityInstance_loadFromFile(this.__ptr, fileName)
}

SceneEntityInstance.prototype.getNumLinkedResourePools = function() {
	return Polycode.SceneEntityInstance_getNumLinkedResourePools(this.__ptr)
}

SceneEntityInstance.prototype.getResourceEntry = function() {
	var retVal = new SceneEntityInstanceResourceEntry("__skip_ptr__")
	retVal.__ptr = Polycode.SceneEntityInstance_getResourceEntry(this.__ptr)
	return retVal
}

SceneEntityInstance.prototype.hasLayerID = function(layerID) {
	return Polycode.SceneEntityInstance_hasLayerID(this.__ptr, layerID)
}

SceneEntityInstance.prototype.getNumLayers = function() {
	return Polycode.SceneEntityInstance_getNumLayers(this.__ptr)
}

SceneEntityInstance.prototype.getFileName = function() {
	return Polycode.SceneEntityInstance_getFileName(this.__ptr)
}
