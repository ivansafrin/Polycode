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
#include "PolyString.h"
#include "PolyLogger.h"
#include "PolyGlobals.h"
#include <stdlib.h>
 
namespace Polycode {

	/**
	* Stores and manipulates color information. Color is always RGBA in Polycode.
	*/						
	class _PolyExport Color {
		public:

			/**
			* Default constructor.
			*/						
			Color();
			
			/**
			* Create from 0-255 integer data.
			* @param r Red value 0-255.
			* @param g Green value 0-255.
			* @param b Blue value 0-255.
			* @param a Alpha value 0-255.									
			*/									
			Color(int r,int g, int b, int a);	
			
			/**
			* Create from 0-1 floating point data.
			* @param r Red value 0-1.
			* @param g Green value 0-1
			* @param b Blue value 0-1
			* @param a Alpha value 0-1									
			*/														
			Color(Number r,Number g, Number b, Number a);
			
			/**
			* Create from another color.
			* @param color The color to create from.
			*/												
			Color(const Color *color);
			
			/**
			* Create from integer color.
			* @param hex Integer color value.
			*/															
			Color(unsigned int hex);
		
			~Color();
			
			/** 
			* Multiplies the color with another color.
			*/
			inline Color operator * ( const Color& v2) const {
				Number nr = r * v2.r;
				Number ng = g * v2.g;
				Number nb = b * v2.b;
				Number na = a * v2.a;				
				return Color(nr, ng, nb, na);
			}	
			
			bool operator == (const Color& c2) {
				return (((int)255.0*r) == ((int)255.0*c2.r) && ((int)255.0*g) == ((int)255.0*c2.g) && ((int)255.0*b) == ((int)255.0*c2.b) && ((int)255.0*a) == ((int)255.0*c2.a));
			}
			
			bool operator != (const Color& c2) {
				return (((int)255.0*r) != ((int)255.0*c2.r) && ((int)255.0*g) != ((int)255.0*c2.g) && ((int)255.0*b) != ((int)255.0*c2.b) && ((int)255.0*a) != ((int)255.0*c2.a));
			}
			

			/** 
			* Sets the color using an integer color value
			* @param hex 32-bit integer with color values.
			*/			
			void setColorHex(unsigned int hex);
			
			/** 
			* Sets the color using a 24-bit RGB integer color value
			* @param hex 24-bit integer with RGB color values.
			*/						
			void setColorHexRGB(unsigned int hex);
		
			/** 
			* Sets the color using HSV values.
			* @param h Hue.
			* @param s Saturation.
			* @param v Value.
			*/								
			void setColorHSV(Number h, Number s, Number v);
			
			/** 
			* Sets the color using 0-255 RGBA integers.
			* @param r Red value 0-255.
			* @param g Green value 0-255.
			* @param b Blue value 0-255.
			* @param a Alpha value 0-255.									
			*/											
			void setColorRGBA(int r, int g, int b, int a);
			
			/** 
			* Sets the color using 0-255 RGB integers.
			* @param r Red value 0-255.
			* @param g Green value 0-255.
			* @param b Blue value 0-255.								
			*/														
			void setColorRGB(int r, int g, int b);
			
			/**
			* Set from 0-1 floating point data.
			* @param r Red value 0-1.
			* @param g Green value 0-1
			* @param b Blue value 0-1
			* @param a Alpha value 0-1									
			*/																	
			void setColor(Number r, Number g, Number b, Number a);
			
			/**
			* Set from another color.
			* @param color The color to set from.
			*/															
			void setColor(const Color *color);
			
			/**
			* Sets the color to a random color. This does not affect alpha.
			*/
			void Random();
		
			/**
			* Retuns the brightness of the color
			* @return Brightness.
			*/
			Number getBrightness() const;
			
			/**
			* Returns the color as a 32-bit usigned integer.
			* @return Color as a single 32-bit unsigned integer.
			*/
			unsigned int getUint() const;
			
			/**
			* Red value.
			*/
			Number r;
			
			/**
			* Green value.
			*/			
			Number g;
			
			/**
			* Blue value.
			*/			
			Number b;
			
			/**
			* Alpha value.
			*/			
			Number a;
		protected:
	
	};

}
