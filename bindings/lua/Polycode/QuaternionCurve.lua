class "QuaternionCurve"


function QuaternionCurve:QuaternionCurve(...)
	local arg = {...}
	for k,v in pairs(arg) do
		if type(v) == "table" then
			if v.__ptr ~= nil then
				arg[k] = v.__ptr
			end
		end
	end
	if self.__ptr == nil and arg[1] ~= "__skip_ptr__" then
		self.__ptr = Polycode.QuaternionCurve(unpack(arg))
	end
end

function QuaternionCurve:interpolate(t, useShortestPath)
	local retVal = Polycode.QuaternionCurve_interpolate(self.__ptr, t, useShortestPath)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function QuaternionCurve:generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve)
	local retVal = Polycode.QuaternionCurve_generatePointsFromCurves(self.__ptr, wCurve.__ptr, xCurve.__ptr, yCurve.__ptr, zCurve.__ptr)
end

function QuaternionCurve:__delete()
	if self then Polycode.delete_QuaternionCurve(self.__ptr) end
end
