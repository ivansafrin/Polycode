require "Physics3D/CollisionSceneEntity"

class "PhysicsSceneEntity" (CollisionSceneEntity)



SHAPE_BOX = 0
SHAPE_TERRAIN = 1
SHAPE_SPHERE = 2
SHAPE_MESH = 3
CHARACTER_CONTROLLER = 4
SHAPE_CAPSULE = 5
SHAPE_PLANE = 6
function PhysicsSceneEntity:__index__(name)
	if name == "enabled" then
		return Physics3D.PhysicsSceneEntity_get_enabled(self.__ptr)
	end
end


function PhysicsSceneEntity:__set_callback(name,value)
	if name == "enabled" then
		Physics3D.PhysicsSceneEntity_set_enabled(self.__ptr, value)
		return true
	end
	return false
end


function PhysicsSceneEntity:PhysicsSceneEntity(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "CollisionSceneEntity" then
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
		self.__ptr = Physics3D.PhysicsSceneEntity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsSceneEntity:getSceneEntity()
	local retVal =  Physics3D.PhysicsSceneEntity_getSceneEntity(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = SceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsSceneEntity:Update()
	local retVal =  Physics3D.PhysicsSceneEntity_Update(self.__ptr)
end

function PhysicsSceneEntity:setFriction(friction)
	local retVal = Physics3D.PhysicsSceneEntity_setFriction(self.__ptr, friction)
end

function PhysicsSceneEntity:getType()
	local retVal =  Physics3D.PhysicsSceneEntity_getType(self.__ptr)
	return retVal
end



function PhysicsSceneEntity:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics3D.delete_PhysicsSceneEntity(self.__ptr)
end
