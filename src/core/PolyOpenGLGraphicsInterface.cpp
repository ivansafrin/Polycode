
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

#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyCoreServices.h"
#include <stdlib.h>

using namespace Polycode;

OpenGLGraphicsInterface::OpenGLGraphicsInterface() {
    lineSmooth = false;
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

void OpenGLGraphicsInterface::setParamInShader(Shader *shader, ProgramParam *param, LocalShaderParam *localParam) {
    
    GLuint paramLocation = *((GLuint*) param->platformData);
    
    switch(param->type) {
        case ProgramParam::PARAM_NUMBER:
            if(localParam) {
                
                if(localParam->arraySize > 0) {
                    
                    GLfloat *data = (GLfloat*) malloc(sizeof(GLfloat) * localParam->arraySize);
                    for(int i=0; i < localParam->arraySize; i++ ){
                        Number *dataPtr = (Number*)localParam->data;
                        data[i] = dataPtr[i];
                    }
                    glUniform1fv(paramLocation, localParam->arraySize, data);
                    free(data);
                    
                } else {
                    glUniform1f(paramLocation, localParam->getNumber());
                }
                
            } else {
                glUniform1f(paramLocation, 0.0f);
            }
            break;
        case ProgramParam::PARAM_VECTOR2:
            if(localParam) {
                
                if(localParam->arraySize > 0) {
                    
                    GLfloat *data = (GLfloat*) malloc(sizeof(GLfloat) * localParam->arraySize * 2);
                    for(int i=0; i < localParam->arraySize; i++ ){
                        Vector2 *dataPtr = (Vector2*)localParam->data;
                        data[(i*2)] = dataPtr[i].x;
                        data[(i*2)+1] = dataPtr[i].y;
                    }
                    glUniform2fv(paramLocation, localParam->arraySize, data);
                    free(data);
                    
                } else {
                    Vector2 vec2 = localParam->getVector2();
                    glUniform2f(paramLocation, vec2.x, vec2.y);
                }
                
            } else {
                glUniform2f(paramLocation, 0.0f, 0.0f);
            }
            break;
        case ProgramParam::PARAM_VECTOR3:
            if(localParam) {
                
                if(localParam->arraySize > 0) {
                    
                    GLfloat *data = (GLfloat*) malloc(sizeof(GLfloat) * localParam->arraySize * 3);
                    for(int i=0; i < localParam->arraySize; i++ ){
                        Vector3 *dataPtr = (Vector3*)localParam->data;
                        data[(i*3)] = dataPtr[i].x;
                        data[(i*3)+1] = dataPtr[i].y;
                        data[(i*3)+2] = dataPtr[i].z;
                    }
                    glUniform3fv(paramLocation, localParam->arraySize, data);
                    free(data);
                    
                } else {
                    Vector3 vec3 = localParam->getVector3();
                    glUniform3f(paramLocation, vec3.x, vec3.y, vec3.z);
                }
                
            } else {
                glUniform3f(paramLocation, 0.0f, 0.0f, 0.0f);
            }
            break;
        case ProgramParam::PARAM_COLOR:
            if(localParam) {
                
                if(localParam->arraySize > 0) {
                    
                    GLfloat *data = (GLfloat*) malloc(sizeof(GLfloat) * localParam->arraySize * 4);
                    for(int i=0; i < localParam->arraySize; i++ ){
                        Color *dataPtr = (Color*)localParam->data;
                        data[(i*3)] = dataPtr[i].r;
                        data[(i*3)+1] = dataPtr[i].g;
                        data[(i*3)+2] = dataPtr[i].b;
                        data[(i*3)+3] = dataPtr[i].a;
                    }
                    glUniform4fv(paramLocation, localParam->arraySize, data);
                    free(data);
                    
                } else {
                    Color color = localParam->getColor();
                    glUniform4f(paramLocation, color.r, color.g, color.b, color.a);
                }
                
            } else {
                glUniform4f(paramLocation, 1.0f, 1.0f, 1.0f, 1.0f);
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
        case ProgramParam::PARAM_TEXTURE:
            glEnable(GL_TEXTURE_2D);
            glActiveTexture(GL_TEXTURE0 + textureIndex);
            glUniform1i(paramLocation, textureIndex);
            if(localParam) {
                Texture* texture = localParam->getTexture();
                if(texture) {
                    if(texture->platformData) {
                        glBindTexture(GL_TEXTURE_2D, *((GLuint*) texture->platformData));
                    }
                } else {
                    glBindTexture(GL_TEXTURE_2D, 0);                    
                }
            } else {
                glBindTexture(GL_TEXTURE_2D, 0);
            }
            textureIndex++;
        break;
        case ProgramParam::PARAM_CUBEMAP:
            // RENDERER_TODO
        break;
    }
}

void OpenGLGraphicsInterface::destroyBuffer(RenderDataArray *array) {
    if(array->platformData) {
        GLuint vboID = *((GLuint*)array->platformData);
        glDeleteBuffers(1, &vboID);
        delete ((GLuint*)array->platformData);
        array->platformData = NULL;
    }
}

void OpenGLGraphicsInterface::createIndexBuffer(IndexDataArray *dataArray) {
    destroyBuffer(dataArray);
    
    if(dataArray->getDataSize() == 0) {
        return;
    }
    
    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataArray->getDataSize() * sizeof(PolyRendererIndexType), dataArray->getArrayData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    dataArray->platformData = (void*)(new GLuint);
    *((GLuint*)dataArray->platformData) = bufferID;
}

void OpenGLGraphicsInterface::createVertexBuffer(VertexDataArray *array) {
    destroyBuffer(array);
    if(array->getDataSize() == 0) {
        return;
    }
    GLuint bufferID;
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, array->getDataSize() * sizeof(PolyRendererVertexType), array->getArrayData(), GL_STATIC_DRAW);
    array->platformData = (void*)(new GLuint);
    *((GLuint*)array->platformData) = bufferID;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLGraphicsInterface::createSubmeshBuffers(MeshGeometry *submesh) {
    createVertexBuffer(&submesh->vertexPositionArray);
    createVertexBuffer(&submesh->vertexTexCoordArray);
    createVertexBuffer(&submesh->vertexNormalArray);
    createVertexBuffer(&submesh->vertexColorArray);
    createVertexBuffer(&submesh->vertexTangentArray);
    createVertexBuffer(&submesh->vertexBoneIndexArray);
    createVertexBuffer(&submesh->vertexBoneWeightArray);
    createVertexBuffer(&submesh->vertexTexCoord2Array);
    createVertexBuffer(&submesh->vertexBoneIndexArray);
    createVertexBuffer(&submesh->customVertexArray1);
    createVertexBuffer(&submesh->customVertexArray2);
    createVertexBuffer(&submesh->customVertexArray3);
    createVertexBuffer(&submesh->customVertexArray4);
    createIndexBuffer(&submesh->indexArray);
}

void OpenGLGraphicsInterface::destroySubmeshBufferData(void *platformData) {
    GLuint vboID = *((GLuint*)platformData);
    glDeleteBuffers(1, &vboID);
    delete ((GLuint*)platformData);
}

void OpenGLGraphicsInterface::drawSubmeshBuffers(MeshGeometry *submesh, Shader *shader) {
    
    static std::vector<int> enabledAttributes;
    enabledAttributes.reserve(16);
    
    for(int i=0; i < shader->expectedAttributes.size(); i++) {
        VertexDataArray *targetArray = NULL;
        switch(shader->expectedAttributes[i].arrayType) {
            case RenderDataArray::VERTEX_DATA_ARRAY:
                targetArray = &submesh->vertexPositionArray;
            break;
            case RenderDataArray::NORMAL_DATA_ARRAY:
                targetArray = &submesh->vertexNormalArray;
            break;
            case RenderDataArray::TEXCOORD_DATA_ARRAY:
                targetArray = &submesh->vertexTexCoordArray;
            break;
            case RenderDataArray::TEXCOORD2_DATA_ARRAY:
                targetArray = &submesh->vertexTexCoord2Array;
            break;
            case RenderDataArray::BONE_INDEX_DATA_ARRAY:
                targetArray = &submesh->vertexBoneIndexArray;
            break;
            case RenderDataArray::BONE_WEIGHT_DATA_ARRAY:
                targetArray = &submesh->vertexBoneWeightArray;
            break;
            case RenderDataArray::TANGENT_DATA_ARRAY:
                targetArray = &submesh->vertexTangentArray;
            break;
            case RenderDataArray::COLOR_DATA_ARRAY:
                targetArray = &submesh->vertexColorArray;
            break;
            case RenderDataArray::CUSTOM_DATA_ARRAY1:
                targetArray = &submesh->customVertexArray1;
            break;
            case RenderDataArray::CUSTOM_DATA_ARRAY2:
                targetArray = &submesh->customVertexArray2;
            break;
            case RenderDataArray::CUSTOM_DATA_ARRAY3:
                targetArray = &submesh->customVertexArray3;
               break;
            case RenderDataArray::CUSTOM_DATA_ARRAY4:
                targetArray = &submesh->customVertexArray4;
            break;
        }
        
        if(targetArray) {
            if(targetArray->platformData) {
                int bufferIndex = *((GLuint*)targetArray->platformData);
                int attributeLocation = *((GLuint*)shader->expectedAttributes[i].platformData);
                glBindBuffer(GL_ARRAY_BUFFER, bufferIndex);
                glVertexAttribPointer(attributeLocation, targetArray->getCountPerVertex(), GL_FLOAT, GL_FALSE, 0, NULL);
                glEnableVertexAttribArray(attributeLocation);
                enabledAttributes.push_back(attributeLocation);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
            }
        }
    }
    
    if(submesh->indexedMesh) {
        if(submesh->indexArray.platformData) {
           glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, *((GLuint*)submesh->indexArray.platformData));
           glDrawElements(getGLDrawMode(submesh->meshType), submesh->indexArray.getDataSize(), GL_UNSIGNED_INT, NULL);
           glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    } else {
        glDrawArrays(getGLDrawMode(submesh->meshType), 0, submesh->getVertexCount());
    }
    
    for(int i=0; i < enabledAttributes.size(); i++) {
        glDisableVertexAttribArray(enabledAttributes[i]);
    }
    enabledAttributes.clear();
}

void OpenGLGraphicsInterface::setBlendingMode(unsigned int blendingMode) {
    if(blendingMode == Renderer::BLEND_MODE_NONE) {
        glDisable(GL_BLEND);
        return;
    } else {
        glEnable(GL_BLEND);
    }
    
    switch(blendingMode) {
        case Renderer::BLEND_MODE_NORMAL:
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case Renderer::BLEND_MODE_LIGHTEN:
            glBlendFunc (GL_SRC_ALPHA, GL_ONE);
            break;
        case Renderer::BLEND_MODE_COLOR:
            glBlendFunc (GL_DST_COLOR, GL_SRC_COLOR);
            break;
        case Renderer::BLEND_MODE_PREMULTIPLIED:
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case Renderer::BLEND_MODE_MULTIPLY:
            glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
            break;
        default:
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
    }
}

void OpenGLGraphicsInterface::beginDrawCall() {
    textureIndex = 0;
#ifndef STRICT_OPENGLES2
    if(lineSmooth) {
        glEnable(GL_LINE_SMOOTH);
    }
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
#endif
}

void OpenGLGraphicsInterface::endDrawCall() {
//    glUseProgram(0);
//    currentShaderID = -1;
}

void OpenGLGraphicsInterface::useShader(Shader *shader) {
    GLuint shaderID = *((GLuint*) shader->platformData);
    if(shaderID != currentShaderID) {
        glUseProgram(shaderID);
        currentShaderID = shaderID;
    }
}

void OpenGLGraphicsInterface::setAttributeInShader(Shader *shader, ProgramAttribute *attribute, AttributeBinding *attributeBinding) {
    GLuint attribLocation = *((GLuint*) attribute->platformData);
    
    if(attributeBinding->vertexData->platformData) {
        GLuint bufferID = *((GLuint*) attributeBinding->vertexData->platformData);
        glBindBuffer(GL_ARRAY_BUFFER, bufferID);
        glVertexAttribPointer(attribLocation, attributeBinding->vertexData->countPerVertex, GL_FLOAT, false, 0, NULL);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    } else {
        glVertexAttribPointer(attribLocation, attributeBinding->vertexData->countPerVertex, GL_FLOAT, false, 0, attributeBinding->vertexData->data.data());
    }
    
    glEnableVertexAttribArray(attribLocation);
}

void OpenGLGraphicsInterface::disableAttribute(Shader *shader, const ProgramAttribute &attribute) {
    GLuint attribLocation = *((GLuint*) attribute.platformData);
    glDisableVertexAttribArray(attribLocation);
}

void OpenGLGraphicsInterface::enableScissor(bool val) {
    if(val) {
        glEnable(GL_SCISSOR_TEST);
    } else {
        glDisable(GL_SCISSOR_TEST);
    }
}

void OpenGLGraphicsInterface::setScissorBox(const Polycode::Rectangle &box) {
    glScissor(box.x, box.y, box.w, box.h);
    
}

void OpenGLGraphicsInterface::setWireframeMode(bool val) {
#ifndef STRICT_OPENGLES2
    if(val) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
    }
#endif
}

GLenum OpenGLGraphicsInterface::getGLDrawMode(int polycodeMode) {
    switch(polycodeMode) {
        case MeshGeometry::POINT_MESH:
            return GL_POINTS;
        break;
        case MeshGeometry::LINE_STRIP_MESH:
            return GL_LINE_STRIP;
        break;
        case MeshGeometry::LINE_LOOP_MESH:
            return GL_LINE_LOOP;
        break;
        case MeshGeometry::LINE_MESH:
            return GL_LINES;
        break;
        case MeshGeometry::TRISTRIP_MESH:
            return GL_TRIANGLE_STRIP;
        break;
        case MeshGeometry::TRIFAN_MESH:
            return GL_TRIANGLE_FAN;
        break;
        case MeshGeometry::TRI_MESH:
            return GL_TRIANGLES;
        break;
    }
    
    return GL_TRIANGLES;
}

void OpenGLGraphicsInterface::createRenderBuffer(RenderBuffer *renderBuffer) {
    if(!renderBuffer->platformData) {
        renderBuffer->platformData = (void*) new GLuint;
        glGenFramebuffers(1, (GLuint*)renderBuffer->platformData);
        glBindFramebuffer(GL_FRAMEBUFFER, *((GLuint*)renderBuffer->platformData));
    }
    
    renderBuffer->colorTexture->framebufferTexture = true;
    createTexture(renderBuffer->colorTexture);
    
    if(renderBuffer->depthTexture) {
        renderBuffer->depthBufferPlatformData = (void*) new GLuint;
        glGenRenderbuffers(1, (GLuint*)renderBuffer->depthBufferPlatformData);
        glBindRenderbuffer(GL_FRAMEBUFFER, *((GLuint*)renderBuffer->depthBufferPlatformData));
        glRenderbufferStorage(GL_RENDERBUFFER, GL_COLOR_ATTACHMENT0, renderBuffer->getWidth(), renderBuffer->getHeight());
    }
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *((GLuint*)renderBuffer->colorTexture->platformData), 0);
    
    
    if(renderBuffer->depthTexture) {
        
        
        renderBuffer->depthTexture->framebufferTexture = true;
        renderBuffer->depthTexture->depthTexture = true;
        renderBuffer->depthTexture->type = renderBuffer->colorTexture->type;
        renderBuffer->depthTexture->filteringMode = Texture::FILTERING_LINEAR;
        createTexture(renderBuffer->depthTexture);
        
        if(renderBuffer->colorTexture->type == Image::IMAGE_FP16) {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, renderBuffer->getWidth(), renderBuffer->getHeight());
            
        } else {
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, renderBuffer->getWidth(), renderBuffer->getHeight());
        }
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *((GLuint*)renderBuffer->depthTexture->platformData), 0);
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLGraphicsInterface::destroyRenderBuffer(RenderBuffer *renderBuffer) {
    if(!renderBuffer) {
        return;
    }
    glDeleteFramebuffers(1, (GLuint*)renderBuffer->platformData);
    if(renderBuffer->colorTexture) {
        destroyTexture(renderBuffer->colorTexture);
    }
    if(renderBuffer->depthTexture) {
        destroyTexture(renderBuffer->depthTexture);
        glDeleteRenderbuffers(1, (GLuint*)renderBuffer->depthBufferPlatformData);
        delete (GLuint*)renderBuffer->depthBufferPlatformData;
    }
    delete (GLuint*)renderBuffer->platformData;
    delete renderBuffer;
}

