function ShaderPlatformData() {
	Object.defineProperties(this, {
		'shaderID': { enumerable: true, configurable: true, get: ShaderPlatformData.prototype.__get_shaderID, set: ShaderPlatformData.prototype.__set_shaderID},
		'vertexProgramID': { enumerable: true, configurable: true, get: ShaderPlatformData.prototype.__get_vertexProgramID, set: ShaderPlatformData.prototype.__set_vertexProgramID},
		'fragmentProgramID': { enumerable: true, configurable: true, get: ShaderPlatformData.prototype.__get_fragmentProgramID, set: ShaderPlatformData.prototype.__set_fragmentProgramID}
	})
}
ShaderPlatformData.prototype.__get_shaderID = function() {
	var retVal = new GLuint()
	retVal.__ptr = 	Polycode.ShaderPlatformData__get_shaderID(this.__ptr)
	return retVal
}

ShaderPlatformData.prototype.__set_shaderID = function(val) {
	Polycode.ShaderPlatformData__set_shaderID(this.__ptr, val.__ptr)
}

ShaderPlatformData.prototype.__get_vertexProgramID = function() {
	var retVal = new GLuint()
	retVal.__ptr = 	Polycode.ShaderPlatformData__get_vertexProgramID(this.__ptr)
	return retVal
}

ShaderPlatformData.prototype.__set_vertexProgramID = function(val) {
	Polycode.ShaderPlatformData__set_vertexProgramID(this.__ptr, val.__ptr)
}

ShaderPlatformData.prototype.__get_fragmentProgramID = function() {
	var retVal = new GLuint()
	retVal.__ptr = 	Polycode.ShaderPlatformData__get_fragmentProgramID(this.__ptr)
	return retVal
}

ShaderPlatformData.prototype.__set_fragmentProgramID = function(val) {
	Polycode.ShaderPlatformData__set_fragmentProgramID(this.__ptr, val.__ptr)
}

Duktape.fin(ShaderPlatformData.prototype, function (x) {
	if (x === ShaderPlatformData.prototype) {
		return;
	}
	Polycode.ShaderPlatformData__delete(x.__ptr)
})
