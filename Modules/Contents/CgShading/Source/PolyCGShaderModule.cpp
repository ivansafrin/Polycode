/*
 *  PolyCGShader.cpp
 *  Poly
 *
 *  Created by Ivan Safrin on 9/20/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */


#include "PolyCGShaderModule.h"

using namespace Polycode;

CGShaderModule::CGShaderModule() : PolycodeShaderModule() {
    if( cgGLIsProfileSupported(CG_PROFILE_ARBVP1) ) {
		Logger::log("Using vertex profile CG_PROFILE_ARBVP1\n");
        vertexProfile = CG_PROFILE_ARBVP1;
	} else if ( cgGLIsProfileSupported(CG_PROFILE_VP40) ) {
		Logger::log("Using vertex profile CG_PROFILE_VP40\n");
        vertexProfile = CG_PROFILE_VP40;
    } else {
		Logger::log("Error, no required vertex profiles supported by your card\n");
    }
	
	if( cgGLIsProfileSupported(CG_PROFILE_ARBFP1) ) {
		Logger::log("Using fragment profile CG_PROFILE_ARBFP1\n");
        fragmentProfile = CG_PROFILE_ARBFP1;		
    } else if( cgGLIsProfileSupported(CG_PROFILE_FP30) ) {
		Logger::log("Using fragment profile CG_PROFILE_FP30\n");
        fragmentProfile = CG_PROFILE_FP30;
	} else if( cgGLIsProfileSupported(CG_PROFILE_FP20) ) {
		Logger::log("Using fragment profile CG_PROFILE_FP20\n");
        fragmentProfile = CG_PROFILE_FP20;
    } else {
		Logger::log("Error, no required fragment profiles supported by your card\n");
		return;
    }
	
	cgContext = cgCreateContext();		
}

CGShaderModule::~CGShaderModule() {
	cgDestroyContext(cgContext);	
}

bool CGShaderModule::acceptsExtension(String extension) {
	if(extension == "cgvert" || extension == "cgfrag") {
		return true;
	} else {
		return false;
	}
}

String CGShaderModule::getShaderType() {
	return "cg";
}

Shader *CGShaderModule::createShader(TiXmlNode *node) {
	TiXmlNode* pChild, *pChild2, *pChild3;	
	CGProgram *vp = NULL;
	CGProgram *fp = NULL;
	CGShader *retShader = NULL;
	
	for (pChild = node->FirstChild(); pChild != 0; pChild = pChild->NextSibling()) {
		if(strcmp(pChild->Value(), "vp") == 0) {
			vp = (CGProgram*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_PROGRAM, pChild->ToElement()->Attribute("source"));
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
			fp = (CGProgram*)CoreServices::getInstance()->getResourceManager()->getResource(Resource::RESOURCE_PROGRAM, pChild->ToElement()->Attribute("source"));
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
		CGShader *cgShader = new CGShader(vp,fp);
		cgShader->setName(node->ToElement()->Attribute("name"));
		retShader = cgShader;
		shaders.push_back((Shader*)cgShader);
	}
	return retShader;

}

void CGShaderModule::clearShader() {
	cgGLDisableProfile(fragmentProfile);
	cgGLDisableProfile(vertexProfile);	
}

void CGShaderModule::setCGAreaLightPositionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumAreaLights() > lightIndex) {
		vector<LightInfo> areaLights = renderer->getAreaLights();			
		Vector3 lPos(areaLights[lightIndex].position.x,areaLights[lightIndex].position.y,areaLights[lightIndex].position.z);
		lPos = renderer->getCameraMatrix().inverse() * lPos;
		cgGLSetParameter4f(param.cgParam, lPos.x,lPos.y,lPos.z, areaLights[lightIndex].distance);
	} else {
		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}	
}

