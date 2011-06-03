require "Polycode/Screen"

class "PhysicsScreen" (Screen)







function PhysicsScreen:PhysicsScreen(...)
	if type(arg[1]) == "table" and count(arg) == 1 then
		if ""..arg[1]:class() == "Screen" then
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
		self.__ptr = Physics2D.PhysicsScreen(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsScreen:Update()
	local retVal =  Physics2D.PhysicsScreen_Update(self.__ptr)
end

function PhysicsScreen:addPhysicsChild(newEntity, entType, isStatic, friction, density, restitution, isSensor, fixedRotation)
	local retVal = Physics2D.PhysicsScreen_addPhysicsChild(self.__ptr, newEntity.__ptr, entType, isStatic, friction, density, restitution, isSensor, fixedRotation)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:removePhysicsChild(entityToRemove)
	local retVal = Physics2D.PhysicsScreen_removePhysicsChild(self.__ptr, entityToRemove.__ptr)
end

function PhysicsScreen:addCollisionChild(newEntity, entType)
	local retVal = Physics2D.PhysicsScreen_addCollisionChild(self.__ptr, newEntity.__ptr, entType)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:destroyJoint(joint)
	local retVal = Physics2D.PhysicsScreen_destroyJoint(self.__ptr, joint.__ptr)
end

function PhysicsScreen:createDistanceJoint(ent1, ent2, collideConnected)
	local retVal = Physics2D.PhysicsScreen_createDistanceJoint(self.__ptr, ent1.__ptr, ent2.__ptr, collideConnected)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsJoint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:createPrismaticJoint(ent1, ent2, worldAxis, ax, ay, collideConnected, lowerTranslation, upperTranslation, enableLimit, motorSpeed, motorForce, motorEnabled)
	local retVal = Physics2D.PhysicsScreen_createPrismaticJoint(self.__ptr, ent1.__ptr, ent2.__ptr, worldAxis.__ptr, ax, ay, collideConnected, lowerTranslation, upperTranslation, enableLimit, motorSpeed, motorForce, motorEnabled)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsJoint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:createRevoluteJoint(ent1, ent2, ax, ay, collideConnected, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque)
	local retVal = Physics2D.PhysicsScreen_createRevoluteJoint(self.__ptr, ent1.__ptr, ent2.__ptr, ax, ay, collideConnected, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsJoint("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:applyForce(ent, fx, fy)
	local retVal = Physics2D.PhysicsScreen_applyForce(self.__ptr, ent.__ptr, fx, fy)
end

function PhysicsScreen:applyImpulse(ent, fx, fy)
	local retVal = Physics2D.PhysicsScreen_applyImpulse(self.__ptr, ent.__ptr, fx, fy)
end

function PhysicsScreen:setGravity(newGravity)
	local retVal = Physics2D.PhysicsScreen_setGravity(self.__ptr, newGravity.__ptr)
end

function PhysicsScreen:setTransform(ent, pos, angle)
	local retVal = Physics2D.PhysicsScreen_setTransform(self.__ptr, ent.__ptr, pos.__ptr, angle)
end

function PhysicsScreen:getPhysicsEntityByShape(shape)
	local retVal = Physics2D.PhysicsScreen_getPhysicsEntityByShape(self.__ptr, shape.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:getPhysicsEntityByFixture(fixture)
	local retVal = Physics2D.PhysicsScreen_getPhysicsEntityByFixture(self.__ptr, fixture.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:setVelocity(ent, fx, fy)
	local retVal = Physics2D.PhysicsScreen_setVelocity(self.__ptr, ent.__ptr, fx, fy)
end

function PhysicsScreen:setVelocityX(ent, fx)
	local retVal = Physics2D.PhysicsScreen_setVelocityX(self.__ptr, ent.__ptr, fx)
end

function PhysicsScreen:setVelocityY(ent, fy)
	local retVal = Physics2D.PhysicsScreen_setVelocityY(self.__ptr, ent.__ptr, fy)
end

function PhysicsScreen:setSpin(ent, spin)
	local retVal = Physics2D.PhysicsScreen_setSpin(self.__ptr, ent.__ptr, spin)
end

function PhysicsScreen:getVelocity(ent)
	local retVal = Physics2D.PhysicsScreen_getVelocity(self.__ptr, ent.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Vector2("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:BeginContact(contact)
	local retVal = Physics2D.PhysicsScreen_BeginContact(self.__ptr, contact.__ptr)
end

function PhysicsScreen:EndContact(contact)
	local retVal = Physics2D.PhysicsScreen_EndContact(self.__ptr, contact.__ptr)
end

function PhysicsScreen:PostSolve(contact, impulse)
	local retVal = Physics2D.PhysicsScreen_PostSolve(self.__ptr, contact.__ptr, impulse.__ptr)
end

function PhysicsScreen:wakeUp(ent)
	local retVal = Physics2D.PhysicsScreen_wakeUp(self.__ptr, ent.__ptr)
end

function PhysicsScreen:getEntityAtPosition(x, y)
	local retVal = Physics2D.PhysicsScreen_getEntityAtPosition(self.__ptr, x, y)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = ScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:testEntityAtPosition(ent, x, y)
	local retVal = Physics2D.PhysicsScreen_testEntityAtPosition(self.__ptr, ent.__ptr, x, y)
	return retVal
end

function PhysicsScreen:Shutdown()
	local retVal =  Physics2D.PhysicsScreen_Shutdown(self.__ptr)
end

function PhysicsScreen:getPhysicsByScreenEntity(ent)
	local retVal = Physics2D.PhysicsScreen_getPhysicsByScreenEntity(self.__ptr, ent.__ptr)
	if retVal == nil then return nil end
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = PhysicsScreenEntity("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function PhysicsScreen:destroyMouseJoint(mJoint)
	local retVal = Physics2D.PhysicsScreen_destroyMouseJoint(self.__ptr, mJoint.__ptr)
end



function PhysicsScreen:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics2D.delete_PhysicsScreen(self.__ptr)
end
