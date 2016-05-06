function Texture() {
}

Texture.prototype.reloadResource = function() {
	Polycode.Texture_reloadResource(this.__ptr)
}

Texture.prototype.setImageData = function(data) {
	Polycode.Texture_setImageData(this.__ptr, data)
}

Texture.prototype.getTextureData = function() {
	Polycode.Texture_getTextureData(this.__ptr)
}

Texture.prototype.getWidth = function() {
	Polycode.Texture_getWidth(this.__ptr)
}

Texture.prototype.getHeight = function() {
	Polycode.Texture_getHeight(this.__ptr)
}

Texture.prototype.setCreateMipmaps = function(createMipmapsIn) {
	Polycode.Texture_setCreateMipmaps(this.__ptr, createMipmapsIn)
}

Texture.prototype.getCreateMipmaps = function() {
	Polycode.Texture_getCreateMipmaps(this.__ptr)
}
