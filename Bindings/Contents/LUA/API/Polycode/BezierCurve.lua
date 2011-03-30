class "BezierCurve"

function BezierCurve:BezierCurve()
	if self.__ptr == nil then
		self.__ptr = Polycore.BezierCurve()
	end
end

function BezierCurve:getControlPoint(index)
	return Polycore.BezierCurve_getControlPoint(self.__ptr, index)
end

function BezierCurve:getNumControlPoints()
	return Polycore.BezierCurve_getNumControlPoints(self.__ptr)
end

function BezierCurve:addControlPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z)
	return Polycore.BezierCurve_addControlPoint(self.__ptr, p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z)
end

function BezierCurve:addControlPoint3dWithHandles(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z)
	return Polycore.BezierCurve_addControlPoint3dWithHandles(self.__ptr, p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z)
end

function BezierCurve:addControlPoint3d(x, y, z)
	return Polycore.BezierCurve_addControlPoint3d(self.__ptr, x, y, z)
end

function BezierCurve:addControlPoint2dWithHandles(p1x, p1y, p2x, p2y, p3x, p3y)
	return Polycore.BezierCurve_addControlPoint2dWithHandles(self.__ptr, p1x, p1y, p2x, p2y, p3x, p3y)
end

function BezierCurve:addControlPoint2d(x, y)
	return Polycore.BezierCurve_addControlPoint2d(self.__ptr, x, y)
end

function BezierCurve:getHeightAt(a)
	return Polycore.BezierCurve_getHeightAt(self.__ptr, a)
end

function BezierCurve:getPointAt(a)
	return Polycore.BezierCurve_getPointAt(self.__ptr, a)
end

function BezierCurve:getPointBetween(a, bp1, bp2)
	return Polycore.BezierCurve_getPointBetween(self.__ptr, a, bp1.__ptr, bp2.__ptr)
end

function BezierCurve:rebuildBuffers()
	return Polycore.BezierCurve_rebuildBuffers(self.__ptr)
end

