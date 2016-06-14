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
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyResource.h"
#include <memory>

namespace Polycode {

	class Texture;

	class _PolyExport Cubemap : public Resource {
		public:
			Cubemap(std::shared_ptr<Texture> t0,
					std::shared_ptr<Texture> t1,
					std::shared_ptr<Texture> t2,
					std::shared_ptr<Texture> t3,
					std::shared_ptr<Texture> t4,
					std::shared_ptr<Texture> t5);
		
			std::shared_ptr<Texture> getTexture(int index);			
			void setTexture(std::shared_ptr<Texture>, int index);
			
			virtual void recreateFromTextures(){}
			
			virtual ~Cubemap(); 
			
			static const int CUBEMAP_XPOS = 0;
			static const int CUBEMAP_XNEG = 1;
			static const int CUBEMAP_YPOS = 2;
			static const int CUBEMAP_YNEG = 3;			
			static const int CUBEMAP_ZPOS = 4;
			static const int CUBEMAP_ZNEG = 5;
																	
		protected:
		
			std::vector<std::shared_ptr<Texture> > textures;
		
	};
}
