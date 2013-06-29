/*
 Copyright (C) 2011 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */


#pragma once 

#include "PolyGlobals.h"
#include "PolyVector3.h"
#include <vector>


#define BUFFER_CACHE_PRECISION 100

namespace Polycode {

/** 
* A curve point defined by 3 positions.
* @see BezierCurve
*/
class _PolyExport BezierPoint : public PolyBase {
	public:

	/**
	* Constructor
	* @param p1x X position of the first handle point.
	* @param p1y Y position of the first handle point.
	* @param p1z Z position of the first handle point.
	* @param p2x X position of the middle point.
	* @param p2y Y position of the middle point.
	* @param p2z Z position of the middle point.
	* @param p3x X position of the second handle point.
	* @param p3y Y position of the second handle point.
	* @param p3z Z position of the second handle point.
	*/
	BezierPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);

	/**
	* First handle position.
	*/
	Vector3 p1;

	/**
	* Middle position.
	*/		
	Vector3 p2;

	/**
	* Second handle position.
	*/		
	Vector3 p3;
};

/**
* A Bezier curve. This class can be used to draw smooth curves or move things smoothly on curves. It's also used internally for skeletal animation. The curves are 3-dimensional, but convenience methods are added for 2d curves and there is a caching mechanism for 2d height data to speed up bezier curve usage in animation.

	A bezier curve consists of control points, each having 3 points: one middle point and two 'handles'. The middle point is the actual position of the control point and the two side points serve as vectors defining how the curve curves towards the next control points.

*/
class _PolyExport BezierCurve : public PolyBase {
	public:
		/** 
		* Default constructor.
		*/
		BezierCurve();
		virtual ~BezierCurve();

		/**
		* Returns a control point by index.
		* @param index Index of the control point to return.
		* @return Control point at specified index.
		*/
		BezierPoint *getControlPoint(unsigned int index);

		/**
		* Returns the total number of control points in the curve.
		* @return Total number of control points.
		*/
		unsigned int getNumControlPoints();


		/**
		* @see addControlPoint3dWithHandles()
		*/
		void addControlPoint(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);

		/**
		* Adds a new control point to the curve after the last point.
		* @param p1x X position of the first handle point.
		* @param p1y Y position of the first handle point.
		* @param p1z Z position of the first handle point.
		* @param p2x X position of the middle point.
		* @param p2y Y position of the middle point.
		* @param p2z Z position of the middle point.
		* @param p3x X position of the second handle point.
		* @param p3y Y position of the second handle point.
		* @param p3z Z position of the second handle point.
		*/
		void addControlPoint3dWithHandles(Number p1x, Number p1y, Number p1z, Number p2x, Number p2y, Number p2z, Number p3x, Number p3y, Number p3z);

		/**
		* Adds a new control point to the curve with handles in the same place as the middle points.
		* @param x X position of the point and both handles.
		* @param y Y position of the point and both handles.
		* @param z Z position of the point and both handles.
		*/
		void addControlPoint3d(Number x, Number y, Number z);

		/**
		* Adds a new control point to the curve after the last point using 2d coordinates. The Z value of the coordinates is set to 0.
		* @param p1x X position of the first handle point.
		* @param p1y Y position of the first handle point.
		* @param p2x X position of the middle point.
		* @param p2y Y position of the middle point.
		* @param p3x X position of the second handle point.
		* @param p3y Y position of the second handle point.
		*/
		void addControlPoint2dWithHandles(Number p1x, Number p1y, Number p2x, Number p2y, Number p3x, Number p3y);

		/**
		* Adds a new control point to the curve with handles in the same place as the middle points using 2d coordinates.The Z value of the coordinates is set to 0.
		* @param x X position of the point and both handles.
		* @param y Y position of the point and both handles.
		*/
		void addControlPoint2d(Number x, Number y);

		/**
		* Returns the height of the curve at a specified point on the curve. Heights are cached into a buffer with a finite cache precision to speed up the curve usage in animation. If you need to quickly get 2D height out of a curve and you don't care about total precision, use this method.
		* @param a Normalized (0-1) position along the curve.
		* @return Height value at specified position.
		*/
		Number getHeightAt(Number a);

		/**
		* Returns the 3d point of the curve at a specified point on the curve.
		* @param a Normalized (0-1) position along the curve.
		* @return 3d point at specified position.
		*/
		Vector3 getPointAt(Number a);

		/**
		* Returns the 3d point of the curve at a specified point between two points.
		* @param a Normalized (0-1) position between two points
		* @return 3d point at specified position.
		*/
		Vector3 getPointBetween(Number a, BezierPoint *bp1, BezierPoint *bp2);

		void clearControlPoints();

		/** 
		* Rebuilds the height cache buffers for 2d height curves.
		*/
		void rebuildBuffers();

		/**
		* Removes (and deletes!) a gives point by pointer
		*/
		void removePoint(BezierPoint *point);

		Number heightBuffer[BUFFER_CACHE_PRECISION];

		BezierPoint *insertPoint;

		std::vector<BezierPoint*> controlPoints;
		std::vector<Number> distances;

		void recalculateDistances();

	protected:

		bool buffersDirty;

};

}
