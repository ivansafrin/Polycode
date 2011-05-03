class "QuaternionCurve"







function QuaternionCurve:QuaternionCurve(...)
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycore.QuaternionCurve(unpack(arg))
	end
end

function QuaternionCurve:interpolate(t, useShortestPath)
	local retVal = Polycore.QuaternionCurve_interpolate(self.__ptr, t, useShortestPath)
	if Polycore.__ptr_lookup[retVal] ~= nil then
		return Polycore.__ptr_lookup[retVal]
	else
		Polycore.__ptr_lookup[retVal] = Quaternion("__skip_ptr__")
		Polycore.__ptr_lookup[retVal].__ptr = retVal
		return Polycore.__ptr_lookup[retVal]
	end
end

function QuaternionCurve:generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve)
	local retVal = Polycore.QuaternionCurve_generatePointsFromCurves(self.__ptr, wCurve.__ptr, xCurve.__ptr, yCurve.__ptr, zCurve.__ptr)
end

function QuaternionCurve:recalcTangents()
	local retVal =  Polycore.QuaternionCurve_recalcTangents(self.__ptr)
end

