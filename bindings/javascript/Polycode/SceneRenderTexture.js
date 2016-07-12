function SceneRenderTexture(renderWidth,renderHeight,floatingPoint) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.SceneRenderTexture(renderWidth,renderHeight,floatingPoint)
	}
	Object.defineProperties(this, {
		'enabled': { enumerable: true, configurable: true, get: SceneRenderTexture.prototype.__get_enabled, set: SceneRenderTexture.prototype.__set_enabled}
	})
}


SceneRenderTexture.prototype.__get_enabled = function() {
	return Polycode.SceneRenderTexture__get_enabled(this.__ptr)
}

SceneRenderTexture.prototype.__set_enabled = function(val) {
	Polycode.SceneRenderTexture__set_enabled(this.__ptr, val)
}

Duktape.fin(SceneRenderTexture.prototype, function (x) {
	if (x === SceneRenderTexture.prototype) {
		return;
	}
	Polycode.SceneRenderTexture__delete(x.__ptr)
})

SceneRenderTexture.prototype.getTargetTexture = function() {
	var retVal = new Texture("__skip_ptr__")
	retVal.__ptr = Polycode.SceneRenderTexture_getTargetTexture(this.__ptr)
	return retVal
}

SceneRenderTexture.prototype.resizeRenderTexture = function(newWidth,newHeight) {
	Polycode.SceneRenderTexture_resizeRenderTexture(this.__ptr, newWidth, newHeight)
}