void CGShaderModule::setCGSpotLightPositionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();		
		Vector3 lPos(spotLights[lightIndex].position.x,spotLights[lightIndex].position.y,spotLights[lightIndex].position.z);
		lPos = renderer->getCameraMatrix().inverse() * lPos;
		cgGLSetParameter4f(param.cgParam, lPos.x,lPos.y,lPos.z, spotLights[lightIndex].distance);
	} else {
		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}	
}

void CGShaderModule::setCGSpotLightDirectionParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();		
		Vector3 lPos(spotLights[lightIndex].dir.x,spotLights[lightIndex].dir.y,spotLights[lightIndex].dir.z);
		lPos = renderer->getCameraMatrix().inverse().rotateVector(lPos);
		cgGLSetParameter3f(param.cgParam, lPos.x,lPos.y,lPos.z);
	} else {
		cgGLSetParameter3f(param.cgParam, 0.0f,0.0f,0.0f);
	}				
}

void CGShaderModule::setCGAreaLightColorParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumAreaLights() > lightIndex) {
		vector<LightInfo> areaLights = renderer->getAreaLights();		
		cgGLSetParameter4f(param.cgParam, areaLights[lightIndex].color.x,areaLights[lightIndex].color.y,areaLights[lightIndex].color.z, areaLights[lightIndex].intensity);
	} else {
		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}
}

void CGShaderModule::setCGSpotLightColorParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumSpotLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();			
		cgGLSetParameter4f(param.cgParam, spotLights[lightIndex].color.x,spotLights[lightIndex].color.y,spotLights[lightIndex].color.z, spotLights[lightIndex].intensity);
	} else {
		cgGLSetParameter4f(param.cgParam, 0,0,0,0);
	}
}

void CGShaderModule::setCGSpotLightTextureMatrixParameter(Renderer *renderer, CGProgramParam &param, int lightIndex) {
	if(renderer->getNumLights() > lightIndex) {
		vector<LightInfo> spotLights = renderer->getSpotLights();			
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadMatrixf((GLfloat*)spotLights[lightIndex].textureMatrix.ml);				
		cgGLSetStateMatrixParameter(param.cgParam, CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_IDENTITY);
		glPopMatrix();
	}					
}



