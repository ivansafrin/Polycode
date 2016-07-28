require('Polycode/EventDispatcher')

function ResourcePool() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ResourcePool()
	}
	Object.defineProperties(this, {
		'reloadResourcesOnModify': { enumerable: true, configurable: true, get: ResourcePool.prototype.__get_reloadResourcesOnModify, set: ResourcePool.prototype.__set_reloadResourcesOnModify},
		'dispatchChangeEvents': { enumerable: true, configurable: true, get: ResourcePool.prototype.__get_dispatchChangeEvents, set: ResourcePool.prototype.__set_dispatchChangeEvents},
		'resourceSubscribers': { enumerable: true, configurable: true, get: ResourcePool.prototype.__get_resourceSubscribers, set: ResourcePool.prototype.__set_resourceSubscribers},
		'deleteOnUnsubscribe': { enumerable: true, configurable: true, get: ResourcePool.prototype.__get_deleteOnUnsubscribe, set: ResourcePool.prototype.__set_deleteOnUnsubscribe}
	})
}


ResourcePool.prototype = Object.create(EventDispatcher.prototype)

ResourcePool.prototype.__get_reloadResourcesOnModify = function() {
	return Polycode.ResourcePool__get_reloadResourcesOnModify(this.__ptr)
}

ResourcePool.prototype.__set_reloadResourcesOnModify = function(val) {
	Polycode.ResourcePool__set_reloadResourcesOnModify(this.__ptr, val)
}

ResourcePool.prototype.__get_dispatchChangeEvents = function() {
	return Polycode.ResourcePool__get_dispatchChangeEvents(this.__ptr)
}

ResourcePool.prototype.__set_dispatchChangeEvents = function(val) {
	Polycode.ResourcePool__set_dispatchChangeEvents(this.__ptr, val)
}

ResourcePool.prototype.__get_resourceSubscribers = function() {
	return Polycode.ResourcePool__get_resourceSubscribers(this.__ptr)
}

ResourcePool.prototype.__set_resourceSubscribers = function(val) {
	Polycode.ResourcePool__set_resourceSubscribers(this.__ptr, val)
}

ResourcePool.prototype.__get_deleteOnUnsubscribe = function() {
	return Polycode.ResourcePool__get_deleteOnUnsubscribe(this.__ptr)
}

ResourcePool.prototype.__set_deleteOnUnsubscribe = function(val) {
	Polycode.ResourcePool__set_deleteOnUnsubscribe(this.__ptr, val)
}

Duktape.fin(ResourcePool.prototype, function (x) {
	if (x === ResourcePool.prototype) {
		return;
	}
	Polycode.ResourcePool__delete(x.__ptr)
})

ResourcePool.prototype.addResource = function(resource) {
	Polycode.ResourcePool_addResource(this.__ptr, resource)
}

ResourcePool.prototype.removeResource = function(resource) {
	Polycode.ResourcePool_removeResource(this.__ptr, resource)
}

ResourcePool.prototype.hasResource = function(resource) {
	return Polycode.ResourcePool_hasResource(this.__ptr, resource)
}

ResourcePool.prototype.loadResourcesFromFolder = function(folder,recursive) {
	Polycode.ResourcePool_loadResourcesFromFolder(this.__ptr, folder, recursive)
}

ResourcePool.prototype.loadResourcesFromMaterialFile = function(path) {
	Polycode.ResourcePool_loadResourcesFromMaterialFile(this.__ptr, path)
}

ResourcePool.prototype.loadResource = function(path) {
	var retVal = new Resource("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_loadResource(this.__ptr, path)
	return retVal
}

ResourcePool.prototype.loadResourceWithName = function(path,name) {
	var retVal = new Resource("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_loadResourceWithName(this.__ptr, path, name)
	return retVal
}

ResourcePool.prototype.getResource = function(resourceType,resourceName) {
	var retVal = new Resource("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_getResource(this.__ptr, resourceType, resourceName)
	return retVal
}

ResourcePool.prototype.getFont = function(name) {
	var retVal = new Font("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_getFont(this.__ptr, name)
	return retVal
}

ResourcePool.prototype.getMaterial = function(name) {
	var retVal = new Material("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_getMaterial(this.__ptr, name)
	return retVal
}

ResourcePool.prototype.getShader = function(name) {
	var retVal = new Shader("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_getShader(this.__ptr, name)
	return retVal
}

ResourcePool.prototype.loadTexture = function(name) {
	var retVal = new Texture("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_loadTexture(this.__ptr, name)
	return retVal
}

ResourcePool.prototype.loadMesh = function(name) {
	var retVal = new Mesh("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_loadMesh(this.__ptr, name)
	return retVal
}

ResourcePool.prototype.getName = function() {
	return Polycode.ResourcePool_getName(this.__ptr)
}

ResourcePool.prototype.setName = function(name) {
	Polycode.ResourcePool_setName(this.__ptr, name)
}

ResourcePool.prototype.loadFont = function(name,path) {
	var retVal = new Font("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_loadFont(this.__ptr, name, path)
	return retVal
}

ResourcePool.prototype.getResourceByPath = function(resourcePath) {
	var retVal = new Resource("__skip_ptr__")
	retVal.__ptr = Polycode.ResourcePool_getResourceByPath(this.__ptr, resourcePath)
	return retVal
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
