/*
 *  PolyGLSLShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyGLSLShaderModule.h"

using namespace Polycode;

GLSLShaderModule::GLSLShaderModule() : PolycodeShaderModule() {
}

GLSLShaderModule::~GLSLShaderModule() {

}

bool GLSLShaderModule::acceptsExtension(String extension) {
	if(extension == "vert" || extension == "frag") {
		return true;
	} else {
		return false;
	}
}

String GLSLShaderModule::getShaderType() {
	return "glsl";
}

Shader *GLSLShaderModule::createShader(TiXmlNode *node) {
	TiXmlNode* pChild, *pChild2, *pChild3;	
	GLSLProgram *vp = NULL;
	GLSLProgram *fp = NULL;
	GLSLShader *retShader = NULL;
	
	for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		if(strcmp(pChild->Value(), "vp") == 0) {
			vp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_PROGRAM, pChild->ToElement()->Attribute("source"));
			if(vp) {
				for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
					if(strcmp(pChild2->Value(), "params") == 0) {
						for (pChild3 = pChild2->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
							if(strcmp(pChild3->Value(), "param") == 0) {
								addParamToProgram(vp,pChild3); 
							}
						}
					}
				}
			}
		}
		if(strcmp(pChild->Value(), "fp") == 0) {
			fp = (GLSLProgram*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_PROGRAM, pChild->ToElement()->Attribute("source"));
			if(fp) {
				for (pChild2 = pChild->FirstChild(); pChild2 != 0; pChild2 = pChild2->NextSibling()) {
					if(strcmp(pChild2->Value(), "params") == 0) {
						for (pChild3 = pChild2->FirstChild(); pChild3 != 0; pChild3 = pChild3->NextSibling()) {
							if(strcmp(pChild3->Value(), "param") == 0) {
								addParamToProgram(fp,pChild3); 										
							}
						}
					}
				}
			}
		}
		
	}
	if(vp != NULL && fp != NULL) {
		GLSLShader *cgShader = new GLSLShader(vp,fp);
		cgShader->setName(node->ToElement()->Attribute("name"));
		retShader = cgShader;
		shaders.push_back((Shader*)cgShader);
	}
	return retShader;

}

void GLSLShaderModule::clearShader() {
	glUseProgram(0);
}

void GLSLShaderModule::setGLSLAreaLightPositionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumAreaLights() > lightIndex) {
		vector<LightInfo> areaLights = renderer->getAreaLights();			
		Vector3 lPos(areaLights[lightIndex].position.x,areaLights[lightIndex].position.y,areaLights[lightIndex].position.z);
		GLfloat LightPosition[] = {lPos.x, lPos.y, lPos.z, 0};		
		glLightfv (GL_LIGHT0+lightIndex, GL_POSITION, LightPosition); //change the 	
	} else {
	}	
}

void GLSLShaderModule::setGLSLSpotLightPositionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();		
		Vector3 lPos(spotLights[lightIndex].position.x,spotLights[lightIndex].position.y,spotLights[lightIndex].position.z);
		lPos = renderer->getCameraMatrix().inverse() * lPos;
//		cgGLSetParameter4f(param.cgParam, lPos.x,lPos.y,lPos.z, spotLights[lightIndex].distance);
	} else {
//		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}	
}

void GLSLShaderModule::setGLSLSpotLightDirectionParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();		
		Vector3 lPos(spotLights[lightIndex].dir.x,spotLights[lightIndex].dir.y,spotLights[lightIndex].dir.z);
		lPos = renderer->getCameraMatrix().inverse().rotateVector(lPos);
//		cgGLSetParameter3f(param.cgParam, lPos.x,lPos.y,lPos.z);
	} else {
//		cgGLSetParameter3f(param.cgParam, 0.0f,0.0f,0.0f);
	}				
}

void GLSLShaderModule::setGLSLAreaLightColorParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumAreaLights() > lightIndex) {
		vector<LightInfo> areaLights = renderer->getAreaLights();		
		
		GLfloat DiffuseLight[] = {areaLights[lightIndex].color.x, areaLights[lightIndex].color.y, areaLights[lightIndex].color.z};
		glLightfv (GL_LIGHT0+lightIndex, GL_DIFFUSE, DiffuseLight);
		
//		cgGLSetParameter4f(param.cgParam, areaLights[lightIndex].color.x,areaLights[lightIndex].color.y,areaLights[lightIndex].color.z, areaLights[lightIndex].intensity);
	} else {
//		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}
}

void GLSLShaderModule::setGLSLSpotLightColorParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();			
//		cgGLSetParameter4f(param.cgParam, spotLights[lightIndex].color.x,spotLights[lightIndex].color.y,spotLights[lightIndex].color.z, spotLights[lightIndex].intensity);
	} else {
//		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}
}

void GLSLShaderModule::setGLSLSpotLightTextureMatrixParameter(Renderer *renderer, GLSLProgramParam &param, int lightIndex) {
	if(renderer->getNumLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();			
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixd(spotLights[lightIndex].textureMatrix.ml);				
//		cgGLSetStateMatrixParameter(param.cgParam, GLSL_GL_MODELVIEW_MATRIX,GLSL_GL_MATRIX_IDENTITY);
		glPopMatrix();
	}					
}



void GLSLShaderModule::updateGLSLParam(Renderer *renderer, GLSLProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions) {
	if(param.isAuto) {
		switch(param.autoID) {
			case GLSLProgramParam::TAU_MODELVIEWPROJ_MATRIX:
//				cgGLSetStateMatrixParameter(param.cgParam, GLSL_GL_MODELVIEW_PROJECTION_MATRIX,GLSL_GL_MATRIX_IDENTITY);
				break;
				
			case GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_0:
				setGLSLSpotLightTextureMatrixParameter(renderer, param, 0);					
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_1:
				setGLSLSpotLightTextureMatrixParameter(renderer, param, 1);					
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_2:
				setGLSLSpotLightTextureMatrixParameter(renderer, param, 2);					
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_3:
				setGLSLSpotLightTextureMatrixParameter(renderer, param, 3);					
				break;
				
				
			case GLSLProgramParam::TAU_AMBIENTCOLOR:
//				cgGLSetParameter3f(param.cgParam, renderer->ambientColor.r,renderer->ambientColor.g,renderer->ambientColor.b);
				break;
			case GLSLProgramParam::TAU_CLEARCOLOR:
//				cgGLSetParameter3f(param.cgParam, renderer->clearColor.r,renderer->clearColor.g,renderer->clearColor.b);				
				break;				
				
			case GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_0:
				setGLSLSpotLightDirectionParameter(renderer, param, 0);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_1:
				setGLSLSpotLightDirectionParameter(renderer, param, 1);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_2:
				setGLSLSpotLightDirectionParameter(renderer, param, 2);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_3:
				setGLSLSpotLightDirectionParameter(renderer, param, 3);
				break;
				
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_0:
				setGLSLAreaLightPositionParameter(renderer, param, 0);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_1:
				setGLSLAreaLightPositionParameter(renderer, param, 1);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_2:
				setGLSLAreaLightPositionParameter(renderer, param, 2);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_3:
				setGLSLAreaLightPositionParameter(renderer, param, 3);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_4:
				setGLSLAreaLightPositionParameter(renderer, param, 4);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_5:
				setGLSLAreaLightPositionParameter(renderer, param, 5);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_6:
				setGLSLAreaLightPositionParameter(renderer, param, 6);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_POSITION_7:
				setGLSLAreaLightPositionParameter(renderer, param, 7);
				break;				
				
			case GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_0:
				setGLSLSpotLightPositionParameter(renderer, param, 0);
				break;				
			case GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_1:
				setGLSLSpotLightPositionParameter(renderer, param, 1);
				break;				
			case GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_2:
				setGLSLSpotLightPositionParameter(renderer, param, 2);
				break;				
			case GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_3:
				setGLSLSpotLightPositionParameter(renderer, param, 3);
				break;				
				
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_0:
				setGLSLAreaLightColorParameter(renderer, param, 0);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_1:
				setGLSLAreaLightColorParameter(renderer, param, 1);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_2:
				setGLSLAreaLightColorParameter(renderer, param, 2);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_3:
				setGLSLAreaLightColorParameter(renderer, param, 3);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_4:
				setGLSLAreaLightColorParameter(renderer, param, 4);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_5:
				setGLSLAreaLightColorParameter(renderer, param, 5);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_6:
				setGLSLAreaLightColorParameter(renderer, param, 6);
				break;
			case GLSLProgramParam::TAU_AREA_LIGHT_COLOR_7:
				setGLSLAreaLightColorParameter(renderer, param, 7);
				break;
				
			case GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_0:
				setGLSLSpotLightColorParameter(renderer, param, 0);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_1:
				setGLSLSpotLightColorParameter(renderer, param, 1);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_2:
				setGLSLSpotLightColorParameter(renderer, param, 2);
				break;
			case GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_3:
				setGLSLSpotLightColorParameter(renderer, param, 3);
				break;				
				
			case GLSLProgramParam::TAU_MODELVIEW_MATRIX: 
//				cgGLSetStateMatrixParameter(param.cgParam, GLSL_GL_MODELVIEW_MATRIX,GLSL_GL_MATRIX_IDENTITY); }
				break;
			case GLSLProgramParam::TAU_MODELVIEW_INVERSE_MATRIX:
//				cgGLSetStateMatrixParameter(param.cgParam, GLSL_GL_MODELVIEW_MATRIX,GLSL_GL_MATRIX_INVERSE_TRANSPOSE);
				break;
			case GLSLProgramParam::TAU_EXPOSURE_LEVEL:
//				cgGLSetParameter1f(param.cgParam, renderer->exposureLevel);
				break;
		}
	} else {
		void *paramData = param.defaultData;
		LocalShaderParam *localParam = materialOptions->getLocalParamByName(param.name);
		if(localParam)
			paramData = localParam->data;
		localParam = localOptions->getLocalParamByName(param.name);
		if(localParam)
			paramData = localParam->data;
		
		float *fval;
		
		switch(param.paramType) {
			case GLSLProgramParam::PARAM_FLOAT:
				fval = (float*)paramData;
//				cgGLSetParameter1f(param.cgParam, *fval);
				break;
			case GLSLProgramParam::PARAM_FLOAT3:
				Vector3 *fval3 = (Vector3*)paramData;
//				cgGLSetParameter3f(param.cgParam, fval3->x,fval3->y,fval3->z);
				break;
		}
	}
}

bool GLSLShaderModule::applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) {	
	
	glEnable(GL_TEXTURE_2D);
		
	GLSLShader *glslShader = (GLSLShader*)material->getShader(shaderIndex);
	GLSLShaderBinding *cgBinding = (GLSLShaderBinding*)material->getShaderBinding(shaderIndex);
	
	for(int i=0; i < glslShader->vp->params.size(); i++) {
		GLSLProgramParam param = glslShader->vp->params[i];
		updateGLSLParam(renderer, param, material->getShaderBinding(shaderIndex), localOptions);
	}
	
	for(int i=0; i < glslShader->fp->params.size(); i++) {
		GLSLProgramParam param = glslShader->fp->params[i];
		updateGLSLParam(renderer, param, material->getShaderBinding(shaderIndex), localOptions);
	}	
	glUseProgram(glslShader->shader_id);	
	
//	glActiveTexture(GL_TEXTURE0);
	
	for(int i=0; i < cgBinding->textures.size(); i++) {
		int texture_location = glGetUniformLocation(glslShader->shader_id, cgBinding->textures[i].name.c_str());
		glUniform1i(texture_location, 0);
		glBindTexture(GL_TEXTURE_2D, ((OpenGLTexture*)cgBinding->textures[i].texture)->getTextureID());	
	}	
	
	/*
	//			Logger::log("applying %s (%s %s)\n", material->getShader()->getName().c_str(), cgShader->vp->getResourceName().c_str(), cgShader->fp->getResourceName().c_str());
		
	for(int i=0; i < cgBinding->cubemaps.size(); i++) {
		cgGLSetTextureParameter(cgBinding->cubemaps[i].vpParam, ((OpenGLCubemap*)cgBinding->cubemaps[i].cubemap)->getTextureID());
		cgGLEnableTextureParameter(cgBinding->cubemaps[i].vpParam);
	}
	
	cgBinding = (GLSLShaderBinding*)localOptions;
	for(int i=0; i < cgBinding->textures.size(); i++) {
		cgGLSetTextureParameter(cgBinding->textures[i].vpParam, ((OpenGLTexture*)cgBinding->textures[i].texture)->getTextureID());
		cgGLEnableTextureParameter(cgBinding->textures[i].vpParam);
	}			
	
	vector<Texture*> shadowMapTextures = renderer->getShadowMapTextures();
	char texName[32];
	for(int i=0; i< 4; i++) {
		if(i < shadowMapTextures.size()) {
			switch(i) {
				case 0:
					strcpy(texName, "shadowMap0");
					break;
				case 1:
					strcpy(texName, "shadowMap1");
					break;
				case 2:
					strcpy(texName, "shadowMap2");
					break;
				case 3:
					strcpy(texName, "shadowMap3");
					break;							
			}
			cgGLSetTextureParameter(cgGetNamedParameter(cgShader->fp->program, texName), ((OpenGLTexture*)shadowMapTextures[i])->getTextureID());
			cgGLEnableTextureParameter(cgGetNamedParameter(cgShader->fp->program, texName));					
		}
	}
	

	 */
}

