/*
 *  PolyVector2.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/14/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Math
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"

namespace Polycode {

	class _PolyExport Vector2 {
		public:
		
			Vector2();
			Vector2(Number x, Number y);
			virtual ~Vector2();
		
			inline bool operator == ( const Vector2& v2)  {
				return (v2.x == x && v2.y == y);
			}		

			inline bool operator != ( const Vector2& v2)  {
				return (v2.x != x || v2.y != y);
			}				
		
			Number x;
			Number y;			
			
		private:

	};
}