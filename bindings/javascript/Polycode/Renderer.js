function Renderer() {
}

Renderer.BLEND_MODE_NONE = 0
Renderer.BLEND_MODE_NORMAL = 1
Renderer.BLEND_MODE_LIGHTEN = 2
Renderer.BLEND_MODE_COLOR = 3
Renderer.BLEND_MODE_PREMULTIPLIED = 4
Renderer.BLEND_MODE_MULTIPLY = 5
Renderer.BLEND_MODE_MATERIAL = 6
Renderer.DEPTH_FUNCTION_GREATER = 0
Renderer.DEPTH_FUNCTION_LEQUAL = 1

Duktape.fin(Renderer.prototype, function (x) {
	if (x === Renderer.prototype) {
		return;
	}
	Polycode.Renderer__delete(x.__ptr)
})

Renderer.prototype.setBackingResolutionScale = function(xScale,yScale) {
	Polycode.Renderer_setBackingResolutionScale(this.__ptr, xScale, yScale)
}

Renderer.prototype.getBackingResolutionScaleX = function() {
	return Polycode.Renderer_getBackingResolutionScaleX(this.__ptr)
}

Renderer.prototype.getBackingResolutionScaleY = function() {
	return Polycode.Renderer_getBackingResolutionScaleY(this.__ptr)
}

Renderer.prototype.setAnisotropyAmount = function(amount) {
	Polycode.Renderer_setAnisotropyAmount(this.__ptr, amount)
}

Renderer.prototype.getAnisotropyAmount = function() {
	return Polycode.Renderer_getAnisotropyAmount(this.__ptr)
}

Renderer.prototype.unProject = function(position,modelMatrix,projectionMatrix,viewport) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Renderer_unProject(position, modelMatrix, projectionMatrix, viewport)
	return retVal
}

Renderer.prototype.project = function(position,modelMatrix,projectionMatrix,viewport) {
	var retVal = new Vector3("__skip_ptr__")
	retVal.__ptr = Polycode.Renderer_project(position, modelMatrix, projectionMatrix, viewport)
	return retVal
}
