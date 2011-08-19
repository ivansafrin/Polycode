require "Polycode/Event"

class "PhysicsScreenEvent" (Event)



EVENT_NEW_SHAPE_COLLISION = 0
EVENT_END_SHAPE_COLLISION = 1
EVENT_SOLVE_SHAPE_COLLISION = 3
function PhysicsScreenEvent:__index__(name)
	if name == "localCollisionNormal" then
		retVal = Physics2D.PhysicsScreenEvent_get_localCollisionNormal(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "worldCollisionNormal" then
		retVal = Physics2D.PhysicsScreenEvent_get_worldCollisionNormal(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "localCollisionPoint" then
		retVal = Physics2D.PhysicsScreenEvent_get_localCollisionPoint(self.__ptr)
		if Polycore.__ptr_lookup[retVal] ~= nil then
			return Polycore.__ptr_lookup[retVal]
		else
			Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
			Polycore.__ptr_lookup[retVal].__ptr = retVal
			return Polycore.__ptr_lookup[retVal]
		end
	elseif name == "impactStrength" then
		return Physics2D.PhysicsScreenEvent_get_impactStrength(self.__ptr)
	elseif name == "frictionStrength" then
		return Physics2D.PhysicsScreenEvent_get_frictionStrength(self.__ptr)
	end
end


function PhysicsScreenEvent:__set_callback(name,value)
	if name == "impactStrength" then
		Physics2D.PhysicsScreenEvent_set_impactStrength(self.__ptr, value)
		return true
	elseif name == "frictionStrength" then
		Physics2D.PhysicsScreenEvent_set_frictionStrength(self.__ptr, value)
		return true
	end
	return false
end


function PhysicsScreenEvent:PhysicsScreenEvent(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Event" then
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
		self.__ptr = Physics2D.PhysicsScreenEvent(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsScreenEvent:getFirstEntity()
	local retVal =  Physics2D.PhysicsScreenEvent_getFirstEntity(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreenEvent:getSecondEntity()
	local retVal =  Physics2D.PhysicsScreenEvent_getSecondEntity(self.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end



function PhysicsScreenEvent:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics2D.delete_PhysicsScreenEvent(self.__ptr)
end
