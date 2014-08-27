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

#include "PolyString.h"
#include "PolyData.h"
#include "PolyObject.h"
#include "PolyLogger.h"
#include "PolyConfig.h"
#include "PolyPerlin.h"
#include "PolyEntity.h"
#include "PolyEvent.h"
#include "PolyEventDispatcher.h"
#include "PolyEventHandler.h"
#include "PolyTimer.h"
#include "PolyTween.h"
#include "PolyTweenManager.h"
#include "PolyResourceManager.h"
#include "PolyCore.h"
#include "PolyCoreInput.h"
#include "PolyInputKeys.h"
#include "PolyInputEvent.h"
#include "PolyVector2.h"
#include "PolyVector3.h"
#include "PolyVector4.h"
#include "PolyBezierCurve.h"
#include "PolyQuaternionCurve.h"
#include "PolyRectangle.h"
#include "PolyRenderer.h"
#include "PolyRenderDataArray.h"
#include "PolyCoreServices.h"
#include "PolyImage.h"
#include "PolyLabel.h"
#include "PolyFont.h"
#include "PolyFontGlyphSheet.h"
#include "PolyFontManager.h"
#include "PolyTexture.h"
#include "PolyMaterial.h"
#include "PolyMesh.h"
#include "PolyTextMesh.h"
#include "PolyShader.h"
#include "PolyFixedShader.h"
#include "PolySceneManager.h"
#include "PolyCoreServices.h"
#include "PolyCamera.h"
#include "PolyScene.h"
#include "PolyEntity.h"
#include "PolySceneMesh.h"
#include "PolySceneLine.h"
#include "PolySceneLight.h"
#include "PolySkeleton.h"
#include "PolyBone.h"
#include "PolyScenePrimitive.h"
#include "PolySceneLabel.h"
#include "PolyParticleEmitter.h"
#include "PolySceneRenderTexture.h"
#include "PolyResource.h"
#include "PolyThreaded.h"
#include "PolySound.h"
#include "PolySoundManager.h"
#include "PolySceneSound.h"
#include "PolySceneImage.h"
#include "PolyClient.h"
#include "PolyPeer.h"
#include "PolyServer.h"
#include "PolyServerWorld.h"
#include "PolySocket.h"
#include "PolyRay.h"
#include "PolySceneSprite.h"
#include "PolySceneEntityInstance.h"
#include "PolyGlobals.h"

#ifdef _WINDOWS
#include "PolyWinCore.h"
#endif
