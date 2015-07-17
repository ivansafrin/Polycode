
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



using namespace Polycode;

OpenGLGraphicsInterface::OpenGLGraphicsInterface() {

}

OpenGLGraphicsInterface::~OpenGLGraphicsInterface() {
    
}

void OpenGLGraphicsInterface::executeDrawCall(const GPUDrawCall& drawCall) {
    
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