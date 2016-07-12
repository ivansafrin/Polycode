require('Polycode/SceneMesh')

function SceneSprite() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneSprite()
	}
}


SceneSprite.prototype = Object.create(SceneMesh.prototype)


SceneSprite.prototype.getCurrentSprite = function() {
	var retVal = new Sprite("__skip_ptr__")
	retVal.__ptr = Polycode.SceneSprite_getCurrentSprite(this.__ptr)
	return retVal
}

SceneSprite.prototype.setSpriteByName = function(spriteName) {
	Polycode.SceneSprite_setSpriteByName(this.__ptr, spriteName)
}

SceneSprite.prototype.setCurrentFrame = function(frameIndex) {
	Polycode.SceneSprite_setCurrentFrame(this.__ptr, frameIndex)
}

SceneSprite.prototype.getCurrentFrame = function() {
	return Polycode.SceneSprite_getCurrentFrame(this.__ptr)
}

SceneSprite.prototype.Update = function() {
	Polycode.SceneSprite_Update(this.__ptr)
}

SceneSprite.prototype.getSpriteBoundingBox = function() {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.SceneSprite_getSpriteBoundingBox(this.__ptr)
	return retVal
}

SceneSprite.prototype.setPaused = function(val) {
	Polycode.SceneSprite_setPaused(this.__ptr, val)
}

SceneSprite.prototype.isPaused = function() {
	return Polycode.SceneSprite_isPaused(this.__ptr)
}

SceneSprite.prototype.setSprite = function(spriteEntry) {
	Polycode.SceneSprite_setSprite(this.__ptr, spriteEntry)
}

SceneSprite.prototype.setSpriteStateByName = function(name,startingFrame,playOnce) {
	Polycode.SceneSprite_setSpriteStateByName(this.__ptr, name, startingFrame, playOnce)
}

SceneSprite.prototype.getStartOnRandomFrame = function() {
	return Polycode.SceneSprite_getStartOnRandomFrame(this.__ptr)
}

SceneSprite.prototype.setStartOnRandomFrame = function(val) {
	Polycode.SceneSprite_setStartOnRandomFrame(this.__ptr, val)
}
