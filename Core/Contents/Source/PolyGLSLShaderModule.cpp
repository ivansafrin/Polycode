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


#ifdef _WINDOWS
#include <windows.h>
#endif

#include "PolyGLHeaders.h"

#include "PolyGLSLShaderModule.h"
#include "PolyCoreServices.h"
#include "PolyCore.h"
#include "PolyResourceManager.h"
#include "PolyRenderer.h"
#include "PolyGLSLProgram.h"
#include "PolyGLSLShader.h"
#include "PolyGLCubemap.h"
#include "PolyMaterial.h"
#include "PolyGLTexture.h"

#include "tinyxml.h"

using std::vector;

using namespace Polycode;

#if defined(_WINDOWS) && !defined(_MINGW)
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLUNIFORM1IPROC glUniform1i;
PFNGLUNIFORM1FPROC glUniform1f;
PFNGLUNIFORM2FPROC glUniform2f;
PFNGLUNIFORM3FPROC glUniform3f;
PFNGLUNIFORM4FPROC glUniform4f;
extern PFNGLACTIVETEXTUREPROC glActiveTexture;
PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLDELETESHADERPROC glDeleteShader;
PFNGLDELETEPROGRAMPROC glDeleteProgram;

PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
PFNGLGETSHADERIVPROC glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
PFNGLGETUNIFORMLOCATIONARBPROC glGetUniformLocation;
#endif

GLSLShaderModule::GLSLShaderModule() : PolycodeShaderModule() {
#ifdef _WINDOWS
	glUseProgram   = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");

#ifndef _MINGW
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
#endif
#endif
}

GLSLShaderModule::~GLSLShaderModule() {

}

bool GLSLShaderModule::acceptsExtension(const String& extension) {
	if(extension == "vert" || extension == "frag") {
		return true;
	} else {
		return false;
	}
}

String GLSLShaderModule::getShaderType() {
	return "glsl";
}

Shader *GLSLShaderModule::createShader(String name, String vpName, String fpName) {

	GLSLShader *retShader = NULL;

	GLSLProgram *vp = NULL;
	GLSLProgram *fp = NULL;

	vp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResourceByPath(vpName);
	fp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResourceByPath(fpName);

	if(vp != NULL && fp != NULL) {
		GLSLShader *shader = new GLSLShader(vp,fp);
		shader->setName(name);
		retShader = shader;
		shaders.push_back((Shader*)shader);
	}
	return retShader;
}

Shader *GLSLShaderModule::createShader(TiXmlNode *node) {
	TiXmlNode* pChild, *pChild2, *pChild3;	
	GLSLProgram *vp = NULL;
	GLSLProgram *fp = NULL;
	GLSLShader *retShader = NULL;

	TiXmlElement *nodeElement = node->ToElement();
	if (!nodeElement) return NULL; // Skip comment nodes

	for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		TiXmlElement *pChildElement = pChild->ToElement();
		if (!pChildElement) continue; // Skip comment nodes

		if(strcmp(pChild->Value(), "vp") == 0) {
			String vpFileName = String(pChildElement->Attribute("source"));
			vp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResourceByPath(vpFileName);
			if(!vp) {
				vp = (GLSLProgram*)CoreServices::getInstance()->getMaterialManager()->createProgramFromFile(vpFileName);
				if(vp) {
					vp->setResourcePath(vpFileName);
					OSFileEntry entry = OSFileEntry(vpFileName, OSFileEntry::TYPE_FILE);
					vp->setResourceName(entry.name);
					CoreServices::getInstance()->getResourceManager()->addResource(vp);
				}
			}
		}
		if(strcmp(pChild->Value(), "fp") == 0) {
			String fpFileName = String(pChildElement->Attribute("source"));
			fp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResourceByPath(fpFileName);
			if(!fp) {
				fp = (GLSLProgram*)CoreServices::getInstance()->getMaterialManager()->createProgramFromFile(fpFileName);
				if(fp) {
					fp->setResourcePath(fpFileName);
					OSFileEntry entry = OSFileEntry(fpFileName, OSFileEntry::TYPE_FILE);
					fp->setResourceName(entry.name);
					CoreServices::getInstance()->getResourceManager()->addResource(fp);
				}
			}
		}

	}
	if(vp != NULL && fp != NULL) {
		GLSLShader *cgShader = new GLSLShader(vp,fp);
		cgShader->setName(String(nodeElement->Attribute("name")));
		retShader = cgShader;
		shaders.push_back((Shader*)cgShader);
	}
	return retShader;

}