void CGShaderModule::updateCGParam(Renderer *renderer, CGProgramParam &param, ShaderBinding *materialOptions, ShaderBinding *localOptions) {
	if(param.isAuto) {
		switch(param.autoID) {
			case CGProgramParam::TAU_MODELVIEWPROJ_MATRIX:
				cgGLSetStateMatrixParameter(param.cgParam, CG_GL_MODELVIEW_PROJECTION_MATRIX,CG_GL_MATRIX_IDENTITY);
				break;
				
			case CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_0:
				setCGSpotLightTextureMatrixParameter(renderer, param, 0);					
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_1:
				setCGSpotLightTextureMatrixParameter(renderer, param, 1);					
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_2:
				setCGSpotLightTextureMatrixParameter(renderer, param, 2);					
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_3:
				setCGSpotLightTextureMatrixParameter(renderer, param, 3);					
				break;
				
				
			case CGProgramParam::TAU_AMBIENTCOLOR:
				cgGLSetParameter3f(param.cgParam, renderer->ambientColor.r,renderer->ambientColor.g,renderer->ambientColor.b);
				break;
			case CGProgramParam::TAU_CLEARCOLOR:
				cgGLSetParameter3f(param.cgParam, renderer->clearColor.r,renderer->clearColor.g,renderer->clearColor.b);				
				break;				
				
			case CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_0:
				setCGSpotLightDirectionParameter(renderer, param, 0);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_1:
				setCGSpotLightDirectionParameter(renderer, param, 1);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_2:
				setCGSpotLightDirectionParameter(renderer, param, 2);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_3:
				setCGSpotLightDirectionParameter(renderer, param, 3);
				break;
				
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_0:
				setCGAreaLightPositionParameter(renderer, param, 0);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_1:
				setCGAreaLightPositionParameter(renderer, param, 1);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_2:
				setCGAreaLightPositionParameter(renderer, param, 2);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_3:
				setCGAreaLightPositionParameter(renderer, param, 3);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_4:
				setCGAreaLightPositionParameter(renderer, param, 4);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_5:
				setCGAreaLightPositionParameter(renderer, param, 5);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_6:
				setCGAreaLightPositionParameter(renderer, param, 6);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_POSITION_7:
				setCGAreaLightPositionParameter(renderer, param, 7);
				break;				
				
			case CGProgramParam::TAU_SPOT_LIGHT_POSITION_0:
				setCGSpotLightPositionParameter(renderer, param, 0);
				break;				
			case CGProgramParam::TAU_SPOT_LIGHT_POSITION_1:
				setCGSpotLightPositionParameter(renderer, param, 1);
				break;				
			case CGProgramParam::TAU_SPOT_LIGHT_POSITION_2:
				setCGSpotLightPositionParameter(renderer, param, 2);
				break;				
			case CGProgramParam::TAU_SPOT_LIGHT_POSITION_3:
				setCGSpotLightPositionParameter(renderer, param, 3);
				break;				
				
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_0:
				setCGAreaLightColorParameter(renderer, param, 0);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_1:
				setCGAreaLightColorParameter(renderer, param, 1);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_2:
				setCGAreaLightColorParameter(renderer, param, 2);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_3:
				setCGAreaLightColorParameter(renderer, param, 3);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_4:
				setCGAreaLightColorParameter(renderer, param, 4);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_5:
				setCGAreaLightColorParameter(renderer, param, 5);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_6:
				setCGAreaLightColorParameter(renderer, param, 6);
				break;
			case CGProgramParam::TAU_AREA_LIGHT_COLOR_7:
				setCGAreaLightColorParameter(renderer, param, 7);
				break;
				
			case CGProgramParam::TAU_SPOT_LIGHT_COLOR_0:
				setCGSpotLightColorParameter(renderer, param, 0);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_COLOR_1:
				setCGSpotLightColorParameter(renderer, param, 1);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_COLOR_2:
				setCGSpotLightColorParameter(renderer, param, 2);
				break;
			case CGProgramParam::TAU_SPOT_LIGHT_COLOR_3:
				setCGSpotLightColorParameter(renderer, param, 3);
				break;				
				
			case CGProgramParam::TAU_MODELVIEW_MATRIX: {
				cgGLSetStateMatrixParameter(param.cgParam, CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_IDENTITY); }
				break;
			case CGProgramParam::TAU_MODELVIEW_INVERSE_MATRIX:
				cgGLSetStateMatrixParameter(param.cgParam, CG_GL_MODELVIEW_MATRIX,CG_GL_MATRIX_INVERSE_TRANSPOSE);
				break;
			case CGProgramParam::TAU_EXPOSURE_LEVEL:
				cgGLSetParameter1f(param.cgParam, renderer->exposureLevel);
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
			case CGProgramParam::PARAM_FLOAT:
				fval = (float*)paramData;
				cgGLSetParameter1f(param.cgParam, *fval);
				break;
			case CGProgramParam::PARAM_FLOAT3:
				Vector3 *fval3 = (Vector3*)paramData;
				cgGLSetParameter3f(param.cgParam, fval3->x,fval3->y,fval3->z);
				break;
		}
	}
}

