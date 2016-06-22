require('Polycode/Resource')

function Sprite(name) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Sprite(name)
	}
}

Sprite.prototype = Object.create(Resource.prototype);

Duktape.fin(Sprite.prototype, function (x) {
	if (x === Sprite.prototype) {
		return;
	}
	Polycode.Sprite__delete(x.__ptr)
})

Sprite.prototype.getName = function() {
	return Polycode.Sprite_getName(this.__ptr)
}

Sprite.prototype.setName = function(name) {
	Polycode.Sprite_setName(this.__ptr, name)
}

Sprite.prototype.addSpriteState = function(state) {
	Polycode.Sprite_addSpriteState(this.__ptr, state.__ptr)
}

Sprite.prototype.removeSpriteState = function(state) {
	Polycode.Sprite_removeSpriteState(this.__ptr, state.__ptr)
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
	Polycode.Sprite_setParentSpritSet(this.__ptr, spriteSet.__ptr)
}

Sprite.prototype.getParentSpriteSet = function() {
	var retVal = new SpriteSet()
	retVal.__ptr = Polycode.Sprite_getParentSpriteSet(this.__ptr)
	return retVal
}
