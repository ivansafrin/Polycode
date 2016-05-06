function Sprite() {
}

Sprite.prototype.getName = function() {
	Polycode.Sprite_getName(this.__ptr)
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
	Polycode.Sprite_getNumStates(this.__ptr)
}

Sprite.prototype.getState = function(index) {
	Polycode.Sprite_getState(this.__ptr, index)
}

Sprite.prototype.getStateByName = function(name) {
	Polycode.Sprite_getStateByName(this.__ptr, name)
}

Sprite.prototype.setParentSpritSet = function(spriteSet) {
	Polycode.Sprite_setParentSpritSet(this.__ptr, spriteSet)
}

Sprite.prototype.getParentSpriteSet = function() {
	Polycode.Sprite_getParentSpriteSet(this.__ptr)
}
