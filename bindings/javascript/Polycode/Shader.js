function Shader() {
}

Shader.prototype.getType = function() {
	Polycode.Shader_getType(this.__ptr)
}

Shader.prototype.setName = function(name) {
	Polycode.Shader_setName(this.__ptr, name)
}

Shader.prototype.getName = function() {
	Polycode.Shader_getName(this.__ptr)
}

Shader.prototype.getParamPointer = function(name) {
	Polycode.Shader_getParamPointer(this.__ptr, name)
}

Shader.prototype.getAttribPointer = function(name) {
	Polycode.Shader_getAttribPointer(this.__ptr, name)
}

Shader.prototype.reload = function() {
	Polycode.Shader_reload(this.__ptr)
}

Shader.prototype.getExpectedParamType = function(name) {
	Polycode.Shader_getExpectedParamType(this.__ptr, name)
}

Shader.prototype.setVertexProgram = function(vp) {
	Polycode.Shader_setVertexProgram(this.__ptr, vp)
}

Shader.prototype.setFragmentProgram = function(fp) {
	Polycode.Shader_setFragmentProgram(this.__ptr, fp)
}