void GLSLShaderModule::addParamToProgram(GLSLProgram *program,TiXmlNode *node) {
		bool isAuto = false;
		int autoID = 0;
		int paramType = GLSLProgramParam::PARAM_UNKNOWN;
		void *defaultData = NULL;
		
		if(strcmp(node->ToElement()->Attribute("type"), "auto") == 0) {
			isAuto = true;
			String pid = node->ToElement()->Attribute("id");
			if(pid == "TAU_MODELVIEWPROJ_MATRIX")
				autoID = GLSLProgramParam::TAU_MODELVIEWPROJ_MATRIX;
			else if(pid == "TAU_AREA_LIGHT_POSITION_0")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_0;
			else if(pid == "TAU_AREA_LIGHT_POSITION_1")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_1;
			else if(pid == "TAU_AREA_LIGHT_POSITION_2")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_2;
			else if(pid == "TAU_AREA_LIGHT_POSITION_3")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_3;
			else if(pid == "TAU_AREA_LIGHT_POSITION_4")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_4;
			else if(pid == "TAU_AREA_LIGHT_POSITION_5")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_5;
			else if(pid == "TAU_AREA_LIGHT_POSITION_6")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_6;
			else if(pid == "TAU_AREA_LIGHT_POSITION_7")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_POSITION_7;
			
			else if(pid == "TAU_SPOT_LIGHT_POSITION_0")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_0;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_1")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_1;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_2")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_2;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_3")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_POSITION_3;
			
			
			else if(pid == "TAU_AREA_LIGHT_COLOR_0")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_0;
			else if(pid == "TAU_AREA_LIGHT_COLOR_1")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_1;
			else if(pid == "TAU_AREA_LIGHT_COLOR_2")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_2;
			else if(pid == "TAU_AREA_LIGHT_COLOR_3")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_3;
			else if(pid == "TAU_AREA_LIGHT_COLOR_4")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_4;
			else if(pid == "TAU_AREA_LIGHT_COLOR_5")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_5;
			else if(pid == "TAU_AREA_LIGHT_COLOR_6")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_6;
			else if(pid == "TAU_AREA_LIGHT_COLOR_7")
				autoID = GLSLProgramParam::TAU_AREA_LIGHT_COLOR_7;
			
			else if(pid == "TAU_SPOT_LIGHT_COLOR_0")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_0;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_1")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_1;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_2")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_2;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_3")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_COLOR_3;
			
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_0")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_0;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_1")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_1;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_2")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_2;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_3")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_DIRECTION_3;
			
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_0")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_0;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_1")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_1;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_2")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_2;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_3")
				autoID = GLSLProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_3;		
			
			else if(pid == "TAU_MODELVIEW_MATRIX")
				autoID = GLSLProgramParam::TAU_MODELVIEW_MATRIX;
			else if(pid == "TAU_MODELVIEW_INVERSE_MATRIX")
				autoID = GLSLProgramParam::TAU_MODELVIEW_INVERSE_MATRIX;
			else if(pid == "TAU_EXPOSURE_LEVEL")
				autoID = GLSLProgramParam::TAU_EXPOSURE_LEVEL;
			else if(pid == "TAU_CLEARCOLOR")
				autoID = GLSLProgramParam::TAU_CLEARCOLOR;		
			else if(pid == "TAU_AMBIENTCOLOR")
				autoID = GLSLProgramParam::TAU_AMBIENTCOLOR;				
			else
				isAuto = false;
		} else {
			defaultData = GLSLProgramParam::createParamData(&paramType, node->ToElement()->Attribute("type"), node->ToElement()->Attribute("default"));
		}
		
		program->addParam(node->ToElement()->Attribute("name"), isAuto, autoID, paramType, defaultData);
}

