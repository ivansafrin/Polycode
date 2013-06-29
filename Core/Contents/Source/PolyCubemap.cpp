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

#include "PolyCubemap.h"

using namespace Polycode;

Cubemap::Cubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5) : Resource(Resource::RESOURCE_CUBEMAP) {
	textures.push_back(t0);
	textures.push_back(t1);
	textures.push_back(t2);
	textures.push_back(t3);
	textures.push_back(t4);
	textures.push_back(t5);
}

void Cubemap::setTexture(Texture *texture, int index) {
	if(index >= 0 && index < 6) {
		textures[index] = texture;
	}
}

Texture *Cubemap::getTexture(int index) {
	if(index >= 0 && index < 6) {
		return textures[index];
	} else {
		return NULL;
	}
}

Cubemap::~Cubemap() {

}
