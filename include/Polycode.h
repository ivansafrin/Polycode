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

 
#pragma once

#include "polycode/core/PolyString.h"
#include "polycode/core/PolyData.h"
#include "polycode/core/PolyObject.h"
#include "polycode/core/PolyLogger.h"
#include "polycode/core/PolyConfig.h"
#include "polycode/core/PolyPerlin.h"
#include "polycode/core/PolyEntity.h"
#include "polycode/core/PolyEvent.h"
#include "polycode/core/PolyEventDispatcher.h"
#include "polycode/core/PolyEventHandler.h"
#include "polycode/core/PolyTimer.h"
#include "polycode/core/PolyTween.h"
#include "polycode/core/PolyTweenManager.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyCoreInput.h"
#include "polycode/core/PolyInputKeys.h"
#include "polycode/core/PolyInputEvent.h"
#include "polycode/core/PolyVector2.h"
#include "polycode/core/PolyVector3.h"
#include "polycode/core/PolyVector4.h"
#include "polycode/core/PolyBezierCurve.h"
#include "polycode/core/PolyQuaternionCurve.h"
#include "polycode/core/PolyRectangle.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyRenderDataArray.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyImage.h"
#include "polycode/core/PolyLabel.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyFontGlyphSheet.h"
#include "polycode/core/PolyFontManager.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolySceneManager.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCamera.h"
#include "polycode/core/PolyScene.h"
#include "polycode/core/PolyEntity.h"
#include "polycode/core/PolySceneMesh.h"
#include "polycode/core/PolySceneLine.h"
#include "polycode/core/PolySceneLight.h"
#include "polycode/core/PolySkeleton.h"
#include "polycode/core/PolyBone.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolySceneLabel.h"
#include "polycode/core/PolyParticleEmitter.h"
#include "polycode/core/PolySceneRenderTexture.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyThreaded.h"
#include "polycode/core/PolySound.h"
#include "polycode/core/PolySoundManager.h"
#include "polycode/core/PolySceneSound.h"
#include "polycode/core/PolySceneImage.h"
#include "polycode/core/PolyClient.h"
#include "polycode/core/PolyPeer.h"
#include "polycode/core/PolyServer.h"
#include "polycode/core/PolyServerWorld.h"
#include "polycode/core/PolySocket.h"
#include "polycode/core/PolyRay.h"
#include "polycode/core/PolySceneSprite.h"
#include "polycode/core/PolySceneEntityInstance.h"
#include "polycode/core/PolyGlobals.h"

#ifdef _WINDOWS
#endif

#if defined(__APPLE__) && defined(__MACH__)
        #include "polycode/core/PolyCocoaCore.h"
#else
    #if defined(_WINDOWS) && !defined(_MINGW)
        #include "polycode/core/PolyWinCore.h"
    #else
        #include "polycode/core/PolySDLCore.h"
    #endif
#endif