void OpenGLGraphicsInterface::bindRenderBuffer(RenderBuffer *renderBuffer) {
    if(renderBuffer) {
        glBindFramebuffer(GL_FRAMEBUFFER, *((GLuint*) renderBuffer->platformData));
    } else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void OpenGLGraphicsInterface::destroyTexture(Texture *texture) {
    glDeleteTextures(1, (GLuint*)texture->platformData);
    delete (GLuint*)texture->platformData;
    delete texture;
}

void OpenGLGraphicsInterface::createTexture(Texture *texture) {
    
    
    if(!texture->platformData) {
        texture->platformData = (void*) new GLuint;
        glGenTextures(1, (GLuint*)texture->platformData);
    }
    
    
    GLuint textureID = *((GLuint*)texture->platformData);
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    if(texture->clamp) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    } else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
    GLenum glTextureType;
    GLuint glTextureFormat;
    GLenum pixelType;
    
    switch(texture->type) {
        case Image::IMAGE_RGB:
#ifdef BGRA_TEXTURE_FORMAT
            glTextureType = GL_BGRA;
#else
            glTextureType = GL_RGBA;
#endif
            glTextureFormat = GL_RGB;
            pixelType = GL_UNSIGNED_BYTE;
            break;
        case Image::IMAGE_FP16:
#ifdef BGRA_TEXTURE_FORMAT
            glTextureType = GL_BGRA;
#else
            glTextureType = GL_RGBA;
#endif
#if defined(GL_RGBA16F_EXT)
            glTextureFormat = GL_RGBA16F_EXT;
#elif defined(GL_RGBA16F_ARB)
            glTextureFormat = GL_RGBA16F_ARB;
#else
            glTextureFormat = GL_RGBA16;
#endif
            pixelType = GL_FLOAT;
            break;
        default:
#ifdef BGRA_TEXTURE_FORMAT
            glTextureType = GL_BGRA;
#else
            glTextureType = GL_RGBA;
#endif
            glTextureFormat = GL_RGBA;
            pixelType = GL_UNSIGNED_BYTE;	
            break;
    }
    
    if(texture->depthTexture) {
        glTextureType = GL_DEPTH_COMPONENT;
        
        if(texture->type == Image::IMAGE_FP16) {
            pixelType = GL_FLOAT;
            glTextureFormat = GL_DEPTH_COMPONENT16;
        } else {
            pixelType = GL_UNSIGNED_BYTE;
            glTextureFormat = GL_DEPTH_COMPONENT;
        }
        
      //  glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_LUMINANCE);
    }
    
    switch(texture->filteringMode) {
        case Texture::FILTERING_LINEAR:
            
            if(texture->anisotropy > 0 && !texture->framebufferTexture) {
#ifndef STRICT_OPENGLES2
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, texture->anisotropy);
#endif
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            if(texture->createMipmaps) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            
            break;
        case Texture::FILTERING_NEAREST:
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            
            if(texture->createMipmaps) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            } else {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            }
            break;
    }
    
    if(texture->framebufferTexture) {
        glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, texture->getWidth(), texture->getHeight(), 0, glTextureType, pixelType, NULL);
        
    } else {
        if(texture->getTextureData()) {
            glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, texture->getWidth(), texture->getHeight(), 0, glTextureType, pixelType, texture->getTextureData());
        }
    }
    
    if(texture->createMipmaps && !texture->framebufferTexture) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLGraphicsInterface::setViewport(unsigned int x,unsigned  int y,unsigned  int width, unsigned height) {
    glViewport(x, y, width, height);
}

