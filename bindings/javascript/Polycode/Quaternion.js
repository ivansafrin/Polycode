function Quaternion(w,x,y,z) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Quaternion(w,x,y,z)
	}
	Object.defineProperties(this, {
		'x': { enumerable: true, configurable: true, get: Quaternion.prototype.__get_x, set: Quaternion.prototype.__set_x},
		'y': { enumerable: true, configurable: true, get: Quaternion.prototype.__get_y, set: Quaternion.prototype.__set_y},
		'z': { enumerable: true, configurable: true, get: Quaternion.prototype.__get_z, set: Quaternion.prototype.__set_z},
		'w': { enumerable: true, configurable: true, get: Quaternion.prototype.__get_w, set: Quaternion.prototype.__set_w}
	})
}


Quaternion.prototype.__get_x = function() {
	return Polycode.Quaternion__get_x(this.__ptr)
}

Quaternion.prototype.__set_x = function(val) {
	Polycode.Quaternion__set_x(this.__ptr, val)
}

Quaternion.prototype.__get_y = function() {
	return Polycode.Quaternion__get_y(this.__ptr)
}

Quaternion.prototype.__set_y = function(val) {
	Polycode.Quaternion__set_y(this.__ptr, val)
}

Quaternion.prototype.__get_z = function() {
	return Polycode.Quaternion__get_z(this.__ptr)
}

Quaternion.prototype.__set_z = function(val) {
	Polycode.Quaternion__set_z(this.__ptr, val)
}

Quaternion.prototype.__get_w = function() {
	return Polycode.Quaternion__get_w(this.__ptr)
}

Quaternion.prototype.__set_w = function(val) {
	Polycode.Quaternion__set_w(this.__ptr, val)
}

Duktape.fin(Quaternion.prototype, function (x) {
	if (x === Quaternion.prototype) {
		return;
	}
	Polycode.Quaternion__delete(x.__ptr)
})

Quaternion.prototype.setFromMatrix = function(_mat) {
	Polycode.Quaternion_setFromMatrix(this.__ptr, _mat)
}

Quaternion.prototype.Slerp = function(fT,rkP,rkQ,shortestPath) {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.Quaternion_Slerp(fT, rkP, rkQ, shortestPath)
	return retVal
}

Quaternion.prototype.Dot = function(rkQ) {
	return Polycode.Quaternion_Dot(this.__ptr, rkQ)
}

Quaternion.prototype.Log = function() {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.Quaternion_Log(this.__ptr)
	return retVal
}

Quaternion.prototype.Exp = function() {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.Quaternion_Exp(this.__ptr)
	return retVal
}

Quaternion.prototype.Norm = function() {
	return Polycode.Quaternion_Norm(this.__ptr)
}

Quaternion.prototype.Normalize = function() {
	return Polycode.Quaternion_Normalize(this.__ptr)
}

Quaternion.prototype.lookAt = function(D,upVector) {
	Polycode.Quaternion_lookAt(this.__ptr, D, upVector)
}

Quaternion.prototype.createFromMatrix = function(matrix) {
	Polycode.Quaternion_createFromMatrix(this.__ptr, matrix)
}

Quaternion.prototype.Squad = function(fT,rkP,rkA,rkB,rkQ,shortestPath) {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.Quaternion_Squad(fT, rkP, rkA, rkB, rkQ, shortestPath)
	return retVal
}

Quaternion.prototype.Inverse = function() {
	var retVal = new Quaternion()
	retVal.__ptr = Polycode.Quaternion_Inverse(this.__ptr)
	return retVal
}

Quaternion.prototype.set = function(w,x,y,z) {
	Polycode.Quaternion_set(this.__ptr, w, x, y, z)
}

Quaternion.prototype.InvSqrt = function(x) {
	return Polycode.Quaternion_InvSqrt(this.__ptr, x)
}

Quaternion.prototype.fromAxes = function(az,ay,ax) {
	Polycode.Quaternion_fromAxes(this.__ptr, az, ay, ax)
}

Quaternion.prototype.fromAngleAxis = function(rfAngle,rkAxis) {
	Polycode.Quaternion_fromAngleAxis(this.__ptr, rfAngle, rkAxis)
}

Quaternion.prototype.toEulerAngles = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Quaternion_toEulerAngles(this.__ptr)
	return retVal
}

Quaternion.prototype.toAngleAxis = function(rfAngle,rkAxis) {
	Polycode.Quaternion_toAngleAxis(this.__ptr, rfAngle, rkAxis)
}

Quaternion.prototype.createFromAxisAngle = function(x,y,z,degrees) {
	Polycode.Quaternion_createFromAxisAngle(this.__ptr, x, y, z, degrees)
}

Quaternion.prototype.createMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Quaternion_createMatrix(this.__ptr)
	return retVal
}

Quaternion.prototype.applyTo = function(v) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Quaternion_applyTo(this.__ptr, v)
	return retVal
}