bool CGShaderModule::applyShaderMaterial(Renderer *renderer, Material *material, ShaderBinding *localOptions, unsigned int shaderIndex) {	
	
	glEnable(GL_TEXTURE_2D);
	CGShader *cgShader = (CGShader*)material->getShader(shaderIndex);
	CGShaderBinding *cgBinding = (CGShaderBinding*)material->getShaderBinding(shaderIndex);
	
	//			Logger::log("applying %s (%s %s)\n", material->getShader()->getName().c_str(), cgShader->vp->getResourceName().c_str(), cgShader->fp->getResourceName().c_str());
	
	for(int i=0; i < cgBinding->textures.size(); i++) {
		cgGLSetTextureParameter(cgBinding->textures[i].vpParam, ((OpenGLTexture*)cgBinding->textures[i].texture)->getTextureID());
		cgGLEnableTextureParameter(cgBinding->textures[i].vpParam);
	}
	
	for(int i=0; i < cgBinding->cubemaps.size(); i++) {
		cgGLSetTextureParameter(cgBinding->cubemaps[i].vpParam, ((OpenGLCubemap*)cgBinding->cubemaps[i].cubemap)->getTextureID());
		cgGLEnableTextureParameter(cgBinding->cubemaps[i].vpParam);
	}
	
	cgBinding = (CGShaderBinding*)localOptions;
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
	
	cgGLEnableProfile(vertexProfile);
	cgGLBindProgram(cgShader->vp->program);
	
	cgGLEnableProfile(fragmentProfile);
	cgGLBindProgram(cgShader->fp->program);
	
	
	for(int i=0; i < cgShader->vp->params.size(); i++) {
		CGProgramParam param = cgShader->vp->params[i];
		updateCGParam(renderer, param, material->getShaderBinding(shaderIndex), localOptions);
	}
	
	for(int i=0; i < cgShader->fp->params.size(); i++) {
		CGProgramParam param = cgShader->fp->params[i];
		updateCGParam(renderer, param, material->getShaderBinding(shaderIndex), localOptions);
	}
}

void CGShaderModule::addParamToProgram(CGProgram *program,TiXmlNode *node) {
		bool isAuto = false;
		int autoID = 0;
		int paramType = CGProgramParam::PARAM_UNKNOWN;
		void *defaultData = NULL;
		
		if(strcmp(node->ToElement()->Attribute("type"), "auto") == 0) {
			isAuto = true;
			String pid = node->ToElement()->Attribute("id");
			if(pid == "TAU_MODELVIEWPROJ_MATRIX")
				autoID = CGProgramParam::TAU_MODELVIEWPROJ_MATRIX;
			else if(pid == "TAU_AREA_LIGHT_POSITION_0")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_0;
			else if(pid == "TAU_AREA_LIGHT_POSITION_1")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_1;
			else if(pid == "TAU_AREA_LIGHT_POSITION_2")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_2;
			else if(pid == "TAU_AREA_LIGHT_POSITION_3")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_3;
			else if(pid == "TAU_AREA_LIGHT_POSITION_4")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_4;
			else if(pid == "TAU_AREA_LIGHT_POSITION_5")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_5;
			else if(pid == "TAU_AREA_LIGHT_POSITION_6")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_6;
			else if(pid == "TAU_AREA_LIGHT_POSITION_7")
				autoID = CGProgramParam::TAU_AREA_LIGHT_POSITION_7;
			
			else if(pid == "TAU_SPOT_LIGHT_POSITION_0")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_POSITION_0;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_1")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_POSITION_1;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_2")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_POSITION_2;
			else if(pid == "TAU_SPOT_LIGHT_POSITION_3")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_POSITION_3;
			
			
			else if(pid == "TAU_AREA_LIGHT_COLOR_0")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_0;
			else if(pid == "TAU_AREA_LIGHT_COLOR_1")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_1;
			else if(pid == "TAU_AREA_LIGHT_COLOR_2")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_2;
			else if(pid == "TAU_AREA_LIGHT_COLOR_3")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_3;
			else if(pid == "TAU_AREA_LIGHT_COLOR_4")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_4;
			else if(pid == "TAU_AREA_LIGHT_COLOR_5")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_5;
			else if(pid == "TAU_AREA_LIGHT_COLOR_6")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_6;
			else if(pid == "TAU_AREA_LIGHT_COLOR_7")
				autoID = CGProgramParam::TAU_AREA_LIGHT_COLOR_7;
			
			else if(pid == "TAU_SPOT_LIGHT_COLOR_0")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_COLOR_0;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_1")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_COLOR_1;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_2")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_COLOR_2;
			else if(pid == "TAU_SPOT_LIGHT_COLOR_3")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_COLOR_3;
			
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_0")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_0;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_1")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_1;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_2")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_2;		
			else if(pid == "TAU_SPOT_LIGHT_DIRECTION_3")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_DIRECTION_3;
			
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_0")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_0;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_1")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_1;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_2")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_2;
			else if(pid == "TAU_SPOT_LIGHT_TEXTUREMATRIX_3")
				autoID = CGProgramParam::TAU_SPOT_LIGHT_TEXTUREMATRIX_3;		
			
			else if(pid == "TAU_MODELVIEW_MATRIX")
				autoID = CGProgramParam::TAU_MODELVIEW_MATRIX;
			else if(pid == "TAU_MODELVIEW_INVERSE_MATRIX")
				autoID = CGProgramParam::TAU_MODELVIEW_INVERSE_MATRIX;
			else if(pid == "TAU_EXPOSURE_LEVEL")
				autoID = CGProgramParam::TAU_EXPOSURE_LEVEL;
			else if(pid == "TAU_CLEARCOLOR")
				autoID = CGProgramParam::TAU_CLEARCOLOR;		
			else if(pid == "TAU_AMBIENTCOLOR")
				autoID = CGProgramParam::TAU_AMBIENTCOLOR;				
			else
				isAuto = false;
		} else {
			defaultData = CGProgramParam::createParamData(&paramType, node->ToElement()->Attribute("type"), node->ToElement()->Attribute("default"));
		}
		
		program->addParam(node->ToElement()->Attribute("name"), isAuto, autoID, paramType, defaultData);
}

