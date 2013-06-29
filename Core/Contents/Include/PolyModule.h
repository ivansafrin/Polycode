/*
 *  PolyModule.h
 *  PolyCore
 *
 *  Created by Ivan Safrin on 12/1/10.
 *  Copyright 2010 Local Projects. All rights reserved.
 *
 */

#pragma once
#include "PolyString.h"
#include "PolyGlobals.h"

class TiXmlNode;

namespace Polycode {

class Material;
class Renderer;
class Shader;
class ShaderBinding;
class Resource;
class ShaderProgram;

class _PolyExport PolycodeModule : public PolyBase {
	public:
		PolycodeModule();
		virtual ~PolycodeModule();

		int getType() { return type; }

		static const int TYPE_GENERIC = 0;
		static const int TYPE_SHADER = 1;

		virtual void Update(Number elapsed) {}

		bool requiresUpdate();

	protected:
		int type;
		bool _requiresUpdate;
};

class _PolyExport PolycodeShaderModule : public PolycodeModule {
	public:
		PolycodeShaderModule();
		virtual ~PolycodeShaderModule();

		virtual bool acceptsExtension(const String& extension) = 0;
		virtual ShaderProgram* createProgramFromFile(const String& extension, const String& fullPath) = 0;
		virtual String getShaderType() = 0;
		virtual Shader *createShader(TiXmlNode *node) = 0;
		virtual Shader *createShader(String name, String vpName, String fpName) = 0;

		virtual bool applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) = 0;
		bool hasShader(Shader *shader) { 
			for(int i=0; i < shaders.size(); i++) { 
				if(shaders[i] == shader){ 
					return true; 
				} 
			} 
			return false; 
		}
		virtual void clearShader() = 0;
		virtual void reloadPrograms() = 0;
	protected:
		std::vector<Shader*> shaders;
};

}
