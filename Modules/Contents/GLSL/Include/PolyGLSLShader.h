/*
 *  PolyGLSLShader.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Materials

#pragma once

#include "PolyGlobals.h"

#include "PolyLogger.h"
#include "PolyShader.h"
#include "PolyGLSLProgram.h"
#include "PolyTexture.h"
#include "PolyCubemap.h"
#include <vector>

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glext.h>
#endif


using std::vector;

namespace Polycode {

	typedef struct {
		Texture *texture;
		String name;
	} GLSLTextureBinding;

	typedef struct {
		Cubemap *cubemap;
		String name;
	} GLSLCubemapBinding;
	
	
	class _PolyExport GLSLShader : public Shader {
		public:
			GLSLShader(GLSLProgram *vp, GLSLProgram *fp);
			virtual ~GLSLShader();

			ShaderBinding *createBinding();
			
			unsigned int shader_id;		
			GLSLProgram *vp;
			GLSLProgram *fp;			
			
		protected:
			
	};
	
	class _PolyExport GLSLShaderBinding : public ShaderBinding {
		public:
			GLSLShaderBinding(GLSLShader *shader);
			virtual ~GLSLShaderBinding();
			
			void addTexture(String name, Texture *texture); 
			void addCubemap(String name, Cubemap *cubemap);				
			void clearTexture(String name);			
			void addParam(String type, String name, String value);
			
			vector<GLSLTextureBinding> textures;
			vector<GLSLCubemapBinding> cubemaps;		
		
			GLSLShader *glslShader;
	};
}
