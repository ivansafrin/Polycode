function SceneEntityInstanceLayer(instance,name) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneEntityInstanceLayer(instance,name)
	}
	Object.defineProperties(this, {
		'name': { enumerable: true, configurable: true, get: SceneEntityInstanceLayer.prototype.__get_name, set: SceneEntityInstanceLayer.prototype.__set_name},
		'layerID': { enumerable: true, configurable: true, get: SceneEntityInstanceLayer.prototype.__get_layerID, set: SceneEntityInstanceLayer.prototype.__set_layerID},
		'visible': { enumerable: true, configurable: true, get: SceneEntityInstanceLayer.prototype.__get_visible, set: SceneEntityInstanceLayer.prototype.__set_visible},
		'instance': { enumerable: true, configurable: true, get: SceneEntityInstanceLayer.prototype.__get_instance, set: SceneEntityInstanceLayer.prototype.__set_instance}
	})
}

SceneEntityInstanceLayer.prototype.__get_name = function() {
	return Polycode.SceneEntityInstanceLayer__get_name(this.__ptr)
}

SceneEntityInstanceLayer.prototype.__set_name = function(val) {
	Polycode.SceneEntityInstanceLayer__set_name(this.__ptr, val)
}

SceneEntityInstanceLayer.prototype.__get_layerID = function() {
	var retVal = new char()
	retVal.__ptr = 	Polycode.SceneEntityInstanceLayer__get_layerID(this.__ptr)
	return retVal
}

SceneEntityInstanceLayer.prototype.__set_layerID = function(val) {
	Polycode.SceneEntityInstanceLayer__set_layerID(this.__ptr, val.__ptr)
}

SceneEntityInstanceLayer.prototype.__get_visible = function() {
	return Polycode.SceneEntityInstanceLayer__get_visible(this.__ptr)
}

SceneEntityInstanceLayer.prototype.__set_visible = function(val) {
	Polycode.SceneEntityInstanceLayer__set_visible(this.__ptr, val)
}

SceneEntityInstanceLayer.prototype.__get_instance = function() {
	var retVal = new SceneEntityInstance()
	retVal.__ptr = 	Polycode.SceneEntityInstanceLayer__get_instance(this.__ptr)
	return retVal
}

SceneEntityInstanceLayer.prototype.__set_instance = function(val) {
	Polycode.SceneEntityInstanceLayer__set_instance(this.__ptr, val.__ptr)
}

Duktape.fin(SceneEntityInstanceLayer.prototype, function (x) {
	if (x === SceneEntityInstanceLayer.prototype) {
		return;
	}
	Polycode.SceneEntityInstanceLayer__delete(x.__ptr)
})

SceneEntityInstanceLayer.prototype.setLayerVisibility = function(val) {
	Polycode.SceneEntityInstanceLayer_setLayerVisibility(this.__ptr, val)
}