void OpenGLGraphicsInterface::destroyProgram(ShaderProgram *program) {
    if(program->platformData) {
        GLuint programID = *((GLuint*)program->platformData);
        glDeleteShader(programID);
        delete ((GLuint*)program->platformData);
    }
    delete program;
}

void OpenGLGraphicsInterface::createProgram(ShaderProgram *program) {

    if(!program->platformData) {
        program->platformData = (void*) new GLuint;
    }

    GLuint programID = *((GLuint*)program->platformData);
    if(programID != 0) {
        glDeleteShader(programID);
    }
    
    CoreFile *file = Services()->getCore()->openFile(program->getResourcePath(), "rb");
    if (!file) {
        Logger::log("Error: shader file %s not found\n", program->getResourcePath().c_str());
        *((GLuint*)program->platformData) = -1;
        return;
    }
    
    file->seek(0, SEEK_END);
    long progsize = file->tell();
    file->seek(0, SEEK_SET);
    char *buffer = (char*)malloc(progsize+1);
    memset(buffer, 0, progsize+1);
    file->read(buffer, progsize, 1);
    
    Services()->getCore()->closeFile(file);
    
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

void OpenGLGraphicsInterface::destroyShader(Shader *shader) {
    if(shader->platformData) {
        GLuint shaderID = *((GLuint*)shader->platformData);
        glDetachShader(shaderID, *((GLuint*)shader->fragmentProgram->platformData));
        glDetachShader(shaderID, *((GLuint*)shader->vertexProgram->platformData));
        glDeleteProgram(shaderID);
        delete ((GLuint*)shader->platformData);
    }
    delete shader;
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
   
        int paramLocation = glGetUniformLocation(shaderID, name);
        
        ProgramParam param;
        param.name = String(name);
        param.platformData = (void*) new GLuint;
        *((GLuint*)param.platformData) = paramLocation;
        param.type = getPolycodeParamType(type);
        shader->expectedParams.push_back(param);
    }
    
    total = -1;
    glGetProgramiv( shaderID, GL_ACTIVE_ATTRIBUTES, &total );
    
    for(GLuint i=0; i < total; i++)  {
        
        int name_len=-1, num=-1;
        GLenum type = GL_ZERO;
        char name[128];
        
        glGetActiveAttrib(shaderID, i, sizeof(name)-1, &name_len, &num, &type, name);
        name[name_len] = 0;

        int attribLocation = glGetAttribLocation(shaderID, name);
        
        ProgramAttribute attribute;
        attribute.name = String(name);
        attribute.platformData = (void*) new GLuint;
        *((GLuint*)attribute.platformData) = attribLocation;
        attribute.size = getAttributeSize(type);
        attribute.arrayType = mapNameToArrayType(attribute.name);
        
        attribute.platformData = (void*) new GLuint;
        *((GLuint*)attribute.platformData) = glGetAttribLocation(shaderID, attribute.name.c_str());
        
        
        shader->expectedAttributes.push_back(attribute);
    }
    
     *((GLuint*)shader->platformData) = shaderID;
}

