class "PhysicsScreenEntity"



ENTITY_RECT = 1
ENTITY_CIRCLE = 2
ENTITY_STATICRECT = 3
function PhysicsScreenEntity:__index__(name)
	if name == "collisionOnly" then
		return Physics2D.PhysicsScreenEntity_get_collisionOnly(self.__ptr)
	end
end


function PhysicsScreenEntity:__set_callback(name,value)
	if name == "collisionOnly" then
		Physics2D.PhysicsScreenEntity_set_collisionOnly(self.__ptr, value)
		return true
	end
	return false
end


function PhysicsScreenEntity:PhysicsScreenEntity(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Physics2D.PhysicsScreenEntity(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsScreenEntity:getScreenEntity()
	local retVal =  Physics2D.PhysicsScreenEntity_getScreenEntity(self.__ptr)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreenEntity:applyTorque(torque)
	local retVal = Physics2D.PhysicsScreenEntity_applyTorque(self.__ptr, torque)
end

function PhysicsScreenEntity:applyForce(force)
	local retVal = Physics2D.PhysicsScreenEntity_applyForce(self.__ptr, force.__ptr)
end

function PhysicsScreenEntity:setTransform(pos, angle)
	local retVal = Physics2D.PhysicsScreenEntity_setTransform(self.__ptr, pos.__ptr, angle)
end

function PhysicsScreenEntity:Update()
	local retVal =  Physics2D.PhysicsScreenEntity_Update(self.__ptr)
end



function PhysicsScreenEntity:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics2D.delete_PhysicsScreenEntity(self.__ptr)
end
