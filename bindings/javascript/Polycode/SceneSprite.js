function SceneSprite() {
}

SceneSprite.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneSprite_Clone(this.__ptr, deepClone,ignoreEditorOnly)
	return retVal
}

SceneSprite.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneSprite_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneSprite.prototype.getSpriteSet = function() {
	var retVal = new SpriteSet()
	retVal.__ptr = Polycode.SceneSprite_getSpriteSet(this.__ptr)
	return retVal
}

SceneSprite.prototype.getCurrentSprite = function() {
	var retVal = new shared_ptr<Sprite>()
	retVal.__ptr = Polycode.SceneSprite_getCurrentSprite(this.__ptr)
	return retVal
}

SceneSprite.prototype.setSpriteSet = function(spriteSet) {
	Polycode.SceneSprite_setSpriteSet(this.__ptr, spriteSet)
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

SceneSprite.prototype.Render = function(buffer) {
	Polycode.SceneSprite_Render(this.__ptr, buffer)
}

SceneSprite.prototype.getSpriteBoundingBox = function() {
	var retVal = new Vector3()
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

SceneSprite.prototype.setSpriteState = function(spriteState,startingFrame,playOnce) {
	Polycode.SceneSprite_setSpriteState(this.__ptr, spriteState,startingFrame,playOnce)
}

SceneSprite.prototype.setSpriteStateByName = function(name,startingFrame,playOnce) {
	Polycode.SceneSprite_setSpriteStateByName(this.__ptr, name,startingFrame,playOnce)
}

SceneSprite.prototype.getCurrentSpriteState = function() {
	var retVal = new SpriteState()
	retVal.__ptr = Polycode.SceneSprite_getCurrentSpriteState(this.__ptr)
	return retVal
}

SceneSprite.prototype.getStartOnRandomFrame = function() {
	return Polycode.SceneSprite_getStartOnRandomFrame(this.__ptr)
}

SceneSprite.prototype.setStartOnRandomFrame = function(val) {
	Polycode.SceneSprite_setStartOnRandomFrame(this.__ptr, val)
}
