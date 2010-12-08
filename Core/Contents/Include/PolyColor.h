/*
 *  PolyColor.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <stdlib.h>
 
namespace Polycode {

	class _PolyExport Color {
		public:

			Color();
			Color(int r,int g, int b, int a);		
			Color(float r,float g, float b, float a);
			Color(Color *color);
			Color(unsigned int hex);
		
			~Color();
			
			inline Color operator * ( const Color& v2)  {
				float nr = r * v2.r;
				float ng = g * v2.g;
				float nb = b * v2.b;
				float na = a * v2.a;				
				return Color(nr, ng, nb, na);
			}			
			
			void setColorHex(unsigned int hex);
			void setColorHSV(float h, float s, float v);
			void setColorRGBA(int r, int g, int b, int a);
			void setColorRGB(int r, int g, int b);
			void setColor(float r, float g, float b, float a);
			void setColor(Color *color);
			void Random();
		
			float getBrightness();
			
			unsigned int getUint();
			
			float r;
			float g;
			float b;
			float a;
		private:
	
	};

}