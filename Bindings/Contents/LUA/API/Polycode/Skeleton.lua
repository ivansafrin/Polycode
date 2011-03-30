require "Polycode/SceneEntity"

class "Skeleton" (SceneEntity)

function Skeleton:Skeleton(fileName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Skeleton(fileName)
	end
end

function Skeleton:loadSkeleton(fileName)
	return Polycore.Skeleton_loadSkeleton(self.__ptr, fileName)
end

function Skeleton:playAnimation(animName)
	return Polycore.Skeleton_playAnimation(self.__ptr, animName)
end

function Skeleton:playAnimationByIndex(index)
	return Polycore.Skeleton_playAnimationByIndex(self.__ptr, index)
end

function Skeleton:addAnimation(name, fileName)
	return Polycore.Skeleton_addAnimation(self.__ptr, name, fileName)
end

function Skeleton:getAnimation(name)
	return Polycore.Skeleton_getAnimation(self.__ptr, name)
end

function Skeleton:Update()
	return Polycore.Skeleton_Update(self.__ptr)
end

function Skeleton:getBoneByName(name)
	return Polycore.Skeleton_getBoneByName(self.__ptr, name)
end

function Skeleton:bonesVisible(val)
	return Polycore.Skeleton_bonesVisible(self.__ptr, val)
end

function Skeleton:enableBoneLabels(labelFont, size, scale, labelColor)
	return Polycore.Skeleton_enableBoneLabels(self.__ptr, labelFont, size, scale, labelColor.__ptr)
end

function Skeleton:getNumBones()
	return Polycore.Skeleton_getNumBones(self.__ptr)
end

function Skeleton:getBone(index)
	return Polycore.Skeleton_getBone(self.__ptr, index)
end

function Skeleton:getCurrentAnimation()
	return Polycore.Skeleton_getCurrentAnimation(self.__ptr)
end

