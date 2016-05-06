function SpriteState() {
}

SpriteState.prototype.setName = function(name) {
	Polycode.SpriteState_setName(this.__ptr, name)
}

SpriteState.prototype.getName = function() {
	Polycode.SpriteState_getName(this.__ptr)
}

SpriteState.prototype.getNumFrameIDs = function() {
	Polycode.SpriteState_getNumFrameIDs(this.__ptr)
}

SpriteState.prototype.getFrameIDAtIndex = function(index) {
	Polycode.SpriteState_getFrameIDAtIndex(this.__ptr, index)
}

SpriteState.prototype.getMeshForFrameIndex = function(index) {
	Polycode.SpriteState_getMeshForFrameIndex(this.__ptr, index)
}

SpriteState.prototype.insertFrame = function(index,frameID) {
	Polycode.SpriteState_insertFrame(this.__ptr, index,frameID)
}

SpriteState.prototype.removeFrameByIndex = function(frameIndex) {
	Polycode.SpriteState_removeFrameByIndex(this.__ptr, frameIndex)
}

SpriteState.prototype.clearFrames = function() {
	Polycode.SpriteState_clearFrames(this.__ptr)
}

SpriteState.prototype.setPixelsPerUnit = function(ppu) {
	Polycode.SpriteState_setPixelsPerUnit(this.__ptr, ppu)
}

SpriteState.prototype.getPixelsPerUnit = function() {
	Polycode.SpriteState_getPixelsPerUnit(this.__ptr)
}

SpriteState.prototype.rebuildStateMeshes = function() {
	Polycode.SpriteState_rebuildStateMeshes(this.__ptr)
}

SpriteState.prototype.setStateFPS = function(fps) {
	Polycode.SpriteState_setStateFPS(this.__ptr, fps)
}

SpriteState.prototype.getStateFPS = function() {
	Polycode.SpriteState_getStateFPS(this.__ptr)
}

SpriteState.prototype.getLargestFrameBoundingBox = function() {
	Polycode.SpriteState_getLargestFrameBoundingBox(this.__ptr)
}

SpriteState.prototype.setBoundingBox = function(boundingBox) {
	Polycode.SpriteState_setBoundingBox(this.__ptr, boundingBox)
}

SpriteState.prototype.getBoundingBox = function() {
	Polycode.SpriteState_getBoundingBox(this.__ptr)
}

SpriteState.prototype.getSpriteOffset = function() {
	Polycode.SpriteState_getSpriteOffset(this.__ptr)
}

SpriteState.prototype.setSpriteOffset = function(offset) {
	Polycode.SpriteState_setSpriteOffset(this.__ptr, offset)
}
