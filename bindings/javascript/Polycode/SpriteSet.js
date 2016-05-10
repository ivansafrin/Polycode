function SpriteSet() {
}
Duktape.fin(SpriteSet.prototype, function (x) {
	if (x === SpriteSet.prototype) {
		return;
	}
	Polycode.SpriteSet__delete(x.__ptr)
})

SpriteSet.prototype.setTexture = function(texture) {
	Polycode.SpriteSet_setTexture(this.__ptr, texture)
}

SpriteSet.prototype.getTexture = function() {
	var retVal = new Texture()
	retVal.__ptr = Polycode.SpriteSet_getTexture(this.__ptr)
	return retVal
}

SpriteSet.prototype.loadTexture = function(imageFileName) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.SpriteSet_loadTexture(this.__ptr, imageFileName)
	return retVal
}

SpriteSet.prototype.addSpriteEntry = function(newEntry) {
	Polycode.SpriteSet_addSpriteEntry(this.__ptr, newEntry)
}

SpriteSet.prototype.getNumSpriteEntries = function() {
	return Polycode.SpriteSet_getNumSpriteEntries(this.__ptr)
}

SpriteSet.prototype.getSpriteEntry = function(index) {
	var retVal = new Sprite()
	retVal.__ptr = Polycode.SpriteSet_getSpriteEntry(this.__ptr, index)
	return retVal
}

SpriteSet.prototype.removeSprite = function(sprite) {
	Polycode.SpriteSet_removeSprite(this.__ptr, sprite)
}

SpriteSet.prototype.loadSpriteSet = function(fileName) {
	Polycode.SpriteSet_loadSpriteSet(this.__ptr, fileName)
}

SpriteSet.prototype.addSpriteFrame = function(frame,assignID) {
	Polycode.SpriteSet_addSpriteFrame(this.__ptr, frame,assignID)
}

SpriteSet.prototype.getNumFrames = function() {
	return Polycode.SpriteSet_getNumFrames(this.__ptr)
}

SpriteSet.prototype.getSpriteFrame = function(index) {
	var retVal = new SpriteFrame()
	retVal.__ptr = Polycode.SpriteSet_getSpriteFrame(this.__ptr, index)
	return retVal
}

SpriteSet.prototype.getSpriteFrameByID = function(frameID) {
	var retVal = new SpriteFrame()
	retVal.__ptr = Polycode.SpriteSet_getSpriteFrameByID(this.__ptr, frameID)
	return retVal
}

SpriteSet.prototype.removeFrameByID = function(frameID) {
	Polycode.SpriteSet_removeFrameByID(this.__ptr, frameID)
}

SpriteSet.prototype.setSpriteFrame = function(frame) {
	Polycode.SpriteSet_setSpriteFrame(this.__ptr, frame)
}

SpriteSet.prototype.clearFrames = function() {
	Polycode.SpriteSet_clearFrames(this.__ptr)
}

SpriteSet.prototype.createGridFrames = function(xCount,yCount,defaultAnchor) {
	Polycode.SpriteSet_createGridFrames(this.__ptr, xCount,yCount,defaultAnchor)
}

SpriteSet.prototype.createFramesFromIslands = function(minDistance,defaultAnchor) {
	Polycode.SpriteSet_createFramesFromIslands(this.__ptr, minDistance,defaultAnchor)
}

SpriteSet.prototype.getSpriteByName = function(spriteName) {
	var retVal = new Sprite()
	retVal.__ptr = Polycode.SpriteSet_getSpriteByName(this.__ptr, spriteName)
	return retVal
}
