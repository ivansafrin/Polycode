require('Polycode/Entity')

function Skeleton(fileName) {
	if(arguments[0] != "__skip_ptr__") {
		this.__ptr = Polycode.Skeleton(fileName)
	}
}


Skeleton.prototype = Object.create(Entity.prototype)

Duktape.fin(Skeleton.prototype, function (x) {
	if (x === Skeleton.prototype) {
		return;
	}
	Polycode.Skeleton__delete(x.__ptr)
})

Skeleton.prototype.loadSkeleton = function(fileName) {
	Polycode.Skeleton_loadSkeleton(this.__ptr, fileName)
}

Skeleton.prototype.playAnimationByName = function(animName,weight,once,restartIfPlaying) {
	Polycode.Skeleton_playAnimationByName(this.__ptr, animName, weight, once, restartIfPlaying)
}

Skeleton.prototype.setBaseAnimationByName = function(animName) {
	Polycode.Skeleton_setBaseAnimationByName(this.__ptr, animName)
}

Skeleton.prototype.stopAllAnimations = function() {
	Polycode.Skeleton_stopAllAnimations(this.__ptr)
}

Skeleton.prototype.addAnimation = function(name,fileName) {
	Polycode.Skeleton_addAnimation(this.__ptr, name, fileName)
}

Skeleton.prototype.stopAnimationByName = function(name) {
	Polycode.Skeleton_stopAnimationByName(this.__ptr, name)
}

Skeleton.prototype.Update = function() {
	Polycode.Skeleton_Update(this.__ptr)
}

Skeleton.prototype.getBoneByName = function(name) {
	var retVal = new Bone("__skip_ptr__")
	retVal.__ptr = Polycode.Skeleton_getBoneByName(this.__ptr, name)
	return retVal
}

Skeleton.prototype.bonesVisible = function(val) {
	Polycode.Skeleton_bonesVisible(this.__ptr, val)
}

Skeleton.prototype.getNumBones = function() {
	return Polycode.Skeleton_getNumBones(this.__ptr)
}

Skeleton.prototype.getBone = function(index) {
	var retVal = new Bone("__skip_ptr__")
	retVal.__ptr = Polycode.Skeleton_getBone(this.__ptr, index)
	return retVal
}

Skeleton.prototype.addBone = function(bone) {
	Polycode.Skeleton_addBone(this.__ptr, bone)
}

Skeleton.prototype.removeBone = function(bone) {
	Polycode.Skeleton_removeBone(this.__ptr, bone)
}

Skeleton.prototype.getBoneIndexByBone = function(bone) {
	return Polycode.Skeleton_getBoneIndexByBone(this.__ptr, bone)
}