void CGShaderModule::reloadPrograms() {
	for(int i=0; i < programs.size(); i++) {
		CGProgram *program = programs[i];
		recreateCGProgram(program, program->getResourcePath(), program->type);	
	}	
}

void CGShaderModule::recreateCGProgram(CGProgram *prog, String fileName, int type) {
	
	OSFILE *file = OSBasics::open(fileName, "r");
	OSBasics::seek(file, 0, SEEK_END);	
	long progsize = OSBasics::tell(file);
	OSBasics::seek(file, 0, SEEK_SET);
	char *buffer = (char*)malloc(progsize+1);
	memset(buffer, 0, progsize+1);
	OSBasics::read(buffer, progsize, 1, file);
	
	if(type == CGProgram::TYPE_VERT) {
		prog->program = cgCreateProgram(cgContext, CG_SOURCE, buffer, vertexProfile, NULL, NULL);
	} else {
		prog->program = cgCreateProgram(cgContext, CG_SOURCE, buffer, fragmentProfile, NULL, NULL);		
	}
	
	free(buffer);	
	
	if(prog->program == NULL) {
		Logger::log("SHADER ERROR!\n");
		Logger::log("%s\n",cgGetErrorString(cgGetError()));
		Logger::log("%s\n",cgGetLastListing(cgContext));
	}
	
	cgGLLoadProgram(prog->program);	
	
}

CGProgram *CGShaderModule::createCGProgram(String fileName, int type) {
	CGProgram *prog = new CGProgram(type);	
	recreateCGProgram(prog, fileName, type);	
	programs.push_back(prog);
	return prog;
}

Resource* CGShaderModule::createProgramFromFile(String extension, String fullPath) {
	if(extension == "cgvert") {
		Logger::log("Adding CG vertex program %s\n", fullPath.c_str());				
		return createCGProgram(fullPath, CGProgram::TYPE_VERT);
	}
	if(extension == "cgfrag") {
		Logger::log("Adding CG fragment program %s\n", fullPath.c_str());
		return createCGProgram(fullPath, CGProgram::TYPE_FRAG);								
	}
	return NULL;
}
