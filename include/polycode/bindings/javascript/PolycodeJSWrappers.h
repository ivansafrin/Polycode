#pragma once

extern "C" {
	#include <stdio.h>
 	#include "duktape.h"
} 

#include "polycode/core/PolyBasicFileProvider.h"
#include "polycode/core/PolyBezierCurve.h"
#include "polycode/core/PolyBone.h"
#include "polycode/core/PolyCamera.h"
#include "polycode/core/PolyColor.h"
#include "polycode/core/PolyConfig.h"
#include "polycode/core/PolyCore.h"
#include "polycode/core/PolyCoreFileProvider.h"
#include "polycode/core/PolyCoreInput.h"
#include "polycode/core/PolyCoreServices.h"
#include "polycode/core/PolyCubemap.h"
#include "polycode/core/PolyData.h"
#include "polycode/core/PolyEntity.h"
#include "polycode/core/PolyEvent.h"
#include "polycode/core/PolyEventDispatcher.h"
#include "polycode/core/PolyEventHandler.h"
#include "polycode/core/PolyFont.h"
#include "polycode/core/PolyGlobals.h"
#include "polycode/core/PolyGPUDrawBuffer.h"
#include "polycode/core/PolyImage.h"
#include "polycode/core/PolyInputEvent.h"
#include "polycode/core/PolyInputKeys.h"
#include "polycode/core/PolyLabel.h"
#include "polycode/core/PolyMaterial.h"
#include "polycode/core/PolyMaterialManager.h"
#include "polycode/core/PolyMatrix4.h"
#include "polycode/core/PolyMesh.h"
#include "polycode/core/PolyObject.h"
#include "polycode/core/PolyOpenGLGraphicsInterface.h"
#include "polycode/core/PolyPAAudioInterface.h"
#include "polycode/core/PolyParticleEmitter.h"
#include "polycode/core/PolyPerlin.h"
#include "polycode/core/PolyPhysFSFileProvider.h"
#include "polycode/core/PolyQuaternion.h"
#include "polycode/core/PolyQuaternionCurve.h"
#include "polycode/core/PolyRay.h"
#include "polycode/core/PolyRectangle.h"
#include "polycode/core/PolyRenderDataArray.h"
#include "polycode/core/PolyRenderer.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyScene.h"
#include "polycode/core/PolySceneEntityInstance.h"
#include "polycode/core/PolySceneImage.h"
#include "polycode/core/PolySceneLabel.h"
#include "polycode/core/PolySceneLight.h"
#include "polycode/core/PolySceneLine.h"
#include "polycode/core/PolySceneManager.h"
#include "polycode/core/PolySceneMesh.h"
#include "polycode/core/PolyScenePrimitive.h"
#include "polycode/core/PolySceneRenderTexture.h"
#include "polycode/core/PolySceneSound.h"
#include "polycode/core/PolySceneSprite.h"
#include "polycode/core/PolyScript.h"
#include "polycode/core/PolyShader.h"
#include "polycode/core/PolySkeleton.h"
#include "polycode/core/PolySound.h"
#include "polycode/core/PolySoundManager.h"
#include "polycode/core/PolyString.h"
#include "polycode/core/PolyTexture.h"
#include "polycode/core/PolyTimer.h"
#include "polycode/core/PolyTimerManager.h"
#include "polycode/core/PolyVector2.h"
#include "polycode/core/PolyVector3.h"
#include "polycode/core/PolyVector4.h"


using namespace std;
namespace Polycode {

