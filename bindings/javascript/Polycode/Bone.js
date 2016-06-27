require('Polycode/Entity')

function Bone(boneName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Bone(boneName)
	}
	Object.defineProperties(this, {
		'parentBoneId': { enumerable: true, configurable: true, get: Bone.prototype.__get_parentBoneId, set: Bone.prototype.__set_parentBoneId},
		'boneMatrix': { enumerable: true, configurable: true, get: Bone.prototype.__get_boneMatrix, set: Bone.prototype.__set_boneMatrix},
		'restMatrix': { enumerable: true, configurable: true, get: Bone.prototype.__get_restMatrix, set: Bone.prototype.__set_restMatrix},
		'baseMatrix': { enumerable: true, configurable: true, get: Bone.prototype.__get_baseMatrix, set: Bone.prototype.__set_baseMatrix},
		'finalMatrix': { enumerable: true, configurable: true, get: Bone.prototype.__get_finalMatrix, set: Bone.prototype.__set_finalMatrix},
		'baseRotation': { enumerable: true, configurable: true, get: Bone.prototype.__get_baseRotation, set: Bone.prototype.__set_baseRotation},
		'baseScale': { enumerable: true, configurable: true, get: Bone.prototype.__get_baseScale, set: Bone.prototype.__set_baseScale},
		'basePosition': { enumerable: true, configurable: true, get: Bone.prototype.__get_basePosition, set: Bone.prototype.__set_basePosition},
		'disableAnimation': { enumerable: true, configurable: true, get: Bone.prototype.__get_disableAnimation, set: Bone.prototype.__set_disableAnimation}
	})
}

Bone.prototype = Object.create(Entity.prototype);

Bone.prototype.__get_parentBoneId = function() {
	return Polycode.Bone__get_parentBoneId(this.__ptr)
}

Bone.prototype.__set_parentBoneId = function(val) {
	Polycode.Bone__set_parentBoneId(this.__ptr, val)
}

Bone.prototype.__get_boneMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.Bone__get_boneMatrix(this.__ptr)
	return retVal
}

Bone.prototype.__set_boneMatrix = function(val) {
	Polycode.Bone__set_boneMatrix(this.__ptr, val.__ptr)
}

Bone.prototype.__get_restMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.Bone__get_restMatrix(this.__ptr)
	return retVal
}

Bone.prototype.__set_restMatrix = function(val) {
	Polycode.Bone__set_restMatrix(this.__ptr, val.__ptr)
}

Bone.prototype.__get_baseMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.Bone__get_baseMatrix(this.__ptr)
	return retVal
}

Bone.prototype.__set_baseMatrix = function(val) {
	Polycode.Bone__set_baseMatrix(this.__ptr, val.__ptr)
}

Bone.prototype.__get_finalMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = 	Polycode.Bone__get_finalMatrix(this.__ptr)
	return retVal
}

Bone.prototype.__set_finalMatrix = function(val) {
	Polycode.Bone__set_finalMatrix(this.__ptr, val.__ptr)
}

Bone.prototype.__get_baseRotation = function() {
	var retVal = new Quaternion()
	retVal.__ptr = 	Polycode.Bone__get_baseRotation(this.__ptr)
	return retVal
}

Bone.prototype.__set_baseRotation = function(val) {
	Polycode.Bone__set_baseRotation(this.__ptr, val.__ptr)
}

Bone.prototype.__get_baseScale = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.Bone__get_baseScale(this.__ptr)
	return retVal
}

Bone.prototype.__set_baseScale = function(val) {
	Polycode.Bone__set_baseScale(this.__ptr, val.__ptr)
}

Bone.prototype.__get_basePosition = function() {
	var retVal = new Vector3()
	retVal.__ptr = 	Polycode.Bone__get_basePosition(this.__ptr)
	return retVal
}

Bone.prototype.__set_basePosition = function(val) {
	Polycode.Bone__set_basePosition(this.__ptr, val.__ptr)
}

Bone.prototype.__get_disableAnimation = function() {
	return Polycode.Bone__get_disableAnimation(this.__ptr)
}

Bone.prototype.__set_disableAnimation = function(val) {
	Polycode.Bone__set_disableAnimation(this.__ptr, val)
}

Duktape.fin(Bone.prototype, function (x) {
	if (x === Bone.prototype) {
		return;
	}
	Polycode.Bone__delete(x.__ptr)
})

Bone.prototype.getName = function() {
	return Polycode.Bone_getName(this.__ptr)
}

Bone.prototype.setParentBone = function(bone) {
	Polycode.Bone_setParentBone(this.__ptr, bone)
}

Bone.prototype.addChildBone = function(bone) {
	Polycode.Bone_addChildBone(this.__ptr, bone)
}

Bone.prototype.getParentBone = function() {
	var retVal = new Bone()
	retVal.__ptr = Polycode.Bone_getParentBone(this.__ptr)
	return retVal
}

Bone.prototype.getNumChildBones = function() {
	return Polycode.Bone_getNumChildBones(this.__ptr)
}

Bone.prototype.getChildBone = function(index) {
	var retVal = new Bone()
	retVal.__ptr = Polycode.Bone_getChildBone(this.__ptr, index)
	return retVal
}

Bone.prototype.getBoneMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getBoneMatrix(this.__ptr)
	return retVal
}

Bone.prototype.setBoneMatrix = function(matrix) {
	Polycode.Bone_setBoneMatrix(this.__ptr, matrix)
}

Bone.prototype.getRestMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getRestMatrix(this.__ptr)
	return retVal
}

Bone.prototype.getFullRestMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getFullRestMatrix(this.__ptr)
	return retVal
}

Bone.prototype.getParentRestMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getParentRestMatrix(this.__ptr)
	return retVal
}

Bone.prototype.getFinalMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getFinalMatrix(this.__ptr)
	return retVal
}

Bone.prototype.setRestMatrix = function(matrix) {
	Polycode.Bone_setRestMatrix(this.__ptr, matrix)
}

Bone.prototype.setBaseMatrix = function(matrix) {
	Polycode.Bone_setBaseMatrix(this.__ptr, matrix)
}

Bone.prototype.getBaseMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getBaseMatrix(this.__ptr)
	return retVal
}

Bone.prototype.getFullBaseMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_getFullBaseMatrix(this.__ptr)
	return retVal
}

Bone.prototype.rebuildFinalMatrix = function() {
	Polycode.Bone_rebuildFinalMatrix(this.__ptr)
}

Bone.prototype.buildFinalMatrix = function() {
	var retVal = new Matrix4()
	retVal.__ptr = Polycode.Bone_buildFinalMatrix(this.__ptr)
	return retVal
}

Bone.prototype.intializeBone = function(basePosition,baseScale,baseRotation,restPosition,restScale,restRotation) {
	Polycode.Bone_intializeBone(this.__ptr, basePosition, baseScale, baseRotation, restPosition, restScale, restRotation)
}
