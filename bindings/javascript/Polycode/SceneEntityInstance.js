function SceneEntityInstance() {
	Object.defineProperties(this, {
		'cloneUsingReload': { enumerable: true, configurable: true, get: SceneEntityInstance.prototype.__get_cloneUsingReload, set: SceneEntityInstance.prototype.__set_cloneUsingReload},
		'fileName': { enumerable: true, configurable: true, get: SceneEntityInstance.prototype.__get_fileName, set: SceneEntityInstance.prototype.__set_fileName}
	})
}
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


SceneEntityInstance.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneEntityInstance_Clone(this.__ptr, deepClone,ignoreEditorOnly)
	return retVal
}

SceneEntityInstance.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneEntityInstance_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneEntityInstance.prototype.reloadEntityInstance = function() {
	Polycode.SceneEntityInstance_reloadEntityInstance(this.__ptr)
}

SceneEntityInstance.prototype.clearInstance = function() {
	Polycode.SceneEntityInstance_clearInstance(this.__ptr)
}

SceneEntityInstance.prototype.parseObjectIntoCurve = function(entry,curve) {
	Polycode.SceneEntityInstance_parseObjectIntoCurve(this.__ptr, entry,curve)
}

SceneEntityInstance.prototype.loadObjectEntryIntoEntity = function(entry,targetEntity,entityFileVersion) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneEntityInstance_loadObjectEntryIntoEntity(this.__ptr, entry,targetEntity,entityFileVersion)
	return retVal
}

SceneEntityInstance.prototype.loadFromFile = function(fileName) {
	return Polycode.SceneEntityInstance_loadFromFile(this.__ptr, fileName)
}

SceneEntityInstance.prototype.applySceneMesh = function(entry,sceneMesh) {
	Polycode.SceneEntityInstance_applySceneMesh(this.__ptr, entry,sceneMesh)
}

SceneEntityInstance.prototype.linkResourcePool = function(pool) {
	Polycode.SceneEntityInstance_linkResourcePool(this.__ptr, pool)
}

SceneEntityInstance.prototype.getNumLinkedResourePools = function() {
	return Polycode.SceneEntityInstance_getNumLinkedResourePools(this.__ptr)
}

SceneEntityInstance.prototype.getLinkedResourcePoolAtIndex = function(index) {
	var retVal = new ResourcePool()
	retVal.__ptr = Polycode.SceneEntityInstance_getLinkedResourcePoolAtIndex(this.__ptr, index)
	return retVal
}

SceneEntityInstance.prototype.unlinkResourcePool = function(pool) {
	Polycode.SceneEntityInstance_unlinkResourcePool(this.__ptr, pool)
}

SceneEntityInstance.prototype.getResourceEntry = function() {
	var retVal = new shared_ptr<SceneEntityInstanceResourceEntry>()
	retVal.__ptr = Polycode.SceneEntityInstance_getResourceEntry(this.__ptr)
	return retVal
}

SceneEntityInstance.prototype.getTopLevelResourcePool = function() {
	var retVal = new ResourcePool()
	retVal.__ptr = Polycode.SceneEntityInstance_getTopLevelResourcePool(this.__ptr)
	return retVal
}

SceneEntityInstance.prototype.hasLayerID = function(layerID) {
	return Polycode.SceneEntityInstance_hasLayerID(this.__ptr, layerID)
}

SceneEntityInstance.prototype.getNumLayers = function() {
	return Polycode.SceneEntityInstance_getNumLayers(this.__ptr)
}

SceneEntityInstance.prototype.getLayerAtIndex = function(index) {
	var retVal = new SceneEntityInstanceLayer()
	retVal.__ptr = Polycode.SceneEntityInstance_getLayerAtIndex(this.__ptr, index)
	return retVal
}

SceneEntityInstance.prototype.removeLayer = function(layer) {
	Polycode.SceneEntityInstance_removeLayer(this.__ptr, layer)
}

SceneEntityInstance.prototype.createNewLayer = function(name) {
	var retVal = new SceneEntityInstanceLayer()
	retVal.__ptr = Polycode.SceneEntityInstance_createNewLayer(this.__ptr, name)
	return retVal
}

SceneEntityInstance.prototype.getFileName = function() {
	return Polycode.SceneEntityInstance_getFileName(this.__ptr)
}
