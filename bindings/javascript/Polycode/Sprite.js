function Sprite() {
}

Sprite.prototype.getName = function() {
	return Polycode.Sprite_getName(this.__ptr)
}

Sprite.prototype.setName = function(name) {
	Polycode.Sprite_setName(this.__ptr, name)
}

Sprite.prototype.addSpriteState = function(state) {
	Polycode.Sprite_addSpriteState(this.__ptr, state)
}

Sprite.prototype.removeSpriteState = function(state) {
	Polycode.Sprite_removeSpriteState(this.__ptr, state)
}

Sprite.prototype.getNumStates = function() {
	return Polycode.Sprite_getNumStates(this.__ptr)
}

Sprite.prototype.getState = function(index) {
	var retVal = new SpriteState()
	retVal.__ptr = Polycode.Sprite_getState(this.__ptr, index)
	return retVal
}

Sprite.prototype.getStateByName = function(name) {
	var retVal = new SpriteState()
	retVal.__ptr = Polycode.Sprite_getStateByName(this.__ptr, name)
	return retVal
}

Sprite.prototype.setParentSpritSet = function(spriteSet) {
	Polycode.Sprite_setParentSpritSet(this.__ptr, spriteSet)
}

Sprite.prototype.getParentSpriteSet = function() {
	var retVal = new SpriteSet()
	retVal.__ptr = Polycode.Sprite_getParentSpriteSet(this.__ptr)
	return retVal
}
