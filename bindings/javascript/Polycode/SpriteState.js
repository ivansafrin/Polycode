function SpriteState(spriteSet,name) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SpriteState(spriteSet,name)
	}
}


Duktape.fin(SpriteState.prototype, function (x) {
	if (x === SpriteState.prototype) {
		return;
	}
	Polycode.SpriteState__delete(x.__ptr)
})

SpriteState.prototype.setName = function(name) {
	Polycode.SpriteState_setName(this.__ptr, name)
}

SpriteState.prototype.getName = function() {
	return Polycode.SpriteState_getName(this.__ptr)
}

SpriteState.prototype.getNumFrameIDs = function() {
	return Polycode.SpriteState_getNumFrameIDs(this.__ptr)
}

SpriteState.prototype.getFrameIDAtIndex = function(index) {
	return Polycode.SpriteState_getFrameIDAtIndex(this.__ptr, index)
}

SpriteState.prototype.getMeshForFrameIndex = function(index) {
	var retVal = new Mesh()
	retVal.__ptr = Polycode.SpriteState_getMeshForFrameIndex(this.__ptr, index)
	return retVal
}

SpriteState.prototype.insertFrame = function(index,frameID) {
	Polycode.SpriteState_insertFrame(this.__ptr, index, frameID)
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
	return Polycode.SpriteState_getPixelsPerUnit(this.__ptr)
}

SpriteState.prototype.rebuildStateMeshes = function() {
	Polycode.SpriteState_rebuildStateMeshes(this.__ptr)
}

SpriteState.prototype.setStateFPS = function(fps) {
	Polycode.SpriteState_setStateFPS(this.__ptr, fps)
}

SpriteState.prototype.getStateFPS = function() {
	return Polycode.SpriteState_getStateFPS(this.__ptr)
}

SpriteState.prototype.getLargestFrameBoundingBox = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.SpriteState_getLargestFrameBoundingBox(this.__ptr)
	return retVal
}

SpriteState.prototype.setBoundingBox = function(boundingBox) {
	Polycode.SpriteState_setBoundingBox(this.__ptr, boundingBox)
}

SpriteState.prototype.getBoundingBox = function() {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.SpriteState_getBoundingBox(this.__ptr)
	return retVal
}

SpriteState.prototype.getSpriteOffset = function() {
	var retVal = new Vector2()
	retVal.__ptr = Polycode.SpriteState_getSpriteOffset(this.__ptr)
	return retVal
}

SpriteState.prototype.setSpriteOffset = function(offset) {
	Polycode.SpriteState_setSpriteOffset(this.__ptr, offset)
}
