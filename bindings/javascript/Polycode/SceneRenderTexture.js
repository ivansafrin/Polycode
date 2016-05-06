function SceneRenderTexture() {
}

SceneRenderTexture.prototype.getTargetTexture = function() {
	Polycode.SceneRenderTexture_getTargetTexture(this.__ptr)
}

SceneRenderTexture.prototype.getFilterColorBufferTexture = function() {
	Polycode.SceneRenderTexture_getFilterColorBufferTexture(this.__ptr)
}

SceneRenderTexture.prototype.getFilterZBufferTexture = function() {
	Polycode.SceneRenderTexture_getFilterZBufferTexture(this.__ptr)
}

SceneRenderTexture.prototype.Render = function() {
	Polycode.SceneRenderTexture_Render(this.__ptr)
}

SceneRenderTexture.prototype.saveToImage = function() {
	Polycode.SceneRenderTexture_saveToImage(this.__ptr)
}

SceneRenderTexture.prototype.resizeRenderTexture = function(newWidth,newHeight) {
	Polycode.SceneRenderTexture_resizeRenderTexture(this.__ptr, newWidth,newHeight)
}

SceneRenderTexture.prototype.getTargetScene = function() {
	Polycode.SceneRenderTexture_getTargetScene(this.__ptr)
}

SceneRenderTexture.prototype.getTargetCamera = function() {
	Polycode.SceneRenderTexture_getTargetCamera(this.__ptr)
}
