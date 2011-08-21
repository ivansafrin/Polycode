require "Physics3D/CollisionScene"

class "PhysicsScene" (CollisionScene)







function PhysicsScene:PhysicsScene(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "CollisionScene" then
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
		self.__ptr = Physics3D.PhysicsScene(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsScene:Update()
	local retVal =  Physics3D.PhysicsScene_Update(self.__ptr)
end

function PhysicsScene:removePhysicsChild(entity)
	local retVal = Physics3D.PhysicsScene_removePhysicsChild(self.__ptr, entity.__ptr)
end

function PhysicsScene:getPhysicsEntityBySceneEntity(entity)
	local retVal = Physics3D.PhysicsScene_getPhysicsEntityBySceneEntity(self.__ptr, entity.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsSceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScene:addPhysicsChild(newEntity, type, mass, friction, restitution, group)
	local retVal = Physics3D.PhysicsScene_addPhysicsChild(self.__ptr, newEntity.__ptr, type, mass, friction, restitution, group)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsSceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScene:trackPhysicsChild(newEntity, type, mass, friction, restitution, group)
	local retVal = Physics3D.PhysicsScene_trackPhysicsChild(self.__ptr, newEntity.__ptr, type, mass, friction, restitution, group)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsSceneEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScene:addCharacterChild(newEntity, mass, friction, stepSize, group)
	local retVal = Physics3D.PhysicsScene_addCharacterChild(self.__ptr, newEntity.__ptr, mass, friction, stepSize, group)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsCharacter("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScene:addVehicleChild(newEntity, mass, friction, group)
	local retVal = Physics3D.PhysicsScene_addVehicleChild(self.__ptr, newEntity.__ptr, mass, friction, group)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsVehicle("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function PhysicsScene:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics3D.delete_PhysicsScene(self.__ptr)
end
