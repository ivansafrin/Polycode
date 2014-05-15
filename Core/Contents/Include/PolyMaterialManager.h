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
#include "PolyImage.h"
#include "PolyObject.h"
#include "PolyShader.h"
#include <vector>

class TiXmlNode;

namespace Polycode {
	
	class Cubemap;
	class Material;
	class PolycodeShaderModule;
	class Texture;
	class SceneRenderTexture;
	class Shader;
	class String;
	class ShaderProgram;
    class ResourcePool;
	
	/**
	* Manages loading and reloading of materials, textures and shaders. This class should be only accessed from the CoreServices singleton.
	*/
	class _PolyExport MaterialManager : public PolyBase {
		public:
			MaterialManager();
			~MaterialManager();
			
			void Update(int elapsed);

			/**
			* Creates a new framebuffer texture.
			*/ 
			Texture *createFramebufferTexture(int width, int height, int type);
			Texture *createTexture(int width, int height, char *imageData, bool clamp=false, bool createMipmaps = true, int type=Image::IMAGE_RGBA);
			Texture *createNewTexture(int width, int height, bool clamp=false, bool createMipmaps = true, int type=Image::IMAGE_RGBA);
			Texture *createTextureFromImage(Image *image, bool clamp=false, bool createMipmaps = true);
			Texture *createTextureFromFile(const String& fileName, bool clamp=false, bool createMipmaps = true, ResourcePool *resourcePool = NULL);
			void deleteTexture(Texture *texture);
		
			void reloadTextures();
			
			void reloadProgramsAndTextures();
			void reloadPrograms();		
		
			void addShaderModule(PolycodeShaderModule *module);		
		
			//SceneRenderTexture *createRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight);
			Texture *getTextureByResourcePath(const String& resourcePath) const;
			
			ShaderProgram *createProgramFromFile(String programPath);
			
            void loadMaterialLibraryIntoPool(ResourcePool *pool, const String &materialFile);
        
			// cubemaps
		
			Cubemap *cubemapFromXMLNode(TiXmlNode *node);
		
			// materials
			Material *materialFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node);
			
			Material *createMaterial(ResourcePool *resourcePool, String materialName, String shaderName);
			
			Shader *setShaderFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node);
			Shader *createShaderFromXMLNode(ResourcePool *resourcePool, TiXmlNode *node);
			Shader *createShader(ResourcePool *resourcePool, String shaderType, String name, String vpName, String fpName, bool screenShader);
		
			std::vector<Material*> loadMaterialsFromFile(ResourcePool *resourcePool, const String &fileName);
			std::vector<Shader*> loadShadersFromFile(ResourcePool *resourcePool, String fileName);
			std::vector<Cubemap*> loadCubemapsFromFile(String fileName);
						
			void addMaterial(Material *material);
			void addShader(Shader *shader);
		
			unsigned int getNumShaders();
			Shader *getShaderByIndex(unsigned int index);
		
			bool premultiplyAlphaOnLoad;
			bool clampDefault;
			bool mipmapsDefault;
			bool keepTextureData;
			
		private:
			std::vector<Texture*> textures;
			std::vector<Material*> materials;
			std::vector<Shader*> shaders;
		
			std::vector <PolycodeShaderModule*> shaderModules;
	};
};
