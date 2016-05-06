function Bone() {
}

Bone.prototype.getName = function() {
	Polycode.Bone_getName(this.__ptr)
}

Bone.prototype.setParentBone = function(bone) {
	Polycode.Bone_setParentBone(this.__ptr, bone)
}

Bone.prototype.addChildBone = function(bone) {
	Polycode.Bone_addChildBone(this.__ptr, bone)
}

Bone.prototype.getParentBone = function() {
	Polycode.Bone_getParentBone(this.__ptr)
}

Bone.prototype.getNumChildBones = function() {
	Polycode.Bone_getNumChildBones(this.__ptr)
}

Bone.prototype.getChildBone = function(index) {
	Polycode.Bone_getChildBone(this.__ptr, index)
}

Bone.prototype.getBoneMatrix = function() {
	Polycode.Bone_getBoneMatrix(this.__ptr)
}

Bone.prototype.setBoneMatrix = function(matrix) {
	Polycode.Bone_setBoneMatrix(this.__ptr, matrix)
}

Bone.prototype.getRestMatrix = function() {
	Polycode.Bone_getRestMatrix(this.__ptr)
}

Bone.prototype.getFullRestMatrix = function() {
	Polycode.Bone_getFullRestMatrix(this.__ptr)
}

Bone.prototype.getParentRestMatrix = function() {
	Polycode.Bone_getParentRestMatrix(this.__ptr)
}

Bone.prototype.getFinalMatrix = function() {
	Polycode.Bone_getFinalMatrix(this.__ptr)
}

Bone.prototype.setRestMatrix = function(matrix) {
	Polycode.Bone_setRestMatrix(this.__ptr, matrix)
}

Bone.prototype.setBaseMatrix = function(matrix) {
	Polycode.Bone_setBaseMatrix(this.__ptr, matrix)
}

Bone.prototype.getBaseMatrix = function() {
	Polycode.Bone_getBaseMatrix(this.__ptr)
}

Bone.prototype.getFullBaseMatrix = function() {
	Polycode.Bone_getFullBaseMatrix(this.__ptr)
}

Bone.prototype.rebuildFinalMatrix = function() {
	Polycode.Bone_rebuildFinalMatrix(this.__ptr)
}

Bone.prototype.buildFinalMatrix = function() {
	Polycode.Bone_buildFinalMatrix(this.__ptr)
}

Bone.prototype.intializeBone = function(basePosition,baseScale,baseRotation,restPosition,restScale,restRotation) {
	Polycode.Bone_intializeBone(this.__ptr, basePosition,baseScale,baseRotation,restPosition,restScale,restRotation)
}
