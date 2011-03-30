class "QuaternionCurve"

function QuaternionCurve:QuaternionCurve(wCurve, xCurve, yCurve, zCurve)
	if self.__ptr == nil then
		self.__ptr = Polycore.QuaternionCurve(wCurve, xCurve, yCurve, zCurve)
	end
end

function QuaternionCurve:interpolate(t, useShortestPath)
	return Polycore.QuaternionCurve_interpolate(self.__ptr, t, useShortestPath)
end

function QuaternionCurve:generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve)
	return Polycore.QuaternionCurve_generatePointsFromCurves(self.__ptr, wCurve.__ptr, xCurve.__ptr, yCurve.__ptr, zCurve.__ptr)
end

function QuaternionCurve:recalcTangents()
	return Polycore.QuaternionCurve_recalcTangents(self.__ptr)
end

