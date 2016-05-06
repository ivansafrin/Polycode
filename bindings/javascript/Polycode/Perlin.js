function Perlin() {
}

Perlin.prototype.Get2DTiledX = function(x,y,t) {
	Polycode.Perlin_Get2DTiledX(this.__ptr, x,y,t)
}

Perlin.prototype.Get = function(x,y) {
	Polycode.Perlin_Get(this.__ptr, x,y)
}

Perlin.prototype.Get2D = function(x,y) {
	Polycode.Perlin_Get2D(this.__ptr, x,y)
}

Perlin.prototype.Get3D = function(x,y,z) {
	Polycode.Perlin_Get3D(this.__ptr, x,y,z)
}
