function Cubemap() {
}

Cubemap.prototype.getTexture = function(index) {
	Polycode.Cubemap_getTexture(this.__ptr, index)
}

Cubemap.prototype.setTexture = function(texture,index) {
	Polycode.Cubemap_setTexture(this.__ptr, texture,index)
}

Cubemap.prototype.recreateFromTextures = function() {
	Polycode.Cubemap_recreateFromTextures(this.__ptr)
}
