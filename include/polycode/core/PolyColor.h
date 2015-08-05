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
#include "PolyString.h"

namespace Polycode {

	/**
	* Stores and manipulates color information. Color is always RGBA in Polycode.
	*/						
	class _PolyExport Color : public PolyBase {
		public:

	
			/**
			* Create from 0-1 floating point data.
			* @param r Red value 0-1.
			* @param g Green value 0-1
			* @param b Blue value 0-1
			* @param a Alpha value 0-1									
			*/														
			Color(float r,float g,float b,float a);

			/**
			* @copydoc Color::Color(float,float,float,float)
			*/
			Color(double r,double g,double b,double a);

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
			* Create from another color.
			* @param color The color to create from.
			*/												
			Color(const Color *color);
			
			/**
			* Create from integer color.
			* @param hex Integer color value.
			*/															
			Color(unsigned int hex);
		
			/**
			* Create from 0-255 integer data.
			* @param r Red value 0-255.
			* @param g Green value 0-255.
			* @param b Blue value 0-255.
			* @param a Alpha value 0-255.									
			*/		
			static Color ColorWithInts(int r,int g, int b, int a);
			
			/**
			* Create from integer color.
			* @param hex Integer color value.
			*/			
			static Color ColorWithHex(unsigned int hex);
		
			virtual ~Color();
			
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

			/** 
			* Multiplies the color with a number
			*/
			inline Color operator * ( const Number val) const {
				Number nr = r * val;
				Number ng = g * val;
				Number nb = b * val;
				Number na = a * val;				
				return Color(nr, ng, nb, na);
			}	
			
			/** 
			* Adds the color to another color.
			*/
			inline Color operator + ( const Color& v2) const {
				Number nr = r + v2.r;
				Number ng = g + v2.g;
				Number nb = b + v2.b;
				Number na = a + v2.a;				
				return Color(nr, ng, nb, na);
			}	
			
			
			bool operator == (const Color& c2) {
				return (((int)255.0*r) == ((int)255.0*c2.r) && ((int)255.0*g) == ((int)255.0*c2.g) && ((int)255.0*b) == ((int)255.0*c2.b) && ((int)255.0*a) == ((int)255.0*c2.a));
			}
			
			bool operator != (const Color& c2) {
				return (((int)255.0*r) != ((int)255.0*c2.r) || ((int)255.0*g) != ((int)255.0*c2.g) || ((int)255.0*b) != ((int)255.0*c2.b) || ((int)255.0*a) != ((int)255.0*c2.a));
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
			* Sets the color using an integer color value from a string
			* @param hex String with hex RGBA color values.
			*/			
			void setColorHexFromString(String hex);
			
			/** 
			* Sets the color using a 24-bit RGB integer color value  from a string
			* @param hex String with hex RGB color values.
			*/						
			void setColorHexRGBFromString(String hex);
					
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
			* Returns a new color after blending the second color with specified blending mode. 
			* @param c2 Color to blend with
			* @param mode Blending mode to use. Currently possible values are Color::BLEND_NORMAL, Color::BLEND_REPLACE_COLOR and Color::BLEND_ADDITIVE
			* @param amount Amount to blend.
			*/
			Color blendColor(Color c2, int mode, Number amount, Color c3 = Color());
			
			/**
			* Sets the color to a random color. This does not affect alpha.
			*/
			void Random();
		
			/**
			* Retuns the brightness of the color
			* @return Brightness.
			*/
			Number getBrightness() const;
			
			static void RGBtoHSV(const Number &r, const Number &g, const Number &b, Number &h, Number &s, Number &v);
			
			/**
			* Returns the hue of the color's HSV component.
			* @return HSV Hue.
			*/
			Number getHue() const;

			/**
			* Returns the saturation of the color's HSV component.
			* @return HSV Saturation
			*/
			Number getSaturation() const;

			/**
			* Returns the value of the color's HSV component
			* @return HSV Value
			*/
			Number getValue() const;

			
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
			

			const static int BLEND_NORMAL = 0;
			const static int BLEND_REPLACE_COLOR = 1;
			const static int BLEND_ADDITIVE = 2;
									
		protected:
	
	};

}
