function Resource() {
}

Resource.prototype.reloadResource = function() {
	Polycode.Resource_reloadResource(this.__ptr)
}

Resource.prototype.getResourceName = function() {
	Polycode.Resource_getResourceName(this.__ptr)
}

Resource.prototype.getResourceType = function() {
	Polycode.Resource_getResourceType(this.__ptr)
}

Resource.prototype.setResourceName = function(newName) {
	Polycode.Resource_setResourceName(this.__ptr, newName)
}

Resource.prototype.setResourcePath = function(path) {
	Polycode.Resource_setResourcePath(this.__ptr, path)
}

Resource.prototype.getResourcePath = function() {
	Polycode.Resource_getResourcePath(this.__ptr)
}
