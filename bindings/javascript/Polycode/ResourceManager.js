function ResourceManager() {
}

ResourceManager.prototype.getGlobalPool = function() {
	var retVal = new ResourcePool()
	retVal.__ptr = Polycode.ResourceManager_getGlobalPool(this.__ptr)
	return retVal
}

ResourceManager.prototype.getResourcePoolByName = function(name) {
	var retVal = new ResourcePool()
	retVal.__ptr = Polycode.ResourceManager_getResourcePoolByName(this.__ptr, name)
	return retVal
}

ResourceManager.prototype.addResourceLoader = function(loader) {
	Polycode.ResourceManager_addResourceLoader(this.__ptr, loader)
}

ResourceManager.prototype.getResourceLoaderForExtension = function(extension) {
	var retVal = new ResourceLoader()
	retVal.__ptr = Polycode.ResourceManager_getResourceLoaderForExtension(this.__ptr, extension)
	return retVal
}

ResourceManager.prototype.removeResourceLoader = function(loader) {
	Polycode.ResourceManager_removeResourceLoader(this.__ptr, loader)
}

ResourceManager.prototype.getNumResourceLoaders = function() {
	return Polycode.ResourceManager_getNumResourceLoaders(this.__ptr)
}

ResourceManager.prototype.getResourceLoaderAtIndex = function(index) {
	var retVal = new ResourceLoader()
	retVal.__ptr = Polycode.ResourceManager_getResourceLoaderAtIndex(this.__ptr, index)
	return retVal
}

ResourceManager.prototype.addResourcePool = function(pool) {
	Polycode.ResourceManager_addResourcePool(this.__ptr, pool)
}

ResourceManager.prototype.removeResourcePool = function(pool) {
	Polycode.ResourceManager_removeResourcePool(this.__ptr, pool)
}

ResourceManager.prototype.getResources = function(resourceType) {
	Polycode.ResourceManager_getResources(this.__ptr, resourceType)
}

ResourceManager.prototype.removeResource = function(resource) {
	Polycode.ResourceManager_removeResource(this.__ptr, resource)
}

ResourceManager.prototype.subscribeToResourcePool = function(pool) {
	Polycode.ResourceManager_subscribeToResourcePool(this.__ptr, pool)
}

ResourceManager.prototype.unsubscibeFromResourcePool = function(pool) {
	Polycode.ResourceManager_unsubscibeFromResourcePool(this.__ptr, pool)
}

ResourceManager.prototype.Update = function(elapsed) {
	Polycode.ResourceManager_Update(this.__ptr, elapsed)
}
