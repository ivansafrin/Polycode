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
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyColor.h"
#include <vector>
#include <memory>

namespace Polycode {
	
	class Shader;
	class ShaderBinding;
	class ShaderRenderTarget;
	class Mesh;
	class VertexDataArray;
	
	class _PolyExport ShaderPass {
		public:
			ShaderPass();
			ShaderPass(Shader *shader);
			ShaderPass(const ShaderPass &other);
			~ShaderPass();
		
			std::shared_ptr<ShaderBinding> getShaderBinding();
		
			std::shared_ptr<Shader> shader;
			bool wireframe;
			unsigned short blendingMode;
			std::shared_ptr<ShaderBinding> shaderBinding;
			std::shared_ptr<ShaderBinding> materialShaderBinding;
	};

	class _PolyExport Material : public Resource {
		public:
			explicit Material(const String& name);
			virtual ~Material();

			void addShaderPass(const ShaderPass &pass);
			void addShaderPassAtIndex(const ShaderPass &pass, unsigned int shaderIndex);	
			unsigned int getNumShaderPasses() const;
		
			void removeShaderPass(int shaderIndex);

			void addShaderRenderTarget(ShaderRenderTarget *newTarget);
			int getNumShaderRenderTargets();
			ShaderRenderTarget *getShaderRenderTarget(unsigned int index);
			void removeShaderRenderTarget(int index);
			void recreateRenderTarget(ShaderRenderTarget *renderTarget);
			void recreateRenderTargets();
						
			const String& getName() const;
			ShaderPass getShaderPass(unsigned int index) const;
			std::shared_ptr<ShaderBinding> getShaderBinding(unsigned int index) const;
			std::shared_ptr<Shader> getShader(unsigned int index) const;
		
			void loadMaterial(const String& fileName);
			
			void setName(const String &name);
			
			void clearShaders();
							
			bool fp16RenderTargets;
			int blendingMode;
			bool screenMaterial;
			
		protected:
		
			std::vector<ShaderPass> shaderPasses;
			std::vector<ShaderRenderTarget*> renderTargets;
					
			String name;
		
	};
}
