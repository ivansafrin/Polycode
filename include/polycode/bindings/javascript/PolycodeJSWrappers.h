#pragma once

#include <memory>

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
#include "polycode/core/PolyRendererPlatformData.h"
#include "polycode/core/PolyResource.h"
#include "polycode/core/PolyResourceManager.h"
#include "polycode/core/PolyScene.h"
#include "polycode/core/PolySceneEntityInstance.h"
#include "polycode/core/PolySceneLabel.h"
#include "polycode/core/PolySceneLight.h"
#include "polycode/core/PolySceneLine.h"
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
#include "polycode/core/PolyVector2.h"
#include "polycode/core/PolyVector3.h"
#include "polycode/core/PolyVector4.h"


using namespace std;
namespace Polycode {

	duk_ret_t Polycode_BezierCurve(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = new std::shared_ptr<BezierCurve>;
		(*inst) = std::make_shared<BezierCurve>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve__get_evaluationAccuracy(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->evaluationAccuracy);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve__set_evaluationAccuracy(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, 0);
		inst->evaluationAccuracy = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve__delete(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getNumControlPoints(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumControlPoints());
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p1z = duk_to_number(context, 3);
		Number p2x = duk_to_number(context, 4);
		Number p2y = duk_to_number(context, 5);
		Number p2z = duk_to_number(context, 6);
		Number p3x = duk_to_number(context, 7);
		Number p3y = duk_to_number(context, 8);
		Number p3z = duk_to_number(context, 9);
		(*inst)->addControlPoint(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3dWithHandles(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p1z = duk_to_number(context, 3);
		Number p2x = duk_to_number(context, 4);
		Number p2y = duk_to_number(context, 5);
		Number p2z = duk_to_number(context, 6);
		Number p3x = duk_to_number(context, 7);
		Number p3y = duk_to_number(context, 8);
		Number p3z = duk_to_number(context, 9);
		(*inst)->addControlPoint3dWithHandles(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3d(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->addControlPoint3d(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2dWithHandles(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number p1x = duk_to_number(context, 1);
		Number p1y = duk_to_number(context, 2);
		Number p2x = duk_to_number(context, 3);
		Number p2y = duk_to_number(context, 4);
		Number p3x = duk_to_number(context, 5);
		Number p3y = duk_to_number(context, 6);
		(*inst)->addControlPoint2dWithHandles(p1x,p1y,p2x,p2y,p3x,p3y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2d(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		(*inst)->addControlPoint2d(x,y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getPointAt(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number a = duk_to_number(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getPointAt(a);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_clearControlPoints(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		(*inst)->clearControlPoints();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getYValueAtX(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, (*inst)->getYValueAtX(x));
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_getTValueAtX(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, (*inst)->getTValueAtX(x));
		return 1;
	}

	duk_ret_t Polycode_BezierCurve_setHeightCacheResolution(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		Number resolution = duk_to_number(context, 1);
		(*inst)->setHeightCacheResolution(resolution);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_rebuildHeightCache(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		(*inst)->rebuildHeightCache();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_recalculateDistances(duk_context *context) {
		std::shared_ptr<BezierCurve> *inst = (std::shared_ptr<BezierCurve>*)duk_to_pointer(context, 0);
		(*inst)->recalculateDistances();
		return 0;
	}

	duk_ret_t Polycode_BezierPoint(duk_context *context) {
		Number p1x = duk_to_number(context, 0);
		Number p1y = duk_to_number(context, 1);
		Number p1z = duk_to_number(context, 2);
		Number p2x = duk_to_number(context, 3);
		Number p2y = duk_to_number(context, 4);
		Number p2z = duk_to_number(context, 5);
		Number p3x = duk_to_number(context, 6);
		Number p3y = duk_to_number(context, 7);
		Number p3z = duk_to_number(context, 8);
		std::shared_ptr<BezierPoint> *inst = new std::shared_ptr<BezierPoint>;
		(*inst) = std::make_shared<BezierPoint>(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__get_p1(duk_context *context) {
		std::shared_ptr<BezierPoint> *inst = (std::shared_ptr<BezierPoint>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->p1;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p1(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p1 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__get_p2(duk_context *context) {
		std::shared_ptr<BezierPoint> *inst = (std::shared_ptr<BezierPoint>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->p2;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p2(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p2 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__get_p3(duk_context *context) {
		std::shared_ptr<BezierPoint> *inst = (std::shared_ptr<BezierPoint>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->p3;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BezierPoint__set_p3(duk_context *context) {
		BezierPoint *inst = (BezierPoint*)duk_to_pointer(context, 0);
		inst->p3 = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BezierPoint__delete(duk_context *context) {
		std::shared_ptr<BezierPoint> *inst = (std::shared_ptr<BezierPoint>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Bone(duk_context *context) {
		String boneName = duk_to_string(context, 0);
		std::shared_ptr<Bone> *inst = new std::shared_ptr<Bone>;
		(*inst) = std::make_shared<Bone>(boneName);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Bone__get_parentBoneId(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->parentBoneId);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_parentBoneId(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->parentBoneId = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_boneMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->boneMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_boneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->boneMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_restMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->restMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_restMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->restMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->baseMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_finalMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->finalMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_finalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->finalMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseRotation(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->baseRotation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseRotation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseRotation = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_baseScale(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->baseScale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_baseScale(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->baseScale = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_basePosition(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->basePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_basePosition(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->basePosition = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__get_disableAnimation(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->disableAnimation);
		return 1;
	}

	duk_ret_t Polycode_Bone__set_disableAnimation(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, 0);
		inst->disableAnimation = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Bone__delete(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Bone_getName(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Bone_setParentBone(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 1);
		(*inst)->setParentBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_addChildBone(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 1);
		(*inst)->addChildBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_getParentBone(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Bone>> *retInst = new std::shared_ptr<shared_ptr<Bone>>;
		*(*retInst) = (*inst)->getParentBone();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getNumChildBones(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumChildBones());
		return 1;
	}

	duk_ret_t Polycode_Bone_getChildBone(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<Bone>> *retInst = new std::shared_ptr<shared_ptr<Bone>>;
		*(*retInst) = (*inst)->getChildBone(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getBoneMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getBoneMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_setBoneMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setBoneMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getRestMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFullRestMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getFullRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getParentRestMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getParentRestMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFinalMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getFinalMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_setRestMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setRestMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_setBaseMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setBaseMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getBaseMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getBaseMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_getFullBaseMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getFullBaseMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_rebuildFinalMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		(*inst)->rebuildFinalMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_buildFinalMatrix(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->buildFinalMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Bone_intializeBone(duk_context *context) {
		std::shared_ptr<Bone> *inst = (std::shared_ptr<Bone>*)duk_to_pointer(context, 0);
		Vector3 basePosition = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 baseScale = *(Vector3*)duk_to_pointer(context, 2);
		Quaternion baseRotation = *(Quaternion*)duk_to_pointer(context, 3);
		Vector3 restPosition = *(Vector3*)duk_to_pointer(context, 4);
		Vector3 restScale = *(Vector3*)duk_to_pointer(context, 5);
		Quaternion restRotation = *(Quaternion*)duk_to_pointer(context, 6);
		(*inst)->intializeBone(basePosition,baseScale,baseRotation,restPosition,restScale,restRotation);
		return 0;
	}

	duk_ret_t Polycode_Camera(duk_context *context) {
		std::shared_ptr<Camera> *inst = new std::shared_ptr<Camera>;
		(*inst) = std::make_shared<Camera>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Camera__get_frustumCulling(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->frustumCulling);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_frustumCulling(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->frustumCulling = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__get_topLeftOrtho(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->topLeftOrtho);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_topLeftOrtho(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->topLeftOrtho = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__get_cameraShift(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->cameraShift;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera__set_cameraShift(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, 0);
		inst->cameraShift = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Camera__delete(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Camera_buildFrustumPlanes(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		(*inst)->buildFrustumPlanes();
		return 0;
	}

	duk_ret_t Polycode_Camera_isSphereInFrustum(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Vector3 pos = *(Vector3*)duk_to_pointer(context, 1);
		Number fRadius = duk_to_number(context, 2);
		duk_push_boolean(context, (*inst)->isSphereInFrustum(pos,fRadius));
		return 1;
	}

	duk_ret_t Polycode_Camera_isAABBInFrustum(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		AABB aabb = *(AABB*)duk_to_pointer(context, 1);
		duk_push_boolean(context, (*inst)->isAABBInFrustum(aabb));
		return 1;
	}

	duk_ret_t Polycode_Camera_setOrthoMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		bool mode = duk_to_boolean(context, 1);
		(*inst)->setOrthoMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSize(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Number orthoSizeX = duk_to_number(context, 1);
		Number orthoSizeY = duk_to_number(context, 2);
		(*inst)->setOrthoSize(orthoSizeX,orthoSizeY);
		return 0;
	}

	duk_ret_t Polycode_Camera_setFrustumMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number front = duk_to_number(context, 5);
		Number back = duk_to_number(context, 6);
		(*inst)->setFrustumMode(left,right,bottom,top,front,back);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getOrthoMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeX(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getOrthoSizeX());
		return 1;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeY(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getOrthoSizeY());
		return 1;
	}

	duk_ret_t Polycode_Camera_setFOV(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		(*inst)->setFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_Camera_getFOV(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getFOV());
		return 1;
	}

	duk_ret_t Polycode_Camera_setClippingPlanes(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Number nearClipPlane = duk_to_number(context, 1);
		Number farClipPlane = duk_to_number(context, 2);
		(*inst)->setClippingPlanes(nearClipPlane,farClipPlane);
		return 0;
	}

	duk_ret_t Polycode_Camera_getNearClippingPlane(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getNearClippingPlane());
		return 1;
	}

	duk_ret_t Polycode_Camera_getFarClippingPlane(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getFarClippingPlane());
		return 1;
	}

	duk_ret_t Polycode_Camera_createProjectionMatrix(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->createProjectionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_hasFilterShader(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->hasFilterShader());
		return 1;
	}

	duk_ret_t Polycode_Camera_setPostFilter(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		shared_ptr<Material> material = *(shared_ptr<Material>*)duk_to_pointer(context, 1);
		(*inst)->setPostFilter(material);
		return 0;
	}

	duk_ret_t Polycode_Camera_removePostFilter(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		(*inst)->removePostFilter();
		return 0;
	}

	duk_ret_t Polycode_Camera_getScreenShaderMaterial(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Material>> *retInst = new std::shared_ptr<shared_ptr<Material>>;
		*(*retInst) = (*inst)->getScreenShaderMaterial();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_getProjectionMatrix(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getProjectionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_setCustomProjectionMatrix(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setCustomProjectionMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Camera_getViewport(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*(*retInst) = (*inst)->getViewport();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_setViewport(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		(*inst)->setViewport(viewport);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSizeMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		int orthoSizeMode = duk_to_int(context, 1);
		(*inst)->setOrthoSizeMode(orthoSizeMode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getOrthoSizeMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_setProjectionMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		int mode = duk_to_int(context, 1);
		(*inst)->setProjectionMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getProjectionMode(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getProjectionMode());
		return 1;
	}

	duk_ret_t Polycode_Camera_projectRayFrom2DCoordinate(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		Vector2 coordinate = *(Vector2*)duk_to_pointer(context, 1);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 2);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->projectRayFrom2DCoordinate(coordinate,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_getShaderPass(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<ShaderPass> *retInst = new std::shared_ptr<ShaderPass>;
		*(*retInst) = (*inst)->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Camera_getNumShaderPasses(duk_context *context) {
		std::shared_ptr<Camera> *inst = (std::shared_ptr<Camera>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_Color(duk_context *context) {
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		std::shared_ptr<Color> *inst = new std::shared_ptr<Color>;
		(*inst) = std::make_shared<Color>(r,g,b,a);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Color__get_r(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->r);
		return 1;
	}

	duk_ret_t Polycode_Color__set_r(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->r = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_g(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->g);
		return 1;
	}

	duk_ret_t Polycode_Color__set_g(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->g = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_b(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->b);
		return 1;
	}

	duk_ret_t Polycode_Color__set_b(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->b = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__get_a(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->a);
		return 1;
	}

	duk_ret_t Polycode_Color__set_a(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, 0);
		inst->a = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Color__delete(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Color_ColorWithInts(duk_context *context) {
		int r = duk_to_int(context, 0);
		int g = duk_to_int(context, 1);
		int b = duk_to_int(context, 2);
		int a = duk_to_int(context, 3);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = Color::ColorWithInts(r,g,b,a);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Color_ColorWithHex(duk_context *context) {
		int hex = duk_to_int(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = Color::ColorWithHex(hex);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Color_setColorHex(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		int hex = duk_to_int(context, 1);
		(*inst)->setColorHex(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGB(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		int hex = duk_to_int(context, 1);
		(*inst)->setColorHexRGB(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexFromString(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		String hex = duk_to_string(context, 1);
		(*inst)->setColorHexFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGBFromString(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		String hex = duk_to_string(context, 1);
		(*inst)->setColorHexRGBFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHSV(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		Number h = duk_to_number(context, 1);
		Number s = duk_to_number(context, 2);
		Number v = duk_to_number(context, 3);
		(*inst)->setColorHSV(h,s,v);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGBA(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		int a = duk_to_int(context, 4);
		(*inst)->setColorRGBA(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGB(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		(*inst)->setColorRGB(r,g,b);
		return 0;
	}

	duk_ret_t Polycode_Color_setColor(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_blendColor(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		Color c2 = *(Color*)duk_to_pointer(context, 1);
		int mode = duk_to_int(context, 2);
		Number amount = duk_to_number(context, 3);
		Color c3 = *(Color*)duk_to_pointer(context, 4);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->blendColor(c2,mode,amount,c3);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Color_Random(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		(*inst)->Random();
		return 0;
	}

	duk_ret_t Polycode_Color_getBrightness(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getBrightness());
		return 1;
	}

	duk_ret_t Polycode_Color_RGBtoHSV(duk_context *context) {
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number h = duk_to_number(context, 3);
		Number s = duk_to_number(context, 4);
		Number v = duk_to_number(context, 5);
		Color::RGBtoHSV(r,g,b,h,s,v);
		return 0;
	}

	duk_ret_t Polycode_Color_getHue(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getHue());
		return 1;
	}

	duk_ret_t Polycode_Color_getSaturation(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getSaturation());
		return 1;
	}

	duk_ret_t Polycode_Color_getValue(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getValue());
		return 1;
	}

	duk_ret_t Polycode_Color_getUint(duk_context *context) {
		std::shared_ptr<Color> *inst = (std::shared_ptr<Color>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getUint());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = new std::shared_ptr<ConfigEntry>;
		(*inst) = std::make_shared<ConfigEntry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__get_key(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->key.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_key(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->key = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_configNamespace(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->configNamespace.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_configNamespace(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->configNamespace = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_numVal(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->numVal);
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_numVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->numVal = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_stringVal(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->stringVal.c_str());
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_stringVal(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->stringVal = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__get_isString(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isString);
		return 1;
	}

	duk_ret_t Polycode_ConfigEntry__set_isString(duk_context *context) {
		ConfigEntry *inst = (ConfigEntry*)duk_to_pointer(context, 0);
		inst->isString = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ConfigEntry__delete(duk_context *context) {
		std::shared_ptr<ConfigEntry> *inst = (std::shared_ptr<ConfigEntry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Config(duk_context *context) {
		std::shared_ptr<Config> *inst = new std::shared_ptr<Config>;
		(*inst) = std::make_shared<Config>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Config__delete(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Config_loadConfig(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		(*inst)->loadConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_saveConfig(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String fileName = duk_to_string(context, 2);
		(*inst)->saveConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_setStringValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		String value = duk_to_string(context, 3);
		(*inst)->setStringValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_setNumericValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		Number value = duk_to_number(context, 3);
		(*inst)->setNumericValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getNumericValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_number(context, (*inst)->getNumericValue(configNamespace,key));
		return 1;
	}

	duk_ret_t Polycode_Config_getStringValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_string(context, (*inst)->getStringValue(configNamespace,key).c_str());
		return 1;
	}

	duk_ret_t Polycode_Config_setBoolValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		bool value = duk_to_boolean(context, 3);
		(*inst)->setBoolValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getBoolValue(duk_context *context) {
		std::shared_ptr<Config> *inst = (std::shared_ptr<Config>*)duk_to_pointer(context, 0);
		String configNamespace = duk_to_string(context, 1);
		String key = duk_to_string(context, 2);
		duk_push_boolean(context, (*inst)->getBoolValue(configNamespace,key));
		return 1;
	}

	duk_ret_t Polycode_Core__get_paused(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->paused);
		return 1;
	}

	duk_ret_t Polycode_Core__set_paused(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->paused = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_pauseOnLoseFocus(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->pauseOnLoseFocus);
		return 1;
	}

	duk_ret_t Polycode_Core__set_pauseOnLoseFocus(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->pauseOnLoseFocus = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_defaultScreenWidth(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->defaultScreenWidth);
		return 1;
	}

	duk_ret_t Polycode_Core__set_defaultScreenWidth(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->defaultScreenWidth = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_defaultScreenHeight(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->defaultScreenHeight);
		return 1;
	}

	duk_ret_t Polycode_Core__set_defaultScreenHeight(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->defaultScreenHeight = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__get_deviceAttitude(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->deviceAttitude;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Core__set_deviceAttitude(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, 0);
		inst->deviceAttitude = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Core__delete(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Core_Update(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->Update());
		return 1;
	}

	duk_ret_t Polycode_Core_fixedUpdate(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->fixedUpdate());
		return 1;
	}

	duk_ret_t Polycode_Core_systemUpdate(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->systemUpdate());
		return 1;
	}

	duk_ret_t Polycode_Core_enableMouse(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		bool newval = duk_to_boolean(context, 1);
		(*inst)->enableMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_captureMouse(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		bool newval = duk_to_boolean(context, 1);
		(*inst)->captureMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_setCursor(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		int cursorType = duk_to_int(context, 1);
		(*inst)->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_Core_warpCursor(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		(*inst)->warpCursor(x,y);
		return 0;
	}

	duk_ret_t Polycode_Core_openOnScreenKeyboard(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		bool open = duk_to_boolean(context, 1);
		(*inst)->openOnScreenKeyboard(open);
		return 0;
	}

	duk_ret_t Polycode_Core_copyStringToClipboard(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		(*inst)->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_Core_getClipboardString(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getClipboardString().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getFPS(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getFPS());
		return 1;
	}

	duk_ret_t Polycode_Core_Shutdown(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		(*inst)->Shutdown();
		return 0;
	}

	duk_ret_t Polycode_Core_isFullscreen(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isFullscreen());
		return 1;
	}

	duk_ret_t Polycode_Core_getAALevel(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getAALevel());
		return 1;
	}

	duk_ret_t Polycode_Core_getXRes(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getXRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getYRes(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getYRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getBackingXRes(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getBackingXRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getBackingYRes(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getBackingYRes());
		return 1;
	}

	duk_ret_t Polycode_Core_getScreenWidth(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getScreenWidth());
		return 1;
	}

	duk_ret_t Polycode_Core_getScreenHeight(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getScreenHeight());
		return 1;
	}

	duk_ret_t Polycode_Core_createFolder(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String folderPath = duk_to_string(context, 1);
		(*inst)->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_Core_copyDiskItem(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		(*inst)->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_moveDiskItem(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		(*inst)->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_removeDiskItem(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		(*inst)->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_openFolderPicker(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->openFolderPicker().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_setFramerate(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		int frameRate = duk_to_int(context, 1);
		int maxFixedCycles = duk_to_int(context, 2);
		(*inst)->setFramerate(frameRate,maxFixedCycles);
		return 0;
	}

	duk_ret_t Polycode_Core_openFilePicker(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		bool allowMultiple = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Core_saveFilePicker(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		duk_push_string(context, (*inst)->saveFilePicker(extensions).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_flushRenderContext(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		(*inst)->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_prepareRenderContext(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		(*inst)->prepareRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_isWindowInitialized(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isWindowInitialized());
		return 1;
	}

	duk_ret_t Polycode_Core_addFileSource(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String type = duk_to_string(context, 1);
		String source = duk_to_string(context, 2);
		(*inst)->addFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_removeFileSource(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String type = duk_to_string(context, 1);
		String source = duk_to_string(context, 2);
		(*inst)->removeFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_parseFolder(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_Core_systemParseFolder(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 3);
		duk_push_boolean(context, (*inst)->systemParseFolder(pathString,showHidden,targetVector));
		return 1;
	}

	duk_ret_t Polycode_Core_getResourcePathForFile(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_string(context, (*inst)->getResourcePathForFile(fileName).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_setVideoMode(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		int xRes = duk_to_int(context, 1);
		int yRes = duk_to_int(context, 2);
		bool fullScreen = duk_to_boolean(context, 3);
		bool vSync = duk_to_boolean(context, 4);
		int aaLevel = duk_to_int(context, 5);
		int anisotropyLevel = duk_to_int(context, 6);
		bool retinaSupport = duk_to_boolean(context, 7);
		(*inst)->setVideoMode(xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport);
		return 0;
	}

	duk_ret_t Polycode_Core_resizeTo(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		int xRes = duk_to_int(context, 1);
		int yRes = duk_to_int(context, 2);
		(*inst)->resizeTo(xRes,yRes);
		return 0;
	}

	duk_ret_t Polycode_Core_doSleep(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		(*inst)->doSleep();
		return 0;
	}

	duk_ret_t Polycode_Core_openURL(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String url = duk_to_string(context, 1);
		(*inst)->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_Core_getElapsed(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getElapsed());
		return 1;
	}

	duk_ret_t Polycode_Core_getTicks(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getTicks());
		return 1;
	}

	duk_ret_t Polycode_Core_getRefreshIntervalMs(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getRefreshIntervalMs());
		return 1;
	}

	duk_ret_t Polycode_Core_getTimeSleptMs(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getTimeSleptMs());
		return 1;
	}

	duk_ret_t Polycode_Core_getFixedTimestep(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getFixedTimestep());
		return 1;
	}

	duk_ret_t Polycode_Core_getViewport(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*(*retInst) = (*inst)->getViewport();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Core_getTicksFloat(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getTicksFloat());
		return 1;
	}

	duk_ret_t Polycode_Core_executeExternalCommand(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		String command = duk_to_string(context, 1);
		String args = duk_to_string(context, 2);
		String inDirectory = duk_to_string(context, 3);
		duk_push_string(context, (*inst)->executeExternalCommand(command,args,inDirectory).c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getDefaultWorkingDirectory(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getDefaultWorkingDirectory().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_getUserHomeDirectory(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getUserHomeDirectory().c_str());
		return 1;
	}

	duk_ret_t Polycode_Core_makeApplicationMain(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		(*inst)->makeApplicationMain();
		return 0;
	}

	duk_ret_t Polycode_Core_getConfig(duk_context *context) {
		std::shared_ptr<Core> *inst = (std::shared_ptr<Core>*)duk_to_pointer(context, 0);
		std::shared_ptr<ConfigRef> *retInst = new std::shared_ptr<ConfigRef>;
		*(*retInst) = (*inst)->getConfig();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = new std::shared_ptr<VideoModeChangeInfo>;
		(*inst) = std::make_shared<VideoModeChangeInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_xRes(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->xRes);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_xRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->xRes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_yRes(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->yRes);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_yRes(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->yRes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_fullScreen(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->fullScreen);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_fullScreen(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->fullScreen = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_vSync(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->vSync);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_vSync(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->vSync = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_aaLevel(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->aaLevel);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_aaLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->aaLevel = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_anisotropyLevel(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->anisotropyLevel);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_anisotropyLevel(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->anisotropyLevel = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__get_retinaSupport(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->retinaSupport);
		return 1;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__set_retinaSupport(duk_context *context) {
		VideoModeChangeInfo *inst = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->retinaSupport = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_VideoModeChangeInfo__delete(duk_context *context) {
		std::shared_ptr<VideoModeChangeInfo> *inst = (std::shared_ptr<VideoModeChangeInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_PolycodeViewBase(duk_context *context) {
		std::shared_ptr<PolycodeViewBase> *inst = new std::shared_ptr<PolycodeViewBase>;
		(*inst) = std::make_shared<PolycodeViewBase>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_PolycodeViewBase__get_resizable(duk_context *context) {
		std::shared_ptr<PolycodeViewBase> *inst = (std::shared_ptr<PolycodeViewBase>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->resizable);
		return 1;
	}

	duk_ret_t Polycode_PolycodeViewBase__set_resizable(duk_context *context) {
		PolycodeViewBase *inst = (PolycodeViewBase*)duk_to_pointer(context, 0);
		inst->resizable = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_PolycodeViewBase__delete(duk_context *context) {
		std::shared_ptr<PolycodeViewBase> *inst = (std::shared_ptr<PolycodeViewBase>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_DummyCore(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = new std::shared_ptr<DummyCore>;
		(*inst) = std::make_shared<DummyCore>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_DummyCore__delete(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_DummyCore_systemUpdate(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->systemUpdate());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_setCursor(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		int cursorType = duk_to_int(context, 1);
		(*inst)->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_copyStringToClipboard(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		(*inst)->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getClipboardString(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getClipboardString().c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_createFolder(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String folderPath = duk_to_string(context, 1);
		(*inst)->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_copyDiskItem(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		(*inst)->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_moveDiskItem(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		String destItemPath = duk_to_string(context, 2);
		(*inst)->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_removeDiskItem(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String itemPath = duk_to_string(context, 1);
		(*inst)->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openFolderPicker(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->openFolderPicker().c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_openFilePicker(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		bool allowMultiple = duk_to_boolean(context, 2);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_saveFilePicker(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 1);
		duk_push_string(context, (*inst)->saveFilePicker(extensions).c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_flushRenderContext(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		(*inst)->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openURL(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String url = duk_to_string(context, 1);
		(*inst)->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getTicks(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getTicks());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_executeExternalCommand(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String command = duk_to_string(context, 1);
		String args = duk_to_string(context, 2);
		String inDirectory = duk_to_string(context, 3);
		duk_push_string(context, (*inst)->executeExternalCommand(command,args,inDirectory).c_str());
		return 1;
	}

	duk_ret_t Polycode_DummyCore_systemParseFolder(duk_context *context) {
		std::shared_ptr<DummyCore> *inst = (std::shared_ptr<DummyCore>*)duk_to_pointer(context, 0);
		String pathString = duk_to_string(context, 1);
		bool showHidden = duk_to_boolean(context, 2);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 3);
		duk_push_boolean(context, (*inst)->systemParseFolder(pathString,showHidden,targetVector));
		return 1;
	}

	duk_ret_t Polycode_TimeInfo(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = new std::shared_ptr<TimeInfo>;
		(*inst) = std::make_shared<TimeInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__get_seconds(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->seconds);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_seconds(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->seconds = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_minutes(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->minutes);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_minutes(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->minutes = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_hours(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->hours);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_hours(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->hours = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_month(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->month);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_month(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->month = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_monthDay(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->monthDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_monthDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->monthDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_weekDay(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->weekDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_weekDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->weekDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_year(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->year);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_year(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->year = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__get_yearDay(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->yearDay);
		return 1;
	}

	duk_ret_t Polycode_TimeInfo__set_yearDay(duk_context *context) {
		TimeInfo *inst = (TimeInfo*)duk_to_pointer(context, 0);
		inst->yearDay = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TimeInfo__delete(duk_context *context) {
		std::shared_ptr<TimeInfo> *inst = (std::shared_ptr<TimeInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreMotionEvent(duk_context *context) {
		std::shared_ptr<CoreMotionEvent> *inst = new std::shared_ptr<CoreMotionEvent>;
		(*inst) = std::make_shared<CoreMotionEvent>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_CoreMotionEvent__get_amount(duk_context *context) {
		std::shared_ptr<CoreMotionEvent> *inst = (std::shared_ptr<CoreMotionEvent>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->amount;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreMotionEvent__set_amount(duk_context *context) {
		CoreMotionEvent *inst = (CoreMotionEvent*)duk_to_pointer(context, 0);
		inst->amount = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreMotionEvent__delete(duk_context *context) {
		std::shared_ptr<CoreMotionEvent> *inst = (std::shared_ptr<CoreMotionEvent>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension(duk_context *context) {
		std::shared_ptr<CoreFileExtension> *inst = new std::shared_ptr<CoreFileExtension>;
		(*inst) = std::make_shared<CoreFileExtension>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_CoreFileExtension__get_extension(duk_context *context) {
		std::shared_ptr<CoreFileExtension> *inst = (std::shared_ptr<CoreFileExtension>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->extension.c_str());
		return 1;
	}

	duk_ret_t Polycode_CoreFileExtension__set_extension(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		inst->extension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension__get_description(duk_context *context) {
		std::shared_ptr<CoreFileExtension> *inst = (std::shared_ptr<CoreFileExtension>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->description.c_str());
		return 1;
	}

	duk_ret_t Polycode_CoreFileExtension__set_description(duk_context *context) {
		CoreFileExtension *inst = (CoreFileExtension*)duk_to_pointer(context, 0);
		inst->description = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreFileExtension__delete(duk_context *context) {
		std::shared_ptr<CoreFileExtension> *inst = (std::shared_ptr<CoreFileExtension>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = new std::shared_ptr<OSFileEntry>;
		(*inst) = std::make_shared<OSFileEntry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__get_name(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_name(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_extension(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->extension.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_extension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->extension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_nameWithoutExtension(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->nameWithoutExtension.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_nameWithoutExtension(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->nameWithoutExtension = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_basePath(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->basePath.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_basePath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->basePath = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_fullPath(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->fullPath.c_str());
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_fullPath(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->fullPath = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__get_type(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_OSFileEntry__set_type(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry__delete(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry_init(duk_context *context) {
		std::shared_ptr<OSFileEntry> *inst = (std::shared_ptr<OSFileEntry>*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		String name = duk_to_string(context, 2);
		int type = duk_to_int(context, 3);
		(*inst)->init(path,name,type);
		return 0;
	}

	duk_ret_t Polycode_CoreInput(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = new std::shared_ptr<CoreInput>;
		(*inst) = std::make_shared<CoreInput>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__get_simulateTouchWithMouse(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->simulateTouchWithMouse);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateTouchWithMouse(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateTouchWithMouse = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_simulateTouchAsPen(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->simulateTouchAsPen);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateTouchAsPen(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateTouchAsPen = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_simulateMouseWithTouch(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->simulateMouseWithTouch);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_simulateMouseWithTouch(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->simulateMouseWithTouch = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_keyRepeat(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->keyRepeat);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_keyRepeat(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->keyRepeat = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_mousePosition(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->mousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_mousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->mousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__get_deltaMousePosition(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->deltaMousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput__set_deltaMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, 0);
		inst->deltaMousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_CoreInput__delete(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getMousePosition(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getMousePosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getKeyState(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 1);
		duk_push_boolean(context, (*inst)->getKeyState(keyCode));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickButtonState(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int joystickIndex = duk_to_int(context, 1);
		int button = duk_to_int(context, 2);
		duk_push_boolean(context, (*inst)->getJoystickButtonState(joystickIndex,button));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getJoystickAxisValue(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int joystickIndex = duk_to_int(context, 1);
		int axis = duk_to_int(context, 2);
		duk_push_number(context, (*inst)->getJoystickAxisValue(joystickIndex,axis));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getMouseDelta(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getMouseDelta();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getMouseButtonState(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		duk_push_boolean(context, (*inst)->getMouseButtonState(mouseButton));
		return 1;
	}

	duk_ret_t Polycode_CoreInput_getNumJoysticks(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumJoysticks());
		return 1;
	}

	duk_ret_t Polycode_CoreInput_addJoystick(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int deviceID = duk_to_int(context, 1);
		(*inst)->addJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_removeJoystick(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int deviceID = duk_to_int(context, 1);
		(*inst)->removeJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickAxisMoved(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int axisID = duk_to_int(context, 1);
		Number value = duk_to_number(context, 2);
		int deviceID = duk_to_int(context, 3);
		(*inst)->joystickAxisMoved(axisID,value,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonDown(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int buttonID = duk_to_int(context, 1);
		int deviceID = duk_to_int(context, 2);
		(*inst)->joystickButtonDown(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonUp(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int buttonID = duk_to_int(context, 1);
		int deviceID = duk_to_int(context, 2);
		(*inst)->joystickButtonUp(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelUp(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int ticks = duk_to_int(context, 1);
		(*inst)->mouseWheelUp(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelDown(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int ticks = duk_to_int(context, 1);
		(*inst)->mouseWheelDown(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMouseButtonState(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		bool state = duk_to_boolean(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->setMouseButtonState(mouseButton,state,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMousePosition(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->setMousePosition(x,y,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setKeyState(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 1);
		bool newState = duk_to_boolean(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->setKeyState(keyCode,newState,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setDeltaPosition(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		(*inst)->setDeltaPosition(x,y);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesBegan(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->touchesBegan(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesMoved(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->touchesMoved(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesEnded(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 1);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 2);
		int ticks = duk_to_int(context, 3);
		(*inst)->touchesEnded(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_textInput(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		(*inst)->textInput(text);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_clearInput(duk_context *context) {
		std::shared_ptr<CoreInput> *inst = (std::shared_ptr<CoreInput>*)duk_to_pointer(context, 0);
		(*inst)->clearInput();
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo(duk_context *context) {
		std::shared_ptr<JoystickInfo> *inst = new std::shared_ptr<JoystickInfo>;
		(*inst) = std::make_shared<JoystickInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_JoystickInfo__get_deviceID(duk_context *context) {
		std::shared_ptr<JoystickInfo> *inst = (std::shared_ptr<JoystickInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->deviceID);
		return 1;
	}

	duk_ret_t Polycode_JoystickInfo__set_deviceID(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		inst->deviceID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo__get_deviceIndex(duk_context *context) {
		std::shared_ptr<JoystickInfo> *inst = (std::shared_ptr<JoystickInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->deviceIndex);
		return 1;
	}

	duk_ret_t Polycode_JoystickInfo__set_deviceIndex(duk_context *context) {
		JoystickInfo *inst = (JoystickInfo*)duk_to_pointer(context, 0);
		inst->deviceIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_JoystickInfo__delete(duk_context *context) {
		std::shared_ptr<JoystickInfo> *inst = (std::shared_ptr<JoystickInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Data(duk_context *context) {
		std::shared_ptr<Data> *inst = new std::shared_ptr<Data>;
		(*inst) = std::make_shared<Data>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Data__delete(duk_context *context) {
		std::shared_ptr<Data> *inst = (std::shared_ptr<Data>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Data_getAsString(duk_context *context) {
		std::shared_ptr<Data> *inst = (std::shared_ptr<Data>*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		duk_push_string(context, (*inst)->getAsString(encoding).c_str());
		return 1;
	}

	duk_ret_t Polycode_Data_setFromString(duk_context *context) {
		std::shared_ptr<Data> *inst = (std::shared_ptr<Data>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		int encoding = duk_to_int(context, 2);
		(*inst)->setFromString(str,encoding);
		return 0;
	}

	duk_ret_t Polycode_MouseEventResult(duk_context *context) {
		std::shared_ptr<MouseEventResult> *inst = new std::shared_ptr<MouseEventResult>;
		(*inst) = std::make_shared<MouseEventResult>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__get_hit(duk_context *context) {
		std::shared_ptr<MouseEventResult> *inst = (std::shared_ptr<MouseEventResult>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->hit);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__set_hit(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		inst->hit = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MouseEventResult__get_blocked(duk_context *context) {
		std::shared_ptr<MouseEventResult> *inst = (std::shared_ptr<MouseEventResult>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->blocked);
		return 1;
	}

	duk_ret_t Polycode_MouseEventResult__set_blocked(duk_context *context) {
		MouseEventResult *inst = (MouseEventResult*)duk_to_pointer(context, 0);
		inst->blocked = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MouseEventResult__delete(duk_context *context) {
		std::shared_ptr<MouseEventResult> *inst = (std::shared_ptr<MouseEventResult>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_EntityProp(duk_context *context) {
		std::shared_ptr<EntityProp> *inst = new std::shared_ptr<EntityProp>;
		(*inst) = std::make_shared<EntityProp>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_EntityProp__get_propName(duk_context *context) {
		std::shared_ptr<EntityProp> *inst = (std::shared_ptr<EntityProp>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->propName.c_str());
		return 1;
	}

	duk_ret_t Polycode_EntityProp__set_propName(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		inst->propName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_EntityProp__get_propValue(duk_context *context) {
		std::shared_ptr<EntityProp> *inst = (std::shared_ptr<EntityProp>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->propValue.c_str());
		return 1;
	}

	duk_ret_t Polycode_EntityProp__set_propValue(duk_context *context) {
		EntityProp *inst = (EntityProp*)duk_to_pointer(context, 0);
		inst->propValue = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_EntityProp__delete(duk_context *context) {
		std::shared_ptr<EntityProp> *inst = (std::shared_ptr<EntityProp>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_AABB(duk_context *context) {
		std::shared_ptr<AABB> *inst = new std::shared_ptr<AABB>;
		(*inst) = std::make_shared<AABB>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_AABB__get_min(duk_context *context) {
		std::shared_ptr<AABB> *inst = (std::shared_ptr<AABB>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->min;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AABB__set_min(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		inst->min = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AABB__get_max(duk_context *context) {
		std::shared_ptr<AABB> *inst = (std::shared_ptr<AABB>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->max;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AABB__set_max(duk_context *context) {
		AABB *inst = (AABB*)duk_to_pointer(context, 0);
		inst->max = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AABB__delete(duk_context *context) {
		std::shared_ptr<AABB> *inst = (std::shared_ptr<AABB>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Rotation(duk_context *context) {
		std::shared_ptr<Rotation> *inst = new std::shared_ptr<Rotation>;
		(*inst) = std::make_shared<Rotation>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Rotation__get_pitch(duk_context *context) {
		std::shared_ptr<Rotation> *inst = (std::shared_ptr<Rotation>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->pitch);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_pitch(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->pitch = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__get_yaw(duk_context *context) {
		std::shared_ptr<Rotation> *inst = (std::shared_ptr<Rotation>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->yaw);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_yaw(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->yaw = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__get_roll(duk_context *context) {
		std::shared_ptr<Rotation> *inst = (std::shared_ptr<Rotation>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->roll);
		return 1;
	}

	duk_ret_t Polycode_Rotation__set_roll(duk_context *context) {
		Rotation *inst = (Rotation*)duk_to_pointer(context, 0);
		inst->roll = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rotation__delete(duk_context *context) {
		std::shared_ptr<Rotation> *inst = (std::shared_ptr<Rotation>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Entity(duk_context *context) {
		std::shared_ptr<Entity> *inst = new std::shared_ptr<Entity>;
		(*inst) = std::make_shared<Entity>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Entity__get_ownsChildren(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->ownsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_ownsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->ownsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_billboardMode(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->billboardMode);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_billboardMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->billboardMode = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_color(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_color(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_enabled(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enabled);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_enabled(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_visible(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->visible);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_visible(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->visible = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_depthWrite(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthWrite);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_depthWrite(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->depthWrite = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_depthTest(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthTest);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_depthTest(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->depthTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_colorAffectsChildren(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->colorAffectsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_colorAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->colorAffectsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_visibilityAffectsChildren(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->visibilityAffectsChildren);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_visibilityAffectsChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->visibilityAffectsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_ignoreParentMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->ignoreParentMatrix);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_ignoreParentMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->ignoreParentMatrix = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_enableScissor(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enableScissor);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_enableScissor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->enableScissor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_scissorBox(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->scissorBox;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_scissorBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->scissorBox = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_editorOnly(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->editorOnly);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_editorOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->editorOnly = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_id(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity__set_id(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_collisionShapeType(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<char> *retInst = new std::shared_ptr<char>;
		*retInst = std::make_shared<char>();
		*(*retInst) = (*inst)->collisionShapeType;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_collisionShapeType(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->collisionShapeType = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_processInputEvents(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->processInputEvents);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_processInputEvents(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->processInputEvents = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_blockMouseInput(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->blockMouseInput);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_blockMouseInput(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->blockMouseInput = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_snapToPixels(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->snapToPixels);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_snapToPixels(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->snapToPixels = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_mouseOver(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->mouseOver);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_mouseOver(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->mouseOver = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_rendererVis(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->rendererVis);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_rendererVis(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->rendererVis = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__get_layerID(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<char> *retInst = new std::shared_ptr<char>;
		*retInst = std::make_shared<char>();
		*(*retInst) = (*inst)->layerID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity__set_layerID(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, 0);
		inst->layerID = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Entity__delete(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Entity_initEntity(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->initEntity();
		return 0;
	}

	duk_ret_t Polycode_Entity_Update(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_Entity_fixedUpdate(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Entity_dirtyMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->dirtyMatrix(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_rebuildTransformMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->rebuildTransformMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_updateEntityMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->updateEntityMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getTransformMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getTransformMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getConcatenatedMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getAnchorAdjustedMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getAnchorAdjustedMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedRollMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getConcatenatedRollMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setTransformByMatrixPure(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setTransformByMatrixPure(matrix);
		return 0;
	}

	duk_ret_t Polycode_Entity_getLookAtMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getLookAtMatrix(loc,upVector);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getNumChildren(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumChildren());
		return 1;
	}

	duk_ret_t Polycode_Entity_setOwnsChildrenRecursive(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setOwnsChildrenRecursive(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPosition(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getPosition2D(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getPosition2D();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedPosition(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getCombinedPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setPosition(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionX(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		(*inst)->setPositionX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionY(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		(*inst)->setPositionY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_Translate(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionZ(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		(*inst)->setPositionZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleX(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		(*inst)->setScaleX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleY(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		(*inst)->setScaleY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleZ(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		(*inst)->setScaleZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_Scale(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->Scale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScale(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->setScale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCompoundScale(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getCompoundScale();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getScale(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getScale();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getRotationEuler(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getRotationEuler();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedPitch(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getCombinedPitch());
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedYaw(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getCombinedYaw());
		return 1;
	}

	duk_ret_t Polycode_Entity_getCombinedRoll(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getCombinedRoll());
		return 1;
	}

	duk_ret_t Polycode_Entity_rebuildRotation(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->rebuildRotation();
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationEuler(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Vector3 rotation = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setRotationEuler(rotation);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPitch(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number pitch = duk_to_number(context, 1);
		(*inst)->setPitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_setYaw(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number yaw = duk_to_number(context, 1);
		(*inst)->setYaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRoll(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number roll = duk_to_number(context, 1);
		(*inst)->setRoll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Roll(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number roll = duk_to_number(context, 1);
		(*inst)->Roll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Yaw(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number yaw = duk_to_number(context, 1);
		(*inst)->Yaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_Pitch(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number pitch = duk_to_number(context, 1);
		(*inst)->Pitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPitch(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPitch());
		return 1;
	}

	duk_ret_t Polycode_Entity_getYaw(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getYaw());
		return 1;
	}

	duk_ret_t Polycode_Entity_getRoll(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getRoll());
		return 1;
	}

	duk_ret_t Polycode_Entity_getWidth(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Entity_getHeight(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Entity_getDepth(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getDepth());
		return 1;
	}

	duk_ret_t Polycode_Entity_setWidth(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number width = duk_to_number(context, 1);
		(*inst)->setWidth(width);
		return 0;
	}

	duk_ret_t Polycode_Entity_setHeight(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		(*inst)->setHeight(height);
		return 0;
	}

	duk_ret_t Polycode_Entity_setDepth(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number depth = duk_to_number(context, 1);
		(*inst)->setDepth(depth);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationQuat(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		(*inst)->setRotationQuat(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationByQuaternion(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Quaternion quaternion = *(Quaternion*)duk_to_pointer(context, 1);
		(*inst)->setRotationByQuaternion(quaternion);
		return 0;
	}

	duk_ret_t Polycode_Entity_getRotationQuat(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = (*inst)->getRotationQuat();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getConcatenatedQuat(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = (*inst)->getConcatenatedQuat();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_lookAt(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		(*inst)->lookAt(loc,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedColor(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getCombinedColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setColor(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setColorInt(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		int r = duk_to_int(context, 1);
		int g = duk_to_int(context, 2);
		int b = duk_to_int(context, 3);
		int a = duk_to_int(context, 4);
		(*inst)->setColorInt(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setAnchorPoint(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Vector3 anchorPoint = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setAnchorPoint(anchorPoint);
		return 0;
	}

	duk_ret_t Polycode_Entity_getAnchorPoint(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getAnchorPoint();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseDown(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int mouseButton = duk_to_int(context, 2);
		int timestamp = duk_to_int(context, 3);
		std::shared_ptr<MouseEventResult> *retInst = new std::shared_ptr<MouseEventResult>;
		*(*retInst) = (*inst)->onMouseDown(ray,mouseButton,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseUp(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int mouseButton = duk_to_int(context, 2);
		int timestamp = duk_to_int(context, 3);
		std::shared_ptr<MouseEventResult> *retInst = new std::shared_ptr<MouseEventResult>;
		*(*retInst) = (*inst)->onMouseUp(ray,mouseButton,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseMove(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		std::shared_ptr<MouseEventResult> *retInst = new std::shared_ptr<MouseEventResult>;
		*(*retInst) = (*inst)->onMouseMove(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseWheelUp(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		std::shared_ptr<MouseEventResult> *retInst = new std::shared_ptr<MouseEventResult>;
		*(*retInst) = (*inst)->onMouseWheelUp(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_onMouseWheelDown(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		int timestamp = duk_to_int(context, 2);
		std::shared_ptr<MouseEventResult> *retInst = new std::shared_ptr<MouseEventResult>;
		*(*retInst) = (*inst)->onMouseWheelDown(ray,timestamp);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setDepthOnly(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setDepthOnly(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getDepthOnly(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getDepthOnly());
		return 1;
	}

	duk_ret_t Polycode_Entity_setBlendingMode(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		int newBlendingMode = duk_to_int(context, 1);
		(*inst)->setBlendingMode(newBlendingMode);
		return 0;
	}

	duk_ret_t Polycode_Entity_getBlendingMode(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getBlendingMode());
		return 1;
	}

	duk_ret_t Polycode_Entity_getEntityProp(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		String propName = duk_to_string(context, 1);
		duk_push_string(context, (*inst)->getEntityProp(propName).c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity_setEntityProp(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		String propName = duk_to_string(context, 1);
		String propValue = duk_to_string(context, 2);
		(*inst)->setEntityProp(propName,propValue);
		return 0;
	}

	duk_ret_t Polycode_Entity_setInverseY(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setInverseY(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getInverseY(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getInverseY());
		return 1;
	}

	duk_ret_t Polycode_Entity_doUpdates(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->doUpdates(elapsed);
		return 0;
	}

	duk_ret_t Polycode_Entity_doFixedUpdates(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->doFixedUpdates();
		return 0;
	}

	duk_ret_t Polycode_Entity_buildPositionMatrix(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->buildPositionMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_customHitDetection(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		duk_push_boolean(context, (*inst)->customHitDetection(ray));
		return 1;
	}

	duk_ret_t Polycode_Entity_getNumTags(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumTags());
		return 1;
	}

	duk_ret_t Polycode_Entity_getTagAtIndex(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		duk_push_string(context, (*inst)->getTagAtIndex(index).c_str());
		return 1;
	}

	duk_ret_t Polycode_Entity_hasTag(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		String tag = duk_to_string(context, 1);
		duk_push_boolean(context, (*inst)->hasTag(tag));
		return 1;
	}

	duk_ret_t Polycode_Entity_clearTags(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->clearTags();
		return 0;
	}

	duk_ret_t Polycode_Entity_addTag(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		String tag = duk_to_string(context, 1);
		(*inst)->addTag(tag);
		return 0;
	}

	duk_ret_t Polycode_Entity_getScreenPosition(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Matrix4 projectionMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Matrix4 cameraMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 3);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getScreenPosition(projectionMatrix,cameraMatrix,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_recalculateAABBAllChildren(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->recalculateAABBAllChildren();
		return 0;
	}

	duk_ret_t Polycode_Entity_recalculateAABB(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		(*inst)->recalculateAABB();
		return 0;
	}

	duk_ret_t Polycode_Entity_getWorldAABB(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<AABB> *retInst = new std::shared_ptr<AABB>;
		*(*retInst) = (*inst)->getWorldAABB();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_getLocalBoundingBox(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getLocalBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBox(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setLocalBoundingBox(box);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxX(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		(*inst)->setLocalBoundingBoxX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxY(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number y = duk_to_number(context, 1);
		(*inst)->setLocalBoundingBoxY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxZ(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		Number z = duk_to_number(context, 1);
		(*inst)->setLocalBoundingBoxZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_attachScript(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		shared_ptr<Script> script = *(shared_ptr<Script>*)duk_to_pointer(context, 1);
		(*inst)->attachScript(script);
		return 0;
	}

	duk_ret_t Polycode_Entity_getNumScripts(duk_context *context) {
		std::shared_ptr<Entity> *inst = (std::shared_ptr<Entity>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumScripts());
		return 1;
	}

	duk_ret_t Polycode_Event(duk_context *context) {
		std::shared_ptr<Event> *inst = new std::shared_ptr<Event>;
		(*inst) = std::make_shared<Event>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Event__get_deleteOnDispatch(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->deleteOnDispatch);
		return 1;
	}

	duk_ret_t Polycode_Event__set_deleteOnDispatch(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		inst->deleteOnDispatch = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Event__get_cancelEventFlag(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->cancelEventFlag);
		return 1;
	}

	duk_ret_t Polycode_Event__set_cancelEventFlag(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, 0);
		inst->cancelEventFlag = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Event__delete(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Event_getEventCode(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getEventCode());
		return 1;
	}

	duk_ret_t Polycode_Event_setEventCode(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		(*inst)->setEventCode(eventCode);
		return 0;
	}

	duk_ret_t Polycode_Event_getEventType(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getEventType().c_str());
		return 1;
	}

	duk_ret_t Polycode_Event_cancelEvent(duk_context *context) {
		std::shared_ptr<Event> *inst = (std::shared_ptr<Event>*)duk_to_pointer(context, 0);
		(*inst)->cancelEvent();
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher(duk_context *context) {
		std::shared_ptr<EventDispatcher> *inst = new std::shared_ptr<EventDispatcher>;
		(*inst) = std::make_shared<EventDispatcher>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_EventDispatcher__delete(duk_context *context) {
		std::shared_ptr<EventDispatcher> *inst = (std::shared_ptr<EventDispatcher>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeAllHandlers(duk_context *context) {
		std::shared_ptr<EventDispatcher> *inst = (std::shared_ptr<EventDispatcher>*)duk_to_pointer(context, 0);
		(*inst)->removeAllHandlers();
		return 0;
	}

	duk_ret_t Polycode_EventHandler(duk_context *context) {
		std::shared_ptr<EventHandler> *inst = new std::shared_ptr<EventHandler>;
		(*inst) = std::make_shared<EventHandler>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_EventHandler__delete(duk_context *context) {
		std::shared_ptr<EventHandler> *inst = (std::shared_ptr<EventHandler>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Font(duk_context *context) {
		std::shared_ptr<Font> *inst = new std::shared_ptr<Font>;
		(*inst) = std::make_shared<Font>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Font__get_loaded(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->loaded);
		return 1;
	}

	duk_ret_t Polycode_Font__set_loaded(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, 0);
		inst->loaded = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Font__delete(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Font_getFace(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		std::shared_ptr<FT_Face> *retInst = new std::shared_ptr<FT_Face>;
		*(*retInst) = (*inst)->getFace();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Font_isValid(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isValid());
		return 1;
	}

	duk_ret_t Polycode_Font_setFontName(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		String fontName = duk_to_string(context, 1);
		(*inst)->setFontName(fontName);
		return 0;
	}

	duk_ret_t Polycode_Font_getFontName(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getFontName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Font_getFontPath(duk_context *context) {
		std::shared_ptr<Font> *inst = (std::shared_ptr<Font>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getFontPath().c_str());
		return 1;
	}

	duk_ret_t Polycode_LightInfo(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = new std::shared_ptr<LightInfo>;
		(*inst) = std::make_shared<LightInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__get_importance(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->importance);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_importance(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->importance = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_position(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_position(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_direction(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_direction(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_type(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_type(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_diffuseColor(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->diffuseColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_diffuseColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->diffuseColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_specularColor(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->specularColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_specularColor(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->specularColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_constantAttenuation(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->constantAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_constantAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->constantAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_linearAttenuation(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->linearAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_linearAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->linearAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_quadraticAttenuation(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->quadraticAttenuation);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_quadraticAttenuation(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->quadraticAttenuation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_intensity(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->intensity);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_intensity(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->intensity = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_spotlightCutoff(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->spotlightCutoff);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_spotlightCutoff(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->spotlightCutoff = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_spotlightExponent(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->spotlightExponent);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_spotlightExponent(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->spotlightExponent = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_shadowsEnabled(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->shadowsEnabled);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_shadowsEnabled(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->shadowsEnabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__get_lightViewMatrix(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->lightViewMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LightInfo__set_lightViewMatrix(duk_context *context) {
		LightInfo *inst = (LightInfo*)duk_to_pointer(context, 0);
		inst->lightViewMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LightInfo__delete(duk_context *context) {
		std::shared_ptr<LightInfo> *inst = (std::shared_ptr<LightInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall(duk_context *context) {
		std::shared_ptr<GPUDrawCall> *inst = new std::shared_ptr<GPUDrawCall>;
		(*inst) = std::make_shared<GPUDrawCall>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__get_options(duk_context *context) {
		std::shared_ptr<GPUDrawCall> *inst = (std::shared_ptr<GPUDrawCall>*)duk_to_pointer(context, 0);
		std::shared_ptr<GPUDrawOptions> *retInst = new std::shared_ptr<GPUDrawOptions>;
		*retInst = std::make_shared<GPUDrawOptions>();
		*(*retInst) = (*inst)->options;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_options(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->options = *(GPUDrawOptions*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__get_modelMatrix(duk_context *context) {
		std::shared_ptr<GPUDrawCall> *inst = (std::shared_ptr<GPUDrawCall>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->modelMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawCall__set_modelMatrix(duk_context *context) {
		GPUDrawCall *inst = (GPUDrawCall*)duk_to_pointer(context, 0);
		inst->modelMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawCall__delete(duk_context *context) {
		std::shared_ptr<GPUDrawCall> *inst = (std::shared_ptr<GPUDrawCall>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = new std::shared_ptr<GPUDrawOptions>;
		(*inst) = std::make_shared<GPUDrawOptions>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthTest(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthTest);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthTest(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthTest = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthWrite(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthWrite);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthWrite(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthWrite = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_linePointSize(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->linePointSize);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_linePointSize(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->linePointSize = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_backfaceCull(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->backfaceCull);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_backfaceCull(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->backfaceCull = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_depthOnly(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthOnly);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_depthOnly(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->depthOnly = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_forceMaterial(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->forceMaterial);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_forceMaterial(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->forceMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_blendingMode(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_blendingMode(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_scissorBox(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->scissorBox;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_scissorBox(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->scissorBox = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_enableScissor(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enableScissor);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_enableScissor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->enableScissor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__get_drawColor(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->drawColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawOptions__set_drawColor(duk_context *context) {
		GPUDrawOptions *inst = (GPUDrawOptions*)duk_to_pointer(context, 0);
		inst->drawColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawOptions__delete(duk_context *context) {
		std::shared_ptr<GPUDrawOptions> *inst = (std::shared_ptr<GPUDrawOptions>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = new std::shared_ptr<GPUDrawBuffer>;
		(*inst) = std::make_shared<GPUDrawBuffer>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_projectionMatrix(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->projectionMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_projectionMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->projectionMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_viewMatrix(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->viewMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_viewMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->viewMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_cameraMatrix(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*retInst = std::make_shared<Matrix4>();
		*(*retInst) = (*inst)->cameraMatrix;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_cameraMatrix(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->cameraMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearColor(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->clearColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearColor(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearDepthBuffer(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->clearDepthBuffer);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearDepthBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearDepthBuffer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_clearColorBuffer(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->clearColorBuffer);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_clearColorBuffer(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->clearColorBuffer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_backingResolutionScale(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->backingResolutionScale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_backingResolutionScale(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->backingResolutionScale = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__get_viewport(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->viewport;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GPUDrawBuffer__set_viewport(duk_context *context) {
		GPUDrawBuffer *inst = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->viewport = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GPUDrawBuffer__delete(duk_context *context) {
		std::shared_ptr<GPUDrawBuffer> *inst = (std::shared_ptr<GPUDrawBuffer>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Image(duk_context *context) {
		std::shared_ptr<Image> *inst = new std::shared_ptr<Image>;
		(*inst) = std::make_shared<Image>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Image__delete(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Image_createEmpty(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int width = duk_to_int(context, 1);
		int height = duk_to_int(context, 2);
		Color fillColor = *(Color*)duk_to_pointer(context, 3);
		(*inst)->createEmpty(width,height,fillColor);
		return 0;
	}

	duk_ret_t Polycode_Image_fill(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		(*inst)->fill(color);
		return 0;
	}

	duk_ret_t Polycode_Image_setPixel(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		Number r = duk_to_number(context, 3);
		Number g = duk_to_number(context, 4);
		Number b = duk_to_number(context, 5);
		Number a = duk_to_number(context, 6);
		(*inst)->setPixel(x,y,r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Image_getPixel(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getPixel(x,y);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Image_drawLine(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x0 = duk_to_int(context, 1);
		int y0 = duk_to_int(context, 2);
		int x1 = duk_to_int(context, 3);
		int y1 = duk_to_int(context, 4);
		Color col = *(Color*)duk_to_pointer(context, 5);
		(*inst)->drawLine(x0,y0,x1,y1,col);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrushTo(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		(*inst)->moveBrushTo(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrush(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		(*inst)->moveBrush(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_drawLineTo(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		Color col = *(Color*)duk_to_pointer(context, 3);
		(*inst)->drawLineTo(x,y,col);
		return 0;
	}

	duk_ret_t Polycode_Image_fillRect(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int w = duk_to_int(context, 3);
		int h = duk_to_int(context, 4);
		Color col = *(Color*)duk_to_pointer(context, 5);
		(*inst)->fillRect(x,y,w,h,col);
		return 0;
	}

	duk_ret_t Polycode_Image_perlinNoise(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int seed = duk_to_int(context, 1);
		bool alpha = duk_to_boolean(context, 2);
		(*inst)->perlinNoise(seed,alpha);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlur(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		(*inst)->fastBlur(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurVert(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		(*inst)->fastBlurVert(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurHor(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		int blurSize = duk_to_int(context, 1);
		(*inst)->fastBlurHor(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_getBrushX(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getBrushX());
		return 1;
	}

	duk_ret_t Polycode_Image_getBrushY(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getBrushY());
		return 1;
	}

	duk_ret_t Polycode_Image_isLoaded(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isLoaded());
		return 1;
	}

	duk_ret_t Polycode_Image_getType(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getType());
		return 1;
	}

	duk_ret_t Polycode_Image_getWidth(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Image_getHeight(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Image_premultiplyAlpha(duk_context *context) {
		std::shared_ptr<Image> *inst = (std::shared_ptr<Image>*)duk_to_pointer(context, 0);
		(*inst)->premultiplyAlpha();
		return 0;
	}

	duk_ret_t Polycode_TouchInfo(duk_context *context) {
		std::shared_ptr<TouchInfo> *inst = new std::shared_ptr<TouchInfo>;
		(*inst) = std::make_shared<TouchInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__get_id(duk_context *context) {
		std::shared_ptr<TouchInfo> *inst = (std::shared_ptr<TouchInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->id);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_id(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->id = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__get_position(duk_context *context) {
		std::shared_ptr<TouchInfo> *inst = (std::shared_ptr<TouchInfo>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_position(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->position = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__get_type(duk_context *context) {
		std::shared_ptr<TouchInfo> *inst = (std::shared_ptr<TouchInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_TouchInfo__set_type(duk_context *context) {
		TouchInfo *inst = (TouchInfo*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_TouchInfo__delete(duk_context *context) {
		std::shared_ptr<TouchInfo> *inst = (std::shared_ptr<TouchInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_InputEvent(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = new std::shared_ptr<InputEvent>;
		(*inst) = std::make_shared<InputEvent>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__get_mouseButton(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->mouseButton);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_mouseButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->mouseButton = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_mousePosition(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->mousePosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_mousePosition(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->mousePosition = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_key(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->key);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_key(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->key = (PolyKEY)duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_timestamp(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->timestamp);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_timestamp(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->timestamp = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_text(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->text.c_str());
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_text(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->text = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_touch(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		std::shared_ptr<TouchInfo> *retInst = new std::shared_ptr<TouchInfo>;
		*retInst = std::make_shared<TouchInfo>();
		*(*retInst) = (*inst)->touch;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_touch(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->touch = *(TouchInfo*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_touchType(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->touchType);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_touchType(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->touchType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickDeviceID(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->joystickDeviceID);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickDeviceID(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickDeviceID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickAxisValue(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->joystickAxisValue);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickAxisValue(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickAxisValue = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickButton(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->joystickButton);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickButton = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickAxis(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->joystickAxis);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickAxis(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickAxis = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_joystickIndex(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->joystickIndex);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_joystickIndex(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->joystickIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__get_hitDistance(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->hitDistance);
		return 1;
	}

	duk_ret_t Polycode_InputEvent__set_hitDistance(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, 0);
		inst->hitDistance = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_InputEvent__delete(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getMousePosition(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getMousePosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_InputEvent_getKey(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getKey());
		return 1;
	}

	duk_ret_t Polycode_InputEvent_getMouseButton(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getMouseButton());
		return 1;
	}

	duk_ret_t Polycode_InputEvent_keyCode(duk_context *context) {
		std::shared_ptr<InputEvent> *inst = (std::shared_ptr<InputEvent>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->keyCode());
		return 1;
	}

	duk_ret_t Polycode_GlyphData(duk_context *context) {
		std::shared_ptr<GlyphData> *inst = new std::shared_ptr<GlyphData>;
		(*inst) = std::make_shared<GlyphData>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__get_num_glyphs(duk_context *context) {
		std::shared_ptr<GlyphData> *inst = (std::shared_ptr<GlyphData>*)duk_to_pointer(context, 0);
		std::shared_ptr<FT_UInt> *retInst = new std::shared_ptr<FT_UInt>;
		*retInst = std::make_shared<FT_UInt>();
		*(*retInst) = (*inst)->num_glyphs;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_num_glyphs(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->num_glyphs = *(FT_UInt*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__get_trailingAdvance(duk_context *context) {
		std::shared_ptr<GlyphData> *inst = (std::shared_ptr<GlyphData>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->trailingAdvance);
		return 1;
	}

	duk_ret_t Polycode_GlyphData__set_trailingAdvance(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, 0);
		inst->trailingAdvance = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_GlyphData__delete(duk_context *context) {
		std::shared_ptr<GlyphData> *inst = (std::shared_ptr<GlyphData>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_GlyphData_clearData(duk_context *context) {
		std::shared_ptr<GlyphData> *inst = (std::shared_ptr<GlyphData>*)duk_to_pointer(context, 0);
		(*inst)->clearData();
		return 0;
	}

	duk_ret_t Polycode_ColorRange(duk_context *context) {
		Color color = *(Color*)duk_to_pointer(context, 0);
		int rangeStart = duk_to_int(context, 1);
		int rangeEnd = duk_to_int(context, 2);
		std::shared_ptr<ColorRange> *inst = new std::shared_ptr<ColorRange>;
		(*inst) = std::make_shared<ColorRange>(color,rangeStart,rangeEnd);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__get_color(duk_context *context) {
		std::shared_ptr<ColorRange> *inst = (std::shared_ptr<ColorRange>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_color(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__get_rangeStart(duk_context *context) {
		std::shared_ptr<ColorRange> *inst = (std::shared_ptr<ColorRange>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->rangeStart);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_rangeStart(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->rangeStart = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__get_rangeEnd(duk_context *context) {
		std::shared_ptr<ColorRange> *inst = (std::shared_ptr<ColorRange>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->rangeEnd);
		return 1;
	}

	duk_ret_t Polycode_ColorRange__set_rangeEnd(duk_context *context) {
		ColorRange *inst = (ColorRange*)duk_to_pointer(context, 0);
		inst->rangeEnd = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ColorRange__delete(duk_context *context) {
		std::shared_ptr<ColorRange> *inst = (std::shared_ptr<ColorRange>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Label(duk_context *context) {
		shared_ptr<Font> font = *(shared_ptr<Font>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		int size = duk_to_int(context, 2);
		int antiAliasMode = duk_to_int(context, 3);
		bool premultiplyAlpha = duk_to_boolean(context, 4);
		Color backgroundColor = *(Color*)duk_to_pointer(context, 5);
		Color foregroundColor = *(Color*)duk_to_pointer(context, 6);
		std::shared_ptr<Label> *inst = new std::shared_ptr<Label>;
		(*inst) = std::make_shared<Label>(font,text,size,antiAliasMode,premultiplyAlpha,backgroundColor,foregroundColor);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Label__delete(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Label_setText(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		(*inst)->setText(text);
		return 0;
	}

	duk_ret_t Polycode_Label_getText(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getText().c_str());
		return 1;
	}

	duk_ret_t Polycode_Label_getTextWidthForString(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, (*inst)->getTextWidthForString(text));
		return 1;
	}

	duk_ret_t Polycode_Label_getTextHeightForString(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, (*inst)->getTextHeightForString(text));
		return 1;
	}

	duk_ret_t Polycode_Label_getTextWidth(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getTextWidth());
		return 1;
	}

	duk_ret_t Polycode_Label_getTextHeight(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getTextHeight());
		return 1;
	}

	duk_ret_t Polycode_Label_setColorForRange(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		int rangeStart = duk_to_int(context, 2);
		int rangeEnd = duk_to_int(context, 3);
		(*inst)->setColorForRange(color,rangeStart,rangeEnd);
		return 0;
	}

	duk_ret_t Polycode_Label_clearColors(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		(*inst)->clearColors();
		return 0;
	}

	duk_ret_t Polycode_Label_getColorForIndex(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getColorForIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_getPremultiplyAlpha(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getPremultiplyAlpha());
		return 1;
	}

	duk_ret_t Polycode_Label_setPremultiplyAlpha(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setPremultiplyAlpha(val);
		return 0;
	}

	duk_ret_t Polycode_Label_setFont(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		shared_ptr<Font> newFont = *(shared_ptr<Font>*)duk_to_pointer(context, 1);
		(*inst)->setFont(newFont);
		return 0;
	}

	duk_ret_t Polycode_Label_getFont(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Font>> *retInst = new std::shared_ptr<shared_ptr<Font>>;
		*(*retInst) = (*inst)->getFont();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_setSize(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		int newSize = duk_to_int(context, 1);
		(*inst)->setSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_Label_getSize(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getSize());
		return 1;
	}

	duk_ret_t Polycode_Label_getAntialiasMode(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getAntialiasMode());
		return 1;
	}

	duk_ret_t Polycode_Label_setAntialiasMode(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		int newMode = duk_to_int(context, 1);
		(*inst)->setAntialiasMode(newMode);
		return 0;
	}

	duk_ret_t Polycode_Label_getBaselineAdjust(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getBaselineAdjust());
		return 1;
	}

	duk_ret_t Polycode_Label_setBackgroundColor(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		(*inst)->setBackgroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setForegroundColor(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		(*inst)->setForegroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setColors(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		Color backgroundColor = *(Color*)duk_to_pointer(context, 1);
		Color foregroundColor = *(Color*)duk_to_pointer(context, 2);
		(*inst)->setColors(backgroundColor,foregroundColor);
		return 0;
	}

	duk_ret_t Polycode_Label_getBackgroundColor(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getBackgroundColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_getForegroundColor(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getForegroundColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Label_optionsChanged(duk_context *context) {
		std::shared_ptr<Label> *inst = (std::shared_ptr<Label>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->optionsChanged());
		return 1;
	}

	duk_ret_t Polycode_Material(duk_context *context) {
		String name = duk_to_string(context, 0);
		std::shared_ptr<Material> *inst = new std::shared_ptr<Material>;
		(*inst) = std::make_shared<Material>(name);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Material__get_fp16RenderTargets(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->fp16RenderTargets);
		return 1;
	}

	duk_ret_t Polycode_Material__set_fp16RenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->fp16RenderTargets = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__get_blendingMode(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_Material__set_blendingMode(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__get_screenMaterial(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->screenMaterial);
		return 1;
	}

	duk_ret_t Polycode_Material__set_screenMaterial(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, 0);
		inst->screenMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Material__delete(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPass(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		(*inst)->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPassForShader(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		shared_ptr<Shader> shader = *(shared_ptr<Shader>*)duk_to_pointer(context, 1);
		(*inst)->addShaderPassForShader(shader);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPassAtIndex(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		int shaderIndex = duk_to_int(context, 2);
		(*inst)->addShaderPassAtIndex(pass,shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderPasses(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_Material_removeShaderPass(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		int shaderIndex = duk_to_int(context, 1);
		(*inst)->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderRenderTargets(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumShaderRenderTargets());
		return 1;
	}

	duk_ret_t Polycode_Material_removeShaderRenderTarget(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		(*inst)->removeShaderRenderTarget(index);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateRenderTargets(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		Vector2 screenSize = *(Vector2*)duk_to_pointer(context, 1);
		(*inst)->recreateRenderTargets(screenSize);
		return 0;
	}

	duk_ret_t Polycode_Material_getName(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Material_getShaderPass(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<ShaderPass> *retInst = new std::shared_ptr<ShaderPass>;
		*(*retInst) = (*inst)->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Material_getShaderBinding(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<ShaderBinding>> *retInst = new std::shared_ptr<shared_ptr<ShaderBinding>>;
		*(*retInst) = (*inst)->getShaderBinding(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Material_getShader(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<Shader>> *retInst = new std::shared_ptr<shared_ptr<Shader>>;
		*(*retInst) = (*inst)->getShader(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Material_loadMaterial(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		(*inst)->loadMaterial(fileName);
		return 0;
	}

	duk_ret_t Polycode_Material_setName(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Material_clearShaders(duk_context *context) {
		std::shared_ptr<Material> *inst = (std::shared_ptr<Material>*)duk_to_pointer(context, 0);
		(*inst)->clearShaders();
		return 0;
	}

	duk_ret_t Polycode_ShaderPass(duk_context *context) {
		std::shared_ptr<ShaderPass> *inst = new std::shared_ptr<ShaderPass>;
		(*inst) = std::make_shared<ShaderPass>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__get_wireframe(duk_context *context) {
		std::shared_ptr<ShaderPass> *inst = (std::shared_ptr<ShaderPass>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->wireframe);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_wireframe(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->wireframe = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__get_blendingMode(duk_context *context) {
		std::shared_ptr<ShaderPass> *inst = (std::shared_ptr<ShaderPass>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->blendingMode);
		return 1;
	}

	duk_ret_t Polycode_ShaderPass__set_blendingMode(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, 0);
		inst->blendingMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass__delete(duk_context *context) {
		std::shared_ptr<ShaderPass> *inst = (std::shared_ptr<ShaderPass>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderPass_getShaderBinding(duk_context *context) {
		std::shared_ptr<ShaderPass> *inst = (std::shared_ptr<ShaderPass>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<ShaderBinding>> *retInst = new std::shared_ptr<shared_ptr<ShaderBinding>>;
		*(*retInst) = (*inst)->getShaderBinding();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = new std::shared_ptr<Matrix4>;
		(*inst) = std::make_shared<Matrix4>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4__delete(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Matrix4_identity(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		(*inst)->identity();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_rotateVector(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->rotateVector(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_getPosition(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getPosition();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multiplyWithPerspective(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->multiplyWithPerspective(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multVector3(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->multVector3(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_multVector4(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Vector4 v2 = *(Vector4*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector4> *retInst = new std::shared_ptr<Vector4>;
		*(*retInst) = (*inst)->multVector4(v2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_Translate(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setPosition(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setScale(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Vector3 scale = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setScale(scale);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_transpose(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->transpose();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_Inverse(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->Inverse();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_inverseAffine(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->inverseAffine();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Matrix4_determinant(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->determinant());
		return 1;
	}

	duk_ret_t Polycode_Matrix4_setOrthoProjection(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number zNear = duk_to_number(context, 5);
		Number zFar = duk_to_number(context, 6);
		(*inst)->setOrthoProjection(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjectionFrustum(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Number left = duk_to_number(context, 1);
		Number right = duk_to_number(context, 2);
		Number bottom = duk_to_number(context, 3);
		Number top = duk_to_number(context, 4);
		Number zNear = duk_to_number(context, 5);
		Number zFar = duk_to_number(context, 6);
		(*inst)->setProjectionFrustum(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjection(duk_context *context) {
		std::shared_ptr<Matrix4> *inst = (std::shared_ptr<Matrix4>*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		Number aspect = duk_to_number(context, 2);
		Number zNear = duk_to_number(context, 3);
		Number zFar = duk_to_number(context, 4);
		(*inst)->setProjection(fov,aspect,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Mesh(duk_context *context) {
		std::shared_ptr<Mesh> *inst = new std::shared_ptr<Mesh>;
		(*inst) = std::make_shared<Mesh>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Mesh__delete(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Mesh_addSubmesh(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		MeshGeometry newSubmesh = *(MeshGeometry*)duk_to_pointer(context, 1);
		(*inst)->addSubmesh(newSubmesh);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeSubmeshAtIndex(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		(*inst)->removeSubmeshAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getNumSubmeshes(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumSubmeshes());
		return 1;
	}

	duk_ret_t Polycode_Mesh_getSubmeshAtIndex(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<MeshGeometry> *retInst = new std::shared_ptr<MeshGeometry>;
		*(*retInst) = (*inst)->getSubmeshAtIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getSubmeshPointer(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<MeshGeometry>> *retInst = new std::shared_ptr<shared_ptr<MeshGeometry>>;
		*(*retInst) = (*inst)->getSubmeshPointer(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_clearMesh(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		(*inst)->clearMesh();
		return 0;
	}

	duk_ret_t Polycode_Mesh_calculateBBox(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->calculateBBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Mesh_getRadius(duk_context *context) {
		std::shared_ptr<Mesh> *inst = (std::shared_ptr<Mesh>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getRadius());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = new std::shared_ptr<MeshGeometry>;
		(*inst) = std::make_shared<MeshGeometry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry__get_meshType(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->meshType);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry__set_meshType(duk_context *context) {
		MeshGeometry *inst = (MeshGeometry*)duk_to_pointer(context, 0);
		inst->meshType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry__get_dataChanged(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->dataChanged);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry__set_dataChanged(duk_context *context) {
		MeshGeometry *inst = (MeshGeometry*)duk_to_pointer(context, 0);
		inst->dataChanged = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry__get_indexedMesh(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->indexedMesh);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry__set_indexedMesh(duk_context *context) {
		MeshGeometry *inst = (MeshGeometry*)duk_to_pointer(context, 0);
		inst->indexedMesh = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry__delete(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_clearMesh(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		(*inst)->clearMesh();
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_getVertexCount(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getVertexCount());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_createPlane(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		(*inst)->createPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createVPlane(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		(*inst)->createVPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createCircle(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		(*inst)->createCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createLineCircle(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		(*inst)->createLineCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createTorus(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		Number tubeRadius = duk_to_number(context, 2);
		int segmentsW = duk_to_int(context, 3);
		int segmentsH = duk_to_int(context, 4);
		Number tilingValue = duk_to_number(context, 5);
		(*inst)->createTorus(radius,tubeRadius,segmentsW,segmentsH,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createBox(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number d = duk_to_number(context, 2);
		Number h = duk_to_number(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		(*inst)->createBox(w,d,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createSphere(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int numRings = duk_to_int(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		(*inst)->createSphere(radius,numRings,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createIcosphere(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		(*inst)->createIcosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createOctosphere(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		(*inst)->createOctosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createCylinder(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		Number radius = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		bool capped = duk_to_boolean(context, 4);
		Number tilingValue = duk_to_number(context, 5);
		(*inst)->createCylinder(height,radius,numSegments,capped,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_createCone(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number height = duk_to_number(context, 1);
		Number radius = duk_to_number(context, 2);
		int numSegments = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		(*inst)->createCone(height,radius,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_recenterMesh(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->recenterMesh();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_setVertexAtOffset(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		(*inst)->setVertexAtOffset(offset,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addVertexWithUVAndNormal(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number u = duk_to_number(context, 4);
		Number v = duk_to_number(context, 5);
		Number nx = duk_to_number(context, 6);
		Number ny = duk_to_number(context, 7);
		Number nz = duk_to_number(context, 8);
		(*inst)->addVertexWithUVAndNormal(x,y,z,u,v,nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addTexCoord(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number u = duk_to_number(context, 1);
		Number v = duk_to_number(context, 2);
		(*inst)->addTexCoord(u,v);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addTexCoord2(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number u = duk_to_number(context, 1);
		Number v = duk_to_number(context, 2);
		(*inst)->addTexCoord2(u,v);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addTangent(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->addTangent(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addVertexWithUV(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number u = duk_to_number(context, 4);
		Number v = duk_to_number(context, 5);
		(*inst)->addVertexWithUV(x,y,z,u,v);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addVertex(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->addVertex(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addNormal(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number nx = duk_to_number(context, 1);
		Number ny = duk_to_number(context, 2);
		Number nz = duk_to_number(context, 3);
		(*inst)->addNormal(nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addBoneAssignments(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number b1Weight = duk_to_number(context, 1);
		int b1Index = duk_to_int(context, 2);
		Number b2Weight = duk_to_number(context, 3);
		int b2Index = duk_to_int(context, 4);
		Number b3Weight = duk_to_number(context, 5);
		int b3Index = duk_to_int(context, 6);
		Number b4Weight = duk_to_number(context, 7);
		int b4Index = duk_to_int(context, 8);
		(*inst)->addBoneAssignments(b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addColor(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->addColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_getVertexPosition(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int vertexOffset = duk_to_int(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getVertexPosition(vertexOffset);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_getVertexPositionAtIndex(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getVertexPositionAtIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_getVertexTexCoord(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int vertexOffset = duk_to_int(context, 1);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getVertexTexCoord(vertexOffset);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_getVertexTexCoordAtIndex(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getVertexTexCoordAtIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_getRadius(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getRadius());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_calculateNormals(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		(*inst)->calculateNormals();
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_calculateTangents(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		(*inst)->calculateTangents();
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_getMeshType(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getMeshType());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_setMeshType(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int newType = duk_to_int(context, 1);
		(*inst)->setMeshType(newType);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_getIndexGroupSize(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getIndexGroupSize());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_calculateBBox(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->calculateBBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_addIndexedFace(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int i1 = duk_to_int(context, 1);
		int i2 = duk_to_int(context, 2);
		(*inst)->addIndexedFace(i1,i2);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_addIndex(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		(*inst)->addIndex(index);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_removeVertexRange(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int beginRemoveVertex = duk_to_int(context, 1);
		int vertexRemovalCount = duk_to_int(context, 2);
		(*inst)->removeVertexRange(beginRemoveVertex,vertexRemovalCount);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_removeFace(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		int faceIndex = duk_to_int(context, 1);
		(*inst)->removeFace(faceIndex);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_removeUnusedVertices(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->removeUnusedVertices());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_getIndexCount(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getIndexCount());
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_subdivideToRadius(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		Number radius = duk_to_number(context, 1);
		int subdivisions = duk_to_int(context, 2);
		(*inst)->subdivideToRadius(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_calculateFaceTangent(duk_context *context) {
		Vector3 v1 = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 v3 = *(Vector3*)duk_to_pointer(context, 2);
		Vector2 texCoord1 = *(Vector2*)duk_to_pointer(context, 3);
		Vector2 texCoord2 = *(Vector2*)duk_to_pointer(context, 4);
		Vector2 texCoord3 = *(Vector2*)duk_to_pointer(context, 5);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = MeshGeometry::calculateFaceTangent(v1,v2,v3,texCoord1,texCoord2,texCoord3);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_MeshGeometry_saveAsOBJ(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		(*inst)->saveAsOBJ(fileName);
		return 0;
	}

	duk_ret_t Polycode_MeshGeometry_normalizeBoneWeights(duk_context *context) {
		std::shared_ptr<MeshGeometry> *inst = (std::shared_ptr<MeshGeometry>*)duk_to_pointer(context, 0);
		(*inst)->normalizeBoneWeights();
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = new std::shared_ptr<ObjectEntry>;
		(*inst) = std::make_shared<ObjectEntry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__get_type(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_type(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_name(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_name(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_NumberVal(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->NumberVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_NumberVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->NumberVal = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_intVal(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->intVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_intVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->intVal = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_stringVal(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->stringVal.c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_stringVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->stringVal = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_boolVal(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->boolVal);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_boolVal(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->boolVal = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__get_length(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->length);
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry__set_length(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->length = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry__delete(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_getTypedName(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getTypedName().c_str());
		return 1;
	}

	duk_ret_t Polycode_ObjectEntry_setTypedName(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		(*inst)->setTypedName(str);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_Clear(duk_context *context) {
		std::shared_ptr<ObjectEntry> *inst = (std::shared_ptr<ObjectEntry>*)duk_to_pointer(context, 0);
		(*inst)->Clear();
		return 0;
	}

	duk_ret_t Polycode_ShaderPlatformData(duk_context *context) {
		std::shared_ptr<ShaderPlatformData> *inst = new std::shared_ptr<ShaderPlatformData>;
		(*inst) = std::make_shared<ShaderPlatformData>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ShaderPlatformData__get_shaderID(duk_context *context) {
		std::shared_ptr<ShaderPlatformData> *inst = (std::shared_ptr<ShaderPlatformData>*)duk_to_pointer(context, 0);
		std::shared_ptr<GLuint> *retInst = new std::shared_ptr<GLuint>;
		*retInst = std::make_shared<GLuint>();
		*(*retInst) = (*inst)->shaderID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderPlatformData__set_shaderID(duk_context *context) {
		ShaderPlatformData *inst = (ShaderPlatformData*)duk_to_pointer(context, 0);
		inst->shaderID = *(GLuint*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPlatformData__get_vertexProgramID(duk_context *context) {
		std::shared_ptr<ShaderPlatformData> *inst = (std::shared_ptr<ShaderPlatformData>*)duk_to_pointer(context, 0);
		std::shared_ptr<GLuint> *retInst = new std::shared_ptr<GLuint>;
		*retInst = std::make_shared<GLuint>();
		*(*retInst) = (*inst)->vertexProgramID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderPlatformData__set_vertexProgramID(duk_context *context) {
		ShaderPlatformData *inst = (ShaderPlatformData*)duk_to_pointer(context, 0);
		inst->vertexProgramID = *(GLuint*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPlatformData__get_fragmentProgramID(duk_context *context) {
		std::shared_ptr<ShaderPlatformData> *inst = (std::shared_ptr<ShaderPlatformData>*)duk_to_pointer(context, 0);
		std::shared_ptr<GLuint> *retInst = new std::shared_ptr<GLuint>;
		*retInst = std::make_shared<GLuint>();
		*(*retInst) = (*inst)->fragmentProgramID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderPlatformData__set_fragmentProgramID(duk_context *context) {
		ShaderPlatformData *inst = (ShaderPlatformData*)duk_to_pointer(context, 0);
		inst->fragmentProgramID = *(GLuint*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderPlatformData__delete(duk_context *context) {
		std::shared_ptr<ShaderPlatformData> *inst = (std::shared_ptr<ShaderPlatformData>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneParticle(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = new std::shared_ptr<SceneParticle>;
		(*inst) = std::make_shared<SceneParticle>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__get_lifetime(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->lifetime);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_lifetime(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->lifetime = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_position(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_position(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_velocity(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->velocity;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_velocity(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->velocity = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_perlinPos(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->perlinPos;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_perlinPos(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->perlinPos = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_rotation(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->rotation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_rotation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->rotation = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_brightnessDeviation(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->brightnessDeviation);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_brightnessDeviation(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->brightnessDeviation = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_scale(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->scale);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_scale(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->scale = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_color(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->color;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_color(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->color = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__get_varianceIndex(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->varianceIndex);
		return 1;
	}

	duk_ret_t Polycode_SceneParticle__set_varianceIndex(duk_context *context) {
		SceneParticle *inst = (SceneParticle*)duk_to_pointer(context, 0);
		inst->varianceIndex = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticle__delete(duk_context *context) {
		std::shared_ptr<SceneParticle> *inst = (std::shared_ptr<SceneParticle>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter(duk_context *context) {
		int particleCount = duk_to_int(context, 0);
		Number lifetime = duk_to_number(context, 1);
		Number speed = duk_to_number(context, 2);
		std::shared_ptr<SceneParticleEmitter> *inst = new std::shared_ptr<SceneParticleEmitter>;
		(*inst) = std::make_shared<SceneParticleEmitter>(particleCount,lifetime,speed);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_useScaleCurve(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->useScaleCurve);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_useScaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->useScaleCurve = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_scaleCurve(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<BezierCurve> *retInst = new std::shared_ptr<BezierCurve>;
		*retInst = std::make_shared<BezierCurve>();
		*(*retInst) = (*inst)->scaleCurve;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_scaleCurve(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->scaleCurve = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_useColorCurves(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->useColorCurves);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_useColorCurves(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->useColorCurves = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveR(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<BezierCurve> *retInst = new std::shared_ptr<BezierCurve>;
		*retInst = std::make_shared<BezierCurve>();
		*(*retInst) = (*inst)->colorCurveR;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveR(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveR = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveG(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<BezierCurve> *retInst = new std::shared_ptr<BezierCurve>;
		*retInst = std::make_shared<BezierCurve>();
		*(*retInst) = (*inst)->colorCurveG;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveG(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveG = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveB(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<BezierCurve> *retInst = new std::shared_ptr<BezierCurve>;
		*retInst = std::make_shared<BezierCurve>();
		*(*retInst) = (*inst)->colorCurveB;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveB(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveB = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorCurveA(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<BezierCurve> *retInst = new std::shared_ptr<BezierCurve>;
		*retInst = std::make_shared<BezierCurve>();
		*(*retInst) = (*inst)->colorCurveA;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorCurveA(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorCurveA = *(BezierCurve*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__get_colorDeviation(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->colorDeviation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter__set_colorDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, 0);
		inst->colorDeviation = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter__delete(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleCount(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		int newParticleCount = duk_to_int(context, 1);
		(*inst)->setParticleCount(newParticleCount);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleCount(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getParticleCount());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleLifetime(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number lifetime = duk_to_number(context, 1);
		(*inst)->setParticleLifetime(lifetime);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleLifetime(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getParticleLifetime());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setDirectionDeviation(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 newDeviation = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setDirectionDeviation(newDeviation);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getDirectionDeviation(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getDirectionDeviation();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setEmitterSize(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 newSize = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setEmitterSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getEmitterSize(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getEmitterSize();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setGravity(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 newGravity = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setGravity(newGravity);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getGravity(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getGravity();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_fixedUpdate(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		(*inst)->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_updateParticles(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->updateParticles(elapsed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_triggerParticles(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool allAtOnce = duk_to_boolean(context, 1);
		(*inst)->triggerParticles(allAtOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_enableParticleSystem(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->enableParticleSystem(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setUseFloorPlane(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setUseFloorPlane(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorPlaneOffset(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number floorPlaneOffset = duk_to_number(context, 1);
		(*inst)->setFloorPlaneOffset(floorPlaneOffset);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorDamping(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number floorDamping = duk_to_number(context, 1);
		(*inst)->setFloorDamping(floorDamping);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticlesInWorldSpace(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setParticlesInWorldSpace(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticlesInWorldSpace(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getParticlesInWorldSpace());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinEnabled(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setPerlinEnabled(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinEnabled(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getPerlinEnabled());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSpeed(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getParticleSpeed());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSpeed(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		(*inst)->setParticleSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinValue(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 perlinValue = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setPerlinValue(perlinValue);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinValue(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getPerlinValue();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleType(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		int particleType = duk_to_int(context, 1);
		(*inst)->setParticleType(particleType);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleType(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getParticleType());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSize(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Number particleSize = duk_to_number(context, 1);
		(*inst)->setParticleSize(particleSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSize(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getParticleSize());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleRotationSpeed(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 rotationSpeed = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setParticleRotationSpeed(rotationSpeed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleRotationSpeed(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getParticleRotationSpeed();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleDirection(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setParticleDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleDirection(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getParticleDirection();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setLoopParticles(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setLoopParticles(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getLoopParticles(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getLoopParticles());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getNumSourceMeshes(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumSourceMeshes());
		return 1;
	}

	duk_ret_t Polycode_SceneParticleEmitter_removeSourceMeshAtIndex(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		(*inst)->removeSourceMeshAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_positionParticle(duk_context *context) {
		std::shared_ptr<SceneParticleEmitter> *inst = (std::shared_ptr<SceneParticleEmitter>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		(*inst)->positionParticle(index);
		return 0;
	}

	duk_ret_t Polycode_Perlin(duk_context *context) {
		int octaves = duk_to_int(context, 0);
		Number freq = duk_to_number(context, 1);
		Number amp = duk_to_number(context, 2);
		int seed = duk_to_int(context, 3);
		std::shared_ptr<Perlin> *inst = new std::shared_ptr<Perlin>;
		(*inst) = std::make_shared<Perlin>(octaves,freq,amp,seed);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Perlin__delete(duk_context *context) {
		std::shared_ptr<Perlin> *inst = (std::shared_ptr<Perlin>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get2DTiledX(duk_context *context) {
		std::shared_ptr<Perlin> *inst = (std::shared_ptr<Perlin>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number t = duk_to_number(context, 3);
		duk_push_number(context, (*inst)->Get2DTiledX(x,y,t));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get(duk_context *context) {
		std::shared_ptr<Perlin> *inst = (std::shared_ptr<Perlin>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		duk_push_number(context, (*inst)->Get(x,y));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get2D(duk_context *context) {
		std::shared_ptr<Perlin> *inst = (std::shared_ptr<Perlin>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		duk_push_number(context, (*inst)->Get2D(x,y));
		return 1;
	}

	duk_ret_t Polycode_Perlin_Get3D(duk_context *context) {
		std::shared_ptr<Perlin> *inst = (std::shared_ptr<Perlin>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		duk_push_number(context, (*inst)->Get3D(x,y,z));
		return 1;
	}

	duk_ret_t Polycode_Quaternion(duk_context *context) {
		Number w = duk_to_number(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		std::shared_ptr<Quaternion> *inst = new std::shared_ptr<Quaternion>;
		(*inst) = std::make_shared<Quaternion>(w,x,y,z);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__get_x(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->x);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_x(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_y(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->y);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_y(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_z(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->z);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_z(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__get_w(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->w);
		return 1;
	}

	duk_ret_t Polycode_Quaternion__set_w(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Quaternion__delete(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Quaternion_setFromMatrix(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Matrix4 _mat = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setFromMatrix(_mat);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Slerp(duk_context *context) {
		Number fT = duk_to_number(context, 0);
		Quaternion rkP = *(Quaternion*)duk_to_pointer(context, 1);
		Quaternion rkQ = *(Quaternion*)duk_to_pointer(context, 2);
		bool shortestPath = duk_to_boolean(context, 3);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = Quaternion::Slerp(fT,rkP,rkQ,shortestPath);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Dot(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Quaternion rkQ = *(Quaternion*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->Dot(rkQ));
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Log(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = (*inst)->Log();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Exp(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = (*inst)->Exp();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Norm(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->Norm());
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Normalize(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->Normalize());
		return 1;
	}

	duk_ret_t Polycode_Quaternion_lookAt(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Vector3 D = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 2);
		(*inst)->lookAt(D,upVector);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromMatrix(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->createFromMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Squad(duk_context *context) {
		Number fT = duk_to_number(context, 0);
		Quaternion rkP = *(Quaternion*)duk_to_pointer(context, 1);
		Quaternion rkA = *(Quaternion*)duk_to_pointer(context, 2);
		Quaternion rkB = *(Quaternion*)duk_to_pointer(context, 3);
		Quaternion rkQ = *(Quaternion*)duk_to_pointer(context, 4);
		bool shortestPath = duk_to_boolean(context, 5);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = Quaternion::Squad(fT,rkP,rkA,rkB,rkQ,shortestPath);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_Inverse(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*(*retInst) = (*inst)->Inverse();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_set(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number w = duk_to_number(context, 1);
		Number x = duk_to_number(context, 2);
		Number y = duk_to_number(context, 3);
		Number z = duk_to_number(context, 4);
		(*inst)->set(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_InvSqrt(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		duk_push_number(context, (*inst)->InvSqrt(x));
		return 1;
	}

	duk_ret_t Polycode_Quaternion_fromAxes(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number az = duk_to_number(context, 1);
		Number ay = duk_to_number(context, 2);
		Number ax = duk_to_number(context, 3);
		(*inst)->fromAxes(az,ay,ax);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_fromAngleAxis(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number rfAngle = duk_to_number(context, 1);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 2);
		(*inst)->fromAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_toEulerAngles(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->toEulerAngles();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_toAngleAxis(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number rfAngle = duk_to_number(context, 1);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 2);
		(*inst)->toAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromAxisAngle(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number degrees = duk_to_number(context, 4);
		(*inst)->createFromAxisAngle(x,y,z,degrees);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createMatrix(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->createMatrix();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Quaternion_applyTo(duk_context *context) {
		std::shared_ptr<Quaternion> *inst = (std::shared_ptr<Quaternion>*)duk_to_pointer(context, 0);
		Vector3 v = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->applyTo(v);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = new std::shared_ptr<QuatTriple>;
		(*inst) = std::make_shared<QuatTriple>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__get_q1(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = (std::shared_ptr<QuatTriple>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->q1;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q1(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q1 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_q2(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = (std::shared_ptr<QuatTriple>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->q2;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q2(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q2 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_q3(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = (std::shared_ptr<QuatTriple>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->q3;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_q3(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->q3 = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__get_time(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = (std::shared_ptr<QuatTriple>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->time);
		return 1;
	}

	duk_ret_t Polycode_QuatTriple__set_time(duk_context *context) {
		QuatTriple *inst = (QuatTriple*)duk_to_pointer(context, 0);
		inst->time = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_QuatTriple__delete(duk_context *context) {
		std::shared_ptr<QuatTriple> *inst = (std::shared_ptr<QuatTriple>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Ray(duk_context *context) {
		std::shared_ptr<Ray> *inst = new std::shared_ptr<Ray>;
		(*inst) = std::make_shared<Ray>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Ray__get_origin(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->origin;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_origin(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->origin = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__get_direction(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__get_inv_direction(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->inv_direction;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray__set_inv_direction(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, 0);
		inst->inv_direction = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Ray__delete(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Ray_boxIntersect(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 1);
		Matrix4 transformMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Number vnear = duk_to_number(context, 3);
		Number vfar = duk_to_number(context, 4);
		duk_push_number(context, (*inst)->boxIntersect(box,transformMatrix,vnear,vfar));
		return 1;
	}

	duk_ret_t Polycode_Ray_planeIntersectPoint(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		Vector3 planeNormal = *(Vector3*)duk_to_pointer(context, 1);
		Number planeDistance = duk_to_number(context, 2);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->planeIntersectPoint(planeNormal,planeDistance);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_tranformByMatrix(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 1);
		std::shared_ptr<Ray> *retInst = new std::shared_ptr<Ray>;
		*(*retInst) = (*inst)->tranformByMatrix(matrix);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_closestPointOnRay(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		Vector3 point = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->closestPointOnRay(point);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Ray_polygonIntersect(duk_context *context) {
		std::shared_ptr<Ray> *inst = (std::shared_ptr<Ray>*)duk_to_pointer(context, 0);
		Vector3 v1 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 2);
		Vector3 v3 = *(Vector3*)duk_to_pointer(context, 3);
		duk_push_boolean(context, (*inst)->polygonIntersect(v1,v2,v3));
		return 1;
	}

	duk_ret_t Polycode_Rectangle(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = new std::shared_ptr<Rectangle>;
		(*inst) = std::make_shared<Rectangle>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__get_x(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->x);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_x(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_y(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->y);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_y(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_w(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->w);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_w(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__get_h(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->h);
		return 1;
	}

	duk_ret_t Polycode_Rectangle__set_h(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, 0);
		inst->h = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Rectangle__delete(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Rectangle_setRect(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number w = duk_to_number(context, 3);
		Number h = duk_to_number(context, 4);
		(*inst)->setRect(x,y,w,h);
		return 0;
	}

	duk_ret_t Polycode_Rectangle_Clipped(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		Polycode::Rectangle rect = *(Polycode::Rectangle*)duk_to_pointer(context, 1);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*(*retInst) = (*inst)->Clipped(rect);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Rectangle_minX(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->minX());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_maxX(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->maxX());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_minY(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->minY());
		return 1;
	}

	duk_ret_t Polycode_Rectangle_maxY(duk_context *context) {
		std::shared_ptr<Rectangle> *inst = (std::shared_ptr<Rectangle>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->maxY());
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray(duk_context *context) {
		int type = duk_to_int(context, 0);
		std::shared_ptr<RenderDataArray> *inst = new std::shared_ptr<RenderDataArray>;
		(*inst) = std::make_shared<RenderDataArray>(type);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__get_type(duk_context *context) {
		std::shared_ptr<RenderDataArray> *inst = (std::shared_ptr<RenderDataArray>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_type(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__get_customArrayName(duk_context *context) {
		std::shared_ptr<RenderDataArray> *inst = (std::shared_ptr<RenderDataArray>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->customArrayName.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_customArrayName(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->customArrayName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__get_platformData(duk_context *context) {
		std::shared_ptr<RenderDataArray> *inst = (std::shared_ptr<RenderDataArray>*)duk_to_pointer(context, 0);
		std::shared_ptr<RendererPlatformData> *retInst = new std::shared_ptr<RendererPlatformData>;
		*retInst = std::make_shared<RendererPlatformData>();
		*(*retInst) = (*inst)->platformData;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderDataArray__set_platformData(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->platformData = *(RendererPlatformData*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray__delete(duk_context *context) {
		std::shared_ptr<RenderDataArray> *inst = (std::shared_ptr<RenderDataArray>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray_getDataSize(duk_context *context) {
		std::shared_ptr<RenderDataArray> *inst = (std::shared_ptr<RenderDataArray>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getDataSize());
		return 1;
	}

	duk_ret_t Polycode_LightShadowInfoBinding(duk_context *context) {
		std::shared_ptr<LightShadowInfoBinding> *inst = new std::shared_ptr<LightShadowInfoBinding>;
		(*inst) = std::make_shared<LightShadowInfoBinding>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_LightShadowInfoBinding__delete(duk_context *context) {
		std::shared_ptr<LightShadowInfoBinding> *inst = (std::shared_ptr<LightShadowInfoBinding>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_LightInfoBinding(duk_context *context) {
		std::shared_ptr<LightInfoBinding> *inst = new std::shared_ptr<LightInfoBinding>;
		(*inst) = std::make_shared<LightInfoBinding>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_LightInfoBinding__delete(duk_context *context) {
		std::shared_ptr<LightInfoBinding> *inst = (std::shared_ptr<LightInfoBinding>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderFrame(duk_context *context) {
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 0);
		std::shared_ptr<RenderFrame> *inst = new std::shared_ptr<RenderFrame>;
		(*inst) = std::make_shared<RenderFrame>(viewport);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderFrame__get_viewport(duk_context *context) {
		std::shared_ptr<RenderFrame> *inst = (std::shared_ptr<RenderFrame>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->viewport;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderFrame__set_viewport(duk_context *context) {
		RenderFrame *inst = (RenderFrame*)duk_to_pointer(context, 0);
		inst->viewport = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderFrame__delete(duk_context *context) {
		std::shared_ptr<RenderFrame> *inst = (std::shared_ptr<RenderFrame>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RendererThreadJob(duk_context *context) {
		std::shared_ptr<RendererThreadJob> *inst = new std::shared_ptr<RendererThreadJob>;
		(*inst) = std::make_shared<RendererThreadJob>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RendererThreadJob__get_jobType(duk_context *context) {
		std::shared_ptr<RendererThreadJob> *inst = (std::shared_ptr<RendererThreadJob>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->jobType);
		return 1;
	}

	duk_ret_t Polycode_RendererThreadJob__set_jobType(duk_context *context) {
		RendererThreadJob *inst = (RendererThreadJob*)duk_to_pointer(context, 0);
		inst->jobType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RendererThreadJob__delete(duk_context *context) {
		std::shared_ptr<RendererThreadJob> *inst = (std::shared_ptr<RendererThreadJob>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderThread(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = new std::shared_ptr<RenderThread>;
		(*inst) = std::make_shared<RenderThread>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderThread__delete(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderThread_runThread(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->runThread();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_beginFrame(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->beginFrame();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_endFrame(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->endFrame();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_updateRenderThread(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->updateRenderThread();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_processJob(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		RendererThreadJob job = *(RendererThreadJob*)duk_to_pointer(context, 1);
		(*inst)->processJob(job);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_clearFrameQueue(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->clearFrameQueue();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_getFrameInfo(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		std::shared_ptr<RenderThreadDebugInfo> *retInst = new std::shared_ptr<RenderThreadDebugInfo>;
		*(*retInst) = (*inst)->getFrameInfo();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderThread_initGlobals(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->initGlobals();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_lockRenderMutex(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->lockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_unlockRenderMutex(duk_context *context) {
		std::shared_ptr<RenderThread> *inst = (std::shared_ptr<RenderThread>*)duk_to_pointer(context, 0);
		(*inst)->unlockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo(duk_context *context) {
		std::shared_ptr<RenderThreadDebugInfo> *inst = new std::shared_ptr<RenderThreadDebugInfo>;
		(*inst) = std::make_shared<RenderThreadDebugInfo>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_buffersProcessed(duk_context *context) {
		std::shared_ptr<RenderThreadDebugInfo> *inst = (std::shared_ptr<RenderThreadDebugInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->buffersProcessed);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_buffersProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->buffersProcessed = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_drawCallsProcessed(duk_context *context) {
		std::shared_ptr<RenderThreadDebugInfo> *inst = (std::shared_ptr<RenderThreadDebugInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->drawCallsProcessed);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_drawCallsProcessed(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->drawCallsProcessed = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__get_timeTaken(duk_context *context) {
		std::shared_ptr<RenderThreadDebugInfo> *inst = (std::shared_ptr<RenderThreadDebugInfo>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->timeTaken);
		return 1;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__set_timeTaken(duk_context *context) {
		RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*)duk_to_pointer(context, 0);
		inst->timeTaken = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderThreadDebugInfo__delete(duk_context *context) {
		std::shared_ptr<RenderThreadDebugInfo> *inst = (std::shared_ptr<RenderThreadDebugInfo>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Renderer__delete(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Renderer_setBackingResolutionScale(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		Number xScale = duk_to_number(context, 1);
		Number yScale = duk_to_number(context, 2);
		(*inst)->setBackingResolutionScale(xScale,yScale);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleX(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getBackingResolutionScaleX());
		return 1;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleY(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getBackingResolutionScaleY());
		return 1;
	}

	duk_ret_t Polycode_Renderer_setAnisotropyAmount(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		Number amount = duk_to_number(context, 1);
		(*inst)->setAnisotropyAmount(amount);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getAnisotropyAmount(duk_context *context) {
		std::shared_ptr<Renderer> *inst = (std::shared_ptr<Renderer>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getAnisotropyAmount());
		return 1;
	}

	duk_ret_t Polycode_Renderer_unProject(duk_context *context) {
		Vector3 position = *(Vector3*)duk_to_pointer(context, 0);
		Matrix4 modelMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Matrix4 projectionMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 3);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = Renderer::unProject(position,modelMatrix,projectionMatrix,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Renderer_project(duk_context *context) {
		Vector3 position = *(Vector3*)duk_to_pointer(context, 0);
		Matrix4 modelMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Matrix4 projectionMatrix = *(Matrix4*)duk_to_pointer(context, 2);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*)duk_to_pointer(context, 3);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = Renderer::project(position,modelMatrix,projectionMatrix,viewport);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RendererPlatformData(duk_context *context) {
		std::shared_ptr<RendererPlatformData> *inst = new std::shared_ptr<RendererPlatformData>;
		(*inst) = std::make_shared<RendererPlatformData>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RendererPlatformData__get_type(duk_context *context) {
		std::shared_ptr<RendererPlatformData> *inst = (std::shared_ptr<RendererPlatformData>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_RendererPlatformData__set_type(duk_context *context) {
		RendererPlatformData *inst = (RendererPlatformData*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RendererPlatformData__delete(duk_context *context) {
		std::shared_ptr<RendererPlatformData> *inst = (std::shared_ptr<RendererPlatformData>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Resource(duk_context *context) {
		int type = duk_to_int(context, 0);
		std::shared_ptr<Resource> *inst = new std::shared_ptr<Resource>;
		(*inst) = std::make_shared<Resource>(type);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Resource__get_reloadOnFileModify(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->reloadOnFileModify);
		return 1;
	}

	duk_ret_t Polycode_Resource__set_reloadOnFileModify(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->reloadOnFileModify = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Resource__get_resourceFileTime(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*retInst = std::make_shared<size_t>();
		*(*retInst) = (*inst)->resourceFileTime;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Resource__set_resourceFileTime(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->resourceFileTime = *(size_t*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Resource__get_platformData(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		std::shared_ptr<RendererPlatformData> *retInst = new std::shared_ptr<RendererPlatformData>;
		*retInst = std::make_shared<RendererPlatformData>();
		*(*retInst) = (*inst)->platformData;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Resource__set_platformData(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, 0);
		inst->platformData = *(RendererPlatformData*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Resource__delete(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourceName(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getResourceName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Resource_getResourceType(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getResourceType());
		return 1;
	}

	duk_ret_t Polycode_Resource_setResourceName(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		String newName = duk_to_string(context, 1);
		(*inst)->setResourceName(newName);
		return 0;
	}

	duk_ret_t Polycode_Resource_setResourcePath(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		(*inst)->setResourcePath(path);
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourcePath(duk_context *context) {
		std::shared_ptr<Resource> *inst = (std::shared_ptr<Resource>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getResourcePath().c_str());
		return 1;
	}

	duk_ret_t Polycode_ScriptResourceLoader(duk_context *context) {
		std::shared_ptr<ScriptResourceLoader> *inst = new std::shared_ptr<ScriptResourceLoader>;
		(*inst) = std::make_shared<ScriptResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ScriptResourceLoader__delete(duk_context *context) {
		std::shared_ptr<ScriptResourceLoader> *inst = (std::shared_ptr<ScriptResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ResourcePool(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = new std::shared_ptr<ResourcePool>;
		(*inst) = std::make_shared<ResourcePool>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__get_reloadResourcesOnModify(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->reloadResourcesOnModify);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_reloadResourcesOnModify(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->reloadResourcesOnModify = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_dispatchChangeEvents(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->dispatchChangeEvents);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_dispatchChangeEvents(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->dispatchChangeEvents = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_resourceSubscribers(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->resourceSubscribers);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_resourceSubscribers(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->resourceSubscribers = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__get_deleteOnUnsubscribe(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->deleteOnUnsubscribe);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool__set_deleteOnUnsubscribe(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, 0);
		inst->deleteOnUnsubscribe = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool__delete(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_addResource(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		shared_ptr<Resource> resource = *(shared_ptr<Resource>*)duk_to_pointer(context, 1);
		(*inst)->addResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_removeResource(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		shared_ptr<Resource> resource = *(shared_ptr<Resource>*)duk_to_pointer(context, 1);
		(*inst)->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_hasResource(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		shared_ptr<Resource> resource = *(shared_ptr<Resource>*)duk_to_pointer(context, 1);
		duk_push_boolean(context, (*inst)->hasResource(resource));
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadResourcesFromFolder(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String folder = duk_to_string(context, 1);
		bool recursive = duk_to_boolean(context, 2);
		(*inst)->loadResourcesFromFolder(folder,recursive);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResourcesFromMaterialFile(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		(*inst)->loadResourcesFromMaterialFile(path);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResource(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Resource>> *retInst = new std::shared_ptr<shared_ptr<Resource>>;
		*(*retInst) = (*inst)->loadResource(path);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadResourceWithName(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String path = duk_to_string(context, 1);
		String name = duk_to_string(context, 2);
		std::shared_ptr<shared_ptr<Resource>> *retInst = new std::shared_ptr<shared_ptr<Resource>>;
		*(*retInst) = (*inst)->loadResourceWithName(path,name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getResource(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		String resourceName = duk_to_string(context, 2);
		std::shared_ptr<shared_ptr<Resource>> *retInst = new std::shared_ptr<shared_ptr<Resource>>;
		*(*retInst) = (*inst)->getResource(resourceType,resourceName);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getFont(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Font>> *retInst = new std::shared_ptr<shared_ptr<Font>>;
		*(*retInst) = (*inst)->getFont(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getMaterial(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Material>> *retInst = new std::shared_ptr<shared_ptr<Material>>;
		*(*retInst) = (*inst)->getMaterial(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getShader(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Shader>> *retInst = new std::shared_ptr<shared_ptr<Shader>>;
		*(*retInst) = (*inst)->getShader(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadTexture(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Texture>> *retInst = new std::shared_ptr<shared_ptr<Texture>>;
		*(*retInst) = (*inst)->loadTexture(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_loadMesh(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Mesh>> *retInst = new std::shared_ptr<shared_ptr<Mesh>>;
		*(*retInst) = (*inst)->loadMesh(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getName(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_setName(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->setName(name);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadFont(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		String path = duk_to_string(context, 2);
		std::shared_ptr<shared_ptr<Font>> *retInst = new std::shared_ptr<shared_ptr<Font>>;
		*(*retInst) = (*inst)->loadFont(name,path);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_getResourceByPath(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		String resourcePath = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Resource>> *retInst = new std::shared_ptr<shared_ptr<Resource>>;
		*(*retInst) = (*inst)->getResourceByPath(resourcePath);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ResourcePool_Update(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResources(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_checkForChangedFiles(duk_context *context) {
		std::shared_ptr<ResourcePool> *inst = (std::shared_ptr<ResourcePool>*)duk_to_pointer(context, 0);
		(*inst)->checkForChangedFiles();
		return 0;
	}

	duk_ret_t Polycode_ResourceManager(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = new std::shared_ptr<ResourceManager>;
		(*inst) = std::make_shared<ResourceManager>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ResourceManager__delete(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = (std::shared_ptr<ResourceManager>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getNumResourceLoaders(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = (std::shared_ptr<ResourceManager>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumResourceLoaders());
		return 1;
	}

	duk_ret_t Polycode_ResourceManager_getResources(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = (std::shared_ptr<ResourceManager>*)duk_to_pointer(context, 0);
		int resourceType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResource(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = (std::shared_ptr<ResourceManager>*)duk_to_pointer(context, 0);
		shared_ptr<Resource> resource = *(shared_ptr<Resource>*)duk_to_pointer(context, 1);
		(*inst)->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_Update(duk_context *context) {
		std::shared_ptr<ResourceManager> *inst = (std::shared_ptr<ResourceManager>*)duk_to_pointer(context, 0);
		int elapsed = duk_to_int(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_FontResourceLoader(duk_context *context) {
		std::shared_ptr<FontResourceLoader> *inst = new std::shared_ptr<FontResourceLoader>;
		(*inst) = std::make_shared<FontResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_FontResourceLoader__delete(duk_context *context) {
		std::shared_ptr<FontResourceLoader> *inst = (std::shared_ptr<FontResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramResourceLoader(duk_context *context) {
		std::shared_ptr<ProgramResourceLoader> *inst = new std::shared_ptr<ProgramResourceLoader>;
		(*inst) = std::make_shared<ProgramResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ProgramResourceLoader__delete(duk_context *context) {
		std::shared_ptr<ProgramResourceLoader> *inst = (std::shared_ptr<ProgramResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_DebugBackTraceEntry(duk_context *context) {
		std::shared_ptr<DebugBackTraceEntry> *inst = new std::shared_ptr<DebugBackTraceEntry>;
		(*inst) = std::make_shared<DebugBackTraceEntry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__get_fileName(duk_context *context) {
		std::shared_ptr<DebugBackTraceEntry> *inst = (std::shared_ptr<DebugBackTraceEntry>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->fileName.c_str());
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__set_fileName(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		inst->fileName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__get_lineNumber(duk_context *context) {
		std::shared_ptr<DebugBackTraceEntry> *inst = (std::shared_ptr<DebugBackTraceEntry>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->lineNumber);
		return 1;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__set_lineNumber(duk_context *context) {
		DebugBackTraceEntry *inst = (DebugBackTraceEntry*)duk_to_pointer(context, 0);
		inst->lineNumber = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_DebugBackTraceEntry__delete(duk_context *context) {
		std::shared_ptr<DebugBackTraceEntry> *inst = (std::shared_ptr<DebugBackTraceEntry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MeshResourceLoader(duk_context *context) {
		std::shared_ptr<MeshResourceLoader> *inst = new std::shared_ptr<MeshResourceLoader>;
		(*inst) = std::make_shared<MeshResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_MeshResourceLoader__delete(duk_context *context) {
		std::shared_ptr<MeshResourceLoader> *inst = (std::shared_ptr<MeshResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_MaterialResourceLoader(duk_context *context) {
		std::shared_ptr<MaterialResourceLoader> *inst = new std::shared_ptr<MaterialResourceLoader>;
		(*inst) = std::make_shared<MaterialResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_MaterialResourceLoader__delete(duk_context *context) {
		std::shared_ptr<MaterialResourceLoader> *inst = (std::shared_ptr<MaterialResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_TextureResourceLoader(duk_context *context) {
		std::shared_ptr<TextureResourceLoader> *inst = new std::shared_ptr<TextureResourceLoader>;
		(*inst) = std::make_shared<TextureResourceLoader>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_TextureResourceLoader__delete(duk_context *context) {
		std::shared_ptr<TextureResourceLoader> *inst = (std::shared_ptr<TextureResourceLoader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Scene(duk_context *context) {
		std::shared_ptr<Scene> *inst = new std::shared_ptr<Scene>;
		(*inst) = std::make_shared<Scene>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Scene__get_clearColor(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->clearColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_clearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->clearColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_useClearColor(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->useClearColor);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_useClearColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->useClearColor = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_useClearDepth(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->useClearDepth);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_useClearDepth(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->useClearDepth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_ambientColor(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->ambientColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_ambientColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->ambientColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_fogColor(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*retInst = std::make_shared<Color>();
		*(*retInst) = (*inst)->fogColor;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_fogColor(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->fogColor = *(Color*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_enabled(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enabled);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_enabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_ownsChildren(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->ownsChildren);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_ownsChildren(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->ownsChildren = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_rootEntity(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		std::shared_ptr<Entity> *retInst = new std::shared_ptr<Entity>;
		*retInst = std::make_shared<Entity>();
		*(*retInst) = (*inst)->rootEntity;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_rootEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->rootEntity = *(Entity*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_sceneMouseRect(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->sceneMouseRect;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_sceneMouseRect(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->sceneMouseRect = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_remapMouse(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->remapMouse);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_remapMouse(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->remapMouse = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__get_constrainPickingToViewport(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->constrainPickingToViewport);
		return 1;
	}

	duk_ret_t Polycode_Scene__set_constrainPickingToViewport(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, 0);
		inst->constrainPickingToViewport = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Scene__delete(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Scene_enableFog(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		bool enable = duk_to_boolean(context, 1);
		(*inst)->enableFog(enable);
		return 0;
	}

	duk_ret_t Polycode_Scene_setFogProperties(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		int fogMode = duk_to_int(context, 1);
		Color color = *(Color*)duk_to_pointer(context, 2);
		Number density = duk_to_number(context, 3);
		Number startDepth = duk_to_number(context, 4);
		Number endDepth = duk_to_number(context, 5);
		(*inst)->setFogProperties(fogMode,color,density,startDepth,endDepth);
		return 0;
	}

	duk_ret_t Polycode_Scene_setSceneType(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		int newType = duk_to_int(context, 1);
		(*inst)->setSceneType(newType);
		return 0;
	}

	duk_ret_t Polycode_Scene_fixedUpdate(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		(*inst)->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Scene_Update(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_Scene_isEnabled(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isEnabled());
		return 1;
	}

	duk_ret_t Polycode_Scene_setEnabled(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		bool enabled = duk_to_boolean(context, 1);
		(*inst)->setEnabled(enabled);
		return 0;
	}

	duk_ret_t Polycode_Scene_setOverrideMaterial(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		shared_ptr<Material> material = *(shared_ptr<Material>*)duk_to_pointer(context, 1);
		(*inst)->setOverrideMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_Scene_getNumLights(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumLights());
		return 1;
	}

	duk_ret_t Polycode_Scene_doVisibilityChecking(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->doVisibilityChecking(val);
		return 0;
	}

	duk_ret_t Polycode_Scene_doesVisibilityChecking(duk_context *context) {
		std::shared_ptr<Scene> *inst = (std::shared_ptr<Scene>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->doesVisibilityChecking());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceResourceEntry> *inst = new std::shared_ptr<SceneEntityInstanceResourceEntry>;
		(*inst) = std::make_shared<SceneEntityInstanceResourceEntry>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry__delete(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceResourceEntry> *inst = (std::shared_ptr<SceneEntityInstanceResourceEntry>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = new std::shared_ptr<SceneEntityInstance>;
		(*inst) = std::make_shared<SceneEntityInstance>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance__get_cloneUsingReload(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->cloneUsingReload);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance__set_cloneUsingReload(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->cloneUsingReload = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance__get_fileName(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->fileName.c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance__set_fileName(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, 0);
		inst->fileName = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance__delete(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_reloadEntityInstance(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		(*inst)->reloadEntityInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_clearInstance(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		(*inst)->clearInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_loadFromFile(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		duk_push_boolean(context, (*inst)->loadFromFile(fileName));
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLinkedResourePools(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumLinkedResourePools());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getResourceEntry(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<SceneEntityInstanceResourceEntry>> *retInst = new std::shared_ptr<shared_ptr<SceneEntityInstanceResourceEntry>>;
		*(*retInst) = (*inst)->getResourceEntry();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_hasLayerID(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		char layerID = *(char*)duk_to_pointer(context, 1);
		duk_push_boolean(context, (*inst)->hasLayerID(layerID));
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLayers(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumLayers());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstance_getFileName(duk_context *context) {
		std::shared_ptr<SceneEntityInstance> *inst = (std::shared_ptr<SceneEntityInstance>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getFileName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = new std::shared_ptr<SceneEntityInstanceLayer>;
		(*inst) = std::make_shared<SceneEntityInstanceLayer>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_name(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = (std::shared_ptr<SceneEntityInstanceLayer>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_name(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_layerID(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = (std::shared_ptr<SceneEntityInstanceLayer>*)duk_to_pointer(context, 0);
		std::shared_ptr<char> *retInst = new std::shared_ptr<char>;
		*retInst = std::make_shared<char>();
		*(*retInst) = (*inst)->layerID;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_layerID(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->layerID = *(char*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__get_visible(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = (std::shared_ptr<SceneEntityInstanceLayer>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->visible);
		return 1;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__set_visible(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->visible = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer__delete(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = (std::shared_ptr<SceneEntityInstanceLayer>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer_setLayerVisibility(duk_context *context) {
		std::shared_ptr<SceneEntityInstanceLayer> *inst = (std::shared_ptr<SceneEntityInstanceLayer>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setLayerVisibility(val);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel(duk_context *context) {
		shared_ptr<Material> material = *(shared_ptr<Material>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		int size = duk_to_int(context, 2);
		shared_ptr<Font> font = *(shared_ptr<Font>*)duk_to_pointer(context, 3);
		int amode = duk_to_int(context, 4);
		Number actualHeight = duk_to_number(context, 5);
		std::shared_ptr<SceneLabel> *inst = new std::shared_ptr<SceneLabel>;
		(*inst) = std::make_shared<SceneLabel>(material,text,size,font,amode,actualHeight);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneLabel__get_positionAtBaseline(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->positionAtBaseline);
		return 1;
	}

	duk_ret_t Polycode_SceneLabel__set_positionAtBaseline(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, 0);
		inst->positionAtBaseline = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel__delete(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getText(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getText().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_setLabelActualHeight(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		Number actualHeight = duk_to_number(context, 1);
		(*inst)->setLabelActualHeight(actualHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getLabelActualHeight(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getLabelActualHeight());
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_getTextWidthForString(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		String text = duk_to_string(context, 1);
		duk_push_int(context, (*inst)->getTextWidthForString(text));
		return 1;
	}

	duk_ret_t Polycode_SceneLabel_setText(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		String newText = duk_to_string(context, 1);
		(*inst)->setText(newText);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_updateFromLabel(duk_context *context) {
		std::shared_ptr<SceneLabel> *inst = (std::shared_ptr<SceneLabel>*)duk_to_pointer(context, 0);
		(*inst)->updateFromLabel();
		return 0;
	}

	duk_ret_t Polycode_SceneLight(duk_context *context) {
		int type = duk_to_int(context, 0);
		Number intensity = duk_to_number(context, 1);
		Number constantAttenuation = duk_to_number(context, 2);
		Number linearAttenuation = duk_to_number(context, 3);
		Number quadraticAttenuation = duk_to_number(context, 4);
		shared_ptr<Material> depthMapMaterial = *(shared_ptr<Material>*)duk_to_pointer(context, 5);
		std::shared_ptr<SceneLight> *inst = new std::shared_ptr<SceneLight>;
		(*inst) = std::make_shared<SceneLight>(type,intensity,constantAttenuation,linearAttenuation,quadraticAttenuation,depthMapMaterial);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneLight__delete(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getIntensity(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getIntensity());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setIntensity(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number newIntensity = duk_to_number(context, 1);
		(*inst)->setIntensity(newIntensity);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setAttenuation(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number constantAttenuation = duk_to_number(context, 1);
		Number linearAttenuation = duk_to_number(context, 2);
		Number quadraticAttenuation = duk_to_number(context, 3);
		(*inst)->setAttenuation(constantAttenuation,linearAttenuation,quadraticAttenuation);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getConstantAttenuation(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getConstantAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getLinearAttenuation(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getLinearAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getQuadraticAttenuation(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getQuadraticAttenuation());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getType(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getType());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getZBufferTexture(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Texture>> *retInst = new std::shared_ptr<shared_ptr<Texture>>;
		*(*retInst) = (*inst)->getZBufferTexture();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setSpecularLightColor(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->setSpecularLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setDiffuseLightColor(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->setDiffuseLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setLightColor(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number r = duk_to_number(context, 1);
		Number g = duk_to_number(context, 2);
		Number b = duk_to_number(context, 3);
		Number a = duk_to_number(context, 4);
		(*inst)->setLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setSpotlightProperties(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number spotlightCutoff = duk_to_number(context, 1);
		Number spotlightExponent = duk_to_number(context, 2);
		(*inst)->setSpotlightProperties(spotlightCutoff,spotlightExponent);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightCutoff(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getSpotlightCutoff());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightExponent(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getSpotlightExponent());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_enableShadows(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		int resolution = duk_to_int(context, 2);
		(*inst)->enableShadows(val,resolution);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setShadowMapFOV(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		Number fov = duk_to_number(context, 1);
		(*inst)->setShadowMapFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapFOV(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getShadowMapFOV());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapResolution(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getShadowMapResolution());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_areShadowsEnabled(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->areShadowsEnabled());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_getLightType(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getLightType());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setLightImportance(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		int newImportance = duk_to_int(context, 1);
		(*inst)->setLightImportance(newImportance);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightImportance(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getLightImportance());
		return 1;
	}

	duk_ret_t Polycode_SceneLight_setLightType(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		int lightType = duk_to_int(context, 1);
		(*inst)->setLightType(lightType);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightInfo(duk_context *context) {
		std::shared_ptr<SceneLight> *inst = (std::shared_ptr<SceneLight>*)duk_to_pointer(context, 0);
		std::shared_ptr<LightInfo> *retInst = new std::shared_ptr<LightInfo>;
		*(*retInst) = (*inst)->getLightInfo();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = new std::shared_ptr<SceneCurve>;
		(*inst) = std::make_shared<SceneCurve>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__get_renderCurve(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = (std::shared_ptr<SceneCurve>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->renderCurve);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__set_renderCurve(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		inst->renderCurve = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve__get_curveResolution(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = (std::shared_ptr<SceneCurve>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->curveResolution);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve__set_curveResolution(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, 0);
		inst->curveResolution = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve__delete(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = (std::shared_ptr<SceneCurve>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_getWorldPointAt(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = (std::shared_ptr<SceneCurve>*)duk_to_pointer(context, 0);
		Number t = duk_to_number(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getWorldPointAt(t);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneCurve_Update(duk_context *context) {
		std::shared_ptr<SceneCurve> *inst = (std::shared_ptr<SceneCurve>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneLine(duk_context *context) {
		Vector3 startp = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 endp = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<SceneLine> *inst = new std::shared_ptr<SceneLine>;
		(*inst) = std::make_shared<SceneLine>(startp,endp);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneLine__delete(duk_context *context) {
		std::shared_ptr<SceneLine> *inst = (std::shared_ptr<SceneLine>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setStart(duk_context *context) {
		std::shared_ptr<SceneLine> *inst = (std::shared_ptr<SceneLine>*)duk_to_pointer(context, 0);
		Vector3 startp = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setStart(startp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setEnd(duk_context *context) {
		std::shared_ptr<SceneLine> *inst = (std::shared_ptr<SceneLine>*)duk_to_pointer(context, 0);
		Vector3 endp = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setEnd(endp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_Update(duk_context *context) {
		std::shared_ptr<SceneLine> *inst = (std::shared_ptr<SceneLine>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = new std::shared_ptr<SceneMesh>;
		(*inst) = std::make_shared<SceneMesh>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__get_lineWidth(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->lineWidth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_lineWidth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->lineWidth = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_lineSmooth(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->lineSmooth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_lineSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->lineSmooth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_pointSmooth(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->pointSmooth);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_pointSmooth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->pointSmooth = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_useGeometryHitDetection(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->useGeometryHitDetection);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_useGeometryHitDetection(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->useGeometryHitDetection = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_backfaceCulled(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->backfaceCulled);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_backfaceCulled(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->backfaceCulled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__get_sendBoneMatricesToMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->sendBoneMatricesToMaterial);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh__set_sendBoneMatricesToMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, 0);
		inst->sendBoneMatricesToMaterial = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh__delete(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getShaderPass(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<ShaderPass> *retInst = new std::shared_ptr<ShaderPass>;
		*(*retInst) = (*inst)->getShaderPass(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_getNumShaderPasses(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumShaderPasses());
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_addShaderPass(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 1);
		(*inst)->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_removeShaderPass(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		int shaderIndex = duk_to_int(context, 1);
		(*inst)->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getMesh(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Mesh>> *retInst = new std::shared_ptr<shared_ptr<Mesh>>;
		*(*retInst) = (*inst)->getMesh();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_getMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Material>> *retInst = new std::shared_ptr<shared_ptr<Material>>;
		*(*retInst) = (*inst)->getMaterial();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_clearMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		(*inst)->clearMaterial();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		shared_ptr<Material> material = *(shared_ptr<Material>*)duk_to_pointer(context, 1);
		(*inst)->setMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMesh(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		shared_ptr<Mesh> mesh = *(shared_ptr<Mesh>*)duk_to_pointer(context, 1);
		(*inst)->setMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setSkeleton(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		shared_ptr<Skeleton> skeleton = *(shared_ptr<Skeleton>*)duk_to_pointer(context, 1);
		(*inst)->setSkeleton(skeleton);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getSkeleton(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Skeleton>> *retInst = new std::shared_ptr<shared_ptr<Skeleton>>;
		*(*retInst) = (*inst)->getSkeleton();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_setLineWidth(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		Number newWidth = duk_to_number(context, 1);
		(*inst)->setLineWidth(newWidth);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getFilename(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getFilename().c_str());
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_setFilename(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		(*inst)->setFilename(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_customHitDetection(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		Ray ray = *(Ray*)duk_to_pointer(context, 1);
		duk_push_boolean(context, (*inst)->customHitDetection(ray));
		return 1;
	}

	duk_ret_t Polycode_SceneMesh_setForceMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		bool forceMaterial = duk_to_boolean(context, 1);
		(*inst)->setForceMaterial(forceMaterial);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getForceMaterial(duk_context *context) {
		std::shared_ptr<SceneMesh> *inst = (std::shared_ptr<SceneMesh>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getForceMaterial());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive(duk_context *context) {
		int type = duk_to_int(context, 0);
		Number v1 = duk_to_number(context, 1);
		Number v2 = duk_to_number(context, 2);
		Number v3 = duk_to_number(context, 3);
		Number v4 = duk_to_number(context, 4);
		Number v5 = duk_to_number(context, 5);
		std::shared_ptr<ScenePrimitive> *inst = new std::shared_ptr<ScenePrimitive>;
		(*inst) = std::make_shared<ScenePrimitive>(type,v1,v2,v3,v4,v5);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive__delete(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_setPrimitiveOptions(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		Number v1 = duk_to_number(context, 2);
		Number v2 = duk_to_number(context, 3);
		Number v3 = duk_to_number(context, 4);
		Number v4 = duk_to_number(context, 5);
		Number v5 = duk_to_number(context, 6);
		(*inst)->setPrimitiveOptions(type,v1,v2,v3,v4,v5);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_recreatePrimitive(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		(*inst)->recreatePrimitive();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveType(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getPrimitiveType());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter1(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPrimitiveParameter1());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter2(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPrimitiveParameter2());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter3(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPrimitiveParameter3());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter4(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPrimitiveParameter4());
		return 1;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter5(duk_context *context) {
		std::shared_ptr<ScenePrimitive> *inst = (std::shared_ptr<ScenePrimitive>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPrimitiveParameter5());
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture(duk_context *context) {
		int renderWidth = duk_to_int(context, 0);
		int renderHeight = duk_to_int(context, 1);
		bool floatingPoint = duk_to_boolean(context, 2);
		std::shared_ptr<SceneRenderTexture> *inst = new std::shared_ptr<SceneRenderTexture>;
		(*inst) = std::make_shared<SceneRenderTexture>(renderWidth,renderHeight,floatingPoint);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture__get_enabled(duk_context *context) {
		std::shared_ptr<SceneRenderTexture> *inst = (std::shared_ptr<SceneRenderTexture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enabled);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture__set_enabled(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture__delete(duk_context *context) {
		std::shared_ptr<SceneRenderTexture> *inst = (std::shared_ptr<SceneRenderTexture>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetTexture(duk_context *context) {
		std::shared_ptr<SceneRenderTexture> *inst = (std::shared_ptr<SceneRenderTexture>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Texture>> *retInst = new std::shared_ptr<shared_ptr<Texture>>;
		*(*retInst) = (*inst)->getTargetTexture();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneRenderTexture_resizeRenderTexture(duk_context *context) {
		std::shared_ptr<SceneRenderTexture> *inst = (std::shared_ptr<SceneRenderTexture>*)duk_to_pointer(context, 0);
		int newWidth = duk_to_int(context, 1);
		int newHeight = duk_to_int(context, 2);
		(*inst)->resizeRenderTexture(newWidth,newHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneSound(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = new std::shared_ptr<SceneSound>;
		(*inst) = std::make_shared<SceneSound>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneSound__delete(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSound_Update(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_isDirectionalSound(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isDirectionalSound());
		return 1;
	}

	duk_ret_t Polycode_SceneSound_setDirectionalSound(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setDirectionalSound(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_setLoopOnLoad(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setLoopOnLoad(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_getLoopOnLoad(duk_context *context) {
		std::shared_ptr<SceneSound> *inst = (std::shared_ptr<SceneSound>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getLoopOnLoad());
		return 1;
	}

	duk_ret_t Polycode_SceneSoundListener(duk_context *context) {
		std::shared_ptr<SceneSoundListener> *inst = new std::shared_ptr<SceneSoundListener>;
		(*inst) = std::make_shared<SceneSoundListener>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneSoundListener__delete(duk_context *context) {
		std::shared_ptr<SceneSoundListener> *inst = (std::shared_ptr<SceneSoundListener>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSoundListener_Update(duk_context *context) {
		std::shared_ptr<SceneSoundListener> *inst = (std::shared_ptr<SceneSoundListener>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = new std::shared_ptr<SceneSprite>;
		(*inst) = std::make_shared<SceneSprite>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite__delete(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentSprite(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Sprite>> *retInst = new std::shared_ptr<shared_ptr<Sprite>>;
		*(*retInst) = (*inst)->getCurrentSprite();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteByName(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		String spriteName = duk_to_string(context, 1);
		(*inst)->setSpriteByName(spriteName);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setCurrentFrame(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		int frameIndex = duk_to_int(context, 1);
		(*inst)->setCurrentFrame(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentFrame(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getCurrentFrame());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_Update(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getSpriteBoundingBox(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getSpriteBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setPaused(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setPaused(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_isPaused(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isPaused());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setSprite(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		shared_ptr<Sprite> spriteEntry = *(shared_ptr<Sprite>*)duk_to_pointer(context, 1);
		(*inst)->setSprite(spriteEntry);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteStateByName(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		int startingFrame = duk_to_int(context, 2);
		bool playOnce = duk_to_boolean(context, 3);
		(*inst)->setSpriteStateByName(name,startingFrame,playOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getStartOnRandomFrame(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getStartOnRandomFrame());
		return 1;
	}

	duk_ret_t Polycode_SceneSprite_setStartOnRandomFrame(duk_context *context) {
		std::shared_ptr<SceneSprite> *inst = (std::shared_ptr<SceneSprite>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->setStartOnRandomFrame(val);
		return 0;
	}

	duk_ret_t Polycode_Sprite(duk_context *context) {
		String name = duk_to_string(context, 0);
		std::shared_ptr<Sprite> *inst = new std::shared_ptr<Sprite>;
		(*inst) = std::make_shared<Sprite>(name);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Sprite__delete(duk_context *context) {
		std::shared_ptr<Sprite> *inst = (std::shared_ptr<Sprite>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Sprite_getName(duk_context *context) {
		std::shared_ptr<Sprite> *inst = (std::shared_ptr<Sprite>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Sprite_setName(duk_context *context) {
		std::shared_ptr<Sprite> *inst = (std::shared_ptr<Sprite>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getNumStates(duk_context *context) {
		std::shared_ptr<Sprite> *inst = (std::shared_ptr<Sprite>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumStates());
		return 1;
	}

	duk_ret_t Polycode_SpriteSet(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = new std::shared_ptr<SpriteSet>;
		(*inst) = std::make_shared<SpriteSet>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet__delete(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setTexture(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		shared_ptr<Texture> texture = *(shared_ptr<Texture>*)duk_to_pointer(context, 1);
		(*inst)->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getTexture(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Texture>> *retInst = new std::shared_ptr<shared_ptr<Texture>>;
		*(*retInst) = (*inst)->getTexture();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteEntry(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		shared_ptr<Sprite> newEntry = *(shared_ptr<Sprite>*)duk_to_pointer(context, 1);
		(*inst)->addSpriteEntry(newEntry);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumSpriteEntries(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumSpriteEntries());
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteEntry(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<Sprite>> *retInst = new std::shared_ptr<shared_ptr<Sprite>>;
		*(*retInst) = (*inst)->getSpriteEntry(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_removeSprite(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		shared_ptr<Sprite> sprite = *(shared_ptr<Sprite>*)duk_to_pointer(context, 1);
		(*inst)->removeSprite(sprite);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_loadSpriteSet(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		(*inst)->loadSpriteSet(fileName);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteFrame(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 1);
		bool assignID = duk_to_boolean(context, 2);
		(*inst)->addSpriteFrame(frame,assignID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumFrames(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumFrames());
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrame(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<SpriteFrame> *retInst = new std::shared_ptr<SpriteFrame>;
		*(*retInst) = (*inst)->getSpriteFrame(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrameByID(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int frameID = duk_to_int(context, 1);
		std::shared_ptr<SpriteFrame> *retInst = new std::shared_ptr<SpriteFrame>;
		*(*retInst) = (*inst)->getSpriteFrameByID(frameID);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteSet_removeFrameByID(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int frameID = duk_to_int(context, 1);
		(*inst)->removeFrameByID(frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setSpriteFrame(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 1);
		(*inst)->setSpriteFrame(frame);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_clearFrames(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		(*inst)->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createGridFrames(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int xCount = duk_to_int(context, 1);
		int yCount = duk_to_int(context, 2);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 3);
		(*inst)->createGridFrames(xCount,yCount,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createFramesFromIslands(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		int minDistance = duk_to_int(context, 1);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 2);
		(*inst)->createFramesFromIslands(minDistance,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteByName(duk_context *context) {
		std::shared_ptr<SpriteSet> *inst = (std::shared_ptr<SpriteSet>*)duk_to_pointer(context, 0);
		String spriteName = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Sprite>> *retInst = new std::shared_ptr<shared_ptr<Sprite>>;
		*(*retInst) = (*inst)->getSpriteByName(spriteName);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame(duk_context *context) {
		std::shared_ptr<SpriteFrame> *inst = new std::shared_ptr<SpriteFrame>;
		(*inst) = std::make_shared<SpriteFrame>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__get_coordinates(duk_context *context) {
		std::shared_ptr<SpriteFrame> *inst = (std::shared_ptr<SpriteFrame>*)duk_to_pointer(context, 0);
		std::shared_ptr<Polycode::Rectangle> *retInst = new std::shared_ptr<Polycode::Rectangle>;
		*retInst = std::make_shared<Polycode::Rectangle>();
		*(*retInst) = (*inst)->coordinates;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_coordinates(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->coordinates = *(Rectangle*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__get_anchorPoint(duk_context *context) {
		std::shared_ptr<SpriteFrame> *inst = (std::shared_ptr<SpriteFrame>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*retInst = std::make_shared<Vector2>();
		*(*retInst) = (*inst)->anchorPoint;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_anchorPoint(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->anchorPoint = *(Vector2*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__get_frameID(duk_context *context) {
		std::shared_ptr<SpriteFrame> *inst = (std::shared_ptr<SpriteFrame>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->frameID);
		return 1;
	}

	duk_ret_t Polycode_SpriteFrame__set_frameID(duk_context *context) {
		SpriteFrame *inst = (SpriteFrame*)duk_to_pointer(context, 0);
		inst->frameID = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_SpriteFrame__delete(duk_context *context) {
		std::shared_ptr<SpriteFrame> *inst = (std::shared_ptr<SpriteFrame>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteState(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = new std::shared_ptr<SpriteState>;
		(*inst) = std::make_shared<SpriteState>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState__delete(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setName(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->setName(name);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getName(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getNumFrameIDs(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumFrameIDs());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getFrameIDAtIndex(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		duk_push_int(context, (*inst)->getFrameIDAtIndex(index));
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getMeshForFrameIndex(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<Mesh>> *retInst = new std::shared_ptr<shared_ptr<Mesh>>;
		*(*retInst) = (*inst)->getMeshForFrameIndex(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_insertFrame(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		int frameID = duk_to_int(context, 2);
		(*inst)->insertFrame(index,frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_removeFrameByIndex(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		int frameIndex = duk_to_int(context, 1);
		(*inst)->removeFrameByIndex(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_clearFrames(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		(*inst)->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setPixelsPerUnit(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		Number ppu = duk_to_number(context, 1);
		(*inst)->setPixelsPerUnit(ppu);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getPixelsPerUnit(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPixelsPerUnit());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_rebuildStateMeshes(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		(*inst)->rebuildStateMeshes();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setStateFPS(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		Number fps = duk_to_number(context, 1);
		(*inst)->setStateFPS(fps);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getStateFPS(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getStateFPS());
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getLargestFrameBoundingBox(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getLargestFrameBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_setBoundingBox(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		Vector2 boundingBox = *(Vector2*)duk_to_pointer(context, 1);
		(*inst)->setBoundingBox(boundingBox);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getBoundingBox(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getBoundingBox();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_getSpriteOffset(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getSpriteOffset();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_SpriteState_setSpriteOffset(duk_context *context) {
		std::shared_ptr<SpriteState> *inst = (std::shared_ptr<SpriteState>*)duk_to_pointer(context, 0);
		Vector2 offset = *(Vector2*)duk_to_pointer(context, 1);
		(*inst)->setSpriteOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_ScriptInstance(duk_context *context) {
		std::shared_ptr<ScriptInstance> *inst = new std::shared_ptr<ScriptInstance>;
		(*inst) = std::make_shared<ScriptInstance>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ScriptInstance__delete(duk_context *context) {
		std::shared_ptr<ScriptInstance> *inst = (std::shared_ptr<ScriptInstance>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramParam(duk_context *context) {
		std::shared_ptr<ProgramParam> *inst = new std::shared_ptr<ProgramParam>;
		(*inst) = std::make_shared<ProgramParam>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__get_name(duk_context *context) {
		std::shared_ptr<ProgramParam> *inst = (std::shared_ptr<ProgramParam>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__set_name(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__get_type(duk_context *context) {
		std::shared_ptr<ProgramParam> *inst = (std::shared_ptr<ProgramParam>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_ProgramParam__set_type(duk_context *context) {
		ProgramParam *inst = (ProgramParam*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramParam__delete(duk_context *context) {
		std::shared_ptr<ProgramParam> *inst = (std::shared_ptr<ProgramParam>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute(duk_context *context) {
		std::shared_ptr<ProgramAttribute> *inst = new std::shared_ptr<ProgramAttribute>;
		(*inst) = std::make_shared<ProgramAttribute>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__get_size(duk_context *context) {
		std::shared_ptr<ProgramAttribute> *inst = (std::shared_ptr<ProgramAttribute>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->size);
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__set_size(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		inst->size = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__get_name(duk_context *context) {
		std::shared_ptr<ProgramAttribute> *inst = (std::shared_ptr<ProgramAttribute>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__set_name(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__get_arrayType(duk_context *context) {
		std::shared_ptr<ProgramAttribute> *inst = (std::shared_ptr<ProgramAttribute>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->arrayType);
		return 1;
	}

	duk_ret_t Polycode_ProgramAttribute__set_arrayType(duk_context *context) {
		ProgramAttribute *inst = (ProgramAttribute*)duk_to_pointer(context, 0);
		inst->arrayType = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ProgramAttribute__delete(duk_context *context) {
		std::shared_ptr<ProgramAttribute> *inst = (std::shared_ptr<ProgramAttribute>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = new std::shared_ptr<ShaderRenderTarget>;
		(*inst) = std::make_shared<ShaderRenderTarget>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_id(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_id(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_width(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->width);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_width(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->width = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_height(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->height);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_height(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->height = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_sizeMode(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->sizeMode);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_sizeMode(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->sizeMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_normalizedWidth(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->normalizedWidth);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_normalizedWidth(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->normalizedWidth = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__get_normalizedHeight(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->normalizedHeight);
		return 1;
	}

	duk_ret_t Polycode_ShaderRenderTarget__set_normalizedHeight(duk_context *context) {
		ShaderRenderTarget *inst = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->normalizedHeight = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderRenderTarget__delete(duk_context *context) {
		std::shared_ptr<ShaderRenderTarget> *inst = (std::shared_ptr<ShaderRenderTarget>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding(duk_context *context) {
		std::shared_ptr<RenderTargetBinding> *inst = new std::shared_ptr<RenderTargetBinding>;
		(*inst) = std::make_shared<RenderTargetBinding>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_id(duk_context *context) {
		std::shared_ptr<RenderTargetBinding> *inst = (std::shared_ptr<RenderTargetBinding>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->id.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_id(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->id = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_name(duk_context *context) {
		std::shared_ptr<RenderTargetBinding> *inst = (std::shared_ptr<RenderTargetBinding>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_name(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__get_mode(duk_context *context) {
		std::shared_ptr<RenderTargetBinding> *inst = (std::shared_ptr<RenderTargetBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->mode);
		return 1;
	}

	duk_ret_t Polycode_RenderTargetBinding__set_mode(duk_context *context) {
		RenderTargetBinding *inst = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->mode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderTargetBinding__delete(duk_context *context) {
		std::shared_ptr<RenderTargetBinding> *inst = (std::shared_ptr<RenderTargetBinding>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Shader__get_numSpotLights(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->numSpotLights);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_numSpotLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->numSpotLights = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_numPointLights(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->numPointLights);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_numPointLights(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->numPointLights = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_screenShader(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->screenShader);
		return 1;
	}

	duk_ret_t Polycode_Shader__set_screenShader(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->screenShader = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__get_name(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_Shader__set_name(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Shader__delete(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Shader_getType(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getType());
		return 1;
	}

	duk_ret_t Polycode_Shader_setName(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_getName(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Shader_reload(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		(*inst)->reload();
		return 0;
	}

	duk_ret_t Polycode_Shader_getExpectedParamType(duk_context *context) {
		std::shared_ptr<Shader> *inst = (std::shared_ptr<Shader>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		duk_push_int(context, (*inst)->getExpectedParamType(name));
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = new std::shared_ptr<LocalShaderParam>;
		(*inst) = std::make_shared<LocalShaderParam>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__get_name(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_name(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_type(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_type(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_ownsPointer(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->ownsPointer);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_ownsPointer(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->ownsPointer = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__get_arraySize(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->arraySize);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam__set_arraySize(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->arraySize = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam__delete(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_Copy(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<LocalShaderParam>> *retInst = new std::shared_ptr<shared_ptr<LocalShaderParam>>;
		*(*retInst) = (*inst)->Copy();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getNumber(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getNumber());
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector2(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector2> *retInst = new std::shared_ptr<Vector2>;
		*(*retInst) = (*inst)->getVector2();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector3(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->getVector3();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getMatrix4(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<Matrix4> *retInst = new std::shared_ptr<Matrix4>;
		*(*retInst) = (*inst)->getMatrix4();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_getColor(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<Color> *retInst = new std::shared_ptr<Color>;
		*(*retInst) = (*inst)->getColor();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setNumber(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		(*inst)->setNumber(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector2(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		Vector2 x = *(Vector2*)duk_to_pointer(context, 1);
		(*inst)->setVector2(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector3(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		Vector3 x = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setVector3(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setMatrix4(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		Matrix4 x = *(Matrix4*)duk_to_pointer(context, 1);
		(*inst)->setMatrix4(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setMatrix4Array(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		vector<Matrix4> x = *(vector<Matrix4>*)duk_to_pointer(context, 1);
		(*inst)->setMatrix4Array(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setColor(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		Color x = *(Color*)duk_to_pointer(context, 1);
		(*inst)->setColor(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setTexture(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		shared_ptr<Texture> texture = *(shared_ptr<Texture>*)duk_to_pointer(context, 1);
		(*inst)->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getTexture(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Texture>> *retInst = new std::shared_ptr<shared_ptr<Texture>>;
		*(*retInst) = (*inst)->getTexture();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setCubemap(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		shared_ptr<Cubemap> cubemap = *(shared_ptr<Cubemap>*)duk_to_pointer(context, 1);
		(*inst)->setCubemap(cubemap);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getCubemap(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		std::shared_ptr<shared_ptr<Cubemap>> *retInst = new std::shared_ptr<shared_ptr<Cubemap>>;
		*(*retInst) = (*inst)->getCubemap();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_LocalShaderParam_setParamValueFromString(duk_context *context) {
		std::shared_ptr<LocalShaderParam> *inst = (std::shared_ptr<LocalShaderParam>*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		String pvalue = duk_to_string(context, 2);
		(*inst)->setParamValueFromString(type,pvalue);
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram(duk_context *context) {
		String fileName = duk_to_string(context, 0);
		std::shared_ptr<ShaderProgram> *inst = new std::shared_ptr<ShaderProgram>;
		(*inst) = std::make_shared<ShaderProgram>(fileName);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ShaderProgram__get_type(duk_context *context) {
		std::shared_ptr<ShaderProgram> *inst = (std::shared_ptr<ShaderProgram>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_ShaderProgram__set_type(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram__delete(duk_context *context) {
		std::shared_ptr<ShaderProgram> *inst = (std::shared_ptr<ShaderProgram>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram_reloadProgram(duk_context *context) {
		std::shared_ptr<ShaderProgram> *inst = (std::shared_ptr<ShaderProgram>*)duk_to_pointer(context, 0);
		(*inst)->reloadProgram();
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding(duk_context *context) {
		std::shared_ptr<AttributeBinding> *inst = new std::shared_ptr<AttributeBinding>;
		(*inst) = std::make_shared<AttributeBinding>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__get_name(duk_context *context) {
		std::shared_ptr<AttributeBinding> *inst = (std::shared_ptr<AttributeBinding>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->name.c_str());
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_name(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->name = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__get_enabled(duk_context *context) {
		std::shared_ptr<AttributeBinding> *inst = (std::shared_ptr<AttributeBinding>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->enabled);
		return 1;
	}

	duk_ret_t Polycode_AttributeBinding__set_enabled(duk_context *context) {
		AttributeBinding *inst = (AttributeBinding*)duk_to_pointer(context, 0);
		inst->enabled = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AttributeBinding__delete(duk_context *context) {
		std::shared_ptr<AttributeBinding> *inst = (std::shared_ptr<AttributeBinding>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = new std::shared_ptr<ShaderBinding>;
		(*inst) = std::make_shared<ShaderBinding>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding__delete(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addParam(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		int type = duk_to_int(context, 1);
		String name = duk_to_string(context, 2);
		std::shared_ptr<shared_ptr<LocalShaderParam>> *retInst = new std::shared_ptr<shared_ptr<LocalShaderParam>>;
		*(*retInst) = (*inst)->addParam(type,name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_addParamFromData(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		String data = duk_to_string(context, 2);
		std::shared_ptr<shared_ptr<LocalShaderParam>> *retInst = new std::shared_ptr<shared_ptr<LocalShaderParam>>;
		*(*retInst) = (*inst)->addParamFromData(name,data);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumLocalParams(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumLocalParams());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParam(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<LocalShaderParam>> *retInst = new std::shared_ptr<shared_ptr<LocalShaderParam>>;
		*(*retInst) = (*inst)->getLocalParam(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParamByName(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<LocalShaderParam>> *retInst = new std::shared_ptr<shared_ptr<LocalShaderParam>>;
		*(*retInst) = (*inst)->getLocalParamByName(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_removeParam(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->removeParam(name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_setTextureForParam(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		String paramName = duk_to_string(context, 1);
		shared_ptr<Texture> texture = *(shared_ptr<Texture>*)duk_to_pointer(context, 2);
		(*inst)->setTextureForParam(paramName,texture);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_setCubemapForParam(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		String paramName = duk_to_string(context, 1);
		shared_ptr<Cubemap> cubemap = *(shared_ptr<Cubemap>*)duk_to_pointer(context, 2);
		(*inst)->setCubemapForParam(paramName,cubemap);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumAttributeBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumAttributeBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumRenderTargetBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumRenderTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumInTargetBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumInTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumColorTargetBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumColorTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumDepthTargetBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumDepthTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_ShaderBinding_getNumOutTargetBindings(duk_context *context) {
		std::shared_ptr<ShaderBinding> *inst = (std::shared_ptr<ShaderBinding>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumOutTargetBindings());
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation(duk_context *context) {
		String name = duk_to_string(context, 0);
		Number duration = duk_to_number(context, 1);
		std::shared_ptr<SkeletonAnimation> *inst = new std::shared_ptr<SkeletonAnimation>;
		(*inst) = std::make_shared<SkeletonAnimation>(name,duration);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation__delete(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getName(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getName().c_str());
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation_Play(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		bool once = duk_to_boolean(context, 1);
		(*inst)->Play(once);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Stop(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		(*inst)->Stop();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Reset(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		(*inst)->Reset();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Update(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setSpeed(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		(*inst)->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setWeight(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		Number newWeight = duk_to_number(context, 1);
		(*inst)->setWeight(newWeight);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getWeight(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getWeight());
		return 1;
	}

	duk_ret_t Polycode_SkeletonAnimation_isPlaying(duk_context *context) {
		std::shared_ptr<SkeletonAnimation> *inst = (std::shared_ptr<SkeletonAnimation>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isPlaying());
		return 1;
	}

	duk_ret_t Polycode_Skeleton(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = new std::shared_ptr<Skeleton>;
		(*inst) = std::make_shared<Skeleton>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Skeleton__delete(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Skeleton_playAnimationByName(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		String animName = duk_to_string(context, 1);
		Number weight = duk_to_number(context, 2);
		bool once = duk_to_boolean(context, 3);
		bool restartIfPlaying = duk_to_boolean(context, 4);
		(*inst)->playAnimationByName(animName,weight,once,restartIfPlaying);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_setBaseAnimationByName(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		String animName = duk_to_string(context, 1);
		(*inst)->setBaseAnimationByName(animName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAllAnimations(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		(*inst)->stopAllAnimations();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAnimationByName(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		(*inst)->stopAnimationByName(name);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_Update(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneByName(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		String name = duk_to_string(context, 1);
		std::shared_ptr<shared_ptr<Bone>> *retInst = new std::shared_ptr<shared_ptr<Bone>>;
		*(*retInst) = (*inst)->getBoneByName(name);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_bonesVisible(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		bool val = duk_to_boolean(context, 1);
		(*inst)->bonesVisible(val);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getNumBones(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumBones());
		return 1;
	}

	duk_ret_t Polycode_Skeleton_getBone(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		int index = duk_to_int(context, 1);
		std::shared_ptr<shared_ptr<Bone>> *retInst = new std::shared_ptr<shared_ptr<Bone>>;
		*(*retInst) = (*inst)->getBone(index);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Skeleton_addBone(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 1);
		(*inst)->addBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_removeBone(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 1);
		(*inst)->removeBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneIndexByBone(duk_context *context) {
		std::shared_ptr<Skeleton> *inst = (std::shared_ptr<Skeleton>*)duk_to_pointer(context, 0);
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 1);
		duk_push_int(context, (*inst)->getBoneIndexByBone(bone));
		return 1;
	}

	duk_ret_t Polycode_BoneTrack(duk_context *context) {
		shared_ptr<Bone> bone = *(shared_ptr<Bone>*)duk_to_pointer(context, 0);
		Number length = duk_to_number(context, 1);
		std::shared_ptr<BoneTrack> *inst = new std::shared_ptr<BoneTrack>;
		(*inst) = std::make_shared<BoneTrack>(bone,length);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__get_position(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->position;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_position(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->position = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_scale(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->scale;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_scale(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->scale = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_boneQuat(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->boneQuat;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_boneQuat(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->boneQuat = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__get_weight(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->weight);
		return 1;
	}

	duk_ret_t Polycode_BoneTrack__set_weight(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, 0);
		inst->weight = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack__delete(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Play(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		bool once = duk_to_boolean(context, 1);
		(*inst)->Play(once);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Stop(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		(*inst)->Stop();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Update(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		Number elapsed = duk_to_number(context, 1);
		(*inst)->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Reset(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		(*inst)->Reset();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_setSpeed(duk_context *context) {
		std::shared_ptr<BoneTrack> *inst = (std::shared_ptr<BoneTrack>*)duk_to_pointer(context, 0);
		Number speed = duk_to_number(context, 1);
		(*inst)->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_Sound(duk_context *context) {
		std::shared_ptr<Sound> *inst = new std::shared_ptr<Sound>;
		(*inst) = std::make_shared<Sound>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Sound__delete(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Sound_getSampleAsNumber(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		int channel = duk_to_int(context, 2);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 3);
		Quaternion orientation = *(Quaternion*)duk_to_pointer(context, 4);
		duk_push_number(context, (*inst)->getSampleAsNumber(offset,channel,position,orientation));
		return 1;
	}

	duk_ret_t Polycode_Sound_Play(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		bool loop = duk_to_boolean(context, 1);
		bool restartSound = duk_to_boolean(context, 2);
		(*inst)->Play(loop,restartSound);
		return 0;
	}

	duk_ret_t Polycode_Sound_Stop(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		(*inst)->Stop();
		return 0;
	}

	duk_ret_t Polycode_Sound_setVolume(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number newVolume = duk_to_number(context, 1);
		(*inst)->setVolume(newVolume);
		return 0;
	}

	duk_ret_t Polycode_Sound_getVolume(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getVolume());
		return 1;
	}

	duk_ret_t Polycode_Sound_setPitch(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number newPitch = duk_to_number(context, 1);
		(*inst)->setPitch(newPitch);
		return 0;
	}

	duk_ret_t Polycode_Sound_getPitch(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPitch());
		return 1;
	}

	duk_ret_t Polycode_Sound_isPlaying(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isPlaying());
		return 1;
	}

	duk_ret_t Polycode_Sound_isLooped(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isLooped());
		return 1;
	}

	duk_ret_t Polycode_Sound_setIsPositional(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		bool isPositional = duk_to_boolean(context, 1);
		(*inst)->setIsPositional(isPositional);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundPosition(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setSoundPosition(position);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundVelocity(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Vector3 velocity = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setSoundVelocity(velocity);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundDirection(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setSoundDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_Sound_setOffset(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		int offset = duk_to_int(context, 1);
		(*inst)->setOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_Sound_getFileName(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->getFileName().c_str());
		return 1;
	}

	duk_ret_t Polycode_Sound_getPlaybackDuration(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPlaybackDuration());
		return 1;
	}

	duk_ret_t Polycode_Sound_getPlaybackTime(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getPlaybackTime());
		return 1;
	}

	duk_ret_t Polycode_Sound_seekTo(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number time = duk_to_number(context, 1);
		(*inst)->seekTo(time);
		return 0;
	}

	duk_ret_t Polycode_Sound_getOffset(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getOffset());
		return 1;
	}

	duk_ret_t Polycode_Sound_getSampleLength(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getSampleLength());
		return 1;
	}

	duk_ret_t Polycode_Sound_getFrequency(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getFrequency());
		return 1;
	}

	duk_ret_t Polycode_Sound_setPositionalProperties(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number referenceDistance = duk_to_number(context, 1);
		Number maxDistance = duk_to_number(context, 2);
		(*inst)->setPositionalProperties(referenceDistance,maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setReferenceDistance(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number referenceDistance = duk_to_number(context, 1);
		(*inst)->setReferenceDistance(referenceDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setMaxDistance(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		Number maxDistance = duk_to_number(context, 1);
		(*inst)->setMaxDistance(maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_getReferenceDistance(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getReferenceDistance());
		return 1;
	}

	duk_ret_t Polycode_Sound_getMaxDistance(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->getMaxDistance());
		return 1;
	}

	duk_ret_t Polycode_Sound_soundCheck(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		bool result = duk_to_boolean(context, 1);
		String err = duk_to_string(context, 2);
		(*inst)->soundCheck(result,err);
		return 0;
	}

	duk_ret_t Polycode_Sound_updateStream(duk_context *context) {
		std::shared_ptr<Sound> *inst = (std::shared_ptr<Sound>*)duk_to_pointer(context, 0);
		int streamCount = duk_to_int(context, 1);
		(*inst)->updateStream(streamCount);
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource(duk_context *context) {
		int channels = duk_to_int(context, 0);
		int freq = duk_to_int(context, 1);
		std::shared_ptr<AudioStreamingSource> *inst = new std::shared_ptr<AudioStreamingSource>;
		(*inst) = std::make_shared<AudioStreamingSource>(channels,freq);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_AudioStreamingSource__delete(duk_context *context) {
		std::shared_ptr<AudioStreamingSource> *inst = (std::shared_ptr<AudioStreamingSource>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource_getNumChannels(duk_context *context) {
		std::shared_ptr<AudioStreamingSource> *inst = (std::shared_ptr<AudioStreamingSource>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getNumChannels());
		return 1;
	}

	duk_ret_t Polycode_AudioStreamingSource_getFrequency(duk_context *context) {
		std::shared_ptr<AudioStreamingSource> *inst = (std::shared_ptr<AudioStreamingSource>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getFrequency());
		return 1;
	}

	duk_ret_t Polycode_AudioMixer(duk_context *context) {
		std::shared_ptr<AudioMixer> *inst = new std::shared_ptr<AudioMixer>;
		(*inst) = std::make_shared<AudioMixer>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__get_globalVolume(duk_context *context) {
		std::shared_ptr<AudioMixer> *inst = (std::shared_ptr<AudioMixer>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->globalVolume);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__set_globalVolume(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		inst->globalVolume = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AudioMixer__get_listenerPosition(duk_context *context) {
		std::shared_ptr<AudioMixer> *inst = (std::shared_ptr<AudioMixer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*retInst = std::make_shared<Vector3>();
		*(*retInst) = (*inst)->listenerPosition;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__set_listenerPosition(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		inst->listenerPosition = *(Vector3*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AudioMixer__get_listenerOrientation(duk_context *context) {
		std::shared_ptr<AudioMixer> *inst = (std::shared_ptr<AudioMixer>*)duk_to_pointer(context, 0);
		std::shared_ptr<Quaternion> *retInst = new std::shared_ptr<Quaternion>;
		*retInst = std::make_shared<Quaternion>();
		*(*retInst) = (*inst)->listenerOrientation;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_AudioMixer__set_listenerOrientation(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, 0);
		inst->listenerOrientation = *(Quaternion*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_AudioMixer__delete(duk_context *context) {
		std::shared_ptr<AudioMixer> *inst = (std::shared_ptr<AudioMixer>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SoundManager(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = new std::shared_ptr<SoundManager>;
		(*inst) = std::make_shared<SoundManager>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_SoundManager__delete(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerPosition(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 1);
		(*inst)->setListenerPosition(position);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerOrientation(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		Quaternion orientation = *(Quaternion*)duk_to_pointer(context, 1);
		(*inst)->setListenerOrientation(orientation);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_recordSound(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		int rate = duk_to_int(context, 1);
		int sampleSize = duk_to_int(context, 2);
		duk_push_boolean(context, (*inst)->recordSound(rate,sampleSize));
		return 1;
	}

	duk_ret_t Polycode_SoundManager_Update(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		(*inst)->Update();
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setGlobalVolume(duk_context *context) {
		std::shared_ptr<SoundManager> *inst = (std::shared_ptr<SoundManager>*)duk_to_pointer(context, 0);
		Number globalVolume = duk_to_number(context, 1);
		(*inst)->setGlobalVolume(globalVolume);
		return 0;
	}

	duk_ret_t Polycode_String(duk_context *context) {
		std::shared_ptr<String> *inst = new std::shared_ptr<String>;
		(*inst) = std::make_shared<String>();
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_String__get_contents(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		std::shared_ptr<string> *retInst = new std::shared_ptr<string>;
		*retInst = std::make_shared<string>();
		*(*retInst) = (*inst)->contents;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String__set_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		inst->contents = *(string*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String__get_w_contents(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		std::shared_ptr<wstring> *retInst = new std::shared_ptr<wstring>;
		*retInst = std::make_shared<wstring>();
		*(*retInst) = (*inst)->w_contents;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String__set_w_contents(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, 0);
		inst->w_contents = *(wstring*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String__delete(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_String_size(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->size();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_length(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->length();
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_substr(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		size_t n = *(size_t*)duk_to_pointer(context, 2);
		duk_push_string(context, (*inst)->substr(pos,n).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_rfind(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->rfind(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->find(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find_last_of(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->find_last_of(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find_first_of(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->find_first_of(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_find_first_not_of(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String str = duk_to_string(context, 1);
		size_t pos = *(size_t*)duk_to_pointer(context, 2);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->find_first_not_of(str,pos);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_toLowerCase(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->toLowerCase().c_str());
		return 1;
	}

	duk_ret_t Polycode_String_toUpperCase(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_string(context, (*inst)->toUpperCase().c_str());
		return 1;
	}

	duk_ret_t Polycode_String_split(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String delim = duk_to_string(context, 1);
		return 0;
	}

	duk_ret_t Polycode_String_replace(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		String what = duk_to_string(context, 1);
		String withWhat = duk_to_string(context, 2);
		duk_push_string(context, (*inst)->replace(what,withWhat).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_NumberToString(duk_context *context) {
		Number value = duk_to_number(context, 0);
		int precision = duk_to_int(context, 1);
		duk_push_string(context, String::NumberToString(value,precision).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_toNumber(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->toNumber());
		return 1;
	}

	duk_ret_t Polycode_String_toInteger(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->toInteger());
		return 1;
	}

	duk_ret_t Polycode_String_IntToString(duk_context *context) {
		int value = duk_to_int(context, 0);
		duk_push_string(context, String::IntToString(value).c_str());
		return 1;
	}

	duk_ret_t Polycode_String_append(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		char c = *(char*)duk_to_pointer(context, 1);
		(*inst)->append(c);
		return 0;
	}

	duk_ret_t Polycode_String_getDataSizeWithEncoding(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		std::shared_ptr<size_t> *retInst = new std::shared_ptr<size_t>;
		*(*retInst) = (*inst)->getDataSizeWithEncoding(encoding);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_String_isNumber(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isNumber());
		return 1;
	}

	duk_ret_t Polycode_String_isInteger(duk_context *context) {
		std::shared_ptr<String> *inst = (std::shared_ptr<String>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->isInteger());
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer(duk_context *context) {
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		bool attachDepthBuffer = duk_to_boolean(context, 2);
		bool floatingPoint = duk_to_boolean(context, 3);
		std::shared_ptr<RenderBuffer> *inst = new std::shared_ptr<RenderBuffer>;
		(*inst) = std::make_shared<RenderBuffer>(width,height,attachDepthBuffer,floatingPoint);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__get_platformData(duk_context *context) {
		std::shared_ptr<RenderBuffer> *inst = (std::shared_ptr<RenderBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<RendererPlatformData> *retInst = new std::shared_ptr<RendererPlatformData>;
		*retInst = std::make_shared<RendererPlatformData>();
		*(*retInst) = (*inst)->platformData;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__set_platformData(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->platformData = *(RendererPlatformData*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer__get_depthBufferPlatformData(duk_context *context) {
		std::shared_ptr<RenderBuffer> *inst = (std::shared_ptr<RenderBuffer>*)duk_to_pointer(context, 0);
		std::shared_ptr<RendererPlatformData> *retInst = new std::shared_ptr<RendererPlatformData>;
		*retInst = std::make_shared<RendererPlatformData>();
		*(*retInst) = (*inst)->depthBufferPlatformData;
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer__set_depthBufferPlatformData(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->depthBufferPlatformData = *(RendererPlatformData*)duk_to_pointer(context, 1);
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer__delete(duk_context *context) {
		std::shared_ptr<RenderBuffer> *inst = (std::shared_ptr<RenderBuffer>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer_getWidth(duk_context *context) {
		std::shared_ptr<RenderBuffer> *inst = (std::shared_ptr<RenderBuffer>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getWidth());
		return 1;
	}

	duk_ret_t Polycode_RenderBuffer_getHeight(duk_context *context) {
		std::shared_ptr<RenderBuffer> *inst = (std::shared_ptr<RenderBuffer>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Texture__get_clamp(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->clamp);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_clamp(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->clamp = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_type(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->type);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_type(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->type = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_filteringMode(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->filteringMode);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_filteringMode(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->filteringMode = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_createMipmaps(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->createMipmaps);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_createMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->createMipmaps = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_anisotropy(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->anisotropy);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_anisotropy(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->anisotropy = duk_to_int(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_framebufferTexture(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->framebufferTexture);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_framebufferTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->framebufferTexture = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__get_depthTexture(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->depthTexture);
		return 1;
	}

	duk_ret_t Polycode_Texture__set_depthTexture(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, 0);
		inst->depthTexture = duk_to_boolean(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Texture__delete(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Texture_getWidth(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getWidth());
		return 1;
	}

	duk_ret_t Polycode_Texture_getHeight(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_int(context, (*inst)->getHeight());
		return 1;
	}

	duk_ret_t Polycode_Texture_setCreateMipmaps(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		bool createMipmapsIn = duk_to_boolean(context, 1);
		(*inst)->setCreateMipmaps(createMipmapsIn);
		return 0;
	}

	duk_ret_t Polycode_Texture_getCreateMipmaps(duk_context *context) {
		std::shared_ptr<Texture> *inst = (std::shared_ptr<Texture>*)duk_to_pointer(context, 0);
		duk_push_boolean(context, (*inst)->getCreateMipmaps());
		return 1;
	}

	duk_ret_t Polycode_Vector2(duk_context *context) {
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		std::shared_ptr<Vector2> *inst = new std::shared_ptr<Vector2>;
		(*inst) = std::make_shared<Vector2>(x,y);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Vector2__get_x(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->x);
		return 1;
	}

	duk_ret_t Polycode_Vector2__set_x(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector2__get_y(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->y);
		return 1;
	}

	duk_ret_t Polycode_Vector2__set_y(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector2__delete(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector2_set(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		(*inst)->set(x,y);
		return 0;
	}

	duk_ret_t Polycode_Vector2_distance(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->distance(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_length(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->length());
		return 1;
	}

	duk_ret_t Polycode_Vector2_dot(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		Vector2 u = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->dot(u));
		return 1;
	}

	duk_ret_t Polycode_Vector2_crossProduct(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->crossProduct(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_angle(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->angle(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector2_Normalize(duk_context *context) {
		std::shared_ptr<Vector2> *inst = (std::shared_ptr<Vector2>*)duk_to_pointer(context, 0);
		(*inst)->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector3(duk_context *context) {
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		std::shared_ptr<Vector3> *inst = new std::shared_ptr<Vector3>;
		(*inst) = std::make_shared<Vector3>(x,y,z);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Vector3__get_x(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->x);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_x(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__get_y(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->y);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_y(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__get_z(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->z);
		return 1;
	}

	duk_ret_t Polycode_Vector3__set_z(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector3__delete(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector3_set(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		(*inst)->set(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Vector3_distance(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->distance(vec2));
		return 1;
	}

	duk_ret_t Polycode_Vector3_angleBetween(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Vector3 dest = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->angleBetween(dest));
		return 1;
	}

	duk_ret_t Polycode_Vector3_length(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->length());
		return 1;
	}

	duk_ret_t Polycode_Vector3_lengthSquared(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->lengthSquared());
		return 1;
	}

	duk_ret_t Polycode_Vector3_setLength(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Number newLength = duk_to_number(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->setLength(newLength);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Vector3_dot(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Vector3 u = *(Vector3*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->dot(u));
		return 1;
	}

	duk_ret_t Polycode_Vector3_crossProduct(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 1);
		std::shared_ptr<Vector3> *retInst = new std::shared_ptr<Vector3>;
		*(*retInst) = (*inst)->crossProduct(vec2);
		duk_push_pointer(context, (void*)retInst);
		return 1;
	}

	duk_ret_t Polycode_Vector3_Normalize(duk_context *context) {
		std::shared_ptr<Vector3> *inst = (std::shared_ptr<Vector3>*)duk_to_pointer(context, 0);
		(*inst)->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector4(duk_context *context) {
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		Number w = duk_to_number(context, 3);
		std::shared_ptr<Vector4> *inst = new std::shared_ptr<Vector4>;
		(*inst) = std::make_shared<Vector4>(x,y,z,w);
		duk_push_pointer(context, (void*)inst);
		return 1;
	}

	duk_ret_t Polycode_Vector4__get_x(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->x);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_x(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->x = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_y(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->y);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_y(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->y = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_z(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->z);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_z(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->z = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__get_w(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		duk_push_number(context, (*inst)->w);
		return 1;
	}

	duk_ret_t Polycode_Vector4__set_w(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, 0);
		inst->w = duk_to_number(context, 1);
		return 0;
	}

	duk_ret_t Polycode_Vector4__delete(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		delete inst;
		return 0;
	}

	duk_ret_t Polycode_Vector4_set(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		Number w = duk_to_number(context, 4);
		(*inst)->set(x,y,z,w);
		return 0;
	}

	duk_ret_t Polycode_Vector4_dot(duk_context *context) {
		std::shared_ptr<Vector4> *inst = (std::shared_ptr<Vector4>*)duk_to_pointer(context, 0);
		Vector4 u = *(Vector4*)duk_to_pointer(context, 1);
		duk_push_number(context, (*inst)->dot(u));
		return 1;
	}



}
