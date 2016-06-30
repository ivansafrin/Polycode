function Perlin(octaves,freq,amp,seed) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Perlin(octaves,freq,amp,seed)
	}
}


Duktape.fin(Perlin.prototype, function (x) {
	if (x === Perlin.prototype) {
		return;
	}
	Polycode.Perlin__delete(x.__ptr)
})

Perlin.prototype.Get2DTiledX = function(x,y,t) {
	return Polycode.Perlin_Get2DTiledX(this.__ptr, x, y, t)
}

Perlin.prototype.Get = function(x,y) {
	return Polycode.Perlin_Get(this.__ptr, x, y)
}

Perlin.prototype.Get2D = function(x,y) {
	return Polycode.Perlin_Get2D(this.__ptr, x, y)
}

Perlin.prototype.Get3D = function(x,y,z) {
	return Polycode.Perlin_Get3D(this.__ptr, x, y, z)
}
