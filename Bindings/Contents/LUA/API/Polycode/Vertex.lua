require "Polycode/Vector3"

class "Vertex" (Vector3)



function Vertex:__index__(name)
	if name == "restNormal" then
		retVal = Polycore.Vertex_get_restNormal(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "restPosition" then
		retVal = Polycore.Vertex_get_restPosition(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "normal" then
		retVal = Polycore.Vertex_get_normal(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "tangent" then
		retVal = Polycore.Vertex_get_tangent(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "vertexColor" then
		retVal = Polycore.Vertex_get_vertexColor(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Color("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "texCoord" then
		retVal = Polycore.Vertex_get_texCoord(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "useVertexColor" then
		return Polycore.Vertex_get_useVertexColor(self.__ptr)
	end
end


function Vertex:__set_callback(name,value)
	if name == "useVertexColor" then
		Polycore.Vertex_set_useVertexColor(self.__ptr, value)
		return true
	end
	return false
end


function Vertex:Vertex(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Vector3" then
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
		self.__ptr = Polycore.Vertex(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function Vertex:addBoneAssignment(boneID, boneWeight)
	local retVal = Polycore.Vertex_addBoneAssignment(self.__ptr, boneID, boneWeight)
end

function Vertex:getNumBoneAssignments()
	local retVal =  Polycore.Vertex_getNumBoneAssignments(self.__ptr)
	return retVal
end

function Vertex:getBoneAssignment(index)
	local retVal = Polycore.Vertex_getBoneAssignment(self.__ptr, index)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = BoneAssignment("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Vertex:normalizeWeights()
	local retVal =  Polycore.Vertex_normalizeWeights(self.__ptr)
end

function Vertex:getTexCoord()
	local retVal =  Polycore.Vertex_getTexCoord(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function Vertex:setTexCoord(u, v)
	local retVal = Polycore.Vertex_setTexCoord(self.__ptr, u, v)
end

function Vertex:setNormal(x, y, z)
	local retVal = Polycore.Vertex_setNormal(self.__ptr, x, y, z)
end



function Vertex:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Polycore.delete_Vertex(self.__ptr)
end
