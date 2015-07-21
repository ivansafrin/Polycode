
/*
 Copyright (C) 2015 by Ivan Safrin
 
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

#include "PolyOpenGLGraphicsInterface.h"
#include "OSBasics.h"
#include "PolyLogger.h"
#include "PolyCoreServices.h"

using namespace Polycode;

OpenGLGraphicsInterface::OpenGLGraphicsInterface() {

}

OpenGLGraphicsInterface::~OpenGLGraphicsInterface() {
    
}

void OpenGLGraphicsInterface::setUniformMatrix(GLint paramLocation, const Polycode::Matrix4& matrix) {
#ifdef POLYCODE_NUMBER_IS_SINGLE
    glUniformMatrix4fv(paramLocation, 1, false, matrix.ml);
#else
    // no glUniformMatrix4dv on some systems
    float copyMatrix[16];
    for(int i=0; i < 16; i++) {
        copyMatrix[i] = matrix.ml[i];
    }
    glUniformMatrix4fv(paramLocation, 1, false, copyMatrix);
#endif
}

void OpenGLGraphicsInterface::setParamInShader(Shader *shader, const ProgramParam &param, LocalShaderParam *localParam) {

    // TODO: ALSO DO NOT LOOK UP BY STRING!
    
    GLuint shaderID = *((GLuint*) shader->platformData);
    int paramLocation = glGetUniformLocation(shaderID, param.name.c_str());
    
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
        case ProgramParam::PARAM_MATRIX:
            if(localParam) {
                if(localParam->arraySize > 0) {
                    Matrix4 *matPointer = (Matrix4*)localParam->data;
                    std::vector<float> matrixData;
                    for(int i=0; i < localParam->arraySize; i++) {
                        for(int j=0; j < 16; j++) {
                            matrixData.push_back(matPointer[i].ml[j]);
                        }
                    }
                    
                    glUniformMatrix4fv(paramLocation, localParam->arraySize, false, &matrixData[0]);
                    
                } else {
                    setUniformMatrix(paramLocation, localParam->getMatrix4());
                }
            } else {
                Matrix4 defaultMatrix;
                setUniformMatrix(paramLocation, defaultMatrix);
            }
            break;
    }
    
}

void OpenGLGraphicsInterface::createTexture(Texture *texture, int filteringMode, int anisotropy, bool createMipmaps) {
    if(!texture->platformData) {
        texture->platformData = (void*) new GLuint;
        glGenTextures(1, (GLuint*)texture->platformData);
    }
    
    GLuint textureID = *((GLuint*)texture->platformData);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    if(texture->clamp) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
    GLenum glTextureType;
    GLuint glTextureFormat;
    GLenum pixelType;
    
    switch(texture->type) {
        case Image::IMAGE_RGB:
            glTextureType = GL_RGB;
            glTextureFormat = GL_RGB;
            pixelType = GL_UNSIGNED_BYTE;
            break;
        case Image::IMAGE_FP16:
            glTextureType = GL_RGB;
            glTextureFormat = GL_RGB;
            pixelType = GL_FLOAT;
            break;
        default:
            glTextureType = GL_RGBA;
            glTextureFormat = GL_RGBA;	
            pixelType = GL_UNSIGNED_BYTE;	
            break;
    }
    
    
    switch(filteringMode) {
        case Renderer::TEX_FILTERING_LINEAR:
            
            if(anisotropy > 0) {
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
            }
            
            if(createMipmaps) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                if(texture->getTextureData()) {
                    gluBuild2DMipmaps(GL_TEXTURE_2D, glTextureFormat, texture->getWidth(), texture->getHeight(), glTextureType, pixelType, texture->getTextureData());
                }
            } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                if(texture->getTextureData()) {
                    glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, texture->getWidth(), texture->getHeight(), 0, glTextureType, pixelType, texture->getTextureData());
                }
            }
            break;
        case Renderer::TEX_FILTERING_NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);		
            if(texture->getTextureData()) {
                glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, texture->getWidth(), texture->getHeight(), 0, glTextureType, pixelType, texture->getTextureData());
            }			
            break;
    }
}

void OpenGLGraphicsInterface::setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height) {
    glViewport(x, y, width, height);
}

void OpenGLGraphicsInterface::createProgram(ShaderProgram *program) {

    if(!program->platformData) {
        program->platformData = (void*) new GLuint;
    }

    GLuint programID = *((GLuint*)program->platformData);
    if(programID != 0) {
        glDeleteShader(programID);
    }
    
    OSFILE *file = OSBasics::open(program->getResourcePath(), "rb");
    if (!file) {
        Logger::log("Error: shader file %s not found\n", program->getResourcePath().c_str());
        *((GLuint*)program->platformData) = -1;
        return;
    }
    
    OSBasics::seek(file, 0, SEEK_END);
    long progsize = OSBasics::tell(file);
    OSBasics::seek(file, 0, SEEK_SET);
    char *buffer = (char*)malloc(progsize+1);
    memset(buffer, 0, progsize+1);
    OSBasics::read(buffer, progsize, 1, file);
    OSBasics::close(file);
    
    if( program->type == ShaderProgram::TYPE_VERT) {
        programID = glCreateShader(GL_VERTEX_SHADER);
    } else {
        programID = glCreateShader(GL_FRAGMENT_SHADER);
    }
    
    glShaderSource(programID, 1, (const GLchar**)&buffer, 0);
    glCompileShader(programID);
    
    GLint compiled = true;
    glGetShaderiv(programID, GL_COMPILE_STATUS, &compiled);
    
    if(!compiled) {
        GLint length;
        GLchar* log;
        glGetShaderiv(programID, GL_INFO_LOG_LENGTH, &length);
        
        log = (GLchar*)malloc(length);
        glGetShaderInfoLog(programID, length, &length, log);
        
        Services()->getLogger()->logBroadcast("["+program->getResourcePath()+"] GLSL ERROR:" + String(log));
        free(log);
    }	
    free(buffer);
    
    *((GLuint*)program->platformData) = programID;
}

void OpenGLGraphicsInterface::createShader(Shader *shader) {
    
    shader->expectedParams.clear();
    shader->expectedTextures.clear();
    shader->expectedCubemaps.clear();
    shader->expectedAttributes.clear();
    
    if(!shader->platformData) {
        shader->platformData = (void*) new GLuint;
    }
    
    GLuint shaderID = *((GLuint*)shader->platformData);
    
    if(shaderID != 0) {
        glDetachShader(shaderID, *((GLuint*)shader->fragmentProgram->platformData));
        glDetachShader(shaderID, *((GLuint*)shader->vertexProgram->platformData));
        glDeleteProgram(shaderID);
    }
    
    shaderID = glCreateProgram();
    
    glAttachShader(shaderID, *((GLuint*)shader->fragmentProgram->platformData));
    glAttachShader(shaderID, *((GLuint*)shader->vertexProgram->platformData));
    glLinkProgram(shaderID);


    GLint result;
    glGetProgramiv( shaderID, GL_LINK_STATUS, &result);
    
    if(result == GL_INVALID_VALUE || result == GL_INVALID_OPERATION) {
        Services()->getLogger()->logBroadcast("ERROR: Error linking shader. Invalid shader program.");
    }

    int total = -1;
    glGetProgramiv( shaderID, GL_ACTIVE_UNIFORMS, &total );
    for(int i=0; i < total; i++)  {
        int name_len=-1, num=-1;
        GLenum type = GL_ZERO;
        char name[128];
        glGetActiveUniform(shaderID, GLuint(i), sizeof(name)-1, &name_len, &num, &type, name );
        name[name_len] = 0;
        
        switch(type) {
            case GL_SAMPLER_2D:
                shader->expectedTextures.push_back(String(name));
                break;
            case GL_SAMPLER_CUBE:
                shader->expectedCubemaps.push_back(String(name));
                break;
            default:
                ProgramParam param;
                param.name = String(name);
                param.type = getPolycodeParamType(type);
                shader->expectedParams.push_back(param);
            break;
        }
    }
    
    total = -1;
    glGetProgramiv( shaderID, GL_ACTIVE_ATTRIBUTES, &total );
    
    for(GLuint i=0; i < total; i++)  {
        
        int name_len=-1, num=-1;
        GLenum type = GL_ZERO;
        char name[128];
        
        glGetActiveAttrib(shaderID, i, sizeof(name)-1, &name_len, &num, &type, name);
        name[name_len] = 0;

        ProgramAttribute attribute;
        attribute.name = String(name);
        attribute.size = getAttributeSize(type);
        shader->expectedAttributes.push_back(attribute);
    }
    
    
     *((GLuint*)shader->platformData) = shaderID;
    
}

void OpenGLGraphicsInterface::clearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer) {
    GLbitfield clearMask = 0;
    
    if(colorBuffer) {
        clearMask = clearMask | GL_COLOR_BUFFER_BIT;
    }
    
    if(depthBuffer) {
        clearMask = clearMask | GL_DEPTH_BUFFER_BIT;
    }
    
    if(stencilBuffer) {
        clearMask = clearMask | GL_STENCIL_BUFFER_BIT;
    }
    
    
    glClear(clearMask);
}

int OpenGLGraphicsInterface::getAttributeSize(int glType) {
    switch(glType) {
        case GL_FLOAT:
            return 1;
        break;
        case GL_FLOAT_VEC2:
            return 2;
        break;
        case GL_FLOAT_VEC3:
            return 3;
        break;
        case GL_FLOAT_VEC4:
            return 4;
        break;
        case GL_FLOAT_MAT2:
            return 4;
        break;
        case GL_FLOAT_MAT3:
            return 9;
        break;
        case GL_FLOAT_MAT4:
            return 16;
        break;
    }
    return 0;
}

int OpenGLGraphicsInterface::getPolycodeParamType(int glType) {
    switch(glType) {
        case GL_FLOAT:
            return ProgramParam::PARAM_NUMBER;
            break;
        case GL_FLOAT_VEC2:
            return ProgramParam::PARAM_VECTOR2;
            break;
        case GL_FLOAT_VEC3:
            return ProgramParam::PARAM_VECTOR3;
            break;
        case GL_FLOAT_VEC4:
            return ProgramParam::PARAM_COLOR;
            break;
        case GL_INT:
            return ProgramParam::PARAM_NUMBER;
            break;
        case GL_INT_VEC2:
            return ProgramParam::PARAM_VECTOR2;
            break;
        case GL_INT_VEC3:
            return ProgramParam::PARAM_VECTOR3;
            break;
        case GL_INT_VEC4:
            return ProgramParam::PARAM_COLOR;
            break;
        case GL_BOOL:
            return ProgramParam::PARAM_NUMBER;
            break;
        case GL_BOOL_VEC2:
            return ProgramParam::PARAM_VECTOR2;
            break;
        case GL_BOOL_VEC3:
            return ProgramParam::PARAM_VECTOR3;
            break;
        case GL_BOOL_VEC4:
            return ProgramParam::PARAM_COLOR;
            break;
        case GL_FLOAT_MAT2:
            return ProgramParam::PARAM_MATRIX;
            break;
        case GL_FLOAT_MAT3:
            return ProgramParam::PARAM_MATRIX;		
            break;
        case GL_FLOAT_MAT4:
            return ProgramParam::PARAM_MATRIX;		
            break;
        default:
            return ProgramParam::PARAM_UNKNOWN;
            break;
    }
}