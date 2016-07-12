require('Polycode/EventDispatcher')

function ResourceManager() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ResourceManager()
	}
}


ResourceManager.prototype = Object.create(EventDispatcher.prototype)

Duktape.fin(ResourceManager.prototype, function (x) {
	if (x === ResourceManager.prototype) {
		return;
	}
	Polycode.ResourceManager__delete(x.__ptr)
})

ResourceManager.prototype.getNumResourceLoaders = function() {
	return Polycode.ResourceManager_getNumResourceLoaders(this.__ptr)
}

ResourceManager.prototype.getResources = function(resourceType) {
	Polycode.ResourceManager_getResources(this.__ptr, resourceType)
}

ResourceManager.prototype.removeResource = function(resource) {
	Polycode.ResourceManager_removeResource(this.__ptr, resource)
}

ResourceManager.prototype.Update = function(elapsed) {
	Polycode.ResourceManager_Update(this.__ptr, elapsed)
}