	duk_ret_t Polycode_BezierCurve__get_insertPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->insertPoint;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve__set_insertPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->insertPoint = (BezierPoint*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve__get_evaluationAccuracy(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->evaluationAccuracy);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve__set_evaluationAccuracy(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->evaluationAccuracy = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve__delete(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getControlPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getControlPoint(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_getNumControlPoints(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumControlPoints());
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p1z = duk_to_number(context, 3);
		Number p2x = duk_to_number(context, 4);
		Number p2y = duk_to_number(context, 5);
		Number p2z = duk_to_number(context, 6);
		Number p3x = duk_to_number(context, 7);
		Number p3y = duk_to_number(context, 8);
		Number p3z = duk_to_number(context, 9);
		inst->addControlPoint(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3dWithHandles(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p1z = duk_to_number(context, 3);
		Number p2x = duk_to_number(context, 4);
		Number p2y = duk_to_number(context, 5);
		Number p2z = duk_to_number(context, 6);
		Number p3x = duk_to_number(context, 7);
		Number p3y = duk_to_number(context, 8);
		Number p3z = duk_to_number(context, 9);
		inst->addControlPoint3dWithHandles(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3d(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->addControlPoint3d(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2dWithHandles(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p2x = duk_to_number(context, 3);
		Number p2y = duk_to_number(context, 4);
		Number p3x = duk_to_number(context, 5);
		Number p3y = duk_to_number(context, 6);
		inst->addControlPoint2dWithHandles(p1x,p1y,p2x,p2y,p3x,p3y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2d(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		inst->addControlPoint2d(x,y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getPointAt(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number a = duk_to_number(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPointAt(a);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_getPointBetween(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number a = duk_to_number(context, 1);
		BezierPoint* bp1 = (BezierPoint*)duk_to_pointer(context, 2);
		BezierPoint* bp2 = (BezierPoint*)duk_to_pointer(context, 3);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPointBetween(a,bp1,bp2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_clearControlPoints(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->clearControlPoints();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getYValueAtX(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, inst->getYValueAtX(x));
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_getTValueAtX(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, inst->getTValueAtX(x));
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_removePoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		BezierPoint* point = (BezierPoint*)duk_to_pointer(context, 1);
		inst->removePoint(point);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_setHeightCacheResolution(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		Number resolution = duk_to_number(context, 1);
		inst->setHeightCacheResolution(resolution);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_rebuildHeightCache(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->rebuildHeightCache();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_recalculateDistances(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->recalculateDistances();
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__get_p1(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->p1;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p1(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p1 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__get_p2(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->p2;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p2(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p2 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__get_p3(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->p3;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p3(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p3 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__delete(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Bone__get_parentBoneId(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->parentBoneId);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_parentBoneId(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->parentBoneId = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_boneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->boneMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_boneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->boneMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_restMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->restMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_restMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->restMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->baseMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_finalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->finalMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_finalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->finalMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseRotation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->baseRotation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseRotation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseRotation = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseScale(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->baseScale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseScale(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseScale = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_basePosition(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->basePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_basePosition(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->basePosition = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_disableAnimation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->disableAnimation);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_disableAnimation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->disableAnimation = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__delete(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Bone_getName(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Bone_setParentBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Bone* bone = (Bone*)duk_to_pointer(context, 1);
		inst->setParentBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_addChildBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Bone* bone = (Bone*)duk_to_pointer(context, 1);
		inst->addChildBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_getParentBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentBone();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Bone_getNumChildBones(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumChildBones());
		return 1;
	}

	duk_ret_t Polycode_Bone_getChildBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getChildBone(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Bone_getBoneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getBoneMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_setBoneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setBoneMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFullRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFullRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getParentRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getParentRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFinalMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_setRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setRestMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_setBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setBaseMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getBaseMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFullBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFullBaseMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_rebuildFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->rebuildFinalMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_buildFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->buildFinalMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_intializeBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		Vector3 basePosition = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 baseScale = *(Vector3*)duk_to_pointer(context, 2);
		Quaternion baseRotation = *(Quaternion*)duk_to_pointer(context, 3);
		Vector3 restPosition = *(Vector3*)duk_to_pointer(context, 4);
		Vector3 restScale = *(Vector3*)duk_to_pointer(context, 5);
		Quaternion restRotation = *(Quaternion*)duk_to_pointer(context, 6);
		inst->intializeBone(basePosition,baseScale,baseRotation,restPosition,restScale,restRotation);
		return 0;
	}

	duk_ret_t Polycode_Camera__get_frustumCulling(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->frustumCulling);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_frustumCulling(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->frustumCulling = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__get_topLeftOrtho(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->topLeftOrtho);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_topLeftOrtho(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->topLeftOrtho = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__get_cameraShift(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->cameraShift;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_cameraShift(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->cameraShift = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__delete(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Camera_buildFrustumPlanes(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->buildFrustumPlanes();
		return 0;
	}

	duk_ret_t Polycode_Camera_isSphereInFrustum(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Vector3 pos = *(Vector3*)duk_to_pointer(context, 1);
		Number fRadius = duk_to_number(context, 2);
		duk_push_boolean(context, inst->isSphereInFrustum(pos,fRadius));
		return 1;
	}

	duk_ret_t Polycode_Camera_isAABBInFrustum(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		AABB aabb = *(AABB*)duk_to_pointer(context, 1);
		duk_push_boolean(context, inst->isAABBInFrustum(aabb));
		return 1;
	}

	duk_ret_t Polycode_Camera_setOrthoMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		bool mode = duk_to_boolean(context, 1);
		inst->setOrthoMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSize(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Number orthoSizeX = duk_to_number(context, 1);
		Number orthoSizeY = duk_to_number(context, 2);
		inst->setOrthoSize(orthoSizeX,orthoSizeY);
		return 0;
	}

	duk_ret_t Polycode_Camera_setFrustumMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number front = duk_to_number(context, 5);
		Number back = duk_to_number(context, 6);
		inst->setFrustumMode(left,right,bottom,top,front,back);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getOrthoMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeX(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getOrthoSizeX());
		return 1;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeY(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getOrthoSizeY());
		return 1;
	}

	duk_ret_t Polycode_Camera_setFOV(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		inst->setFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_Camera_getFOV(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getFOV());
		return 1;
	}

	duk_ret_t Polycode_Camera_setClippingPlanes(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Number nearClipPlane = duk_to_number(context, 1);
		Number farClipPlane = duk_to_number(context, 2);
		inst->setClippingPlanes(nearClipPlane,farClipPlane);
		return 0;
	}

	duk_ret_t Polycode_Camera_getNearClippingPlane(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getNearClippingPlane());
		return 1;
	}

	duk_ret_t Polycode_Camera_getFarClippingPlane(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getFarClippingPlane());
		return 1;
	}

	duk_ret_t Polycode_Camera_setParentScene(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Scene* parentScene = (Scene*)duk_to_pointer(context, 1);
		inst->setParentScene(parentScene);
		return 0;
	}

	duk_ret_t Polycode_Camera_getParentScene(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentScene();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Camera_createProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->createProjectionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_hasFilterShader(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->hasFilterShader());
		return 1;
	}

	duk_ret_t Polycode_Camera_drawFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		RenderBuffer* targetBuffer = (RenderBuffer*)duk_to_pointer(context, 1);
		inst->drawFilter(targetBuffer);
		return 0;
	}

	duk_ret_t Polycode_Camera_setPostFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Material* material = (Material*)duk_to_pointer(context, 1);
		inst->setPostFilter(material);
		return 0;
	}

	duk_ret_t Polycode_Camera_setPostFilterByName(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		String shaderName = duk_to_string(context, 1);
		inst->setPostFilterByName(shaderName);
		return 0;
	}

	duk_ret_t Polycode_Camera_removePostFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->removePostFilter();
		return 0;
	}

	duk_ret_t Polycode_Camera_getScreenShaderMaterial(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getScreenShaderMaterial();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Camera_Clone(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Camera_applyClone(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Camera_getProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getProjectionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_setCustomProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setCustomProjectionMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Camera_getViewport(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->getViewport();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_setViewport(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		inst->setViewport(viewport);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSizeMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		int orthoSizeMode = duk_to_int(context, 1);
		inst->setOrthoSizeMode(orthoSizeMode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getOrthoSizeMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_setProjectionMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		int mode = duk_to_int(context, 1);
		inst->setProjectionMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getProjectionMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getProjectionMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_projectRayFrom2DCoordinate(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		Vector2 coordinate = *(Vector2*)duk_to_pointer(context, 1);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->projectRayFrom2DCoordinate(coordinate,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_renderFullScreenQuad(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		int shaderPass = duk_to_int(context, 2);
		inst->renderFullScreenQuad(drawBuffer,shaderPass);
		return 0;
	}

	duk_ret_t Polycode_Camera_getShaderPass(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_getNumShaderPasses(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_Color__get_r(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->r);
		return 1;
	}

	duk_ret_t Polycode_Color__set_r(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->r = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_g(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->g);
		return 1;
	}

	duk_ret_t Polycode_Color__set_g(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->g = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_b(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->b);
		return 1;
	}

	duk_ret_t Polycode_Color__set_b(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->b = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_a(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->a);
		return 1;
	}

	duk_ret_t Polycode_Color__set_a(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->a = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__delete(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHex(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		int hex = duk_to_int(context, 1);
		inst->setColorHex(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGB(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		int hex = duk_to_int(context, 1);
		inst->setColorHexRGB(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexFromString(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		String hex = duk_to_string(context, 1);
		inst->setColorHexFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGBFromString(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		String hex = duk_to_string(context, 1);
		inst->setColorHexRGBFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHSV(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		Number h = duk_to_number(context, 1);
		Number s = duk_to_number(context, 2);
		Number v = duk_to_number(context, 3);
		inst->setColorHSV(h,s,v);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGBA(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		int a = duk_to_int(context, 4);
		inst->setColorRGBA(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGB(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		inst->setColorRGB(r,g,b);
		return 0;
	}

	duk_ret_t Polycode_Color_setColor(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_blendColor(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		Color c2 = *(Color*)duk_to_pointer(context, 1);
		int mode = duk_to_int(context, 2);
		Number amount = duk_to_number(context, 3);
		Color c3 = *(Color*)duk_to_pointer(context, 4);
		Color *retInst = new Color();
		*retInst = inst->blendColor(c2,mode,amount,c3);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Color_Random(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->Random();
		return 0;
	}

	duk_ret_t Polycode_Color_getBrightness(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getBrightness());
		return 1;
	}

	duk_ret_t Polycode_Color_getHue(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getHue());
		return 1;
	}

	duk_ret_t Polycode_Color_getSaturation(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getSaturation());
		return 1;
	}

	duk_ret_t Polycode_Color_getValue(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getValue());
		return 1;
	}

	duk_ret_t Polycode_Color_getUint(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getUint());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__get_key(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->key.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_key(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->key = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_configNamespace(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->configNamespace.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_configNamespace(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->configNamespace = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_numVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->numVal);
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_numVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->numVal = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_stringVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->stringVal.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_stringVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->stringVal = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_isString(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isString);
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_isString(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->isString = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__delete(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Config__delete(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Config_loadConfig(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		inst->loadConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_saveConfig(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		inst->saveConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_getEntry(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getEntry(configNamespace,key);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Config_setStringValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		String value = duk_to_string(context, 3);
		inst->setStringValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_setNumericValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		Number value = duk_to_number(context, 3);
		inst->setNumericValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getNumericValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_number(context, inst->getNumericValue(configNamespace,key));
		return 1;
	}

	duk_ret_t Polycode_Config_getStringValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_string(context, inst->getStringValue(configNamespace,key).c_str());
		return 1;
	}

	duk_ret_t Polycode_Config_setBoolValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		bool value = duk_to_boolean(context, 3);
		inst->setBoolValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getBoolValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_boolean(context, inst->getBoolValue(configNamespace,key));
		return 1;
	}

	duk_ret_t Polycode_Core__get_eventMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->eventMutex;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core__set_eventMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->eventMutex = (CoreMutex*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_paused(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->paused);
		return 1;
	}

	duk_ret_t Polycode_Core__set_paused(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->paused = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_pauseOnLoseFocus(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->pauseOnLoseFocus);
		return 1;
	}

	duk_ret_t Polycode_Core__set_pauseOnLoseFocus(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->pauseOnLoseFocus = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_defaultScreenWidth(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->defaultScreenWidth);
		return 1;
	}

	duk_ret_t Polycode_Core__set_defaultScreenWidth(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->defaultScreenWidth = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_defaultScreenHeight(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->defaultScreenHeight);
		return 1;
	}

	duk_ret_t Polycode_Core__set_defaultScreenHeight(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->defaultScreenHeight = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_deviceAttitude(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->deviceAttitude;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Core__set_deviceAttitude(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->deviceAttitude = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__delete(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Core_Update(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->Update());
		return 1;
	}

	duk_ret_t Polycode_Core_Render(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_Core_fixedUpdate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->fixedUpdate());
		return 1;
	}

	duk_ret_t Polycode_Core_systemUpdate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->systemUpdate());
		return 1;
	}

	duk_ret_t Polycode_Core_updateAndRender(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->updateAndRender());
		return 1;
	}

	duk_ret_t Polycode_Core_enableMouse(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		bool newval = duk_to_boolean(context, 1);
		inst->enableMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_captureMouse(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		bool newval = duk_to_boolean(context, 1);
		inst->captureMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_setCursor(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		int cursorType = duk_to_int(context, 1);
		inst->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_Core_warpCursor(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		inst->warpCursor(x,y);
		return 0;
	}

	duk_ret_t Polycode_Core_createThread(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		Threaded* target = (Threaded*)duk_to_pointer(context, 1);
		inst->createThread(target);
		return 0;
	}

	duk_ret_t Polycode_Core_lockMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		CoreMutex* mutex = (CoreMutex*)duk_to_pointer(context, 1);
		inst->lockMutex(mutex);
		return 0;
	}

	duk_ret_t Polycode_Core_unlockMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		CoreMutex* mutex = (CoreMutex*)duk_to_pointer(context, 1);
		inst->unlockMutex(mutex);
		return 0;
	}

	duk_ret_t Polycode_Core_createMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->createMutex();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core_copyStringToClipboard(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		inst->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_Core_getClipboardString(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getClipboardString().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getServices(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getServices();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core_getFPS(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getFPS());
		return 1;
	}

	duk_ret_t Polycode_Core_Shutdown(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->Shutdown();
		return 0;
	}

	duk_ret_t Polycode_Core_isFullscreen(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isFullscreen());
		return 1;
	}

	duk_ret_t Polycode_Core_getAALevel(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getAALevel());
		return 1;
	}

	duk_ret_t Polycode_Core_getInput(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getInput();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core_getXRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getXRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getYRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getYRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getBackingXRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getBackingXRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getBackingYRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getBackingYRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getScreenWidth(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getScreenWidth());
		return 1;
	}

	duk_ret_t Polycode_Core_getScreenHeight(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getScreenHeight());
		return 1;
	}

	duk_ret_t Polycode_Core_createFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String folderPath = duk_to_string(context, 1);
		inst->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_Core_copyDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		inst->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_moveDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		inst->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_removeDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		inst->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_openFolderPicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->openFolderPicker().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_setFramerate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		int frameRate = duk_to_int(context, 1);
		int maxFixedCycles = duk_to_int(context, 2);
		inst->setFramerate(frameRate,maxFixedCycles);
		return 0;
	}

	duk_ret_t Polycode_Core_openFilePicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		bool allowMultiple = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Core_saveFilePicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		duk_push_string(context, inst->saveFilePicker(extensions).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_handleVideoModeChange(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*)duk_to_pointer(context, 1);
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}

	duk_ret_t Polycode_Core_flushRenderContext(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_prepareRenderContext(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->prepareRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_openFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		String opts = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->openFile(fileName,opts);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core_closeFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		CoreFile* file = (CoreFile*)duk_to_pointer(context, 1);
		inst->closeFile(file);
		return 0;
	}

	duk_ret_t Polycode_Core_addFileSource(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String type = duk_to_string(context, 1);
		String source = duk_to_string(context, 2);
		inst->addFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_removeFileSource(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String type = duk_to_string(context, 1);
		String source = duk_to_string(context, 2);
		inst->removeFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_parseFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Core_systemParseFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 3);
		duk_push_boolean(context, inst->systemParseFolder(pathString,showHidden,targetVector));
		return 1;
	}

	duk_ret_t Polycode_Core_getResourcePathForFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_string(context, inst->getResourcePathForFile(fileName).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_setVideoMode(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		int xRes = duk_to_int(context, 1);
		int yRes = duk_to_int(context, 2);
		bool fullScreen = duk_to_boolean(context, 3);
		bool vSync = duk_to_boolean(context, 4);
		int aaLevel = duk_to_int(context, 5);
		int anisotropyLevel = duk_to_int(context, 6);
		bool retinaSupport = duk_to_boolean(context, 7);
		inst->setVideoMode(xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport);
		return 0;
	}

	duk_ret_t Polycode_Core_resizeTo(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		int xRes = duk_to_int(context, 1);
		int yRes = duk_to_int(context, 2);
		inst->resizeTo(xRes,yRes);
		return 0;
	}

	duk_ret_t Polycode_Core_doSleep(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->doSleep();
		return 0;
	}

	duk_ret_t Polycode_Core_openURL(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String url = duk_to_string(context, 1);
		inst->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_Core_getElapsed(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getElapsed());
		return 1;
	}

	duk_ret_t Polycode_Core_getTicks(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getTicks());
		return 1;
	}

	duk_ret_t Polycode_Core_getRefreshIntervalMs(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getRefreshIntervalMs());
		return 1;
	}

	duk_ret_t Polycode_Core_getTimeSleptMs(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getTimeSleptMs());
		return 1;
	}

	duk_ret_t Polycode_Core_getFixedTimestep(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getFixedTimestep());
		return 1;
	}

	duk_ret_t Polycode_Core_getTicksFloat(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getTicksFloat());
		return 1;
	}

	duk_ret_t Polycode_Core_setUserPointer(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		void* ptr = (void*)duk_to_pointer(context, 1);
		inst->setUserPointer(ptr);
		return 0;
	}

	duk_ret_t Polycode_Core_getUserPointer(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->getUserPointer();
		return 0;
	}

	duk_ret_t Polycode_Core_executeExternalCommand(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		String command = duk_to_string(context, 1);
		String args = duk_to_string(context, 2);
		String inDirectory = duk_to_string(context, 3);
		duk_push_string(context, inst->executeExternalCommand(command,args,inDirectory).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getDefaultWorkingDirectory(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getDefaultWorkingDirectory().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getUserHomeDirectory(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getUserHomeDirectory().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_makeApplicationMain(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->makeApplicationMain();
		return 0;
	}

	duk_ret_t Polycode_Core_getEventMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getEventMutex();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Core_removeThread(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		Threaded* thread = (Threaded*)duk_to_pointer(context, 1);
		inst->removeThread(thread);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_xRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->xRes);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_xRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->xRes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_yRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->yRes);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_yRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->yRes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_fullScreen(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->fullScreen);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_fullScreen(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->fullScreen = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_vSync(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->vSync);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_vSync(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->vSync = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_aaLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->aaLevel);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_aaLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->aaLevel = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_anisotropyLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->anisotropyLevel);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_anisotropyLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->anisotropyLevel = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_retinaSupport(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->retinaSupport);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_retinaSupport(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->retinaSupport = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__delete(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_PolycodeViewBase__get_resizable(duk_context *context) {
		PolycodeViewBase *inst = (PolycodeViewBase*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->resizable);
		return 1;
	}

	duk_ret_t Polycode_PolycodeViewBase__set_resizable(duk_context *context) {
		PolycodeViewBase *inst = (PolycodeViewBase*)duk_to_pointer(context, 0);
		inst->resizable = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_PolycodeViewBase__delete(duk_context *context) {
		PolycodeViewBase *inst = (PolycodeViewBase*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_DummyCore__delete(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_DummyCore_Render(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_systemUpdate(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->systemUpdate());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_setCursor(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		int cursorType = duk_to_int(context, 1);
		inst->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_createThread(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		Threaded* target = (Threaded*)duk_to_pointer(context, 1);
		inst->createThread(target);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_createMutex(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->createMutex();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_DummyCore_copyStringToClipboard(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		inst->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getClipboardString(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getClipboardString().c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_createFolder(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String folderPath = duk_to_string(context, 1);
		inst->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_copyDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		inst->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_moveDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		inst->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_removeDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		inst->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openFolderPicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->openFolderPicker().c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_openFilePicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		bool allowMultiple = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_saveFilePicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		duk_push_string(context, inst->saveFilePicker(extensions).c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_handleVideoModeChange(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*)duk_to_pointer(context, 1);
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_flushRenderContext(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		inst->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openURL(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String url = duk_to_string(context, 1);
		inst->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getTicks(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getTicks());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_executeExternalCommand(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String command = duk_to_string(context, 1);
		String args = duk_to_string(context, 2);
		String inDirectory = duk_to_string(context, 3);
		duk_push_string(context, inst->executeExternalCommand(command,args,inDirectory).c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_systemParseFolder(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 3);
		duk_push_boolean(context, inst->systemParseFolder(pathString,showHidden,targetVector));
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__get_seconds(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->seconds);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_seconds(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->seconds = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_minutes(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->minutes);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_minutes(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->minutes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_hours(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->hours);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_hours(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->hours = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_month(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->month);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_month(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->month = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_monthDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->monthDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_monthDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->monthDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_weekDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->weekDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_weekDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->weekDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_year(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->year);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_year(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->year = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_yearDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->yearDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_yearDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->yearDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__delete(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreMutex__get_mutexID(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->mutexID);
		return 1;
	}

	duk_ret_t Polycode_CoreMutex__set_mutexID(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, 0);
		inst->mutexID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreMutex__delete(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreMutex_lock(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, 0);
		inst->lock();
		return 0;
	}

	duk_ret_t Polycode_CoreMutex_unlock(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, 0);
		inst->unlock();
		return 0;
	}

	duk_ret_t Polycode_CoreMotionEvent__get_amount(duk_context *context) {
		CoreMotionEvent *inst = (CoreMotionEvent*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->amount;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreMotionEvent__set_amount(duk_context *context) {
		CoreMotionEvent *inst = (CoreMotionEvent*)duk_to_pointer(context, 0);
		inst->amount = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreMotionEvent__delete(duk_context *context) {
		CoreMotionEvent *inst = (CoreMotionEvent*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension__get_extension(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->extension.c_str());
		return 1;
	}

	duk_ret_t Polycode_CoreFileExtension__set_extension(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		inst->extension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension__get_description(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->description.c_str());
		return 1;
	}

	duk_ret_t Polycode_CoreFileExtension__set_description(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		inst->description = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension__delete(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_name(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_name(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_extension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->extension.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_extension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->extension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_nameWithoutExtension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->nameWithoutExtension.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_nameWithoutExtension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->nameWithoutExtension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_basePath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->basePath.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_basePath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->basePath = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_fullPath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->fullPath.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_fullPath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->fullPath = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_type(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_type(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__delete(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry_init(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		String name = duk_to_string(context, 2);
		int type = duk_to_int(context, 3);
		inst->init(path,name,type);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_simulateTouchWithMouse(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->simulateTouchWithMouse);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateTouchWithMouse(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateTouchWithMouse = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_simulateTouchAsPen(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->simulateTouchAsPen);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateTouchAsPen(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateTouchAsPen = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_simulateMouseWithTouch(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->simulateMouseWithTouch);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateMouseWithTouch(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateMouseWithTouch = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_ignoreOffScreenTouch(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ignoreOffScreenTouch);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_ignoreOffScreenTouch(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->ignoreOffScreenTouch = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_keyRepeat(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->keyRepeat);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_keyRepeat(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->keyRepeat = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_mousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->mousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_mousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->mousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_deltaMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->deltaMousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_deltaMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->deltaMousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__delete(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMousePosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getKeyState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 1);
		duk_push_boolean(context, inst->getKeyState(keyCode));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int joystickIndex = duk_to_int(context, 1);
		int button = duk_to_int(context, 2);
		duk_push_boolean(context, inst->getJoystickButtonState(joystickIndex,button));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickAxisValue(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int joystickIndex = duk_to_int(context, 1);
		int axis = duk_to_int(context, 2);
		duk_push_number(context, inst->getJoystickAxisValue(joystickIndex,axis));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getMouseDelta(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMouseDelta();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getMouseButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		duk_push_boolean(context, inst->getMouseButtonState(mouseButton));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getNumJoysticks(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumJoysticks());
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickInfoByIndex(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickInfoByID(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int deviceID = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByID(deviceID);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_addJoystick(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int deviceID = duk_to_int(context, 1);
		inst->addJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_removeJoystick(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int deviceID = duk_to_int(context, 1);
		inst->removeJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickAxisMoved(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int axisID = duk_to_int(context, 1);
		Number value = duk_to_number(context, 2);
		int deviceID = duk_to_int(context, 3);
		inst->joystickAxisMoved(axisID,value,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonDown(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int buttonID = duk_to_int(context, 1);
		int deviceID = duk_to_int(context, 2);
		inst->joystickButtonDown(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonUp(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int buttonID = duk_to_int(context, 1);
		int deviceID = duk_to_int(context, 2);
		inst->joystickButtonUp(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelUp(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int ticks = duk_to_int(context, 1);
		inst->mouseWheelUp(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelDown(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int ticks = duk_to_int(context, 1);
		inst->mouseWheelDown(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMouseButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		bool state = duk_to_boolean(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->setMouseButtonState(mouseButton,state,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->setMousePosition(x,y,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setKeyState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 1);
		wchar_t code = *(wchar_t*)duk_to_pointer(context, 2);
		bool newState = duk_to_boolean(context, 3);
		int ticks = duk_to_int(context, 4);
		inst->setKeyState(keyCode,code,newState,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setDeltaPosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		inst->setDeltaPosition(x,y);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesBegan(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->touchesBegan(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesMoved(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->touchesMoved(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesEnded(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->touchesEnded(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_clearInput(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->clearInput();
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo__get_deviceID(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->deviceID);
		return 1;
	}

	duk_ret_t Polycode_JoystickInfo__set_deviceID(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		inst->deviceID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo__get_deviceIndex(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->deviceIndex);
		return 1;
	}

	duk_ret_t Polycode_JoystickInfo__set_deviceIndex(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		inst->deviceIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo__delete(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreServices__delete(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreServices_setRenderer(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 1);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getRenderer(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderer();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_Update(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_fixedUpdate(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_Render(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		inst->Render(viewport);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_setCore(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		Core* core = (Core*)duk_to_pointer(context, 1);
		inst->setCore(core);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getCore(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getCore();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getInput(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getInput();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getMaterialManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getMaterialManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getSceneManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSceneManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getTimerManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTimerManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getTweenManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTweenManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getResourceManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getSoundManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSoundManager();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getLogger(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLogger();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_CoreServices_getConfig(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getConfig();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Data__delete(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Data_loadFromFile(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->loadFromFile(fileName));
		return 1;
	}

	duk_ret_t Polycode_Data_getAsString(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		duk_push_string(context, inst->getAsString(encoding).c_str());
		return 1;
	}

	duk_ret_t Polycode_Data_setFromString(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		int encoding = duk_to_int(context, 2);
		inst->setFromString(str,encoding);
		return 0;
	}

	duk_ret_t Polycode_Data_saveToFile(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->saveToFile(fileName));
		return 1;
	}

	duk_ret_t Polycode_Data_getData(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getData();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__get_hit(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->hit);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__set_hit(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		inst->hit = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MouseEventResult__get_blocked(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->blocked);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__set_blocked(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		inst->blocked = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MouseEventResult__delete(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_EntityProp__get_propName(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->propName.c_str());
		return 1;
	}

	duk_ret_t Polycode_EntityProp__set_propName(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		inst->propName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_EntityProp__get_propValue(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->propValue.c_str());
		return 1;
	}

	duk_ret_t Polycode_EntityProp__set_propValue(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		inst->propValue = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_EntityProp__delete(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_AABB__get_min(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->min;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AABB__set_min(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		inst->min = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AABB__get_max(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->max;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AABB__set_max(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		inst->max = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AABB__delete(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Rotation__get_pitch(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->pitch);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_pitch(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->pitch = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__get_yaw(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->yaw);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_yaw(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->yaw = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__get_roll(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->roll);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_roll(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->roll = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__delete(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Entity__get_ownsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ownsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_ownsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->ownsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_billboardMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->billboardMode);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_billboardMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->billboardMode = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_color(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_color(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_enabled(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enabled);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_enabled(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_visible(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->visible);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_visible(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->visible = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_depthWrite(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthWrite);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_depthWrite(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->depthWrite = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_depthTest(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthTest);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_depthTest(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->depthTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_colorAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->colorAffectsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_colorAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->colorAffectsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_visibilityAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->visibilityAffectsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_visibilityAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->visibilityAffectsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_ignoreParentMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ignoreParentMatrix);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_ignoreParentMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->ignoreParentMatrix = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_enableScissor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enableScissor);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_enableScissor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->enableScissor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_scissorBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->scissorBox;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_scissorBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->scissorBox = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_editorOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->editorOnly);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_editorOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->editorOnly = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_id(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity__set_id(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_collisionShapeType(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		char *retInst = new char();
		*retInst = inst->collisionShapeType;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_collisionShapeType(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->collisionShapeType = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_processInputEvents(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->processInputEvents);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_processInputEvents(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->processInputEvents = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_blockMouseInput(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->blockMouseInput);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_blockMouseInput(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->blockMouseInput = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_snapToPixels(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->snapToPixels);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_snapToPixels(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->snapToPixels = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_mouseOver(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->mouseOver);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_mouseOver(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->mouseOver = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_rendererVis(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->rendererVis);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_rendererVis(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->rendererVis = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_layerID(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		char *retInst = new char();
		*retInst = inst->layerID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_layerID(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->layerID = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__delete(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Entity_initEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->initEntity();
		return 0;
	}

	duk_ret_t Polycode_Entity_Render(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_Entity_Update(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Entity_fixedUpdate(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Entity_transformAndRender(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		Polycode::Rectangle* parentScissorBox = (Polycode::Rectangle*)duk_to_pointer(context, 2);
		inst->transformAndRender(drawBuffer,parentScissorBox);
		return 0;
	}

	duk_ret_t Polycode_Entity_renderChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		Polycode::Rectangle* parentScissorBox = (Polycode::Rectangle*)duk_to_pointer(context, 2);
		inst->renderChildren(buffer,parentScissorBox);
		return 0;
	}

	duk_ret_t Polycode_Entity_Clone(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Entity_applyClone(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Entity_dirtyMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->dirtyMatrix(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_rebuildTransformMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->rebuildTransformMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_updateEntityMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->updateEntityMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getTransformMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getTransformMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedMatrixRelativeTo(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* relativeEntity = (Entity*)duk_to_pointer(context, 1);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedMatrixRelativeTo(relativeEntity);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getAnchorAdjustedMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getAnchorAdjustedMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedRollMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedRollMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setTransformByMatrixPure(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setTransformByMatrixPure(matrix);
		return 0;
	}

	duk_ret_t Polycode_Entity_getLookAtMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getLookAtMatrix(loc,upVector);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_addChild(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* newChild = (Entity*)duk_to_pointer(context, 1);
		inst->addChild(newChild);
		return 0;
	}

	duk_ret_t Polycode_Entity_removeChild(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* entityToRemove = (Entity*)duk_to_pointer(context, 1);
		inst->removeChild(entityToRemove);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* child = (Entity*)duk_to_pointer(context, 1);
		inst->moveChildUp(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* child = (Entity*)duk_to_pointer(context, 1);
		inst->moveChildDown(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildTop(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* child = (Entity*)duk_to_pointer(context, 1);
		inst->moveChildTop(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildBottom(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* child = (Entity*)duk_to_pointer(context, 1);
		inst->moveChildBottom(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_setParentEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* entity = (Entity*)duk_to_pointer(context, 1);
		inst->setParentEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Entity_getParentEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentEntity();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Entity_getNumChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumChildren());
		return 1;
	}

	duk_ret_t Polycode_Entity_getChildAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getChildAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Entity_setOwnsChildrenRecursive(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setOwnsChildrenRecursive(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getPosition2D(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getPosition2D();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getCombinedPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		inst->setPositionX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		inst->setPositionY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_Translate(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		inst->setPositionZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		inst->setScaleX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		inst->setScaleY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		inst->setScaleZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_Scale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->Scale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->setScale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCompoundScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getCompoundScale();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getScale();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getRotationEuler(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getRotationEuler();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getCombinedPitch());
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getCombinedYaw());
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getCombinedRoll());
		return 1;
	}

	duk_ret_t Polycode_Entity_rebuildRotation(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->rebuildRotation();
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationEuler(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 rotation = *(Vector3*)duk_to_pointer(context, 1);
		inst->setRotationEuler(rotation);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number pitch = duk_to_number(context, 1);
		inst->setPitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_setYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number yaw = duk_to_number(context, 1);
		inst->setYaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number roll = duk_to_number(context, 1);
		inst->setRoll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Roll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number roll = duk_to_number(context, 1);
		inst->Roll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Yaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number yaw = duk_to_number(context, 1);
		inst->Yaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_Pitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number pitch = duk_to_number(context, 1);
		inst->Pitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPitch());
		return 1;
	}

	duk_ret_t Polycode_Entity_getYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getYaw());
		return 1;
	}

	duk_ret_t Polycode_Entity_getRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getRoll());
		return 1;
	}

	duk_ret_t Polycode_Entity_getWidth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Entity_getHeight(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Entity_getDepth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getDepth());
		return 1;
	}

	duk_ret_t Polycode_Entity_setWidth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number width = duk_to_number(context, 1);
		inst->setWidth(width);
		return 0;
	}

	duk_ret_t Polycode_Entity_setHeight(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		inst->setHeight(height);
		return 0;
	}

	duk_ret_t Polycode_Entity_setDepth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number depth = duk_to_number(context, 1);
		inst->setDepth(depth);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		inst->setRotationQuat(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationByQuaternion(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Quaternion quaternion = *(Quaternion*)duk_to_pointer(context, 1);
		inst->setRotationByQuaternion(quaternion);
		return 0;
	}

	duk_ret_t Polycode_Entity_getRotationQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->getRotationQuat();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->getConcatenatedQuat();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_lookAt(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		inst->lookAt(loc,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_lookAtEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Entity* entity = (Entity*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		inst->lookAtEntity(entity,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedColor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->getCombinedColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setColor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setColorInt(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		int a = duk_to_int(context, 4);
		inst->setColorInt(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setAnchorPoint(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 anchorPoint = *(Vector3*)duk_to_pointer(context, 1);
		inst->setAnchorPoint(anchorPoint);
		return 0;
	}

	duk_ret_t Polycode_Entity_getAnchorPoint(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getAnchorPoint();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int mouseButton = duk_to_int(context, 2);
		int timestamp = duk_to_int(context, 3);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseDown(ray,mouseButton,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int mouseButton = duk_to_int(context, 2);
		int timestamp = duk_to_int(context, 3);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseUp(ray,mouseButton,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseMove(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseMove(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseWheelUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseWheelUp(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseWheelDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseWheelDown(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setDepthOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setDepthOnly(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getDepthOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getDepthOnly());
		return 1;
	}

	duk_ret_t Polycode_Entity_setUserData(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		void* userData = (void*)duk_to_pointer(context, 1);
		inst->setUserData(userData);
		return 0;
	}

	duk_ret_t Polycode_Entity_getUserData(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->getUserData();
		return 0;
	}

	duk_ret_t Polycode_Entity_setBlendingMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		int newBlendingMode = duk_to_int(context, 1);
		inst->setBlendingMode(newBlendingMode);
		return 0;
	}

	duk_ret_t Polycode_Entity_getBlendingMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getBlendingMode());
		return 1;
	}

	duk_ret_t Polycode_Entity_getEntityById(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String id = duk_to_string(context, 1);
		bool recursive = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getEntityById(id,recursive);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Entity_getEntitiesByTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String tag = duk_to_string(context, 1);
		bool recursive = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntitiesByLayerID(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		char layerID = *(char*)duk_to_pointer(context, 1);
		bool recursive = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntityProp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String propName = duk_to_string(context, 1);
		duk_push_string(context, inst->getEntityProp(propName).c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity_setEntityProp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String propName = duk_to_string(context, 1);
		String propValue = duk_to_string(context, 2);
		inst->setEntityProp(propName,propValue);
		return 0;
	}

	duk_ret_t Polycode_Entity_setInverseY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setInverseY(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getInverseY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getInverseY());
		return 1;
	}

	duk_ret_t Polycode_Entity_doUpdates(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->doUpdates();
		return 0;
	}

	duk_ret_t Polycode_Entity_doFixedUpdates(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->doFixedUpdates();
		return 0;
	}

	duk_ret_t Polycode_Entity_buildPositionMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->buildPositionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setRenderer(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 1);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_Entity_customHitDetection(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		duk_push_boolean(context, inst->customHitDetection(ray));
		return 1;
	}

	duk_ret_t Polycode_Entity_getNumTags(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumTags());
		return 1;
	}

	duk_ret_t Polycode_Entity_getTagAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		duk_push_string(context, inst->getTagAtIndex(index).c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity_hasTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String tag = duk_to_string(context, 1);
		duk_push_boolean(context, inst->hasTag(tag));
		return 1;
	}

	duk_ret_t Polycode_Entity_clearTags(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->clearTags();
		return 0;
	}

	duk_ret_t Polycode_Entity_addTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		String tag = duk_to_string(context, 1);
		inst->addTag(tag);
		return 0;
	}

	duk_ret_t Polycode_Entity_getScreenPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Matrix4 projectionMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Matrix4 cameraMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 3);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getScreenPosition(projectionMatrix,cameraMatrix,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_recalculateAABBAllChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->recalculateAABBAllChildren();
		return 0;
	}

	duk_ret_t Polycode_Entity_recalculateAABB(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->recalculateAABB();
		return 0;
	}

	duk_ret_t Polycode_Entity_getWorldAABB(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		AABB *retInst = new AABB();
		*retInst = inst->getWorldAABB();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getLocalBoundingBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getLocalBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 1);
		inst->setLocalBoundingBox(box);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		inst->setLocalBoundingBoxX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		inst->setLocalBoundingBoxY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		inst->setLocalBoundingBoxZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setContainerScene(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Scene* scene = (Scene*)duk_to_pointer(context, 1);
		inst->setContainerScene(scene);
		return 0;
	}

	duk_ret_t Polycode_Entity_getContainerScene(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getContainerScene();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Entity_attachScript(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Script* script = (Script*)duk_to_pointer(context, 1);
		inst->attachScript(script);
		return 0;
	}

	duk_ret_t Polycode_Entity_detachScript(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		Script* script = (Script*)duk_to_pointer(context, 1);
		inst->detachScript(script);
		return 0;
	}

	duk_ret_t Polycode_Entity_getNumScripts(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumScripts());
		return 1;
	}

	duk_ret_t Polycode_Entity_getScriptAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getScriptAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Event__get_deleteOnDispatch(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->deleteOnDispatch);
		return 1;
	}

	duk_ret_t Polycode_Event__set_deleteOnDispatch(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		inst->deleteOnDispatch = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Event__get_cancelEventFlag(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->cancelEventFlag);
		return 1;
	}

	duk_ret_t Polycode_Event__set_cancelEventFlag(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		inst->cancelEventFlag = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Event__delete(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Event_getEventCode(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getEventCode());
		return 1;
	}

	duk_ret_t Polycode_Event_getDispatcher(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDispatcher();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Event_setEventCode(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->setEventCode(eventCode);
		return 0;
	}

	duk_ret_t Polycode_Event_setDispatcher(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		EventDispatcher* dispatcher = (EventDispatcher*)duk_to_pointer(context, 1);
		inst->setDispatcher(dispatcher);
		return 0;
	}

	duk_ret_t Polycode_Event_getEventType(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getEventType().c_str());
		return 1;
	}

	duk_ret_t Polycode_Event_cancelEvent(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		inst->cancelEvent();
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher__delete(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeAllHandlers(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		inst->removeAllHandlers();
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeAllHandlersForListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 1);
		inst->removeAllHandlersForListener(handler);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_addEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->addEventListener(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_addEventListenerUnique(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->addEventListenerUnique(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_hasEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		duk_push_boolean(context, inst->hasEventListener(handler,eventCode));
		return 1;
	}

	duk_ret_t Polycode_EventDispatcher_removeEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->removeEventListener(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher___dispatchEvent(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		Event* event = (Event*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->__dispatchEvent(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_dispatchEvent(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		Event* event = (Event*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->dispatchEvent(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_dispatchEventNoDelete(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, 0);
		Event* event = (Event*)duk_to_pointer(context, 1);
		int eventCode = duk_to_int(context, 2);
		inst->dispatchEventNoDelete(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventHandler__delete(duk_context *context) {
		EventHandler *inst = (EventHandler*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Font__get_loaded(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->loaded);
		return 1;
	}

	duk_ret_t Polycode_Font__set_loaded(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		inst->loaded = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Font__delete(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Font_getFace(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		FT_Face *retInst = new FT_Face();
		*retInst = inst->getFace();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Font_isValid(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isValid());
		return 1;
	}

	duk_ret_t Polycode_Font_setFontName(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		String fontName = duk_to_string(context, 1);
		inst->setFontName(fontName);
		return 0;
	}

	duk_ret_t Polycode_Font_getFontName(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getFontName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Font_getFontPath(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getFontPath().c_str());
		return 1;
	}

	duk_ret_t Polycode_LightInfo__get_importance(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->importance);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_importance(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->importance = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_position(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_position(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_direction(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_direction(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_type(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_type(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_diffuseColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->diffuseColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_diffuseColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->diffuseColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_specularColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->specularColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_specularColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->specularColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_constantAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->constantAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_constantAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->constantAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_linearAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->linearAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_linearAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->linearAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_quadraticAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->quadraticAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_quadraticAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->quadraticAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_intensity(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->intensity);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_intensity(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->intensity = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_spotlightCutoff(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->spotlightCutoff);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_spotlightCutoff(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->spotlightCutoff = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_spotlightExponent(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->spotlightExponent);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_spotlightExponent(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->spotlightExponent = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_shadowsEnabled(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->shadowsEnabled);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_shadowsEnabled(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->shadowsEnabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_shadowMapTexture(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shadowMapTexture;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_shadowMapTexture(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->shadowMapTexture = (Texture*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_lightViewMatrix(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->lightViewMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_lightViewMatrix(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->lightViewMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__delete(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__get_mesh(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->mesh;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_mesh(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->mesh = (Mesh*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__get_options(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		GPUDrawOptions *retInst = new GPUDrawOptions();
		*retInst = inst->options;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_options(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->options = *(GPUDrawOptions*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__get_modelMatrix(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->modelMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_modelMatrix(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->modelMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__get_material(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->material;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_material(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->material = (Material*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__delete(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthTest(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthTest);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthTest(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthWrite(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthWrite);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthWrite(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthWrite = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_linePointSize(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->linePointSize);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_linePointSize(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->linePointSize = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_alphaTest(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->alphaTest);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_alphaTest(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->alphaTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_backfaceCull(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->backfaceCull);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_backfaceCull(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->backfaceCull = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthOnly(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthOnly);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthOnly(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthOnly = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_forceMaterial(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->forceMaterial);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_forceMaterial(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->forceMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_blendingMode(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_blendingMode(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_scissorBox(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->scissorBox;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_scissorBox(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->scissorBox = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_enableScissor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enableScissor);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_enableScissor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->enableScissor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_drawColor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->drawColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_drawColor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->drawColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__delete(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_targetFramebuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->targetFramebuffer;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_targetFramebuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->targetFramebuffer = (RenderBuffer*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_projectionMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->projectionMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_projectionMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->projectionMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_viewMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->viewMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_viewMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->viewMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_cameraMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->cameraMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_cameraMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->cameraMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearColor(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->clearColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearColor(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearDepthBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->clearDepthBuffer);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearDepthBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearDepthBuffer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearColorBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->clearColorBuffer);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearColorBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearColorBuffer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_backingResolutionScale(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->backingResolutionScale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_backingResolutionScale(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->backingResolutionScale = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_globalMaterial(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->globalMaterial;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_globalMaterial(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->globalMaterial = (Material*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_viewport(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->viewport;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_viewport(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->viewport = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__delete(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Image__delete(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Image_loadImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->loadImage(fileName));
		return 1;
	}

	duk_ret_t Polycode_Image_saveImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->saveImage(fileName));
		return 1;
	}

	duk_ret_t Polycode_Image_pasteImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		Image* image = (Image*)duk_to_pointer(context, 1);
		int x = duk_to_int(context, 2);
		int y = duk_to_int(context, 3);
		int blendingMode = duk_to_int(context, 4);
		Number blendAmount = duk_to_number(context, 5);
		Color blendColor = *(Color*)duk_to_pointer(context, 6);
		inst->pasteImage(image,x,y,blendingMode,blendAmount,blendColor);
		return 0;
	}

	duk_ret_t Polycode_Image_createEmpty(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		Color fillColor = *(Color*)duk_to_pointer(context, 3);
		inst->createEmpty(width,height,fillColor);
		return 0;
	}

	duk_ret_t Polycode_Image_fill(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		inst->fill(color);
		return 0;
	}

	duk_ret_t Polycode_Image_setPixel(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		Number r = duk_to_number(context, 3);
		Number g = duk_to_number(context, 4);
		Number b = duk_to_number(context, 5);
		Number a = duk_to_number(context, 6);
		inst->setPixel(x,y,r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Image_getPixel(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		Color *retInst = new Color();
		*retInst = inst->getPixel(x,y);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Image_swap(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int* v1 = (int*)duk_to_pointer(context, 1);
		int* v2 = (int*)duk_to_pointer(context, 2);
		inst->swap(v1,v2);
		return 0;
	}

	duk_ret_t Polycode_Image_drawLine(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x0 = duk_to_int(context, 1);
		int y0 = duk_to_int(context, 2);
		int x1 = duk_to_int(context, 3);
		int y1 = duk_to_int(context, 4);
		Color col = *(Color*)duk_to_pointer(context, 5);
		inst->drawLine(x0,y0,x1,y1,col);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrushTo(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		inst->moveBrushTo(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrush(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		inst->moveBrush(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_drawLineTo(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		Color col = *(Color*)duk_to_pointer(context, 3);
		inst->drawLineTo(x,y,col);
		return 0;
	}

	duk_ret_t Polycode_Image_fillRect(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int w = duk_to_int(context, 3);
		int h = duk_to_int(context, 4);
		Color col = *(Color*)duk_to_pointer(context, 5);
		inst->fillRect(x,y,w,h,col);
		return 0;
	}

	duk_ret_t Polycode_Image_perlinNoise(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int seed = duk_to_int(context, 1);
		bool alpha = duk_to_boolean(context, 2);
		inst->perlinNoise(seed,alpha);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlur(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		inst->fastBlur(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurVert(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		inst->fastBlurVert(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurHor(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		inst->fastBlurHor(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_getPixelsInRect(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int width = duk_to_int(context, 3);
		int height = duk_to_int(context, 4);
		PolyBase *ptrRetVal = (PolyBase*)inst->getPixelsInRect(x,y,width,height);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Image_getImagePart(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		Polycode::Rectangle subRect = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getImagePart(subRect);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Image_getBrushX(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getBrushX());
		return 1;
	}

	duk_ret_t Polycode_Image_getBrushY(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getBrushY());
		return 1;
	}

	duk_ret_t Polycode_Image_isLoaded(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isLoaded());
		return 1;
	}

	duk_ret_t Polycode_Image_getType(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getType());
		return 1;
	}

	duk_ret_t Polycode_Image_getWidth(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Image_getHeight(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Image_getPixels(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getPixels();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Image_premultiplyAlpha(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		inst->premultiplyAlpha();
		return 0;
	}

	duk_ret_t Polycode_Image_savePNG(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->savePNG(fileName));
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__get_id(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->id);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_id(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->id = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__get_position(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_position(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->position = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__get_type(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_type(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__delete(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_mouseButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->mouseButton);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_mouseButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->mouseButton = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_mousePosition(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->mousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_mousePosition(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->mousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_key(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->key);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_key(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->key = (PolyKEY)duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_charCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		wchar_t *retInst = new wchar_t();
		*retInst = inst->charCode;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_charCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->charCode = *(wchar_t*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_timestamp(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->timestamp);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_timestamp(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->timestamp = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_touch(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		TouchInfo *retInst = new TouchInfo();
		*retInst = inst->touch;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_touch(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->touch = *(TouchInfo*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_touchType(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->touchType);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_touchType(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->touchType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickDeviceID(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->joystickDeviceID);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickDeviceID(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickDeviceID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickAxisValue(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->joystickAxisValue);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickAxisValue(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickAxisValue = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->joystickButton);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickButton = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickAxis(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->joystickAxis);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickAxis(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickAxis = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickIndex(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->joystickIndex);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickIndex(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_hitDistance(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->hitDistance);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_hitDistance(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->hitDistance = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__delete(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getMousePosition(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMousePosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent_getKey(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getKey());
		return 1;
	}

	duk_ret_t Polycode_InputEvent_getMouseButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getMouseButton());
		return 1;
	}

	duk_ret_t Polycode_InputEvent_getCharCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		wchar_t *retInst = new wchar_t();
		*retInst = inst->getCharCode();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent_keyCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->keyCode());
		return 1;
	}

	duk_ret_t Polycode_GlyphData__get_glyphs(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->glyphs;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_glyphs(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->glyphs = (FT_Glyph*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__get_positions(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->positions;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_positions(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->positions = (FT_Vector*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__get_num_glyphs(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		FT_UInt *retInst = new FT_UInt();
		*retInst = inst->num_glyphs;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_num_glyphs(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->num_glyphs = *(FT_UInt*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__get_trailingAdvance(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->trailingAdvance);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_trailingAdvance(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->trailingAdvance = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__delete(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GlyphData_clearData(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->clearData();
		return 0;
	}

	duk_ret_t Polycode_ColorRange__get_color(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_color(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__get_rangeStart(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->rangeStart);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_rangeStart(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->rangeStart = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__get_rangeEnd(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->rangeEnd);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_rangeEnd(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->rangeEnd = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__delete(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Label__delete(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Label_setText(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		inst->setText(text);
		return 0;
	}

	duk_ret_t Polycode_Label_getText(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getText().c_str());
		return 1;
	}

	duk_ret_t Polycode_Label_getTextWidthForString(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, inst->getTextWidthForString(text));
		return 1;
	}

	duk_ret_t Polycode_Label_getTextHeightForString(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, inst->getTextHeightForString(text));
		return 1;
	}

	duk_ret_t Polycode_Label_getTextWidth(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getTextWidth());
		return 1;
	}

	duk_ret_t Polycode_Label_getTextHeight(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getTextHeight());
		return 1;
	}

	duk_ret_t Polycode_Label_setColorForRange(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		int rangeStart = duk_to_int(context, 2);
		int rangeEnd = duk_to_int(context, 3);
		inst->setColorForRange(color,rangeStart,rangeEnd);
		return 0;
	}

	duk_ret_t Polycode_Label_clearColors(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		inst->clearColors();
		return 0;
	}

	duk_ret_t Polycode_Label_getColorForIndex(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		Color *retInst = new Color();
		*retInst = inst->getColorForIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_getPremultiplyAlpha(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getPremultiplyAlpha());
		return 1;
	}

	duk_ret_t Polycode_Label_setPremultiplyAlpha(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setPremultiplyAlpha(val);
		return 0;
	}

	duk_ret_t Polycode_Label_setFont(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Font* newFont = (Font*)duk_to_pointer(context, 1);
		inst->setFont(newFont);
		return 0;
	}

	duk_ret_t Polycode_Label_getFont(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getFont();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Label_setSize(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		int newSize = duk_to_int(context, 1);
		inst->setSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_Label_getSize(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getSize());
		return 1;
	}

	duk_ret_t Polycode_Label_getAntialiasMode(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getAntialiasMode());
		return 1;
	}

	duk_ret_t Polycode_Label_setAntialiasMode(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		int newMode = duk_to_int(context, 1);
		inst->setAntialiasMode(newMode);
		return 0;
	}

	duk_ret_t Polycode_Label_getBaselineAdjust(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getBaselineAdjust());
		return 1;
	}

	duk_ret_t Polycode_Label_setBackgroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		inst->setBackgroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setForegroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		inst->setForegroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setColors(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color backgroundColor = *(Color*)duk_to_pointer(context, 1);
		Color foregroundColor = *(Color*)duk_to_pointer(context, 2);
		inst->setColors(backgroundColor,foregroundColor);
		return 0;
	}

	duk_ret_t Polycode_Label_getBackgroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->getBackgroundColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_getForegroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->getForegroundColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_optionsChanged(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->optionsChanged());
		return 1;
	}

	duk_ret_t Polycode_Material__get_fp16RenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->fp16RenderTargets);
		return 1;
	}

	duk_ret_t Polycode_Material__set_fp16RenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->fp16RenderTargets = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__get_blendingMode(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_Material__set_blendingMode(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__get_screenMaterial(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->screenMaterial);
		return 1;
	}

	duk_ret_t Polycode_Material__set_screenMaterial(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->screenMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__delete(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		inst->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPassAtIndex(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		int shaderIndex = duk_to_int(context, 2);
		inst->addShaderPassAtIndex(pass,shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_addShader(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		Shader* shader = (Shader*)duk_to_pointer(context, 1);
		ShaderBinding* shaderBinding = (ShaderBinding*)duk_to_pointer(context, 2);
		inst->addShader(shader,shaderBinding);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderAtIndex(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		Shader* shader = (Shader*)duk_to_pointer(context, 1);
		ShaderBinding* shaderBinding = (ShaderBinding*)duk_to_pointer(context, 2);
		int shaderIndex = duk_to_int(context, 3);
		inst->addShaderAtIndex(shader,shaderBinding,shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderPasses(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_Material_removeShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int shaderIndex = duk_to_int(context, 1);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateExpectedShaderParams(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->recreateExpectedShaderParams();
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		ShaderRenderTarget* newTarget = (ShaderRenderTarget*)duk_to_pointer(context, 1);
		inst->addShaderRenderTarget(newTarget);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderRenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumShaderRenderTargets());
		return 1;
	}

	duk_ret_t Polycode_Material_getShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderRenderTarget(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Material_removeShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		inst->removeShaderRenderTarget(index);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		ShaderRenderTarget* renderTarget = (ShaderRenderTarget*)duk_to_pointer(context, 1);
		inst->recreateRenderTarget(renderTarget);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateRenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->recreateRenderTargets();
		return 0;
	}

	duk_ret_t Polycode_Material_getName(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Material_getShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Material_getShaderBinding(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Material_getShader(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShader(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Material_loadMaterial(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadMaterial(fileName);
		return 0;
	}

	duk_ret_t Polycode_Material_setName(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Material_clearShaders(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->clearShaders();
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_shader(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shader;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_shader(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->shader = (Shader*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_wireframe(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->wireframe);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_wireframe(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->wireframe = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_blendingMode(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_blendingMode(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_shaderBinding(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shaderBinding;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_shaderBinding(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->shaderBinding = (ShaderBinding*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_materialShaderBinding(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->materialShaderBinding;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_materialShaderBinding(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->materialShaderBinding = (ShaderBinding*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__delete(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderPass_setAttributeArraysFromMesh(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 1);
		inst->setAttributeArraysFromMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass_setExpectedAttributes(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->setExpectedAttributes();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager__get_premultiplyAlphaOnLoad(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->premultiplyAlphaOnLoad);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager__set_premultiplyAlphaOnLoad(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->premultiplyAlphaOnLoad = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager__get_clampDefault(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->clampDefault);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager__set_clampDefault(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->clampDefault = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager__get_mipmapsDefault(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->mipmapsDefault);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager__set_mipmapsDefault(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->mipmapsDefault = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager__get_keepTextureData(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->keepTextureData);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager__set_keepTextureData(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->keepTextureData = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager__delete(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_Update(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		char* imageData = (char*)duk_to_pointer(context, 3);
		bool clamp = duk_to_boolean(context, 4);
		bool createMipmaps = duk_to_boolean(context, 5);
		int type = duk_to_int(context, 6);
		PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width,height,imageData,clamp,createMipmaps,type);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createNewTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		bool clamp = duk_to_boolean(context, 3);
		bool createMipmaps = duk_to_boolean(context, 4);
		int type = duk_to_int(context, 5);
		PolyBase *ptrRetVal = (PolyBase*)inst->createNewTexture(width,height,clamp,createMipmaps,type);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createTextureFromImage(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		Image* image = (Image*)duk_to_pointer(context, 1);
		bool clamp = duk_to_boolean(context, 2);
		bool createMipmaps = duk_to_boolean(context, 3);
		PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromImage(image,clamp,createMipmaps);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createTextureFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		bool clamp = duk_to_boolean(context, 2);
		bool createMipmaps = duk_to_boolean(context, 3);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 4);
		PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromFile(fileName,clamp,createMipmaps,resourcePool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_deleteTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->deleteTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadTextures(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->reloadTextures();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadProgramsAndTextures(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->reloadProgramsAndTextures();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadPrograms(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		inst->reloadPrograms();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getTextureByResourcePath(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		String resourcePath = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTextureByResourcePath(resourcePath);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createProgramFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		String programPath = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->createProgramFromFile(programPath);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_loadMaterialLibraryIntoPool(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		String materialFile = duk_to_string(context, 2);
		inst->loadMaterialLibraryIntoPool(pool,materialFile);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_cubemapFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->cubemapFromXMLNode(node);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_materialFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->materialFromXMLNode(resourcePool,node);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createMaterial(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		String materialName = duk_to_string(context, 2);
		String shaderName = duk_to_string(context, 3);
		PolyBase *ptrRetVal = (PolyBase*)inst->createMaterial(resourcePool,materialName,shaderName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_setShaderFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->setShaderFromXMLNode(resourcePool,node);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createShaderFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->createShaderFromXMLNode(resourcePool,node);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_createShader(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		String shaderType = duk_to_string(context, 2);
		String name = duk_to_string(context, 3);
		String vpName = duk_to_string(context, 4);
		String fpName = duk_to_string(context, 5);
		bool screenShader = duk_to_boolean(context, 6);
		PolyBase *ptrRetVal = (PolyBase*)inst->createShader(resourcePool,shaderType,name,vpName,fpName,screenShader);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_loadMaterialsFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		String fileName = duk_to_string(context, 2);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadShadersFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		String fileName = duk_to_string(context, 2);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadCubemapsFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_setAnisotropyAmount(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int anisotropy = duk_to_int(context, 1);
		inst->setAnisotropyAmount(anisotropy);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_setTextureFilteringMode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int textureFilteringMode = duk_to_int(context, 1);
		inst->setTextureFilteringMode(textureFilteringMode);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getTextureFilteringMode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getTextureFilteringMode());
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_addMaterial(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		Material* material = (Material*)duk_to_pointer(context, 1);
		inst->addMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_addShader(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		Shader* shader = (Shader*)duk_to_pointer(context, 1);
		inst->addShader(shader);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getNumShaders(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumShaders());
		return 1;
	}

	duk_ret_t Polycode_MaterialManager_getShaderByIndex(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderByIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Matrix4__delete(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Matrix4_identity(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		inst->identity();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_rotateVector(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->rotateVector(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_getPosition(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multiplyWithPerspective(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->multiplyWithPerspective(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multVector3(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->multVector3(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multVector4(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector4 v2 = *(Vector4*)duk_to_pointer(context, 1);
		Vector4 *retInst = new Vector4();
		*retInst = inst->multVector4(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_Translate(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setPosition(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setScale(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Vector3 scale = *(Vector3*)duk_to_pointer(context, 1);
		inst->setScale(scale);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_getEulerAngles(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number* ax = (Number*)duk_to_pointer(context, 1);
		Number* ay = (Number*)duk_to_pointer(context, 2);
		Number* az = (Number*)duk_to_pointer(context, 3);
		inst->getEulerAngles(ax,ay,az);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_transpose(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->transpose();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_Inverse(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->Inverse();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_inverseAffine(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->inverseAffine();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_determinant(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->determinant());
		return 1;
	}

	duk_ret_t Polycode_Matrix4_setOrthoProjection(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number zNear = duk_to_number(context, 5);
		Number zFar = duk_to_number(context, 6);
		inst->setOrthoProjection(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjectionFrustum(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number zNear = duk_to_number(context, 5);
		Number zFar = duk_to_number(context, 6);
		inst->setProjectionFrustum(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjection(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		Number aspect = duk_to_number(context, 2);
		Number zNear = duk_to_number(context, 3);
		Number zFar = duk_to_number(context, 4);
		inst->setProjection(fov,aspect,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Mesh__get_indexedMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->indexedMesh);
		return 1;
	}

	duk_ret_t Polycode_Mesh__set_indexedMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		inst->indexedMesh = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Mesh__delete(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Mesh_loadMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadMesh(fileName);
		return 0;
	}

	duk_ret_t Polycode_Mesh_clearMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		inst->clearMesh();
		return 0;
	}

	duk_ret_t Polycode_Mesh_saveToFile(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		bool writeNormals = duk_to_boolean(context, 2);
		bool writeTangents = duk_to_boolean(context, 3);
		bool writeColors = duk_to_boolean(context, 4);
		bool writeBoneWeights = duk_to_boolean(context, 5);
		bool writeUVs = duk_to_boolean(context, 6);
		bool writeSecondaryUVs = duk_to_boolean(context, 7);
		inst->saveToFile(fileName,writeNormals,writeTangents,writeColors,writeBoneWeights,writeUVs,writeSecondaryUVs);
		return 0;
	}

	duk_ret_t Polycode_Mesh_loadFromFile(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		CoreFile* inFile = (CoreFile*)duk_to_pointer(context, 1);
		inst->loadFromFile(inFile);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexCount(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getVertexCount());
		return 1;
	}

	duk_ret_t Polycode_Mesh_createPlane(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createVPlane(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createVPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCircle(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createLineCircle(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createLineCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createTorus(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		Number tubeRadius = duk_to_number(context, 2);
		int segmentsW = duk_to_int(context, 3);
		int segmentsH = duk_to_int(context, 4);
		Number tilingValue = duk_to_number(context, 5);
		inst->createTorus(radius,tubeRadius,segmentsW,segmentsH,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createBox(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number d = duk_to_number(context, 2);
		Number h = duk_to_number(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createBox(w,d,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createSphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int numRings = duk_to_int(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createSphere(radius,numRings,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createIcosphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		inst->createIcosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createOctosphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		inst->createOctosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCylinder(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		Number radius = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		bool capped = duk_to_boolean(context, 4);
		Number tilingValue = duk_to_number(context, 5);
		inst->createCylinder(height,radius,numSegments,capped,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCone(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		Number radius = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createCone(height,radius,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_recenterMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->recenterMesh();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_setVertexAtOffset(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		inst->setVertexAtOffset(offset,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertexWithUVAndNormal(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number u = duk_to_number(context, 4);
		Number v = duk_to_number(context, 5);
		Number nx = duk_to_number(context, 6);
		Number ny = duk_to_number(context, 7);
		Number nz = duk_to_number(context, 8);
		inst->addVertexWithUVAndNormal(x,y,z,u,v,nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTexCoord(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number u = duk_to_number(context, 1);
		Number v = duk_to_number(context, 2);
		inst->addTexCoord(u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTexCoord2(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number u = duk_to_number(context, 1);
		Number v = duk_to_number(context, 2);
		inst->addTexCoord2(u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTangent(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->addTangent(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertexWithUV(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number u = duk_to_number(context, 4);
		Number v = duk_to_number(context, 5);
		inst->addVertexWithUV(x,y,z,u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->addVertex(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addNormal(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number nx = duk_to_number(context, 1);
		Number ny = duk_to_number(context, 2);
		Number nz = duk_to_number(context, 3);
		inst->addNormal(nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addBoneAssignments(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number b1Weight = duk_to_number(context, 1);
		int b1Index = duk_to_int(context, 2);
		Number b2Weight = duk_to_number(context, 3);
		int b2Index = duk_to_int(context, 4);
		Number b3Weight = duk_to_number(context, 5);
		int b3Index = duk_to_int(context, 6);
		Number b4Weight = duk_to_number(context, 7);
		int b4Index = duk_to_int(context, 8);
		inst->addBoneAssignments(b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addColor(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->addColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexPosition(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int vertexOffset = duk_to_int(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVertexPosition(vertexOffset);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getVertexPositionAtIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVertexPositionAtIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getVertexTexCoord(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int vertexOffset = duk_to_int(context, 1);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVertexTexCoord(vertexOffset);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getVertexTexCoordAtIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVertexTexCoordAtIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_Copy(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->Copy();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getRadius(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getRadius());
		return 1;
	}

	duk_ret_t Polycode_Mesh_calculateNormals(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		inst->calculateNormals();
		return 0;
	}

	duk_ret_t Polycode_Mesh_calculateTangents(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		inst->calculateTangents();
		return 0;
	}

	duk_ret_t Polycode_Mesh_getMeshType(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getMeshType());
		return 1;
	}

	duk_ret_t Polycode_Mesh_setMeshType(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int newType = duk_to_int(context, 1);
		inst->setMeshType(newType);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getIndexGroupSize(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getIndexGroupSize());
		return 1;
	}

	duk_ret_t Polycode_Mesh_calculateBBox(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->calculateBBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_hasVertexBuffer(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->hasVertexBuffer());
		return 1;
	}

	duk_ret_t Polycode_Mesh_addIndexedFace(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int i1 = duk_to_int(context, 1);
		int i2 = duk_to_int(context, 2);
		inst->addIndexedFace(i1,i2);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		inst->addIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeVertexRange(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int beginRemoveVertex = duk_to_int(context, 1);
		int vertexRemovalCount = duk_to_int(context, 2);
		inst->removeVertexRange(beginRemoveVertex,vertexRemovalCount);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeFace(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		int faceIndex = duk_to_int(context, 1);
		inst->removeFace(faceIndex);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeUnusedVertices(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->removeUnusedVertices());
		return 1;
	}

	duk_ret_t Polycode_Mesh_getIndexCount(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getIndexCount());
		return 1;
	}

	duk_ret_t Polycode_Mesh_subdivideToRadius(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		inst->subdivideToRadius(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_saveAsOBJ(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->saveAsOBJ(fileName);
		return 0;
	}

	duk_ret_t Polycode_Mesh_normalizeBoneWeights(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, 0);
		inst->normalizeBoneWeights();
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_type(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_type(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_name(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_name(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_NumberVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->NumberVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_NumberVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->NumberVal = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_intVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->intVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_intVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->intVal = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_stringVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->stringVal.c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_stringVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->stringVal = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_boolVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->boolVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_boolVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->boolVal = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_length(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->length);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_length(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->length = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__delete(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_readNumber(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		String key = duk_to_string(context, 1);
		Number* out = (Number*)duk_to_pointer(context, 2);
		duk_push_boolean(context, inst->readNumber(key,out));
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_readString(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		String key = duk_to_string(context, 1);
		String* out = (String*)duk_to_pointer(context, 2);
		duk_push_boolean(context, inst->readString(key,out));
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_readBool(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		String key = duk_to_string(context, 1);
		bool* out = (bool*)duk_to_pointer(context, 2);
		duk_push_boolean(context, inst->readBool(key,out));
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_addChild(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->addChild(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_getTypedName(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getTypedName().c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_setTypedName(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		inst->setTypedName(str);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_Clear(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->Clear();
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectReader__get_success(duk_context *context) {
		BinaryObjectReader *inst = (BinaryObjectReader*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->success);
		return 1;
	}

	duk_ret_t Polycode_BinaryObjectReader__set_success(duk_context *context) {
		BinaryObjectReader *inst = (BinaryObjectReader*)duk_to_pointer(context, 0);
		inst->success = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectReader__delete(duk_context *context) {
		BinaryObjectReader *inst = (BinaryObjectReader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter__delete(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_parseKeysFromObjectEntry(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 1);
		inst->parseKeysFromObjectEntry(entry);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_writeEntryToFile(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 1);
		inst->writeEntryToFile(entry);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_addKey(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		String key = duk_to_string(context, 1);
		duk_push_int(context, inst->addKey(key));
		return 1;
	}

	duk_ret_t Polycode_BinaryObjectWriter_getKeyIndex(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		String key = duk_to_string(context, 1);
		duk_push_int(context, inst->getKeyIndex(key));
		return 1;
	}

	duk_ret_t Polycode_BinaryObjectWriter_writeToFile(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->writeToFile(fileName));
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__get_lifetime(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->lifetime);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_lifetime(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->lifetime = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_position(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_position(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_velocity(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->velocity;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_velocity(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->velocity = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_perlinPos(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->perlinPos;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_perlinPos(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->perlinPos = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_rotation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->rotation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_rotation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->rotation = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_brightnessDeviation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->brightnessDeviation);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_brightnessDeviation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->brightnessDeviation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_scale(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->scale);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_scale(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->scale = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_color(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_color(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_varianceIndex(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->varianceIndex);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_varianceIndex(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->varianceIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__delete(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_useScaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->useScaleCurve);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_useScaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->useScaleCurve = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_scaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		BezierCurve *retInst = new BezierCurve();
		*retInst = inst->scaleCurve;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_scaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->scaleCurve = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_useColorCurves(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->useColorCurves);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_useColorCurves(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->useColorCurves = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveR(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		BezierCurve *retInst = new BezierCurve();
		*retInst = inst->colorCurveR;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveR(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveR = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveG(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		BezierCurve *retInst = new BezierCurve();
		*retInst = inst->colorCurveG;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveG(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveG = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveB(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		BezierCurve *retInst = new BezierCurve();
		*retInst = inst->colorCurveB;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveB(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveB = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveA(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		BezierCurve *retInst = new BezierCurve();
		*retInst = inst->colorCurveA;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveA(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveA = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->colorDeviation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorDeviation = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__delete(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleCount(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		int newParticleCount = duk_to_int(context, 1);
		inst->setParticleCount(newParticleCount);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleCount(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getParticleCount());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleLifetime(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Number lifetime = duk_to_number(context, 1);
		inst->setParticleLifetime(lifetime);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleLifetime(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getParticleLifetime());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setDirectionDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 newDeviation = *(Vector3*)duk_to_pointer(context, 1);
		inst->setDirectionDeviation(newDeviation);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getDirectionDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getDirectionDeviation();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setEmitterSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 newSize = *(Vector3*)duk_to_pointer(context, 1);
		inst->setEmitterSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getEmitterSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getEmitterSize();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setGravity(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 newGravity = *(Vector3*)duk_to_pointer(context, 1);
		inst->setGravity(newGravity);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getGravity(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getGravity();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_fixedUpdate(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_Render(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_updateParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->updateParticles();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_rebuildParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->rebuildParticles(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_triggerParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool allAtOnce = duk_to_boolean(context, 1);
		inst->triggerParticles(allAtOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_enableParticleSystem(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->enableParticleSystem(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setUseFloorPlane(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setUseFloorPlane(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorPlaneOffset(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Number floorPlaneOffset = duk_to_number(context, 1);
		inst->setFloorPlaneOffset(floorPlaneOffset);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorDamping(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Number floorDamping = duk_to_number(context, 1);
		inst->setFloorDamping(floorDamping);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticlesInWorldSpace(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setParticlesInWorldSpace(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticlesInWorldSpace(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getParticlesInWorldSpace());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinEnabled(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setPerlinEnabled(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinEnabled(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getPerlinEnabled());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getParticleSpeed());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		inst->setParticleSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinValue(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 perlinValue = *(Vector3*)duk_to_pointer(context, 1);
		inst->setPerlinValue(perlinValue);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinValue(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPerlinValue();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleType(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		int particleType = duk_to_int(context, 1);
		inst->setParticleType(particleType);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleType(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getParticleType());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Number particleSize = duk_to_number(context, 1);
		inst->setParticleSize(particleSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getParticleSize());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleRotationSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 rotationSpeed = *(Vector3*)duk_to_pointer(context, 1);
		inst->setParticleRotationSpeed(rotationSpeed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleRotationSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getParticleRotationSpeed();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleDirection(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 1);
		inst->setParticleDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleDirection(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getParticleDirection();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setLoopParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setLoopParticles(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getLoopParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getLoopParticles());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_addSourceMesh(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 1);
		inst->addSourceMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getNumSourceMeshes(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumSourceMeshes());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getSourcesMeshAtIndex(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSourcesMeshAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_removeSourceMeshAtIndex(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		inst->removeSourceMeshAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_positionParticle(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		inst->positionParticle(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_Clone(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_applyClone(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Perlin__delete(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get2DTiledX(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number t = duk_to_number(context, 3);
		duk_push_number(context, inst->Get2DTiledX(x,y,t));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		duk_push_number(context, inst->Get(x,y));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get2D(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		duk_push_number(context, inst->Get2D(x,y));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get3D(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		duk_push_number(context, inst->Get3D(x,y,z));
		return 1;
	}

	duk_ret_t Polycode_Quaternion__get_x(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->x);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_x(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_y(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->y);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_y(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_z(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->z);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_z(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_w(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->w);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_w(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__delete(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Quaternion_setFromMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Matrix4 _mat = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setFromMatrix(_mat);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Dot(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Quaternion rkQ = *(Quaternion*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->Dot(rkQ));
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Log(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Log();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Exp(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Exp();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Norm(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->Norm());
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Normalize(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->Normalize());
		return 1;
	}

	duk_ret_t Polycode_Quaternion_lookAt(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Vector3 D = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		inst->lookAt(D,upVector);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		inst->createFromMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Inverse(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Inverse();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_set(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		inst->set(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_InvSqrt(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, inst->InvSqrt(x));
		return 1;
	}

	duk_ret_t Polycode_Quaternion_fromAxes(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number az = duk_to_number(context, 1);
		Number ay = duk_to_number(context, 2);
		Number ax = duk_to_number(context, 3);
		inst->fromAxes(az,ay,ax);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_fromAngleAxis(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number rfAngle = duk_to_number(context, 1);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 2);
		inst->fromAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_toEulerAngles(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->toEulerAngles();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_toAngleAxis(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number rfAngle = duk_to_number(context, 1);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 2);
		inst->toAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromAxisAngle(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number degrees = duk_to_number(context, 4);
		inst->createFromAxisAngle(x,y,z,degrees);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->createMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_applyTo(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		Vector3 v = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->applyTo(v);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__get_q1(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->q1;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q1(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q1 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_q2(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->q2;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q2(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q2 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_q3(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->q3;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q3(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q3 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_time(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->time);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_time(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->time = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__delete(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_QuaternionCurve__delete(duk_context *context) {
		QuaternionCurve *inst = (QuaternionCurve*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_QuaternionCurve_interpolate(duk_context *context) {
		QuaternionCurve *inst = (QuaternionCurve*)duk_to_pointer(context, 0);
		Number t = duk_to_number(context, 1);
		bool useShortestPath = duk_to_boolean(context, 2);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->interpolate(t,useShortestPath);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuaternionCurve_generatePointsFromCurves(duk_context *context) {
		QuaternionCurve *inst = (QuaternionCurve*)duk_to_pointer(context, 0);
		BezierCurve* wCurve = (BezierCurve*)duk_to_pointer(context, 1);
		BezierCurve* xCurve = (BezierCurve*)duk_to_pointer(context, 2);
		BezierCurve* yCurve = (BezierCurve*)duk_to_pointer(context, 3);
		BezierCurve* zCurve = (BezierCurve*)duk_to_pointer(context, 4);
		inst->generatePointsFromCurves(wCurve,xCurve,yCurve,zCurve);
		return 0;
	}

	duk_ret_t Polycode_Ray__get_origin(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->origin;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_origin(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->origin = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__get_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__get_inv_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->inv_direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_inv_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->inv_direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__delete(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Ray_boxIntersect(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 1);
		Matrix4 transformMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Number near = duk_to_number(context, 3);
		Number far = duk_to_number(context, 4);
		duk_push_number(context, inst->boxIntersect(box,transformMatrix,near,far));
		return 1;
	}

	duk_ret_t Polycode_Ray_planeIntersectPoint(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 planeNormal = *(Vector3*)duk_to_pointer(context, 1);
		Number planeDistance = duk_to_number(context, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->planeIntersectPoint(planeNormal,planeDistance);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_tranformByMatrix(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		Ray *retInst = new Ray();
		*retInst = inst->tranformByMatrix(matrix);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_closestPointOnRay(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 point = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->closestPointOnRay(point);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_closestPointsBetween(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Ray ray2 = *(Ray*)duk_to_pointer(context, 1);
		Vector3* point1 = (Vector3*)duk_to_pointer(context, 2);
		Vector3* point2 = (Vector3*)duk_to_pointer(context, 3);
		duk_push_boolean(context, inst->closestPointsBetween(ray2,point1,point2));
		return 1;
	}

	duk_ret_t Polycode_Ray_polygonIntersect(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		Vector3 v1 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 2);
		Vector3 v3 = *(Vector3*)duk_to_pointer(context, 3);
		duk_push_boolean(context, inst->polygonIntersect(v1,v2,v3));
		return 1;
	}

	duk_ret_t Polycode_Rectangle__get_x(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->x);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_x(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_y(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->y);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_y(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_w(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->w);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_w(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_h(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->h);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_h(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->h = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__delete(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Rectangle_setRect(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number w = duk_to_number(context, 3);
		Number h = duk_to_number(context, 4);
		inst->setRect(x,y,w,h);
		return 0;
	}

	duk_ret_t Polycode_Rectangle_Clipped(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		Polycode::Rectangle rect = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->Clipped(rect);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Rectangle_minX(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->minX());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_maxX(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->maxX());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_minY(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->minY());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_maxY(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->maxY());
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__get_type(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_type(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__get_customArrayName(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->customArrayName.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_customArrayName(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->customArrayName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__get_hasVBO(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->hasVBO);
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_hasVBO(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->hasVBO = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__delete(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray_getArrayData(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->getArrayData();
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray_getDataSize(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getDataSize());
		return 1;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__get_shadowMatrix(duk_context *context) {
		LightShadowInfoBinding *inst = (LightShadowInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shadowMatrix;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__set_shadowMatrix(duk_context *context) {
		LightShadowInfoBinding *inst = (LightShadowInfoBinding*)duk_to_pointer(context, 0);
		inst->shadowMatrix = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__get_shadowBuffer(duk_context *context) {
		LightShadowInfoBinding *inst = (LightShadowInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shadowBuffer;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__set_shadowBuffer(duk_context *context) {
		LightShadowInfoBinding *inst = (LightShadowInfoBinding*)duk_to_pointer(context, 0);
		inst->shadowBuffer = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__delete(duk_context *context) {
		LightShadowInfoBinding *inst = (LightShadowInfoBinding*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_position(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->position;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_position(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->position = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_direction(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->direction;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_direction(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->direction = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_specular(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->specular;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_specular(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->specular = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_diffuse(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->diffuse;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_diffuse(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->diffuse = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_spotExponent(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->spotExponent;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_spotExponent(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->spotExponent = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_spotCosCutoff(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->spotCosCutoff;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_spotCosCutoff(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->spotCosCutoff = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_constantAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->constantAttenuation;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_constantAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->constantAttenuation = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_linearAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->linearAttenuation;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_linearAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->linearAttenuation = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_quadraticAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->quadraticAttenuation;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_quadraticAttenuation(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->quadraticAttenuation = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__get_shadowEnabled(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->shadowEnabled;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__set_shadowEnabled(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		inst->shadowEnabled = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding__delete(duk_context *context) {
		LightInfoBinding *inst = (LightInfoBinding*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderFrame__delete(duk_context *context) {
		RenderFrame *inst = (RenderFrame*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RendererThreadJob__get_jobType(duk_context *context) {
		RendererThreadJob *inst = (RendererThreadJob*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->jobType);
		return 1;
	}

	duk_ret_t Polycode_RendererThreadJob__set_jobType(duk_context *context) {
		RendererThreadJob *inst = (RendererThreadJob*)duk_to_pointer(context, 0);
		inst->jobType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RendererThreadJob__delete(duk_context *context) {
		RendererThreadJob *inst = (RendererThreadJob*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderThread__delete(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderThread_setGraphicsInterface(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		Core* core = (Core*)duk_to_pointer(context, 1);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*)duk_to_pointer(context, 2);
		inst->setGraphicsInterface(core,graphicsInterface);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_runThread(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		inst->runThread();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_enqueueFrame(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		RenderFrame* frame = (RenderFrame*)duk_to_pointer(context, 1);
		inst->enqueueFrame(frame);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_enqueueJob(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		int jobType = duk_to_int(context, 1);
		void* data = (void*)duk_to_pointer(context, 2);
		void* data2 = (void*)duk_to_pointer(context, 3);
		inst->enqueueJob(jobType,data,data2);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_processJob(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		RendererThreadJob job = *(RendererThreadJob*)duk_to_pointer(context, 1);
		inst->processJob(job);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_getShaderBinding(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderBinding();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_RenderThread_processDrawBuffer(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->processDrawBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_getFrameInfo(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		RenderThreadDebugInfo *retInst = new RenderThreadDebugInfo();
		*retInst = inst->getFrameInfo();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderThread_clearFrameQueue(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		inst->clearFrameQueue();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_initGlobals(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		inst->initGlobals();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_lockRenderMutex(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		inst->lockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_unlockRenderMutex(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, 0);
		inst->unlockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_buffersProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->buffersProcessed);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_buffersProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->buffersProcessed = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_drawCallsProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->drawCallsProcessed);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_drawCallsProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->drawCallsProcessed = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_timeTaken(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->timeTaken);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_timeTaken(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->timeTaken = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__delete(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Renderer__delete(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Renderer_setGraphicsInterface(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Core* core = (Core*)duk_to_pointer(context, 1);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*)duk_to_pointer(context, 2);
		inst->setGraphicsInterface(core,graphicsInterface);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getRenderThread(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderThread();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_createCubemap(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Texture* t0 = (Texture*)duk_to_pointer(context, 1);
		Texture* t1 = (Texture*)duk_to_pointer(context, 2);
		Texture* t2 = (Texture*)duk_to_pointer(context, 3);
		Texture* t3 = (Texture*)duk_to_pointer(context, 4);
		Texture* t4 = (Texture*)duk_to_pointer(context, 5);
		Texture* t5 = (Texture*)duk_to_pointer(context, 6);
		PolyBase *ptrRetVal = (PolyBase*)inst->createCubemap(t0,t1,t2,t3,t4,t5);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_createTexture(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		char* textureData = (char*)duk_to_pointer(context, 3);
		bool clamp = duk_to_boolean(context, 4);
		bool createMipmaps = duk_to_boolean(context, 5);
		int type = duk_to_int(context, 6);
		int filteringMode = duk_to_int(context, 7);
		int anisotropy = duk_to_int(context, 8);
		bool framebufferTexture = duk_to_boolean(context, 9);
		PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width,height,textureData,clamp,createMipmaps,type,filteringMode,anisotropy,framebufferTexture);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_createRenderBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		bool attachDepthBuffer = duk_to_boolean(context, 3);
		bool floatingPoint = duk_to_boolean(context, 4);
		PolyBase *ptrRetVal = (PolyBase*)inst->createRenderBuffer(width,height,attachDepthBuffer,floatingPoint);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_destroyRenderBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		RenderBuffer* buffer = (RenderBuffer*)duk_to_pointer(context, 1);
		inst->destroyRenderBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyTexture(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->destroyTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_Renderer_processDrawBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->processDrawBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setBackingResolutionScale(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Number xScale = duk_to_number(context, 1);
		Number yScale = duk_to_number(context, 2);
		inst->setBackingResolutionScale(xScale,yScale);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleX(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getBackingResolutionScaleX());
		return 1;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleY(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getBackingResolutionScaleY());
		return 1;
	}

	duk_ret_t Polycode_Renderer_createProgram(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->createProgram(fileName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_createShader(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		ShaderProgram* vertexProgram = (ShaderProgram*)duk_to_pointer(context, 1);
		ShaderProgram* fragmentProgram = (ShaderProgram*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->createShader(vertexProgram,fragmentProgram);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_createVertexBuffers(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 1);
		inst->createVertexBuffers(mesh);
		return 0;
	}

	duk_ret_t Polycode_Renderer_enqueueFrameJob(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		int jobType = duk_to_int(context, 1);
		void* data = (void*)duk_to_pointer(context, 2);
		inst->enqueueFrameJob(jobType,data);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyProgram(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		ShaderProgram* program = (ShaderProgram*)duk_to_pointer(context, 1);
		inst->destroyProgram(program);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShader(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Shader* shader = (Shader*)duk_to_pointer(context, 1);
		inst->destroyShader(shader);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		RenderDataArray* array = (RenderDataArray*)duk_to_pointer(context, 1);
		inst->destroyBuffer(array);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShaderBinding(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		ShaderBinding* binding = (ShaderBinding*)duk_to_pointer(context, 1);
		inst->destroyShaderBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShaderParam(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		LocalShaderParam* param = (LocalShaderParam*)duk_to_pointer(context, 1);
		inst->destroyShaderParam(param);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setTextureParam(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		LocalShaderParam* param = (LocalShaderParam*)duk_to_pointer(context, 1);
		Texture* texture = (Texture*)duk_to_pointer(context, 2);
		inst->setTextureParam(param,texture);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setAnisotropyAmount(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Number amount = duk_to_number(context, 1);
		inst->setAnisotropyAmount(amount);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getAnisotropyAmount(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getAnisotropyAmount());
		return 1;
	}

	duk_ret_t Polycode_Renderer_createMesh(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->createMesh(fileName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Renderer_destroyMesh(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 1);
		inst->destroyMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_Renderer_beginFrame(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		inst->beginFrame();
		return 0;
	}

	duk_ret_t Polycode_Renderer_endFrame(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, 0);
		inst->endFrame();
		return 0;
	}

	duk_ret_t Polycode_Resource__get_reloadOnFileModify(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->reloadOnFileModify);
		return 1;
	}

	duk_ret_t Polycode_Resource__set_reloadOnFileModify(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->reloadOnFileModify = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Resource__get_resourceFileTime(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		time_t *retInst = new time_t();
		*retInst = inst->resourceFileTime;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Resource__set_resourceFileTime(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->resourceFileTime = *(time_t*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Resource__delete(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Resource_reloadResource(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourceName(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getResourceName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Resource_getResourceType(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getResourceType());
		return 1;
	}

	duk_ret_t Polycode_Resource_setResourceName(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		String newName = duk_to_string(context, 1);
		inst->setResourceName(newName);
		return 0;
	}

	duk_ret_t Polycode_Resource_setResourcePath(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		inst->setResourcePath(path);
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourcePath(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getResourcePath().c_str());
		return 1;
	}

	duk_ret_t Polycode_ScriptResourceLoader__delete(duk_context *context) {
		ScriptResourceLoader *inst = (ScriptResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ScriptResourceLoader_loadResource(duk_context *context) {
		ScriptResourceLoader *inst = (ScriptResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__get_reloadResourcesOnModify(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->reloadResourcesOnModify);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_reloadResourcesOnModify(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->reloadResourcesOnModify = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_dispatchChangeEvents(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->dispatchChangeEvents);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_dispatchChangeEvents(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->dispatchChangeEvents = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_resourceSubscribers(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->resourceSubscribers);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_resourceSubscribers(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->resourceSubscribers = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_deleteOnUnsubscribe(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->deleteOnUnsubscribe);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_deleteOnUnsubscribe(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->deleteOnUnsubscribe = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__delete(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_setFallbackPool(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->setFallbackPool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_addResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		Resource* resource = (Resource*)duk_to_pointer(context, 1);
		inst->addResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_removeResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		Resource* resource = (Resource*)duk_to_pointer(context, 1);
		inst->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_hasResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		Resource* resource = (Resource*)duk_to_pointer(context, 1);
		duk_push_boolean(context, inst->hasResource(resource));
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadResourcesFromFolder(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		String folder = duk_to_string(context, 1);
		bool recursive = duk_to_boolean(context, 2);
		inst->loadResourcesFromFolder(folder,recursive);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadResourceWithName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		String name = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResourceWithName(path,name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		String resourceName = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResource(resourceType,resourceName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_setName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResourceByPath(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		String resourcePath = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceByPath(resourcePath);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_Update(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResources(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_checkForChangedFiles(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->checkForChangedFiles();
		return 0;
	}

	duk_ret_t Polycode_ResourceManager__delete(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getGlobalPool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getGlobalPool();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_getResourcePoolByName(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourcePoolByName(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_addResourceLoader(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourceLoader* loader = (ResourceLoader*)duk_to_pointer(context, 1);
		inst->addResourceLoader(loader);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResourceLoaderForExtension(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		String extension = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceLoaderForExtension(extension);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_removeResourceLoader(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourceLoader* loader = (ResourceLoader*)duk_to_pointer(context, 1);
		inst->removeResourceLoader(loader);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getNumResourceLoaders(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumResourceLoaders());
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_getResourceLoaderAtIndex(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceLoaderAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_addResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->addResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->removeResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResources(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResource(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		Resource* resource = (Resource*)duk_to_pointer(context, 1);
		inst->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_subscribeToResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->subscribeToResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_unsubscibeFromResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->unsubscibeFromResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_Update(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_FontResourceLoader__delete(duk_context *context) {
		FontResourceLoader *inst = (FontResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_FontResourceLoader_loadResource(duk_context *context) {
		FontResourceLoader *inst = (FontResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ProgramResourceLoader__delete(duk_context *context) {
		ProgramResourceLoader *inst = (ProgramResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramResourceLoader_loadResource(duk_context *context) {
		ProgramResourceLoader *inst = (ProgramResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__get_fileName(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->fileName.c_str());
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__set_fileName(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		inst->fileName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__get_lineNumber(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->lineNumber);
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__set_lineNumber(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		inst->lineNumber = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__delete(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MeshResourceLoader__delete(duk_context *context) {
		MeshResourceLoader *inst = (MeshResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MeshResourceLoader_loadResource(duk_context *context) {
		MeshResourceLoader *inst = (MeshResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_MaterialResourceLoader__delete(duk_context *context) {
		MaterialResourceLoader *inst = (MaterialResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MaterialResourceLoader_loadResource(duk_context *context) {
		MaterialResourceLoader *inst = (MaterialResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_TextureResourceLoader__delete(duk_context *context) {
		TextureResourceLoader *inst = (TextureResourceLoader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_TextureResourceLoader_loadResource(duk_context *context) {
		TextureResourceLoader *inst = (TextureResourceLoader*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path,targetPool);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Scene__get_clearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->clearColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_clearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->clearColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_useClearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->useClearColor);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_useClearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->useClearColor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_useClearDepth(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->useClearDepth);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_useClearDepth(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->useClearDepth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_ambientColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->ambientColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_ambientColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->ambientColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_fogColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->fogColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_fogColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->fogColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_enabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enabled);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_enabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_ownsChildren(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ownsChildren);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_ownsChildren(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->ownsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_rootEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Entity *retInst = new Entity();
		*retInst = inst->rootEntity;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_rootEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->rootEntity = *(Entity*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_sceneMouseRect(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->sceneMouseRect;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_sceneMouseRect(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->sceneMouseRect = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_remapMouse(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->remapMouse);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_remapMouse(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->remapMouse = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_constrainPickingToViewport(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->constrainPickingToViewport);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_constrainPickingToViewport(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->constrainPickingToViewport = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__delete(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Scene_addEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Entity* entity = (Entity*)duk_to_pointer(context, 1);
		inst->addEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_addChild(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Entity* entity = (Entity*)duk_to_pointer(context, 1);
		inst->addChild(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_removeEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Entity* entity = (Entity*)duk_to_pointer(context, 1);
		inst->removeEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_getDefaultCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDefaultCamera();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Scene_getActiveCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getActiveCamera();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Scene_setActiveCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Camera* camera = (Camera*)duk_to_pointer(context, 1);
		inst->setActiveCamera(camera);
		return 0;
	}

	duk_ret_t Polycode_Scene_enableFog(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		bool enable = duk_to_boolean(context, 1);
		inst->enableFog(enable);
		return 0;
	}

	duk_ret_t Polycode_Scene_setFogProperties(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		int fogMode = duk_to_int(context, 1);
		Color color = *(Color*)duk_to_pointer(context, 2);
		Number density = duk_to_number(context, 3);
		Number startDepth = duk_to_number(context, 4);
		Number endDepth = duk_to_number(context, 5);
		inst->setFogProperties(fogMode,color,density,startDepth,endDepth);
		return 0;
	}

	duk_ret_t Polycode_Scene_setSceneType(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		int newType = duk_to_int(context, 1);
		inst->setSceneType(newType);
		return 0;
	}

	duk_ret_t Polycode_Scene_fixedUpdate(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Scene_Update(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Scene_setVirtual(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setVirtual(val);
		return 0;
	}

	duk_ret_t Polycode_Scene_isVirtual(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isVirtual());
		return 1;
	}

	duk_ret_t Polycode_Scene_isEnabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isEnabled());
		return 1;
	}

	duk_ret_t Polycode_Scene_setEnabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		bool enabled = duk_to_boolean(context, 1);
		inst->setEnabled(enabled);
		return 0;
	}

	duk_ret_t Polycode_Scene_Render(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Camera* targetCamera = (Camera*)duk_to_pointer(context, 1);
		RenderBuffer* targetFramebuffer = (RenderBuffer*)duk_to_pointer(context, 2);
		Material* overrideMaterial = (Material*)duk_to_pointer(context, 3);
		bool sendLights = duk_to_boolean(context, 4);
		inst->Render(targetCamera,targetFramebuffer,overrideMaterial,sendLights);
		return 0;
	}

	duk_ret_t Polycode_Scene_setOverrideMaterial(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Material* material = (Material*)duk_to_pointer(context, 1);
		inst->setOverrideMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_Scene_projectRayFromCameraAndViewportCoordinate(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		Camera* camera = (Camera*)duk_to_pointer(context, 1);
		Vector2 coordinate = *(Vector2*)duk_to_pointer(context, 2);
		Ray *retInst = new Ray();
		*retInst = inst->projectRayFromCameraAndViewportCoordinate(camera,coordinate);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene_addLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		SceneLight* light = (SceneLight*)duk_to_pointer(context, 1);
		inst->addLight(light);
		return 0;
	}

	duk_ret_t Polycode_Scene_removeLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		SceneLight* light = (SceneLight*)duk_to_pointer(context, 1);
		inst->removeLight(light);
		return 0;
	}

	duk_ret_t Polycode_Scene_getNumLights(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumLights());
		return 1;
	}

	duk_ret_t Polycode_Scene_getLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLight(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Scene_doVisibilityChecking(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->doVisibilityChecking(val);
		return 0;
	}

	duk_ret_t Polycode_Scene_doesVisibilityChecking(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->doesVisibilityChecking());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry__delete(duk_context *context) {
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry_getInstance(duk_context *context) {
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getInstance();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry_reloadResource(duk_context *context) {
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*)duk_to_pointer(context, 0);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance__get_cloneUsingReload(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->cloneUsingReload);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance__set_cloneUsingReload(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->cloneUsingReload = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance__get_fileName(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->fileName.c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance__set_fileName(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->fileName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance__delete(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_Clone(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_applyClone(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_reloadEntityInstance(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->reloadEntityInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_clearInstance(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->clearInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_parseObjectIntoCurve(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 1);
		BezierCurve* curve = (BezierCurve*)duk_to_pointer(context, 2);
		inst->parseObjectIntoCurve(entry,curve);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_loadObjectEntryIntoEntity(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 1);
		Entity* targetEntity = (Entity*)duk_to_pointer(context, 2);
		int entityFileVersion = duk_to_int(context, 3);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadObjectEntryIntoEntity(entry,targetEntity,entityFileVersion);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_loadFromFile(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->loadFromFile(fileName));
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_applySceneMesh(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 1);
		SceneMesh* sceneMesh = (SceneMesh*)duk_to_pointer(context, 2);
		inst->applySceneMesh(entry,sceneMesh);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_linkResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->linkResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLinkedResourePools(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumLinkedResourePools());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getLinkedResourcePoolAtIndex(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLinkedResourcePoolAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_unlinkResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->unlinkResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getResourceEntry(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceEntry();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getTopLevelResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTopLevelResourcePool();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_hasLayerID(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		char layerID = *(char*)duk_to_pointer(context, 1);
		duk_push_boolean(context, inst->hasLayerID(layerID));
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLayers(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumLayers());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getLayerAtIndex(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLayerAtIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_removeLayer(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		SceneEntityInstanceLayer* layer = (SceneEntityInstanceLayer*)duk_to_pointer(context, 1);
		inst->removeLayer(layer);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_createNewLayer(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->createNewLayer(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getFileName(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getFileName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_name(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_name(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_layerID(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		char *retInst = new char();
		*retInst = inst->layerID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_layerID(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->layerID = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_visible(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->visible);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_visible(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->visible = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_instance(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->instance;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_instance(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->instance = (SceneEntityInstance*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__delete(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer_setLayerVisibility(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setLayerVisibility(val);
		return 0;
	}

	duk_ret_t Polycode_SceneImage__delete(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneImage_Clone(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneImage_applyClone(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_setImageCoordinates(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number width = duk_to_number(context, 3);
		Number height = duk_to_number(context, 4);
		Number realWidth = duk_to_number(context, 5);
		Number realHeight = duk_to_number(context, 6);
		inst->setImageCoordinates(x,y,width,height,realWidth,realHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_getImageWidth(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getImageWidth());
		return 1;
	}

	duk_ret_t Polycode_SceneImage_getImageHeight(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getImageHeight());
		return 1;
	}

	duk_ret_t Polycode_SceneLabel__get_positionAtBaseline(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->positionAtBaseline);
		return 1;
	}

	duk_ret_t Polycode_SceneLabel__set_positionAtBaseline(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		inst->positionAtBaseline = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel__delete(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getText(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getText().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_setLabelActualHeight(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		Number actualHeight = duk_to_number(context, 1);
		inst->setLabelActualHeight(actualHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getLabelActualHeight(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getLabelActualHeight());
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_Render(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getTextWidthForString(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, inst->getTextWidthForString(text));
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_setText(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		String newText = duk_to_string(context, 1);
		inst->setText(newText);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_Clone(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_applyClone(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_updateFromLabel(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		inst->updateFromLabel();
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getLabel(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLabel();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLight__delete(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getIntensity(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getIntensity());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setIntensity(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number newIntensity = duk_to_number(context, 1);
		inst->setIntensity(newIntensity);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number constantAttenuation = duk_to_number(context, 1);
		Number linearAttenuation = duk_to_number(context, 2);
		Number quadraticAttenuation = duk_to_number(context, 3);
		inst->setAttenuation(constantAttenuation,linearAttenuation,quadraticAttenuation);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getConstantAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getConstantAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getLinearAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getLinearAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getQuadraticAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getQuadraticAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getType());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_renderDepthMap(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Scene* scene = (Scene*)duk_to_pointer(context, 1);
		inst->renderDepthMap(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getZBufferTexture(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getZBufferTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setSpecularLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->setSpecularLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setDiffuseLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->setDiffuseLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		inst->setLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setSpotlightProperties(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number spotlightCutoff = duk_to_number(context, 1);
		Number spotlightExponent = duk_to_number(context, 2);
		inst->setSpotlightProperties(spotlightCutoff,spotlightExponent);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightCutoff(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getSpotlightCutoff());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightExponent(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getSpotlightExponent());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_enableShadows(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		int resolution = duk_to_int(context, 2);
		inst->enableShadows(val,resolution);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setShadowMapFOV(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		inst->setShadowMapFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapFOV(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getShadowMapFOV());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapResolution(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getShadowMapResolution());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_areShadowsEnabled(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->areShadowsEnabled());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getLightType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getLightType());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setLightImportance(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		int newImportance = duk_to_int(context, 1);
		inst->setLightImportance(newImportance);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightImportance(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getLightImportance());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setLightType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		int lightType = duk_to_int(context, 1);
		inst->setLightType(lightType);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_Clone(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLight_applyClone(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getParentScene(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentScene();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setParentScene(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		Scene* scene = (Scene*)duk_to_pointer(context, 1);
		inst->setParentScene(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightCamera(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpotlightCamera();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getLightInfo(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, 0);
		LightInfo *retInst = new LightInfo();
		*retInst = inst->getLightInfo();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__get_renderCurve(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->renderCurve);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__set_renderCurve(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		inst->renderCurve = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve__get_curveResolution(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->curveResolution);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__set_curveResolution(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		inst->curveResolution = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve__delete(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_getWorldPointAt(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		Number t = duk_to_number(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getWorldPointAt(t);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve_Update(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_Clone(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve_applyClone(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_getCurve(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurve();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneLine__delete(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setStart(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, 0);
		Vector3 startp = *(Vector3*)duk_to_pointer(context, 1);
		inst->setStart(startp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setEnd(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, 0);
		Vector3 endp = *(Vector3*)duk_to_pointer(context, 1);
		inst->setEnd(endp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_Update(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneManager__delete(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneManager_addScene(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		Scene* newScene = (Scene*)duk_to_pointer(context, 1);
		inst->addScene(newScene);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_removeScene(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		Scene* scene = (Scene*)duk_to_pointer(context, 1);
		inst->removeScene(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_Update(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_fixedUpdate(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_Render(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		inst->Render(viewport);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_renderVirtual(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		inst->renderVirtual();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_registerRenderTexture(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*)duk_to_pointer(context, 1);
		inst->registerRenderTexture(renderTexture);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_unregisterRenderTexture(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*)duk_to_pointer(context, 1);
		inst->unregisterRenderTexture(renderTexture);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_setRenderer(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, 0);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 1);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_lineWidth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->lineWidth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_lineWidth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->lineWidth = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_lineSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->lineSmooth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_lineSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->lineSmooth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_pointSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->pointSmooth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_pointSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->pointSmooth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_ownsMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ownsMesh);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_ownsMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->ownsMesh = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_ownsSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ownsSkeleton);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_ownsSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->ownsSkeleton = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_useGeometryHitDetection(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->useGeometryHitDetection);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_useGeometryHitDetection(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->useGeometryHitDetection = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_alphaTest(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->alphaTest);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_alphaTest(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->alphaTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_backfaceCulled(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->backfaceCulled);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_backfaceCulled(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->backfaceCulled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_sendBoneMatricesToMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->sendBoneMatricesToMaterial);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_sendBoneMatricesToMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->sendBoneMatricesToMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__delete(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_Render(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_getNumShaderPasses(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_addShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		inst->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_removeShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		int shaderIndex = duk_to_int(context, 1);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getMesh();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_getMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getMaterial();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_loadSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadSkeleton(fileName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_clearMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->clearMaterial();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Material* material = (Material*)duk_to_pointer(context, 1);
		inst->setMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_rebuildAttributes(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->rebuildAttributes();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMaterialByName(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		String materialName = duk_to_string(context, 1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 2);
		inst->setMaterialByName(materialName,resourcePool);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 1);
		inst->setMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Skeleton* skeleton = (Skeleton*)duk_to_pointer(context, 1);
		inst->setSkeleton(skeleton);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSkeleton();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_applySkeletonLocally(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->applySkeletonLocally();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setLineWidth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Number newWidth = duk_to_number(context, 1);
		inst->setLineWidth(newWidth);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getFilename(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getFilename().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_setFilename(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->setFilename(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_loadFromFile(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadFromFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_customHitDetection(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		duk_push_boolean(context, inst->customHitDetection(ray));
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_setForceMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		bool forceMaterial = duk_to_boolean(context, 1);
		inst->setForceMaterial(forceMaterial);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getForceMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getForceMaterial());
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_Clone(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_applyClone(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive__delete(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_setPrimitiveOptions(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		Number v1 = duk_to_number(context, 2);
		Number v2 = duk_to_number(context, 3);
		Number v3 = duk_to_number(context, 4);
		Number v4 = duk_to_number(context, 5);
		Number v5 = duk_to_number(context, 6);
		inst->setPrimitiveOptions(type,v1,v2,v3,v4,v5);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_recreatePrimitive(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		inst->recreatePrimitive();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveType(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getPrimitiveType());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter1(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPrimitiveParameter1());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter2(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPrimitiveParameter2());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter3(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPrimitiveParameter3());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter4(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPrimitiveParameter4());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter5(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPrimitiveParameter5());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_Clone(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_applyClone(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture__get_enabled(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enabled);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture__set_enabled(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture__delete(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_getFilterColorBufferTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getFilterColorBufferTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_getFilterZBufferTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getFilterZBufferTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_Render(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_saveToImage(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->saveToImage();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_resizeRenderTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		int newWidth = duk_to_int(context, 1);
		int newHeight = duk_to_int(context, 2);
		inst->resizeRenderTexture(newWidth,newHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetScene(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetScene();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetCamera(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetCamera();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSound__delete(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSound_Update(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_Clone(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSound_applyClone(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_isDirectionalSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isDirectionalSound());
		return 1;
	}

	duk_ret_t Polycode_SceneSound_setDirectionalSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setDirectionalSound(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_getSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSound();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSound_setLoopOnLoad(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setLoopOnLoad(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_getLoopOnLoad(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getLoopOnLoad());
		return 1;
	}

	duk_ret_t Polycode_SceneSoundListener__delete(duk_context *context) {
		SceneSoundListener *inst = (SceneSoundListener*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSoundListener_Update(duk_context *context) {
		SceneSoundListener *inst = (SceneSoundListener*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite__delete(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_Clone(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone,ignoreEditorOnly);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_applyClone(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		Entity* clone = (Entity*)duk_to_pointer(context, 1);
		bool deepClone = duk_to_boolean(context, 2);
		bool ignoreEditorOnly = duk_to_boolean(context, 3);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getSpriteSet(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteSet();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentSprite(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentSprite();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteSet(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		SpriteSet* spriteSet = (SpriteSet*)duk_to_pointer(context, 1);
		inst->setSpriteSet(spriteSet);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteByName(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		String spriteName = duk_to_string(context, 1);
		inst->setSpriteByName(spriteName);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setCurrentFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		int frameIndex = duk_to_int(context, 1);
		inst->setCurrentFrame(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getCurrentFrame());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_Update(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_Render(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 1);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getSpriteBoundingBox(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getSpriteBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setPaused(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setPaused(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_isPaused(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isPaused());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setSprite(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		Sprite* spriteEntry = (Sprite*)duk_to_pointer(context, 1);
		inst->setSprite(spriteEntry);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteState(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		SpriteState* spriteState = (SpriteState*)duk_to_pointer(context, 1);
		int startingFrame = duk_to_int(context, 2);
		bool playOnce = duk_to_boolean(context, 3);
		inst->setSpriteState(spriteState,startingFrame,playOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteStateByName(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		int startingFrame = duk_to_int(context, 2);
		bool playOnce = duk_to_boolean(context, 3);
		inst->setSpriteStateByName(name,startingFrame,playOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentSpriteState(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentSpriteState();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_getStartOnRandomFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getStartOnRandomFrame());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setStartOnRandomFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->setStartOnRandomFrame(val);
		return 0;
	}

	duk_ret_t Polycode_Sprite__delete(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Sprite_getName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Sprite_setName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Sprite_addSpriteState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		SpriteState* state = (SpriteState*)duk_to_pointer(context, 1);
		inst->addSpriteState(state);
		return 0;
	}

	duk_ret_t Polycode_Sprite_removeSpriteState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		SpriteState* state = (SpriteState*)duk_to_pointer(context, 1);
		inst->removeSpriteState(state);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getNumStates(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumStates());
		return 1;
	}

	duk_ret_t Polycode_Sprite_getState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getState(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Sprite_getStateByName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getStateByName(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Sprite_setParentSpritSet(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		SpriteSet* spriteSet = (SpriteSet*)duk_to_pointer(context, 1);
		inst->setParentSpritSet(spriteSet);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getParentSpriteSet(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentSpriteSet();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet__delete(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_loadTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		String imageFileName = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadTexture(imageFileName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteEntry(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		Sprite* newEntry = (Sprite*)duk_to_pointer(context, 1);
		inst->addSpriteEntry(newEntry);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumSpriteEntries(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumSpriteEntries());
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteEntry(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteEntry(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_removeSprite(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		Sprite* sprite = (Sprite*)duk_to_pointer(context, 1);
		inst->removeSprite(sprite);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_loadSpriteSet(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadSpriteSet(fileName);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 1);
		bool assignID = duk_to_boolean(context, 2);
		inst->addSpriteFrame(frame,assignID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumFrames());
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		SpriteFrame *retInst = new SpriteFrame();
		*retInst = inst->getSpriteFrame(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrameByID(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int frameID = duk_to_int(context, 1);
		SpriteFrame *retInst = new SpriteFrame();
		*retInst = inst->getSpriteFrameByID(frameID);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_removeFrameByID(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int frameID = duk_to_int(context, 1);
		inst->removeFrameByID(frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 1);
		inst->setSpriteFrame(frame);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_clearFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		inst->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createGridFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int xCount = duk_to_int(context, 1);
		int yCount = duk_to_int(context, 2);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 3);
		inst->createGridFrames(xCount,yCount,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createFramesFromIslands(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		int minDistance = duk_to_int(context, 1);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 2);
		inst->createFramesFromIslands(minDistance,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteByName(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, 0);
		String spriteName = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteByName(spriteName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__get_coordinates(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->coordinates;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_coordinates(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->coordinates = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__get_anchorPoint(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->anchorPoint;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_anchorPoint(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->anchorPoint = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__get_frameID(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->frameID);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_frameID(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->frameID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__delete(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteState__delete(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setName(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getName(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getNumFrameIDs(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumFrameIDs());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getFrameIDAtIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		duk_push_int(context, inst->getFrameIDAtIndex(index));
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getMeshForFrameIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getMeshForFrameIndex(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_insertFrame(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		int frameID = duk_to_int(context, 2);
		inst->insertFrame(index,frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_removeFrameByIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		int frameIndex = duk_to_int(context, 1);
		inst->removeFrameByIndex(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_clearFrames(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		inst->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setPixelsPerUnit(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Number ppu = duk_to_number(context, 1);
		inst->setPixelsPerUnit(ppu);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getPixelsPerUnit(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPixelsPerUnit());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_rebuildStateMeshes(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		inst->rebuildStateMeshes();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setStateFPS(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Number fps = duk_to_number(context, 1);
		inst->setStateFPS(fps);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getStateFPS(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getStateFPS());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getLargestFrameBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getLargestFrameBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_setBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Vector2 boundingBox = *(Vector2*)duk_to_pointer(context, 1);
		inst->setBoundingBox(boundingBox);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getSpriteOffset(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getSpriteOffset();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_setSpriteOffset(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, 0);
		Vector2 offset = *(Vector2*)duk_to_pointer(context, 1);
		inst->setSpriteOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_JSScriptInstance__delete(duk_context *context) {
		JSScriptInstance *inst = (JSScriptInstance*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_LuaScriptInstance__get_tableRef(duk_context *context) {
		LuaScriptInstance *inst = (LuaScriptInstance*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->tableRef);
		return 1;
	}

	duk_ret_t Polycode_LuaScriptInstance__set_tableRef(duk_context *context) {
		LuaScriptInstance *inst = (LuaScriptInstance*)duk_to_pointer(context, 0);
		inst->tableRef = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LuaScriptInstance__delete(duk_context *context) {
		LuaScriptInstance *inst = (LuaScriptInstance*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ScriptInstance__get_script(duk_context *context) {
		ScriptInstance *inst = (ScriptInstance*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->script;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ScriptInstance__set_script(duk_context *context) {
		ScriptInstance *inst = (ScriptInstance*)duk_to_pointer(context, 0);
		inst->script = (Script*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ScriptInstance__delete(duk_context *context) {
		ScriptInstance *inst = (ScriptInstance*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__get_name(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__set_name(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__get_type(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__set_type(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__get_globalParam(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->globalParam;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__set_globalParam(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		inst->globalParam = (LocalShaderParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__delete(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__get_size(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->size);
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__set_size(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		inst->size = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__get_name(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__set_name(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__delete(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_id(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_id(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_width(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->width);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_width(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->width = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_height(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->height);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_height(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->height = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_sizeMode(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->sizeMode);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_sizeMode(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->sizeMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_buffer(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->buffer;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_buffer(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->buffer = (RenderBuffer*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_normalizedWidth(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->normalizedWidth);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_normalizedWidth(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->normalizedWidth = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_normalizedHeight(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->normalizedHeight);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_normalizedHeight(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->normalizedHeight = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__delete(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_id(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_id(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_name(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_name(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_mode(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->mode);
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_mode(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->mode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_buffer(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->buffer;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_buffer(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->buffer = (RenderBuffer*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__delete(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Shader__get_numSpotLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->numSpotLights);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_numSpotLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->numSpotLights = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_numPointLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->numPointLights);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_numPointLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->numPointLights = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_screenShader(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->screenShader);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_screenShader(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->screenShader = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_vertexProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->vertexProgram;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_vertexProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->vertexProgram = (ShaderProgram*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_fragmentProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->fragmentProgram;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_fragmentProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->fragmentProgram = (ShaderProgram*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_name(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_Shader__set_name(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__delete(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Shader_getType(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getType());
		return 1;
	}

	duk_ret_t Polycode_Shader_setName(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_getName(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Shader_getParamPointer(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getParamPointer(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Shader_getAttribPointer(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttribPointer(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Shader_reload(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->reload();
		return 0;
	}

	duk_ret_t Polycode_Shader_getExpectedParamType(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		duk_push_int(context, inst->getExpectedParamType(name));
		return 1;
	}

	duk_ret_t Polycode_Shader_setVertexProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		ShaderProgram* vp = (ShaderProgram*)duk_to_pointer(context, 1);
		inst->setVertexProgram(vp);
		return 0;
	}

	duk_ret_t Polycode_Shader_setFragmentProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		ShaderProgram* fp = (ShaderProgram*)duk_to_pointer(context, 1);
		inst->setFragmentProgram(fp);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_name(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_name(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_type(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_type(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_ownsPointer(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->ownsPointer);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_ownsPointer(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->ownsPointer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_arraySize(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->arraySize);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_arraySize(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->arraySize = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_param(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->param;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_param(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->param = (ProgramParam*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__delete(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_Copy(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->Copy();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getNumber(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getNumber());
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector2(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVector2();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector3(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVector3();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getMatrix4(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getMatrix4();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getColor(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Color *retInst = new Color();
		*retInst = inst->getColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setNumber(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		inst->setNumber(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector2(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Vector2 x = *(Vector2*)duk_to_pointer(context, 1);
		inst->setVector2(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector3(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Vector3 x = *(Vector3*)duk_to_pointer(context, 1);
		inst->setVector3(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setMatrix4(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Matrix4 x = *(Matrix4*)duk_to_pointer(context, 1);
		inst->setMatrix4(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setColor(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Color x = *(Color*)duk_to_pointer(context, 1);
		inst->setColor(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setTexture(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getTexture(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setCubemap(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		Cubemap* cubemap = (Cubemap*)duk_to_pointer(context, 1);
		inst->setCubemap(cubemap);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getCubemap(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getCubemap();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setParamValueFromString(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		String pvalue = duk_to_string(context, 2);
		inst->setParamValueFromString(type,pvalue);
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram__get_type(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_ShaderProgram__set_type(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram__delete(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram_reloadProgram(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->reloadProgram();
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram_reloadResource(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__get_name(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_name(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__get_vertexData(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->vertexData;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_vertexData(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->vertexData = (VertexDataArray*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__get_attribute(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->attribute;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_attribute(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->attribute = (ProgramAttribute*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__get_enabled(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->enabled);
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_enabled(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__delete(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding__get_resetAttributes(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->resetAttributes);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding__set_resetAttributes(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		inst->resetAttributes = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding__get_targetShader(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->targetShader;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding__set_targetShader(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		inst->targetShader = (Shader*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding__get_accessMutex(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->accessMutex;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding__set_accessMutex(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		inst->accessMutex = (CoreMutex*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding__delete(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_copyTo(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		ShaderBinding* targetBinding = (ShaderBinding*)duk_to_pointer(context, 1);
		inst->copyTo(targetBinding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		String name = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->addParam(type,name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_addParamPointer(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		String name = duk_to_string(context, 2);
		void* ptr = (void*)duk_to_pointer(context, 3);
		PolyBase *ptrRetVal = (PolyBase*)inst->addParamPointer(type,name,ptr);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumLocalParams(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumLocalParams());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParam(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParamByName(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParamByName(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_removeParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->removeParam(name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_loadTextureForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String paramName = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->loadTextureForParam(paramName,fileName);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_setTextureForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String paramName = duk_to_string(context, 1);
		Texture* texture = (Texture*)duk_to_pointer(context, 2);
		inst->setTextureForParam(paramName,texture);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_setCubemapForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String paramName = duk_to_string(context, 1);
		Cubemap* cubemap = (Cubemap*)duk_to_pointer(context, 2);
		inst->setCubemapForParam(paramName,cubemap);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumAttributeBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumAttributeBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getAttributeBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttributeBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_addAttributeBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		VertexDataArray* dataArray = (VertexDataArray*)duk_to_pointer(context, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->addAttributeBinding(name,dataArray);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getAttributeBindingByName(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttributeBindingByName(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_addRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		RenderTargetBinding* binding = (RenderTargetBinding*)duk_to_pointer(context, 1);
		inst->addRenderTargetBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_removeRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		RenderTargetBinding* binding = (RenderTargetBinding*)duk_to_pointer(context, 1);
		inst->removeRenderTargetBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumRenderTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumRenderTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderTargetBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumInTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumInTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getInTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getInTargetBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumColorTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumColorTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getColorTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getColorTargetBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumDepthTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumDepthTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getDepthTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDepthTargetBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumOutTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumOutTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getOutTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getOutTargetBinding(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation__delete(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_addBoneTrack(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		BoneTrack* boneTrack = (BoneTrack*)duk_to_pointer(context, 1);
		inst->addBoneTrack(boneTrack);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getName(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation_Play(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		bool once = duk_to_boolean(context, 1);
		inst->Play(once);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Stop(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Reset(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Update(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setSpeed(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		inst->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setWeight(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		Number newWeight = duk_to_number(context, 1);
		inst->setWeight(newWeight);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getWeight(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getWeight());
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation_isPlaying(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isPlaying());
		return 1;
	}

	duk_ret_t Polycode_Skeleton__delete(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Skeleton_loadSkeleton(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadSkeleton(fileName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_playAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String animName = duk_to_string(context, 1);
		Number weight = duk_to_number(context, 2);
		bool once = duk_to_boolean(context, 3);
		bool restartIfPlaying = duk_to_boolean(context, 4);
		inst->playAnimationByName(animName,weight,once,restartIfPlaying);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_playAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 1);
		Number weight = duk_to_number(context, 2);
		bool once = duk_to_boolean(context, 3);
		bool restartIfPlaying = duk_to_boolean(context, 4);
		inst->playAnimation(animation,weight,once,restartIfPlaying);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_setBaseAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String animName = duk_to_string(context, 1);
		inst->setBaseAnimationByName(animName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_setBaseAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 1);
		inst->setBaseAnimation(animation);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAllAnimations(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		inst->stopAllAnimations();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBaseAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getBaseAnimation();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_addAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		inst->addAnimation(name,fileName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getAnimation(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_stopAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		inst->stopAnimationByName(name);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 1);
		inst->stopAnimation(animation);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_Update(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getBoneByName(name);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_bonesVisible(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		inst->bonesVisible(val);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getNumBones(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumBones());
		return 1;
	}

	duk_ret_t Polycode_Skeleton_getBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getBone(index);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_addBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		Bone* bone = (Bone*)duk_to_pointer(context, 1);
		inst->addBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_removeBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		Bone* bone = (Bone*)duk_to_pointer(context, 1);
		inst->removeBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneIndexByBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, 0);
		Bone* bone = (Bone*)duk_to_pointer(context, 1);
		duk_push_int(context, inst->getBoneIndexByBone(bone));
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__get_scaleX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->scaleX;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_scaleX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->scaleX = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_scaleY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->scaleY;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_scaleY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->scaleY = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_scaleZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->scaleZ;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_scaleZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->scaleZ = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_QuatW(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->QuatW;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_QuatW(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->QuatW = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_QuatX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->QuatX;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_QuatX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->QuatX = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_QuatY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->QuatY;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_QuatY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->QuatY = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_QuatZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->QuatZ;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_QuatZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->QuatZ = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_LocX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->LocX;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_LocX(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->LocX = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_LocY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->LocY;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_LocY(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->LocY = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_LocZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->LocZ;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_LocZ(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->LocZ = (BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_position(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_position(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_scale(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		Vector3 *retInst = new Vector3();
		*retInst = inst->scale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_scale(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->scale = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_boneQuat(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		Quaternion *retInst = new Quaternion();
		*retInst = inst->boneQuat;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_boneQuat(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->boneQuat = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_quatCurve(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->quatCurve;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_quatCurve(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->quatCurve = (QuaternionCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_weight(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->weight);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_weight(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->weight = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__delete(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Play(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		bool once = duk_to_boolean(context, 1);
		inst->Play(once);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Stop(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Update(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Reset(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_setSpeed(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		inst->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_Sound__delete(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Sound_getSampleAsNumber(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		int channel = duk_to_int(context, 2);
		duk_push_number(context, inst->getSampleAsNumber(offset,channel));
		return 1;
	}

	duk_ret_t Polycode_Sound_loadFile(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_Sound_Play(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		bool loop = duk_to_boolean(context, 1);
		bool restartSound = duk_to_boolean(context, 2);
		inst->Play(loop,restartSound);
		return 0;
	}

	duk_ret_t Polycode_Sound_Stop(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_Sound_setVolume(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number newVolume = duk_to_number(context, 1);
		inst->setVolume(newVolume);
		return 0;
	}

	duk_ret_t Polycode_Sound_getVolume(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getVolume());
		return 1;
	}

	duk_ret_t Polycode_Sound_setPitch(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number newPitch = duk_to_number(context, 1);
		inst->setPitch(newPitch);
		return 0;
	}

	duk_ret_t Polycode_Sound_getPitch(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPitch());
		return 1;
	}

	duk_ret_t Polycode_Sound_isPlaying(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isPlaying());
		return 1;
	}

	duk_ret_t Polycode_Sound_isLooped(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isLooped());
		return 1;
	}

	duk_ret_t Polycode_Sound_setIsPositional(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		bool isPositional = duk_to_boolean(context, 1);
		inst->setIsPositional(isPositional);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundPosition(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 1);
		inst->setSoundPosition(position);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundVelocity(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Vector3 velocity = *(Vector3*)duk_to_pointer(context, 1);
		inst->setSoundVelocity(velocity);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundDirection(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 1);
		inst->setSoundDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_Sound_setOffset(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		inst->setOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_Sound_getFileName(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->getFileName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Sound_getPlaybackDuration(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPlaybackDuration());
		return 1;
	}

	duk_ret_t Polycode_Sound_getPlaybackTime(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getPlaybackTime());
		return 1;
	}

	duk_ret_t Polycode_Sound_seekTo(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number time = duk_to_number(context, 1);
		inst->seekTo(time);
		return 0;
	}

	duk_ret_t Polycode_Sound_getOffset(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getOffset());
		return 1;
	}

	duk_ret_t Polycode_Sound_getSampleLength(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getSampleLength());
		return 1;
	}

	duk_ret_t Polycode_Sound_getFrequency(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getFrequency());
		return 1;
	}

	duk_ret_t Polycode_Sound_setPositionalProperties(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number referenceDistance = duk_to_number(context, 1);
		Number maxDistance = duk_to_number(context, 2);
		inst->setPositionalProperties(referenceDistance,maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setReferenceDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number referenceDistance = duk_to_number(context, 1);
		inst->setReferenceDistance(referenceDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setMaxDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		Number maxDistance = duk_to_number(context, 1);
		inst->setMaxDistance(maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_getReferenceDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getReferenceDistance());
		return 1;
	}

	duk_ret_t Polycode_Sound_getMaxDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getMaxDistance());
		return 1;
	}

	duk_ret_t Polycode_Sound_loadBytes(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		char* data = (char*)duk_to_pointer(context, 1);
		int size = duk_to_int(context, 2);
		int channels = duk_to_int(context, 3);
		int freq = duk_to_int(context, 4);
		SoundFormat format = *(SoundFormat*)duk_to_pointer(context, 5);
		duk_push_boolean(context, inst->loadBytes(data,size,channels,freq,format));
		return 1;
	}

	duk_ret_t Polycode_Sound_loadWAV(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->loadWAV(fileName));
		return 1;
	}

	duk_ret_t Polycode_Sound_loadOGG(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, inst->loadOGG(fileName));
		return 1;
	}

	duk_ret_t Polycode_Sound_soundCheck(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		bool result = duk_to_boolean(context, 1);
		String err = duk_to_string(context, 2);
		inst->soundCheck(result,err);
		return 0;
	}

	duk_ret_t Polycode_Sound_updateStream(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, 0);
		int streamCount = duk_to_int(context, 1);
		inst->updateStream(streamCount);
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource__delete(duk_context *context) {
		AudioStreamingSource *inst = (AudioStreamingSource*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource_getNumChannels(duk_context *context) {
		AudioStreamingSource *inst = (AudioStreamingSource*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getNumChannels());
		return 1;
	}

	duk_ret_t Polycode_AudioStreamingSource_getFrequency(duk_context *context) {
		AudioStreamingSource *inst = (AudioStreamingSource*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getFrequency());
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__get_globalVolume(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->globalVolume);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__set_globalVolume(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		inst->globalVolume = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AudioMixer__get_mixerMutex(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->mixerMutex;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__set_mixerMutex(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		inst->mixerMutex = (CoreMutex*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AudioMixer__delete(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_AudioMixer_mixIntoBuffer(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		int16_t* buffer = (int16_t*)duk_to_pointer(context, 1);
		int numSamples = duk_to_int(context, 2);
		inst->mixIntoBuffer(buffer,numSamples);
		return 0;
	}

	duk_ret_t Polycode_SoundManager__delete(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerPosition(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 1);
		inst->setListenerPosition(position);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerOrientation(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		Vector3 orientation = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		inst->setListenerOrientation(orientation,upVector);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_recordSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		int rate = duk_to_int(context, 1);
		int sampleSize = duk_to_int(context, 2);
		duk_push_boolean(context, inst->recordSound(rate,sampleSize));
		return 1;
	}

	duk_ret_t Polycode_SoundManager_stopRecording(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		bool generateFloatBuffer = duk_to_boolean(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->stopRecording(generateFloatBuffer);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_SoundManager_setAudioInterface(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		AudioInterface* audioInterface = (AudioInterface*)duk_to_pointer(context, 1);
		inst->setAudioInterface(audioInterface);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_Update(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setGlobalVolume(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		Number globalVolume = duk_to_number(context, 1);
		inst->setGlobalVolume(globalVolume);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_registerSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		Sound* sound = (Sound*)duk_to_pointer(context, 1);
		inst->registerSound(sound);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_unregisterSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, 0);
		Sound* sound = (Sound*)duk_to_pointer(context, 1);
		inst->unregisterSound(sound);
		return 0;
	}

	duk_ret_t Polycode_String__get_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		string *retInst = new string();
		*retInst = inst->contents;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String__set_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		inst->contents = *(string*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String__get_w_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		wstring *retInst = new wstring();
		*retInst = inst->w_contents;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String__set_w_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		inst->w_contents = *(wstring*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String__delete(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_String_size(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		size_t *retInst = new size_t();
		*retInst = inst->size();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_length(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		size_t *retInst = new size_t();
		*retInst = inst->length();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_substr(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		size_t n = *(size_t*)duk_to_pointer(context, 2);
		duk_push_string(context, inst->substr(pos,n).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_rfind(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		size_t *retInst = new size_t();
		*retInst = inst->rfind(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		size_t *retInst = new size_t();
		*retInst = inst->find(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find_last_of(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		size_t *retInst = new size_t();
		*retInst = inst->find_last_of(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find_first_of(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		size_t *retInst = new size_t();
		*retInst = inst->find_first_of(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_toLowerCase(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->toLowerCase().c_str());
		return 1;
	}

	duk_ret_t Polycode_String_toUpperCase(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		duk_push_string(context, inst->toUpperCase().c_str());
		return 1;
	}

	duk_ret_t Polycode_String_split(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String delim = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String_replace(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		String what = duk_to_string(context, 1);
		String withWhat = duk_to_string(context, 2);
		duk_push_string(context, inst->replace(what,withWhat).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_toNumber(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->toNumber());
		return 1;
	}

	duk_ret_t Polycode_String_toInteger(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->toInteger());
		return 1;
	}

	duk_ret_t Polycode_String_c_str(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->c_str();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_String_getDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDataWithEncoding(encoding);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_String_getWDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		PolyBase *ptrRetVal = (PolyBase*)inst->getWDataWithEncoding(encoding);
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_String_append(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		char c = *(char*)duk_to_pointer(context, 1);
		inst->append(c);
		return 0;
	}

	duk_ret_t Polycode_String_getDataSizeWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		size_t *retInst = new size_t();
		*retInst = inst->getDataSizeWithEncoding(encoding);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_setDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		char* data = (char*)duk_to_pointer(context, 1);
		int encoding = duk_to_int(context, 2);
		inst->setDataWithEncoding(data,encoding);
		return 0;
	}

	duk_ret_t Polycode_String_isNumber(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isNumber());
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__get_colorTexture(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->colorTexture;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__set_colorTexture(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->colorTexture = (Texture*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer__get_depthTexture(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->depthTexture;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__set_depthTexture(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->depthTexture = (Texture*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer__delete(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer_getWidth(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getWidth());
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer_getHeight(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Texture__get_clamp(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->clamp);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_clamp(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->clamp = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_textureData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->textureData;
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_textureData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->textureData = (char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_type(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->type);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_type(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_filteringMode(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->filteringMode);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_filteringMode(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->filteringMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_createMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->createMipmaps);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_createMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->createMipmaps = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_anisotropy(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->anisotropy);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_anisotropy(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->anisotropy = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_framebufferTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->framebufferTexture);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_framebufferTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->framebufferTexture = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_depthTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->depthTexture);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_depthTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->depthTexture = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__delete(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Texture_reloadResource(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_Texture_setImageData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		Image* data = (Image*)duk_to_pointer(context, 1);
		inst->setImageData(data);
		return 0;
	}

	duk_ret_t Polycode_Texture_getTextureData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTextureData();
		duk_push_pointer(context, (void*)ptrRetVal);
		return 1;
	}

	duk_ret_t Polycode_Texture_getWidth(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Texture_getHeight(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Texture_setCreateMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		bool createMipmapsIn = duk_to_boolean(context, 1);
		inst->setCreateMipmaps(createMipmapsIn);
		return 0;
	}

	duk_ret_t Polycode_Texture_getCreateMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->getCreateMipmaps());
		return 1;
	}

	duk_ret_t Polycode_Timer__delete(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Timer_Pause(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		bool paused = duk_to_boolean(context, 1);
		inst->Pause(paused);
		return 0;
	}

	duk_ret_t Polycode_Timer_isPaused(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->isPaused());
		return 1;
	}

	duk_ret_t Polycode_Timer_getTicks(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		duk_push_int(context, inst->getTicks());
		return 1;
	}

	duk_ret_t Polycode_Timer_Update(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		int ticks = duk_to_int(context, 1);
		inst->Update(ticks);
		return 0;
	}

	duk_ret_t Polycode_Timer_Reset(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_Timer_hasElapsed(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		duk_push_boolean(context, inst->hasElapsed());
		return 1;
	}

	duk_ret_t Polycode_Timer_getElapsedf(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->getElapsedf());
		return 1;
	}

	duk_ret_t Polycode_Timer_setTimerInterval(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, 0);
		int msecs = duk_to_int(context, 1);
		inst->setTimerInterval(msecs);
		return 0;
	}

	duk_ret_t Polycode_Vector2__get_x(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->x);
		return 1;
	}

	duk_ret_t Polycode_Vector2__set_x(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector2__get_y(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->y);
		return 1;
	}

	duk_ret_t Polycode_Vector2__set_y(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector2__delete(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector2_set(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		inst->set(x,y);
		return 0;
	}

	duk_ret_t Polycode_Vector2_distance(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->distance(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_length(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->length());
		return 1;
	}

	duk_ret_t Polycode_Vector2_dot(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		Vector2 u = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->dot(u));
		return 1;
	}

	duk_ret_t Polycode_Vector2_crossProduct(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->crossProduct(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_angle(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->angle(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_Normalize(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		inst->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector3__get_x(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->x);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_x(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__get_y(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->y);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_y(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__get_z(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->z);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_z(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__delete(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector3_set(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->set(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Vector3_distance(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->distance(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector3_angleBetween(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Vector3 dest = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->angleBetween(dest));
		return 1;
	}

	duk_ret_t Polycode_Vector3_length(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->length());
		return 1;
	}

	duk_ret_t Polycode_Vector3_lengthSquared(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->lengthSquared());
		return 1;
	}

	duk_ret_t Polycode_Vector3_setLength(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Number newLength = duk_to_number(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->setLength(newLength);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Vector3_dot(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Vector3 u = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->dot(u));
		return 1;
	}

	duk_ret_t Polycode_Vector3_crossProduct(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 *retInst = new Vector3();
		*retInst = inst->crossProduct(vec2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Vector3_Normalize(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_x(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->x);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_x(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_y(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->y);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_y(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_z(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->z);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_z(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_w(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		duk_push_number(context, inst->w);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_w(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__delete(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector4_set(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number w = duk_to_number(context, 4);
		inst->set(x,y,z,w);
		return 0;
	}

	duk_ret_t Polycode_Vector4_dot(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		Vector4 u = *(Vector4*)duk_to_pointer(context, 1);
		duk_push_number(context, inst->dot(u));
		return 1;
	}



}
