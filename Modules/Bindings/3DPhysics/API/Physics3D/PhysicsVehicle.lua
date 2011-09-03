require "Physics3D/PhysicsSceneEntity"

class "PhysicsVehicle" (PhysicsSceneEntity)



function PhysicsVehicle:__index__(name)
	if name == "tuning" then
		retVal = Physics3D.PhysicsVehicle_get_tuning(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = btRaycastVehicle::btVehicleTuning("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	end
end


function PhysicsVehicle:__set_callback(name,value)
	return false
end


function PhysicsVehicle:PhysicsVehicle(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "PhysicsSceneEntity" then
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
		self.__ptr = Physics3D.PhysicsVehicle(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsVehicle:addWheel(entity, connection, direction, axle, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence)
	local retVal = Physics3D.PhysicsVehicle_addWheel(self.__ptr, entity.__ptr, connection.__ptr, direction.__ptr, axle.__ptr, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence)
end

function PhysicsVehicle:applyEngineForce(force, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_applyEngineForce(self.__ptr, force, wheelIndex)
end

function PhysicsVehicle:setSteeringValue(value, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_setSteeringValue(self.__ptr, value, wheelIndex)
end

function PhysicsVehicle:setBrake(value, wheelIndex)
	local retVal = Physics3D.PhysicsVehicle_setBrake(self.__ptr, value, wheelIndex)
end

function PhysicsVehicle:warpVehicle(position)
	local retVal = Physics3D.PhysicsVehicle_warpVehicle(self.__ptr, position.__ptr)
end

function PhysicsVehicle:Update()
	local retVal =  Physics3D.PhysicsVehicle_Update(self.__ptr)
end



function PhysicsVehicle:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics3D.delete_PhysicsVehicle(self.__ptr)
end
