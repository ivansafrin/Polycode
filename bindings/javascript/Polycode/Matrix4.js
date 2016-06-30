function Matrix4() {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Matrix4()
	}
}


Duktape.fin(Matrix4.prototype, function (x) {
	if (x === Matrix4.prototype) {
		return;
	}
	Polycode.Matrix4__delete(x.__ptr)
})

Matrix4.prototype.identity = function() {
	Polycode.Matrix4_identity(this.__ptr)
}

Matrix4.prototype.rotateVector = function(v2) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Matrix4_rotateVector(this.__ptr, v2)
	return retVal
}

Matrix4.prototype.getPosition = function() {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Matrix4_getPosition(this.__ptr)
	return retVal
}

Matrix4.prototype.multiplyWithPerspective = function(v2) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Matrix4_multiplyWithPerspective(this.__ptr, v2)
	return retVal
}

Matrix4.prototype.multVector3 = function(v2) {
	var retVal = new Vector3()
	retVal.__ptr = Polycode.Matrix4_multVector3(this.__ptr, v2)
	return retVal
}

Matrix4.prototype.multVector4 = function(v2) {
	var retVal = new Vector4()
	retVal.__ptr = Polycode.Matrix4_multVector4(this.__ptr, v2)
	return retVal
}

Matrix4.prototype.Translate = function(x,y,z) {
	Polycode.Matrix4_Translate(this.__ptr, x, y, z)
}

Matrix4.prototype.setPosition = function(x,y,z) {
	Polycode.Matrix4_setPosition(this.__ptr, x, y, z)
}

Matrix4.prototype.setScale = function(scale) {
	Polycode.Matrix4_setScale(this.__ptr, scale)
}

Matrix4.prototype.getEulerAngles = function(ax,ay,az) {
	Polycode.Matrix4_getEulerAngles(this.__ptr, ax.__ptr, ay.__ptr, az.__ptr)
}

Matrix4.prototype.transpose = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Matrix4_transpose(this.__ptr)
	return retVal
}

Matrix4.prototype.Inverse = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Matrix4_Inverse(this.__ptr)
	return retVal
}

Matrix4.prototype.inverseAffine = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Matrix4_inverseAffine(this.__ptr)
	return retVal
}

Matrix4.prototype.determinant = function() {
	return Polycode.Matrix4_determinant(this.__ptr)
}

Matrix4.prototype.generalDeterminant = function(a,n) {
	return Polycode.Matrix4_generalDeterminant(a.__ptr, n)
}

Matrix4.prototype.setOrthoProjection = function(left,right,bottom,top,zNear,zFar) {
	Polycode.Matrix4_setOrthoProjection(this.__ptr, left, right, bottom, top, zNear, zFar)
}

Matrix4.prototype.setProjectionFrustum = function(left,right,bottom,top,zNear,zFar) {
	Polycode.Matrix4_setProjectionFrustum(this.__ptr, left, right, bottom, top, zNear, zFar)
}

Matrix4.prototype.setProjection = function(fov,aspect,zNear,zFar) {
	Polycode.Matrix4_setProjection(this.__ptr, fov, aspect, zNear, zFar)
}
