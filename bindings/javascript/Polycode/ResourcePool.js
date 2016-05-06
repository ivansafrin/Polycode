function ResourcePool() {
}

ResourcePool.prototype.setFallbackPool = function(pool) {
	Polycode.ResourcePool_setFallbackPool(this.__ptr, pool)
}

ResourcePool.prototype.addResource = function(resource) {
	Polycode.ResourcePool_addResource(this.__ptr, resource)
}

ResourcePool.prototype.removeResource = function(resource) {
	Polycode.ResourcePool_removeResource(this.__ptr, resource)
}

ResourcePool.prototype.hasResource = function(resource) {
	Polycode.ResourcePool_hasResource(this.__ptr, resource)
}

ResourcePool.prototype.loadResourcesFromFolder = function(folder,recursive) {
	Polycode.ResourcePool_loadResourcesFromFolder(this.__ptr, folder,recursive)
}

ResourcePool.prototype.loadResource = function(path) {
	Polycode.ResourcePool_loadResource(this.__ptr, path)
}

ResourcePool.prototype.loadResourceWithName = function(path,name) {
	Polycode.ResourcePool_loadResourceWithName(this.__ptr, path,name)
}

ResourcePool.prototype.getResource = function(resourceType,resourceName) {
	Polycode.ResourcePool_getResource(this.__ptr, resourceType,resourceName)
}

ResourcePool.prototype.getName = function() {
	Polycode.ResourcePool_getName(this.__ptr)
}

ResourcePool.prototype.setName = function(name) {
	Polycode.ResourcePool_setName(this.__ptr, name)
}

ResourcePool.prototype.getResourceByPath = function(resourcePath) {
	Polycode.ResourcePool_getResourceByPath(this.__ptr, resourcePath)
}

ResourcePool.prototype.Update = function(elapsed) {
	Polycode.ResourcePool_Update(this.__ptr, elapsed)
}

ResourcePool.prototype.getResources = function(resourceType) {
	Polycode.ResourcePool_getResources(this.__ptr, resourceType)
}

ResourcePool.prototype.checkForChangedFiles = function() {
	Polycode.ResourcePool_checkForChangedFiles(this.__ptr)
}
