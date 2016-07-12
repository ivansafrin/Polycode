require('Polycode/Resource')

function Shader() {
	Object.defineProperties(this, {
		'numSpotLights': { enumerable: true, configurable: true, get: Shader.prototype.__get_numSpotLights, set: Shader.prototype.__set_numSpotLights},
		'numPointLights': { enumerable: true, configurable: true, get: Shader.prototype.__get_numPointLights, set: Shader.prototype.__set_numPointLights},
		'screenShader': { enumerable: true, configurable: true, get: Shader.prototype.__get_screenShader, set: Shader.prototype.__set_screenShader},
		'name': { enumerable: true, configurable: true, get: Shader.prototype.__get_name, set: Shader.prototype.__set_name}
	})
}


Shader.prototype = Object.create(Resource.prototype)

Shader.prototype.__get_numSpotLights = function() {
	return Polycode.Shader__get_numSpotLights(this.__ptr)
}

Shader.prototype.__set_numSpotLights = function(val) {
	Polycode.Shader__set_numSpotLights(this.__ptr, val)
}

Shader.prototype.__get_numPointLights = function() {
	return Polycode.Shader__get_numPointLights(this.__ptr)
}

Shader.prototype.__set_numPointLights = function(val) {
	Polycode.Shader__set_numPointLights(this.__ptr, val)
}

Shader.prototype.__get_screenShader = function() {
	return Polycode.Shader__get_screenShader(this.__ptr)
}

Shader.prototype.__set_screenShader = function(val) {
	Polycode.Shader__set_screenShader(this.__ptr, val)
}

Shader.prototype.__get_name = function() {
	return Polycode.Shader__get_name(this.__ptr)
}

Shader.prototype.__set_name = function(val) {
	Polycode.Shader__set_name(this.__ptr, val)
}

Duktape.fin(Shader.prototype, function (x) {
	if (x === Shader.prototype) {
		return;
	}
	Polycode.Shader__delete(x.__ptr)
})

Shader.prototype.getType = function() {
	return Polycode.Shader_getType(this.__ptr)
}

Shader.prototype.setName = function(name) {
	Polycode.Shader_setName(this.__ptr, name)
}

Shader.prototype.getName = function() {
	return Polycode.Shader_getName(this.__ptr)
}

Shader.prototype.reload = function() {
	Polycode.Shader_reload(this.__ptr)
}

Shader.prototype.getExpectedParamType = function(name) {
	return Polycode.Shader_getExpectedParamType(this.__ptr, name)
}
