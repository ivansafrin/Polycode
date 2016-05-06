#pragma once

extern "C" {
	#include <stdio.h>
 	#include "duktape.h"
} 



using namespace std;
namespace Polycode {

	duk_ret_t Polycode_BezierCurve_getControlPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getControlPoint(index);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getNumControlPoints(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		inst->getNumControlPoints();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number p1x = duk_to_number(context, 0);
		Number p1y = duk_to_number(context, 1);
		Number p1z = duk_to_number(context, 2);
		Number p2x = duk_to_number(context, 3);
		Number p2y = duk_to_number(context, 4);
		Number p2z = duk_to_number(context, 5);
		Number p3x = duk_to_number(context, 6);
		Number p3y = duk_to_number(context, 7);
		Number p3z = duk_to_number(context, 8);
		inst->addControlPoint(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3dWithHandles(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number p1x = duk_to_number(context, 0);
		Number p1y = duk_to_number(context, 1);
		Number p1z = duk_to_number(context, 2);
		Number p2x = duk_to_number(context, 3);
		Number p2y = duk_to_number(context, 4);
		Number p2z = duk_to_number(context, 5);
		Number p3x = duk_to_number(context, 6);
		Number p3y = duk_to_number(context, 7);
		Number p3z = duk_to_number(context, 8);
		inst->addControlPoint3dWithHandles(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint3d(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->addControlPoint3d(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2dWithHandles(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number p1x = duk_to_number(context, 0);
		Number p1y = duk_to_number(context, 1);
		Number p2x = duk_to_number(context, 2);
		Number p2y = duk_to_number(context, 3);
		Number p3x = duk_to_number(context, 4);
		Number p3y = duk_to_number(context, 5);
		inst->addControlPoint2dWithHandles(p1x,p1y,p2x,p2y,p3x,p3y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_addControlPoint2d(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		inst->addControlPoint2d(x,y);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getPointAt(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number a = duk_to_number(context, 0);
		inst->getPointAt(a);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getPointBetween(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number a = duk_to_number(context, 0);
		BezierPoint* bp1 = (BezierPoint*)duk_to_pointer(context, 1);
		BezierPoint* bp2 = (BezierPoint*)duk_to_pointer(context, 2);
		inst->getPointBetween(a,bp1,bp2);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_clearControlPoints(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		inst->clearControlPoints();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getYValueAtX(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->getYValueAtX(x);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_getTValueAtX(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->getTValueAtX(x);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_removePoint(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		BezierPoint* point = (BezierPoint*)duk_to_pointer(context, 0);
		inst->removePoint(point);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_setHeightCacheResolution(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		Number resolution = duk_to_number(context, 0);
		inst->setHeightCacheResolution(resolution);
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_rebuildHeightCache(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		inst->rebuildHeightCache();
		return 0;
	}

	duk_ret_t Polycode_BezierCurve_recalculateDistances(duk_context *context) {
		BezierCurve *inst = (BezierCurve*)duk_to_pointer(context, -1);
		inst->recalculateDistances();
		return 0;
	}

	duk_ret_t Polycode_Bone_getName(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_Bone_setParentBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Bone* bone = (Bone*)duk_to_pointer(context, 0);
		inst->setParentBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_addChildBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Bone* bone = (Bone*)duk_to_pointer(context, 0);
		inst->addChildBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Bone_getParentBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getParentBone();
		return 0;
	}

	duk_ret_t Polycode_Bone_getNumChildBones(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getNumChildBones();
		return 0;
	}

	duk_ret_t Polycode_Bone_getChildBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getChildBone(index);
		return 0;
	}

	duk_ret_t Polycode_Bone_getBoneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getBoneMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_setBoneMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setBoneMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getRestMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_getFullRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getFullRestMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_getParentRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getParentRestMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_getFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getFinalMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_setRestMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setRestMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_setBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setBaseMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Bone_getBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getBaseMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_getFullBaseMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->getFullBaseMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_rebuildFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->rebuildFinalMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_buildFinalMatrix(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		inst->buildFinalMatrix();
		return 0;
	}

	duk_ret_t Polycode_Bone_intializeBone(duk_context *context) {
		Bone *inst = (Bone*)duk_to_pointer(context, -1);
		Vector3 basePosition = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 baseScale = *(Vector3*)duk_to_pointer(context, 1);
		Quaternion baseRotation = *(Quaternion*)duk_to_pointer(context, 2);
		Vector3 restPosition = *(Vector3*)duk_to_pointer(context, 3);
		Vector3 restScale = *(Vector3*)duk_to_pointer(context, 4);
		Quaternion restRotation = *(Quaternion*)duk_to_pointer(context, 5);
		inst->intializeBone(basePosition,baseScale,baseRotation,restPosition,restScale,restRotation);
		return 0;
	}

	duk_ret_t Polycode_Camera_buildFrustumPlanes(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->buildFrustumPlanes();
		return 0;
	}

	duk_ret_t Polycode_Camera_isSphereInFrustum(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Vector3 pos = *(Vector3*)duk_to_pointer(context, 0);
		Number fRadius = duk_to_number(context, 1);
		inst->isSphereInFrustum(pos,fRadius);
		return 0;
	}

	duk_ret_t Polycode_Camera_isAABBInFrustum(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		AABB aabb = *(AABB*)duk_to_pointer(context, 0);
		inst->isAABBInFrustum(aabb);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		bool mode = duk_to_boolean(context, 0);
		inst->setOrthoMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSize(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Number orthoSizeX = duk_to_number(context, 0);
		Number orthoSizeY = duk_to_number(context, 1);
		inst->setOrthoSize(orthoSizeX,orthoSizeY);
		return 0;
	}

	duk_ret_t Polycode_Camera_setFrustumMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Number left = duk_to_number(context, 0);
		Number right = duk_to_number(context, 1);
		Number bottom = duk_to_number(context, 2);
		Number top = duk_to_number(context, 3);
		Number front = duk_to_number(context, 4);
		Number back = duk_to_number(context, 5);
		inst->setFrustumMode(left,right,bottom,top,front,back);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getOrthoMode();
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeX(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getOrthoSizeX();
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeY(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getOrthoSizeY();
		return 0;
	}

	duk_ret_t Polycode_Camera_setFOV(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Number fov = duk_to_number(context, 0);
		inst->setFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_Camera_getFOV(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getFOV();
		return 0;
	}

	duk_ret_t Polycode_Camera_setClippingPlanes(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Number nearClipPlane = duk_to_number(context, 0);
		Number farClipPlane = duk_to_number(context, 1);
		inst->setClippingPlanes(nearClipPlane,farClipPlane);
		return 0;
	}

	duk_ret_t Polycode_Camera_getNearClippingPlane(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getNearClippingPlane();
		return 0;
	}

	duk_ret_t Polycode_Camera_getFarClippingPlane(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getFarClippingPlane();
		return 0;
	}

	duk_ret_t Polycode_Camera_setParentScene(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Scene* parentScene = (Scene*)duk_to_pointer(context, 0);
		inst->setParentScene(parentScene);
		return 0;
	}

	duk_ret_t Polycode_Camera_getParentScene(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getParentScene();
		return 0;
	}

	duk_ret_t Polycode_Camera_createProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->createProjectionMatrix();
		return 0;
	}

	duk_ret_t Polycode_Camera_hasFilterShader(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->hasFilterShader();
		return 0;
	}

	duk_ret_t Polycode_Camera_drawFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		RenderBuffer* targetBuffer = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->drawFilter(targetBuffer);
		return 0;
	}

	duk_ret_t Polycode_Camera_setPostFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Material* material = (Material*)duk_to_pointer(context, 0);
		inst->setPostFilter(material);
		return 0;
	}

	duk_ret_t Polycode_Camera_setPostFilterByName(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		String shaderName = duk_to_string(context, 0);
		inst->setPostFilterByName(shaderName);
		return 0;
	}

	duk_ret_t Polycode_Camera_removePostFilter(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->removePostFilter();
		return 0;
	}

	duk_ret_t Polycode_Camera_getScreenShaderMaterial(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getScreenShaderMaterial();
		return 0;
	}

	duk_ret_t Polycode_Camera_Clone(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Camera_applyClone(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Camera_getProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getProjectionMatrix();
		return 0;
	}

	duk_ret_t Polycode_Camera_setCustomProjectionMatrix(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setCustomProjectionMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Camera_getViewport(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getViewport();
		return 0;
	}

	duk_ret_t Polycode_Camera_setViewport(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Rectangle viewport = *(Rectangle*)duk_to_pointer(context, 0);
		inst->setViewport(viewport);
		return 0;
	}

	duk_ret_t Polycode_Camera_setOrthoSizeMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		int orthoSizeMode = duk_to_int(context, 0);
		inst->setOrthoSizeMode(orthoSizeMode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getOrthoSizeMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getOrthoSizeMode();
		return 0;
	}

	duk_ret_t Polycode_Camera_setProjectionMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		int mode = duk_to_int(context, 0);
		inst->setProjectionMode(mode);
		return 0;
	}

	duk_ret_t Polycode_Camera_getProjectionMode(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getProjectionMode();
		return 0;
	}

	duk_ret_t Polycode_Camera_projectRayFrom2DCoordinate(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		Vector2 coordinate = *(Vector2*)duk_to_pointer(context, 0);
		Rectangle viewport = *(Rectangle*)duk_to_pointer(context, 1);
		inst->projectRayFrom2DCoordinate(coordinate,viewport);
		return 0;
	}

	duk_ret_t Polycode_Camera_renderFullScreenQuad(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		int shaderPass = duk_to_int(context, 1);
		inst->renderFullScreenQuad(drawBuffer,shaderPass);
		return 0;
	}

	duk_ret_t Polycode_Camera_getShaderPass(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderPass(index);
		return 0;
	}

	duk_ret_t Polycode_Camera_getNumShaderPasses(duk_context *context) {
		Camera *inst = (Camera*)duk_to_pointer(context, -1);
		inst->getNumShaderPasses();
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHex(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		int hex = duk_to_int(context, 0);
		inst->setColorHex(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGB(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		int hex = duk_to_int(context, 0);
		inst->setColorHexRGB(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexFromString(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		String hex = duk_to_string(context, 0);
		inst->setColorHexFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHexRGBFromString(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		String hex = duk_to_string(context, 0);
		inst->setColorHexRGBFromString(hex);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorHSV(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		Number h = duk_to_number(context, 0);
		Number s = duk_to_number(context, 1);
		Number v = duk_to_number(context, 2);
		inst->setColorHSV(h,s,v);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGBA(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		int r = duk_to_int(context, 0);
		int g = duk_to_int(context, 1);
		int b = duk_to_int(context, 2);
		int a = duk_to_int(context, 3);
		inst->setColorRGBA(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_setColorRGB(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		int r = duk_to_int(context, 0);
		int g = duk_to_int(context, 1);
		int b = duk_to_int(context, 2);
		inst->setColorRGB(r,g,b);
		return 0;
	}

	duk_ret_t Polycode_Color_setColor(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Color_blendColor(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		Color c2 = *(Color*)duk_to_pointer(context, 0);
		int mode = duk_to_int(context, 1);
		Number amount = duk_to_number(context, 2);
		Color c3 = *(Color*)duk_to_pointer(context, 3);
		inst->blendColor(c2,mode,amount,c3);
		return 0;
	}

	duk_ret_t Polycode_Color_Random(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->Random();
		return 0;
	}

	duk_ret_t Polycode_Color_getBrightness(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->getBrightness();
		return 0;
	}

	duk_ret_t Polycode_Color_getHue(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->getHue();
		return 0;
	}

	duk_ret_t Polycode_Color_getSaturation(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->getSaturation();
		return 0;
	}

	duk_ret_t Polycode_Color_getValue(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->getValue();
		return 0;
	}

	duk_ret_t Polycode_Color_getUint(duk_context *context) {
		Color *inst = (Color*)duk_to_pointer(context, -1);
		inst->getUint();
		return 0;
	}

	duk_ret_t Polycode_Config_loadConfig(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_saveConfig(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->saveConfig(configNamespace,fileName);
		return 0;
	}

	duk_ret_t Polycode_Config_getEntry(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		inst->getEntry(configNamespace,key);
		return 0;
	}

	duk_ret_t Polycode_Config_setStringValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		String value = duk_to_string(context, 2);
		inst->setStringValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_setNumericValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		Number value = duk_to_number(context, 2);
		inst->setNumericValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getNumericValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		inst->getNumericValue(configNamespace,key);
		return 0;
	}

	duk_ret_t Polycode_Config_getStringValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		inst->getStringValue(configNamespace,key);
		return 0;
	}

	duk_ret_t Polycode_Config_setBoolValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		bool value = duk_to_boolean(context, 2);
		inst->setBoolValue(configNamespace,key,value);
		return 0;
	}

	duk_ret_t Polycode_Config_getBoolValue(duk_context *context) {
		Config *inst = (Config*)duk_to_pointer(context, -1);
		String configNamespace = duk_to_string(context, 0);
		String key = duk_to_string(context, 1);
		inst->getBoolValue(configNamespace,key);
		return 0;
	}

	duk_ret_t Polycode_Core_Update(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Core_Render(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_Core_fixedUpdate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Core_systemUpdate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->systemUpdate();
		return 0;
	}

	duk_ret_t Polycode_Core_updateAndRender(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->updateAndRender();
		return 0;
	}

	duk_ret_t Polycode_Core_enableMouse(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		bool newval = duk_to_boolean(context, 0);
		inst->enableMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_captureMouse(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		bool newval = duk_to_boolean(context, 0);
		inst->captureMouse(newval);
		return 0;
	}

	duk_ret_t Polycode_Core_setCursor(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		int cursorType = duk_to_int(context, 0);
		inst->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_Core_warpCursor(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		inst->warpCursor(x,y);
		return 0;
	}

	duk_ret_t Polycode_Core_createThread(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		Threaded* target = (Threaded*)duk_to_pointer(context, 0);
		inst->createThread(target);
		return 0;
	}

	duk_ret_t Polycode_Core_lockMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		CoreMutex* mutex = (CoreMutex*)duk_to_pointer(context, 0);
		inst->lockMutex(mutex);
		return 0;
	}

	duk_ret_t Polycode_Core_unlockMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		CoreMutex* mutex = (CoreMutex*)duk_to_pointer(context, 0);
		inst->unlockMutex(mutex);
		return 0;
	}

	duk_ret_t Polycode_Core_createMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->createMutex();
		return 0;
	}

	duk_ret_t Polycode_Core_copyStringToClipboard(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		inst->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_Core_getClipboardString(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getClipboardString();
		return 0;
	}

	duk_ret_t Polycode_Core_getServices(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getServices();
		return 0;
	}

	duk_ret_t Polycode_Core_getFPS(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getFPS();
		return 0;
	}

	duk_ret_t Polycode_Core_Shutdown(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->Shutdown();
		return 0;
	}

	duk_ret_t Polycode_Core_isFullscreen(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->isFullscreen();
		return 0;
	}

	duk_ret_t Polycode_Core_getAALevel(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getAALevel();
		return 0;
	}

	duk_ret_t Polycode_Core_getInput(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getInput();
		return 0;
	}

	duk_ret_t Polycode_Core_getXRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getXRes();
		return 0;
	}

	duk_ret_t Polycode_Core_getYRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getYRes();
		return 0;
	}

	duk_ret_t Polycode_Core_getBackingXRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getBackingXRes();
		return 0;
	}

	duk_ret_t Polycode_Core_getBackingYRes(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getBackingYRes();
		return 0;
	}

	duk_ret_t Polycode_Core_getScreenWidth(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getScreenWidth();
		return 0;
	}

	duk_ret_t Polycode_Core_getScreenHeight(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getScreenHeight();
		return 0;
	}

	duk_ret_t Polycode_Core_createFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String folderPath = duk_to_string(context, 0);
		inst->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_Core_copyDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		String destItemPath = duk_to_string(context, 1);
		inst->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_moveDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		String destItemPath = duk_to_string(context, 1);
		inst->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_removeDiskItem(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		inst->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_Core_openFolderPicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->openFolderPicker();
		return 0;
	}

	duk_ret_t Polycode_Core_setFramerate(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		int frameRate = duk_to_int(context, 0);
		int maxFixedCycles = duk_to_int(context, 1);
		inst->setFramerate(frameRate,maxFixedCycles);
		return 0;
	}

	duk_ret_t Polycode_Core_openFilePicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 0);
		bool allowMultiple = duk_to_boolean(context, 1);
		inst->openFilePicker(extensions,allowMultiple);
		return 0;
	}

	duk_ret_t Polycode_Core_saveFilePicker(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 0);
		inst->saveFilePicker(extensions);
		return 0;
	}

	duk_ret_t Polycode_Core_handleVideoModeChange(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}

	duk_ret_t Polycode_Core_flushRenderContext(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_prepareRenderContext(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->prepareRenderContext();
		return 0;
	}

	duk_ret_t Polycode_Core_openFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		String opts = duk_to_string(context, 1);
		inst->openFile(fileName,opts);
		return 0;
	}

	duk_ret_t Polycode_Core_closeFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		CoreFile* file = (CoreFile*)duk_to_pointer(context, 0);
		inst->closeFile(file);
		return 0;
	}

	duk_ret_t Polycode_Core_addFileSource(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String type = duk_to_string(context, 0);
		String source = duk_to_string(context, 1);
		inst->addFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_removeFileSource(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String type = duk_to_string(context, 0);
		String source = duk_to_string(context, 1);
		inst->removeFileSource(type,source);
		return 0;
	}

	duk_ret_t Polycode_Core_parseFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String pathString = duk_to_string(context, 0);
		bool showHidden = duk_to_boolean(context, 1);
		inst->parseFolder(pathString,showHidden);
		return 0;
	}

	duk_ret_t Polycode_Core_systemParseFolder(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String pathString = duk_to_string(context, 0);
		bool showHidden = duk_to_boolean(context, 1);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 2);
		inst->systemParseFolder(pathString,showHidden,targetVector);
		return 0;
	}

	duk_ret_t Polycode_Core_getResourcePathForFile(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->getResourcePathForFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_Core_setVideoMode(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		int xRes = duk_to_int(context, 0);
		int yRes = duk_to_int(context, 1);
		bool fullScreen = duk_to_boolean(context, 2);
		bool vSync = duk_to_boolean(context, 3);
		int aaLevel = duk_to_int(context, 4);
		int anisotropyLevel = duk_to_int(context, 5);
		bool retinaSupport = duk_to_boolean(context, 6);
		inst->setVideoMode(xRes,yRes,fullScreen,vSync,aaLevel,anisotropyLevel,retinaSupport);
		return 0;
	}

	duk_ret_t Polycode_Core_resizeTo(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		int xRes = duk_to_int(context, 0);
		int yRes = duk_to_int(context, 1);
		inst->resizeTo(xRes,yRes);
		return 0;
	}

	duk_ret_t Polycode_Core_doSleep(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->doSleep();
		return 0;
	}

	duk_ret_t Polycode_Core_openURL(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String url = duk_to_string(context, 0);
		inst->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_Core_getElapsed(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getElapsed();
		return 0;
	}

	duk_ret_t Polycode_Core_getTicks(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getTicks();
		return 0;
	}

	duk_ret_t Polycode_Core_getRefreshIntervalMs(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getRefreshIntervalMs();
		return 0;
	}

	duk_ret_t Polycode_Core_getTimeSleptMs(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getTimeSleptMs();
		return 0;
	}

	duk_ret_t Polycode_Core_getFixedTimestep(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getFixedTimestep();
		return 0;
	}

	duk_ret_t Polycode_Core_getTicksFloat(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getTicksFloat();
		return 0;
	}

	duk_ret_t Polycode_Core_setUserPointer(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		void* ptr = (void*)duk_to_pointer(context, 0);
		inst->setUserPointer(ptr);
		return 0;
	}

	duk_ret_t Polycode_Core_getUserPointer(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getUserPointer();
		return 0;
	}

	duk_ret_t Polycode_Core_executeExternalCommand(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		String command = duk_to_string(context, 0);
		String args = duk_to_string(context, 1);
		String inDirectory = duk_to_string(context, 2);
		inst->executeExternalCommand(command,args,inDirectory);
		return 0;
	}

	duk_ret_t Polycode_Core_getDefaultWorkingDirectory(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getDefaultWorkingDirectory();
		return 0;
	}

	duk_ret_t Polycode_Core_getUserHomeDirectory(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getUserHomeDirectory();
		return 0;
	}

	duk_ret_t Polycode_Core_makeApplicationMain(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->makeApplicationMain();
		return 0;
	}

	duk_ret_t Polycode_Core_getEventMutex(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		inst->getEventMutex();
		return 0;
	}

	duk_ret_t Polycode_Core_removeThread(duk_context *context) {
		Core *inst = (Core*)duk_to_pointer(context, -1);
		Threaded* thread = (Threaded*)duk_to_pointer(context, 0);
		inst->removeThread(thread);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_Render(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_systemUpdate(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->systemUpdate();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_setCursor(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		int cursorType = duk_to_int(context, 0);
		inst->setCursor(cursorType);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_createThread(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		Threaded* target = (Threaded*)duk_to_pointer(context, 0);
		inst->createThread(target);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_createMutex(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->createMutex();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_copyStringToClipboard(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		inst->copyStringToClipboard(str);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getClipboardString(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->getClipboardString();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_createFolder(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String folderPath = duk_to_string(context, 0);
		inst->createFolder(folderPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_copyDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		String destItemPath = duk_to_string(context, 1);
		inst->copyDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_moveDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		String destItemPath = duk_to_string(context, 1);
		inst->moveDiskItem(itemPath,destItemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_removeDiskItem(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String itemPath = duk_to_string(context, 0);
		inst->removeDiskItem(itemPath);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openFolderPicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->openFolderPicker();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openFilePicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 0);
		bool allowMultiple = duk_to_boolean(context, 1);
		inst->openFilePicker(extensions,allowMultiple);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_saveFilePicker(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*)duk_to_pointer(context, 0);
		inst->saveFilePicker(extensions);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_handleVideoModeChange(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*)duk_to_pointer(context, 0);
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_flushRenderContext(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->flushRenderContext();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_openURL(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String url = duk_to_string(context, 0);
		inst->openURL(url);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_getTicks(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		inst->getTicks();
		return 0;
	}

	duk_ret_t Polycode_DummyCore_executeExternalCommand(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String command = duk_to_string(context, 0);
		String args = duk_to_string(context, 1);
		String inDirectory = duk_to_string(context, 2);
		inst->executeExternalCommand(command,args,inDirectory);
		return 0;
	}

	duk_ret_t Polycode_DummyCore_systemParseFolder(duk_context *context) {
		DummyCore *inst = (DummyCore*)duk_to_pointer(context, -1);
		String pathString = duk_to_string(context, 0);
		bool showHidden = duk_to_boolean(context, 1);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*)duk_to_pointer(context, 2);
		inst->systemParseFolder(pathString,showHidden,targetVector);
		return 0;
	}

	duk_ret_t Polycode_CoreMutex_lock(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, -1);
		inst->lock();
		return 0;
	}

	duk_ret_t Polycode_CoreMutex_unlock(duk_context *context) {
		CoreMutex *inst = (CoreMutex*)duk_to_pointer(context, -1);
		inst->unlock();
		return 0;
	}

	duk_ret_t Polycode_OSFileEntry_init(duk_context *context) {
		OSFileEntry *inst = (OSFileEntry*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		String name = duk_to_string(context, 1);
		int type = duk_to_int(context, 2);
		inst->init(path,name,type);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		inst->getMousePosition();
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getKeyState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 0);
		inst->getKeyState(keyCode);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getJoystickButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int joystickIndex = duk_to_int(context, 0);
		int button = duk_to_int(context, 1);
		inst->getJoystickButtonState(joystickIndex,button);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getJoystickAxisValue(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int joystickIndex = duk_to_int(context, 0);
		int axis = duk_to_int(context, 1);
		inst->getJoystickAxisValue(joystickIndex,axis);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getMouseDelta(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		inst->getMouseDelta();
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getMouseButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int mouseButton = duk_to_int(context, 0);
		inst->getMouseButtonState(mouseButton);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getNumJoysticks(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		inst->getNumJoysticks();
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getJoystickInfoByIndex(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getJoystickInfoByIndex(index);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_getJoystickInfoByID(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int deviceID = duk_to_int(context, 0);
		inst->getJoystickInfoByID(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_addJoystick(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int deviceID = duk_to_int(context, 0);
		inst->addJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_removeJoystick(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int deviceID = duk_to_int(context, 0);
		inst->removeJoystick(deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickAxisMoved(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int axisID = duk_to_int(context, 0);
		Number value = duk_to_number(context, 1);
		int deviceID = duk_to_int(context, 2);
		inst->joystickAxisMoved(axisID,value,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonDown(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int buttonID = duk_to_int(context, 0);
		int deviceID = duk_to_int(context, 1);
		inst->joystickButtonDown(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_joystickButtonUp(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int buttonID = duk_to_int(context, 0);
		int deviceID = duk_to_int(context, 1);
		inst->joystickButtonUp(buttonID,deviceID);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelUp(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int ticks = duk_to_int(context, 0);
		inst->mouseWheelUp(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_mouseWheelDown(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int ticks = duk_to_int(context, 0);
		inst->mouseWheelDown(ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMouseButtonState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int mouseButton = duk_to_int(context, 0);
		bool state = duk_to_boolean(context, 1);
		int ticks = duk_to_int(context, 2);
		inst->setMouseButtonState(mouseButton,state,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setMousePosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		int ticks = duk_to_int(context, 2);
		inst->setMousePosition(x,y,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setKeyState(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		PolyKEY keyCode = (PolyKEY)duk_to_int(context, 0);
		wchar_t code = *(wchar_t*)duk_to_pointer(context, 1);
		bool newState = duk_to_boolean(context, 2);
		int ticks = duk_to_int(context, 3);
		inst->setKeyState(keyCode,code,newState,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_setDeltaPosition(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		inst->setDeltaPosition(x,y);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesBegan(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 0);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 1);
		int ticks = duk_to_int(context, 2);
		inst->touchesBegan(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesMoved(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 0);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 1);
		int ticks = duk_to_int(context, 2);
		inst->touchesMoved(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_touchesEnded(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		TouchInfo touch = *(TouchInfo*)duk_to_pointer(context, 0);
		vector<TouchInfo> touches = *(vector<TouchInfo>*)duk_to_pointer(context, 1);
		int ticks = duk_to_int(context, 2);
		inst->touchesEnded(touch,touches,ticks);
		return 0;
	}

	duk_ret_t Polycode_CoreInput_clearInput(duk_context *context) {
		CoreInput *inst = (CoreInput*)duk_to_pointer(context, -1);
		inst->clearInput();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_setRenderer(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 0);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getRenderer(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getRenderer();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_Update(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		int elapsed = duk_to_int(context, 0);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_fixedUpdate(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_Render(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		Rectangle viewport = *(Rectangle*)duk_to_pointer(context, 0);
		inst->Render(viewport);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_setCore(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		Core* core = (Core*)duk_to_pointer(context, 0);
		inst->setCore(core);
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getCore(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getCore();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getInput(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getInput();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getMaterialManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getMaterialManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getSceneManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getSceneManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getTimerManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getTimerManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getTweenManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getTweenManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getResourceManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getResourceManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getSoundManager(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getSoundManager();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getLogger(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getLogger();
		return 0;
	}

	duk_ret_t Polycode_CoreServices_getConfig(duk_context *context) {
		CoreServices *inst = (CoreServices*)duk_to_pointer(context, -1);
		inst->getConfig();
		return 0;
	}

	duk_ret_t Polycode_Data_loadFromFile(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadFromFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_Data_getAsString(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, -1);
		int encoding = duk_to_int(context, 0);
		inst->getAsString(encoding);
		return 0;
	}

	duk_ret_t Polycode_Data_setFromString(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		int encoding = duk_to_int(context, 1);
		inst->setFromString(str,encoding);
		return 0;
	}

	duk_ret_t Polycode_Data_saveToFile(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->saveToFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_Data_getData(duk_context *context) {
		Data *inst = (Data*)duk_to_pointer(context, -1);
		inst->getData();
		return 0;
	}

	duk_ret_t Polycode_Entity_initEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->initEntity();
		return 0;
	}

	duk_ret_t Polycode_Entity_Render(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_Entity_Update(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Entity_fixedUpdate(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Entity_transformAndRender(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Rectangle* parentScissorBox = (Rectangle*)duk_to_pointer(context, 1);
		inst->transformAndRender(drawBuffer,parentScissorBox);
		return 0;
	}

	duk_ret_t Polycode_Entity_renderChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		Rectangle* parentScissorBox = (Rectangle*)duk_to_pointer(context, 1);
		inst->renderChildren(buffer,parentScissorBox);
		return 0;
	}

	duk_ret_t Polycode_Entity_Clone(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Entity_applyClone(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Entity_dirtyMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->dirtyMatrix(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_rebuildTransformMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->rebuildTransformMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_updateEntityMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->updateEntityMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getTransformMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getTransformMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getConcatenatedMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getConcatenatedMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getConcatenatedMatrixRelativeTo(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* relativeEntity = (Entity*)duk_to_pointer(context, 0);
		inst->getConcatenatedMatrixRelativeTo(relativeEntity);
		return 0;
	}

	duk_ret_t Polycode_Entity_getAnchorAdjustedMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getAnchorAdjustedMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_getConcatenatedRollMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getConcatenatedRollMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_setTransformByMatrixPure(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setTransformByMatrixPure(matrix);
		return 0;
	}

	duk_ret_t Polycode_Entity_getLookAtMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 1);
		inst->getLookAtMatrix(loc,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_addChild(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* newChild = (Entity*)duk_to_pointer(context, 0);
		inst->addChild(newChild);
		return 0;
	}

	duk_ret_t Polycode_Entity_removeChild(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* entityToRemove = (Entity*)duk_to_pointer(context, 0);
		inst->removeChild(entityToRemove);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* child = (Entity*)duk_to_pointer(context, 0);
		inst->moveChildUp(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* child = (Entity*)duk_to_pointer(context, 0);
		inst->moveChildDown(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildTop(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* child = (Entity*)duk_to_pointer(context, 0);
		inst->moveChildTop(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_moveChildBottom(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* child = (Entity*)duk_to_pointer(context, 0);
		inst->moveChildBottom(child);
		return 0;
	}

	duk_ret_t Polycode_Entity_setParentEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* entity = (Entity*)duk_to_pointer(context, 0);
		inst->setParentEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Entity_getParentEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getParentEntity();
		return 0;
	}

	duk_ret_t Polycode_Entity_getNumChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getNumChildren();
		return 0;
	}

	duk_ret_t Polycode_Entity_getChildAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getChildAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Entity_setOwnsChildrenRecursive(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setOwnsChildrenRecursive(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getPosition();
		return 0;
	}

	duk_ret_t Polycode_Entity_getPosition2D(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getPosition2D();
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCombinedPosition();
		return 0;
	}

	duk_ret_t Polycode_Entity_setPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->setPositionX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number y = duk_to_number(context, 0);
		inst->setPositionY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_Translate(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPositionZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number z = duk_to_number(context, 0);
		inst->setPositionZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->setScaleX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number y = duk_to_number(context, 0);
		inst->setScaleY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScaleZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number z = duk_to_number(context, 0);
		inst->setScaleZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_Scale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->Scale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->setScale(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCompoundScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCompoundScale();
		return 0;
	}

	duk_ret_t Polycode_Entity_getScale(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getScale();
		return 0;
	}

	duk_ret_t Polycode_Entity_getRotationEuler(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getRotationEuler();
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCombinedPitch();
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCombinedYaw();
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCombinedRoll();
		return 0;
	}

	duk_ret_t Polycode_Entity_rebuildRotation(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->rebuildRotation();
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationEuler(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Vector3 rotation = *(Vector3*)duk_to_pointer(context, 0);
		inst->setRotationEuler(rotation);
		return 0;
	}

	duk_ret_t Polycode_Entity_setPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number pitch = duk_to_number(context, 0);
		inst->setPitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_setYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number yaw = duk_to_number(context, 0);
		inst->setYaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number roll = duk_to_number(context, 0);
		inst->setRoll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Roll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number roll = duk_to_number(context, 0);
		inst->Roll(roll);
		return 0;
	}

	duk_ret_t Polycode_Entity_Yaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number yaw = duk_to_number(context, 0);
		inst->Yaw(yaw);
		return 0;
	}

	duk_ret_t Polycode_Entity_Pitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number pitch = duk_to_number(context, 0);
		inst->Pitch(pitch);
		return 0;
	}

	duk_ret_t Polycode_Entity_getPitch(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getPitch();
		return 0;
	}

	duk_ret_t Polycode_Entity_getYaw(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getYaw();
		return 0;
	}

	duk_ret_t Polycode_Entity_getRoll(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getRoll();
		return 0;
	}

	duk_ret_t Polycode_Entity_getWidth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getWidth();
		return 0;
	}

	duk_ret_t Polycode_Entity_getHeight(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getHeight();
		return 0;
	}

	duk_ret_t Polycode_Entity_getDepth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getDepth();
		return 0;
	}

	duk_ret_t Polycode_Entity_setWidth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number width = duk_to_number(context, 0);
		inst->setWidth(width);
		return 0;
	}

	duk_ret_t Polycode_Entity_setHeight(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number height = duk_to_number(context, 0);
		inst->setHeight(height);
		return 0;
	}

	duk_ret_t Polycode_Entity_setDepth(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number depth = duk_to_number(context, 0);
		inst->setDepth(depth);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->setRotationQuat(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setRotationByQuaternion(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Quaternion quaternion = *(Quaternion*)duk_to_pointer(context, 0);
		inst->setRotationByQuaternion(quaternion);
		return 0;
	}

	duk_ret_t Polycode_Entity_getRotationQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getRotationQuat();
		return 0;
	}

	duk_ret_t Polycode_Entity_getConcatenatedQuat(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getConcatenatedQuat();
		return 0;
	}

	duk_ret_t Polycode_Entity_lookAt(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Vector3 loc = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 1);
		inst->lookAt(loc,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_lookAtEntity(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Entity* entity = (Entity*)duk_to_pointer(context, 0);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 1);
		inst->lookAtEntity(entity,upVector);
		return 0;
	}

	duk_ret_t Polycode_Entity_getCombinedColor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getCombinedColor();
		return 0;
	}

	duk_ret_t Polycode_Entity_setColor(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->setColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setColorInt(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		int r = duk_to_int(context, 0);
		int g = duk_to_int(context, 1);
		int b = duk_to_int(context, 2);
		int a = duk_to_int(context, 3);
		inst->setColorInt(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Entity_setAnchorPoint(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Vector3 anchorPoint = *(Vector3*)duk_to_pointer(context, 0);
		inst->setAnchorPoint(anchorPoint);
		return 0;
	}

	duk_ret_t Polycode_Entity_getAnchorPoint(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getAnchorPoint();
		return 0;
	}

	duk_ret_t Polycode_Entity_onMouseDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		int timestamp = duk_to_int(context, 2);
		inst->onMouseDown(ray,mouseButton,timestamp);
		return 0;
	}

	duk_ret_t Polycode_Entity_onMouseUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		int mouseButton = duk_to_int(context, 1);
		int timestamp = duk_to_int(context, 2);
		inst->onMouseUp(ray,mouseButton,timestamp);
		return 0;
	}

	duk_ret_t Polycode_Entity_onMouseMove(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		int timestamp = duk_to_int(context, 1);
		inst->onMouseMove(ray,timestamp);
		return 0;
	}

	duk_ret_t Polycode_Entity_onMouseWheelUp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		int timestamp = duk_to_int(context, 1);
		inst->onMouseWheelUp(ray,timestamp);
		return 0;
	}

	duk_ret_t Polycode_Entity_onMouseWheelDown(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		int timestamp = duk_to_int(context, 1);
		inst->onMouseWheelDown(ray,timestamp);
		return 0;
	}

	duk_ret_t Polycode_Entity_setDepthOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setDepthOnly(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getDepthOnly(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getDepthOnly();
		return 0;
	}

	duk_ret_t Polycode_Entity_setUserData(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		void* userData = (void*)duk_to_pointer(context, 0);
		inst->setUserData(userData);
		return 0;
	}

	duk_ret_t Polycode_Entity_getUserData(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getUserData();
		return 0;
	}

	duk_ret_t Polycode_Entity_setBlendingMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		int newBlendingMode = duk_to_int(context, 0);
		inst->setBlendingMode(newBlendingMode);
		return 0;
	}

	duk_ret_t Polycode_Entity_getBlendingMode(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getBlendingMode();
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntityById(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String id = duk_to_string(context, 0);
		bool recursive = duk_to_boolean(context, 1);
		inst->getEntityById(id,recursive);
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntitiesByTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String tag = duk_to_string(context, 0);
		bool recursive = duk_to_boolean(context, 1);
		inst->getEntitiesByTag(tag,recursive);
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntitiesByLayerID(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		char layerID = *(char*)duk_to_pointer(context, 0);
		bool recursive = duk_to_boolean(context, 1);
		inst->getEntitiesByLayerID(layerID,recursive);
		return 0;
	}

	duk_ret_t Polycode_Entity_getEntityProp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String propName = duk_to_string(context, 0);
		inst->getEntityProp(propName);
		return 0;
	}

	duk_ret_t Polycode_Entity_setEntityProp(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String propName = duk_to_string(context, 0);
		String propValue = duk_to_string(context, 1);
		inst->setEntityProp(propName,propValue);
		return 0;
	}

	duk_ret_t Polycode_Entity_setInverseY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setInverseY(val);
		return 0;
	}

	duk_ret_t Polycode_Entity_getInverseY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getInverseY();
		return 0;
	}

	duk_ret_t Polycode_Entity_doUpdates(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->doUpdates();
		return 0;
	}

	duk_ret_t Polycode_Entity_doFixedUpdates(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->doFixedUpdates();
		return 0;
	}

	duk_ret_t Polycode_Entity_buildPositionMatrix(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->buildPositionMatrix();
		return 0;
	}

	duk_ret_t Polycode_Entity_setRenderer(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 0);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_Entity_customHitDetection(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		inst->customHitDetection(ray);
		return 0;
	}

	duk_ret_t Polycode_Entity_getNumTags(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getNumTags();
		return 0;
	}

	duk_ret_t Polycode_Entity_getTagAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getTagAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Entity_hasTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String tag = duk_to_string(context, 0);
		inst->hasTag(tag);
		return 0;
	}

	duk_ret_t Polycode_Entity_clearTags(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->clearTags();
		return 0;
	}

	duk_ret_t Polycode_Entity_addTag(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		String tag = duk_to_string(context, 0);
		inst->addTag(tag);
		return 0;
	}

	duk_ret_t Polycode_Entity_getScreenPosition(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Matrix4 projectionMatrix = *(Matrix4*)duk_to_pointer(context, 0);
		Matrix4 cameraMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Rectangle viewport = *(Rectangle*)duk_to_pointer(context, 2);
		inst->getScreenPosition(projectionMatrix,cameraMatrix,viewport);
		return 0;
	}

	duk_ret_t Polycode_Entity_recalculateAABBAllChildren(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->recalculateAABBAllChildren();
		return 0;
	}

	duk_ret_t Polycode_Entity_recalculateAABB(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->recalculateAABB();
		return 0;
	}

	duk_ret_t Polycode_Entity_getWorldAABB(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getWorldAABB();
		return 0;
	}

	duk_ret_t Polycode_Entity_getLocalBoundingBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getLocalBoundingBox();
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBox(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 0);
		inst->setLocalBoundingBox(box);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxX(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->setLocalBoundingBoxX(x);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxY(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number y = duk_to_number(context, 0);
		inst->setLocalBoundingBoxY(y);
		return 0;
	}

	duk_ret_t Polycode_Entity_setLocalBoundingBoxZ(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Number z = duk_to_number(context, 0);
		inst->setLocalBoundingBoxZ(z);
		return 0;
	}

	duk_ret_t Polycode_Entity_setContainerScene(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Scene* scene = (Scene*)duk_to_pointer(context, 0);
		inst->setContainerScene(scene);
		return 0;
	}

	duk_ret_t Polycode_Entity_getContainerScene(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getContainerScene();
		return 0;
	}

	duk_ret_t Polycode_Entity_attachScript(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Script* script = (Script*)duk_to_pointer(context, 0);
		inst->attachScript(script);
		return 0;
	}

	duk_ret_t Polycode_Entity_detachScript(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		Script* script = (Script*)duk_to_pointer(context, 0);
		inst->detachScript(script);
		return 0;
	}

	duk_ret_t Polycode_Entity_getNumScripts(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		inst->getNumScripts();
		return 0;
	}

	duk_ret_t Polycode_Entity_getScriptAtIndex(duk_context *context) {
		Entity *inst = (Entity*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getScriptAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Event_getEventCode(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		inst->getEventCode();
		return 0;
	}

	duk_ret_t Polycode_Event_getDispatcher(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		inst->getDispatcher();
		return 0;
	}

	duk_ret_t Polycode_Event_setEventCode(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		int eventCode = duk_to_int(context, 0);
		inst->setEventCode(eventCode);
		return 0;
	}

	duk_ret_t Polycode_Event_setDispatcher(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		EventDispatcher* dispatcher = (EventDispatcher*)duk_to_pointer(context, 0);
		inst->setDispatcher(dispatcher);
		return 0;
	}

	duk_ret_t Polycode_Event_getEventType(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		inst->getEventType();
		return 0;
	}

	duk_ret_t Polycode_Event_cancelEvent(duk_context *context) {
		Event *inst = (Event*)duk_to_pointer(context, -1);
		inst->cancelEvent();
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeAllHandlers(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		inst->removeAllHandlers();
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeAllHandlersForListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 0);
		inst->removeAllHandlersForListener(handler);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_addEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->addEventListener(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_addEventListenerUnique(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->addEventListenerUnique(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_hasEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->hasEventListener(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_removeEventListener(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		EventHandler* handler = (EventHandler*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->removeEventListener(handler,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher___dispatchEvent(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		Event* event = (Event*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->__dispatchEvent(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_dispatchEvent(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		Event* event = (Event*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->dispatchEvent(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_EventDispatcher_dispatchEventNoDelete(duk_context *context) {
		EventDispatcher *inst = (EventDispatcher*)duk_to_pointer(context, -1);
		Event* event = (Event*)duk_to_pointer(context, 0);
		int eventCode = duk_to_int(context, 1);
		inst->dispatchEventNoDelete(event,eventCode);
		return 0;
	}

	duk_ret_t Polycode_Font_getFace(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, -1);
		inst->getFace();
		return 0;
	}

	duk_ret_t Polycode_Font_isValid(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, -1);
		inst->isValid();
		return 0;
	}

	duk_ret_t Polycode_Font_setFontName(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, -1);
		String fontName = duk_to_string(context, 0);
		inst->setFontName(fontName);
		return 0;
	}

	duk_ret_t Polycode_Font_getFontName(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, -1);
		inst->getFontName();
		return 0;
	}

	duk_ret_t Polycode_Font_getFontPath(duk_context *context) {
		Font *inst = (Font*)duk_to_pointer(context, -1);
		inst->getFontPath();
		return 0;
	}

	duk_ret_t Polycode_Image_loadImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadImage(fileName);
		return 0;
	}

	duk_ret_t Polycode_Image_saveImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->saveImage(fileName);
		return 0;
	}

	duk_ret_t Polycode_Image_pasteImage(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		Image* image = (Image*)duk_to_pointer(context, 0);
		int x = duk_to_int(context, 1);
		int y = duk_to_int(context, 2);
		int blendingMode = duk_to_int(context, 3);
		Number blendAmount = duk_to_number(context, 4);
		Color blendColor = *(Color*)duk_to_pointer(context, 5);
		inst->pasteImage(image,x,y,blendingMode,blendAmount,blendColor);
		return 0;
	}

	duk_ret_t Polycode_Image_createEmpty(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		Color fillColor = *(Color*)duk_to_pointer(context, 2);
		inst->createEmpty(width,height,fillColor);
		return 0;
	}

	duk_ret_t Polycode_Image_fill(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		Color color = *(Color*)duk_to_pointer(context, 0);
		inst->fill(color);
		return 0;
	}

	duk_ret_t Polycode_Image_setPixel(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		Number r = duk_to_number(context, 2);
		Number g = duk_to_number(context, 3);
		Number b = duk_to_number(context, 4);
		Number a = duk_to_number(context, 5);
		inst->setPixel(x,y,r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Image_getPixel(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		inst->getPixel(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_swap(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int* v1 = (int*)duk_to_pointer(context, 0);
		int* v2 = (int*)duk_to_pointer(context, 1);
		inst->swap(v1,v2);
		return 0;
	}

	duk_ret_t Polycode_Image_drawLine(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x0 = duk_to_int(context, 0);
		int y0 = duk_to_int(context, 1);
		int x1 = duk_to_int(context, 2);
		int y1 = duk_to_int(context, 3);
		Color col = *(Color*)duk_to_pointer(context, 4);
		inst->drawLine(x0,y0,x1,y1,col);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrushTo(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		inst->moveBrushTo(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_moveBrush(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		inst->moveBrush(x,y);
		return 0;
	}

	duk_ret_t Polycode_Image_drawLineTo(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		Color col = *(Color*)duk_to_pointer(context, 2);
		inst->drawLineTo(x,y,col);
		return 0;
	}

	duk_ret_t Polycode_Image_fillRect(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		int w = duk_to_int(context, 2);
		int h = duk_to_int(context, 3);
		Color col = *(Color*)duk_to_pointer(context, 4);
		inst->fillRect(x,y,w,h,col);
		return 0;
	}

	duk_ret_t Polycode_Image_perlinNoise(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int seed = duk_to_int(context, 0);
		bool alpha = duk_to_boolean(context, 1);
		inst->perlinNoise(seed,alpha);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlur(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int blurSize = duk_to_int(context, 0);
		inst->fastBlur(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurVert(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int blurSize = duk_to_int(context, 0);
		inst->fastBlurVert(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_fastBlurHor(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int blurSize = duk_to_int(context, 0);
		inst->fastBlurHor(blurSize);
		return 0;
	}

	duk_ret_t Polycode_Image_getPixelsInRect(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		int x = duk_to_int(context, 0);
		int y = duk_to_int(context, 1);
		int width = duk_to_int(context, 2);
		int height = duk_to_int(context, 3);
		inst->getPixelsInRect(x,y,width,height);
		return 0;
	}

	duk_ret_t Polycode_Image_getImagePart(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		Rectangle subRect = *(Rectangle*)duk_to_pointer(context, 0);
		inst->getImagePart(subRect);
		return 0;
	}

	duk_ret_t Polycode_Image_getBrushX(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getBrushX();
		return 0;
	}

	duk_ret_t Polycode_Image_getBrushY(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getBrushY();
		return 0;
	}

	duk_ret_t Polycode_Image_isLoaded(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->isLoaded();
		return 0;
	}

	duk_ret_t Polycode_Image_getType(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getType();
		return 0;
	}

	duk_ret_t Polycode_Image_getWidth(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getWidth();
		return 0;
	}

	duk_ret_t Polycode_Image_getHeight(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getHeight();
		return 0;
	}

	duk_ret_t Polycode_Image_getPixels(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->getPixels();
		return 0;
	}

	duk_ret_t Polycode_Image_premultiplyAlpha(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		inst->premultiplyAlpha();
		return 0;
	}

	duk_ret_t Polycode_Image_savePNG(duk_context *context) {
		Image *inst = (Image*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->savePNG(fileName);
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getMousePosition(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, -1);
		inst->getMousePosition();
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getKey(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, -1);
		inst->getKey();
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getMouseButton(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, -1);
		inst->getMouseButton();
		return 0;
	}

	duk_ret_t Polycode_InputEvent_getCharCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, -1);
		inst->getCharCode();
		return 0;
	}

	duk_ret_t Polycode_InputEvent_keyCode(duk_context *context) {
		InputEvent *inst = (InputEvent*)duk_to_pointer(context, -1);
		inst->keyCode();
		return 0;
	}

	duk_ret_t Polycode_GlyphData_clearData(duk_context *context) {
		GlyphData *inst = (GlyphData*)duk_to_pointer(context, -1);
		inst->clearData();
		return 0;
	}

	duk_ret_t Polycode_Label_setText(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		String text = duk_to_string(context, 0);
		inst->setText(text);
		return 0;
	}

	duk_ret_t Polycode_Label_getText(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getText();
		return 0;
	}

	duk_ret_t Polycode_Label_getTextWidthForString(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		String text = duk_to_string(context, 0);
		inst->getTextWidthForString(text);
		return 0;
	}

	duk_ret_t Polycode_Label_getTextHeightForString(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		String text = duk_to_string(context, 0);
		inst->getTextHeightForString(text);
		return 0;
	}

	duk_ret_t Polycode_Label_getTextWidth(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getTextWidth();
		return 0;
	}

	duk_ret_t Polycode_Label_getTextHeight(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getTextHeight();
		return 0;
	}

	duk_ret_t Polycode_Label_setColorForRange(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		Color color = *(Color*)duk_to_pointer(context, 0);
		int rangeStart = duk_to_int(context, 1);
		int rangeEnd = duk_to_int(context, 2);
		inst->setColorForRange(color,rangeStart,rangeEnd);
		return 0;
	}

	duk_ret_t Polycode_Label_clearColors(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->clearColors();
		return 0;
	}

	duk_ret_t Polycode_Label_getColorForIndex(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getColorForIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Label_getPremultiplyAlpha(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getPremultiplyAlpha();
		return 0;
	}

	duk_ret_t Polycode_Label_setPremultiplyAlpha(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setPremultiplyAlpha(val);
		return 0;
	}

	duk_ret_t Polycode_Label_setFont(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		Font* newFont = (Font*)duk_to_pointer(context, 0);
		inst->setFont(newFont);
		return 0;
	}

	duk_ret_t Polycode_Label_getFont(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getFont();
		return 0;
	}

	duk_ret_t Polycode_Label_setSize(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		int newSize = duk_to_int(context, 0);
		inst->setSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_Label_getSize(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getSize();
		return 0;
	}

	duk_ret_t Polycode_Label_getAntialiasMode(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getAntialiasMode();
		return 0;
	}

	duk_ret_t Polycode_Label_setAntialiasMode(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		int newMode = duk_to_int(context, 0);
		inst->setAntialiasMode(newMode);
		return 0;
	}

	duk_ret_t Polycode_Label_getBaselineAdjust(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getBaselineAdjust();
		return 0;
	}

	duk_ret_t Polycode_Label_setBackgroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		Color color = *(Color*)duk_to_pointer(context, 0);
		inst->setBackgroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setForegroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		Color color = *(Color*)duk_to_pointer(context, 0);
		inst->setForegroundColor(color);
		return 0;
	}

	duk_ret_t Polycode_Label_setColors(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		Color backgroundColor = *(Color*)duk_to_pointer(context, 0);
		Color foregroundColor = *(Color*)duk_to_pointer(context, 1);
		inst->setColors(backgroundColor,foregroundColor);
		return 0;
	}

	duk_ret_t Polycode_Label_getBackgroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getBackgroundColor();
		return 0;
	}

	duk_ret_t Polycode_Label_getForegroundColor(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->getForegroundColor();
		return 0;
	}

	duk_ret_t Polycode_Label_optionsChanged(duk_context *context) {
		Label *inst = (Label*)duk_to_pointer(context, -1);
		inst->optionsChanged();
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 0);
		inst->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderPassAtIndex(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 0);
		int shaderIndex = duk_to_int(context, 1);
		inst->addShaderPassAtIndex(pass,shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_addShader(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		Shader* shader = (Shader*)duk_to_pointer(context, 0);
		ShaderBinding* shaderBinding = (ShaderBinding*)duk_to_pointer(context, 1);
		inst->addShader(shader,shaderBinding);
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderAtIndex(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		Shader* shader = (Shader*)duk_to_pointer(context, 0);
		ShaderBinding* shaderBinding = (ShaderBinding*)duk_to_pointer(context, 1);
		int shaderIndex = duk_to_int(context, 2);
		inst->addShaderAtIndex(shader,shaderBinding,shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderPasses(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->getNumShaderPasses();
		return 0;
	}

	duk_ret_t Polycode_Material_removeShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int shaderIndex = duk_to_int(context, 0);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateExpectedShaderParams(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->recreateExpectedShaderParams();
		return 0;
	}

	duk_ret_t Polycode_Material_addShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		ShaderRenderTarget* newTarget = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->addShaderRenderTarget(newTarget);
		return 0;
	}

	duk_ret_t Polycode_Material_getNumShaderRenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->getNumShaderRenderTargets();
		return 0;
	}

	duk_ret_t Polycode_Material_getShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderRenderTarget(index);
		return 0;
	}

	duk_ret_t Polycode_Material_removeShaderRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->removeShaderRenderTarget(index);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateRenderTarget(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		ShaderRenderTarget* renderTarget = (ShaderRenderTarget*)duk_to_pointer(context, 0);
		inst->recreateRenderTarget(renderTarget);
		return 0;
	}

	duk_ret_t Polycode_Material_recreateRenderTargets(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->recreateRenderTargets();
		return 0;
	}

	duk_ret_t Polycode_Material_getName(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_Material_getShaderPass(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderPass(index);
		return 0;
	}

	duk_ret_t Polycode_Material_getShaderBinding(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderBinding(index);
		return 0;
	}

	duk_ret_t Polycode_Material_getShader(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShader(index);
		return 0;
	}

	duk_ret_t Polycode_Material_loadMaterial(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadMaterial(fileName);
		return 0;
	}

	duk_ret_t Polycode_Material_setName(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Material_clearShaders(duk_context *context) {
		Material *inst = (Material*)duk_to_pointer(context, -1);
		inst->clearShaders();
		return 0;
	}

	duk_ret_t Polycode_ShaderPass_setAttributeArraysFromMesh(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, -1);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 0);
		inst->setAttributeArraysFromMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_ShaderPass_setExpectedAttributes(duk_context *context) {
		ShaderPass *inst = (ShaderPass*)duk_to_pointer(context, -1);
		inst->setExpectedAttributes();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_Update(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int elapsed = duk_to_int(context, 0);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		char* imageData = (char*)duk_to_pointer(context, 2);
		bool clamp = duk_to_boolean(context, 3);
		bool createMipmaps = duk_to_boolean(context, 4);
		int type = duk_to_int(context, 5);
		inst->createTexture(width,height,imageData,clamp,createMipmaps,type);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createNewTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		bool clamp = duk_to_boolean(context, 2);
		bool createMipmaps = duk_to_boolean(context, 3);
		int type = duk_to_int(context, 4);
		inst->createNewTexture(width,height,clamp,createMipmaps,type);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createTextureFromImage(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		Image* image = (Image*)duk_to_pointer(context, 0);
		bool clamp = duk_to_boolean(context, 1);
		bool createMipmaps = duk_to_boolean(context, 2);
		inst->createTextureFromImage(image,clamp,createMipmaps);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createTextureFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		bool clamp = duk_to_boolean(context, 1);
		bool createMipmaps = duk_to_boolean(context, 2);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 3);
		inst->createTextureFromFile(fileName,clamp,createMipmaps,resourcePool);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_deleteTexture(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		Texture* texture = (Texture*)duk_to_pointer(context, 0);
		inst->deleteTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadTextures(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		inst->reloadTextures();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadProgramsAndTextures(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		inst->reloadProgramsAndTextures();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_reloadPrograms(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		inst->reloadPrograms();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getTextureByResourcePath(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		String resourcePath = duk_to_string(context, 0);
		inst->getTextureByResourcePath(resourcePath);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createProgramFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		String programPath = duk_to_string(context, 0);
		inst->createProgramFromFile(programPath);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadMaterialLibraryIntoPool(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		String materialFile = duk_to_string(context, 1);
		inst->loadMaterialLibraryIntoPool(pool,materialFile);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_cubemapFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 0);
		inst->cubemapFromXMLNode(node);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_materialFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 1);
		inst->materialFromXMLNode(resourcePool,node);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createMaterial(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		String materialName = duk_to_string(context, 1);
		String shaderName = duk_to_string(context, 2);
		inst->createMaterial(resourcePool,materialName,shaderName);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_setShaderFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 1);
		inst->setShaderFromXMLNode(resourcePool,node);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createShaderFromXMLNode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		TiXmlNode* node = (TiXmlNode*)duk_to_pointer(context, 1);
		inst->createShaderFromXMLNode(resourcePool,node);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_createShader(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		String shaderType = duk_to_string(context, 1);
		String name = duk_to_string(context, 2);
		String vpName = duk_to_string(context, 3);
		String fpName = duk_to_string(context, 4);
		bool screenShader = duk_to_boolean(context, 5);
		inst->createShader(resourcePool,shaderType,name,vpName,fpName,screenShader);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadMaterialsFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadMaterialsFromFile(resourcePool,fileName);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadShadersFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadShadersFromFile(resourcePool,fileName);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_loadCubemapsFromFile(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadCubemapsFromFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_setAnisotropyAmount(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int anisotropy = duk_to_int(context, 0);
		inst->setAnisotropyAmount(anisotropy);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_setTextureFilteringMode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int textureFilteringMode = duk_to_int(context, 0);
		inst->setTextureFilteringMode(textureFilteringMode);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getTextureFilteringMode(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		inst->getTextureFilteringMode();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_addMaterial(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		Material* material = (Material*)duk_to_pointer(context, 0);
		inst->addMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_addShader(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		Shader* shader = (Shader*)duk_to_pointer(context, 0);
		inst->addShader(shader);
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getNumShaders(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		inst->getNumShaders();
		return 0;
	}

	duk_ret_t Polycode_MaterialManager_getShaderByIndex(duk_context *context) {
		MaterialManager *inst = (MaterialManager*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderByIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_identity(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->identity();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_rotateVector(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 0);
		inst->rotateVector(v2);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_getPosition(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->getPosition();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_multiplyWithPerspective(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 0);
		inst->multiplyWithPerspective(v2);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_multVector3(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 0);
		inst->multVector3(v2);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_multVector4(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Vector4 v2 = *(Vector4*)duk_to_pointer(context, 0);
		inst->multVector4(v2);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_Translate(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->Translate(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setPosition(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->setPosition(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setScale(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Vector3 scale = *(Vector3*)duk_to_pointer(context, 0);
		inst->setScale(scale);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_getEulerAngles(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number* ax = (Number*)duk_to_pointer(context, 0);
		Number* ay = (Number*)duk_to_pointer(context, 1);
		Number* az = (Number*)duk_to_pointer(context, 2);
		inst->getEulerAngles(ax,ay,az);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_transpose(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->transpose();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_Inverse(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->Inverse();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_inverseAffine(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->inverseAffine();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_determinant(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		inst->determinant();
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setOrthoProjection(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number left = duk_to_number(context, 0);
		Number right = duk_to_number(context, 1);
		Number bottom = duk_to_number(context, 2);
		Number top = duk_to_number(context, 3);
		Number zNear = duk_to_number(context, 4);
		Number zFar = duk_to_number(context, 5);
		inst->setOrthoProjection(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjectionFrustum(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number left = duk_to_number(context, 0);
		Number right = duk_to_number(context, 1);
		Number bottom = duk_to_number(context, 2);
		Number top = duk_to_number(context, 3);
		Number zNear = duk_to_number(context, 4);
		Number zFar = duk_to_number(context, 5);
		inst->setProjectionFrustum(left,right,bottom,top,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Matrix4_setProjection(duk_context *context) {
		Matrix4 *inst = (Matrix4*)duk_to_pointer(context, -1);
		Number fov = duk_to_number(context, 0);
		Number aspect = duk_to_number(context, 1);
		Number zNear = duk_to_number(context, 2);
		Number zFar = duk_to_number(context, 3);
		inst->setProjection(fov,aspect,zNear,zFar);
		return 0;
	}

	duk_ret_t Polycode_Mesh_loadMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadMesh(fileName);
		return 0;
	}

	duk_ret_t Polycode_Mesh_clearMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->clearMesh();
		return 0;
	}

	duk_ret_t Polycode_Mesh_saveToFile(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		bool writeNormals = duk_to_boolean(context, 1);
		bool writeTangents = duk_to_boolean(context, 2);
		bool writeColors = duk_to_boolean(context, 3);
		bool writeBoneWeights = duk_to_boolean(context, 4);
		bool writeUVs = duk_to_boolean(context, 5);
		bool writeSecondaryUVs = duk_to_boolean(context, 6);
		inst->saveToFile(fileName,writeNormals,writeTangents,writeColors,writeBoneWeights,writeUVs,writeSecondaryUVs);
		return 0;
	}

	duk_ret_t Polycode_Mesh_loadFromFile(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		CoreFile* inFile = (CoreFile*)duk_to_pointer(context, 0);
		inst->loadFromFile(inFile);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexCount(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->getVertexCount();
		return 0;
	}

	duk_ret_t Polycode_Mesh_createPlane(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number h = duk_to_number(context, 1);
		Number tilingValue = duk_to_number(context, 2);
		inst->createPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createVPlane(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number h = duk_to_number(context, 1);
		Number tilingValue = duk_to_number(context, 2);
		inst->createVPlane(w,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCircle(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number h = duk_to_number(context, 1);
		int numSegments = duk_to_int(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createLineCircle(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number h = duk_to_number(context, 1);
		int numSegments = duk_to_int(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createLineCircle(w,h,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createTorus(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number radius = duk_to_number(context, 0);
		Number tubeRadius = duk_to_number(context, 1);
		int segmentsW = duk_to_int(context, 2);
		int segmentsH = duk_to_int(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createTorus(radius,tubeRadius,segmentsW,segmentsH,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createBox(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number d = duk_to_number(context, 1);
		Number h = duk_to_number(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createBox(w,d,h,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createSphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number radius = duk_to_number(context, 0);
		int numRings = duk_to_int(context, 1);
		int numSegments = duk_to_int(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createSphere(radius,numRings,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createIcosphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number radius = duk_to_number(context, 0);
		int subdivisions = duk_to_int(context, 1);
		inst->createIcosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createOctosphere(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number radius = duk_to_number(context, 0);
		int subdivisions = duk_to_int(context, 1);
		inst->createOctosphere(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCylinder(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number height = duk_to_number(context, 0);
		Number radius = duk_to_number(context, 1);
		int numSegments = duk_to_int(context, 2);
		bool capped = duk_to_boolean(context, 3);
		Number tilingValue = duk_to_number(context, 4);
		inst->createCylinder(height,radius,numSegments,capped,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_createCone(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number height = duk_to_number(context, 0);
		Number radius = duk_to_number(context, 1);
		int numSegments = duk_to_int(context, 2);
		Number tilingValue = duk_to_number(context, 3);
		inst->createCone(height,radius,numSegments,tilingValue);
		return 0;
	}

	duk_ret_t Polycode_Mesh_recenterMesh(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->recenterMesh();
		return 0;
	}

	duk_ret_t Polycode_Mesh_setVertexAtOffset(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int offset = duk_to_int(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->setVertexAtOffset(offset,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertexWithUVAndNormal(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		Number u = duk_to_number(context, 3);
		Number v = duk_to_number(context, 4);
		Number nx = duk_to_number(context, 5);
		Number ny = duk_to_number(context, 6);
		Number nz = duk_to_number(context, 7);
		inst->addVertexWithUVAndNormal(x,y,z,u,v,nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTexCoord(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number u = duk_to_number(context, 0);
		Number v = duk_to_number(context, 1);
		inst->addTexCoord(u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTexCoord2(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number u = duk_to_number(context, 0);
		Number v = duk_to_number(context, 1);
		inst->addTexCoord2(u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addTangent(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->addTangent(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertexWithUV(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		Number u = duk_to_number(context, 3);
		Number v = duk_to_number(context, 4);
		inst->addVertexWithUV(x,y,z,u,v);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addVertex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->addVertex(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addNormal(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number nx = duk_to_number(context, 0);
		Number ny = duk_to_number(context, 1);
		Number nz = duk_to_number(context, 2);
		inst->addNormal(nx,ny,nz);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addBoneAssignments(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number b1Weight = duk_to_number(context, 0);
		int b1Index = duk_to_int(context, 1);
		Number b2Weight = duk_to_number(context, 2);
		int b2Index = duk_to_int(context, 3);
		Number b3Weight = duk_to_number(context, 4);
		int b3Index = duk_to_int(context, 5);
		Number b4Weight = duk_to_number(context, 6);
		int b4Index = duk_to_int(context, 7);
		inst->addBoneAssignments(b1Weight,b1Index,b2Weight,b2Index,b3Weight,b3Index,b4Weight,b4Index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addColor(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->addColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexPosition(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int vertexOffset = duk_to_int(context, 0);
		inst->getVertexPosition(vertexOffset);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexPositionAtIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getVertexPositionAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexTexCoord(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int vertexOffset = duk_to_int(context, 0);
		inst->getVertexTexCoord(vertexOffset);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getVertexTexCoordAtIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getVertexTexCoordAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_Copy(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->Copy();
		return 0;
	}

	duk_ret_t Polycode_Mesh_getRadius(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->getRadius();
		return 0;
	}

	duk_ret_t Polycode_Mesh_calculateNormals(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->calculateNormals();
		return 0;
	}

	duk_ret_t Polycode_Mesh_calculateTangents(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->calculateTangents();
		return 0;
	}

	duk_ret_t Polycode_Mesh_getMeshType(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->getMeshType();
		return 0;
	}

	duk_ret_t Polycode_Mesh_setMeshType(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int newType = duk_to_int(context, 0);
		inst->setMeshType(newType);
		return 0;
	}

	duk_ret_t Polycode_Mesh_getIndexGroupSize(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->getIndexGroupSize();
		return 0;
	}

	duk_ret_t Polycode_Mesh_calculateBBox(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->calculateBBox();
		return 0;
	}

	duk_ret_t Polycode_Mesh_hasVertexBuffer(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->hasVertexBuffer();
		return 0;
	}

	duk_ret_t Polycode_Mesh_addIndexedFace(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int i1 = duk_to_int(context, 0);
		int i2 = duk_to_int(context, 1);
		inst->addIndexedFace(i1,i2);
		return 0;
	}

	duk_ret_t Polycode_Mesh_addIndex(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->addIndex(index);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeVertexRange(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int beginRemoveVertex = duk_to_int(context, 0);
		int vertexRemovalCount = duk_to_int(context, 1);
		inst->removeVertexRange(beginRemoveVertex,vertexRemovalCount);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeFace(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		int faceIndex = duk_to_int(context, 0);
		inst->removeFace(faceIndex);
		return 0;
	}

	duk_ret_t Polycode_Mesh_removeUnusedVertices(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->removeUnusedVertices();
		return 0;
	}

	duk_ret_t Polycode_Mesh_getIndexCount(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->getIndexCount();
		return 0;
	}

	duk_ret_t Polycode_Mesh_subdivideToRadius(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		Number radius = duk_to_number(context, 0);
		int subdivisions = duk_to_int(context, 1);
		inst->subdivideToRadius(radius,subdivisions);
		return 0;
	}

	duk_ret_t Polycode_Mesh_saveAsOBJ(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->saveAsOBJ(fileName);
		return 0;
	}

	duk_ret_t Polycode_Mesh_normalizeBoneWeights(duk_context *context) {
		Mesh *inst = (Mesh*)duk_to_pointer(context, -1);
		inst->normalizeBoneWeights();
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_readNumber(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		String key = duk_to_string(context, 0);
		Number* out = (Number*)duk_to_pointer(context, 1);
		inst->readNumber(key,out);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_readString(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		String key = duk_to_string(context, 0);
		String* out = (String*)duk_to_pointer(context, 1);
		inst->readString(key,out);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_readBool(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		String key = duk_to_string(context, 0);
		bool* out = (bool*)duk_to_pointer(context, 1);
		inst->readBool(key,out);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_addChild(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->addChild(name);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_getTypedName(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		inst->getTypedName();
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_setTypedName(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		inst->setTypedName(str);
		return 0;
	}

	duk_ret_t Polycode_ObjectEntry_Clear(duk_context *context) {
		ObjectEntry *inst = (ObjectEntry*)duk_to_pointer(context, -1);
		inst->Clear();
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_parseKeysFromObjectEntry(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, -1);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->parseKeysFromObjectEntry(entry);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_writeEntryToFile(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, -1);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 0);
		inst->writeEntryToFile(entry);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_addKey(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, -1);
		String key = duk_to_string(context, 0);
		inst->addKey(key);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_getKeyIndex(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, -1);
		String key = duk_to_string(context, 0);
		inst->getKeyIndex(key);
		return 0;
	}

	duk_ret_t Polycode_BinaryObjectWriter_writeToFile(duk_context *context) {
		BinaryObjectWriter *inst = (BinaryObjectWriter*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->writeToFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleCount(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		int newParticleCount = duk_to_int(context, 0);
		inst->setParticleCount(newParticleCount);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleCount(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleCount();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleLifetime(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Number lifetime = duk_to_number(context, 0);
		inst->setParticleLifetime(lifetime);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleLifetime(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleLifetime();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setDirectionDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 newDeviation = *(Vector3*)duk_to_pointer(context, 0);
		inst->setDirectionDeviation(newDeviation);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getDirectionDeviation(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getDirectionDeviation();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setEmitterSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 newSize = *(Vector3*)duk_to_pointer(context, 0);
		inst->setEmitterSize(newSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getEmitterSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getEmitterSize();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setGravity(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 newGravity = *(Vector3*)duk_to_pointer(context, 0);
		inst->setGravity(newGravity);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getGravity(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getGravity();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_fixedUpdate(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_Render(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_updateParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->updateParticles();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_rebuildParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->rebuildParticles(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_triggerParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool allAtOnce = duk_to_boolean(context, 0);
		inst->triggerParticles(allAtOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_enableParticleSystem(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->enableParticleSystem(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setUseFloorPlane(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setUseFloorPlane(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorPlaneOffset(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Number floorPlaneOffset = duk_to_number(context, 0);
		inst->setFloorPlaneOffset(floorPlaneOffset);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setFloorDamping(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Number floorDamping = duk_to_number(context, 0);
		inst->setFloorDamping(floorDamping);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticlesInWorldSpace(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setParticlesInWorldSpace(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticlesInWorldSpace(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticlesInWorldSpace();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinEnabled(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setPerlinEnabled(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinEnabled(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getPerlinEnabled();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleSpeed();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Number speed = duk_to_number(context, 0);
		inst->setParticleSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setPerlinValue(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 perlinValue = *(Vector3*)duk_to_pointer(context, 0);
		inst->setPerlinValue(perlinValue);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getPerlinValue(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getPerlinValue();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleType(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		int particleType = duk_to_int(context, 0);
		inst->setParticleType(particleType);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleType(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleType();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Number particleSize = duk_to_number(context, 0);
		inst->setParticleSize(particleSize);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleSize(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleSize();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleRotationSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 rotationSpeed = *(Vector3*)duk_to_pointer(context, 0);
		inst->setParticleRotationSpeed(rotationSpeed);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleRotationSpeed(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleRotationSpeed();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setParticleDirection(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 0);
		inst->setParticleDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getParticleDirection(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getParticleDirection();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_setLoopParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setLoopParticles(val);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getLoopParticles(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getLoopParticles();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_addSourceMesh(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 0);
		inst->addSourceMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getNumSourceMeshes(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		inst->getNumSourceMeshes();
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_getSourcesMeshAtIndex(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getSourcesMeshAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_removeSourceMeshAtIndex(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->removeSourceMeshAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_positionParticle(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->positionParticle(index);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_Clone(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneParticleEmitter_applyClone(duk_context *context) {
		SceneParticleEmitter *inst = (SceneParticleEmitter*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get2DTiledX(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number t = duk_to_number(context, 2);
		inst->Get2DTiledX(x,y,t);
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		inst->Get(x,y);
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get2D(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		inst->Get2D(x,y);
		return 0;
	}

	duk_ret_t Polycode_Perlin_Get3D(duk_context *context) {
		Perlin *inst = (Perlin*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->Get3D(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_setFromMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Matrix4 _mat = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setFromMatrix(_mat);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Dot(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Quaternion rkQ = *(Quaternion*)duk_to_pointer(context, 0);
		inst->Dot(rkQ);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Log(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->Log();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Exp(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->Exp();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Norm(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->Norm();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Normalize(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_lookAt(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Vector3 D = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 1);
		inst->lookAt(D,upVector);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->createFromMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_Inverse(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->Inverse();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_set(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number w = duk_to_number(context, 0);
		Number x = duk_to_number(context, 1);
		Number y = duk_to_number(context, 2);
		Number z = duk_to_number(context, 3);
		inst->set(w,x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_InvSqrt(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->InvSqrt(x);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_fromAxes(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number az = duk_to_number(context, 0);
		Number ay = duk_to_number(context, 1);
		Number ax = duk_to_number(context, 2);
		inst->fromAxes(az,ay,ax);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_fromAngleAxis(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number rfAngle = duk_to_number(context, 0);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 1);
		inst->fromAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_toEulerAngles(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->toEulerAngles();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_toAngleAxis(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number rfAngle = duk_to_number(context, 0);
		Vector3 rkAxis = *(Vector3*)duk_to_pointer(context, 1);
		inst->toAngleAxis(rfAngle,rkAxis);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createFromAxisAngle(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		Number degrees = duk_to_number(context, 3);
		inst->createFromAxisAngle(x,y,z,degrees);
		return 0;
	}

	duk_ret_t Polycode_Quaternion_createMatrix(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		inst->createMatrix();
		return 0;
	}

	duk_ret_t Polycode_Quaternion_applyTo(duk_context *context) {
		Quaternion *inst = (Quaternion*)duk_to_pointer(context, -1);
		Vector3 v = *(Vector3*)duk_to_pointer(context, 0);
		inst->applyTo(v);
		return 0;
	}

	duk_ret_t Polycode_QuaternionCurve_interpolate(duk_context *context) {
		QuaternionCurve *inst = (QuaternionCurve*)duk_to_pointer(context, -1);
		Number t = duk_to_number(context, 0);
		bool useShortestPath = duk_to_boolean(context, 1);
		inst->interpolate(t,useShortestPath);
		return 0;
	}

	duk_ret_t Polycode_QuaternionCurve_generatePointsFromCurves(duk_context *context) {
		QuaternionCurve *inst = (QuaternionCurve*)duk_to_pointer(context, -1);
		BezierCurve* wCurve = (BezierCurve*)duk_to_pointer(context, 0);
		BezierCurve* xCurve = (BezierCurve*)duk_to_pointer(context, 1);
		BezierCurve* yCurve = (BezierCurve*)duk_to_pointer(context, 2);
		BezierCurve* zCurve = (BezierCurve*)duk_to_pointer(context, 3);
		inst->generatePointsFromCurves(wCurve,xCurve,yCurve,zCurve);
		return 0;
	}

	duk_ret_t Polycode_Ray_boxIntersect(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Vector3 box = *(Vector3*)duk_to_pointer(context, 0);
		Matrix4 transformMatrix = *(Matrix4*)duk_to_pointer(context, 1);
		Number near = duk_to_number(context, 2);
		Number far = duk_to_number(context, 3);
		inst->boxIntersect(box,transformMatrix,near,far);
		return 0;
	}

	duk_ret_t Polycode_Ray_planeIntersectPoint(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Vector3 planeNormal = *(Vector3*)duk_to_pointer(context, 0);
		Number planeDistance = duk_to_number(context, 1);
		inst->planeIntersectPoint(planeNormal,planeDistance);
		return 0;
	}

	duk_ret_t Polycode_Ray_tranformByMatrix(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Matrix4 matrix = *(Matrix4*)duk_to_pointer(context, 0);
		inst->tranformByMatrix(matrix);
		return 0;
	}

	duk_ret_t Polycode_Ray_closestPointOnRay(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Vector3 point = *(Vector3*)duk_to_pointer(context, 0);
		inst->closestPointOnRay(point);
		return 0;
	}

	duk_ret_t Polycode_Ray_closestPointsBetween(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Ray ray2 = *(Ray*)duk_to_pointer(context, 0);
		Vector3* point1 = (Vector3*)duk_to_pointer(context, 1);
		Vector3* point2 = (Vector3*)duk_to_pointer(context, 2);
		inst->closestPointsBetween(ray2,point1,point2);
		return 0;
	}

	duk_ret_t Polycode_Ray_polygonIntersect(duk_context *context) {
		Ray *inst = (Ray*)duk_to_pointer(context, -1);
		Vector3 v1 = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 v2 = *(Vector3*)duk_to_pointer(context, 1);
		Vector3 v3 = *(Vector3*)duk_to_pointer(context, 2);
		inst->polygonIntersect(v1,v2,v3);
		return 0;
	}

	duk_ret_t Polycode_Rectangle_setRect(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number w = duk_to_number(context, 2);
		Number h = duk_to_number(context, 3);
		inst->setRect(x,y,w,h);
		return 0;
	}

	duk_ret_t Polycode_Rectangle_Clipped(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		Rectangle rect = *(Rectangle*)duk_to_pointer(context, 0);
		inst->Clipped(rect);
		return 0;
	}

	duk_ret_t Polycode_Rectangle_minX(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		inst->minX();
		return 0;
	}

	duk_ret_t Polycode_Rectangle_maxX(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		inst->maxX();
		return 0;
	}

	duk_ret_t Polycode_Rectangle_minY(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		inst->minY();
		return 0;
	}

	duk_ret_t Polycode_Rectangle_maxY(duk_context *context) {
		Rectangle *inst = (Rectangle*)duk_to_pointer(context, -1);
		inst->maxY();
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray_getArrayData(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, -1);
		inst->getArrayData();
		return 0;
	}

	duk_ret_t Polycode_RenderDataArray_getDataSize(duk_context *context) {
		RenderDataArray *inst = (RenderDataArray*)duk_to_pointer(context, -1);
		inst->getDataSize();
		return 0;
	}

	duk_ret_t Polycode_VertexDataArray_getCountPerVertex(duk_context *context) {
		VertexDataArray *inst = (VertexDataArray*)duk_to_pointer(context, -1);
		inst->getCountPerVertex();
		return 0;
	}

	duk_ret_t Polycode_VertexDataArray_getArrayData(duk_context *context) {
		VertexDataArray *inst = (VertexDataArray*)duk_to_pointer(context, -1);
		inst->getArrayData();
		return 0;
	}

	duk_ret_t Polycode_VertexDataArray_getDataSize(duk_context *context) {
		VertexDataArray *inst = (VertexDataArray*)duk_to_pointer(context, -1);
		inst->getDataSize();
		return 0;
	}

	duk_ret_t Polycode_IndexDataArray_getArrayData(duk_context *context) {
		IndexDataArray *inst = (IndexDataArray*)duk_to_pointer(context, -1);
		inst->getArrayData();
		return 0;
	}

	duk_ret_t Polycode_IndexDataArray_getDataSize(duk_context *context) {
		IndexDataArray *inst = (IndexDataArray*)duk_to_pointer(context, -1);
		inst->getDataSize();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_setGraphicsInterface(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		Core* core = (Core*)duk_to_pointer(context, 0);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*)duk_to_pointer(context, 1);
		inst->setGraphicsInterface(core,graphicsInterface);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_runThread(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->runThread();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_enqueueFrame(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		RenderFrame* frame = (RenderFrame*)duk_to_pointer(context, 0);
		inst->enqueueFrame(frame);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_enqueueJob(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		int jobType = duk_to_int(context, 0);
		void* data = (void*)duk_to_pointer(context, 1);
		void* data2 = (void*)duk_to_pointer(context, 2);
		inst->enqueueJob(jobType,data,data2);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_processJob(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		RendererThreadJob job = *(RendererThreadJob*)duk_to_pointer(context, 0);
		inst->processJob(job);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_getShaderBinding(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->getShaderBinding();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_processDrawBuffer(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->processDrawBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_RenderThread_getFrameInfo(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->getFrameInfo();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_clearFrameQueue(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->clearFrameQueue();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_initGlobals(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->initGlobals();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_lockRenderMutex(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->lockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_RenderThread_unlockRenderMutex(duk_context *context) {
		RenderThread *inst = (RenderThread*)duk_to_pointer(context, -1);
		inst->unlockRenderMutex();
		return 0;
	}

	duk_ret_t Polycode_Renderer_setGraphicsInterface(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Core* core = (Core*)duk_to_pointer(context, 0);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*)duk_to_pointer(context, 1);
		inst->setGraphicsInterface(core,graphicsInterface);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getRenderThread(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->getRenderThread();
		return 0;
	}

	duk_ret_t Polycode_Renderer_createCubemap(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Texture* t0 = (Texture*)duk_to_pointer(context, 0);
		Texture* t1 = (Texture*)duk_to_pointer(context, 1);
		Texture* t2 = (Texture*)duk_to_pointer(context, 2);
		Texture* t3 = (Texture*)duk_to_pointer(context, 3);
		Texture* t4 = (Texture*)duk_to_pointer(context, 4);
		Texture* t5 = (Texture*)duk_to_pointer(context, 5);
		inst->createCubemap(t0,t1,t2,t3,t4,t5);
		return 0;
	}

	duk_ret_t Polycode_Renderer_createTexture(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		char* textureData = (char*)duk_to_pointer(context, 2);
		bool clamp = duk_to_boolean(context, 3);
		bool createMipmaps = duk_to_boolean(context, 4);
		int type = duk_to_int(context, 5);
		int filteringMode = duk_to_int(context, 6);
		int anisotropy = duk_to_int(context, 7);
		bool framebufferTexture = duk_to_boolean(context, 8);
		inst->createTexture(width,height,textureData,clamp,createMipmaps,type,filteringMode,anisotropy,framebufferTexture);
		return 0;
	}

	duk_ret_t Polycode_Renderer_createRenderBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		int width = duk_to_int(context, 0);
		int height = duk_to_int(context, 1);
		bool attachDepthBuffer = duk_to_boolean(context, 2);
		bool floatingPoint = duk_to_boolean(context, 3);
		inst->createRenderBuffer(width,height,attachDepthBuffer,floatingPoint);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyRenderBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		RenderBuffer* buffer = (RenderBuffer*)duk_to_pointer(context, 0);
		inst->destroyRenderBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyTexture(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Texture* texture = (Texture*)duk_to_pointer(context, 0);
		inst->destroyTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_Renderer_processDrawBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->processDrawBuffer(buffer);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setBackingResolutionScale(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Number xScale = duk_to_number(context, 0);
		Number yScale = duk_to_number(context, 1);
		inst->setBackingResolutionScale(xScale,yScale);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleX(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->getBackingResolutionScaleX();
		return 0;
	}

	duk_ret_t Polycode_Renderer_getBackingResolutionScaleY(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->getBackingResolutionScaleY();
		return 0;
	}

	duk_ret_t Polycode_Renderer_createProgram(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->createProgram(fileName);
		return 0;
	}

	duk_ret_t Polycode_Renderer_createShader(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		ShaderProgram* vertexProgram = (ShaderProgram*)duk_to_pointer(context, 0);
		ShaderProgram* fragmentProgram = (ShaderProgram*)duk_to_pointer(context, 1);
		inst->createShader(vertexProgram,fragmentProgram);
		return 0;
	}

	duk_ret_t Polycode_Renderer_createVertexBuffers(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 0);
		inst->createVertexBuffers(mesh);
		return 0;
	}

	duk_ret_t Polycode_Renderer_enqueueFrameJob(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		int jobType = duk_to_int(context, 0);
		void* data = (void*)duk_to_pointer(context, 1);
		inst->enqueueFrameJob(jobType,data);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyProgram(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		ShaderProgram* program = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->destroyProgram(program);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShader(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Shader* shader = (Shader*)duk_to_pointer(context, 0);
		inst->destroyShader(shader);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyBuffer(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		RenderDataArray* array = (RenderDataArray*)duk_to_pointer(context, 0);
		inst->destroyBuffer(array);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShaderBinding(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		ShaderBinding* binding = (ShaderBinding*)duk_to_pointer(context, 0);
		inst->destroyShaderBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyShaderParam(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		LocalShaderParam* param = (LocalShaderParam*)duk_to_pointer(context, 0);
		inst->destroyShaderParam(param);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setTextureParam(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		LocalShaderParam* param = (LocalShaderParam*)duk_to_pointer(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->setTextureParam(param,texture);
		return 0;
	}

	duk_ret_t Polycode_Renderer_setAnisotropyAmount(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Number amount = duk_to_number(context, 0);
		inst->setAnisotropyAmount(amount);
		return 0;
	}

	duk_ret_t Polycode_Renderer_getAnisotropyAmount(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->getAnisotropyAmount();
		return 0;
	}

	duk_ret_t Polycode_Renderer_createMesh(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->createMesh(fileName);
		return 0;
	}

	duk_ret_t Polycode_Renderer_destroyMesh(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 0);
		inst->destroyMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_Renderer_beginFrame(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->beginFrame();
		return 0;
	}

	duk_ret_t Polycode_Renderer_endFrame(duk_context *context) {
		Renderer *inst = (Renderer*)duk_to_pointer(context, -1);
		inst->endFrame();
		return 0;
	}

	duk_ret_t Polycode_Resource_reloadResource(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourceName(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		inst->getResourceName();
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourceType(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		inst->getResourceType();
		return 0;
	}

	duk_ret_t Polycode_Resource_setResourceName(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		String newName = duk_to_string(context, 0);
		inst->setResourceName(newName);
		return 0;
	}

	duk_ret_t Polycode_Resource_setResourcePath(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		inst->setResourcePath(path);
		return 0;
	}

	duk_ret_t Polycode_Resource_getResourcePath(duk_context *context) {
		Resource *inst = (Resource*)duk_to_pointer(context, -1);
		inst->getResourcePath();
		return 0;
	}

	duk_ret_t Polycode_ScriptResourceLoader_loadResource(duk_context *context) {
		ScriptResourceLoader *inst = (ScriptResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_setFallbackPool(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->setFallbackPool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_addResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		Resource* resource = (Resource*)duk_to_pointer(context, 0);
		inst->addResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_removeResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		Resource* resource = (Resource*)duk_to_pointer(context, 0);
		inst->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_hasResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		Resource* resource = (Resource*)duk_to_pointer(context, 0);
		inst->hasResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResourcesFromFolder(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		String folder = duk_to_string(context, 0);
		bool recursive = duk_to_boolean(context, 1);
		inst->loadResourcesFromFolder(folder,recursive);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		inst->loadResource(path);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_loadResourceWithName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		String name = duk_to_string(context, 1);
		inst->loadResourceWithName(path,name);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResource(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		int resourceType = duk_to_int(context, 0);
		String resourceName = duk_to_string(context, 1);
		inst->getResource(resourceType,resourceName);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_setName(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResourceByPath(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		String resourcePath = duk_to_string(context, 0);
		inst->getResourceByPath(resourcePath);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_Update(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		int elapsed = duk_to_int(context, 0);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_getResources(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		int resourceType = duk_to_int(context, 0);
		inst->getResources(resourceType);
		return 0;
	}

	duk_ret_t Polycode_ResourcePool_checkForChangedFiles(duk_context *context) {
		ResourcePool *inst = (ResourcePool*)duk_to_pointer(context, -1);
		inst->checkForChangedFiles();
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getGlobalPool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		inst->getGlobalPool();
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResourcePoolByName(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getResourcePoolByName(name);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_addResourceLoader(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourceLoader* loader = (ResourceLoader*)duk_to_pointer(context, 0);
		inst->addResourceLoader(loader);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResourceLoaderForExtension(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		String extension = duk_to_string(context, 0);
		inst->getResourceLoaderForExtension(extension);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResourceLoader(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourceLoader* loader = (ResourceLoader*)duk_to_pointer(context, 0);
		inst->removeResourceLoader(loader);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getNumResourceLoaders(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		inst->getNumResourceLoaders();
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResourceLoaderAtIndex(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getResourceLoaderAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_addResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->addResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->removeResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_getResources(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		int resourceType = duk_to_int(context, 0);
		inst->getResources(resourceType);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_removeResource(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		Resource* resource = (Resource*)duk_to_pointer(context, 0);
		inst->removeResource(resource);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_subscribeToResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->subscribeToResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_unsubscibeFromResourcePool(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->unsubscibeFromResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_ResourceManager_Update(duk_context *context) {
		ResourceManager *inst = (ResourceManager*)duk_to_pointer(context, -1);
		int elapsed = duk_to_int(context, 0);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_FontResourceLoader_loadResource(duk_context *context) {
		FontResourceLoader *inst = (FontResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_ProgramResourceLoader_loadResource(duk_context *context) {
		ProgramResourceLoader *inst = (ProgramResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_MeshResourceLoader_loadResource(duk_context *context) {
		MeshResourceLoader *inst = (MeshResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_MaterialResourceLoader_loadResource(duk_context *context) {
		MaterialResourceLoader *inst = (MaterialResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_TextureResourceLoader_loadResource(duk_context *context) {
		TextureResourceLoader *inst = (TextureResourceLoader*)duk_to_pointer(context, -1);
		String path = duk_to_string(context, 0);
		ResourcePool* targetPool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->loadResource(path,targetPool);
		return 0;
	}

	duk_ret_t Polycode_Scene_addEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Entity* entity = (Entity*)duk_to_pointer(context, 0);
		inst->addEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_addChild(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Entity* entity = (Entity*)duk_to_pointer(context, 0);
		inst->addChild(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_removeEntity(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Entity* entity = (Entity*)duk_to_pointer(context, 0);
		inst->removeEntity(entity);
		return 0;
	}

	duk_ret_t Polycode_Scene_getDefaultCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->getDefaultCamera();
		return 0;
	}

	duk_ret_t Polycode_Scene_getActiveCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->getActiveCamera();
		return 0;
	}

	duk_ret_t Polycode_Scene_setActiveCamera(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Camera* camera = (Camera*)duk_to_pointer(context, 0);
		inst->setActiveCamera(camera);
		return 0;
	}

	duk_ret_t Polycode_Scene_enableFog(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		bool enable = duk_to_boolean(context, 0);
		inst->enableFog(enable);
		return 0;
	}

	duk_ret_t Polycode_Scene_setFogProperties(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		int fogMode = duk_to_int(context, 0);
		Color color = *(Color*)duk_to_pointer(context, 1);
		Number density = duk_to_number(context, 2);
		Number startDepth = duk_to_number(context, 3);
		Number endDepth = duk_to_number(context, 4);
		inst->setFogProperties(fogMode,color,density,startDepth,endDepth);
		return 0;
	}

	duk_ret_t Polycode_Scene_setSceneType(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		int newType = duk_to_int(context, 0);
		inst->setSceneType(newType);
		return 0;
	}

	duk_ret_t Polycode_Scene_fixedUpdate(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_Scene_Update(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Scene_setVirtual(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setVirtual(val);
		return 0;
	}

	duk_ret_t Polycode_Scene_isVirtual(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->isVirtual();
		return 0;
	}

	duk_ret_t Polycode_Scene_isEnabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->isEnabled();
		return 0;
	}

	duk_ret_t Polycode_Scene_setEnabled(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		bool enabled = duk_to_boolean(context, 0);
		inst->setEnabled(enabled);
		return 0;
	}

	duk_ret_t Polycode_Scene_Render(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Camera* targetCamera = (Camera*)duk_to_pointer(context, 0);
		RenderBuffer* targetFramebuffer = (RenderBuffer*)duk_to_pointer(context, 1);
		Material* overrideMaterial = (Material*)duk_to_pointer(context, 2);
		bool sendLights = duk_to_boolean(context, 3);
		inst->Render(targetCamera,targetFramebuffer,overrideMaterial,sendLights);
		return 0;
	}

	duk_ret_t Polycode_Scene_setOverrideMaterial(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Material* material = (Material*)duk_to_pointer(context, 0);
		inst->setOverrideMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_Scene_projectRayFromCameraAndViewportCoordinate(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		Camera* camera = (Camera*)duk_to_pointer(context, 0);
		Vector2 coordinate = *(Vector2*)duk_to_pointer(context, 1);
		inst->projectRayFromCameraAndViewportCoordinate(camera,coordinate);
		return 0;
	}

	duk_ret_t Polycode_Scene_addLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		SceneLight* light = (SceneLight*)duk_to_pointer(context, 0);
		inst->addLight(light);
		return 0;
	}

	duk_ret_t Polycode_Scene_removeLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		SceneLight* light = (SceneLight*)duk_to_pointer(context, 0);
		inst->removeLight(light);
		return 0;
	}

	duk_ret_t Polycode_Scene_getNumLights(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->getNumLights();
		return 0;
	}

	duk_ret_t Polycode_Scene_getLight(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getLight(index);
		return 0;
	}

	duk_ret_t Polycode_Scene_doVisibilityChecking(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->doVisibilityChecking(val);
		return 0;
	}

	duk_ret_t Polycode_Scene_doesVisibilityChecking(duk_context *context) {
		Scene *inst = (Scene*)duk_to_pointer(context, -1);
		inst->doesVisibilityChecking();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry_getInstance(duk_context *context) {
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*)duk_to_pointer(context, -1);
		inst->getInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceResourceEntry_reloadResource(duk_context *context) {
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*)duk_to_pointer(context, -1);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_Clone(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_applyClone(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_reloadEntityInstance(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->reloadEntityInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_clearInstance(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->clearInstance();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_parseObjectIntoCurve(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 0);
		BezierCurve* curve = (BezierCurve*)duk_to_pointer(context, 1);
		inst->parseObjectIntoCurve(entry,curve);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_loadObjectEntryIntoEntity(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 0);
		Entity* targetEntity = (Entity*)duk_to_pointer(context, 1);
		int entityFileVersion = duk_to_int(context, 2);
		inst->loadObjectEntryIntoEntity(entry,targetEntity,entityFileVersion);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_loadFromFile(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadFromFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_applySceneMesh(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		ObjectEntry* entry = (ObjectEntry*)duk_to_pointer(context, 0);
		SceneMesh* sceneMesh = (SceneMesh*)duk_to_pointer(context, 1);
		inst->applySceneMesh(entry,sceneMesh);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_linkResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->linkResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLinkedResourePools(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->getNumLinkedResourePools();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getLinkedResourcePoolAtIndex(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getLinkedResourcePoolAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_unlinkResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		ResourcePool* pool = (ResourcePool*)duk_to_pointer(context, 0);
		inst->unlinkResourcePool(pool);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getResourceEntry(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->getResourceEntry();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getTopLevelResourcePool(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->getTopLevelResourcePool();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_hasLayerID(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		char layerID = *(char*)duk_to_pointer(context, 0);
		inst->hasLayerID(layerID);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getNumLayers(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->getNumLayers();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getLayerAtIndex(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getLayerAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_removeLayer(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		SceneEntityInstanceLayer* layer = (SceneEntityInstanceLayer*)duk_to_pointer(context, 0);
		inst->removeLayer(layer);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_createNewLayer(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->createNewLayer(name);
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstance_getFileName(duk_context *context) {
		SceneEntityInstance *inst = (SceneEntityInstance*)duk_to_pointer(context, -1);
		inst->getFileName();
		return 0;
	}

	duk_ret_t Polycode_SceneEntityInstanceLayer_setLayerVisibility(duk_context *context) {
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setLayerVisibility(val);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_Clone(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_applyClone(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_setImageCoordinates(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number width = duk_to_number(context, 2);
		Number height = duk_to_number(context, 3);
		Number realWidth = duk_to_number(context, 4);
		Number realHeight = duk_to_number(context, 5);
		inst->setImageCoordinates(x,y,width,height,realWidth,realHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneImage_getImageWidth(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, -1);
		inst->getImageWidth();
		return 0;
	}

	duk_ret_t Polycode_SceneImage_getImageHeight(duk_context *context) {
		SceneImage *inst = (SceneImage*)duk_to_pointer(context, -1);
		inst->getImageHeight();
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getText(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		inst->getText();
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_setLabelActualHeight(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		Number actualHeight = duk_to_number(context, 0);
		inst->setLabelActualHeight(actualHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getLabelActualHeight(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		inst->getLabelActualHeight();
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_Render(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getTextWidthForString(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		String text = duk_to_string(context, 0);
		inst->getTextWidthForString(text);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_setText(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		String newText = duk_to_string(context, 0);
		inst->setText(newText);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_Clone(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_applyClone(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_updateFromLabel(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		inst->updateFromLabel();
		return 0;
	}

	duk_ret_t Polycode_SceneLabel_getLabel(duk_context *context) {
		SceneLabel *inst = (SceneLabel*)duk_to_pointer(context, -1);
		inst->getLabel();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getIntensity(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getIntensity();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setIntensity(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number newIntensity = duk_to_number(context, 0);
		inst->setIntensity(newIntensity);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number constantAttenuation = duk_to_number(context, 0);
		Number linearAttenuation = duk_to_number(context, 1);
		Number quadraticAttenuation = duk_to_number(context, 2);
		inst->setAttenuation(constantAttenuation,linearAttenuation,quadraticAttenuation);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getConstantAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getConstantAttenuation();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLinearAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getLinearAttenuation();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getQuadraticAttenuation(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getQuadraticAttenuation();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getType();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_renderDepthMap(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Scene* scene = (Scene*)duk_to_pointer(context, 0);
		inst->renderDepthMap(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getZBufferTexture(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getZBufferTexture();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setSpecularLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->setSpecularLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setDiffuseLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->setDiffuseLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setLightColor(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number r = duk_to_number(context, 0);
		Number g = duk_to_number(context, 1);
		Number b = duk_to_number(context, 2);
		Number a = duk_to_number(context, 3);
		inst->setLightColor(r,g,b,a);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setSpotlightProperties(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number spotlightCutoff = duk_to_number(context, 0);
		Number spotlightExponent = duk_to_number(context, 1);
		inst->setSpotlightProperties(spotlightCutoff,spotlightExponent);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightCutoff(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getSpotlightCutoff();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightExponent(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getSpotlightExponent();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_enableShadows(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		int resolution = duk_to_int(context, 1);
		inst->enableShadows(val,resolution);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setShadowMapFOV(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Number fov = duk_to_number(context, 0);
		inst->setShadowMapFOV(fov);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapFOV(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getShadowMapFOV();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getShadowMapResolution(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getShadowMapResolution();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_areShadowsEnabled(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->areShadowsEnabled();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getLightType();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setLightImportance(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		int newImportance = duk_to_int(context, 0);
		inst->setLightImportance(newImportance);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightImportance(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getLightImportance();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setLightType(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		int lightType = duk_to_int(context, 0);
		inst->setLightType(lightType);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_Clone(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_applyClone(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getParentScene(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getParentScene();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_setParentScene(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		Scene* scene = (Scene*)duk_to_pointer(context, 0);
		inst->setParentScene(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getSpotlightCamera(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getSpotlightCamera();
		return 0;
	}

	duk_ret_t Polycode_SceneLight_getLightInfo(duk_context *context) {
		SceneLight *inst = (SceneLight*)duk_to_pointer(context, -1);
		inst->getLightInfo();
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_getWorldPointAt(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, -1);
		Number t = duk_to_number(context, 0);
		inst->getWorldPointAt(t);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_Update(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_Clone(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_applyClone(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneCurve_getCurve(duk_context *context) {
		SceneCurve *inst = (SceneCurve*)duk_to_pointer(context, -1);
		inst->getCurve();
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setStart(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, -1);
		Vector3 startp = *(Vector3*)duk_to_pointer(context, 0);
		inst->setStart(startp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_setEnd(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, -1);
		Vector3 endp = *(Vector3*)duk_to_pointer(context, 0);
		inst->setEnd(endp);
		return 0;
	}

	duk_ret_t Polycode_SceneLine_Update(duk_context *context) {
		SceneLine *inst = (SceneLine*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_addScene(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		Scene* newScene = (Scene*)duk_to_pointer(context, 0);
		inst->addScene(newScene);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_removeScene(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		Scene* scene = (Scene*)duk_to_pointer(context, 0);
		inst->removeScene(scene);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_Update(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_fixedUpdate(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		inst->fixedUpdate();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_Render(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		Rectangle viewport = *(Rectangle*)duk_to_pointer(context, 0);
		inst->Render(viewport);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_renderVirtual(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		inst->renderVirtual();
		return 0;
	}

	duk_ret_t Polycode_SceneManager_registerRenderTexture(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*)duk_to_pointer(context, 0);
		inst->registerRenderTexture(renderTexture);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_unregisterRenderTexture(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*)duk_to_pointer(context, 0);
		inst->unregisterRenderTexture(renderTexture);
		return 0;
	}

	duk_ret_t Polycode_SceneManager_setRenderer(duk_context *context) {
		SceneManager *inst = (SceneManager*)duk_to_pointer(context, -1);
		Renderer* renderer = (Renderer*)duk_to_pointer(context, 0);
		inst->setRenderer(renderer);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_Render(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getShaderPass(index);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getNumShaderPasses(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getNumShaderPasses();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_addShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		ShaderPass pass = *(ShaderPass*)duk_to_pointer(context, 0);
		inst->addShaderPass(pass);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_removeShaderPass(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		int shaderIndex = duk_to_int(context, 0);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getMesh();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getMaterial();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_loadSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadSkeleton(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_clearMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->clearMaterial();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Material* material = (Material*)duk_to_pointer(context, 0);
		inst->setMaterial(material);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_rebuildAttributes(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->rebuildAttributes();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMaterialByName(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		String materialName = duk_to_string(context, 0);
		ResourcePool* resourcePool = (ResourcePool*)duk_to_pointer(context, 1);
		inst->setMaterialByName(materialName,resourcePool);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setMesh(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Mesh* mesh = (Mesh*)duk_to_pointer(context, 0);
		inst->setMesh(mesh);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Skeleton* skeleton = (Skeleton*)duk_to_pointer(context, 0);
		inst->setSkeleton(skeleton);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getSkeleton(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getSkeleton();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_applySkeletonLocally(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->applySkeletonLocally();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setLineWidth(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Number newWidth = duk_to_number(context, 0);
		inst->setLineWidth(newWidth);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getFilename(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getFilename();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setFilename(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->setFilename(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_loadFromFile(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadFromFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_customHitDetection(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Ray ray = *(Ray*)duk_to_pointer(context, 0);
		inst->customHitDetection(ray);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_setForceMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		bool forceMaterial = duk_to_boolean(context, 0);
		inst->setForceMaterial(forceMaterial);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_getForceMaterial(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		inst->getForceMaterial();
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_Clone(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneMesh_applyClone(duk_context *context) {
		SceneMesh *inst = (SceneMesh*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_setPrimitiveOptions(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		int type = duk_to_int(context, 0);
		Number v1 = duk_to_number(context, 1);
		Number v2 = duk_to_number(context, 2);
		Number v3 = duk_to_number(context, 3);
		Number v4 = duk_to_number(context, 4);
		Number v5 = duk_to_number(context, 5);
		inst->setPrimitiveOptions(type,v1,v2,v3,v4,v5);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_recreatePrimitive(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->recreatePrimitive();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveType(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveType();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter1(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveParameter1();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter2(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveParameter2();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter3(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveParameter3();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter4(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveParameter4();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_getPrimitiveParameter5(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		inst->getPrimitiveParameter5();
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_Clone(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_ScenePrimitive_applyClone(duk_context *context) {
		ScenePrimitive *inst = (ScenePrimitive*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->getTargetTexture();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getFilterColorBufferTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->getFilterColorBufferTexture();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getFilterZBufferTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->getFilterZBufferTexture();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_Render(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->Render();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_saveToImage(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->saveToImage();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_resizeRenderTexture(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		int newWidth = duk_to_int(context, 0);
		int newHeight = duk_to_int(context, 1);
		inst->resizeRenderTexture(newWidth,newHeight);
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetScene(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->getTargetScene();
		return 0;
	}

	duk_ret_t Polycode_SceneRenderTexture_getTargetCamera(duk_context *context) {
		SceneRenderTexture *inst = (SceneRenderTexture*)duk_to_pointer(context, -1);
		inst->getTargetCamera();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_Update(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_Clone(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_applyClone(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_isDirectionalSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		inst->isDirectionalSound();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_setDirectionalSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setDirectionalSound(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_getSound(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		inst->getSound();
		return 0;
	}

	duk_ret_t Polycode_SceneSound_setLoopOnLoad(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setLoopOnLoad(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSound_getLoopOnLoad(duk_context *context) {
		SceneSound *inst = (SceneSound*)duk_to_pointer(context, -1);
		inst->getLoopOnLoad();
		return 0;
	}

	duk_ret_t Polycode_SceneSoundListener_Update(duk_context *context) {
		SceneSoundListener *inst = (SceneSoundListener*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_Clone(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		bool deepClone = duk_to_boolean(context, 0);
		bool ignoreEditorOnly = duk_to_boolean(context, 1);
		inst->Clone(deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_applyClone(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		Entity* clone = (Entity*)duk_to_pointer(context, 0);
		bool deepClone = duk_to_boolean(context, 1);
		bool ignoreEditorOnly = duk_to_boolean(context, 2);
		inst->applyClone(clone,deepClone,ignoreEditorOnly);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getSpriteSet(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getSpriteSet();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentSprite(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getCurrentSprite();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteSet(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		SpriteSet* spriteSet = (SpriteSet*)duk_to_pointer(context, 0);
		inst->setSpriteSet(spriteSet);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteByName(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		String spriteName = duk_to_string(context, 0);
		inst->setSpriteByName(spriteName);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setCurrentFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		int frameIndex = duk_to_int(context, 0);
		inst->setCurrentFrame(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getCurrentFrame();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_Update(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_Render(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*)duk_to_pointer(context, 0);
		inst->Render(buffer);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getSpriteBoundingBox(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getSpriteBoundingBox();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setPaused(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setPaused(val);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_isPaused(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->isPaused();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSprite(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		Sprite* spriteEntry = (Sprite*)duk_to_pointer(context, 0);
		inst->setSprite(spriteEntry);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteState(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		SpriteState* spriteState = (SpriteState*)duk_to_pointer(context, 0);
		int startingFrame = duk_to_int(context, 1);
		bool playOnce = duk_to_boolean(context, 2);
		inst->setSpriteState(spriteState,startingFrame,playOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setSpriteStateByName(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		int startingFrame = duk_to_int(context, 1);
		bool playOnce = duk_to_boolean(context, 2);
		inst->setSpriteStateByName(name,startingFrame,playOnce);
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getCurrentSpriteState(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getCurrentSpriteState();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_getStartOnRandomFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		inst->getStartOnRandomFrame();
		return 0;
	}

	duk_ret_t Polycode_SceneSprite_setStartOnRandomFrame(duk_context *context) {
		SceneSprite *inst = (SceneSprite*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->setStartOnRandomFrame(val);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_Sprite_setName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Sprite_addSpriteState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		SpriteState* state = (SpriteState*)duk_to_pointer(context, 0);
		inst->addSpriteState(state);
		return 0;
	}

	duk_ret_t Polycode_Sprite_removeSpriteState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		SpriteState* state = (SpriteState*)duk_to_pointer(context, 0);
		inst->removeSpriteState(state);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getNumStates(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		inst->getNumStates();
		return 0;
	}

	duk_ret_t Polycode_Sprite_getState(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getState(index);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getStateByName(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getStateByName(name);
		return 0;
	}

	duk_ret_t Polycode_Sprite_setParentSpritSet(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		SpriteSet* spriteSet = (SpriteSet*)duk_to_pointer(context, 0);
		inst->setParentSpritSet(spriteSet);
		return 0;
	}

	duk_ret_t Polycode_Sprite_getParentSpriteSet(duk_context *context) {
		Sprite *inst = (Sprite*)duk_to_pointer(context, -1);
		inst->getParentSpriteSet();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		Texture* texture = (Texture*)duk_to_pointer(context, 0);
		inst->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		inst->getTexture();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_loadTexture(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		String imageFileName = duk_to_string(context, 0);
		inst->loadTexture(imageFileName);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteEntry(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		Sprite* newEntry = (Sprite*)duk_to_pointer(context, 0);
		inst->addSpriteEntry(newEntry);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumSpriteEntries(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		inst->getNumSpriteEntries();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteEntry(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getSpriteEntry(index);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_removeSprite(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		Sprite* sprite = (Sprite*)duk_to_pointer(context, 0);
		inst->removeSprite(sprite);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_loadSpriteSet(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadSpriteSet(fileName);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_addSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 0);
		bool assignID = duk_to_boolean(context, 1);
		inst->addSpriteFrame(frame,assignID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getNumFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		inst->getNumFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getSpriteFrame(index);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteFrameByID(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int frameID = duk_to_int(context, 0);
		inst->getSpriteFrameByID(frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_removeFrameByID(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int frameID = duk_to_int(context, 0);
		inst->removeFrameByID(frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_setSpriteFrame(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		SpriteFrame frame = *(SpriteFrame*)duk_to_pointer(context, 0);
		inst->setSpriteFrame(frame);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_clearFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		inst->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createGridFrames(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int xCount = duk_to_int(context, 0);
		int yCount = duk_to_int(context, 1);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 2);
		inst->createGridFrames(xCount,yCount,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_createFramesFromIslands(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		int minDistance = duk_to_int(context, 0);
		Vector2 defaultAnchor = *(Vector2*)duk_to_pointer(context, 1);
		inst->createFramesFromIslands(minDistance,defaultAnchor);
		return 0;
	}

	duk_ret_t Polycode_SpriteSet_getSpriteByName(duk_context *context) {
		SpriteSet *inst = (SpriteSet*)duk_to_pointer(context, -1);
		String spriteName = duk_to_string(context, 0);
		inst->getSpriteByName(spriteName);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setName(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getName(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getNumFrameIDs(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getNumFrameIDs();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getFrameIDAtIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getFrameIDAtIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getMeshForFrameIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getMeshForFrameIndex(index);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_insertFrame(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		int frameID = duk_to_int(context, 1);
		inst->insertFrame(index,frameID);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_removeFrameByIndex(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		int frameIndex = duk_to_int(context, 0);
		inst->removeFrameByIndex(frameIndex);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_clearFrames(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->clearFrames();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setPixelsPerUnit(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		Number ppu = duk_to_number(context, 0);
		inst->setPixelsPerUnit(ppu);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getPixelsPerUnit(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getPixelsPerUnit();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_rebuildStateMeshes(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->rebuildStateMeshes();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setStateFPS(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		Number fps = duk_to_number(context, 0);
		inst->setStateFPS(fps);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getStateFPS(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getStateFPS();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getLargestFrameBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getLargestFrameBoundingBox();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		Vector2 boundingBox = *(Vector2*)duk_to_pointer(context, 0);
		inst->setBoundingBox(boundingBox);
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getBoundingBox(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getBoundingBox();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_getSpriteOffset(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		inst->getSpriteOffset();
		return 0;
	}

	duk_ret_t Polycode_SpriteState_setSpriteOffset(duk_context *context) {
		SpriteState *inst = (SpriteState*)duk_to_pointer(context, -1);
		Vector2 offset = *(Vector2*)duk_to_pointer(context, 0);
		inst->setSpriteOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_Shader_getType(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		inst->getType();
		return 0;
	}

	duk_ret_t Polycode_Shader_setName(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->setName(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_getName(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_Shader_getParamPointer(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getParamPointer(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_getAttribPointer(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getAttribPointer(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_reload(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		inst->reload();
		return 0;
	}

	duk_ret_t Polycode_Shader_getExpectedParamType(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getExpectedParamType(name);
		return 0;
	}

	duk_ret_t Polycode_Shader_setVertexProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		ShaderProgram* vp = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->setVertexProgram(vp);
		return 0;
	}

	duk_ret_t Polycode_Shader_setFragmentProgram(duk_context *context) {
		Shader *inst = (Shader*)duk_to_pointer(context, -1);
		ShaderProgram* fp = (ShaderProgram*)duk_to_pointer(context, 0);
		inst->setFragmentProgram(fp);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_Copy(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->Copy();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getNumber(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getNumber();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector2(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getVector2();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getVector3(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getVector3();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getMatrix4(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getMatrix4();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getColor(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getColor();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setNumber(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		inst->setNumber(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector2(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Vector2 x = *(Vector2*)duk_to_pointer(context, 0);
		inst->setVector2(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setVector3(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Vector3 x = *(Vector3*)duk_to_pointer(context, 0);
		inst->setVector3(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setMatrix4(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Matrix4 x = *(Matrix4*)duk_to_pointer(context, 0);
		inst->setMatrix4(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setColor(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Color x = *(Color*)duk_to_pointer(context, 0);
		inst->setColor(x);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setTexture(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Texture* texture = (Texture*)duk_to_pointer(context, 0);
		inst->setTexture(texture);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getTexture(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getTexture();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setCubemap(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		Cubemap* cubemap = (Cubemap*)duk_to_pointer(context, 0);
		inst->setCubemap(cubemap);
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_getCubemap(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		inst->getCubemap();
		return 0;
	}

	duk_ret_t Polycode_LocalShaderParam_setParamValueFromString(duk_context *context) {
		LocalShaderParam *inst = (LocalShaderParam*)duk_to_pointer(context, -1);
		int type = duk_to_int(context, 0);
		String pvalue = duk_to_string(context, 1);
		inst->setParamValueFromString(type,pvalue);
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram_reloadProgram(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, -1);
		inst->reloadProgram();
		return 0;
	}

	duk_ret_t Polycode_ShaderProgram_reloadResource(duk_context *context) {
		ShaderProgram *inst = (ShaderProgram*)duk_to_pointer(context, -1);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_copyTo(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		ShaderBinding* targetBinding = (ShaderBinding*)duk_to_pointer(context, 0);
		inst->copyTo(targetBinding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int type = duk_to_int(context, 0);
		String name = duk_to_string(context, 1);
		inst->addParam(type,name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addParamPointer(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int type = duk_to_int(context, 0);
		String name = duk_to_string(context, 1);
		void* ptr = (void*)duk_to_pointer(context, 2);
		inst->addParamPointer(type,name,ptr);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumLocalParams(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumLocalParams();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getLocalParam(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getLocalParamByName(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getLocalParamByName(name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_removeParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->removeParam(name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_loadTextureForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String paramName = duk_to_string(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->loadTextureForParam(paramName,fileName);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_setTextureForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String paramName = duk_to_string(context, 0);
		Texture* texture = (Texture*)duk_to_pointer(context, 1);
		inst->setTextureForParam(paramName,texture);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_setCubemapForParam(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String paramName = duk_to_string(context, 0);
		Cubemap* cubemap = (Cubemap*)duk_to_pointer(context, 1);
		inst->setCubemapForParam(paramName,cubemap);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumAttributeBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumAttributeBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getAttributeBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getAttributeBinding(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addAttributeBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		VertexDataArray* dataArray = (VertexDataArray*)duk_to_pointer(context, 1);
		inst->addAttributeBinding(name,dataArray);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getAttributeBindingByName(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getAttributeBindingByName(name);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_addRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		RenderTargetBinding* binding = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->addRenderTargetBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_removeRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		RenderTargetBinding* binding = (RenderTargetBinding*)duk_to_pointer(context, 0);
		inst->removeRenderTargetBinding(binding);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumRenderTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumRenderTargetBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getRenderTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getRenderTargetBinding(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumInTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumInTargetBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getInTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getInTargetBinding(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumColorTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumColorTargetBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getColorTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getColorTargetBinding(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumDepthTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumDepthTargetBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getDepthTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getDepthTargetBinding(index);
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getNumOutTargetBindings(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		inst->getNumOutTargetBindings();
		return 0;
	}

	duk_ret_t Polycode_ShaderBinding_getOutTargetBinding(duk_context *context) {
		ShaderBinding *inst = (ShaderBinding*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getOutTargetBinding(index);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_addBoneTrack(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		BoneTrack* boneTrack = (BoneTrack*)duk_to_pointer(context, 0);
		inst->addBoneTrack(boneTrack);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getName(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->getName();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Play(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		bool once = duk_to_boolean(context, 0);
		inst->Play(once);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Stop(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Reset(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_Update(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setSpeed(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		Number speed = duk_to_number(context, 0);
		inst->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_setWeight(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		Number newWeight = duk_to_number(context, 0);
		inst->setWeight(newWeight);
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_getWeight(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->getWeight();
		return 0;
	}

	duk_ret_t Polycode_SkeletonAnimation_isPlaying(duk_context *context) {
		SkeletonAnimation *inst = (SkeletonAnimation*)duk_to_pointer(context, -1);
		inst->isPlaying();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_loadSkeleton(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadSkeleton(fileName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_playAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String animName = duk_to_string(context, 0);
		Number weight = duk_to_number(context, 1);
		bool once = duk_to_boolean(context, 2);
		bool restartIfPlaying = duk_to_boolean(context, 3);
		inst->playAnimationByName(animName,weight,once,restartIfPlaying);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_playAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 0);
		Number weight = duk_to_number(context, 1);
		bool once = duk_to_boolean(context, 2);
		bool restartIfPlaying = duk_to_boolean(context, 3);
		inst->playAnimation(animation,weight,once,restartIfPlaying);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_setBaseAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String animName = duk_to_string(context, 0);
		inst->setBaseAnimationByName(animName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_setBaseAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 0);
		inst->setBaseAnimation(animation);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAllAnimations(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		inst->stopAllAnimations();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBaseAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		inst->getBaseAnimation();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_addAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		String fileName = duk_to_string(context, 1);
		inst->addAnimation(name,fileName);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getAnimation(name);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAnimationByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->stopAnimationByName(name);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_stopAnimation(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		SkeletonAnimation* animation = (SkeletonAnimation*)duk_to_pointer(context, 0);
		inst->stopAnimation(animation);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_Update(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneByName(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		String name = duk_to_string(context, 0);
		inst->getBoneByName(name);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_bonesVisible(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		bool val = duk_to_boolean(context, 0);
		inst->bonesVisible(val);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getNumBones(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		inst->getNumBones();
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		int index = duk_to_int(context, 0);
		inst->getBone(index);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_addBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		Bone* bone = (Bone*)duk_to_pointer(context, 0);
		inst->addBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_removeBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		Bone* bone = (Bone*)duk_to_pointer(context, 0);
		inst->removeBone(bone);
		return 0;
	}

	duk_ret_t Polycode_Skeleton_getBoneIndexByBone(duk_context *context) {
		Skeleton *inst = (Skeleton*)duk_to_pointer(context, -1);
		Bone* bone = (Bone*)duk_to_pointer(context, 0);
		inst->getBoneIndexByBone(bone);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Play(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, -1);
		bool once = duk_to_boolean(context, 0);
		inst->Play(once);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Stop(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, -1);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Update(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, -1);
		Number elapsed = duk_to_number(context, 0);
		inst->Update(elapsed);
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_Reset(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, -1);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_BoneTrack_setSpeed(duk_context *context) {
		BoneTrack *inst = (BoneTrack*)duk_to_pointer(context, -1);
		Number speed = duk_to_number(context, 0);
		inst->setSpeed(speed);
		return 0;
	}

	duk_ret_t Polycode_Sound_getSampleAsNumber(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		int offset = duk_to_int(context, 0);
		int channel = duk_to_int(context, 1);
		inst->getSampleAsNumber(offset,channel);
		return 0;
	}

	duk_ret_t Polycode_Sound_loadFile(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadFile(fileName);
		return 0;
	}

	duk_ret_t Polycode_Sound_Play(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		bool loop = duk_to_boolean(context, 0);
		bool restartSound = duk_to_boolean(context, 1);
		inst->Play(loop,restartSound);
		return 0;
	}

	duk_ret_t Polycode_Sound_Stop(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->Stop();
		return 0;
	}

	duk_ret_t Polycode_Sound_setVolume(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number newVolume = duk_to_number(context, 0);
		inst->setVolume(newVolume);
		return 0;
	}

	duk_ret_t Polycode_Sound_getVolume(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getVolume();
		return 0;
	}

	duk_ret_t Polycode_Sound_setPitch(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number newPitch = duk_to_number(context, 0);
		inst->setPitch(newPitch);
		return 0;
	}

	duk_ret_t Polycode_Sound_getPitch(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getPitch();
		return 0;
	}

	duk_ret_t Polycode_Sound_isPlaying(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->isPlaying();
		return 0;
	}

	duk_ret_t Polycode_Sound_isLooped(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->isLooped();
		return 0;
	}

	duk_ret_t Polycode_Sound_setIsPositional(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		bool isPositional = duk_to_boolean(context, 0);
		inst->setIsPositional(isPositional);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundPosition(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 0);
		inst->setSoundPosition(position);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundVelocity(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Vector3 velocity = *(Vector3*)duk_to_pointer(context, 0);
		inst->setSoundVelocity(velocity);
		return 0;
	}

	duk_ret_t Polycode_Sound_setSoundDirection(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Vector3 direction = *(Vector3*)duk_to_pointer(context, 0);
		inst->setSoundDirection(direction);
		return 0;
	}

	duk_ret_t Polycode_Sound_setOffset(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		int offset = duk_to_int(context, 0);
		inst->setOffset(offset);
		return 0;
	}

	duk_ret_t Polycode_Sound_getFileName(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getFileName();
		return 0;
	}

	duk_ret_t Polycode_Sound_getPlaybackDuration(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getPlaybackDuration();
		return 0;
	}

	duk_ret_t Polycode_Sound_getPlaybackTime(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getPlaybackTime();
		return 0;
	}

	duk_ret_t Polycode_Sound_seekTo(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number time = duk_to_number(context, 0);
		inst->seekTo(time);
		return 0;
	}

	duk_ret_t Polycode_Sound_getOffset(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getOffset();
		return 0;
	}

	duk_ret_t Polycode_Sound_getSampleLength(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getSampleLength();
		return 0;
	}

	duk_ret_t Polycode_Sound_getFrequency(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getFrequency();
		return 0;
	}

	duk_ret_t Polycode_Sound_setPositionalProperties(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number referenceDistance = duk_to_number(context, 0);
		Number maxDistance = duk_to_number(context, 1);
		inst->setPositionalProperties(referenceDistance,maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setReferenceDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number referenceDistance = duk_to_number(context, 0);
		inst->setReferenceDistance(referenceDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_setMaxDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		Number maxDistance = duk_to_number(context, 0);
		inst->setMaxDistance(maxDistance);
		return 0;
	}

	duk_ret_t Polycode_Sound_getReferenceDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getReferenceDistance();
		return 0;
	}

	duk_ret_t Polycode_Sound_getMaxDistance(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		inst->getMaxDistance();
		return 0;
	}

	duk_ret_t Polycode_Sound_loadBytes(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		char* data = (char*)duk_to_pointer(context, 0);
		int size = duk_to_int(context, 1);
		int channels = duk_to_int(context, 2);
		int freq = duk_to_int(context, 3);
		SoundFormat format = *(SoundFormat*)duk_to_pointer(context, 4);
		inst->loadBytes(data,size,channels,freq,format);
		return 0;
	}

	duk_ret_t Polycode_Sound_loadWAV(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadWAV(fileName);
		return 0;
	}

	duk_ret_t Polycode_Sound_loadOGG(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		String fileName = duk_to_string(context, 0);
		inst->loadOGG(fileName);
		return 0;
	}

	duk_ret_t Polycode_Sound_soundCheck(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		bool result = duk_to_boolean(context, 0);
		String err = duk_to_string(context, 1);
		inst->soundCheck(result,err);
		return 0;
	}

	duk_ret_t Polycode_Sound_updateStream(duk_context *context) {
		Sound *inst = (Sound*)duk_to_pointer(context, -1);
		int streamCount = duk_to_int(context, 0);
		inst->updateStream(streamCount);
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource_getNumChannels(duk_context *context) {
		AudioStreamingSource *inst = (AudioStreamingSource*)duk_to_pointer(context, -1);
		inst->getNumChannels();
		return 0;
	}

	duk_ret_t Polycode_AudioStreamingSource_getFrequency(duk_context *context) {
		AudioStreamingSource *inst = (AudioStreamingSource*)duk_to_pointer(context, -1);
		inst->getFrequency();
		return 0;
	}

	duk_ret_t Polycode_AudioMixer_mixIntoBuffer(duk_context *context) {
		AudioMixer *inst = (AudioMixer*)duk_to_pointer(context, -1);
		int16_t* buffer = (int16_t*)duk_to_pointer(context, 0);
		int numSamples = duk_to_int(context, 1);
		inst->mixIntoBuffer(buffer,numSamples);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerPosition(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		Vector3 position = *(Vector3*)duk_to_pointer(context, 0);
		inst->setListenerPosition(position);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setListenerOrientation(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		Vector3 orientation = *(Vector3*)duk_to_pointer(context, 0);
		Vector3 upVector = *(Vector3*)duk_to_pointer(context, 1);
		inst->setListenerOrientation(orientation,upVector);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_recordSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		int rate = duk_to_int(context, 0);
		int sampleSize = duk_to_int(context, 1);
		inst->recordSound(rate,sampleSize);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_stopRecording(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		bool generateFloatBuffer = duk_to_boolean(context, 0);
		inst->stopRecording(generateFloatBuffer);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setAudioInterface(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		AudioInterface* audioInterface = (AudioInterface*)duk_to_pointer(context, 0);
		inst->setAudioInterface(audioInterface);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_Update(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		inst->Update();
		return 0;
	}

	duk_ret_t Polycode_SoundManager_setGlobalVolume(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		Number globalVolume = duk_to_number(context, 0);
		inst->setGlobalVolume(globalVolume);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_registerSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		Sound* sound = (Sound*)duk_to_pointer(context, 0);
		inst->registerSound(sound);
		return 0;
	}

	duk_ret_t Polycode_SoundManager_unregisterSound(duk_context *context) {
		SoundManager *inst = (SoundManager*)duk_to_pointer(context, -1);
		Sound* sound = (Sound*)duk_to_pointer(context, 0);
		inst->unregisterSound(sound);
		return 0;
	}

	duk_ret_t Polycode_String_size(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->size();
		return 0;
	}

	duk_ret_t Polycode_String_length(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->length();
		return 0;
	}

	duk_ret_t Polycode_String_substr(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		size_t pos = *(size_t*)duk_to_pointer(context, 0);
		size_t n = *(size_t*)duk_to_pointer(context, 1);
		inst->substr(pos,n);
		return 0;
	}

	duk_ret_t Polycode_String_rfind(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		inst->rfind(str,pos);
		return 0;
	}

	duk_ret_t Polycode_String_find(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		inst->find(str,pos);
		return 0;
	}

	duk_ret_t Polycode_String_find_last_of(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		inst->find_last_of(str,pos);
		return 0;
	}

	duk_ret_t Polycode_String_find_first_of(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String str = duk_to_string(context, 0);
		size_t pos = *(size_t*)duk_to_pointer(context, 1);
		inst->find_first_of(str,pos);
		return 0;
	}

	duk_ret_t Polycode_String_toLowerCase(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->toLowerCase();
		return 0;
	}

	duk_ret_t Polycode_String_toUpperCase(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->toUpperCase();
		return 0;
	}

	duk_ret_t Polycode_String_split(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String delim = duk_to_string(context, 0);
		inst->split(delim);
		return 0;
	}

	duk_ret_t Polycode_String_replace(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		String what = duk_to_string(context, 0);
		String withWhat = duk_to_string(context, 1);
		inst->replace(what,withWhat);
		return 0;
	}

	duk_ret_t Polycode_String_toNumber(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->toNumber();
		return 0;
	}

	duk_ret_t Polycode_String_toInteger(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->toInteger();
		return 0;
	}

	duk_ret_t Polycode_String_c_str(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->c_str();
		return 0;
	}

	duk_ret_t Polycode_String_getDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		int encoding = duk_to_int(context, 0);
		inst->getDataWithEncoding(encoding);
		return 0;
	}

	duk_ret_t Polycode_String_getWDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		int encoding = duk_to_int(context, 0);
		inst->getWDataWithEncoding(encoding);
		return 0;
	}

	duk_ret_t Polycode_String_append(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		char c = *(char*)duk_to_pointer(context, 0);
		inst->append(c);
		return 0;
	}

	duk_ret_t Polycode_String_getDataSizeWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		int encoding = duk_to_int(context, 0);
		inst->getDataSizeWithEncoding(encoding);
		return 0;
	}

	duk_ret_t Polycode_String_setDataWithEncoding(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		char* data = (char*)duk_to_pointer(context, 0);
		int encoding = duk_to_int(context, 1);
		inst->setDataWithEncoding(data,encoding);
		return 0;
	}

	duk_ret_t Polycode_String_isNumber(duk_context *context) {
		String *inst = (String*)duk_to_pointer(context, -1);
		inst->isNumber();
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer_getWidth(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, -1);
		inst->getWidth();
		return 0;
	}

	duk_ret_t Polycode_RenderBuffer_getHeight(duk_context *context) {
		RenderBuffer *inst = (RenderBuffer*)duk_to_pointer(context, -1);
		inst->getHeight();
		return 0;
	}

	duk_ret_t Polycode_Texture_reloadResource(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		inst->reloadResource();
		return 0;
	}

	duk_ret_t Polycode_Texture_setImageData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		Image* data = (Image*)duk_to_pointer(context, 0);
		inst->setImageData(data);
		return 0;
	}

	duk_ret_t Polycode_Texture_getTextureData(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		inst->getTextureData();
		return 0;
	}

	duk_ret_t Polycode_Texture_getWidth(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		inst->getWidth();
		return 0;
	}

	duk_ret_t Polycode_Texture_getHeight(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		inst->getHeight();
		return 0;
	}

	duk_ret_t Polycode_Texture_setCreateMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		bool createMipmapsIn = duk_to_boolean(context, 0);
		inst->setCreateMipmaps(createMipmapsIn);
		return 0;
	}

	duk_ret_t Polycode_Texture_getCreateMipmaps(duk_context *context) {
		Texture *inst = (Texture*)duk_to_pointer(context, -1);
		inst->getCreateMipmaps();
		return 0;
	}

	duk_ret_t Polycode_Timer_Pause(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		bool paused = duk_to_boolean(context, 0);
		inst->Pause(paused);
		return 0;
	}

	duk_ret_t Polycode_Timer_isPaused(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		inst->isPaused();
		return 0;
	}

	duk_ret_t Polycode_Timer_getTicks(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		inst->getTicks();
		return 0;
	}

	duk_ret_t Polycode_Timer_Update(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		int ticks = duk_to_int(context, 0);
		inst->Update(ticks);
		return 0;
	}

	duk_ret_t Polycode_Timer_Reset(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		inst->Reset();
		return 0;
	}

	duk_ret_t Polycode_Timer_hasElapsed(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		inst->hasElapsed();
		return 0;
	}

	duk_ret_t Polycode_Timer_getElapsedf(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		inst->getElapsedf();
		return 0;
	}

	duk_ret_t Polycode_Timer_setTimerInterval(duk_context *context) {
		Timer *inst = (Timer*)duk_to_pointer(context, -1);
		int msecs = duk_to_int(context, 0);
		inst->setTimerInterval(msecs);
		return 0;
	}

	duk_ret_t Polycode_Vector2_set(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		inst->set(x,y);
		return 0;
	}

	duk_ret_t Polycode_Vector2_distance(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 0);
		inst->distance(vec2);
		return 0;
	}

	duk_ret_t Polycode_Vector2_length(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		inst->length();
		return 0;
	}

	duk_ret_t Polycode_Vector2_dot(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		Vector2 u = *(Vector2*)duk_to_pointer(context, 0);
		inst->dot(u);
		return 0;
	}

	duk_ret_t Polycode_Vector2_crossProduct(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 0);
		inst->crossProduct(vec2);
		return 0;
	}

	duk_ret_t Polycode_Vector2_angle(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		Vector2 vec2 = *(Vector2*)duk_to_pointer(context, 0);
		inst->angle(vec2);
		return 0;
	}

	duk_ret_t Polycode_Vector2_Normalize(duk_context *context) {
		Vector2 *inst = (Vector2*)duk_to_pointer(context, -1);
		inst->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector3_set(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		inst->set(x,y,z);
		return 0;
	}

	duk_ret_t Polycode_Vector3_distance(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 0);
		inst->distance(vec2);
		return 0;
	}

	duk_ret_t Polycode_Vector3_angleBetween(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Vector3 dest = *(Vector3*)duk_to_pointer(context, 0);
		inst->angleBetween(dest);
		return 0;
	}

	duk_ret_t Polycode_Vector3_length(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		inst->length();
		return 0;
	}

	duk_ret_t Polycode_Vector3_lengthSquared(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		inst->lengthSquared();
		return 0;
	}

	duk_ret_t Polycode_Vector3_setLength(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Number newLength = duk_to_number(context, 0);
		inst->setLength(newLength);
		return 0;
	}

	duk_ret_t Polycode_Vector3_dot(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Vector3 u = *(Vector3*)duk_to_pointer(context, 0);
		inst->dot(u);
		return 0;
	}

	duk_ret_t Polycode_Vector3_crossProduct(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		Vector3 vec2 = *(Vector3*)duk_to_pointer(context, 0);
		inst->crossProduct(vec2);
		return 0;
	}

	duk_ret_t Polycode_Vector3_Normalize(duk_context *context) {
		Vector3 *inst = (Vector3*)duk_to_pointer(context, -1);
		inst->Normalize();
		return 0;
	}

	duk_ret_t Polycode_Vector4_set(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, -1);
		Number x = duk_to_number(context, 0);
		Number y = duk_to_number(context, 1);
		Number z = duk_to_number(context, 2);
		Number w = duk_to_number(context, 3);
		inst->set(x,y,z,w);
		return 0;
	}

	duk_ret_t Polycode_Vector4_dot(duk_context *context) {
		Vector4 *inst = (Vector4*)duk_to_pointer(context, -1);
		Vector4 u = *(Vector4*)duk_to_pointer(context, 0);
		inst->dot(u);
		return 0;
	}



}
