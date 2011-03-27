/*
 *  PolyColor.h
 *  Poly
 *
 *  Created by Ivan Safrin on 3/16/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package BasicTypes

#pragma once
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <stdlib.h>
 
namespace Polycode {

	class _PolyExport Color {
		public:

			Color();
			Color(int r,int g, int b, int a);		
			Color(Number r,Number g, Number b, Number a);
			Color(Color *color);
			Color(unsigned int hex);
		
			~Color();
			
			inline Color operator * ( const Color& v2)  {
				Number nr = r * v2.r;
				Number ng = g * v2.g;
				Number nb = b * v2.b;
				Number na = a * v2.a;				
				return Color(nr, ng, nb, na);
			}			
			
			void setColorHex(unsigned int hex);
			void setColorHexRGB(unsigned int hex);
		
			void setColorHSV(Number h, Number s, Number v);
			void setColorRGBA(int r, int g, int b, int a);
			void setColorRGB(int r, int g, int b);
			void setColor(Number r, Number g, Number b, Number a);
			void setColor(Color *color);
			void Random();
		
			Number getBrightness();
			
			unsigned int getUint();
			
			Number r;
			Number g;
			Number b;
			Number a;
		private:
	
	};

}