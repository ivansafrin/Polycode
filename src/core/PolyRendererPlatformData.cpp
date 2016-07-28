/*
 Copyright (C) 2016 by Ivan Safrin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or se ll
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

#include "polycode/core/PolyRendererPlatformData.h"
#include "polycode/core/PolyRenderer.h"

using namespace Polycode;

RendererPlatformData::RendererPlatformData()  : type(0), data(NULL), renderer(NULL) {
	
}

RendererPlatformData::~RendererPlatformData() {
	if(renderer) {
		switch(type) {
			case PLATFORM_DATA_TEXTURE:
				renderer->destroyTexturePlatformData(data);
				break;
			case PLATFORM_DATA_RENDER_BUFFER:
				renderer->destroyRenderBufferPlatformData(data);
				break;
			case PLATFORM_DATA_PROGRAM:
				renderer->destroyProgramPlatformData(data);
				break;
			case PLATFORM_DATA_SHADER:
				renderer->destroyShaderPlatformData(data);
				break;
			case PLATFORM_DATA_SUBMESH:
				renderer->destroySubmeshPlatformData(data);
				break;
		}
	}
}