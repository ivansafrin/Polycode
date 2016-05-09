function SceneImage() {
}

SceneImage.prototype.Clone = function(deepClone,ignoreEditorOnly) {
	var retVal = new Entity()
	retVal.__ptr = Polycode.SceneImage_Clone(this.__ptr, deepClone,ignoreEditorOnly)
	return retVal
}

SceneImage.prototype.applyClone = function(clone,deepClone,ignoreEditorOnly) {
	Polycode.SceneImage_applyClone(this.__ptr, clone,deepClone,ignoreEditorOnly)
}

SceneImage.prototype.setImageCoordinates = function(x,y,width,height,realWidth,realHeight) {
	Polycode.SceneImage_setImageCoordinates(this.__ptr, x,y,width,height,realWidth,realHeight)
}

SceneImage.prototype.getImageWidth = function() {
	return Polycode.SceneImage_getImageWidth(this.__ptr)
}

SceneImage.prototype.getImageHeight = function() {
	return Polycode.SceneImage_getImageHeight(this.__ptr)
}
