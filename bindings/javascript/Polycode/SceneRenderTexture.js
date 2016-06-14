function SceneRenderTexture() {
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
	var retVal = new shared_ptr<Texture>()
	retVal.__ptr = Polycode.SceneRenderTexture_getTargetTexture(this.__ptr)
	return retVal
}

SceneRenderTexture.prototype.Render = function() {
	Polycode.SceneRenderTexture_Render(this.__ptr)
}

SceneRenderTexture.prototype.saveToImage = function() {
	var retVal = new Image()
	retVal.__ptr = Polycode.SceneRenderTexture_saveToImage(this.__ptr)
	return retVal
}

SceneRenderTexture.prototype.resizeRenderTexture = function(newWidth,newHeight) {
	Polycode.SceneRenderTexture_resizeRenderTexture(this.__ptr, newWidth,newHeight)
}

SceneRenderTexture.prototype.getTargetScene = function() {
	var retVal = new Scene()
	retVal.__ptr = Polycode.SceneRenderTexture_getTargetScene(this.__ptr)
	return retVal
}

SceneRenderTexture.prototype.getTargetCamera = function() {
	var retVal = new Camera()
	retVal.__ptr = Polycode.SceneRenderTexture_getTargetCamera(this.__ptr)
	return retVal
}
