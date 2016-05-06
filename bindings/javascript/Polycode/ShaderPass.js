function ShaderPass() {
}

ShaderPass.prototype.setAttributeArraysFromMesh = function(mesh) {
	Polycode.ShaderPass_setAttributeArraysFromMesh(this.__ptr, mesh)
}

ShaderPass.prototype.setExpectedAttributes = function() {
	Polycode.ShaderPass_setExpectedAttributes(this.__ptr)
}