void GLSLShaderModule::reloadPrograms() {
	for(int i=0; i < programs.size(); i++) {
		GLSLProgram *program = programs[i];
		recreateGLSLProgram(program, program->getResourcePath(), program->type);	
	}	
}

void GLSLShaderModule::recreateGLSLProgram(GLSLProgram *prog, String fileName, int type) {
	
	OSFILE *file = OSBasics::open(fileName, "r");
	OSBasics::seek(file, 0, SEEK_END);	
	long progsize = OSBasics::tell(file);
	OSBasics::seek(file, 0, SEEK_SET);
	char *buffer = (char*)malloc(progsize+1);
	memset(buffer, 0, progsize+1);
	OSBasics::read(buffer, progsize, 1, file);
	
	if(type == GLSLProgram::TYPE_VERT) {
		prog->program =  glCreateShader(GL_VERTEX_SHADER);
	} else {
		prog->program =  glCreateShader(GL_FRAGMENT_SHADER);
	}
	
	glShaderSource(prog->program, 1, (const GLchar**)&buffer, 0);
	glCompileShader(prog->program);	
	
	free(buffer);		
	
}

GLSLProgram *GLSLShaderModule::createGLSLProgram(String fileName, int type) {
	GLSLProgram *prog = new GLSLProgram(type);	
	recreateGLSLProgram(prog, fileName, type);	
	programs.push_back(prog);
	return prog;
}

Resource* GLSLShaderModule::createProgramFromFile(String extension, String fullPath) {
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
