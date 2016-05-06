function Quaternion() {
}

Quaternion.prototype.setFromMatrix = function(_mat) {
	Polycode.Quaternion_setFromMatrix(this.__ptr, _mat)
}

Quaternion.prototype.Dot = function(rkQ) {
	Polycode.Quaternion_Dot(this.__ptr, rkQ)
}

Quaternion.prototype.Log = function() {
	Polycode.Quaternion_Log(this.__ptr)
}

Quaternion.prototype.Exp = function() {
	Polycode.Quaternion_Exp(this.__ptr)
}

Quaternion.prototype.Norm = function() {
	Polycode.Quaternion_Norm(this.__ptr)
}

Quaternion.prototype.Normalize = function() {
	Polycode.Quaternion_Normalize(this.__ptr)
}

Quaternion.prototype.lookAt = function(D,upVector) {
	Polycode.Quaternion_lookAt(this.__ptr, D,upVector)
}

Quaternion.prototype.createFromMatrix = function(matrix) {
	Polycode.Quaternion_createFromMatrix(this.__ptr, matrix)
}

Quaternion.prototype.Inverse = function() {
	Polycode.Quaternion_Inverse(this.__ptr)
}

Quaternion.prototype.set = function(w,x,y,z) {
	Polycode.Quaternion_set(this.__ptr, w,x,y,z)
}

Quaternion.prototype.InvSqrt = function(x) {
	Polycode.Quaternion_InvSqrt(this.__ptr, x)
}

Quaternion.prototype.fromAxes = function(az,ay,ax) {
	Polycode.Quaternion_fromAxes(this.__ptr, az,ay,ax)
}

Quaternion.prototype.fromAngleAxis = function(rfAngle,rkAxis) {
	Polycode.Quaternion_fromAngleAxis(this.__ptr, rfAngle,rkAxis)
}

Quaternion.prototype.toEulerAngles = function() {
	Polycode.Quaternion_toEulerAngles(this.__ptr)
}

Quaternion.prototype.toAngleAxis = function(rfAngle,rkAxis) {
	Polycode.Quaternion_toAngleAxis(this.__ptr, rfAngle,rkAxis)
}

Quaternion.prototype.createFromAxisAngle = function(x,y,z,degrees) {
	Polycode.Quaternion_createFromAxisAngle(this.__ptr, x,y,z,degrees)
}

Quaternion.prototype.createMatrix = function() {
	Polycode.Quaternion_createMatrix(this.__ptr)
}

Quaternion.prototype.applyTo = function(v) {
	Polycode.Quaternion_applyTo(this.__ptr, v)
}
