require "Polycode/Entity"

class "Bone" (Entity)


function Bone:__getvar(name)
	if name == "parentBoneId" then
		return Polycode.Bone_get_parentBoneId(self.__ptr)
	elseif name == "boneMatrix" then
		local retVal = Polycode.Bone_get_boneMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "restMatrix" then
		local retVal = Polycode.Bone_get_restMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "baseMatrix" then
		local retVal = Polycode.Bone_get_baseMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "finalMatrix" then
		local retVal = Polycode.Bone_get_finalMatrix(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Matrix4"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "baseRotation" then
		local retVal = Polycode.Bone_get_baseRotation(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Quaternion"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "baseScale" then
		local retVal = Polycode.Bone_get_baseScale(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "basePosition" then
		local retVal = Polycode.Bone_get_basePosition(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "disableAnimation" then
		return Polycode.Bone_get_disableAnimation(self.__ptr)
	end
	if Entity["__getvar"] ~= nil then
		return Entity.__getvar(self, name)
	end
end

function Bone:__setvar(name,value)
	if name == "parentBoneId" then
		Polycode.Bone_set_parentBoneId(self.__ptr, value)
		return true
	elseif name == "boneMatrix" then
		Polycode.Bone_set_boneMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "restMatrix" then
		Polycode.Bone_set_restMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "baseMatrix" then
		Polycode.Bone_set_baseMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "finalMatrix" then
		Polycode.Bone_set_finalMatrix(self.__ptr, value.__ptr)
		return true
	elseif name == "baseRotation" then
		Polycode.Bone_set_baseRotation(self.__ptr, value.__ptr)
		return true
	elseif name == "baseScale" then
		Polycode.Bone_set_baseScale(self.__ptr, value.__ptr)
		return true
	elseif name == "basePosition" then
		Polycode.Bone_set_basePosition(self.__ptr, value.__ptr)
		return true
	elseif name == "disableAnimation" then
		Polycode.Bone_set_disableAnimation(self.__ptr, value)
		return true
	end
	if Entity["__setvar"] ~= nil then
		return Entity.__setvar(self, name, value)
	else
		return false
	end
end
function Bone:Bone(...)
	local arg = {...}
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1].__classname == "Entity" then
			self.__ptr = arg[1].__ptr
			return
		end
	end
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.Bone(unpack(arg))
	end
end

function Bone:getName()
	local retVal =  Polycode.Bone_getName(self.__ptr)
	return retVal
end

function Bone:setParentBone(bone)
	local retVal = Polycode.Bone_setParentBone(self.__ptr, bone.__ptr)
end

function Bone:addChildBone(bone)
	local retVal = Polycode.Bone_addChildBone(self.__ptr, bone.__ptr)
end

function Bone:getParentBone()
	local retVal =  Polycode.Bone_getParentBone(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Bone"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getNumChildBones()
	local retVal =  Polycode.Bone_getNumChildBones(self.__ptr)
	return retVal
end

function Bone:getChildBone(index)
	local retVal = Polycode.Bone_getChildBone(self.__ptr, index)
	if retVal == nil then return nil end
	local __c = _G["Bone"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getBoneMatrix()
	local retVal =  Polycode.Bone_getBoneMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:setBoneMatrix(matrix)
	local retVal = Polycode.Bone_setBoneMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getRestMatrix()
	local retVal =  Polycode.Bone_getRestMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getFullRestMatrix()
	local retVal =  Polycode.Bone_getFullRestMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getParentRestMatrix()
	local retVal =  Polycode.Bone_getParentRestMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getFinalMatrix()
	local retVal =  Polycode.Bone_getFinalMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:setRestMatrix(matrix)
	local retVal = Polycode.Bone_setRestMatrix(self.__ptr, matrix.__ptr)
end

function Bone:setBaseMatrix(matrix)
	local retVal = Polycode.Bone_setBaseMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getBaseMatrix()
	local retVal =  Polycode.Bone_getBaseMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:getFullBaseMatrix()
	local retVal =  Polycode.Bone_getFullBaseMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:rebuildFinalMatrix()
	local retVal =  Polycode.Bone_rebuildFinalMatrix(self.__ptr)
end

function Bone:buildFinalMatrix()
	local retVal =  Polycode.Bone_buildFinalMatrix(self.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Matrix4"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Bone:intializeBone(basePosition, baseScale, baseRotation, restPosition, restScale, restRotation)
	local retVal = Polycode.Bone_intializeBone(self.__ptr, basePosition.__ptr, baseScale.__ptr, baseRotation.__ptr, restPosition.__ptr, restScale.__ptr, restRotation.__ptr)
end

function Bone:__delete()
	if self then Polycode.delete_Bone(self.__ptr) end
end
