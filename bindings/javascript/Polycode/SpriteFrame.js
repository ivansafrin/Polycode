function SpriteFrame() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SpriteFrame()
	}
	Object.defineProperties(this, {
		'coordinates': { enumerable: true, configurable: true, get: SpriteFrame.prototype.__get_coordinates, set: SpriteFrame.prototype.__set_coordinates},
		'anchorPoint': { enumerable: true, configurable: true, get: SpriteFrame.prototype.__get_anchorPoint, set: SpriteFrame.prototype.__set_anchorPoint},
		'frameID': { enumerable: true, configurable: true, get: SpriteFrame.prototype.__get_frameID, set: SpriteFrame.prototype.__set_frameID}
	})
}


SpriteFrame.prototype.__get_coordinates = function() {
	var retVal = new Rectangle("__skip_ptr__")
	retVal.__ptr = 	Polycode.SpriteFrame__get_coordinates(this.__ptr)
	return retVal
}

SpriteFrame.prototype.__set_coordinates = function(val) {
	Polycode.SpriteFrame__set_coordinates(this.__ptr, val.__ptr)
}

SpriteFrame.prototype.__get_anchorPoint = function() {
	var retVal = new Vector2("__skip_ptr__")
	retVal.__ptr = 	Polycode.SpriteFrame__get_anchorPoint(this.__ptr)
	return retVal
}

SpriteFrame.prototype.__set_anchorPoint = function(val) {
	Polycode.SpriteFrame__set_anchorPoint(this.__ptr, val.__ptr)
}

SpriteFrame.prototype.__get_frameID = function() {
	return Polycode.SpriteFrame__get_frameID(this.__ptr)
}

SpriteFrame.prototype.__set_frameID = function(val) {
	Polycode.SpriteFrame__set_frameID(this.__ptr, val)
}

Duktape.fin(SpriteFrame.prototype, function (x) {
	if (x === SpriteFrame.prototype) {
		return;
	}
	Polycode.SpriteFrame__delete(x.__ptr)
})
