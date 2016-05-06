function SceneSprite() {
}

SceneSprite.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneSprite_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneSprite.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneSprite_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneSprite.prototype.getSpriteSet = function() {
	Polycode.SceneSprite_getSpriteSet(this.__ptr)
}

SceneSprite.prototype.getCurrentSprite = function() {
	Polycode.SceneSprite_getCurrentSprite(this.__ptr)
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
	Polycode.SceneSprite_getCurrentFrame(this.__ptr)
}

SceneSprite.prototype.Update = function() {
	Polycode.SceneSprite_Update(this.__ptr)
}

SceneSprite.prototype.Render = function(buffer) {
	Polycode.SceneSprite_Render(this.__ptr, buffer)
}

SceneSprite.prototype.getSpriteBoundingBox = function() {
	Polycode.SceneSprite_getSpriteBoundingBox(this.__ptr)
}

SceneSprite.prototype.setPaused = function(val) {
	Polycode.SceneSprite_setPaused(this.__ptr, val)
}

SceneSprite.prototype.isPaused = function() {
	Polycode.SceneSprite_isPaused(this.__ptr)
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
	Polycode.SceneSprite_getCurrentSpriteState(this.__ptr)
}

SceneSprite.prototype.getStartOnRandomFrame = function() {
	Polycode.SceneSprite_getStartOnRandomFrame(this.__ptr)
}

SceneSprite.prototype.setStartOnRandomFrame = function(val) {
	Polycode.SceneSprite_setStartOnRandomFrame(this.__ptr, val)
}
