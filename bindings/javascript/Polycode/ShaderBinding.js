function ShaderBinding() {
}

ShaderBinding.prototype.copyTo = function(targetBinding) {
	Polycode.ShaderBinding_copyTo(this.__ptr, targetBinding)
}

ShaderBinding.prototype.addParam = function(type,name) {
	Polycode.ShaderBinding_addParam(this.__ptr, type,name)
}

ShaderBinding.prototype.addParamPointer = function(type,name,ptr) {
	Polycode.ShaderBinding_addParamPointer(this.__ptr, type,name,ptr)
}

ShaderBinding.prototype.getNumLocalParams = function() {
	Polycode.ShaderBinding_getNumLocalParams(this.__ptr)
}

ShaderBinding.prototype.getLocalParam = function(index) {
	Polycode.ShaderBinding_getLocalParam(this.__ptr, index)
}

ShaderBinding.prototype.getLocalParamByName = function(name) {
	Polycode.ShaderBinding_getLocalParamByName(this.__ptr, name)
}

ShaderBinding.prototype.removeParam = function(name) {
	Polycode.ShaderBinding_removeParam(this.__ptr, name)
}

ShaderBinding.prototype.loadTextureForParam = function(paramName,fileName) {
	Polycode.ShaderBinding_loadTextureForParam(this.__ptr, paramName,fileName)
}

ShaderBinding.prototype.setTextureForParam = function(paramName,texture) {
	Polycode.ShaderBinding_setTextureForParam(this.__ptr, paramName,texture)
}

ShaderBinding.prototype.setCubemapForParam = function(paramName,cubemap) {
	Polycode.ShaderBinding_setCubemapForParam(this.__ptr, paramName,cubemap)
}

ShaderBinding.prototype.getNumAttributeBindings = function() {
	Polycode.ShaderBinding_getNumAttributeBindings(this.__ptr)
}

ShaderBinding.prototype.getAttributeBinding = function(index) {
	Polycode.ShaderBinding_getAttributeBinding(this.__ptr, index)
}

ShaderBinding.prototype.addAttributeBinding = function(name,dataArray) {
	Polycode.ShaderBinding_addAttributeBinding(this.__ptr, name,dataArray)
}

ShaderBinding.prototype.getAttributeBindingByName = function(name) {
	Polycode.ShaderBinding_getAttributeBindingByName(this.__ptr, name)
}

ShaderBinding.prototype.addRenderTargetBinding = function(binding) {
	Polycode.ShaderBinding_addRenderTargetBinding(this.__ptr, binding)
}

ShaderBinding.prototype.removeRenderTargetBinding = function(binding) {
	Polycode.ShaderBinding_removeRenderTargetBinding(this.__ptr, binding)
}

ShaderBinding.prototype.getNumRenderTargetBindings = function() {
	Polycode.ShaderBinding_getNumRenderTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getRenderTargetBinding = function(index) {
	Polycode.ShaderBinding_getRenderTargetBinding(this.__ptr, index)
}

ShaderBinding.prototype.getNumInTargetBindings = function() {
	Polycode.ShaderBinding_getNumInTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getInTargetBinding = function(index) {
	Polycode.ShaderBinding_getInTargetBinding(this.__ptr, index)
}

ShaderBinding.prototype.getNumColorTargetBindings = function() {
	Polycode.ShaderBinding_getNumColorTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getColorTargetBinding = function(index) {
	Polycode.ShaderBinding_getColorTargetBinding(this.__ptr, index)
}

ShaderBinding.prototype.getNumDepthTargetBindings = function() {
	Polycode.ShaderBinding_getNumDepthTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getDepthTargetBinding = function(index) {
	Polycode.ShaderBinding_getDepthTargetBinding(this.__ptr, index)
}

ShaderBinding.prototype.getNumOutTargetBindings = function() {
	Polycode.ShaderBinding_getNumOutTargetBindings(this.__ptr)
}

ShaderBinding.prototype.getOutTargetBinding = function(index) {
	Polycode.ShaderBinding_getOutTargetBinding(this.__ptr, index)
}