void GLSLShaderModule::clearShader() {
	glUseProgram(0);
}

void GLSLShaderModule::updateGLSLParam(Renderer *renderer, GLSLShader *glslShader, ProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions) {

		LocalShaderParam *localParam = NULL;
		localParam = materialOptions->getLocalParamByName(param.name);

		// local options override material options.
		LocalShaderParam *localOptionsParam = localOptions->getLocalParamByName(param.name);
		if(localOptionsParam) {
			localParam = localOptionsParam;
		}

		int paramLocation = glGetUniformLocation(glslShader->shader_id, param.name.c_str());

		switch(param.type) {
			case ProgramParam::PARAM_NUMBER:
				if(localParam) {
					glUniform1f(paramLocation, localParam->getNumber());
				} else {
					glUniform1f(paramLocation, 0.0f);
				}
			break;
			case ProgramParam::PARAM_VECTOR2:
				if(localParam) {
					Vector2 vec2 = localParam->getVector2();
					glUniform2f(paramLocation, vec2.x, vec2.y);
				} else {
					glUniform2f(paramLocation, 0.0f, 0.0f);
				}
			break;
			case ProgramParam::PARAM_VECTOR3:
				if(localParam) {
					Vector3 vec3 = localParam->getVector3();
					glUniform3f(paramLocation, vec3.x, vec3.y, vec3.z);
				} else {
					glUniform3f(paramLocation, 0.0f, 0.0f, 0.0f);
				}
			break;
			case ProgramParam::PARAM_COLOR:
				if(localParam) {
					Color color = localParam->getColor();
					glUniform4f(paramLocation, color.r, color.g, color.b, color.a);
				} else {
					glUniform4f(paramLocation, 0.0f, 0.0f, 0.0f, 0.0f);
				}
			break;
		}
}

