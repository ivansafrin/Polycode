class "Ray"



function Ray:__getvar(name)
	if name == "origin" then
		local retVal = Polycore.Ray_get_origin(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "direction" then
		local retVal = Polycore.Ray_get_direction(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	elseif name == "inv_direction" then
		local retVal = Polycore.Ray_get_inv_direction(self.__ptr)
		if retVal == nil then return nil end
		local __c = _G["Vector3"]("__skip_ptr__")
		__c.__ptr = retVal
		return __c
	end
end


function Ray:__setvar(name,value)
	if name == "origin" then
		Polycore.Ray_set_origin(self.__ptr, value.__ptr)
		return true
	elseif name == "direction" then
		Polycore.Ray_set_direction(self.__ptr, value.__ptr)
		return true
	elseif name == "inv_direction" then
		Polycore.Ray_set_inv_direction(self.__ptr, value.__ptr)
		return true
	end
	return false
end


function Ray:Ray(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.Ray(unpack(arg))
	end
end

function Ray:boxIntersect(box, transformMatrix, near, far)
	local retVal = Polycore.Ray_boxIntersect(self.__ptr, box.__ptr, transformMatrix.__ptr, near, far)
	return retVal
end

function Ray:planeIntersectPoint(planeNormal, planeDistance)
	local retVal = Polycore.Ray_planeIntersectPoint(self.__ptr, planeNormal.__ptr, planeDistance)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Ray:tranformByMatrix(matrix)
	local retVal = Polycore.Ray_tranformByMatrix(self.__ptr, matrix.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Ray"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Ray:closestPointOnRay(point)
	local retVal = Polycore.Ray_closestPointOnRay(self.__ptr, point.__ptr)
	if retVal == nil then return nil end
	local __c = _G["Vector3"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function Ray:closestPointsBetween(ray2, point1, point2)
	local retVal = Polycore.Ray_closestPointsBetween(self.__ptr, ray2.__ptr, point1.__ptr, point2.__ptr)
	return retVal
end

function Ray:polygonIntersect(v1, v2, v3)
	local retVal = Polycore.Ray_polygonIntersect(self.__ptr, v1.__ptr, v2.__ptr, v3.__ptr)
	return retVal
end

function Ray:__delete()
	if self then Polycore.delete_Ray(self.__ptr) end
end
