function LocalShaderParam() {
}

LocalShaderParam.prototype.Copy = function() {
	Polycode.LocalShaderParam_Copy(this.__ptr)
}

LocalShaderParam.prototype.getNumber = function() {
	Polycode.LocalShaderParam_getNumber(this.__ptr)
}

LocalShaderParam.prototype.getVector2 = function() {
	Polycode.LocalShaderParam_getVector2(this.__ptr)
}

LocalShaderParam.prototype.getVector3 = function() {
	Polycode.LocalShaderParam_getVector3(this.__ptr)
}

LocalShaderParam.prototype.getMatrix4 = function() {
	Polycode.LocalShaderParam_getMatrix4(this.__ptr)
}

LocalShaderParam.prototype.getColor = function() {
	Polycode.LocalShaderParam_getColor(this.__ptr)
}

LocalShaderParam.prototype.setNumber = function(x) {
	Polycode.LocalShaderParam_setNumber(this.__ptr, x)
}

LocalShaderParam.prototype.setVector2 = function(x) {
	Polycode.LocalShaderParam_setVector2(this.__ptr, x)
}

LocalShaderParam.prototype.setVector3 = function(x) {
	Polycode.LocalShaderParam_setVector3(this.__ptr, x)
}

LocalShaderParam.prototype.setMatrix4 = function(x) {
	Polycode.LocalShaderParam_setMatrix4(this.__ptr, x)
}

LocalShaderParam.prototype.setColor = function(x) {
	Polycode.LocalShaderParam_setColor(this.__ptr, x)
}

LocalShaderParam.prototype.setTexture = function(texture) {
	Polycode.LocalShaderParam_setTexture(this.__ptr, texture)
}

LocalShaderParam.prototype.getTexture = function() {
	Polycode.LocalShaderParam_getTexture(this.__ptr)
}

LocalShaderParam.prototype.setCubemap = function(cubemap) {
	Polycode.LocalShaderParam_setCubemap(this.__ptr, cubemap)
}

LocalShaderParam.prototype.getCubemap = function() {
	Polycode.LocalShaderParam_getCubemap(this.__ptr)
}

LocalShaderParam.prototype.setParamValueFromString = function(type,pvalue) {
	Polycode.LocalShaderParam_setParamValueFromString(this.__ptr, type,pvalue)
}