int OpenGLGraphicsInterface::mapNameToArrayType(const String &name) {
    if(name == "position") {
        return RenderDataArray::VERTEX_DATA_ARRAY;
    } else if(name == "normal") {
        return RenderDataArray::NORMAL_DATA_ARRAY;
    } else if(name == "texCoord") {
        return RenderDataArray::TEXCOORD_DATA_ARRAY;
    } else if(name == "color") {
        return RenderDataArray::COLOR_DATA_ARRAY;
    } else if(name == "tangent") {
        return RenderDataArray::TANGENT_DATA_ARRAY;
    } else if(name == "texCoord2") {
        return RenderDataArray::TEXCOORD2_DATA_ARRAY;
    } else if(name == "boneWeights") {
        return RenderDataArray::BONE_WEIGHT_DATA_ARRAY;
    } else if(name == "boneIndices") {
        return RenderDataArray::BONE_INDEX_DATA_ARRAY;
    } else if(name == "customData1") {
        return RenderDataArray::CUSTOM_DATA_ARRAY1;
    } else if(name == "customData2") {
        return RenderDataArray::CUSTOM_DATA_ARRAY2;
    } else if(name == "customData3") {
        return RenderDataArray::CUSTOM_DATA_ARRAY3;
    } else if(name == "customData4") {
        return RenderDataArray::CUSTOM_DATA_ARRAY4;
    }
    return RenderDataArray::UNKNOWN_DATA_ARRAY;
}

void OpenGLGraphicsInterface::enableBackfaceCulling(bool val) {
    if(val) {
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void OpenGLGraphicsInterface::enableDepthTest(bool val) {
    if(val) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc( GL_LEQUAL );
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void OpenGLGraphicsInterface::enableDepthWrite(bool val) {
    if(val) {
        glDepthMask(GL_TRUE);
    } else {
        glDepthMask(GL_FALSE);
    }
}

void OpenGLGraphicsInterface::setLineSize(Number lineSize) {
    glLineWidth(lineSize);
}

void OpenGLGraphicsInterface::clearBuffers(const Color &clearColor, bool colorBuffer, bool depthBuffer, bool stencilBuffer) {
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
    
    
    glDepthMask(GL_TRUE);
    glDisable(GL_SCISSOR_TEST);
    
    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
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
        case GL_SAMPLER_2D:
            return ProgramParam::PARAM_TEXTURE;
        break;
        case GL_SAMPLER_CUBE:
            return ProgramParam::PARAM_CUBEMAP;
        break;
        default:
            return ProgramParam::PARAM_UNKNOWN;
        break;
    }
}
