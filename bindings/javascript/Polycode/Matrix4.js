function Matrix4() {
}

Matrix4.prototype.identity = function() {
	Polycode.Matrix4_identity(this.__ptr)
}

Matrix4.prototype.rotateVector = function(v2) {
	Polycode.Matrix4_rotateVector(this.__ptr, v2)
}

Matrix4.prototype.getPosition = function() {
	Polycode.Matrix4_getPosition(this.__ptr)
}

Matrix4.prototype.multiplyWithPerspective = function(v2) {
	Polycode.Matrix4_multiplyWithPerspective(this.__ptr, v2)
}

Matrix4.prototype.multVector3 = function(v2) {
	Polycode.Matrix4_multVector3(this.__ptr, v2)
}

Matrix4.prototype.multVector4 = function(v2) {
	Polycode.Matrix4_multVector4(this.__ptr, v2)
}

Matrix4.prototype.Translate = function(x,y,z) {
	Polycode.Matrix4_Translate(this.__ptr, x,y,z)
}

Matrix4.prototype.setPosition = function(x,y,z) {
	Polycode.Matrix4_setPosition(this.__ptr, x,y,z)
}

Matrix4.prototype.setScale = function(scale) {
	Polycode.Matrix4_setScale(this.__ptr, scale)
}

Matrix4.prototype.getEulerAngles = function(ax,ay,az) {
	Polycode.Matrix4_getEulerAngles(this.__ptr, ax,ay,az)
}

Matrix4.prototype.transpose = function() {
	Polycode.Matrix4_transpose(this.__ptr)
}

Matrix4.prototype.Inverse = function() {
	Polycode.Matrix4_Inverse(this.__ptr)
}

Matrix4.prototype.inverseAffine = function() {
	Polycode.Matrix4_inverseAffine(this.__ptr)
}

Matrix4.prototype.determinant = function() {
	Polycode.Matrix4_determinant(this.__ptr)
}

Matrix4.prototype.setOrthoProjection = function(left,right,bottom,top,zNear,zFar) {
	Polycode.Matrix4_setOrthoProjection(this.__ptr, left,right,bottom,top,zNear,zFar)
}

Matrix4.prototype.setProjectionFrustum = function(left,right,bottom,top,zNear,zFar) {
	Polycode.Matrix4_setProjectionFrustum(this.__ptr, left,right,bottom,top,zNear,zFar)
}

Matrix4.prototype.setProjection = function(fov,aspect,zNear,zFar) {
	Polycode.Matrix4_setProjection(this.__ptr, fov,aspect,zNear,zFar)
}
