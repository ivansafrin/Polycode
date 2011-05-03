/*
 *  PolyGLCubemap.h
 *  Poly
 *
 *  Created by Ivan Safrin on 9/9/09.
 *  Copyright 2009 Ivan Safrin. All rights reserved.
 *
 */


#pragma once

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "PolyString.h"
#include "PolyGlobals.h"
#include "PolyTexture.h"
#include "PolyGLRenderer.h"
#include "PolyCubemap.h"
#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#endif


namespace Polycode {
	
	class _PolyExport OpenGLCubemap : public Cubemap {
	public:
		
		OpenGLCubemap(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5);
		virtual ~OpenGLCubemap();
		
		GLuint getTextureID();		
			
	private:
		
		int filteringMode;
		GLuint textureID;
	};
	
}