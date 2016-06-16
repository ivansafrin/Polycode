require('Polycode/EventDispatcher')

function Resource(type) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Resource(type)
	}
	Object.defineProperties(this, {
		'reloadOnFileModify': { enumerable: true, configurable: true, get: Resource.prototype.__get_reloadOnFileModify, set: Resource.prototype.__set_reloadOnFileModify},
		'resourceFileTime': { enumerable: true, configurable: true, get: Resource.prototype.__get_resourceFileTime, set: Resource.prototype.__set_resourceFileTime}
	})
}

Resource.prototype = Object.create(EventDispatcher.prototype);

Resource.prototype.__get_reloadOnFileModify = function() {
	return Polycode.Resource__get_reloadOnFileModify(this.__ptr)
}

Resource.prototype.__set_reloadOnFileModify = function(val) {
	Polycode.Resource__set_reloadOnFileModify(this.__ptr, val)
}

Resource.prototype.__get_resourceFileTime = function() {
	var retVal = new size_t()
	retVal.__ptr = 	Polycode.Resource__get_resourceFileTime(this.__ptr)
	return retVal
}

Resource.prototype.__set_resourceFileTime = function(val) {
	Polycode.Resource__set_resourceFileTime(this.__ptr, val.__ptr)
}

Duktape.fin(Resource.prototype, function (x) {
	if (x === Resource.prototype) {
		return;
	}
	Polycode.Resource__delete(x.__ptr)
})

Resource.prototype.reloadResource = function() {
	Polycode.Resource_reloadResource(this.__ptr)
}

Resource.prototype.getResourceName = function() {
	return Polycode.Resource_getResourceName(this.__ptr)
}

Resource.prototype.getResourceType = function() {
	return Polycode.Resource_getResourceType(this.__ptr)
}

Resource.prototype.setResourceName = function(newName) {
	Polycode.Resource_setResourceName(this.__ptr, newName)
}

Resource.prototype.setResourcePath = function(path) {
	Polycode.Resource_setResourcePath(this.__ptr, path)
}

Resource.prototype.getResourcePath = function() {
	return Polycode.Resource_getResourcePath(this.__ptr)
}
