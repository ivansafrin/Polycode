class "CollisionSceneEntity"



SHAPE_BOX = 0
SHAPE_TERRAIN = 1
SHAPE_SPHERE = 2
SHAPE_MESH = 3
CHARACTER_CONTROLLER = 4
SHAPE_CAPSULE = 5
SHAPE_PLANE = 6
SHAPE_CONE = 7
SHAPE_CYLINDER = 8
function CollisionSceneEntity:__index__(name)
	if name == "lastPosition" then
		retVal = Physics3D.CollisionSceneEntity_get_lastPosition(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector3("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "enabled" then
		return Physics3D.CollisionSceneEntity_get_enabled(self.__ptr)
	end
end


function CollisionSceneEntity:__set_callback(name,value)
	if name == "enabled" then
		Physics3D.CollisionSceneEntity_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function CollisionSceneEntity:CollisionSceneEntity(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics3D.CollisionSceneEntity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function CollisionSceneEntity:getSceneEntity()
	local retVal =  Physics3D.CollisionSceneEntity_getSceneEntity(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CollisionSceneEntity:getType()
	local retVal =  Physics3D.CollisionSceneEntity_getType(self.__ptr)
	return retVal
end

function CollisionSceneEntity:Update()
	local retVal =  Physics3D.CollisionSceneEntity_Update(self.__ptr)
end

function CollisionSceneEntity:getConvexShape()
	local retVal =  Physics3D.CollisionSceneEntity_getConvexShape(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = btConvexShape("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function CollisionSceneEntity:createCollisionShape(entity, type)
	local retVal = Physics3D.CollisionSceneEntity_createCollisionShape(self.__ptr, entity.__ptr, type)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = btCollisionShape("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function CollisionSceneEntity:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics3D.delete_CollisionSceneEntity(self.__ptr)
end
