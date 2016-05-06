function SpriteSet() {
}

SpriteSet.prototype.setTexture = function(texture) {
	Polycode.SpriteSet_setTexture(this.__ptr, texture)
}

SpriteSet.prototype.getTexture = function() {
	Polycode.SpriteSet_getTexture(this.__ptr)
}

SpriteSet.prototype.loadTexture = function(imageFileName) {
	Polycode.SpriteSet_loadTexture(this.__ptr, imageFileName)
}

SpriteSet.prototype.addSpriteEntry = function(newEntry) {
	Polycode.SpriteSet_addSpriteEntry(this.__ptr, newEntry)
}

SpriteSet.prototype.getNumSpriteEntries = function() {
	Polycode.SpriteSet_getNumSpriteEntries(this.__ptr)
}

SpriteSet.prototype.getSpriteEntry = function(index) {
	Polycode.SpriteSet_getSpriteEntry(this.__ptr, index)
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
	Polycode.SpriteSet_getNumFrames(this.__ptr)
}

SpriteSet.prototype.getSpriteFrame = function(index) {
	Polycode.SpriteSet_getSpriteFrame(this.__ptr, index)
}

SpriteSet.prototype.getSpriteFrameByID = function(frameID) {
	Polycode.SpriteSet_getSpriteFrameByID(this.__ptr, frameID)
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
	Polycode.SpriteSet_getSpriteByName(this.__ptr, spriteName)
}
