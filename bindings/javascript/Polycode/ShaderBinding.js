function ShaderBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ShaderBinding()
	}
	Object.defineProperties(this, {
		'accessMutex': { enumerable: true, configurable: true, get: ShaderBinding.prototype.__get_accessMutex, set: ShaderBinding.prototype.__set_accessMutex}
	})
}

ShaderBinding.prototype.__get_accessMutex = function() {
	var retVal = new CoreMutex()
	retVal.__ptr = 	Polycode.ShaderBinding__get_accessMutex(this.__ptr)
	return retVal
}

ShaderBinding.prototype.__set_accessMutex = function(val) {
	Polycode.ShaderBinding__set_accessMutex(this.__ptr, val.__ptr)
}

Duktape.fin(ShaderBinding.prototype, function (x) {
	if (x === ShaderBinding.prototype) {
		return;
	}
	Polycode.ShaderBinding__delete(x.__ptr)
})

ShaderBinding.prototype.copyTo = function(targetBinding) {
	Polycode.ShaderBinding_copyTo(this.__ptr, targetBinding.__ptr)
}

ShaderBinding.prototype.addParam = function(type,name) {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.ShaderBinding_addParam(this.__ptr, type, name)
	return retVal
}

ShaderBinding.prototype.addParamPointer = function(type,name,ptr) {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.ShaderBinding_addParamPointer(this.__ptr, type, name, ptr.__ptr)
	return retVal
}

ShaderBinding.prototype.addParamFromData = function(name,data) {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.ShaderBinding_addParamFromData(this.__ptr, name, data)
	return retVal
}

ShaderBinding.prototype.getNumLocalParams = function() {
	return Polycode.ShaderBinding_getNumLocalParams(this.__ptr)
}

ShaderBinding.prototype.getLocalParam = function(index) {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.ShaderBinding_getLocalParam(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getLocalParamByName = function(name) {
	var retVal = new LocalShaderParam()
	retVal.__ptr = Polycode.ShaderBinding_getLocalParamByName(this.__ptr, name)
	return retVal
}

ShaderBinding.prototype.removeParam = function(name) {
	Polycode.ShaderBinding_removeParam(this.__ptr, name)
}

ShaderBinding.prototype.loadTextureForParam = function(paramName,fileName) {
	var retVal = new Texture()
	retVal.__ptr = Polycode.ShaderBinding_loadTextureForParam(this.__ptr, paramName, fileName)
	return retVal
}

ShaderBinding.prototype.setTextureForParam = function(paramName,texture) {
	Polycode.ShaderBinding_setTextureForParam(this.__ptr, paramName, texture)
}

ShaderBinding.prototype.setCubemapForParam = function(paramName,cubemap) {
	Polycode.ShaderBinding_setCubemapForParam(this.__ptr, paramName, cubemap)
}

ShaderBinding.prototype.getNumAttributeBindings = function() {
	return Polycode.ShaderBinding_getNumAttributeBindings(this.__ptr)
}

ShaderBinding.prototype.getAttributeBinding = function(index) {
	var retVal = new AttributeBinding()
	retVal.__ptr = Polycode.ShaderBinding_getAttributeBinding(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.addAttributeBinding = function(name,dataArray) {
	var retVal = new AttributeBinding()
	retVal.__ptr = Polycode.ShaderBinding_addAttributeBinding(this.__ptr, name, dataArray.__ptr)
	return retVal
}

ShaderBinding.prototype.getAttributeBindingByName = function(name) {
	var retVal = new AttributeBinding()
	retVal.__ptr = Polycode.ShaderBinding_getAttributeBindingByName(this.__ptr, name)
	return retVal
}

ShaderBinding.prototype.addRenderTargetBinding = function(binding) {
	Polycode.ShaderBinding_addRenderTargetBinding(this.__ptr, binding.__ptr)
}

ShaderBinding.prototype.removeRenderTargetBinding = function(binding) {
	Polycode.ShaderBinding_removeRenderTargetBinding(this.__ptr, binding.__ptr)
}

ShaderBinding.prototype.getNumRenderTargetBindings = function() {
	return Polycode.ShaderBinding_getNumRenderTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getRenderTargetBinding = function(index) {
	var retVal = new RenderTargetBinding()
	retVal.__ptr = Polycode.ShaderBinding_getRenderTargetBinding(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getNumInTargetBindings = function() {
	return Polycode.ShaderBinding_getNumInTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getInTargetBinding = function(index) {
	var retVal = new RenderTargetBinding()
	retVal.__ptr = Polycode.ShaderBinding_getInTargetBinding(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getNumColorTargetBindings = function() {
	return Polycode.ShaderBinding_getNumColorTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getColorTargetBinding = function(index) {
	var retVal = new RenderTargetBinding()
	retVal.__ptr = Polycode.ShaderBinding_getColorTargetBinding(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getNumDepthTargetBindings = function() {
	return Polycode.ShaderBinding_getNumDepthTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getDepthTargetBinding = function(index) {
	var retVal = new RenderTargetBinding()
	retVal.__ptr = Polycode.ShaderBinding_getDepthTargetBinding(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getNumOutTargetBindings = function() {
	return Polycode.ShaderBinding_getNumOutTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getOutTargetBinding = function(index) {
	var retVal = new RenderTargetBinding()
	retVal.__ptr = Polycode.ShaderBinding_getOutTargetBinding(this.__ptr, index)
	return retVal
}
