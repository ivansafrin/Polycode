/*
 *  PolyModule.h
 *  PolyCore
 *
 *  Created by Ivan Safrin on 12/1/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#pragma once
#include "PolyGlobals.h"
#include "tinyxml.h"
#include "PolyShader.h"
#include "PolyMaterial.h"

namespace Polycode {
	
	class Renderer;	
	
	class _PolyExport PolycodeModule {
	public:
		PolycodeModule();
		virtual ~PolycodeModule();
		
		int getType() { return type; }
		
		static const int TYPE_GENERIC = 0;
		static const int TYPE_SHADER = 0;
	protected:
		int type;
	};
	
	class _PolyExport PolycodeShaderModule : public PolycodeModule {
	public:
		PolycodeShaderModule();
		virtual ~PolycodeShaderModule();
		
		virtual bool acceptsExtension(string extension) = 0;
		virtual Resource* createProgramFromFile(string extension, string fullPath) = 0;
		virtual string getShaderType() = 0;
		virtual Shader *createShader(TiXmlNode *node) = 0;
	
		virtual bool applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) = 0;
		bool hasShader(Shader *shader) { for(int i=0; i < shaders.size(); i++) { if(shaders[i] == shader){ return true; } } return false; }	
		virtual void clearShader() = 0;
		virtual void reloadPrograms() = 0;
	protected:
		vector<Shader*> shaders;
	};
	
}