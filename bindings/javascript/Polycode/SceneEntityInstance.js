function SceneEntityInstance() {
}

SceneEntityInstance.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneEntityInstance_Clone(this.__ptr, deepClone,ignoreEditorOnly)
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
	Polycode.SceneEntityInstance_loadObjectEntryIntoEntity(this.__ptr, entry,targetEntity,entityFileVersion)
}

SceneEntityInstance.prototype.loadFromFile = function(fileName) {
	Polycode.SceneEntityInstance_loadFromFile(this.__ptr, fileName)
}

SceneEntityInstance.prototype.applySceneMesh = function(entry,sceneMesh) {
	Polycode.SceneEntityInstance_applySceneMesh(this.__ptr, entry,sceneMesh)
}

SceneEntityInstance.prototype.linkResourcePool = function(pool) {
	Polycode.SceneEntityInstance_linkResourcePool(this.__ptr, pool)
}

SceneEntityInstance.prototype.getNumLinkedResourePools = function() {
	Polycode.SceneEntityInstance_getNumLinkedResourePools(this.__ptr)
}

SceneEntityInstance.prototype.getLinkedResourcePoolAtIndex = function(index) {
	Polycode.SceneEntityInstance_getLinkedResourcePoolAtIndex(this.__ptr, index)
}

SceneEntityInstance.prototype.unlinkResourcePool = function(pool) {
	Polycode.SceneEntityInstance_unlinkResourcePool(this.__ptr, pool)
}

SceneEntityInstance.prototype.getResourceEntry = function() {
	Polycode.SceneEntityInstance_getResourceEntry(this.__ptr)
}

SceneEntityInstance.prototype.getTopLevelResourcePool = function() {
	Polycode.SceneEntityInstance_getTopLevelResourcePool(this.__ptr)
}

SceneEntityInstance.prototype.hasLayerID = function(layerID) {
	Polycode.SceneEntityInstance_hasLayerID(this.__ptr, layerID)
}

SceneEntityInstance.prototype.getNumLayers = function() {
	Polycode.SceneEntityInstance_getNumLayers(this.__ptr)
}

SceneEntityInstance.prototype.getLayerAtIndex = function(index) {
	Polycode.SceneEntityInstance_getLayerAtIndex(this.__ptr, index)
}

SceneEntityInstance.prototype.removeLayer = function(layer) {
	Polycode.SceneEntityInstance_removeLayer(this.__ptr, layer)
}

SceneEntityInstance.prototype.createNewLayer = function(name) {
	Polycode.SceneEntityInstance_createNewLayer(this.__ptr, name)
}

SceneEntityInstance.prototype.getFileName = function() {
	Polycode.SceneEntityInstance_getFileName(this.__ptr)
}
