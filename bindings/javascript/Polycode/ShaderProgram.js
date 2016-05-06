function ShaderProgram() {
}

ShaderProgram.prototype.reloadProgram = function() {
	Polycode.ShaderProgram_reloadProgram(this.__ptr)
}

ShaderProgram.prototype.reloadResource = function() {
	Polycode.ShaderProgram_reloadResource(this.__ptr)
}
