require('Polycode/Resource')

function Sprite(name) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Sprite(name)
	}
}


Sprite.prototype = Object.create(Resource.prototype)

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

Sprite.prototype.getNumStates = function() {
	return Polycode.Sprite_getNumStates(this.__ptr)
}
