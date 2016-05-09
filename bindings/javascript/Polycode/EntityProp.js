function EntityProp() {
	Object.defineProperties(this, {
		'propName': { enumerable: true, configurable: true, get: EntityProp.prototype.__get_propName, set: EntityProp.prototype.__set_propName},
		'propValue': { enumerable: true, configurable: true, get: EntityProp.prototype.__get_propValue, set: EntityProp.prototype.__set_propValue}
	})
}
EntityProp.prototype.__get_propName = function() {
	return Polycode.EntityProp__get_propName(this.__ptr)
}

EntityProp.prototype.__set_propName = function(val) {
	Polycode.EntityProp__set_propName(this.__ptr, val)
}

EntityProp.prototype.__get_propValue = function() {
	return Polycode.EntityProp__get_propValue(this.__ptr)
}

EntityProp.prototype.__set_propValue = function(val) {
	Polycode.EntityProp__set_propValue(this.__ptr, val)
}

