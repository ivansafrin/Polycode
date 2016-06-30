require('Polycode/Entity')

function SceneSound(fileName,referenceDistance,maxDistance,directionalSound) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneSound(fileName,referenceDistance,maxDistance,directionalSound)
	}
}


SceneSound.prototype = Object.create(Entity.prototype)


SceneSound.prototype.Update = function() {
	Polycode.SceneSound_Update(this.__ptr)
}

SceneSound.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneSound_Clone(this.__ptr, deepClone, ignoreEditorOnly)
	return retVal
}

SceneSound.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneSound_applyClone(this.__ptr, clone.__ptr, deepClone, ignoreEditorOnly)
}

SceneSound.prototype.isDirectionalSound = function() {
	return Polycode.SceneSound_isDirectionalSound(this.__ptr)
}

SceneSound.prototype.setDirectionalSound = function(val) {
	Polycode.SceneSound_setDirectionalSound(this.__ptr, val)
}

SceneSound.prototype.getSound = function() {
	var retVal = new Sound()
	retVal.__ptr = Polycode.SceneSound_getSound(this.__ptr)
	return retVal
}

SceneSound.prototype.setLoopOnLoad = function(val) {
	Polycode.SceneSound_setLoopOnLoad(this.__ptr, val)
}

SceneSound.prototype.getLoopOnLoad = function() {
	return Polycode.SceneSound_getLoopOnLoad(this.__ptr)
}
