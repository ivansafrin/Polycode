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
#include "PolyResource.h"

namespace Polycode {

class Texture;

class _PolyExport Cubemap : public Resource {
	public:
		Cubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);

		Texture *getTexture(int index);
		void setTexture(Texture *texture, int index);

		virtual void recreateFromTextures(){}

		virtual ~Cubemap();

		static const int CUBEMAP_XPOS = 0;
		static const int CUBEMAP_XNEG = 1;
		static const int CUBEMAP_YPOS = 2;
		static const int CUBEMAP_YNEG = 3;
		static const int CUBEMAP_ZPOS = 4;
		static const int CUBEMAP_ZNEG = 5;

	protected:

		std::vector<Texture*> textures;

};
}
