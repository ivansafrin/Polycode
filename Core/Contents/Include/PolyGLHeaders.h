#pragma once

#ifdef _MINGW
#include "GLee.h"
#endif

#if defined(__APPLE__) && defined(__MACH__)
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/glu.h>	
#else
#include <GL/gl.h>	
#include <GL/glu.h>	
#include <GL/glext.h>

#ifdef _WINDOWS
#include <GL/wglext.h>
#endif
#endif