class "QuaternionCurve"


function QuaternionCurve:interpolate(t, useShortestPath)
	local retVal = Polycode.QuaternionCurve_interpolate(self.__ptr, t, useShortestPath)
	if retVal == nil then return nil end
	local __c = _G["Quaternion"]("__skip_ptr__")
	__c.__ptr = retVal
	return __c
end

function QuaternionCurve:__delete()
	if self then Polycode.delete_QuaternionCurve(self.__ptr) end
end
