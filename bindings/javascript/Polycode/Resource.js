function Resource() {
	Object.defineProperties(this, {
		'reloadOnFileModify': { enumerable: true, configurable: true, get: Resource.prototype.__get_reloadOnFileModify, set: Resource.prototype.__set_reloadOnFileModify},
		'resourceFileTime': { enumerable: true, configurable: true, get: Resource.prototype.__get_resourceFileTime, set: Resource.prototype.__set_resourceFileTime},
		'platformData': { enumerable: true, configurable: true, get: Resource.prototype.__get_platformData, set: Resource.prototype.__set_platformData}
	})
}
Resource.prototype.__get_reloadOnFileModify = function() {
	return Polycode.Resource__get_reloadOnFileModify(this.__ptr)
}

Resource.prototype.__set_reloadOnFileModify = function(val) {
	Polycode.Resource__set_reloadOnFileModify(this.__ptr, val)
}

Resource.prototype.__get_resourceFileTime = function() {
	var retVal = new time_t()
	retVal.__ptr = 	Polycode.Resource__get_resourceFileTime(this.__ptr)
	return retVal
}

Resource.prototype.__set_resourceFileTime = function(val) {
	Polycode.Resource__set_resourceFileTime(this.__ptr, val.__ptr)
}

Resource.prototype.__get_platformData = function() {
	var retVal = new void()
	retVal.__ptr = 	Polycode.Resource__get_platformData(this.__ptr)
	return retVal
}

Resource.prototype.__set_platformData = function(val) {
	Polycode.Resource__set_platformData(this.__ptr, val.__ptr)
}


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
