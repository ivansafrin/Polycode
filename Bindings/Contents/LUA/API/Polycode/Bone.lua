require "Polycode/SceneEntity"

class "Bone" (SceneEntity)



function Bone:__index__(name)
	if name == "parentBoneId" then
		return Polycore.Bone_get_parentBoneId(self.__ptr)
	elseif name == "boneMatrix" then
		retVal = Polycore.Bone_get_boneMatrix(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "restMatrix" then
		retVal = Polycore.Bone_get_restMatrix(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "baseMatrix" then
		retVal = Polycore.Bone_get_baseMatrix(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function Bone:__set_callback(name,value)
	if name == "parentBoneId" then
		Polycore.Bone_set_parentBoneId(self.__ptr, value)
		return true
	end
	return false
end


function Bone:Bone(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "SceneEntity" then
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
		self.__ptr = Polycore.Bone(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Bone:enableBoneLabel(labelFont, size, scale, labelColor)
	local retVal = Polycore.Bone_enableBoneLabel(self.__ptr, labelFont, size, scale, labelColor.__ptr)
end

function Bone:getName()
	local retVal =  Polycore.Bone_getName(self.__ptr)
	return retVal
end

function Bone:Render()
	local retVal =  Polycore.Bone_Render(self.__ptr)
end

function Bone:setParentBone(bone)
	local retVal = Polycore.Bone_setParentBone(self.__ptr, bone.__ptr)
end

function Bone:addChildBone(bone)
	local retVal = Polycore.Bone_addChildBone(self.__ptr, bone.__ptr)
end

function Bone:getParentBone()
	local retVal =  Polycore.Bone_getParentBone(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Bone("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getNumChildBones()
	local retVal =  Polycore.Bone_getNumChildBones(self.__ptr)
	return retVal
end

function Bone:getChildBone(index)
	local retVal = Polycore.Bone_getChildBone(self.__ptr, index)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Bone("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getBoneMatrix()
	local retVal =  Polycore.Bone_getBoneMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:setBoneMatrix(matrix)
	local retVal = Polycore.Bone_setBoneMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getRestMatrix()
	local retVal =  Polycore.Bone_getRestMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getFullRestMatrix()
	local retVal =  Polycore.Bone_getFullRestMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getParentRestMatrix()
	local retVal =  Polycore.Bone_getParentRestMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getFinalMatrix()
	local retVal =  Polycore.Bone_getFinalMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:setRestMatrix(matrix)
	local retVal = Polycore.Bone_setRestMatrix(self.__ptr, matrix.__ptr)
end

function Bone:setBaseMatrix(matrix)
	local retVal = Polycore.Bone_setBaseMatrix(self.__ptr, matrix.__ptr)
end

function Bone:getBaseMatrix()
	local retVal =  Polycore.Bone_getBaseMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Bone:getFullBaseMatrix()
	local retVal =  Polycore.Bone_getFullBaseMatrix(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Matrix4("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function Bone:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Bone(self.__ptr)
end
