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
#include "PolyGlobals.h"
#include <string>
#include <vector>
#include "PolyTexture.h"
#include "PolyShader.h"
#include "PolyResource.h"


using std::string;
using std::vector;

namespace Polycode {
	
	class _PolyExport Material : public Resource {
		public:
			Material(const String& name);
			virtual ~Material();
			
			void addShader(Shader *shader,ShaderBinding *shaderBinding);
			unsigned int getNumShaders() const;
			
			void addShaderRenderTarget(ShaderRenderTarget *newTarget);
			int getNumShaderRenderTargets();
			ShaderRenderTarget *getShaderRenderTarget(unsigned int index);
				
			const String& getName() const;
			Shader *getShader(unsigned int index) const;
			ShaderBinding *getShaderBinding(unsigned int index) const;
			void loadMaterial(const String& fileName);
			
			Number specularValue;
			Color specularColor;
			Color diffuseColor;
						
		protected:
		
			vector<Shader*> materialShaders;
			vector<ShaderBinding*> shaderBindings;
			vector<ShaderRenderTarget*> renderTargets;
					
			String name;
		
	};
}