bool GLSLShaderModule::applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) {

	GLSLShader *glslShader = (GLSLShader*)material->getShader(shaderIndex);

	glPushMatrix();
	glLoadIdentity();


	int numRendererAreaLights = renderer->getNumAreaLights();
	int numRendererSpotLights = renderer->getNumSpotLights();

	int numTotalLights = glslShader->numAreaLights + glslShader->numSpotLights;

	if(numTotalLights > 0) {
		renderer->sortLights();	
	}

	for(int i=0 ; i < numTotalLights; i++) {
		GLfloat resetData[] = {0.0, 0.0, 0.0, 0.0};
		glLightfv (GL_LIGHT0+i, GL_DIFFUSE, resetData);
		glLightfv (GL_LIGHT0+i, GL_SPECULAR, resetData);
		glLightfv (GL_LIGHT0+i, GL_AMBIENT, resetData);
		glLightfv (GL_LIGHT0+i, GL_POSITION, resetData);
		glLightf (GL_LIGHT0+i, GL_SPOT_CUTOFF, 180);
		glLightf (GL_LIGHT0+i, GL_CONSTANT_ATTENUATION,1.0);
		glLightf (GL_LIGHT0+i, GL_LINEAR_ATTENUATION,0.0);
		glLightf (GL_LIGHT0+i, GL_QUADRATIC_ATTENUATION, 0.0);
	}

	int lightIndex = 0;

	vector<LightInfo> areaLights = renderer->getAreaLights();

	GLfloat ambientVal[] = {1, 1, 1, 1.0};
	for(int i=0; i < glslShader->numAreaLights; i++) {
		LightInfo light;
		if(i < numRendererAreaLights) {
			light = areaLights[i];
			light.position = renderer->getCameraMatrix().Inverse() * light.position;
			ambientVal[0] = renderer->ambientColor.r;
			ambientVal[1] = renderer->ambientColor.g;
			ambientVal[2] = renderer->ambientColor.b;
			ambientVal[3] = 1;

			GLfloat data4[] = {light.color.x * light.intensity, light.color.y * light.intensity, light.color.z * light.intensity, 1.0};
			glLightfv (GL_LIGHT0+lightIndex, GL_DIFFUSE, data4);

			data4[0] = light.specularColor.r* light.intensity;
			data4[1] = light.specularColor.g* light.intensity;
			data4[2] = light.specularColor.b* light.intensity;
			data4[3] = light.specularColor.a* light.intensity;
			glLightfv (GL_LIGHT0+lightIndex, GL_SPECULAR, data4);

			data4[3] = 1.0;

			glLightfv (GL_LIGHT0+lightIndex, GL_AMBIENT, ambientVal);
			glLightf (GL_LIGHT0+lightIndex, GL_SPOT_CUTOFF, 180);

			data4[0] = light.position.x;
			data4[1] = light.position.y;
			data4[2] = light.position.z;
			glLightfv (GL_LIGHT0+lightIndex, GL_POSITION, data4);

			glLightf (GL_LIGHT0+lightIndex, GL_CONSTANT_ATTENUATION, light.constantAttenuation);
			glLightf (GL_LIGHT0+lightIndex, GL_LINEAR_ATTENUATION, light.linearAttenuation);
			glLightf (GL_LIGHT0+lightIndex, GL_QUADRATIC_ATTENUATION, light.quadraticAttenuation);

		}
		lightIndex++;
	}

	vector<LightInfo> spotLights = renderer->getSpotLights();
//	vector<Texture*> shadowMapTextures = renderer->getShadowMapTextures();	
	char texName[32];
	char matName[32];
	int shadowMapTextureIndex = 0;

	glUseProgram(glslShader->shader_id);
	int textureIndex = 0;

	for(int i=0; i < glslShader->numSpotLights; i++) {
		LightInfo light;
		Vector3 pos;
		Vector3 dir;
		if(i < numRendererSpotLights) {
			light = spotLights[i];
			pos = light.position;
			dir = light.dir;
			pos = renderer->getCameraMatrix().Inverse() * pos;
			dir = renderer->getCameraMatrix().Inverse().rotateVector(dir);

			ambientVal[0] = renderer->ambientColor.r;
			ambientVal[1] = renderer->ambientColor.g;
			ambientVal[2] = renderer->ambientColor.b;
			ambientVal[3] = 1;

			GLfloat data4[] = {light.color.x * light.intensity, light.color.y * light.intensity, light.color.z * light.intensity, 1.0};
			glLightfv (GL_LIGHT0+lightIndex, GL_DIFFUSE, data4);

			data4[0] = light.specularColor.r* light.intensity;
			data4[1] = light.specularColor.g* light.intensity;
			data4[2] = light.specularColor.b* light.intensity;
			data4[3] = light.specularColor.a* light.intensity;
			glLightfv (GL_LIGHT0+lightIndex, GL_SPECULAR, data4);

			data4[3] = 1.0;

			glLightfv (GL_LIGHT0+lightIndex, GL_AMBIENT, ambientVal);
			glLightf (GL_LIGHT0+lightIndex, GL_SPOT_CUTOFF, light.spotlightCutoff);

			glLightf (GL_LIGHT0+lightIndex, GL_SPOT_EXPONENT, light.spotlightExponent);

			data4[0] = dir.x;
			data4[1] = dir.y;
			data4[2] = dir.z;
			glLightfv (GL_LIGHT0+lightIndex, GL_SPOT_DIRECTION, data4);

			data4[0] = pos.x;
			data4[1] = pos.y;
			data4[2] = pos.z;
			glLightfv (GL_LIGHT0+lightIndex, GL_POSITION, data4);

			glLightf (GL_LIGHT0+lightIndex, GL_CONSTANT_ATTENUATION, light.constantAttenuation);
			glLightf (GL_LIGHT0+lightIndex, GL_LINEAR_ATTENUATION, light.linearAttenuation);
			glLightf (GL_LIGHT0+lightIndex, GL_QUADRATIC_ATTENUATION, light.quadraticAttenuation);

			if(light.shadowsEnabled) {
				if(shadowMapTextureIndex < 4) {
					switch(shadowMapTextureIndex) {
						case 0:
							strcpy(texName, "shadowMap0");
							strcpy(matName, "shadowMatrix0");
						break;
						case 1:
							strcpy(texName, "shadowMap1");
							strcpy(matName, "shadowMatrix1");
						break;
						case 2:
							strcpy(texName, "shadowMap2");
							strcpy(matName, "shadowMatrix2");
						break;
						case 3:
							strcpy(texName, "shadowMap3");
							strcpy(matName, "shadowMatrix3");
						break;
					}

					int texture_location = glGetUniformLocation(glslShader->shader_id, texName);
					glUniform1i(texture_location, textureIndex);
					glActiveTexture(GL_TEXTURE0 + textureIndex);
					glBindTexture(GL_TEXTURE_2D, ((OpenGLTexture*)light.shadowMapTexture)->getTextureID());	
					textureIndex++;

					int mloc = glGetUniformLocation(glslShader->shader_id, matName);
					light.textureMatrix = light.textureMatrix;


					GLfloat mat[16];
					for(int z=0; z < 16; z++) {
						mat[z] = light.textureMatrix.ml[z];
					}
					glUniformMatrix4fv(mloc, 1, false, mat);


				}
				shadowMapTextureIndex++;
			} else {
				light.shadowsEnabled = false;
			}
		}
		lightIndex++;
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);

	Matrix4 modelMatrix = renderer->getCurrentModelMatrix();
	int mloc = glGetUniformLocation(glslShader->shader_id, "modelMatrix");
	GLfloat mat[16];
	for(int z=0; z < 16; z++) {
		mat[z] = modelMatrix.ml[z];
	}
	glUniformMatrix4fv(mloc, 1, false, mat);


	GLSLShaderBinding *cgBinding = (GLSLShaderBinding*)material->getShaderBinding(shaderIndex);

	for(int i=0; i < glslShader->expectedParams.size(); i++) {
		ProgramParam param = glslShader->expectedParams[i];
		updateGLSLParam(renderer, glslShader, param, material->getShaderBinding(shaderIndex), localOptions);
	}

	for(int i=0; i < cgBinding->textures.size(); i++) {
		OpenGLTexture *glTexture = (OpenGLTexture*)cgBinding->textures[i].texture;
		if(glTexture) {
			int texture_location = glGetUniformLocation(glslShader->shader_id, cgBinding->textures[i].name.c_str());
			glUniform1i(texture_location, textureIndex);
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_2D, glTexture->getTextureID());
			textureIndex++;
		}
	}


	for(int i=0; i < cgBinding->cubemaps.size(); i++) {
		OpenGLCubemap *glCubemap = (OpenGLCubemap*)cgBinding->cubemaps[i].cubemap;
		if(glCubemap) {
			int texture_location = glGetUniformLocation(glslShader->shader_id, cgBinding->cubemaps[i].name.c_str());
			glUniform1i(texture_location, textureIndex);
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_CUBE_MAP, glCubemap->getTextureID());
			textureIndex++;
		}
	}

	cgBinding = (GLSLShaderBinding*)localOptions;
	for(int i=0; i < cgBinding->textures.size(); i++) {
		OpenGLTexture *glTexture = (OpenGLTexture*)cgBinding->textures[i].texture;
		if(glTexture) {
			int texture_location = glGetUniformLocation(glslShader->shader_id, cgBinding->textures[i].name.c_str());
			glUniform1i(texture_location, textureIndex);
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_2D, glTexture->getTextureID());
			textureIndex++;
		}
	}

	for(int i=0; i < cgBinding->cubemaps.size(); i++) {
		OpenGLCubemap *glCubemap = (OpenGLCubemap*)cgBinding->cubemaps[i].cubemap;
		if(glCubemap) {
			int texture_location = glGetUniformLocation(glslShader->shader_id, cgBinding->cubemaps[i].name.c_str());
			glUniform1i(texture_location, textureIndex);
			glActiveTexture(GL_TEXTURE0 + textureIndex);
			glBindTexture(GL_TEXTURE_CUBE_MAP, glCubemap->getTextureID());
			textureIndex++;
		}
	}


	return true;
}

void GLSLShaderModule::reloadPrograms() {
	for(int i=0; i < programs.size(); i++) {
		GLSLProgram *program = programs[i];
		program->reloadProgram();
	}
}

GLSLProgram *GLSLShaderModule::createGLSLProgram(const String& fileName, int type) {
	GLSLProgram *prog = new GLSLProgram(fileName, type);
	programs.push_back(prog);
	return prog;
}

ShaderProgram* GLSLShaderModule::createProgramFromFile(const String& extension, const String& fullPath) {
	if(extension == "vert") {
		Logger::log("Adding GLSL vertex program %s\n", fullPath.c_str());
		return createGLSLProgram(fullPath, GLSLProgram::TYPE_VERT);
	}
	if(extension == "frag") {
		Logger::log("Adding GLSL fragment program %s\n", fullPath.c_str());
		return createGLSLProgram(fullPath, GLSLProgram::TYPE_FRAG);
	}
	return NULL;
}
