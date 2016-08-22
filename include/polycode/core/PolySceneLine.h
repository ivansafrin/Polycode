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
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolySceneMesh.h"
#include "polycode/core/PolyBezierCurve.h"
#include "polycode/core/PolyMesh.h"

namespace Polycode {

	/**
	 * BezierCurve scene rendering/placement class. You can use this class to place a bezier curve in scene space for use as animation tracks or rendering.
	 */
	class _PolyExport SceneCurve : public SceneMesh {
		public:
		
			/*
			 * Create empty scene curve.
			 */
			SceneCurve();
		
			/*
			 * Create scene curve with an existing curve.
			 * @param curve Existing curve to use.
			 */
			SceneCurve(BezierCurve *curve);

			/*
			 * Create scene curve with an existing curve.
			 * @param curve Existing curve to use.
			 */
			static SceneCurve *SceneCurveWithCurve(BezierCurve *curve);
		
			/*
			 * Return a point along the curve in world space.
			 * @param t Number value from 0.0 to 1.0 along the curve
			 * @return A Vector3 point along the curve in world space.
			 */
			Vector3 getWorldPointAt(Number t);

		
			virtual ~SceneCurve();
			void Render(GPUDrawBuffer *buffer);
		
		
			virtual Entity *Clone(bool deepClone, bool ignoreEditorOnly) const;
			virtual void applyClone(Entity *clone, bool deepClone, bool ignoreEditorOnly) const;
 
			/*
			 * Return the actual bezier curve class.
			 * @return The bezier curve used in this scene curve.
			 */
			BezierCurve *getCurve();
		
			/*
			 * If set to true, renders the curve on every frame (defaults to true).
			 */
			bool renderCurve;
		
			/*
			 * Number of vertices to use in rendering the curve.
			 */
			int curveResolution;
		
		protected:
		
			BezierCurve *curve;
	};
	
	/**
	* 3D line class. Can connect two SceneEntity classes with a line.
	*/ 
	class _PolyExport SceneLine : public SceneMesh {
		public:
		
			/**
			* Constructs the line with two taraget positions.
			* @param start Starting position.
			* @param end Ending position.
			*/			
			SceneLine(const Vector3 &startp, const Vector3 &endp);

			
			virtual ~SceneLine();
			
			void setStart(Vector3 startp);
			void setEnd(Vector3 endp);
			
			void Update();
				
			
		protected:		
		
			void initLine();		
			
			Vector3 start;
			Vector3 end;			

	};

}