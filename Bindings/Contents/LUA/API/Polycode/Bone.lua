require "Polycode/SceneEntity"

class "Bone" (SceneEntity)

function Bone:Bone(boneName)
	if self.__ptr == nil then
		self.__ptr = Polycore.Bone(boneName)
	end
end

function Bone:enableBoneLabel(labelFont, size, scale, labelColor)
	return Polycore.Bone_enableBoneLabel(self.__ptr, labelFont, size, scale, labelColor.__ptr)
end

function Bone:getName()
	return Polycore.Bone_getName(self.__ptr)
end

function Bone:Render()
	return Polycore.Bone_Render(self.__ptr)
end

function Bone:setParentBone(bone)
	return Polycore.Bone_setParentBone(self.__ptr, bone.__ptr)
end

function Bone:addChildBone(bone)
	return Polycore.Bone_addChildBone(self.__ptr, bone.__ptr)
end

function Bone:getParentBone()
	return Polycore.Bone_getParentBone(self.__ptr)
end

function Bone:getNumChildBones()
	return Polycore.Bone_getNumChildBones(self.__ptr)
end

function Bone:getChildBone(index)
	return Polycore.Bone_getChildBone(self.__ptr, index)
end

function Bone:getBoneMatrix()
	return Polycore.Bone_getBoneMatrix(self.__ptr)
end

function Bone:setBoneMatrix(matrix)
	return Polycore.Bone_setBoneMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getRestMatrix()
	return Polycore.Bone_getRestMatrix(self.__ptr)
end

function Bone:getFullRestMatrix()
	return Polycore.Bone_getFullRestMatrix(self.__ptr)
end

function Bone:getParentRestMatrix()
	return Polycore.Bone_getParentRestMatrix(self.__ptr)
end

function Bone:getFinalMatrix()
	return Polycore.Bone_getFinalMatrix(self.__ptr)
end

function Bone:setRestMatrix(matrix)
	return Polycore.Bone_setRestMatrix(self.__ptr, matrix.__ptr)
end

function Bone:setBaseMatrix(matrix)
	return Polycore.Bone_setBaseMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getBaseMatrix()
	return Polycore.Bone_getBaseMatrix(self.__ptr)
end

function Bone:getFullBaseMatrix()
	return Polycore.Bone_getFullBaseMatrix(self.__ptr)
end

