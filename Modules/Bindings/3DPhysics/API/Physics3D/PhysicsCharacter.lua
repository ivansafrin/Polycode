require "Physics3D/PhysicsSceneEntity"

class "PhysicsCharacter" (PhysicsSceneEntity)







function PhysicsCharacter:PhysicsCharacter(...)
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
		self.__ptr = Physics3D.PhysicsCharacter(unpack(arg))
		Polycore.__ptr_lookup[self.__ptr] = self
	end
end

function PhysicsCharacter:setWalkDirection(direction)
	local retVal = Physics3D.PhysicsCharacter_setWalkDirection(self.__ptr, direction.__ptr)
end

function PhysicsCharacter:jump()
	local retVal =  Physics3D.PhysicsCharacter_jump(self.__ptr)
end

function PhysicsCharacter:Update()
	local retVal =  Physics3D.PhysicsCharacter_Update(self.__ptr)
end



function PhysicsCharacter:__delete()
	Polycore.__ptr_lookup[self.__ptr] = nil
	Physics3D.delete_PhysicsCharacter(self.__ptr)
end
