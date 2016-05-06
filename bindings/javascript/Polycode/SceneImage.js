function SceneImage() {
}

SceneImage.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	Polycode.SceneImage_Clone(this.__ptr, deepClone,ignoreEditorOnly)
}

SceneImage.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneImage_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneImage.prototype.setImageCoordinates = function(x,y,width,height,realWidth,realHeight) {
	Polycode.SceneImage_setImageCoordinates(this.__ptr, x,y,width,height,realWidth,realHeight)
}

SceneImage.prototype.getImageWidth = function() {
	Polycode.SceneImage_getImageWidth(this.__ptr)
}

SceneImage.prototype.getImageHeight = function() {
	Polycode.SceneImage_getImageHeight(this.__ptr)
}
