function ShaderBinding() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.ShaderBinding()
	}
}


Duktape.fin(ShaderBinding.prototype, function (x) {
	if (x === ShaderBinding.prototype) {
		return;
	}
	Polycode.ShaderBinding__delete(x.__ptr)
})

ShaderBinding.prototype.addParam = function(type,name) {
	var retVal = new LocalShaderParam("__skip_ptr__")
	retVal.__ptr = Polycode.ShaderBinding_addParam(this.__ptr, type, name)
	return retVal
}

ShaderBinding.prototype.addParamFromData = function(name,data) {
	var retVal = new LocalShaderParam("__skip_ptr__")
	retVal.__ptr = Polycode.ShaderBinding_addParamFromData(this.__ptr, name, data)
	return retVal
}

ShaderBinding.prototype.getNumLocalParams = function() {
	return Polycode.ShaderBinding_getNumLocalParams(this.__ptr)
}

ShaderBinding.prototype.getLocalParam = function(index) {
	var retVal = new LocalShaderParam("__skip_ptr__")
	retVal.__ptr = Polycode.ShaderBinding_getLocalParam(this.__ptr, index)
	return retVal
}

ShaderBinding.prototype.getLocalParamByName = function(name) {
	var retVal = new LocalShaderParam("__skip_ptr__")
	retVal.__ptr = Polycode.ShaderBinding_getLocalParamByName(this.__ptr, name)
	return retVal
}

ShaderBinding.prototype.removeParam = function(name) {
	Polycode.ShaderBinding_removeParam(this.__ptr, name)
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

ShaderBinding.prototype.getNumRenderTargetBindings = function() {
	return Polycode.ShaderBinding_getNumRenderTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getNumInTargetBindings = function() {
	return Polycode.ShaderBinding_getNumInTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getNumColorTargetBindings = function() {
	return Polycode.ShaderBinding_getNumColorTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getNumDepthTargetBindings = function() {
	return Polycode.ShaderBinding_getNumDepthTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getNumOutTargetBindings = function() {
	return Polycode.ShaderBinding_getNumOutTargetBindings(this.__ptr)
}
