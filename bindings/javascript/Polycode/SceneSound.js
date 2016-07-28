require('Polycode/Entity')

function SceneSound() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneSound()
	}
}


SceneSound.prototype = Object.create(Entity.prototype)


SceneSound.prototype.Update = function() {
	Polycode.SceneSound_Update(this.__ptr)
}

SceneSound.prototype.isDirectionalSound = function() {
	return Polycode.SceneSound_isDirectionalSound(this.__ptr)
}

SceneSound.prototype.setDirectionalSound = function(val) {
	Polycode.SceneSound_setDirectionalSound(this.__ptr, val)
}

SceneSound.prototype.setLoopOnLoad = function(val) {
	Polycode.SceneSound_setLoopOnLoad(this.__ptr, val)
}

SceneSound.prototype.getLoopOnLoad = function() {
	return Polycode.SceneSound_getLoopOnLoad(this.__ptr)
}
