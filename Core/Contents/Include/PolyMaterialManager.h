/*
 *  PolyMaterialManager.h
 *  TAU
 *
 *  Created by Ivan Safrin on 3/13/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

// @package Services
 
#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyCoreServices.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include "PolyMaterial.h"
#include "PolyShader.h"
#include "PolyFixedShader.h"
#include "PolyModule.h"
#include "PolyImage.h"
#include "tinyxml.h"
#include "PolyUtil.h"
#include <vector>

using namespace std;

namespace Polycode {
	
	class Texture;
	class SceneRenderTexture;
	class _PolyExport MaterialManager {
		public:
			MaterialManager();
			~MaterialManager();
			
			void Update(int elapsed);

			Texture *createFramebufferTexture(int width, int height, int type);
			Texture *createTexture(int width, int height, char *imageData, bool clamp=true, int type=Image::IMAGE_RGBA);
			Texture *createNewTexture(int width, int height, bool clamp=true, int type=Image::IMAGE_RGBA);
			Texture *createTextureFromImage(Image *image, bool clamp=true);
			Texture *createTextureFromFile(String fileName);
			void deleteTexture(Texture *texture);
		
			void reloadTextures();
			
			void reloadProgramsAndTextures();
			void reloadPrograms();		
		
			void addShaderModule(PolycodeShaderModule *module);		
		
			//SceneRenderTexture *createRenderTexture(Scene *targetScene, Camera *targetCamera, int renderWidth,int renderHeight);
			Texture *getTextureByResourcePath(String resourcePath);
			
			// cubemaps
		
			Cubemap *cubemapFromXMLNode(TiXmlNode *node);
		
			// materials
			void loadMaterialsFromFile(String fileName);
			Material *materialFromXMLNode(TiXmlNode *node);
			Shader *setShaderFromXMLNode(TiXmlNode *node);
			Shader *createShaderFromXMLNode(TiXmlNode *node);
		
		private:
			vector<Texture*> textures;
			vector<Material*> materials;
		
			vector <PolycodeShaderModule*> shaderModules;
	};
};