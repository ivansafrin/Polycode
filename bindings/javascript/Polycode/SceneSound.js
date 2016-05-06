function SceneSound() {
}

SceneSound.prototype.Update = function() {
	Polycode.SceneSound_Update(this.__ptr)
}

SceneSound.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneSound_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneSound.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneSound_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneSound.prototype.isDirectionalSound = function() {
	Polycode.SceneSound_isDirectionalSound(this.__ptr)
}

SceneSound.prototype.setDirectionalSound = function(val) {
	Polycode.SceneSound_setDirectionalSound(this.__ptr, val)
}

SceneSound.prototype.getSound = function() {
	Polycode.SceneSound_getSound(this.__ptr)
}

SceneSound.prototype.setLoopOnLoad = function(val) {
	Polycode.SceneSound_setLoopOnLoad(this.__ptr, val)
}

SceneSound.prototype.getLoopOnLoad = function() {
	Polycode.SceneSound_getLoopOnLoad(this.__ptr)
}
