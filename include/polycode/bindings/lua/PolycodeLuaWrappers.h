#pragma once

extern "C" {
	#include <stdio.h>
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
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

	class LuaEventHandler : public EventHandler {
	public:
		LuaEventHandler() : EventHandler() {}
		void handleEvent(Event *e) {
			lua_getglobal(L, "__customError");
			int errH = lua_gettop(L);
			lua_getglobal(L, "__handleEvent");
			lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)e;
			lua_pcall(L, 2, 0, errH);
			lua_settop(L, 0);
		}
		int wrapperIndex;
		lua_State *L;
	};

static int Polycode_BasicFile_get_file(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->file) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->file;
	}
	return 1;
}

static int Polycode_BasicFile_set_file(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FILE* *argInst = (FILE**) *((PolyBase**)lua_touserdata(L, 2));
	inst->file = *argInst;
	return 0;
}

	static int Polycode_BasicFile_read(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t size = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		size_t count = *(size_t*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushinteger(L, inst->read(ptr, size, count));
		return 1;
	}
	static int Polycode_BasicFile_write(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t size = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		size_t count = *(size_t*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushinteger(L, inst->write(ptr, size, count));
		return 1;
	}
	static int Polycode_BasicFile_seek(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int offset = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int origin = lua_tointeger(L, 3);
		lua_pushinteger(L, inst->seek(offset, origin));
		return 1;
	}
	static int Polycode_BasicFile_tell(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFile *inst = (BasicFile*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->tell());
		return 1;
	}
	static int Polycode_delete_BasicFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BasicFile*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_BasicFileProvider(lua_State *L) {
		BasicFileProvider *inst = new BasicFileProvider();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BasicFileProvider");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_BasicFileProvider_openFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFileProvider *inst = (BasicFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String opts = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->openFile(fileName, opts);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_BasicFileProvider_closeFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFileProvider *inst = (BasicFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreFile* file = (CoreFile*) *((PolyBase**)lua_touserdata(L, 2));
		inst->closeFile(file);
		return 0;
	}
	static int Polycode_BasicFileProvider_addSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFileProvider *inst = (BasicFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String source = String(lua_tostring(L, 2));
		inst->addSource(source);
		return 0;
	}
	static int Polycode_BasicFileProvider_removeSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BasicFileProvider *inst = (BasicFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String source = String(lua_tostring(L, 2));
		inst->removeSource(source);
		return 0;
	}
	static int Polycode_delete_BasicFileProvider(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BasicFileProvider*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_BezierCurve_get_insertPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->insertPoint) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->insertPoint;
	}
	return 1;
}

static int Polycode_BezierCurve_get_evaluationAccuracy(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->evaluationAccuracy);
	return 1;
}

static int Polycode_BezierCurve_set_insertPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierPoint* *argInst = (BezierPoint**) *((PolyBase**)lua_touserdata(L, 2));
	inst->insertPoint = *argInst;
	return 0;
}

static int Polycode_BezierCurve_set_evaluationAccuracy(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->evaluationAccuracy = param;
	return 0;
}

	static int Polycode_BezierCurve(lua_State *L) {
		BezierCurve *inst = new BezierCurve();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BezierCurve");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_BezierCurve_getControlPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getControlPoint(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_BezierCurve_getNumControlPoints(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumControlPoints());
		return 1;
	}
	static int Polycode_BezierCurve_addControlPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number p1x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number p1y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number p1z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number p2x = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number p2y = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number p2z = lua_tonumber(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		Number p3x = lua_tonumber(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		Number p3y = lua_tonumber(L, 9);
		luaL_checktype(L, 10, LUA_TNUMBER);
		Number p3z = lua_tonumber(L, 10);
		inst->addControlPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
		return 0;
	}
	static int Polycode_BezierCurve_addControlPoint3dWithHandles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number p1x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number p1y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number p1z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number p2x = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number p2y = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number p2z = lua_tonumber(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		Number p3x = lua_tonumber(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		Number p3y = lua_tonumber(L, 9);
		luaL_checktype(L, 10, LUA_TNUMBER);
		Number p3z = lua_tonumber(L, 10);
		inst->addControlPoint3dWithHandles(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
		return 0;
	}
	static int Polycode_BezierCurve_addControlPoint3d(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->addControlPoint3d(x, y, z);
		return 0;
	}
	static int Polycode_BezierCurve_addControlPoint2dWithHandles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number p1x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number p1y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number p2x = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number p2y = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number p3x = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number p3y = lua_tonumber(L, 7);
		inst->addControlPoint2dWithHandles(p1x, p1y, p2x, p2y, p3x, p3y);
		return 0;
	}
	static int Polycode_BezierCurve_addControlPoint2d(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		inst->addControlPoint2d(x, y);
		return 0;
	}
	static int Polycode_BezierCurve_getPointAt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number a = lua_tonumber(L, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPointAt(a);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_BezierCurve_getPointBetween(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number a = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		BezierPoint* bp1 = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		BezierPoint* bp2 = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 4));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPointBetween(a, bp1, bp2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_BezierCurve_clearControlPoints(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearControlPoints();
		return 0;
	}
	static int Polycode_BezierCurve_getYValueAtX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		lua_pushnumber(L, inst->getYValueAtX(x));
		return 1;
	}
	static int Polycode_BezierCurve_getTValueAtX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		lua_pushnumber(L, inst->getTValueAtX(x));
		return 1;
	}
	static int Polycode_BezierCurve_removePoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		BezierPoint* point = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removePoint(point);
		return 0;
	}
	static int Polycode_BezierCurve_setHeightCacheResolution(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number resolution = lua_tonumber(L, 2);
		inst->setHeightCacheResolution(resolution);
		return 0;
	}
	static int Polycode_BezierCurve_rebuildHeightCache(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildHeightCache();
		return 0;
	}
	static int Polycode_BezierCurve_recalculateDistances(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve *inst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recalculateDistances();
		return 0;
	}
	static int Polycode_delete_BezierCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BezierCurve*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_BezierPoint_get_p1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->p1;
	return 1;
}

static int Polycode_BezierPoint_get_p2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->p2;
	return 1;
}

static int Polycode_BezierPoint_get_p3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->p3;
	return 1;
}

static int Polycode_BezierPoint_set_p1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->p1 = *argInst;
	return 0;
}

static int Polycode_BezierPoint_set_p2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->p2 = *argInst;
	return 0;
}

static int Polycode_BezierPoint_set_p3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BezierPoint *inst = (BezierPoint*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->p3 = *argInst;
	return 0;
}

	static int Polycode_BezierPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number p1x = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number p1y = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number p1z = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number p2x = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number p2y = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number p2z = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number p3x = lua_tonumber(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		Number p3y = lua_tonumber(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		Number p3z = lua_tonumber(L, 9);
		BezierPoint *inst = new BezierPoint(p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BezierPoint");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_BezierPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BezierPoint*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Bone_get_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->parentBoneId);
	return 1;
}

static int Polycode_Bone_get_boneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->boneMatrix;
	return 1;
}

static int Polycode_Bone_get_restMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->restMatrix;
	return 1;
}

static int Polycode_Bone_get_baseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->baseMatrix;
	return 1;
}

static int Polycode_Bone_get_finalMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->finalMatrix;
	return 1;
}

static int Polycode_Bone_get_baseRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->baseRotation;
	return 1;
}

static int Polycode_Bone_get_baseScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->baseScale;
	return 1;
}

static int Polycode_Bone_get_basePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->basePosition;
	return 1;
}

static int Polycode_Bone_get_disableAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->disableAnimation);
	return 1;
}

static int Polycode_Bone_set_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->parentBoneId = param;
	return 0;
}

static int Polycode_Bone_set_boneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->boneMatrix = *argInst;
	return 0;
}

static int Polycode_Bone_set_restMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->restMatrix = *argInst;
	return 0;
}

static int Polycode_Bone_set_baseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->baseMatrix = *argInst;
	return 0;
}

static int Polycode_Bone_set_finalMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->finalMatrix = *argInst;
	return 0;
}

static int Polycode_Bone_set_baseRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->baseRotation = *argInst;
	return 0;
}

static int Polycode_Bone_set_baseScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->baseScale = *argInst;
	return 0;
}

static int Polycode_Bone_set_basePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->basePosition = *argInst;
	return 0;
}

static int Polycode_Bone_set_disableAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->disableAnimation = param;
	return 0;
}

	static int Polycode_Bone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String boneName = String(lua_tostring(L, 1));
		Bone *inst = new Bone(boneName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Bone");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Bone_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_Bone_setParentBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParentBone(bone);
		return 0;
	}
	static int Polycode_Bone_addChildBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addChildBone(bone);
		return 0;
	}
	static int Polycode_Bone_getParentBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentBone();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Bone_getNumChildBones(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumChildBones());
		return 1;
	}
	static int Polycode_Bone_getChildBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getChildBone(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Bone_getBoneMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getBoneMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_setBoneMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setBoneMatrix(matrix);
		return 0;
	}
	static int Polycode_Bone_getRestMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getRestMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_getFullRestMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFullRestMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_getParentRestMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getParentRestMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_getFinalMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFinalMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_setRestMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRestMatrix(matrix);
		return 0;
	}
	static int Polycode_Bone_setBaseMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setBaseMatrix(matrix);
		return 0;
	}
	static int Polycode_Bone_getBaseMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getBaseMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_getFullBaseMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getFullBaseMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_rebuildFinalMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildFinalMatrix();
		return 0;
	}
	static int Polycode_Bone_buildFinalMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->buildFinalMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Bone_intializeBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone *inst = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 basePosition = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 baseScale = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Quaternion baseRotation = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Vector3 restPosition = *(Vector3*) *((PolyBase**)lua_touserdata(L, 5));
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Vector3 restScale = *(Vector3*) *((PolyBase**)lua_touserdata(L, 6));
		luaL_checktype(L, 7, LUA_TUSERDATA);
		Quaternion restRotation = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 7));
		inst->intializeBone(basePosition, baseScale, baseRotation, restPosition, restScale, restRotation);
		return 0;
	}
	static int Polycode_delete_Bone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Bone*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Camera_get_frustumCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->frustumCulling);
	return 1;
}

static int Polycode_Camera_get_topLeftOrtho(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->topLeftOrtho);
	return 1;
}

static int Polycode_Camera_get_cameraShift(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->cameraShift;
	return 1;
}

static int Polycode_Camera_set_frustumCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->frustumCulling = param;
	return 0;
}

static int Polycode_Camera_set_topLeftOrtho(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->topLeftOrtho = param;
	return 0;
}

static int Polycode_Camera_set_cameraShift(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->cameraShift = *argInst;
	return 0;
}

	static int Polycode_Camera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		Camera *inst = new Camera(parentScene);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Camera");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Camera_buildFrustumPlanes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		inst->buildFrustumPlanes();
		return 0;
	}
	static int Polycode_Camera_isSphereInFrustum(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 pos = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number fRadius = lua_tonumber(L, 3);
		lua_pushboolean(L, inst->isSphereInFrustum(pos, fRadius));
		return 1;
	}
	static int Polycode_Camera_isAABBInFrustum(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		AABB aabb = *(AABB*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushboolean(L, inst->isAABBInFrustum(aabb));
		return 1;
	}
	static int Polycode_Camera_setOrthoMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool mode = lua_toboolean(L, 2) != 0;
		inst->setOrthoMode(mode);
		return 0;
	}
	static int Polycode_Camera_setOrthoSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number orthoSizeX = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number orthoSizeY = lua_tonumber(L, 3);
		inst->setOrthoSize(orthoSizeX, orthoSizeY);
		return 0;
	}
	static int Polycode_Camera_setFrustumMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number left = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number right = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number bottom = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number top = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number front = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number back = lua_tonumber(L, 7);
		inst->setFrustumMode(left, right, bottom, top, front, back);
		return 0;
	}
	static int Polycode_Camera_getOrthoMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getOrthoMode());
		return 1;
	}
	static int Polycode_Camera_getOrthoSizeX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getOrthoSizeX());
		return 1;
	}
	static int Polycode_Camera_getOrthoSizeY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getOrthoSizeY());
		return 1;
	}
	static int Polycode_Camera_setFOV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number fov = lua_tonumber(L, 2);
		inst->setFOV(fov);
		return 0;
	}
	static int Polycode_Camera_getFOV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getFOV());
		return 1;
	}
	static int Polycode_Camera_setClippingPlanes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number nearClipPlane = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number farClipPlane = lua_tonumber(L, 3);
		inst->setClippingPlanes(nearClipPlane, farClipPlane);
		return 0;
	}
	static int Polycode_Camera_getNearClippingPlane(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getNearClippingPlane());
		return 1;
	}
	static int Polycode_Camera_getFarClippingPlane(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getFarClippingPlane());
		return 1;
	}
	static int Polycode_Camera_setParentScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParentScene(parentScene);
		return 0;
	}
	static int Polycode_Camera_getParentScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentScene();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Camera_createProjectionMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->createProjectionMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Camera_hasFilterShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->hasFilterShader());
		return 1;
	}
	static int Polycode_Camera_drawFilter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderBuffer* targetBuffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->drawFilter(targetBuffer);
		return 0;
	}
	static int Polycode_Camera_setPostFilter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setPostFilter(material);
		return 0;
	}
	static int Polycode_Camera_setPostFilterByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String shaderName = String(lua_tostring(L, 2));
		inst->setPostFilterByName(shaderName);
		return 0;
	}
	static int Polycode_Camera_removePostFilter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		inst->removePostFilter();
		return 0;
	}
	static int Polycode_Camera_getScreenShaderMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getScreenShaderMaterial();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Camera_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Camera_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_Camera_getProjectionMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getProjectionMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Camera_setCustomProjectionMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setCustomProjectionMatrix(matrix);
		return 0;
	}
	static int Polycode_Camera_getViewport(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->getViewport();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Polycode::Rectangle");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Camera_setViewport(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setViewport(viewport);
		return 0;
	}
	static int Polycode_Camera_setOrthoSizeMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int orthoSizeMode = lua_tointeger(L, 2);
		inst->setOrthoSizeMode(orthoSizeMode);
		return 0;
	}
	static int Polycode_Camera_getOrthoSizeMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getOrthoSizeMode());
		return 1;
	}
	static int Polycode_Camera_setProjectionMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int mode = lua_tointeger(L, 2);
		inst->setProjectionMode(mode);
		return 0;
	}
	static int Polycode_Camera_getProjectionMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getProjectionMode());
		return 1;
	}
	static int Polycode_Camera_projectRayFrom2DCoordinate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 coordinate = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 3));
		Vector3 *retInst = new Vector3();
		*retInst = inst->projectRayFrom2DCoordinate(coordinate, viewport);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Camera_renderFullScreenQuad(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int shaderPass = lua_tointeger(L, 3);
		inst->renderFullScreenQuad(drawBuffer, shaderPass);
		return 0;
	}
	static int Polycode_Camera_getShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.ShaderPass");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Camera_getNumShaderPasses(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Camera *inst = (Camera*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumShaderPasses());
		return 1;
	}
	static int Polycode_delete_Camera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Camera*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Color_get_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->r);
	return 1;
}

static int Polycode_Color_get_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->g);
	return 1;
}

static int Polycode_Color_get_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->b);
	return 1;
}

static int Polycode_Color_get_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->a);
	return 1;
}

static int Polycode_Color_set_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->r = param;
	return 0;
}

static int Polycode_Color_set_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->g = param;
	return 0;
}

static int Polycode_Color_set_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->b = param;
	return 0;
}

static int Polycode_Color_set_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->a = param;
	return 0;
}

	static int Polycode_Color(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number r = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number g = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number b = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number a = lua_tonumber(L, 4);
		Color *inst = new Color(r, g, b, a);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Color_ColorWithInts(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int r = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		int g = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int b = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int a = lua_tointeger(L, 4);
		Color *retInst = new Color();
		*retInst = Color::ColorWithInts(r, g, b, a);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Color_ColorWithHex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int hex = lua_tointeger(L, 1);
		Color *retInst = new Color();
		*retInst = Color::ColorWithHex(hex);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Color_setColorHex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int hex = lua_tointeger(L, 2);
		inst->setColorHex(hex);
		return 0;
	}
	static int Polycode_Color_setColorHexRGB(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int hex = lua_tointeger(L, 2);
		inst->setColorHexRGB(hex);
		return 0;
	}
	static int Polycode_Color_setColorHexFromString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String hex = String(lua_tostring(L, 2));
		inst->setColorHexFromString(hex);
		return 0;
	}
	static int Polycode_Color_setColorHexRGBFromString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String hex = String(lua_tostring(L, 2));
		inst->setColorHexRGBFromString(hex);
		return 0;
	}
	static int Polycode_Color_setColorHSV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number h = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number s = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number v = lua_tonumber(L, 4);
		inst->setColorHSV(h, s, v);
		return 0;
	}
	static int Polycode_Color_setColorRGBA(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int r = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int g = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int b = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int a = lua_tointeger(L, 5);
		inst->setColorRGBA(r, g, b, a);
		return 0;
	}
	static int Polycode_Color_setColorRGB(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int r = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int g = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int b = lua_tointeger(L, 4);
		inst->setColorRGB(r, g, b);
		return 0;
	}
	static int Polycode_Color_setColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number a = lua_tonumber(L, 5);
		inst->setColor(r, g, b, a);
		return 0;
	}
	static int Polycode_Color_blendColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color c2 = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int mode = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number amount = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Color c3 = *(Color*) *((PolyBase**)lua_touserdata(L, 5));
		Color *retInst = new Color();
		*retInst = inst->blendColor(c2, mode, amount, c3);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Color_Random(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Random();
		return 0;
	}
	static int Polycode_Color_getBrightness(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getBrightness());
		return 1;
	}
	static int Polycode_Color_RGBtoHSV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number r = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number g = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number b = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number h = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number s = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number v = lua_tonumber(L, 6);
		Color::RGBtoHSV(r, g, b, h, s, v);
		return 0;
	}
	static int Polycode_Color_getHue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getHue());
		return 1;
	}
	static int Polycode_Color_getSaturation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getSaturation());
		return 1;
	}
	static int Polycode_Color_getValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getValue());
		return 1;
	}
	static int Polycode_Color_getUint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color *inst = (Color*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getUint());
		return 1;
	}
	static int Polycode_delete_Color(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Color*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ConfigEntry_get_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->key.c_str());
	return 1;
}

static int Polycode_ConfigEntry_get_configNamespace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->configNamespace.c_str());
	return 1;
}

static int Polycode_ConfigEntry_get_numVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->numVal);
	return 1;
}

static int Polycode_ConfigEntry_get_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->stringVal.c_str());
	return 1;
}

static int Polycode_ConfigEntry_get_isString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->isString);
	return 1;
}

static int Polycode_ConfigEntry_set_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->key = param;
	return 0;
}

static int Polycode_ConfigEntry_set_configNamespace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->configNamespace = param;
	return 0;
}

static int Polycode_ConfigEntry_set_numVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->numVal = param;
	return 0;
}

static int Polycode_ConfigEntry_set_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->stringVal = param;
	return 0;
}

static int Polycode_ConfigEntry_set_isString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ConfigEntry *inst = (ConfigEntry*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->isString = param;
	return 0;
}

	static int Polycode_delete_ConfigEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ConfigEntry*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Config(lua_State *L) {
		Config *inst = new Config();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Config");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Config_loadConfig(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		inst->loadConfig(configNamespace, fileName);
		return 0;
	}
	static int Polycode_Config_saveConfig(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		inst->saveConfig(configNamespace, fileName);
		return 0;
	}
	static int Polycode_Config_getEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->getEntry(configNamespace, key);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Config_setStringValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TSTRING);
		String value = String(lua_tostring(L, 4));
		inst->setStringValue(configNamespace, key, value);
		return 0;
	}
	static int Polycode_Config_setNumericValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number value = lua_tonumber(L, 4);
		inst->setNumericValue(configNamespace, key, value);
		return 0;
	}
	static int Polycode_Config_getNumericValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		lua_pushnumber(L, inst->getNumericValue(configNamespace, key));
		return 1;
	}
	static int Polycode_Config_getStringValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		lua_pushstring(L, inst->getStringValue(configNamespace, key).c_str());
		return 1;
	}
	static int Polycode_Config_setBoolValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool value = lua_toboolean(L, 4) != 0;
		inst->setBoolValue(configNamespace, key, value);
		return 0;
	}
	static int Polycode_Config_getBoolValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Config *inst = (Config*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String configNamespace = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String key = String(lua_tostring(L, 3));
		lua_pushboolean(L, inst->getBoolValue(configNamespace, key));
		return 1;
	}
	static int Polycode_delete_Config(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Config*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Core_get_eventMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->eventMutex) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->eventMutex;
	}
	return 1;
}

static int Polycode_Core_get_paused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->paused);
	return 1;
}

static int Polycode_Core_get_pauseOnLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->pauseOnLoseFocus);
	return 1;
}

static int Polycode_Core_get_defaultScreenWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->defaultScreenWidth);
	return 1;
}

static int Polycode_Core_get_defaultScreenHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->defaultScreenHeight);
	return 1;
}

static int Polycode_Core_get_deviceAttitude(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->deviceAttitude;
	return 1;
}

static int Polycode_Core_set_eventMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CoreMutex* *argInst = (CoreMutex**) *((PolyBase**)lua_touserdata(L, 2));
	inst->eventMutex = *argInst;
	return 0;
}

static int Polycode_Core_set_paused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->paused = param;
	return 0;
}

static int Polycode_Core_set_pauseOnLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->pauseOnLoseFocus = param;
	return 0;
}

static int Polycode_Core_set_defaultScreenWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->defaultScreenWidth = param;
	return 0;
}

static int Polycode_Core_set_defaultScreenHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->defaultScreenHeight = param;
	return 0;
}

static int Polycode_Core_set_deviceAttitude(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deviceAttitude = *argInst;
	return 0;
}

	static int Polycode_Core_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->Update());
		return 1;
	}
	static int Polycode_Core_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Render();
		return 0;
	}
	static int Polycode_Core_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->fixedUpdate());
		return 1;
	}
	static int Polycode_Core_systemUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->systemUpdate());
		return 1;
	}
	static int Polycode_Core_updateAndRender(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->updateAndRender());
		return 1;
	}
	static int Polycode_Core_enableMouse(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool newval = lua_toboolean(L, 2) != 0;
		inst->enableMouse(newval);
		return 0;
	}
	static int Polycode_Core_captureMouse(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool newval = lua_toboolean(L, 2) != 0;
		inst->captureMouse(newval);
		return 0;
	}
	static int Polycode_Core_setCursor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int cursorType = lua_tointeger(L, 2);
		inst->setCursor(cursorType);
		return 0;
	}
	static int Polycode_Core_warpCursor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		inst->warpCursor(x, y);
		return 0;
	}
	static int Polycode_Core_createThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Threaded* target = (Threaded*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createThread(target);
		return 0;
	}
	static int Polycode_Core_lockMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreMutex* mutex = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 2));
		inst->lockMutex(mutex);
		return 0;
	}
	static int Polycode_Core_unlockMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreMutex* mutex = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 2));
		inst->unlockMutex(mutex);
		return 0;
	}
	static int Polycode_Core_createMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->createMutex();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_copyStringToClipboard(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		inst->copyStringToClipboard(str);
		return 0;
	}
	static int Polycode_Core_getClipboardString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getClipboardString().c_str());
		return 1;
	}
	static int Polycode_Core_getServices(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getServices();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_getFPS(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getFPS());
		return 1;
	}
	static int Polycode_Core_Shutdown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Shutdown();
		return 0;
	}
	static int Polycode_Core_isFullscreen(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isFullscreen());
		return 1;
	}
	static int Polycode_Core_getAALevel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getAALevel());
		return 1;
	}
	static int Polycode_Core_getInput(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getInput();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_getXRes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getXRes());
		return 1;
	}
	static int Polycode_Core_getYRes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getYRes());
		return 1;
	}
	static int Polycode_Core_getBackingXRes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getBackingXRes());
		return 1;
	}
	static int Polycode_Core_getBackingYRes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getBackingYRes());
		return 1;
	}
	static int Polycode_Core_getScreenInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		int* width = (int*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		int* height = (int*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		int* hz = (int*) *((PolyBase**)lua_touserdata(L, 3));
		Core::getScreenInfo(width, height, hz);
		return 0;
	}
	static int Polycode_Core_getScreenWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getScreenWidth());
		return 1;
	}
	static int Polycode_Core_getScreenHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getScreenHeight());
		return 1;
	}
	static int Polycode_Core_createFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String folderPath = String(lua_tostring(L, 2));
		inst->createFolder(folderPath);
		return 0;
	}
	static int Polycode_Core_copyDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String destItemPath = String(lua_tostring(L, 3));
		inst->copyDiskItem(itemPath, destItemPath);
		return 0;
	}
	static int Polycode_Core_moveDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String destItemPath = String(lua_tostring(L, 3));
		inst->moveDiskItem(itemPath, destItemPath);
		return 0;
	}
	static int Polycode_Core_removeDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		inst->removeDiskItem(itemPath);
		return 0;
	}
	static int Polycode_Core_openFolderPicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->openFolderPicker().c_str());
		return 1;
	}
	static int Polycode_Core_setFramerate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int frameRate = lua_tointeger(L, 2);
		int maxFixedCycles;
		if(lua_isnumber(L, 3)) {
			maxFixedCycles = lua_tointeger(L, 3);
		} else {
			maxFixedCycles = 8;
		}
		inst->setFramerate(frameRate, maxFixedCycles);
		return 0;
	}
	static int Polycode_Core_openFilePicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool allowMultiple = lua_toboolean(L, 3) != 0;
		return 0;
	}
	static int Polycode_Core_saveFilePicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushstring(L, inst->saveFilePicker(extensions).c_str());
		return 1;
	}
	static int Polycode_Core_handleVideoModeChange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 2));
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}
	static int Polycode_Core_flushRenderContext(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->flushRenderContext();
		return 0;
	}
	static int Polycode_Core_prepareRenderContext(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->prepareRenderContext();
		return 0;
	}
	static int Polycode_Core_openFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String opts = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->openFile(fileName, opts);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_closeFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreFile* file = (CoreFile*) *((PolyBase**)lua_touserdata(L, 2));
		inst->closeFile(file);
		return 0;
	}
	static int Polycode_Core_addFileSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String type = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String source = String(lua_tostring(L, 3));
		inst->addFileSource(type, source);
		return 0;
	}
	static int Polycode_Core_removeFileSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String type = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String source = String(lua_tostring(L, 3));
		inst->removeFileSource(type, source);
		return 0;
	}
	static int Polycode_Core_parseFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String pathString = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool showHidden = lua_toboolean(L, 3) != 0;
		return 0;
	}
	static int Polycode_Core_systemParseFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String pathString = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool showHidden = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TUSERDATA);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushboolean(L, inst->systemParseFolder(pathString, showHidden, targetVector));
		return 1;
	}
	static int Polycode_Core_getResourcePathForFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushstring(L, inst->getResourcePathForFile(fileName).c_str());
		return 1;
	}
	static int Polycode_Core_setVideoMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int xRes = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int yRes = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool fullScreen = lua_toboolean(L, 4) != 0;
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool vSync = lua_toboolean(L, 5) != 0;
		luaL_checktype(L, 6, LUA_TNUMBER);
		int aaLevel = lua_tointeger(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		int anisotropyLevel = lua_tointeger(L, 7);
		bool retinaSupport;
		if(lua_isboolean(L, 8)) {
			retinaSupport = lua_toboolean(L, 8) != 0;
		} else {
			retinaSupport = true;
		}
		inst->setVideoMode(xRes, yRes, fullScreen, vSync, aaLevel, anisotropyLevel, retinaSupport);
		return 0;
	}
	static int Polycode_Core_resizeTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int xRes = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int yRes = lua_tointeger(L, 3);
		inst->resizeTo(xRes, yRes);
		return 0;
	}
	static int Polycode_Core_doSleep(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->doSleep();
		return 0;
	}
	static int Polycode_Core_openURL(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String url = String(lua_tostring(L, 2));
		inst->openURL(url);
		return 0;
	}
	static int Polycode_Core_getElapsed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getElapsed());
		return 1;
	}
	static int Polycode_Core_getTicks(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getTicks());
		return 1;
	}
	static int Polycode_Core_getRefreshIntervalMs(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getRefreshIntervalMs());
		return 1;
	}
	static int Polycode_Core_getTimeSleptMs(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getTimeSleptMs());
		return 1;
	}
	static int Polycode_Core_getFixedTimestep(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getFixedTimestep());
		return 1;
	}
	static int Polycode_Core_getTicksFloat(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getTicksFloat());
		return 1;
	}
	static int Polycode_Core_setUserPointer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setUserPointer(ptr);
		return 0;
	}
	static int Polycode_Core_getUserPointer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getUserPointer();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_executeExternalCommand(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String command = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String args = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TSTRING);
		String inDirectory = String(lua_tostring(L, 4));
		lua_pushstring(L, inst->executeExternalCommand(command, args, inDirectory).c_str());
		return 1;
	}
	static int Polycode_Core_getDefaultWorkingDirectory(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getDefaultWorkingDirectory().c_str());
		return 1;
	}
	static int Polycode_Core_getUserHomeDirectory(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getUserHomeDirectory().c_str());
		return 1;
	}
	static int Polycode_Core_makeApplicationMain(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		inst->makeApplicationMain();
		return 0;
	}
	static int Polycode_Core_getEventMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getEventMutex();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Core_removeThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Core *inst = (Core*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Threaded* thread = (Threaded*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeThread(thread);
		return 0;
	}
	static int Polycode_delete_Core(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Core*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_VideoModeChangeInfo_get_xRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->xRes);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_yRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->yRes);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_fullScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->fullScreen);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_vSync(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->vSync);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_aaLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->aaLevel);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_anisotropyLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->anisotropyLevel);
	return 1;
}

static int Polycode_VideoModeChangeInfo_get_retinaSupport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->retinaSupport);
	return 1;
}

static int Polycode_VideoModeChangeInfo_set_xRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->xRes = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_yRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->yRes = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_fullScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->fullScreen = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_vSync(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->vSync = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_aaLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->aaLevel = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_anisotropyLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->anisotropyLevel = param;
	return 0;
}

static int Polycode_VideoModeChangeInfo_set_retinaSupport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VideoModeChangeInfo *inst = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->retinaSupport = param;
	return 0;
}

	static int Polycode_delete_VideoModeChangeInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((VideoModeChangeInfo*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_PolycodeViewBase_get_windowData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->windowData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->windowData;
	}
	return 1;
}

static int Polycode_PolycodeViewBase_get_resizable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->resizable);
	return 1;
}

static int Polycode_PolycodeViewBase_set_windowData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->windowData = *argInst;
	return 0;
}

static int Polycode_PolycodeViewBase_set_resizable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->resizable = param;
	return 0;
}

	static int Polycode_PolycodeViewBase(lua_State *L) {
		PolycodeViewBase *inst = new PolycodeViewBase();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.PolycodeViewBase");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_PolycodeViewBase(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((PolycodeViewBase*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_DummyCore(lua_State *L) {
		DummyCore *inst = new DummyCore();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.DummyCore");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_DummyCore_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Render();
		return 0;
	}
	static int Polycode_DummyCore_systemUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->systemUpdate());
		return 1;
	}
	static int Polycode_DummyCore_setCursor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int cursorType = lua_tointeger(L, 2);
		inst->setCursor(cursorType);
		return 0;
	}
	static int Polycode_DummyCore_createThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Threaded* target = (Threaded*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createThread(target);
		return 0;
	}
	static int Polycode_DummyCore_createMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->createMutex();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_DummyCore_copyStringToClipboard(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		inst->copyStringToClipboard(str);
		return 0;
	}
	static int Polycode_DummyCore_getClipboardString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getClipboardString().c_str());
		return 1;
	}
	static int Polycode_DummyCore_createFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String folderPath = String(lua_tostring(L, 2));
		inst->createFolder(folderPath);
		return 0;
	}
	static int Polycode_DummyCore_copyDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String destItemPath = String(lua_tostring(L, 3));
		inst->copyDiskItem(itemPath, destItemPath);
		return 0;
	}
	static int Polycode_DummyCore_moveDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String destItemPath = String(lua_tostring(L, 3));
		inst->moveDiskItem(itemPath, destItemPath);
		return 0;
	}
	static int Polycode_DummyCore_removeDiskItem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String itemPath = String(lua_tostring(L, 2));
		inst->removeDiskItem(itemPath);
		return 0;
	}
	static int Polycode_DummyCore_openFolderPicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->openFolderPicker().c_str());
		return 1;
	}
	static int Polycode_DummyCore_openFilePicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool allowMultiple = lua_toboolean(L, 3) != 0;
		return 0;
	}
	static int Polycode_DummyCore_saveFilePicker(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		vector<CoreFileExtension> extensions = *(vector<CoreFileExtension>*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushstring(L, inst->saveFilePicker(extensions).c_str());
		return 1;
	}
	static int Polycode_DummyCore_handleVideoModeChange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		VideoModeChangeInfo* modeInfo = (VideoModeChangeInfo*) *((PolyBase**)lua_touserdata(L, 2));
		inst->handleVideoModeChange(modeInfo);
		return 0;
	}
	static int Polycode_DummyCore_flushRenderContext(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		inst->flushRenderContext();
		return 0;
	}
	static int Polycode_DummyCore_openURL(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String url = String(lua_tostring(L, 2));
		inst->openURL(url);
		return 0;
	}
	static int Polycode_DummyCore_getTicks(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getTicks());
		return 1;
	}
	static int Polycode_DummyCore_executeExternalCommand(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String command = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String args = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TSTRING);
		String inDirectory = String(lua_tostring(L, 4));
		lua_pushstring(L, inst->executeExternalCommand(command, args, inDirectory).c_str());
		return 1;
	}
	static int Polycode_DummyCore_systemParseFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		DummyCore *inst = (DummyCore*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String pathString = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool showHidden = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TUSERDATA);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushboolean(L, inst->systemParseFolder(pathString, showHidden, targetVector));
		return 1;
	}
	static int Polycode_delete_DummyCore(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((DummyCore*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_TimeInfo_get_seconds(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->seconds);
	return 1;
}

static int Polycode_TimeInfo_get_minutes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->minutes);
	return 1;
}

static int Polycode_TimeInfo_get_hours(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->hours);
	return 1;
}

static int Polycode_TimeInfo_get_month(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->month);
	return 1;
}

static int Polycode_TimeInfo_get_monthDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->monthDay);
	return 1;
}

static int Polycode_TimeInfo_get_weekDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->weekDay);
	return 1;
}

static int Polycode_TimeInfo_get_year(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->year);
	return 1;
}

static int Polycode_TimeInfo_get_yearDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->yearDay);
	return 1;
}

static int Polycode_TimeInfo_set_seconds(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->seconds = param;
	return 0;
}

static int Polycode_TimeInfo_set_minutes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->minutes = param;
	return 0;
}

static int Polycode_TimeInfo_set_hours(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->hours = param;
	return 0;
}

static int Polycode_TimeInfo_set_month(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->month = param;
	return 0;
}

static int Polycode_TimeInfo_set_monthDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->monthDay = param;
	return 0;
}

static int Polycode_TimeInfo_set_weekDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->weekDay = param;
	return 0;
}

static int Polycode_TimeInfo_set_year(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->year = param;
	return 0;
}

static int Polycode_TimeInfo_set_yearDay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TimeInfo *inst = (TimeInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->yearDay = param;
	return 0;
}

	static int Polycode_TimeInfo(lua_State *L) {
		TimeInfo *inst = new TimeInfo();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.TimeInfo");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_TimeInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((TimeInfo*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_CoreMutex_get_mutexID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreMutex *inst = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->mutexID);
	return 1;
}

static int Polycode_CoreMutex_set_mutexID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreMutex *inst = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->mutexID = param;
	return 0;
}

	static int Polycode_CoreMutex_lock(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreMutex *inst = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 1));
		inst->lock();
		return 0;
	}
	static int Polycode_CoreMutex_unlock(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreMutex *inst = (CoreMutex*) *((PolyBase**)lua_touserdata(L, 1));
		inst->unlock();
		return 0;
	}
	static int Polycode_delete_CoreMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((CoreMutex*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_CoreMotionEvent_get_amount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreMotionEvent *inst = (CoreMotionEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->amount;
	return 1;
}

static int Polycode_CoreMotionEvent_set_amount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreMotionEvent *inst = (CoreMotionEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->amount = *argInst;
	return 0;
}

	static int Polycode_delete_CoreMotionEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((CoreMotionEvent*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_CoreFileExtension_get_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreFileExtension *inst = (CoreFileExtension*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->extension.c_str());
	return 1;
}

static int Polycode_CoreFileExtension_get_description(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreFileExtension *inst = (CoreFileExtension*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->description.c_str());
	return 1;
}

static int Polycode_CoreFileExtension_set_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreFileExtension *inst = (CoreFileExtension*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->extension = param;
	return 0;
}

static int Polycode_CoreFileExtension_set_description(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreFileExtension *inst = (CoreFileExtension*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->description = param;
	return 0;
}

	static int Polycode_CoreFileExtension(lua_State *L) {
		CoreFileExtension *inst = new CoreFileExtension();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.CoreFileExtension");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_CoreFileExtension(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((CoreFileExtension*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_OSFileEntry_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_OSFileEntry_get_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->extension.c_str());
	return 1;
}

static int Polycode_OSFileEntry_get_nameWithoutExtension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->nameWithoutExtension.c_str());
	return 1;
}

static int Polycode_OSFileEntry_get_basePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->basePath.c_str());
	return 1;
}

static int Polycode_OSFileEntry_get_fullPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->fullPath.c_str());
	return 1;
}

static int Polycode_OSFileEntry_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_OSFileEntry_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_OSFileEntry_set_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->extension = param;
	return 0;
}

static int Polycode_OSFileEntry_set_nameWithoutExtension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->nameWithoutExtension = param;
	return 0;
}

static int Polycode_OSFileEntry_set_basePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->basePath = param;
	return 0;
}

static int Polycode_OSFileEntry_set_fullPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->fullPath = param;
	return 0;
}

static int Polycode_OSFileEntry_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

	static int Polycode_OSFileEntry(lua_State *L) {
		OSFileEntry *inst = new OSFileEntry();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.OSFileEntry");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_OSFileEntry_init(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OSFileEntry *inst = (OSFileEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String name = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		int type = lua_tointeger(L, 4);
		inst->init(path, name, type);
		return 0;
	}
	static int Polycode_delete_OSFileEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((OSFileEntry*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_CoreInput_get_simulateTouchWithMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->simulateTouchWithMouse);
	return 1;
}

static int Polycode_CoreInput_get_simulateTouchAsPen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->simulateTouchAsPen);
	return 1;
}

static int Polycode_CoreInput_get_simulateMouseWithTouch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->simulateMouseWithTouch);
	return 1;
}

static int Polycode_CoreInput_get_ignoreOffScreenTouch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ignoreOffScreenTouch);
	return 1;
}

static int Polycode_CoreInput_get_keyRepeat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->keyRepeat);
	return 1;
}

static int Polycode_CoreInput_get_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->mousePosition;
	return 1;
}

static int Polycode_CoreInput_get_deltaMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->deltaMousePosition;
	return 1;
}

static int Polycode_CoreInput_set_simulateTouchWithMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->simulateTouchWithMouse = param;
	return 0;
}

static int Polycode_CoreInput_set_simulateTouchAsPen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->simulateTouchAsPen = param;
	return 0;
}

static int Polycode_CoreInput_set_simulateMouseWithTouch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->simulateMouseWithTouch = param;
	return 0;
}

static int Polycode_CoreInput_set_ignoreOffScreenTouch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ignoreOffScreenTouch = param;
	return 0;
}

static int Polycode_CoreInput_set_keyRepeat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->keyRepeat = param;
	return 0;
}

static int Polycode_CoreInput_set_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->mousePosition = *argInst;
	return 0;
}

static int Polycode_CoreInput_set_deltaMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->deltaMousePosition = *argInst;
	return 0;
}

	static int Polycode_CoreInput(lua_State *L) {
		CoreInput *inst = new CoreInput();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.CoreInput");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_CoreInput_getMousePosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMousePosition();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_CoreInput_getKeyState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		PolyKEY keyCode = (PolyKEY)lua_tointeger(L, 2);
		lua_pushboolean(L, inst->getKeyState(keyCode));
		return 1;
	}
	static int Polycode_CoreInput_getJoystickButtonState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int joystickIndex = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int button = lua_tointeger(L, 3);
		lua_pushboolean(L, inst->getJoystickButtonState(joystickIndex, button));
		return 1;
	}
	static int Polycode_CoreInput_getJoystickAxisValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int joystickIndex = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int axis = lua_tointeger(L, 3);
		lua_pushnumber(L, inst->getJoystickAxisValue(joystickIndex, axis));
		return 1;
	}
	static int Polycode_CoreInput_getMouseDelta(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMouseDelta();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_CoreInput_getMouseButtonState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int mouseButton = lua_tointeger(L, 2);
		lua_pushboolean(L, inst->getMouseButtonState(mouseButton));
		return 1;
	}
	static int Polycode_CoreInput_getNumJoysticks(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumJoysticks());
		return 1;
	}
	static int Polycode_CoreInput_getJoystickInfoByIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreInput_getJoystickInfoByID(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getJoystickInfoByID(deviceID);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreInput_addJoystick(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 2);
		inst->addJoystick(deviceID);
		return 0;
	}
	static int Polycode_CoreInput_removeJoystick(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 2);
		inst->removeJoystick(deviceID);
		return 0;
	}
	static int Polycode_CoreInput_joystickAxisMoved(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int axisID = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number value = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 4);
		inst->joystickAxisMoved(axisID, value, deviceID);
		return 0;
	}
	static int Polycode_CoreInput_joystickButtonDown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int buttonID = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 3);
		inst->joystickButtonDown(buttonID, deviceID);
		return 0;
	}
	static int Polycode_CoreInput_joystickButtonUp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int buttonID = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int deviceID = lua_tointeger(L, 3);
		inst->joystickButtonUp(buttonID, deviceID);
		return 0;
	}
	static int Polycode_CoreInput_mouseWheelUp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 2);
		inst->mouseWheelUp(ticks);
		return 0;
	}
	static int Polycode_CoreInput_mouseWheelDown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 2);
		inst->mouseWheelDown(ticks);
		return 0;
	}
	static int Polycode_CoreInput_setMouseButtonState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int mouseButton = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool state = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 4);
		inst->setMouseButtonState(mouseButton, state, ticks);
		return 0;
	}
	static int Polycode_CoreInput_setMousePosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 4);
		inst->setMousePosition(x, y, ticks);
		return 0;
	}
	static int Polycode_CoreInput_setKeyState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		PolyKEY keyCode = (PolyKEY)lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		wchar_t code = *(wchar_t*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool newState = lua_toboolean(L, 4) != 0;
		luaL_checktype(L, 5, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 5);
		inst->setKeyState(keyCode, code, newState, ticks);
		return 0;
	}
	static int Polycode_CoreInput_setDeltaPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		inst->setDeltaPosition(x, y);
		return 0;
	}
	static int Polycode_CoreInput_touchesBegan(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 4);
		inst->touchesBegan(touch, touches, ticks);
		return 0;
	}
	static int Polycode_CoreInput_touchesMoved(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 4);
		inst->touchesMoved(touch, touches, ticks);
		return 0;
	}
	static int Polycode_CoreInput_touchesEnded(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		TouchInfo touch = *(TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		vector<TouchInfo> touches = *(vector<TouchInfo>*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 4);
		inst->touchesEnded(touch, touches, ticks);
		return 0;
	}
	static int Polycode_CoreInput_createEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)CoreInput::createEvent(event);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreInput_clearInput(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreInput *inst = (CoreInput*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearInput();
		return 0;
	}
	static int Polycode_delete_CoreInput(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((CoreInput*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_JoystickInfo_get_deviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JoystickInfo *inst = (JoystickInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->deviceID);
	return 1;
}

static int Polycode_JoystickInfo_get_deviceIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JoystickInfo *inst = (JoystickInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->deviceIndex);
	return 1;
}

static int Polycode_JoystickInfo_set_deviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JoystickInfo *inst = (JoystickInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->deviceID = param;
	return 0;
}

static int Polycode_JoystickInfo_set_deviceIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JoystickInfo *inst = (JoystickInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->deviceIndex = param;
	return 0;
}

	static int Polycode_JoystickInfo(lua_State *L) {
		JoystickInfo *inst = new JoystickInfo();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.JoystickInfo");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_JoystickInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((JoystickInfo*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_CoreServices_getInstance(lua_State *L) {
		PolyBase *ptrRetVal = (PolyBase*)CoreServices::getInstance();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_setInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices* _instance = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		CoreServices::setInstance(_instance);
		return 0;
	}
	static int Polycode_CoreServices_getRenderMutex(lua_State *L) {
		PolyBase *ptrRetVal = (PolyBase*)CoreServices::getRenderMutex();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_createInstance(lua_State *L) {
		CoreServices::createInstance();
		return 0;
	}
	static int Polycode_CoreServices_setRenderer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Renderer* renderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRenderer(renderer);
		return 0;
	}
	static int Polycode_CoreServices_getRenderer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderer();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int elapsed = lua_tointeger(L, 2);
		inst->Update(elapsed);
		return 0;
	}
	static int Polycode_CoreServices_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		inst->fixedUpdate();
		return 0;
	}
	static int Polycode_CoreServices_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(viewport);
		return 0;
	}
	static int Polycode_CoreServices_setCore(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Core* core = (Core*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setCore(core);
		return 0;
	}
	static int Polycode_CoreServices_getCore(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getCore();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getInput(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getInput();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getMaterialManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getMaterialManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getSceneManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSceneManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getTimerManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTimerManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getTweenManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTweenManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getResourceManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getSoundManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSoundManager();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getLogger(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getLogger();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_CoreServices_getConfig(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		CoreServices *inst = (CoreServices*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getConfig();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_CoreServices(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((CoreServices*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Cubemap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture* t0 = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* t1 = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Texture* t2 = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Texture* t3 = (Texture*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Texture* t4 = (Texture*) *((PolyBase**)lua_touserdata(L, 5));
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Texture* t5 = (Texture*) *((PolyBase**)lua_touserdata(L, 6));
		Cubemap *inst = new Cubemap(t0, t1, t2, t3, t4, t5);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Cubemap");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Cubemap_getTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getTexture(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Cubemap_setTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int index = lua_tointeger(L, 3);
		inst->setTexture(texture, index);
		return 0;
	}
	static int Polycode_Cubemap_recreateFromTextures(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Cubemap *inst = (Cubemap*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recreateFromTextures();
		return 0;
	}
	static int Polycode_delete_Cubemap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Cubemap*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Data(lua_State *L) {
		Data *inst = new Data();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Data");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Data_loadFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->loadFromFile(fileName));
		return 1;
	}
	static int Polycode_Data_getAsString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 2);
		lua_pushstring(L, inst->getAsString(encoding).c_str());
		return 1;
	}
	static int Polycode_Data_setFromString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 3);
		inst->setFromString(str, encoding);
		return 0;
	}
	static int Polycode_Data_saveToFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->saveToFile(fileName));
		return 1;
	}
	static int Polycode_Data_getData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Data *inst = (Data*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_Data(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Data*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_MouseEventResult_get_hit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MouseEventResult *inst = (MouseEventResult*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hit);
	return 1;
}

static int Polycode_MouseEventResult_get_blocked(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MouseEventResult *inst = (MouseEventResult*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->blocked);
	return 1;
}

static int Polycode_MouseEventResult_set_hit(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MouseEventResult *inst = (MouseEventResult*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->hit = param;
	return 0;
}

static int Polycode_MouseEventResult_set_blocked(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MouseEventResult *inst = (MouseEventResult*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->blocked = param;
	return 0;
}

	static int Polycode_delete_MouseEventResult(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((MouseEventResult*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_EntityProp_get_propName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EntityProp *inst = (EntityProp*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->propName.c_str());
	return 1;
}

static int Polycode_EntityProp_get_propValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EntityProp *inst = (EntityProp*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->propValue.c_str());
	return 1;
}

static int Polycode_EntityProp_set_propName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EntityProp *inst = (EntityProp*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->propName = param;
	return 0;
}

static int Polycode_EntityProp_set_propValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	EntityProp *inst = (EntityProp*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->propValue = param;
	return 0;
}

	static int Polycode_delete_EntityProp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((EntityProp*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_AABB_get_min(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AABB *inst = (AABB*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->min;
	return 1;
}

static int Polycode_AABB_get_max(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AABB *inst = (AABB*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->max;
	return 1;
}

static int Polycode_AABB_set_min(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AABB *inst = (AABB*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->min = *argInst;
	return 0;
}

static int Polycode_AABB_set_max(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AABB *inst = (AABB*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->max = *argInst;
	return 0;
}

	static int Polycode_delete_AABB(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((AABB*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Rotation_get_pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->pitch);
	return 1;
}

static int Polycode_Rotation_get_yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->yaw);
	return 1;
}

static int Polycode_Rotation_get_roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->roll);
	return 1;
}

static int Polycode_Rotation_set_pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->pitch = param;
	return 0;
}

static int Polycode_Rotation_set_yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->yaw = param;
	return 0;
}

static int Polycode_Rotation_set_roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rotation *inst = (Rotation*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->roll = param;
	return 0;
}

	static int Polycode_Rotation(lua_State *L) {
		Rotation *inst = new Rotation();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Rotation");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_Rotation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Rotation*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Entity_get_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsChildren);
	return 1;
}

static int Polycode_Entity_get_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->billboardMode);
	return 1;
}

static int Polycode_Entity_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int Polycode_Entity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycode_Entity_get_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->visible);
	return 1;
}

static int Polycode_Entity_get_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthWrite);
	return 1;
}

static int Polycode_Entity_get_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthTest);
	return 1;
}

static int Polycode_Entity_get_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->colorAffectsChildren);
	return 1;
}

static int Polycode_Entity_get_visibilityAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->visibilityAffectsChildren);
	return 1;
}

static int Polycode_Entity_get_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ignoreParentMatrix);
	return 1;
}

static int Polycode_Entity_get_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enableScissor);
	return 1;
}

static int Polycode_Entity_get_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scissorBox;
	return 1;
}

static int Polycode_Entity_get_editorOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->editorOnly);
	return 1;
}

static int Polycode_Entity_get_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->id.c_str());
	return 1;
}

static int Polycode_Entity_get_collisionShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->collisionShapeType;
	return 1;
}

static int Polycode_Entity_get_processInputEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->processInputEvents);
	return 1;
}

static int Polycode_Entity_get_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->blockMouseInput);
	return 1;
}

static int Polycode_Entity_get_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->snapToPixels);
	return 1;
}

static int Polycode_Entity_get_mouseOver(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->mouseOver);
	return 1;
}

static int Polycode_Entity_get_rendererVis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->rendererVis);
	return 1;
}

static int Polycode_Entity_get_layerID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->layerID;
	return 1;
}

static int Polycode_Entity_set_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsChildren = param;
	return 0;
}

static int Polycode_Entity_set_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->billboardMode = param;
	return 0;
}

static int Polycode_Entity_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int Polycode_Entity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Polycode_Entity_set_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->visible = param;
	return 0;
}

static int Polycode_Entity_set_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthWrite = param;
	return 0;
}

static int Polycode_Entity_set_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthTest = param;
	return 0;
}

static int Polycode_Entity_set_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->colorAffectsChildren = param;
	return 0;
}

static int Polycode_Entity_set_visibilityAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->visibilityAffectsChildren = param;
	return 0;
}

static int Polycode_Entity_set_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ignoreParentMatrix = param;
	return 0;
}

static int Polycode_Entity_set_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enableScissor = param;
	return 0;
}

static int Polycode_Entity_set_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scissorBox = *argInst;
	return 0;
}

static int Polycode_Entity_set_editorOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->editorOnly = param;
	return 0;
}

static int Polycode_Entity_set_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->id = param;
	return 0;
}

static int Polycode_Entity_set_collisionShapeType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char *argInst = (char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->collisionShapeType = *argInst;
	return 0;
}

static int Polycode_Entity_set_processInputEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->processInputEvents = param;
	return 0;
}

static int Polycode_Entity_set_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->blockMouseInput = param;
	return 0;
}

static int Polycode_Entity_set_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->snapToPixels = param;
	return 0;
}

static int Polycode_Entity_set_mouseOver(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->mouseOver = param;
	return 0;
}

static int Polycode_Entity_set_rendererVis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->rendererVis = param;
	return 0;
}

static int Polycode_Entity_set_layerID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char *argInst = (char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->layerID = *argInst;
	return 0;
}

	static int Polycode_Entity(lua_State *L) {
		Entity *inst = new Entity();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Entity");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Entity_initEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->initEntity();
		return 0;
	}
	static int Polycode_Entity_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(buffer);
		return 0;
	}
	static int Polycode_Entity_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_Entity_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->fixedUpdate();
		return 0;
	}
	static int Polycode_Entity_transformAndRender(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* drawBuffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Polycode::Rectangle* parentScissorBox = (Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 3));
		inst->transformAndRender(drawBuffer, parentScissorBox);
		return 0;
	}
	static int Polycode_Entity_renderChildren(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Polycode::Rectangle* parentScissorBox = (Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 3));
		inst->renderChildren(buffer, parentScissorBox);
		return 0;
	}
	static int Polycode_Entity_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_Entity_dirtyMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->dirtyMatrix(val);
		return 0;
	}
	static int Polycode_Entity_rebuildTransformMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildTransformMatrix();
		return 0;
	}
	static int Polycode_Entity_updateEntityMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->updateEntityMatrix();
		return 0;
	}
	static int Polycode_Entity_getTransformMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getTransformMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getConcatenatedMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getConcatenatedMatrixRelativeTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* relativeEntity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedMatrixRelativeTo(relativeEntity);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getAnchorAdjustedMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getAnchorAdjustedMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getConcatenatedRollMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getConcatenatedRollMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setTransformByMatrixPure(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setTransformByMatrixPure(matrix);
		return 0;
	}
	static int Polycode_Entity_getLookAtMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 loc = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getLookAtMatrix(loc, upVector);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_addChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* newChild = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addChild(newChild);
		return 0;
	}
	static int Polycode_Entity_removeChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entityToRemove = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeChild(entityToRemove);
		return 0;
	}
	static int Polycode_Entity_moveChildUp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->moveChildUp(child);
		return 0;
	}
	static int Polycode_Entity_moveChildDown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->moveChildDown(child);
		return 0;
	}
	static int Polycode_Entity_moveChildTop(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->moveChildTop(child);
		return 0;
	}
	static int Polycode_Entity_moveChildBottom(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* child = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->moveChildBottom(child);
		return 0;
	}
	static int Polycode_Entity_setParentEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParentEntity(entity);
		return 0;
	}
	static int Polycode_Entity_getParentEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentEntity();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_getNumChildren(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumChildren());
		return 1;
	}
	static int Polycode_Entity_getChildAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getChildAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_setOwnsChildrenRecursive(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setOwnsChildrenRecursive(val);
		return 0;
	}
	static int Polycode_Entity_getPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPosition();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getPosition2D(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getPosition2D();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getCombinedPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getCombinedPosition();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		Number z;
		if(lua_isnumber(L, 4)) {
			z = lua_tonumber(L, 4);
		} else {
			z = 0.0;
		}
		inst->setPosition(x, y, z);
		return 0;
	}
	static int Polycode_Entity_setPositionX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		inst->setPositionX(x);
		return 0;
	}
	static int Polycode_Entity_setPositionY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		inst->setPositionY(y);
		return 0;
	}
	static int Polycode_Entity_Translate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		Number z;
		if(lua_isnumber(L, 4)) {
			z = lua_tonumber(L, 4);
		} else {
			z = 0.0;
		}
		inst->Translate(x, y, z);
		return 0;
	}
	static int Polycode_Entity_setPositionZ(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number z = lua_tonumber(L, 2);
		inst->setPositionZ(z);
		return 0;
	}
	static int Polycode_Entity_setScaleX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		inst->setScaleX(x);
		return 0;
	}
	static int Polycode_Entity_setScaleY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		inst->setScaleY(y);
		return 0;
	}
	static int Polycode_Entity_setScaleZ(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number z = lua_tonumber(L, 2);
		inst->setScaleZ(z);
		return 0;
	}
	static int Polycode_Entity_Scale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		Number z;
		if(lua_isnumber(L, 4)) {
			z = lua_tonumber(L, 4);
		} else {
			z = 0.0;
		}
		inst->Scale(x, y, z);
		return 0;
	}
	static int Polycode_Entity_setScale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		Number z;
		if(lua_isnumber(L, 4)) {
			z = lua_tonumber(L, 4);
		} else {
			z = 1.0;
		}
		inst->setScale(x, y, z);
		return 0;
	}
	static int Polycode_Entity_getCompoundScale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getCompoundScale();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getScale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getScale();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getRotationEuler(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getRotationEuler();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getCombinedPitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getCombinedPitch());
		return 1;
	}
	static int Polycode_Entity_getCombinedYaw(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getCombinedYaw());
		return 1;
	}
	static int Polycode_Entity_getCombinedRoll(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getCombinedRoll());
		return 1;
	}
	static int Polycode_Entity_rebuildRotation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildRotation();
		return 0;
	}
	static int Polycode_Entity_setRotationEuler(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 rotation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRotationEuler(rotation);
		return 0;
	}
	static int Polycode_Entity_setPitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number pitch = lua_tonumber(L, 2);
		inst->setPitch(pitch);
		return 0;
	}
	static int Polycode_Entity_setYaw(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number yaw = lua_tonumber(L, 2);
		inst->setYaw(yaw);
		return 0;
	}
	static int Polycode_Entity_setRoll(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number roll = lua_tonumber(L, 2);
		inst->setRoll(roll);
		return 0;
	}
	static int Polycode_Entity_Roll(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number roll = lua_tonumber(L, 2);
		inst->Roll(roll);
		return 0;
	}
	static int Polycode_Entity_Yaw(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number yaw = lua_tonumber(L, 2);
		inst->Yaw(yaw);
		return 0;
	}
	static int Polycode_Entity_Pitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number pitch = lua_tonumber(L, 2);
		inst->Pitch(pitch);
		return 0;
	}
	static int Polycode_Entity_getPitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPitch());
		return 1;
	}
	static int Polycode_Entity_getYaw(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getYaw());
		return 1;
	}
	static int Polycode_Entity_getRoll(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getRoll());
		return 1;
	}
	static int Polycode_Entity_getWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getWidth());
		return 1;
	}
	static int Polycode_Entity_getHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getHeight());
		return 1;
	}
	static int Polycode_Entity_getDepth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getDepth());
		return 1;
	}
	static int Polycode_Entity_setWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number width = lua_tonumber(L, 2);
		inst->setWidth(width);
		return 0;
	}
	static int Polycode_Entity_setHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number height = lua_tonumber(L, 2);
		inst->setHeight(height);
		return 0;
	}
	static int Polycode_Entity_setDepth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number depth = lua_tonumber(L, 2);
		inst->setDepth(depth);
		return 0;
	}
	static int Polycode_Entity_setRotationQuat(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number x = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number y = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number z = lua_tonumber(L, 5);
		inst->setRotationQuat(w, x, y, z);
		return 0;
	}
	static int Polycode_Entity_setRotationByQuaternion(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Quaternion quaternion = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRotationByQuaternion(quaternion);
		return 0;
	}
	static int Polycode_Entity_getRotationQuat(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Quaternion *retInst = new Quaternion();
		*retInst = inst->getRotationQuat();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getConcatenatedQuat(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Quaternion *retInst = new Quaternion();
		*retInst = inst->getConcatenatedQuat();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_lookAt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 loc = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->lookAt(loc, upVector);
		return 0;
	}
	static int Polycode_Entity_lookAtEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->lookAtEntity(entity, upVector);
		return 0;
	}
	static int Polycode_Entity_getCombinedColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Color *retInst = new Color();
		*retInst = inst->getCombinedColor();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number a = lua_tonumber(L, 5);
		inst->setColor(r, g, b, a);
		return 0;
	}
	static int Polycode_Entity_setColorInt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int r = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int g = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int b = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int a = lua_tointeger(L, 5);
		inst->setColorInt(r, g, b, a);
		return 0;
	}
	static int Polycode_Entity_setAnchorPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 anchorPoint = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setAnchorPoint(anchorPoint);
		return 0;
	}
	static int Polycode_Entity_getAnchorPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getAnchorPoint();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_onMouseDown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int mouseButton = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int timestamp = lua_tointeger(L, 4);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseDown(ray, mouseButton, timestamp);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.MouseEventResult");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_onMouseUp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int mouseButton = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int timestamp = lua_tointeger(L, 4);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseUp(ray, mouseButton, timestamp);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.MouseEventResult");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_onMouseMove(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int timestamp = lua_tointeger(L, 3);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseMove(ray, timestamp);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.MouseEventResult");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_onMouseWheelUp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int timestamp = lua_tointeger(L, 3);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseWheelUp(ray, timestamp);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.MouseEventResult");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_onMouseWheelDown(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int timestamp = lua_tointeger(L, 3);
		MouseEventResult *retInst = new MouseEventResult();
		*retInst = inst->onMouseWheelDown(ray, timestamp);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.MouseEventResult");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setDepthOnly(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setDepthOnly(val);
		return 0;
	}
	static int Polycode_Entity_getDepthOnly(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getDepthOnly());
		return 1;
	}
	static int Polycode_Entity_setUserData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* userData = (void*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setUserData(userData);
		return 0;
	}
	static int Polycode_Entity_getUserData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getUserData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_setBlendingMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newBlendingMode = lua_tointeger(L, 2);
		inst->setBlendingMode(newBlendingMode);
		return 0;
	}
	static int Polycode_Entity_getBlendingMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getBlendingMode());
		return 1;
	}
	static int Polycode_Entity_getEntityById(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String id = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool recursive = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->getEntityById(id, recursive);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_getEntitiesByTag(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String tag = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool recursive = lua_toboolean(L, 3) != 0;
		std::vector<Entity*> retVector = inst->getEntitiesByTag(tag, recursive);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_Entity_getEntitiesByLayerID(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		char layerID = *(char*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool recursive = lua_toboolean(L, 3) != 0;
		std::vector<Entity*> retVector = inst->getEntitiesByLayerID(layerID, recursive);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_Entity_getEntityProp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String propName = String(lua_tostring(L, 2));
		lua_pushstring(L, inst->getEntityProp(propName).c_str());
		return 1;
	}
	static int Polycode_Entity_setEntityProp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String propName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String propValue = String(lua_tostring(L, 3));
		inst->setEntityProp(propName, propValue);
		return 0;
	}
	static int Polycode_Entity_setInverseY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setInverseY(val);
		return 0;
	}
	static int Polycode_Entity_getInverseY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getInverseY());
		return 1;
	}
	static int Polycode_Entity_doUpdates(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->doUpdates();
		return 0;
	}
	static int Polycode_Entity_doFixedUpdates(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->doFixedUpdates();
		return 0;
	}
	static int Polycode_Entity_buildPositionMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->buildPositionMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setRenderer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Renderer* renderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRenderer(renderer);
		return 0;
	}
	static int Polycode_Entity_customHitDetection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushboolean(L, inst->customHitDetection(ray));
		return 1;
	}
	static int Polycode_Entity_getNumTags(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumTags());
		return 1;
	}
	static int Polycode_Entity_getTagAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		lua_pushstring(L, inst->getTagAtIndex(index).c_str());
		return 1;
	}
	static int Polycode_Entity_hasTag(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String tag = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->hasTag(tag));
		return 1;
	}
	static int Polycode_Entity_clearTags(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearTags();
		return 0;
	}
	static int Polycode_Entity_addTag(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String tag = String(lua_tostring(L, 2));
		inst->addTag(tag);
		return 0;
	}
	static int Polycode_Entity_getScreenPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 projectionMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Matrix4 cameraMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 4));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getScreenPosition(projectionMatrix, cameraMatrix, viewport);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_recalculateAABBAllChildren(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recalculateAABBAllChildren();
		return 0;
	}
	static int Polycode_Entity_recalculateAABB(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recalculateAABB();
		return 0;
	}
	static int Polycode_Entity_getWorldAABB(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		AABB *retInst = new AABB();
		*retInst = inst->getWorldAABB();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.AABB");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_getLocalBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getLocalBoundingBox();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Entity_setLocalBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 box = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setLocalBoundingBox(box);
		return 0;
	}
	static int Polycode_Entity_setLocalBoundingBoxX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		inst->setLocalBoundingBoxX(x);
		return 0;
	}
	static int Polycode_Entity_setLocalBoundingBoxY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		inst->setLocalBoundingBoxY(y);
		return 0;
	}
	static int Polycode_Entity_setLocalBoundingBoxZ(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number z = lua_tonumber(L, 2);
		inst->setLocalBoundingBoxZ(z);
		return 0;
	}
	static int Polycode_Entity_setContainerScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setContainerScene(scene);
		return 0;
	}
	static int Polycode_Entity_getContainerScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getContainerScene();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Entity_attachScript(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Script* script = (Script*) *((PolyBase**)lua_touserdata(L, 2));
		inst->attachScript(script);
		return 0;
	}
	static int Polycode_Entity_detachScript(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Script* script = (Script*) *((PolyBase**)lua_touserdata(L, 2));
		inst->detachScript(script);
		return 0;
	}
	static int Polycode_Entity_getNumScripts(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumScripts());
		return 1;
	}
	static int Polycode_Entity_getScriptAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity *inst = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getScriptAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_Entity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Entity*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Event_get_deleteOnDispatch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->deleteOnDispatch);
	return 1;
}

static int Polycode_Event_get_cancelEventFlag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->cancelEventFlag);
	return 1;
}

static int Polycode_Event_set_deleteOnDispatch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->deleteOnDispatch = param;
	return 0;
}

static int Polycode_Event_set_cancelEventFlag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->cancelEventFlag = param;
	return 0;
}

	static int Polycode_Event(lua_State *L) {
		Event *inst = new Event();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Event");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Event_getEventCode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getEventCode());
		return 1;
	}
	static int Polycode_Event_getDispatcher(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getDispatcher();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Event_setEventCode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 2);
		inst->setEventCode(eventCode);
		return 0;
	}
	static int Polycode_Event_setDispatcher(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventDispatcher* dispatcher = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setDispatcher(dispatcher);
		return 0;
	}
	static int Polycode_Event_getEventType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getEventType().c_str());
		return 1;
	}
	static int Polycode_Event_cancelEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Event *inst = (Event*) *((PolyBase**)lua_touserdata(L, 1));
		inst->cancelEvent();
		return 0;
	}
	static int Polycode_delete_Event(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Event*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_EventDispatcher(lua_State *L) {
		EventDispatcher *inst = new EventDispatcher();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.EventDispatcher");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_EventDispatcher_removeAllHandlers(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		inst->removeAllHandlers();
		return 0;
	}
	static int Polycode_EventDispatcher_removeAllHandlersForListener(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeAllHandlersForListener(handler);
		return 0;
	}
	static int Polycode_EventDispatcher_addEventListener(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->addEventListener(handler, eventCode);
		return 0;
	}
	static int Polycode_EventDispatcher_addEventListenerUnique(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->addEventListenerUnique(handler, eventCode);
		return 0;
	}
	static int Polycode_EventDispatcher_hasEventListener(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		lua_pushboolean(L, inst->hasEventListener(handler, eventCode));
		return 1;
	}
	static int Polycode_EventDispatcher_removeEventListener(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		EventHandler* handler = (EventHandler*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->removeEventListener(handler, eventCode);
		return 0;
	}
	static int Polycode_EventDispatcher___dispatchEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->__dispatchEvent(event, eventCode);
		return 0;
	}
	static int Polycode_EventDispatcher_dispatchEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->dispatchEvent(event, eventCode);
		return 0;
	}
	static int Polycode_EventDispatcher_dispatchEventNoDelete(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		EventDispatcher *inst = (EventDispatcher*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Event* event = (Event*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int eventCode = lua_tointeger(L, 3);
		inst->dispatchEventNoDelete(event, eventCode);
		return 0;
	}
	static int Polycode_delete_EventDispatcher(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((EventDispatcher*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_EventHandler(lua_State *L) {
		LuaEventHandler *inst = new LuaEventHandler();
		inst->wrapperIndex = luaL_ref(L, LUA_REGISTRYINDEX );
		inst->L = L;
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.EventHandler");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_EventHandler(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((EventHandler*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Font_get_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->loaded);
	return 1;
}

static int Polycode_Font_set_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->loaded = param;
	return 0;
}

	static int Polycode_Font(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		FT_Library FTLibrary = *(FT_Library*) *((PolyBase**)lua_touserdata(L, 2));
		Font *inst = new Font(fileName, FTLibrary);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Font");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Font_getFace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		FT_Face *retInst = new FT_Face();
		*retInst = inst->getFace();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.FT_Face");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Font_isValid(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isValid());
		return 1;
	}
	static int Polycode_Font_setFontName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fontName = String(lua_tostring(L, 2));
		inst->setFontName(fontName);
		return 0;
	}
	static int Polycode_Font_getFontName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getFontName().c_str());
		return 1;
	}
	static int Polycode_Font_getFontPath(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font *inst = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getFontPath().c_str());
		return 1;
	}
	static int Polycode_delete_Font(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Font*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_LightInfo_get_importance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->importance);
	return 1;
}

static int Polycode_LightInfo_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->position;
	return 1;
}

static int Polycode_LightInfo_get_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->direction;
	return 1;
}

static int Polycode_LightInfo_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_LightInfo_get_diffuseColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->diffuseColor;
	return 1;
}

static int Polycode_LightInfo_get_specularColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->specularColor;
	return 1;
}

static int Polycode_LightInfo_get_constantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->constantAttenuation);
	return 1;
}

static int Polycode_LightInfo_get_linearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->linearAttenuation);
	return 1;
}

static int Polycode_LightInfo_get_quadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->quadraticAttenuation);
	return 1;
}

static int Polycode_LightInfo_get_intensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->intensity);
	return 1;
}

static int Polycode_LightInfo_get_spotlightCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->spotlightCutoff);
	return 1;
}

static int Polycode_LightInfo_get_spotlightExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->spotlightExponent);
	return 1;
}

static int Polycode_LightInfo_get_shadowsEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->shadowsEnabled);
	return 1;
}

static int Polycode_LightInfo_get_shadowMapTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shadowMapTexture) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shadowMapTexture;
	}
	return 1;
}

static int Polycode_LightInfo_get_lightViewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->lightViewMatrix;
	return 1;
}

static int Polycode_LightInfo_set_importance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->importance = param;
	return 0;
}

static int Polycode_LightInfo_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycode_LightInfo_set_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->direction = *argInst;
	return 0;
}

static int Polycode_LightInfo_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_LightInfo_set_diffuseColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->diffuseColor = *argInst;
	return 0;
}

static int Polycode_LightInfo_set_specularColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->specularColor = *argInst;
	return 0;
}

static int Polycode_LightInfo_set_constantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->constantAttenuation = param;
	return 0;
}

static int Polycode_LightInfo_set_linearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->linearAttenuation = param;
	return 0;
}

static int Polycode_LightInfo_set_quadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->quadraticAttenuation = param;
	return 0;
}

static int Polycode_LightInfo_set_intensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->intensity = param;
	return 0;
}

static int Polycode_LightInfo_set_spotlightCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->spotlightCutoff = param;
	return 0;
}

static int Polycode_LightInfo_set_spotlightExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->spotlightExponent = param;
	return 0;
}

static int Polycode_LightInfo_set_shadowsEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->shadowsEnabled = param;
	return 0;
}

static int Polycode_LightInfo_set_shadowMapTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* *argInst = (Texture**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shadowMapTexture = *argInst;
	return 0;
}

static int Polycode_LightInfo_set_lightViewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfo *inst = (LightInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->lightViewMatrix = *argInst;
	return 0;
}

	static int Polycode_delete_LightInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((LightInfo*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_GPUDrawCall_get_mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->mesh) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->mesh;
	}
	return 1;
}

static int Polycode_GPUDrawCall_get_options(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->options;
	return 1;
}

static int Polycode_GPUDrawCall_get_modelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->modelMatrix;
	return 1;
}

static int Polycode_GPUDrawCall_get_material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->material) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->material;
	}
	return 1;
}

static int Polycode_GPUDrawCall_set_mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Mesh* *argInst = (Mesh**) *((PolyBase**)lua_touserdata(L, 2));
	inst->mesh = *argInst;
	return 0;
}

static int Polycode_GPUDrawCall_set_options(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	GPUDrawOptions *argInst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 2));
	inst->options = *argInst;
	return 0;
}

static int Polycode_GPUDrawCall_set_modelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->modelMatrix = *argInst;
	return 0;
}

static int Polycode_GPUDrawCall_set_material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawCall *inst = (GPUDrawCall*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* *argInst = (Material**) *((PolyBase**)lua_touserdata(L, 2));
	inst->material = *argInst;
	return 0;
}

	static int Polycode_delete_GPUDrawCall(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((GPUDrawCall*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_GPUDrawOptions_get_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthTest);
	return 1;
}

static int Polycode_GPUDrawOptions_get_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthWrite);
	return 1;
}

static int Polycode_GPUDrawOptions_get_linePointSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->linePointSize);
	return 1;
}

static int Polycode_GPUDrawOptions_get_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->alphaTest);
	return 1;
}

static int Polycode_GPUDrawOptions_get_backfaceCull(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->backfaceCull);
	return 1;
}

static int Polycode_GPUDrawOptions_get_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthOnly);
	return 1;
}

static int Polycode_GPUDrawOptions_get_forceMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->forceMaterial);
	return 1;
}

static int Polycode_GPUDrawOptions_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycode_GPUDrawOptions_get_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scissorBox;
	return 1;
}

static int Polycode_GPUDrawOptions_get_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enableScissor);
	return 1;
}

static int Polycode_GPUDrawOptions_get_drawColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->drawColor;
	return 1;
}

static int Polycode_GPUDrawOptions_set_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthTest = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthWrite = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_linePointSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->linePointSize = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->alphaTest = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_backfaceCull(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->backfaceCull = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthOnly = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_forceMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->forceMaterial = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_scissorBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scissorBox = *argInst;
	return 0;
}

static int Polycode_GPUDrawOptions_set_enableScissor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enableScissor = param;
	return 0;
}

static int Polycode_GPUDrawOptions_set_drawColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawOptions *inst = (GPUDrawOptions*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->drawColor = *argInst;
	return 0;
}

	static int Polycode_delete_GPUDrawOptions(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((GPUDrawOptions*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_GPUDrawBuffer_get_targetFramebuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->targetFramebuffer) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->targetFramebuffer;
	}
	return 1;
}

static int Polycode_GPUDrawBuffer_get_projectionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->projectionMatrix;
	return 1;
}

static int Polycode_GPUDrawBuffer_get_viewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->viewMatrix;
	return 1;
}

static int Polycode_GPUDrawBuffer_get_cameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->cameraMatrix;
	return 1;
}

static int Polycode_GPUDrawBuffer_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->clearColor;
	return 1;
}

static int Polycode_GPUDrawBuffer_get_clearDepthBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clearDepthBuffer);
	return 1;
}

static int Polycode_GPUDrawBuffer_get_clearColorBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clearColorBuffer);
	return 1;
}

static int Polycode_GPUDrawBuffer_get_backingResolutionScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->backingResolutionScale;
	return 1;
}

static int Polycode_GPUDrawBuffer_get_globalMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->globalMaterial) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->globalMaterial;
	}
	return 1;
}

static int Polycode_GPUDrawBuffer_get_viewport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->viewport;
	return 1;
}

static int Polycode_GPUDrawBuffer_set_targetFramebuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderBuffer* *argInst = (RenderBuffer**) *((PolyBase**)lua_touserdata(L, 2));
	inst->targetFramebuffer = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_projectionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->projectionMatrix = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_viewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->viewMatrix = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_cameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Matrix4 *argInst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
	inst->cameraMatrix = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->clearColor = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_clearDepthBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clearDepthBuffer = param;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_clearColorBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clearColorBuffer = param;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_backingResolutionScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->backingResolutionScale = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_globalMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Material* *argInst = (Material**) *((PolyBase**)lua_touserdata(L, 2));
	inst->globalMaterial = *argInst;
	return 0;
}

static int Polycode_GPUDrawBuffer_set_viewport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GPUDrawBuffer *inst = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->viewport = *argInst;
	return 0;
}

	static int Polycode_GPUDrawBuffer(lua_State *L) {
		GPUDrawBuffer *inst = new GPUDrawBuffer();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.GPUDrawBuffer");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_GPUDrawBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((GPUDrawBuffer*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Image(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		Image *inst = new Image(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Image");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Image_BlankImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int width = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		int height = lua_tointeger(L, 2);
		int type;
		if(lua_isnumber(L, 3)) {
			type = lua_tointeger(L, 3);
		} else {
			type = Image :: IMAGE_RGBA;
		}
		PolyBase *ptrRetVal = (PolyBase*)Image::BlankImage(width, height, type);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Image_loadImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->loadImage(fileName));
		return 1;
	}
	static int Polycode_Image_saveImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->saveImage(fileName));
		return 1;
	}
	static int Polycode_Image_pasteImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int x = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int y = lua_tointeger(L, 4);
		int blendingMode;
		if(lua_isnumber(L, 5)) {
			blendingMode = lua_tointeger(L, 5);
		} else {
			blendingMode = 0;
		}
		Number blendAmount;
		if(lua_isnumber(L, 6)) {
			blendAmount = lua_tonumber(L, 6);
		} else {
			blendAmount = 1.0;
		}
		luaL_checktype(L, 7, LUA_TUSERDATA);
		Color blendColor = *(Color*) *((PolyBase**)lua_touserdata(L, 7));
		inst->pasteImage(image, x, y, blendingMode, blendAmount, blendColor);
		return 0;
	}
	static int Polycode_Image_createEmpty(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int width = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int height = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Color fillColor = *(Color*) *((PolyBase**)lua_touserdata(L, 4));
		inst->createEmpty(width, height, fillColor);
		return 0;
	}
	static int Polycode_Image_fill(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		inst->fill(color);
		return 0;
	}
	static int Polycode_Image_setPixel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number r = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number g = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number b = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number a = lua_tonumber(L, 7);
		inst->setPixel(x, y, r, g, b, a);
		return 0;
	}
	static int Polycode_Image_getPixel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		Color *retInst = new Color();
		*retInst = inst->getPixel(x, y);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Image_swap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		int* v1 = (int*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		int* v2 = (int*) *((PolyBase**)lua_touserdata(L, 3));
		inst->swap(v1, v2);
		return 0;
	}
	static int Polycode_Image_drawLine(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x0 = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y0 = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int x1 = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int y1 = lua_tointeger(L, 5);
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
		inst->drawLine(x0, y0, x1, y1, col);
		return 0;
	}
	static int Polycode_Image_moveBrushTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		inst->moveBrushTo(x, y);
		return 0;
	}
	static int Polycode_Image_moveBrush(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		inst->moveBrush(x, y);
		return 0;
	}
	static int Polycode_Image_drawLineTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 4));
		inst->drawLineTo(x, y, col);
		return 0;
	}
	static int Polycode_Image_fillRect(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int w = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int h = lua_tointeger(L, 5);
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Color col = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
		inst->fillRect(x, y, w, h, col);
		return 0;
	}
	static int Polycode_Image_perlinNoise(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int seed = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool alpha = lua_toboolean(L, 3) != 0;
		inst->perlinNoise(seed, alpha);
		return 0;
	}
	static int Polycode_Image_fastBlur(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int blurSize = lua_tointeger(L, 2);
		inst->fastBlur(blurSize);
		return 0;
	}
	static int Polycode_Image_fastBlurVert(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int blurSize = lua_tointeger(L, 2);
		inst->fastBlurVert(blurSize);
		return 0;
	}
	static int Polycode_Image_fastBlurHor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int blurSize = lua_tointeger(L, 2);
		inst->fastBlurHor(blurSize);
		return 0;
	}
	static int Polycode_Image_getPixelsInRect(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int width = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int height = lua_tointeger(L, 5);
		PolyBase *ptrRetVal = (PolyBase*)inst->getPixelsInRect(x, y, width, height);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Image_getImagePart(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle subRect = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getImagePart(subRect);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Image_getBrushX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getBrushX());
		return 1;
	}
	static int Polycode_Image_getBrushY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getBrushY());
		return 1;
	}
	static int Polycode_Image_isLoaded(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isLoaded());
		return 1;
	}
	static int Polycode_Image_getType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getType());
		return 1;
	}
	static int Polycode_Image_getWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getWidth());
		return 1;
	}
	static int Polycode_Image_getHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getHeight());
		return 1;
	}
	static int Polycode_Image_getPixels(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getPixels();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Image_premultiplyAlpha(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		inst->premultiplyAlpha();
		return 0;
	}
	static int Polycode_Image_savePNG(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image *inst = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->savePNG(fileName));
		return 1;
	}
	static int Polycode_delete_Image(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Image*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_TouchInfo_get_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->id);
	return 1;
}

static int Polycode_TouchInfo_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->position;
	return 1;
}

static int Polycode_TouchInfo_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_TouchInfo_set_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->id = param;
	return 0;
}

static int Polycode_TouchInfo_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycode_TouchInfo_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	TouchInfo *inst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

	static int Polycode_TouchInfo(lua_State *L) {
		TouchInfo *inst = new TouchInfo();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.TouchInfo");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_TouchInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((TouchInfo*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_InputEvent_get_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->mouseButton);
	return 1;
}

static int Polycode_InputEvent_get_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->mousePosition;
	return 1;
}

static int Polycode_InputEvent_get_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->key);
	return 1;
}

static int Polycode_InputEvent_get_charCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->charCode;
	return 1;
}

static int Polycode_InputEvent_get_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->timestamp);
	return 1;
}

static int Polycode_InputEvent_get_touch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->touch;
	return 1;
}

static int Polycode_InputEvent_get_touchType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->touchType);
	return 1;
}

static int Polycode_InputEvent_get_joystickDeviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickDeviceID);
	return 1;
}

static int Polycode_InputEvent_get_joystickAxisValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->joystickAxisValue);
	return 1;
}

static int Polycode_InputEvent_get_joystickButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickButton);
	return 1;
}

static int Polycode_InputEvent_get_joystickAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickAxis);
	return 1;
}

static int Polycode_InputEvent_get_joystickIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->joystickIndex);
	return 1;
}

static int Polycode_InputEvent_get_hitDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->hitDistance);
	return 1;
}

static int Polycode_InputEvent_set_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->mouseButton = param;
	return 0;
}

static int Polycode_InputEvent_set_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->mousePosition = *argInst;
	return 0;
}

static int Polycode_InputEvent_set_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	PolyKEY param = (PolyKEY)lua_tointeger(L, 2);
	inst->key = param;
	return 0;
}

static int Polycode_InputEvent_set_charCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	wchar_t *argInst = (wchar_t*) *((PolyBase**)lua_touserdata(L, 2));
	inst->charCode = *argInst;
	return 0;
}

static int Polycode_InputEvent_set_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->timestamp = param;
	return 0;
}

static int Polycode_InputEvent_set_touch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	TouchInfo *argInst = (TouchInfo*) *((PolyBase**)lua_touserdata(L, 2));
	inst->touch = *argInst;
	return 0;
}

static int Polycode_InputEvent_set_touchType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->touchType = param;
	return 0;
}

static int Polycode_InputEvent_set_joystickDeviceID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickDeviceID = param;
	return 0;
}

static int Polycode_InputEvent_set_joystickAxisValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->joystickAxisValue = param;
	return 0;
}

static int Polycode_InputEvent_set_joystickButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickButton = param;
	return 0;
}

static int Polycode_InputEvent_set_joystickAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickAxis = param;
	return 0;
}

static int Polycode_InputEvent_set_joystickIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->joystickIndex = param;
	return 0;
}

static int Polycode_InputEvent_set_hitDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->hitDistance = param;
	return 0;
}

	static int Polycode_InputEvent(lua_State *L) {
		InputEvent *inst = new InputEvent();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.InputEvent");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_InputEvent_getMousePosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getMousePosition();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_InputEvent_getKey(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getKey());
		return 1;
	}
	static int Polycode_InputEvent_getMouseButton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getMouseButton());
		return 1;
	}
	static int Polycode_InputEvent_getCharCode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
		wchar_t *retInst = new wchar_t();
		*retInst = inst->getCharCode();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.wchar_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_InputEvent_keyCode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		InputEvent *inst = (InputEvent*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->keyCode());
		return 1;
	}
	static int Polycode_delete_InputEvent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((InputEvent*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_GlyphData_get_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->glyphs) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->glyphs;
	}
	return 1;
}

static int Polycode_GlyphData_get_positions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->positions) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->positions;
	}
	return 1;
}

static int Polycode_GlyphData_get_num_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->num_glyphs;
	return 1;
}

static int Polycode_GlyphData_get_trailingAdvance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->trailingAdvance);
	return 1;
}

static int Polycode_GlyphData_set_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FT_Glyph* *argInst = (FT_Glyph**) *((PolyBase**)lua_touserdata(L, 2));
	inst->glyphs = *argInst;
	return 0;
}

static int Polycode_GlyphData_set_positions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FT_Vector* *argInst = (FT_Vector**) *((PolyBase**)lua_touserdata(L, 2));
	inst->positions = *argInst;
	return 0;
}

static int Polycode_GlyphData_set_num_glyphs(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	FT_UInt *argInst = (FT_UInt*) *((PolyBase**)lua_touserdata(L, 2));
	inst->num_glyphs = *argInst;
	return 0;
}

static int Polycode_GlyphData_set_trailingAdvance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->trailingAdvance = param;
	return 0;
}

	static int Polycode_GlyphData(lua_State *L) {
		GlyphData *inst = new GlyphData();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.GlyphData");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_GlyphData_clearData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		GlyphData *inst = (GlyphData*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearData();
		return 0;
	}
	static int Polycode_delete_GlyphData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((GlyphData*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ColorRange_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int Polycode_ColorRange_get_rangeStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->rangeStart);
	return 1;
}

static int Polycode_ColorRange_get_rangeEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->rangeEnd);
	return 1;
}

static int Polycode_ColorRange_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int Polycode_ColorRange_set_rangeStart(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->rangeStart = param;
	return 0;
}

static int Polycode_ColorRange_set_rangeEnd(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ColorRange *inst = (ColorRange*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->rangeEnd = param;
	return 0;
}

	static int Polycode_ColorRange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int rangeStart = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int rangeEnd = lua_tointeger(L, 3);
		ColorRange *inst = new ColorRange(color, rangeStart, rangeEnd);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ColorRange");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_ColorRange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ColorRange*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Label(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Font* font = (Font*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String text = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int size = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int antiAliasMode = lua_tointeger(L, 4);
		bool premultiplyAlpha;
		if(lua_isboolean(L, 5)) {
			premultiplyAlpha = lua_toboolean(L, 5) != 0;
		} else {
			premultiplyAlpha = false;
		}
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Color backgroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 6));
		luaL_checktype(L, 7, LUA_TUSERDATA);
		Color foregroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 7));
		Label *inst = new Label(font, text, size, antiAliasMode, premultiplyAlpha, backgroundColor, foregroundColor);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Label");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Label_setText(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String text = String(lua_tostring(L, 2));
		inst->setText(text);
		return 0;
	}
	static int Polycode_Label_getText(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getText().c_str());
		return 1;
	}
	static int Polycode_Label_getTextWidthForString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String text = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->getTextWidthForString(text));
		return 1;
	}
	static int Polycode_Label_getTextHeightForString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String text = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->getTextHeightForString(text));
		return 1;
	}
	static int Polycode_Label_getTextWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getTextWidth());
		return 1;
	}
	static int Polycode_Label_getTextHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getTextHeight());
		return 1;
	}
	static int Polycode_Label_setColorForRange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int rangeStart = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int rangeEnd = lua_tointeger(L, 4);
		inst->setColorForRange(color, rangeStart, rangeEnd);
		return 0;
	}
	static int Polycode_Label_clearColors(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearColors();
		return 0;
	}
	static int Polycode_Label_getColorForIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		Color *retInst = new Color();
		*retInst = inst->getColorForIndex(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Label_getPremultiplyAlpha(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getPremultiplyAlpha());
		return 1;
	}
	static int Polycode_Label_setPremultiplyAlpha(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setPremultiplyAlpha(val);
		return 0;
	}
	static int Polycode_Label_setFont(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Font* newFont = (Font*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setFont(newFont);
		return 0;
	}
	static int Polycode_Label_getFont(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getFont();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Label_setSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newSize = lua_tointeger(L, 2);
		inst->setSize(newSize);
		return 0;
	}
	static int Polycode_Label_getSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getSize());
		return 1;
	}
	static int Polycode_Label_getAntialiasMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getAntialiasMode());
		return 1;
	}
	static int Polycode_Label_setAntialiasMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newMode = lua_tointeger(L, 2);
		inst->setAntialiasMode(newMode);
		return 0;
	}
	static int Polycode_Label_getBaselineAdjust(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getBaselineAdjust());
		return 1;
	}
	static int Polycode_Label_setBackgroundColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setBackgroundColor(color);
		return 0;
	}
	static int Polycode_Label_setForegroundColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setForegroundColor(color);
		return 0;
	}
	static int Polycode_Label_setColors(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color backgroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Color foregroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setColors(backgroundColor, foregroundColor);
		return 0;
	}
	static int Polycode_Label_getBackgroundColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		Color *retInst = new Color();
		*retInst = inst->getBackgroundColor();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Label_getForegroundColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		Color *retInst = new Color();
		*retInst = inst->getForegroundColor();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Label_optionsChanged(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Label *inst = (Label*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->optionsChanged());
		return 1;
	}
	static int Polycode_delete_Label(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Label*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Material_get_fp16RenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->fp16RenderTargets);
	return 1;
}

static int Polycode_Material_get_shaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shaderModule) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shaderModule;
	}
	return 1;
}

static int Polycode_Material_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycode_Material_get_screenMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->screenMaterial);
	return 1;
}

static int Polycode_Material_set_fp16RenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->fp16RenderTargets = param;
	return 0;
}

static int Polycode_Material_set_shaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shaderModule = *argInst;
	return 0;
}

static int Polycode_Material_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycode_Material_set_screenMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->screenMaterial = param;
	return 0;
}

	static int Polycode_Material(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String name = String(lua_tostring(L, 1));
		Material *inst = new Material(name);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Material");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Material_addShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderPass pass = *(ShaderPass*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addShaderPass(pass);
		return 0;
	}
	static int Polycode_Material_addShaderPassAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderPass pass = *(ShaderPass*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int shaderIndex = lua_tointeger(L, 3);
		inst->addShaderPassAtIndex(pass, shaderIndex);
		return 0;
	}
	static int Polycode_Material_addShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ShaderBinding* shaderBinding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
		inst->addShader(shader, shaderBinding);
		return 0;
	}
	static int Polycode_Material_addShaderAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ShaderBinding* shaderBinding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		int shaderIndex = lua_tointeger(L, 4);
		inst->addShaderAtIndex(shader, shaderBinding, shaderIndex);
		return 0;
	}
	static int Polycode_Material_getNumShaderPasses(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumShaderPasses());
		return 1;
	}
	static int Polycode_Material_removeShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int shaderIndex = lua_tointeger(L, 2);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}
	static int Polycode_Material_recreateExpectedShaderParams(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recreateExpectedShaderParams();
		return 0;
	}
	static int Polycode_Material_addShaderRenderTarget(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderRenderTarget* newTarget = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addShaderRenderTarget(newTarget);
		return 0;
	}
	static int Polycode_Material_getNumShaderRenderTargets(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumShaderRenderTargets());
		return 1;
	}
	static int Polycode_Material_getShaderRenderTarget(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderRenderTarget(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Material_removeShaderRenderTarget(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		inst->removeShaderRenderTarget(index);
		return 0;
	}
	static int Polycode_Material_recreateRenderTarget(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderRenderTarget* renderTarget = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 2));
		inst->recreateRenderTarget(renderTarget);
		return 0;
	}
	static int Polycode_Material_recreateRenderTargets(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recreateRenderTargets();
		return 0;
	}
	static int Polycode_Material_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_Material_getShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.ShaderPass");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Material_getShaderBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Material_getShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShader(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Material_loadMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadMaterial(fileName);
		return 0;
	}
	static int Polycode_Material_setName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->setName(name);
		return 0;
	}
	static int Polycode_Material_clearShaders(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Material *inst = (Material*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearShaders();
		return 0;
	}
	static int Polycode_delete_Material(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Material*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ShaderPass_get_shader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shader) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shader;
	}
	return 1;
}

static int Polycode_ShaderPass_get_wireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->wireframe);
	return 1;
}

static int Polycode_ShaderPass_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycode_ShaderPass_get_shaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shaderBinding) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shaderBinding;
	}
	return 1;
}

static int Polycode_ShaderPass_get_materialShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->materialShaderBinding) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->materialShaderBinding;
	}
	return 1;
}

static int Polycode_ShaderPass_set_shader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* *argInst = (Shader**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shader = *argInst;
	return 0;
}

static int Polycode_ShaderPass_set_wireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->wireframe = param;
	return 0;
}

static int Polycode_ShaderPass_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycode_ShaderPass_set_shaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderBinding* *argInst = (ShaderBinding**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shaderBinding = *argInst;
	return 0;
}

static int Polycode_ShaderPass_set_materialShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderBinding* *argInst = (ShaderBinding**) *((PolyBase**)lua_touserdata(L, 2));
	inst->materialShaderBinding = *argInst;
	return 0;
}

	static int Polycode_ShaderPass(lua_State *L) {
		ShaderPass *inst = new ShaderPass();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ShaderPass");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ShaderPass_setAttributeArraysFromMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setAttributeArraysFromMesh(mesh);
		return 0;
	}
	static int Polycode_ShaderPass_setExpectedAttributes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderPass *inst = (ShaderPass*) *((PolyBase**)lua_touserdata(L, 1));
		inst->setExpectedAttributes();
		return 0;
	}
	static int Polycode_ShaderPass_arrayToAttributeName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		VertexDataArray* array = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, ShaderPass::arrayToAttributeName(array).c_str());
		return 1;
	}
	static int Polycode_delete_ShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ShaderPass*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_MaterialManager_get_premultiplyAlphaOnLoad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->premultiplyAlphaOnLoad);
	return 1;
}

static int Polycode_MaterialManager_get_clampDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clampDefault);
	return 1;
}

static int Polycode_MaterialManager_get_mipmapsDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->mipmapsDefault);
	return 1;
}

static int Polycode_MaterialManager_get_keepTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->keepTextureData);
	return 1;
}

static int Polycode_MaterialManager_set_premultiplyAlphaOnLoad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->premultiplyAlphaOnLoad = param;
	return 0;
}

static int Polycode_MaterialManager_set_clampDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clampDefault = param;
	return 0;
}

static int Polycode_MaterialManager_set_mipmapsDefault(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->mipmapsDefault = param;
	return 0;
}

static int Polycode_MaterialManager_set_keepTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->keepTextureData = param;
	return 0;
}

	static int Polycode_MaterialManager(lua_State *L) {
		MaterialManager *inst = new MaterialManager();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.MaterialManager");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_MaterialManager_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int elapsed = lua_tointeger(L, 2);
		inst->Update(elapsed);
		return 0;
	}
	static int Polycode_MaterialManager_createTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int width = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int height = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TUSERDATA);
		char* imageData = (char*) *((PolyBase**)lua_touserdata(L, 4));
		bool clamp;
		if(lua_isboolean(L, 5)) {
			clamp = lua_toboolean(L, 5) != 0;
		} else {
			clamp = true;
		}
		bool createMipmaps;
		if(lua_isboolean(L, 6)) {
			createMipmaps = lua_toboolean(L, 6) != 0;
		} else {
			createMipmaps = false;
		}
		int type;
		if(lua_isnumber(L, 7)) {
			type = lua_tointeger(L, 7);
		} else {
			type = Image :: IMAGE_RGBA;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width, height, imageData, clamp, createMipmaps, type);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createNewTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int width = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int height = lua_tointeger(L, 3);
		bool clamp;
		if(lua_isboolean(L, 4)) {
			clamp = lua_toboolean(L, 4) != 0;
		} else {
			clamp = true;
		}
		bool createMipmaps;
		if(lua_isboolean(L, 5)) {
			createMipmaps = lua_toboolean(L, 5) != 0;
		} else {
			createMipmaps = false;
		}
		int type;
		if(lua_isnumber(L, 6)) {
			type = lua_tointeger(L, 6);
		} else {
			type = Image :: IMAGE_RGBA;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->createNewTexture(width, height, clamp, createMipmaps, type);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createTextureFromImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 2));
		bool clamp;
		if(lua_isboolean(L, 3)) {
			clamp = lua_toboolean(L, 3) != 0;
		} else {
			clamp = true;
		}
		bool createMipmaps;
		if(lua_isboolean(L, 4)) {
			createMipmaps = lua_toboolean(L, 4) != 0;
		} else {
			createMipmaps = false;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromImage(image, clamp, createMipmaps);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createTextureFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		bool clamp;
		if(lua_isboolean(L, 3)) {
			clamp = lua_toboolean(L, 3) != 0;
		} else {
			clamp = true;
		}
		bool createMipmaps;
		if(lua_isboolean(L, 4)) {
			createMipmaps = lua_toboolean(L, 4) != 0;
		} else {
			createMipmaps = false;
		}
		ResourcePool* resourcePool;
		if(lua_isuserdata(L, 5)) {
			resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 5));
		} else {
			resourcePool = NULL;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->createTextureFromFile(fileName, clamp, createMipmaps, resourcePool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_deleteTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->deleteTexture(texture);
		return 0;
	}
	static int Polycode_MaterialManager_reloadTextures(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadTextures();
		return 0;
	}
	static int Polycode_MaterialManager_reloadProgramsAndTextures(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadProgramsAndTextures();
		return 0;
	}
	static int Polycode_MaterialManager_reloadPrograms(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadPrograms();
		return 0;
	}
	static int Polycode_MaterialManager_getTextureByResourcePath(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String resourcePath = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTextureByResourcePath(resourcePath);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createProgramFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String programPath = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->createProgramFromFile(programPath);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_loadMaterialLibraryIntoPool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String materialFile = String(lua_tostring(L, 3));
		inst->loadMaterialLibraryIntoPool(pool, materialFile);
		return 0;
	}
	static int Polycode_MaterialManager_cubemapFromXMLNode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->cubemapFromXMLNode(node);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_materialFromXMLNode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->materialFromXMLNode(resourcePool, node);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String materialName = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TSTRING);
		String shaderName = String(lua_tostring(L, 4));
		PolyBase *ptrRetVal = (PolyBase*)inst->createMaterial(resourcePool, materialName, shaderName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_setShaderFromXMLNode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->setShaderFromXMLNode(resourcePool, node);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createShaderFromXMLNode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		TiXmlNode* node = (TiXmlNode*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->createShaderFromXMLNode(resourcePool, node);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_createShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String shaderType = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TSTRING);
		String name = String(lua_tostring(L, 4));
		luaL_checktype(L, 5, LUA_TSTRING);
		String vpName = String(lua_tostring(L, 5));
		luaL_checktype(L, 6, LUA_TSTRING);
		String fpName = String(lua_tostring(L, 6));
		luaL_checktype(L, 7, LUA_TBOOLEAN);
		bool screenShader = lua_toboolean(L, 7) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->createShader(resourcePool, shaderType, name, vpName, fpName, screenShader);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_MaterialManager_loadMaterialsFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		std::vector<Material*> retVector = inst->loadMaterialsFromFile(resourcePool, fileName);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_MaterialManager_loadShadersFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		std::vector<Shader*> retVector = inst->loadShadersFromFile(resourcePool, fileName);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_MaterialManager_loadCubemapsFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		std::vector<Cubemap*> retVector = inst->loadCubemapsFromFile(fileName);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_MaterialManager_setAnisotropyAmount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int anisotropy = lua_tointeger(L, 2);
		inst->setAnisotropyAmount(anisotropy);
		return 0;
	}
	static int Polycode_MaterialManager_setTextureFilteringMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int textureFilteringMode = lua_tointeger(L, 2);
		inst->setTextureFilteringMode(textureFilteringMode);
		return 0;
	}
	static int Polycode_MaterialManager_getTextureFilteringMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getTextureFilteringMode());
		return 1;
	}
	static int Polycode_MaterialManager_addMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addMaterial(material);
		return 0;
	}
	static int Polycode_MaterialManager_addShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addShader(shader);
		return 0;
	}
	static int Polycode_MaterialManager_getNumShaders(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumShaders());
		return 1;
	}
	static int Polycode_MaterialManager_getShaderByIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialManager *inst = (MaterialManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderByIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_MaterialManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((MaterialManager*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Matrix4(lua_State *L) {
		Matrix4 *inst = new Matrix4();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Matrix4_identity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		inst->identity();
		return 0;
	}
	static int Polycode_Matrix4_rotateVector(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->rotateVector(v2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_getPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPosition();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_multiplyWithPerspective(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->multiplyWithPerspective(v2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_multVector3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->multVector3(v2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_multVector4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector4 v2 = *(Vector4*) *((PolyBase**)lua_touserdata(L, 2));
		Vector4 *retInst = new Vector4();
		*retInst = inst->multVector4(v2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_Translate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->Translate(x, y, z);
		return 0;
	}
	static int Polycode_Matrix4_setPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->setPosition(x, y, z);
		return 0;
	}
	static int Polycode_Matrix4_setScale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 scale = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setScale(scale);
		return 0;
	}
	static int Polycode_Matrix4_getEulerAngles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Number* ax = (Number*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Number* ay = (Number*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Number* az = (Number*) *((PolyBase**)lua_touserdata(L, 4));
		inst->getEulerAngles(ax, ay, az);
		return 0;
	}
	static int Polycode_Matrix4_transpose(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->transpose();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_Inverse(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->Inverse();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_inverseAffine(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->inverseAffine();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Matrix4_determinant(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->determinant());
		return 1;
	}
	static int Polycode_Matrix4_generalDeterminant(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Number** a = (Number**) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int n = lua_tointeger(L, 2);
		lua_pushnumber(L, Matrix4::generalDeterminant(a, n));
		return 1;
	}
	static int Polycode_Matrix4_setOrthoProjection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number left = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number right = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number bottom = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number top = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number zNear = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number zFar = lua_tonumber(L, 7);
		inst->setOrthoProjection(left, right, bottom, top, zNear, zFar);
		return 0;
	}
	static int Polycode_Matrix4_setProjectionFrustum(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number left = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number right = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number bottom = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number top = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number zNear = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number zFar = lua_tonumber(L, 7);
		inst->setProjectionFrustum(left, right, bottom, top, zNear, zFar);
		return 0;
	}
	static int Polycode_Matrix4_setProjection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Matrix4 *inst = (Matrix4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number fov = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number aspect = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number zNear = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number zFar = lua_tonumber(L, 5);
		inst->setProjection(fov, aspect, zNear, zFar);
		return 0;
	}
	static int Polycode_delete_Matrix4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Matrix4*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Mesh_get_indexedMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->indexedMesh);
	return 1;
}

static int Polycode_Mesh_get_vertexPositionArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexPositionArray;
	return 1;
}

static int Polycode_Mesh_get_vertexColorArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexColorArray;
	return 1;
}

static int Polycode_Mesh_get_vertexNormalArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexNormalArray;
	return 1;
}

static int Polycode_Mesh_get_vertexTexCoordArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexTexCoordArray;
	return 1;
}

static int Polycode_Mesh_get_vertexTexCoord2Array(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexTexCoord2Array;
	return 1;
}

static int Polycode_Mesh_get_vertexTangentArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexTangentArray;
	return 1;
}

static int Polycode_Mesh_get_vertexBoneWeightArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexBoneWeightArray;
	return 1;
}

static int Polycode_Mesh_get_vertexBoneIndexArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->vertexBoneIndexArray;
	return 1;
}

static int Polycode_Mesh_get_indexArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->indexArray;
	return 1;
}

static int Polycode_Mesh_set_indexedMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->indexedMesh = param;
	return 0;
}

static int Polycode_Mesh_set_vertexPositionArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexPositionArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexColorArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexColorArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexNormalArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexNormalArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexTexCoordArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexTexCoordArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexTexCoord2Array(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexTexCoord2Array = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexTangentArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexTangentArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexBoneWeightArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexBoneWeightArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_vertexBoneIndexArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray *argInst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexBoneIndexArray = *argInst;
	return 0;
}

static int Polycode_Mesh_set_indexArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	IndexDataArray *argInst = (IndexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
	inst->indexArray = *argInst;
	return 0;
}

	static int Polycode_Mesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int meshType = lua_tointeger(L, 1);
		Mesh *inst = new Mesh(meshType);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Mesh");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Mesh_MeshFromFileName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)Mesh::MeshFromFileName(fileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Mesh_loadMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadMesh(fileName);
		return 0;
	}
	static int Polycode_Mesh_clearMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearMesh();
		return 0;
	}
	static int Polycode_Mesh_saveToFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		bool writeNormals;
		if(lua_isboolean(L, 3)) {
			writeNormals = lua_toboolean(L, 3) != 0;
		} else {
			writeNormals = true;
		}
		bool writeTangents;
		if(lua_isboolean(L, 4)) {
			writeTangents = lua_toboolean(L, 4) != 0;
		} else {
			writeTangents = true;
		}
		bool writeColors;
		if(lua_isboolean(L, 5)) {
			writeColors = lua_toboolean(L, 5) != 0;
		} else {
			writeColors = true;
		}
		bool writeBoneWeights;
		if(lua_isboolean(L, 6)) {
			writeBoneWeights = lua_toboolean(L, 6) != 0;
		} else {
			writeBoneWeights = true;
		}
		bool writeUVs;
		if(lua_isboolean(L, 7)) {
			writeUVs = lua_toboolean(L, 7) != 0;
		} else {
			writeUVs = true;
		}
		bool writeSecondaryUVs;
		if(lua_isboolean(L, 8)) {
			writeSecondaryUVs = lua_toboolean(L, 8) != 0;
		} else {
			writeSecondaryUVs = false;
		}
		inst->saveToFile(fileName, writeNormals, writeTangents, writeColors, writeBoneWeights, writeUVs, writeSecondaryUVs);
		return 0;
	}
	static int Polycode_Mesh_loadFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreFile* inFile = (CoreFile*) *((PolyBase**)lua_touserdata(L, 2));
		inst->loadFromFile(inFile);
		return 0;
	}
	static int Polycode_Mesh_getVertexCount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getVertexCount());
		return 1;
	}
	static int Polycode_Mesh_createPlane(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number h = lua_tonumber(L, 3);
		Number tilingValue;
		if(lua_isnumber(L, 4)) {
			tilingValue = lua_tonumber(L, 4);
		} else {
			tilingValue = 1.0;
		}
		inst->createPlane(w, h, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createVPlane(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number h = lua_tonumber(L, 3);
		Number tilingValue;
		if(lua_isnumber(L, 4)) {
			tilingValue = lua_tonumber(L, 4);
		} else {
			tilingValue = 1.0;
		}
		inst->createVPlane(w, h, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createCircle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number h = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int numSegments = lua_tointeger(L, 4);
		Number tilingValue;
		if(lua_isnumber(L, 5)) {
			tilingValue = lua_tonumber(L, 5);
		} else {
			tilingValue = 1.0;
		}
		inst->createCircle(w, h, numSegments, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createLineCircle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number h = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int numSegments = lua_tointeger(L, 4);
		Number tilingValue;
		if(lua_isnumber(L, 5)) {
			tilingValue = lua_tonumber(L, 5);
		} else {
			tilingValue = 1.0;
		}
		inst->createLineCircle(w, h, numSegments, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createTorus(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number tubeRadius = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int segmentsW = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int segmentsH = lua_tointeger(L, 5);
		Number tilingValue;
		if(lua_isnumber(L, 6)) {
			tilingValue = lua_tonumber(L, 6);
		} else {
			tilingValue = 1.0;
		}
		inst->createTorus(radius, tubeRadius, segmentsW, segmentsH, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number d = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number h = lua_tonumber(L, 4);
		Number tilingValue;
		if(lua_isnumber(L, 5)) {
			tilingValue = lua_tonumber(L, 5);
		} else {
			tilingValue = 1.0;
		}
		inst->createBox(w, d, h, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createSphere(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int numRings = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int numSegments = lua_tointeger(L, 4);
		Number tilingValue;
		if(lua_isnumber(L, 5)) {
			tilingValue = lua_tonumber(L, 5);
		} else {
			tilingValue = 1.0;
		}
		inst->createSphere(radius, numRings, numSegments, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createIcosphere(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int subdivisions = lua_tointeger(L, 3);
		inst->createIcosphere(radius, subdivisions);
		return 0;
	}
	static int Polycode_Mesh_createOctosphere(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int subdivisions = lua_tointeger(L, 3);
		inst->createOctosphere(radius, subdivisions);
		return 0;
	}
	static int Polycode_Mesh_createCylinder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number height = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int numSegments = lua_tointeger(L, 4);
		bool capped;
		if(lua_isboolean(L, 5)) {
			capped = lua_toboolean(L, 5) != 0;
		} else {
			capped = true;
		}
		Number tilingValue;
		if(lua_isnumber(L, 6)) {
			tilingValue = lua_tonumber(L, 6);
		} else {
			tilingValue = 1.0;
		}
		inst->createCylinder(height, radius, numSegments, capped, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_createCone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number height = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int numSegments = lua_tointeger(L, 4);
		Number tilingValue;
		if(lua_isnumber(L, 5)) {
			tilingValue = lua_tonumber(L, 5);
		} else {
			tilingValue = 1.0;
		}
		inst->createCone(height, radius, numSegments, tilingValue);
		return 0;
	}
	static int Polycode_Mesh_recenterMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->recenterMesh();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_setVertexAtOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int offset = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number x = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number y = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number z = lua_tonumber(L, 5);
		inst->setVertexAtOffset(offset, x, y, z);
		return 0;
	}
	static int Polycode_Mesh_addVertexWithUVAndNormal(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number u = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number v = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		Number nx = lua_tonumber(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		Number ny = lua_tonumber(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		Number nz = lua_tonumber(L, 9);
		inst->addVertexWithUVAndNormal(x, y, z, u, v, nx, ny, nz);
		return 0;
	}
	static int Polycode_Mesh_addTexCoord(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number u = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number v = lua_tonumber(L, 3);
		inst->addTexCoord(u, v);
		return 0;
	}
	static int Polycode_Mesh_addTexCoord2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number u = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number v = lua_tonumber(L, 3);
		inst->addTexCoord2(u, v);
		return 0;
	}
	static int Polycode_Mesh_addTangent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->addTangent(x, y, z);
		return 0;
	}
	static int Polycode_Mesh_addVertexWithUV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number u = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number v = lua_tonumber(L, 6);
		inst->addVertexWithUV(x, y, z, u, v);
		return 0;
	}
	static int Polycode_Mesh_addVertex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->addVertex(x, y, z);
		return 0;
	}
	static int Polycode_Mesh_addNormal(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number nx = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number ny = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number nz = lua_tonumber(L, 4);
		inst->addNormal(nx, ny, nz);
		return 0;
	}
	static int Polycode_Mesh_addBoneAssignments(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number b1Weight = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int b1Index = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b2Weight = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int b2Index = lua_tointeger(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number b3Weight = lua_tonumber(L, 6);
		luaL_checktype(L, 7, LUA_TNUMBER);
		int b3Index = lua_tointeger(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		Number b4Weight = lua_tonumber(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		int b4Index = lua_tointeger(L, 9);
		inst->addBoneAssignments(b1Weight, b1Index, b2Weight, b2Index, b3Weight, b3Index, b4Weight, b4Index);
		return 0;
	}
	static int Polycode_Mesh_addColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number a = lua_tonumber(L, 5);
		inst->addColor(r, g, b, a);
		return 0;
	}
	static int Polycode_Mesh_getVertexPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int vertexOffset = lua_tointeger(L, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVertexPosition(vertexOffset);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_getVertexPositionAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVertexPositionAtIndex(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_getVertexTexCoord(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int vertexOffset = lua_tointeger(L, 2);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVertexTexCoord(vertexOffset);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_getVertexTexCoordAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVertexTexCoordAtIndex(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_Copy(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->Copy();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Mesh_getRadius(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getRadius());
		return 1;
	}
	static int Polycode_Mesh_calculateNormals(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->calculateNormals();
		return 0;
	}
	static int Polycode_Mesh_calculateTangents(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->calculateTangents();
		return 0;
	}
	static int Polycode_Mesh_getMeshType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getMeshType());
		return 1;
	}
	static int Polycode_Mesh_setMeshType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newType = lua_tointeger(L, 2);
		inst->setMeshType(newType);
		return 0;
	}
	static int Polycode_Mesh_getIndexGroupSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getIndexGroupSize());
		return 1;
	}
	static int Polycode_Mesh_calculateBBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->calculateBBox();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_hasVertexBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->hasVertexBuffer());
		return 1;
	}
	static int Polycode_Mesh_addIndexedFace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int i1 = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int i2 = lua_tointeger(L, 3);
		inst->addIndexedFace(i1, i2);
		return 0;
	}
	static int Polycode_Mesh_addIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		inst->addIndex(index);
		return 0;
	}
	static int Polycode_Mesh_removeVertexRange(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int beginRemoveVertex = lua_tointeger(L, 2);
		int vertexRemovalCount;
		if(lua_isnumber(L, 3)) {
			vertexRemovalCount = lua_tointeger(L, 3);
		} else {
			vertexRemovalCount = 3;
		}
		inst->removeVertexRange(beginRemoveVertex, vertexRemovalCount);
		return 0;
	}
	static int Polycode_Mesh_removeFace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int faceIndex = lua_tointeger(L, 2);
		inst->removeFace(faceIndex);
		return 0;
	}
	static int Polycode_Mesh_removeUnusedVertices(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->removeUnusedVertices());
		return 1;
	}
	static int Polycode_Mesh_getIndexCount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getIndexCount());
		return 1;
	}
	static int Polycode_Mesh_subdivideToRadius(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number radius = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int subdivisions = lua_tointeger(L, 3);
		inst->subdivideToRadius(radius, subdivisions);
		return 0;
	}
	static int Polycode_Mesh_calculateFaceTangent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 v1 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 v3 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Vector2 texCoord1 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Vector2 texCoord2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 5));
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Vector2 texCoord3 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 6));
		Vector3 *retInst = new Vector3();
		*retInst = Mesh::calculateFaceTangent(v1, v2, v3, texCoord1, texCoord2, texCoord3);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Mesh_saveAsOBJ(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->saveAsOBJ(fileName);
		return 0;
	}
	static int Polycode_Mesh_normalizeBoneWeights(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh *inst = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->normalizeBoneWeights();
		return 0;
	}
	static int Polycode_delete_Mesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Mesh*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ObjectEntry_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_ObjectEntry_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_ObjectEntry_get_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->NumberVal);
	return 1;
}

static int Polycode_ObjectEntry_get_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->intVal);
	return 1;
}

static int Polycode_ObjectEntry_get_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->stringVal.c_str());
	return 1;
}

static int Polycode_ObjectEntry_get_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->boolVal);
	return 1;
}

static int Polycode_ObjectEntry_get_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->length);
	return 1;
}

static int Polycode_ObjectEntry_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_ObjectEntry_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_ObjectEntry_set_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->NumberVal = param;
	return 0;
}

static int Polycode_ObjectEntry_set_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->intVal = param;
	return 0;
}

static int Polycode_ObjectEntry_set_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->stringVal = param;
	return 0;
}

static int Polycode_ObjectEntry_set_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->boolVal = param;
	return 0;
}

static int Polycode_ObjectEntry_set_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->length = param;
	return 0;
}

	static int Polycode_ObjectEntry(lua_State *L) {
		ObjectEntry *inst = new ObjectEntry();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ObjectEntry");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ObjectEntry_readNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String key = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Number* out = (Number*) *((PolyBase**)lua_touserdata(L, 3));
		lua_pushboolean(L, inst->readNumber(key, out));
		return 1;
	}
	static int Polycode_ObjectEntry_readString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String key = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		String* out = (String*) *((PolyBase**)lua_touserdata(L, 3));
		lua_pushboolean(L, inst->readString(key, out));
		return 1;
	}
	static int Polycode_ObjectEntry_readBool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String key = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		bool* out = (bool*) *((PolyBase**)lua_touserdata(L, 3));
		lua_pushboolean(L, inst->readBool(key, out));
		return 1;
	}
	static int Polycode_ObjectEntry_addChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->addChild(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ObjectEntry_getTypedName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getTypedName().c_str());
		return 1;
	}
	static int Polycode_ObjectEntry_setTypedName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		inst->setTypedName(str);
		return 0;
	}
	static int Polycode_ObjectEntry_Clear(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ObjectEntry *inst = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Clear();
		return 0;
	}
	static int Polycode_delete_ObjectEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ObjectEntry*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_BinaryObjectReader_get_success(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectReader *inst = (BinaryObjectReader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->success);
	return 1;
}

static int Polycode_BinaryObjectReader_set_success(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BinaryObjectReader *inst = (BinaryObjectReader*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->success = param;
	return 0;
}

	static int Polycode_BinaryObjectReader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Object* object = (Object*) *((PolyBase**)lua_touserdata(L, 2));
		BinaryObjectReader *inst = new BinaryObjectReader(fileName, object);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BinaryObjectReader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_BinaryObjectReader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BinaryObjectReader*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_BinaryObjectWriter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Object* object = (Object*) *((PolyBase**)lua_touserdata(L, 1));
		BinaryObjectWriter *inst = new BinaryObjectWriter(object);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BinaryObjectWriter");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_BinaryObjectWriter_parseKeysFromObjectEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
		inst->parseKeysFromObjectEntry(entry);
		return 0;
	}
	static int Polycode_BinaryObjectWriter_writeEntryToFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
		inst->writeEntryToFile(entry);
		return 0;
	}
	static int Polycode_BinaryObjectWriter_addKey(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String key = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->addKey(key));
		return 1;
	}
	static int Polycode_BinaryObjectWriter_getKeyIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String key = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->getKeyIndex(key));
		return 1;
	}
	static int Polycode_BinaryObjectWriter_writeToFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BinaryObjectWriter *inst = (BinaryObjectWriter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->writeToFile(fileName));
		return 1;
	}
	static int Polycode_delete_BinaryObjectWriter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BinaryObjectWriter*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_OpenGLGraphicsInterface_get_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->lineSmooth);
	return 1;
}

static int Polycode_OpenGLGraphicsInterface_set_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->lineSmooth = param;
	return 0;
}

	static int Polycode_OpenGLGraphicsInterface(lua_State *L) {
		OpenGLGraphicsInterface *inst = new OpenGLGraphicsInterface();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.OpenGLGraphicsInterface");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_OpenGLGraphicsInterface_createTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createTexture(texture);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyTexture(texture);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setViewport(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int x = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int y = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int width = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int height = lua_tointeger(L, 5);
		inst->setViewport(x, y, width, height);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_clearBuffers(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color clearColor = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool colorBuffer = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool depthBuffer = lua_toboolean(L, 4) != 0;
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool stencilBuffer = lua_toboolean(L, 5) != 0;
		inst->clearBuffers(clearColor, colorBuffer, depthBuffer, stencilBuffer);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setParamInShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ProgramParam* param = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		LocalShaderParam* localParam = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 4));
		inst->setParamInShader(shader, param, localParam);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setAttributeInShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ProgramAttribute* attribute = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		AttributeBinding* attributeBinding = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 4));
		inst->setAttributeInShader(shader, attribute, attributeBinding);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_disableAttribute(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ProgramAttribute attribute = *(ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 3));
		inst->disableAttribute(shader, attribute);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_useShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->useShader(shader);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* program = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createProgram(program);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* program = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyProgram(program);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createVBOForVertexArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		VertexDataArray* array = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createVBOForVertexArray(array);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createMesh(mesh);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyMesh(mesh);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createShader(shader);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyShader(shader);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_beginDrawCall(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		inst->beginDrawCall();
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_endDrawCall(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		inst->endDrawCall();
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setBlendingMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int blendingMode = lua_tointeger(L, 2);
		inst->setBlendingMode(blendingMode);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createRenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderBuffer* renderBuffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createRenderBuffer(renderBuffer);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyRenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderBuffer* renderBuffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyRenderBuffer(renderBuffer);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_bindRenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderBuffer* renderBuffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->bindRenderBuffer(renderBuffer);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createVertexBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		VertexDataArray* dataArray = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createVertexBuffer(dataArray);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_createIndexBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		IndexDataArray* dataArray = (IndexDataArray*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createIndexBuffer(dataArray);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_destroyBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderDataArray* array = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyBuffer(array);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_drawIndices(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		IndexDataArray* indexArray = (IndexDataArray*) *((PolyBase**)lua_touserdata(L, 3));
		inst->drawIndices(type, indexArray);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_drawArrays(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int vertexCount = lua_tointeger(L, 3);
		inst->drawArrays(type, vertexCount);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_enableDepthTest(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->enableDepthTest(val);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_enableDepthWrite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->enableDepthWrite(val);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_enableBackfaceCulling(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->enableBackfaceCulling(val);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setLineSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number lineSize = lua_tonumber(L, 2);
		inst->setLineSize(lineSize);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setWireframeMode(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setWireframeMode(val);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_enableScissor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->enableScissor(val);
		return 0;
	}
	static int Polycode_OpenGLGraphicsInterface_setScissorBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		OpenGLGraphicsInterface *inst = (OpenGLGraphicsInterface*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle box = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setScissorBox(box);
		return 0;
	}
	static int Polycode_delete_OpenGLGraphicsInterface(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((OpenGLGraphicsInterface*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneParticle_get_lifetime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lifetime);
	return 1;
}

static int Polycode_SceneParticle_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->position;
	return 1;
}

static int Polycode_SceneParticle_get_velocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->velocity;
	return 1;
}

static int Polycode_SceneParticle_get_perlinPos(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->perlinPos;
	return 1;
}

static int Polycode_SceneParticle_get_rotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->rotation;
	return 1;
}

static int Polycode_SceneParticle_get_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->brightnessDeviation);
	return 1;
}

static int Polycode_SceneParticle_get_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->scale);
	return 1;
}

static int Polycode_SceneParticle_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->color;
	return 1;
}

static int Polycode_SceneParticle_get_varianceIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->varianceIndex);
	return 1;
}

static int Polycode_SceneParticle_set_lifetime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lifetime = param;
	return 0;
}

static int Polycode_SceneParticle_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycode_SceneParticle_set_velocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->velocity = *argInst;
	return 0;
}

static int Polycode_SceneParticle_set_perlinPos(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->perlinPos = *argInst;
	return 0;
}

static int Polycode_SceneParticle_set_rotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->rotation = *argInst;
	return 0;
}

static int Polycode_SceneParticle_set_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->brightnessDeviation = param;
	return 0;
}

static int Polycode_SceneParticle_set_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->scale = param;
	return 0;
}

static int Polycode_SceneParticle_set_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->color = *argInst;
	return 0;
}

static int Polycode_SceneParticle_set_varianceIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticle *inst = (SceneParticle*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->varianceIndex = param;
	return 0;
}

	static int Polycode_delete_SceneParticle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneParticle*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneParticleEmitter_get_useScaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useScaleCurve);
	return 1;
}

static int Polycode_SceneParticleEmitter_get_scaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scaleCurve;
	return 1;
}

static int Polycode_SceneParticleEmitter_get_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useColorCurves);
	return 1;
}

static int Polycode_SceneParticleEmitter_get_colorCurveR(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveR;
	return 1;
}

static int Polycode_SceneParticleEmitter_get_colorCurveG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveG;
	return 1;
}

static int Polycode_SceneParticleEmitter_get_colorCurveB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveB;
	return 1;
}

static int Polycode_SceneParticleEmitter_get_colorCurveA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorCurveA;
	return 1;
}

static int Polycode_SceneParticleEmitter_get_colorDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->colorDeviation;
	return 1;
}

static int Polycode_SceneParticleEmitter_set_useScaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useScaleCurve = param;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_scaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scaleCurve = *argInst;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useColorCurves = param;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_colorCurveR(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveR = *argInst;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_colorCurveG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveG = *argInst;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_colorCurveB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveB = *argInst;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_colorCurveA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve *argInst = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorCurveA = *argInst;
	return 0;
}

static int Polycode_SceneParticleEmitter_set_colorDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorDeviation = *argInst;
	return 0;
}

	static int Polycode_SceneParticleEmitter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int particleCount = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number lifetime = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number speed = lua_tonumber(L, 3);
		SceneParticleEmitter *inst = new SceneParticleEmitter(particleCount, lifetime, speed);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneParticleEmitter");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleCount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newParticleCount = lua_tointeger(L, 2);
		inst->setParticleCount(newParticleCount);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleCount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getParticleCount());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleLifetime(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number lifetime = lua_tonumber(L, 2);
		inst->setParticleLifetime(lifetime);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleLifetime(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getParticleLifetime());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setDirectionDeviation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 newDeviation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setDirectionDeviation(newDeviation);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getDirectionDeviation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getDirectionDeviation();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setEmitterSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 newSize = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setEmitterSize(newSize);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getEmitterSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getEmitterSize();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setGravity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 newGravity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setGravity(newGravity);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getGravity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getGravity();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		inst->fixedUpdate();
		return 0;
	}
	static int Polycode_SceneParticleEmitter_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(buffer);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_updateParticles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		inst->updateParticles();
		return 0;
	}
	static int Polycode_SceneParticleEmitter_rebuildParticles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->rebuildParticles(buffer);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_triggerParticles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool allAtOnce = lua_toboolean(L, 2) != 0;
		inst->triggerParticles(allAtOnce);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_enableParticleSystem(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->enableParticleSystem(val);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_setUseFloorPlane(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setUseFloorPlane(val);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_setFloorPlaneOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number floorPlaneOffset = lua_tonumber(L, 2);
		inst->setFloorPlaneOffset(floorPlaneOffset);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_setFloorDamping(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number floorDamping = lua_tonumber(L, 2);
		inst->setFloorDamping(floorDamping);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_setParticlesInWorldSpace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setParticlesInWorldSpace(val);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticlesInWorldSpace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getParticlesInWorldSpace());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setPerlinEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setPerlinEnabled(val);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getPerlinEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getPerlinEnabled());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_getParticleSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getParticleSpeed());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number speed = lua_tonumber(L, 2);
		inst->setParticleSpeed(speed);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_setPerlinValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 perlinValue = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setPerlinValue(perlinValue);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getPerlinValue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getPerlinValue();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int particleType = lua_tointeger(L, 2);
		inst->setParticleType(particleType);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getParticleType());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number particleSize = lua_tonumber(L, 2);
		inst->setParticleSize(particleSize);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getParticleSize());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleRotationSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 rotationSpeed = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParticleRotationSpeed(rotationSpeed);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleRotationSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getParticleRotationSpeed();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setParticleDirection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParticleDirection(direction);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getParticleDirection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getParticleDirection();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneParticleEmitter_setLoopParticles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setLoopParticles(val);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getLoopParticles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getLoopParticles());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_addSourceMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addSourceMesh(mesh);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_getNumSourceMeshes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumSourceMeshes());
		return 1;
	}
	static int Polycode_SceneParticleEmitter_getSourcesMeshAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSourcesMeshAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneParticleEmitter_removeSourceMeshAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		inst->removeSourceMeshAtIndex(index);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_positionParticle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		inst->positionParticle(index);
		return 0;
	}
	static int Polycode_SceneParticleEmitter_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneParticleEmitter_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneParticleEmitter *inst = (SceneParticleEmitter*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_delete_SceneParticleEmitter(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneParticleEmitter*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Perlin(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int octaves = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number freq = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number amp = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int seed = lua_tointeger(L, 4);
		Perlin *inst = new Perlin(octaves, freq, amp, seed);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Perlin");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Perlin_Get2DTiledX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number t = lua_tonumber(L, 4);
		lua_pushnumber(L, inst->Get2DTiledX(x, y, t));
		return 1;
	}
	static int Polycode_Perlin_Get(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		lua_pushnumber(L, inst->Get(x, y));
		return 1;
	}
	static int Polycode_Perlin_Get2D(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		lua_pushnumber(L, inst->Get2D(x, y));
		return 1;
	}
	static int Polycode_Perlin_Get3D(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Perlin *inst = (Perlin*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		lua_pushnumber(L, inst->Get3D(x, y, z));
		return 1;
	}
	static int Polycode_delete_Perlin(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Perlin*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_PhysFSFile_get_physFSFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->physFSFile) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->physFSFile;
	}
	return 1;
}

static int Polycode_PhysFSFile_set_physFSFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	PHYSFS_File* *argInst = (PHYSFS_File**) *((PolyBase**)lua_touserdata(L, 2));
	inst->physFSFile = *argInst;
	return 0;
}

	static int Polycode_PhysFSFile_read(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t size = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		size_t count = *(size_t*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushinteger(L, inst->read(ptr, size, count));
		return 1;
	}
	static int Polycode_PhysFSFile_write(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t size = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		size_t count = *(size_t*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushinteger(L, inst->write(ptr, size, count));
		return 1;
	}
	static int Polycode_PhysFSFile_seek(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int offset = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int origin = lua_tointeger(L, 3);
		lua_pushinteger(L, inst->seek(offset, origin));
		return 1;
	}
	static int Polycode_PhysFSFile_tell(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFile *inst = (PhysFSFile*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->tell());
		return 1;
	}
	static int Polycode_delete_PhysFSFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((PhysFSFile*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_PhysFSFileProvider(lua_State *L) {
		PhysFSFileProvider *inst = new PhysFSFileProvider();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.PhysFSFileProvider");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_PhysFSFileProvider_openFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFileProvider *inst = (PhysFSFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String opts = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->openFile(fileName, opts);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_PhysFSFileProvider_closeFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFileProvider *inst = (PhysFSFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		CoreFile* file = (CoreFile*) *((PolyBase**)lua_touserdata(L, 2));
		inst->closeFile(file);
		return 0;
	}
	static int Polycode_PhysFSFileProvider_parseFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFileProvider *inst = (PhysFSFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String pathString = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool showHidden = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TUSERDATA);
		vector<OSFileEntry> targetVector = *(vector<OSFileEntry>*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushboolean(L, inst->parseFolder(pathString, showHidden, targetVector));
		return 1;
	}
	static int Polycode_PhysFSFileProvider_addSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFileProvider *inst = (PhysFSFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String source = String(lua_tostring(L, 2));
		inst->addSource(source);
		return 0;
	}
	static int Polycode_PhysFSFileProvider_removeSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PhysFSFileProvider *inst = (PhysFSFileProvider*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String source = String(lua_tostring(L, 2));
		inst->removeSource(source);
		return 0;
	}
	static int Polycode_delete_PhysFSFileProvider(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((PhysFSFileProvider*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Quaternion_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycode_Quaternion_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycode_Quaternion_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycode_Quaternion_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycode_Quaternion_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycode_Quaternion_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycode_Quaternion_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycode_Quaternion_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

	static int Polycode_Quaternion(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number w = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		Quaternion *inst = new Quaternion(w, x, y, z);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Quaternion_setFromMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 _mat = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setFromMatrix(_mat);
		return 0;
	}
	static int Polycode_Quaternion_Slerp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number fT = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Quaternion rkP = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 3));
		bool shortestPath;
		if(lua_isboolean(L, 4)) {
			shortestPath = lua_toboolean(L, 4) != 0;
		} else {
			shortestPath = false;
		}
		Quaternion *retInst = new Quaternion();
		*retInst = Quaternion::Slerp(fT, rkP, rkQ, shortestPath);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_Dot(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->Dot(rkQ));
		return 1;
	}
	static int Polycode_Quaternion_Log(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Log();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_Exp(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Exp();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_Norm(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->Norm());
		return 1;
	}
	static int Polycode_Quaternion_Normalize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->Normalize());
		return 1;
	}
	static int Polycode_Quaternion_lookAt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 D = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->lookAt(D, upVector);
		return 0;
	}
	static int Polycode_Quaternion_createFromMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createFromMatrix(matrix);
		return 0;
	}
	static int Polycode_Quaternion_Squad(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number fT = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Quaternion rkP = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Quaternion rkA = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Quaternion rkB = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Quaternion rkQ = *(Quaternion*) *((PolyBase**)lua_touserdata(L, 5));
		luaL_checktype(L, 6, LUA_TBOOLEAN);
		bool shortestPath = lua_toboolean(L, 6) != 0;
		Quaternion *retInst = new Quaternion();
		*retInst = Quaternion::Squad(fT, rkP, rkA, rkB, rkQ, shortestPath);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_Inverse(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		Quaternion *retInst = new Quaternion();
		*retInst = inst->Inverse();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_set(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number w = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number x = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number y = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number z = lua_tonumber(L, 5);
		inst->set(w, x, y, z);
		return 0;
	}
	static int Polycode_Quaternion_InvSqrt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		lua_pushnumber(L, inst->InvSqrt(x));
		return 1;
	}
	static int Polycode_Quaternion_fromAxes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number az = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number ay = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number ax = lua_tonumber(L, 4);
		inst->fromAxes(az, ay, ax);
		return 0;
	}
	static int Polycode_Quaternion_fromAngleAxis(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number rfAngle = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 rkAxis = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->fromAngleAxis(rfAngle, rkAxis);
		return 0;
	}
	static int Polycode_Quaternion_toEulerAngles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->toEulerAngles();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_toAngleAxis(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number rfAngle = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 rkAxis = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->toAngleAxis(rfAngle, rkAxis);
		return 0;
	}
	static int Polycode_Quaternion_createFromAxisAngle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number degrees = lua_tonumber(L, 5);
		inst->createFromAxisAngle(x, y, z, degrees);
		return 0;
	}
	static int Polycode_Quaternion_createMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->createMatrix();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Quaternion_applyTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Quaternion *inst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->applyTo(v);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_delete_Quaternion(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Quaternion*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_QuatTriple_get_q1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->q1;
	return 1;
}

static int Polycode_QuatTriple_get_q2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->q2;
	return 1;
}

static int Polycode_QuatTriple_get_q3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->q3;
	return 1;
}

static int Polycode_QuatTriple_get_time(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->time);
	return 1;
}

static int Polycode_QuatTriple_set_q1(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->q1 = *argInst;
	return 0;
}

static int Polycode_QuatTriple_set_q2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->q2 = *argInst;
	return 0;
}

static int Polycode_QuatTriple_set_q3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->q3 = *argInst;
	return 0;
}

static int Polycode_QuatTriple_set_time(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	QuatTriple *inst = (QuatTriple*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->time = param;
	return 0;
}

	static int Polycode_delete_QuatTriple(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((QuatTriple*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_QuaternionCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve* wCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		BezierCurve* xCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		BezierCurve* yCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		BezierCurve* zCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 4));
		QuaternionCurve *inst = new QuaternionCurve(wCurve, xCurve, yCurve, zCurve);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.QuaternionCurve");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_QuaternionCurve_interpolate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		QuaternionCurve *inst = (QuaternionCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number t = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool useShortestPath = lua_toboolean(L, 3) != 0;
		Quaternion *retInst = new Quaternion();
		*retInst = inst->interpolate(t, useShortestPath);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Quaternion");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_QuaternionCurve_generatePointsFromCurves(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		QuaternionCurve *inst = (QuaternionCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		BezierCurve* wCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		BezierCurve* xCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		BezierCurve* yCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		BezierCurve* zCurve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 5));
		inst->generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve);
		return 0;
	}
	static int Polycode_delete_QuaternionCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((QuaternionCurve*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Ray_get_origin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->origin;
	return 1;
}

static int Polycode_Ray_get_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->direction;
	return 1;
}

static int Polycode_Ray_get_inv_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->inv_direction;
	return 1;
}

static int Polycode_Ray_set_origin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->origin = *argInst;
	return 0;
}

static int Polycode_Ray_set_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->direction = *argInst;
	return 0;
}

static int Polycode_Ray_set_inv_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->inv_direction = *argInst;
	return 0;
}

	static int Polycode_Ray(lua_State *L) {
		Ray *inst = new Ray();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Ray");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Ray_boxIntersect(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 box = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Matrix4 transformMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 3));
		Number near;
		if(lua_isnumber(L, 4)) {
			near = lua_tonumber(L, 4);
		} else {
			near = 0.0;
		}
		Number far;
		if(lua_isnumber(L, 5)) {
			far = lua_tonumber(L, 5);
		} else {
			far = 9999.0;
		}
		lua_pushnumber(L, inst->boxIntersect(box, transformMatrix, near, far));
		return 1;
	}
	static int Polycode_Ray_planeIntersectPoint(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 planeNormal = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number planeDistance = lua_tonumber(L, 3);
		Vector3 *retInst = new Vector3();
		*retInst = inst->planeIntersectPoint(planeNormal, planeDistance);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Ray_tranformByMatrix(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 matrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		Ray *retInst = new Ray();
		*retInst = inst->tranformByMatrix(matrix);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Ray");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Ray_closestPointOnRay(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 point = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->closestPointOnRay(point);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Ray_closestPointsBetween(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray2 = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3* point1 = (Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Vector3* point2 = (Vector3*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushboolean(L, inst->closestPointsBetween(ray2, point1, point2));
		return 1;
	}
	static int Polycode_Ray_polygonIntersect(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Ray *inst = (Ray*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 v1 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 v2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Vector3 v3 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 4));
		lua_pushboolean(L, inst->polygonIntersect(v1, v2, v3));
		return 1;
	}
	static int Polycode_delete_Ray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Ray*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Rectangle_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycode_Rectangle_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycode_Rectangle_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycode_Rectangle_get_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->h);
	return 1;
}

static int Polycode_Rectangle_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycode_Rectangle_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycode_Rectangle_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

static int Polycode_Rectangle_set_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->h = param;
	return 0;
}

	static int Polycode_Rectangle(lua_State *L) {
		Rectangle *inst = new Rectangle();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Rectangle");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Rectangle_setRect(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number w = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number h = lua_tonumber(L, 5);
		inst->setRect(x, y, w, h);
		return 0;
	}
	static int Polycode_Rectangle_Clipped(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle rect = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		Polycode::Rectangle *retInst = new Polycode::Rectangle();
		*retInst = inst->Clipped(rect);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Polycode::Rectangle");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Rectangle_minX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->minX());
		return 1;
	}
	static int Polycode_Rectangle_maxX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->maxX());
		return 1;
	}
	static int Polycode_Rectangle_minY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->minY());
		return 1;
	}
	static int Polycode_Rectangle_maxY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Rectangle *inst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->maxY());
		return 1;
	}
	static int Polycode_delete_Rectangle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Rectangle*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RenderDataArray_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_RenderDataArray_get_customArrayName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->customArrayName.c_str());
	return 1;
}

static int Polycode_RenderDataArray_get_hasVBO(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->hasVBO);
	return 1;
}

static int Polycode_RenderDataArray_get_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->platformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->platformData;
	}
	return 1;
}

static int Polycode_RenderDataArray_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_RenderDataArray_set_customArrayName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->customArrayName = param;
	return 0;
}

static int Polycode_RenderDataArray_set_hasVBO(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->hasVBO = param;
	return 0;
}

static int Polycode_RenderDataArray_set_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->platformData = *argInst;
	return 0;
}

	static int Polycode_RenderDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		RenderDataArray *inst = new RenderDataArray(type);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.RenderDataArray");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_RenderDataArray_getArrayData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getArrayData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_RenderDataArray_getDataSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderDataArray *inst = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getDataSize());
		return 1;
	}
	static int Polycode_delete_RenderDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderDataArray*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_VertexDataArray_get_countPerVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexDataArray *inst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->countPerVertex;
	return 1;
}

static int Polycode_VertexDataArray_set_countPerVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	VertexDataArray *inst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char *argInst = (char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->countPerVertex = *argInst;
	return 0;
}

	static int Polycode_VertexDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		char countPerVertex = *(char*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		VertexDataArray *inst = new VertexDataArray(countPerVertex, type);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.VertexDataArray");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_VertexDataArray_getCountPerVertex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		VertexDataArray *inst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		char *retInst = new char();
		*retInst = inst->getCountPerVertex();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.char");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_VertexDataArray_getArrayData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		VertexDataArray *inst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getArrayData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_VertexDataArray_getDataSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		VertexDataArray *inst = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getDataSize());
		return 1;
	}
	static int Polycode_delete_VertexDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((VertexDataArray*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_IndexDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		IndexDataArray *inst = new IndexDataArray(type);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.IndexDataArray");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_IndexDataArray_getArrayData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		IndexDataArray *inst = (IndexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getArrayData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_IndexDataArray_getDataSize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		IndexDataArray *inst = (IndexDataArray*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getDataSize());
		return 1;
	}
	static int Polycode_delete_IndexDataArray(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((IndexDataArray*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_LightShadowInfoBinding_get_shadowMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightShadowInfoBinding *inst = (LightShadowInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shadowMatrix) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shadowMatrix;
	}
	return 1;
}

static int Polycode_LightShadowInfoBinding_get_shadowBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightShadowInfoBinding *inst = (LightShadowInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shadowBuffer) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shadowBuffer;
	}
	return 1;
}

static int Polycode_LightShadowInfoBinding_set_shadowMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightShadowInfoBinding *inst = (LightShadowInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shadowMatrix = *argInst;
	return 0;
}

static int Polycode_LightShadowInfoBinding_set_shadowBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightShadowInfoBinding *inst = (LightShadowInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shadowBuffer = *argInst;
	return 0;
}

	static int Polycode_delete_LightShadowInfoBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((LightShadowInfoBinding*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_LightInfoBinding_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->position) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->position;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->direction) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->direction;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_specular(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->specular) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->specular;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_diffuse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->diffuse) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->diffuse;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_spotExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->spotExponent) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->spotExponent;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_spotCosCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->spotCosCutoff) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->spotCosCutoff;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_constantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->constantAttenuation) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->constantAttenuation;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_linearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->linearAttenuation) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->linearAttenuation;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_quadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->quadraticAttenuation) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->quadraticAttenuation;
	}
	return 1;
}

static int Polycode_LightInfoBinding_get_shadowEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->shadowEnabled) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->shadowEnabled;
	}
	return 1;
}

static int Polycode_LightInfoBinding_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_direction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->direction = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_specular(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->specular = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_diffuse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->diffuse = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_spotExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->spotExponent = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_spotCosCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->spotCosCutoff = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_constantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->constantAttenuation = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_linearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->linearAttenuation = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_quadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->quadraticAttenuation = *argInst;
	return 0;
}

static int Polycode_LightInfoBinding_set_shadowEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LightInfoBinding *inst = (LightInfoBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->shadowEnabled = *argInst;
	return 0;
}

	static int Polycode_delete_LightInfoBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((LightInfoBinding*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RenderFrame_get_jobQueue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderFrame *inst = (RenderFrame*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->jobQueue;
	return 1;
}

static int Polycode_RenderFrame_set_jobQueue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderFrame *inst = (RenderFrame*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	queue<RendererThreadJob> *argInst = (queue<RendererThreadJob>*) *((PolyBase**)lua_touserdata(L, 2));
	inst->jobQueue = *argInst;
	return 0;
}

	static int Polycode_delete_RenderFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderFrame*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RendererThreadJob_get_jobType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->jobType);
	return 1;
}

static int Polycode_RendererThreadJob_get_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->data) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->data;
	}
	return 1;
}

static int Polycode_RendererThreadJob_get_data2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->data2) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->data2;
	}
	return 1;
}

static int Polycode_RendererThreadJob_set_jobType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->jobType = param;
	return 0;
}

static int Polycode_RendererThreadJob_set_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->data = *argInst;
	return 0;
}

static int Polycode_RendererThreadJob_set_data2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RendererThreadJob *inst = (RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->data2 = *argInst;
	return 0;
}

	static int Polycode_delete_RendererThreadJob(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RendererThreadJob*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_RenderThread(lua_State *L) {
		RenderThread *inst = new RenderThread();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.RenderThread");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_RenderThread_setGraphicsInterface(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Core* core = (Core*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setGraphicsInterface(core, graphicsInterface);
		return 0;
	}
	static int Polycode_RenderThread_runThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		inst->runThread();
		return 0;
	}
	static int Polycode_RenderThread_enqueueFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderFrame* frame = (RenderFrame*) *((PolyBase**)lua_touserdata(L, 2));
		inst->enqueueFrame(frame);
		return 0;
	}
	static int Polycode_RenderThread_enqueueJob(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int jobType = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		void* data = (void*) *((PolyBase**)lua_touserdata(L, 3));
		void* data2;
		if(lua_isuserdata(L, 4)) {
			data2 = (void*) *((PolyBase**)lua_touserdata(L, 4));
		} else {
			data2 = NULL;
		}
		inst->enqueueJob(jobType, data, data2);
		return 0;
	}
	static int Polycode_RenderThread_processJob(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RendererThreadJob job = *(RendererThreadJob*) *((PolyBase**)lua_touserdata(L, 2));
		inst->processJob(job);
		return 0;
	}
	static int Polycode_RenderThread_getShaderBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getShaderBinding();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_RenderThread_processDrawBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->processDrawBuffer(buffer);
		return 0;
	}
	static int Polycode_RenderThread_getFrameInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		RenderThreadDebugInfo *retInst = new RenderThreadDebugInfo();
		*retInst = inst->getFrameInfo();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.RenderThreadDebugInfo");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_RenderThread_clearFrameQueue(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearFrameQueue();
		return 0;
	}
	static int Polycode_RenderThread_initGlobals(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		inst->initGlobals();
		return 0;
	}
	static int Polycode_RenderThread_lockRenderMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		inst->lockRenderMutex();
		return 0;
	}
	static int Polycode_RenderThread_unlockRenderMutex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderThread *inst = (RenderThread*) *((PolyBase**)lua_touserdata(L, 1));
		inst->unlockRenderMutex();
		return 0;
	}
	static int Polycode_delete_RenderThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderThread*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RenderThreadDebugInfo_get_buffersProcessed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->buffersProcessed);
	return 1;
}

static int Polycode_RenderThreadDebugInfo_get_drawCallsProcessed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->drawCallsProcessed);
	return 1;
}

static int Polycode_RenderThreadDebugInfo_get_timeTaken(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->timeTaken);
	return 1;
}

static int Polycode_RenderThreadDebugInfo_set_buffersProcessed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->buffersProcessed = param;
	return 0;
}

static int Polycode_RenderThreadDebugInfo_set_drawCallsProcessed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->drawCallsProcessed = param;
	return 0;
}

static int Polycode_RenderThreadDebugInfo_set_timeTaken(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderThreadDebugInfo *inst = (RenderThreadDebugInfo*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->timeTaken = param;
	return 0;
}

	static int Polycode_delete_RenderThreadDebugInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderThreadDebugInfo*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Renderer_setGraphicsInterface(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Core* core = (Core*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		GraphicsInterface* graphicsInterface = (GraphicsInterface*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setGraphicsInterface(core, graphicsInterface);
		return 0;
	}
	static int Polycode_Renderer_getRenderThread(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderThread();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_createCubemap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* t0 = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Texture* t1 = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Texture* t2 = (Texture*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TUSERDATA);
		Texture* t3 = (Texture*) *((PolyBase**)lua_touserdata(L, 5));
		luaL_checktype(L, 6, LUA_TUSERDATA);
		Texture* t4 = (Texture*) *((PolyBase**)lua_touserdata(L, 6));
		luaL_checktype(L, 7, LUA_TUSERDATA);
		Texture* t5 = (Texture*) *((PolyBase**)lua_touserdata(L, 7));
		PolyBase *ptrRetVal = (PolyBase*)inst->createCubemap(t0, t1, t2, t3, t4, t5);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_createTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int width = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int height = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TUSERDATA);
		char* textureData = (char*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool clamp = lua_toboolean(L, 5) != 0;
		luaL_checktype(L, 6, LUA_TBOOLEAN);
		bool createMipmaps = lua_toboolean(L, 6) != 0;
		luaL_checktype(L, 7, LUA_TNUMBER);
		int type = lua_tointeger(L, 7);
		luaL_checktype(L, 8, LUA_TNUMBER);
		int filteringMode = lua_tointeger(L, 8);
		luaL_checktype(L, 9, LUA_TNUMBER);
		int anisotropy = lua_tointeger(L, 9);
		luaL_checktype(L, 10, LUA_TBOOLEAN);
		bool framebufferTexture = lua_toboolean(L, 10) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->createTexture(width, height, textureData, clamp, createMipmaps, type, filteringMode, anisotropy, framebufferTexture);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_createRenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int width = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int height = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool attachDepthBuffer = lua_toboolean(L, 4) != 0;
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool floatingPoint = lua_toboolean(L, 5) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->createRenderBuffer(width, height, attachDepthBuffer, floatingPoint);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_destroyRenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderBuffer* buffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyRenderBuffer(buffer);
		return 0;
	}
	static int Polycode_Renderer_destroyTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyTexture(texture);
		return 0;
	}
	static int Polycode_Renderer_processDrawBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->processDrawBuffer(buffer);
		return 0;
	}
	static int Polycode_Renderer_setBackingResolutionScale(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number xScale = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number yScale = lua_tonumber(L, 3);
		inst->setBackingResolutionScale(xScale, yScale);
		return 0;
	}
	static int Polycode_Renderer_getBackingResolutionScaleX(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getBackingResolutionScaleX());
		return 1;
	}
	static int Polycode_Renderer_getBackingResolutionScaleY(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getBackingResolutionScaleY());
		return 1;
	}
	static int Polycode_Renderer_createProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->createProgram(fileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_createShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* vertexProgram = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ShaderProgram* fragmentProgram = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->createShader(vertexProgram, fragmentProgram);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_createVertexBuffers(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->createVertexBuffers(mesh);
		return 0;
	}
	static int Polycode_Renderer_enqueueFrameJob(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int jobType = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		void* data = (void*) *((PolyBase**)lua_touserdata(L, 3));
		inst->enqueueFrameJob(jobType, data);
		return 0;
	}
	static int Polycode_Renderer_destroyProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* program = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyProgram(program);
		return 0;
	}
	static int Polycode_Renderer_destroyShader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Shader* shader = (Shader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyShader(shader);
		return 0;
	}
	static int Polycode_Renderer_destroyBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderDataArray* array = (RenderDataArray*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyBuffer(array);
		return 0;
	}
	static int Polycode_Renderer_destroyShaderBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderBinding* binding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyShaderBinding(binding);
		return 0;
	}
	static int Polycode_Renderer_destroyShaderParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		LocalShaderParam* param = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyShaderParam(param);
		return 0;
	}
	static int Polycode_Renderer_setTextureParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		LocalShaderParam* param = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setTextureParam(param, texture);
		return 0;
	}
	static int Polycode_Renderer_setAnisotropyAmount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number amount = lua_tonumber(L, 2);
		inst->setAnisotropyAmount(amount);
		return 0;
	}
	static int Polycode_Renderer_getAnisotropyAmount(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getAnisotropyAmount());
		return 1;
	}
	static int Polycode_Renderer_createMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->createMesh(fileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Renderer_destroyMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->destroyMesh(mesh);
		return 0;
	}
	static int Polycode_Renderer_unProject(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 modelMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Matrix4 projectionMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 4));
		Vector3 *retInst = new Vector3();
		*retInst = Renderer::unProject(position, modelMatrix, projectionMatrix, viewport);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Renderer_project(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 modelMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Matrix4 projectionMatrix = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 4));
		Vector3 *retInst = new Vector3();
		*retInst = Renderer::project(position, modelMatrix, projectionMatrix, viewport);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Renderer_beginFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		inst->beginFrame();
		return 0;
	}
	static int Polycode_Renderer_endFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Renderer *inst = (Renderer*) *((PolyBase**)lua_touserdata(L, 1));
		inst->endFrame();
		return 0;
	}
	static int Polycode_delete_Renderer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Renderer*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Resource_get_reloadOnFileModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->reloadOnFileModify);
	return 1;
}

static int Polycode_Resource_get_resourceFileTime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->resourceFileTime;
	return 1;
}

static int Polycode_Resource_get_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->platformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->platformData;
	}
	return 1;
}

static int Polycode_Resource_set_reloadOnFileModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->reloadOnFileModify = param;
	return 0;
}

static int Polycode_Resource_set_resourceFileTime(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	time_t *argInst = (time_t*) *((PolyBase**)lua_touserdata(L, 2));
	inst->resourceFileTime = *argInst;
	return 0;
}

static int Polycode_Resource_set_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->platformData = *argInst;
	return 0;
}

	static int Polycode_Resource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		Resource *inst = new Resource(type);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Resource");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Resource_reloadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadResource();
		return 0;
	}
	static int Polycode_Resource_getResourceName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getResourceName().c_str());
		return 1;
	}
	static int Polycode_Resource_getResourceType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getResourceType());
		return 1;
	}
	static int Polycode_Resource_setResourceName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String newName = String(lua_tostring(L, 2));
		inst->setResourceName(newName);
		return 0;
	}
	static int Polycode_Resource_setResourcePath(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		inst->setResourcePath(path);
		return 0;
	}
	static int Polycode_Resource_getResourcePath(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Resource *inst = (Resource*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getResourcePath().c_str());
		return 1;
	}
	static int Polycode_delete_Resource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Resource*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_ScriptResourceLoader(lua_State *L) {
		ScriptResourceLoader *inst = new ScriptResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ScriptResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ScriptResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScriptResourceLoader *inst = (ScriptResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_ScriptResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ScriptResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ResourcePool_get_reloadResourcesOnModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->reloadResourcesOnModify);
	return 1;
}

static int Polycode_ResourcePool_get_dispatchChangeEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->dispatchChangeEvents);
	return 1;
}

static int Polycode_ResourcePool_get_resourceSubscribers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->resourceSubscribers);
	return 1;
}

static int Polycode_ResourcePool_get_deleteOnUnsubscribe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->deleteOnUnsubscribe);
	return 1;
}

static int Polycode_ResourcePool_set_reloadResourcesOnModify(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->reloadResourcesOnModify = param;
	return 0;
}

static int Polycode_ResourcePool_set_dispatchChangeEvents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->dispatchChangeEvents = param;
	return 0;
}

static int Polycode_ResourcePool_set_resourceSubscribers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->resourceSubscribers = param;
	return 0;
}

static int Polycode_ResourcePool_set_deleteOnUnsubscribe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->deleteOnUnsubscribe = param;
	return 0;
}

	static int Polycode_ResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String name = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* fallbackPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		ResourcePool *inst = new ResourcePool(name, fallbackPool);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ResourcePool");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ResourcePool_setFallbackPool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setFallbackPool(pool);
		return 0;
	}
	static int Polycode_ResourcePool_addResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addResource(resource);
		return 0;
	}
	static int Polycode_ResourcePool_removeResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeResource(resource);
		return 0;
	}
	static int Polycode_ResourcePool_hasResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushboolean(L, inst->hasResource(resource));
		return 1;
	}
	static int Polycode_ResourcePool_loadResourcesFromFolder(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String folder = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool recursive = lua_toboolean(L, 3) != 0;
		inst->loadResourcesFromFolder(folder, recursive);
		return 0;
	}
	static int Polycode_ResourcePool_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourcePool_loadResourceWithName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String name = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResourceWithName(path, name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourcePool_getResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int resourceType = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TSTRING);
		String resourceName = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResource(resourceType, resourceName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourcePool_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_ResourcePool_setName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->setName(name);
		return 0;
	}
	static int Polycode_ResourcePool_getResourceByPath(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String resourcePath = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceByPath(resourcePath);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourcePool_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int elapsed = lua_tointeger(L, 2);
		inst->Update(elapsed);
		return 0;
	}
	static int Polycode_ResourcePool_getResources(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int resourceType = lua_tointeger(L, 2);
		std::vector<Resource*> retVector = inst->getResources(resourceType);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_ResourcePool_checkForChangedFiles(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourcePool *inst = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 1));
		inst->checkForChangedFiles();
		return 0;
	}
	static int Polycode_delete_ResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ResourcePool*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_ResourceManager(lua_State *L) {
		ResourceManager *inst = new ResourceManager();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ResourceManager");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ResourceManager_getGlobalPool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getGlobalPool();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourceManager_getResourcePoolByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourcePoolByName(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourceManager_addResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourceLoader* loader = (ResourceLoader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addResourceLoader(loader);
		return 0;
	}
	static int Polycode_ResourceManager_getResourceLoaderForExtension(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String extension = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceLoaderForExtension(extension);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourceManager_removeResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourceLoader* loader = (ResourceLoader*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeResourceLoader(loader);
		return 0;
	}
	static int Polycode_ResourceManager_getNumResourceLoaders(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumResourceLoaders());
		return 1;
	}
	static int Polycode_ResourceManager_getResourceLoaderAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceLoaderAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ResourceManager_addResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addResourcePool(pool);
		return 0;
	}
	static int Polycode_ResourceManager_removeResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeResourcePool(pool);
		return 0;
	}
	static int Polycode_ResourceManager_getResources(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int resourceType = lua_tointeger(L, 2);
		std::vector<Resource*> retVector = inst->getResources(resourceType);
		lua_newtable(L);
		for(int i=0; i < retVector.size(); i++) {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = (PolyBase*)retVector[i];
			lua_rawseti(L, -2, i+1);
		}
		return 1;
	}
	static int Polycode_ResourceManager_removeResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Resource* resource = (Resource*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeResource(resource);
		return 0;
	}
	static int Polycode_ResourceManager_subscribeToResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->subscribeToResourcePool(pool);
		return 0;
	}
	static int Polycode_ResourceManager_unsubscibeFromResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->unsubscibeFromResourcePool(pool);
		return 0;
	}
	static int Polycode_ResourceManager_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ResourceManager *inst = (ResourceManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int elapsed = lua_tointeger(L, 2);
		inst->Update(elapsed);
		return 0;
	}
	static int Polycode_delete_ResourceManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ResourceManager*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_FontResourceLoader(lua_State *L) {
		FontResourceLoader *inst = new FontResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.FontResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_FontResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		FontResourceLoader *inst = (FontResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_FontResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((FontResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_ProgramResourceLoader(lua_State *L) {
		ProgramResourceLoader *inst = new ProgramResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ProgramResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ProgramResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ProgramResourceLoader *inst = (ProgramResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_ProgramResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ProgramResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_DebugBackTraceEntry_get_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	DebugBackTraceEntry *inst = (DebugBackTraceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->fileName.c_str());
	return 1;
}

static int Polycode_DebugBackTraceEntry_get_lineNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	DebugBackTraceEntry *inst = (DebugBackTraceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->lineNumber);
	return 1;
}

static int Polycode_DebugBackTraceEntry_set_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	DebugBackTraceEntry *inst = (DebugBackTraceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->fileName = param;
	return 0;
}

static int Polycode_DebugBackTraceEntry_set_lineNumber(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	DebugBackTraceEntry *inst = (DebugBackTraceEntry*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->lineNumber = param;
	return 0;
}

	static int Polycode_delete_DebugBackTraceEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((DebugBackTraceEntry*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_MeshResourceLoader(lua_State *L) {
		MeshResourceLoader *inst = new MeshResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.MeshResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_MeshResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MeshResourceLoader *inst = (MeshResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_MeshResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((MeshResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_MaterialResourceLoader(lua_State *L) {
		MaterialResourceLoader *inst = new MaterialResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.MaterialResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_MaterialResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		MaterialResourceLoader *inst = (MaterialResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_MaterialResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((MaterialResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_TextureResourceLoader(lua_State *L) {
		TextureResourceLoader *inst = new TextureResourceLoader();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.TextureResourceLoader");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_TextureResourceLoader_loadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		TextureResourceLoader *inst = (TextureResourceLoader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String path = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		ResourcePool* targetPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadResource(path, targetPool);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_TextureResourceLoader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((TextureResourceLoader*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Scene_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->clearColor;
	return 1;
}

static int Polycode_Scene_get_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useClearColor);
	return 1;
}

static int Polycode_Scene_get_useClearDepth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useClearDepth);
	return 1;
}

static int Polycode_Scene_get_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->ambientColor;
	return 1;
}

static int Polycode_Scene_get_fogColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->fogColor;
	return 1;
}

static int Polycode_Scene_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycode_Scene_get_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsChildren);
	return 1;
}

static int Polycode_Scene_get_rootEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->rootEntity;
	return 1;
}

static int Polycode_Scene_get_sceneMouseRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->sceneMouseRect;
	return 1;
}

static int Polycode_Scene_get_remapMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->remapMouse);
	return 1;
}

static int Polycode_Scene_get_constrainPickingToViewport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->constrainPickingToViewport);
	return 1;
}

static int Polycode_Scene_set_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->clearColor = *argInst;
	return 0;
}

static int Polycode_Scene_set_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useClearColor = param;
	return 0;
}

static int Polycode_Scene_set_useClearDepth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useClearDepth = param;
	return 0;
}

static int Polycode_Scene_set_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->ambientColor = *argInst;
	return 0;
}

static int Polycode_Scene_set_fogColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Color *argInst = (Color*) *((PolyBase**)lua_touserdata(L, 2));
	inst->fogColor = *argInst;
	return 0;
}

static int Polycode_Scene_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

static int Polycode_Scene_set_ownsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsChildren = param;
	return 0;
}

static int Polycode_Scene_set_rootEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Entity *argInst = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
	inst->rootEntity = *argInst;
	return 0;
}

static int Polycode_Scene_set_sceneMouseRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->sceneMouseRect = *argInst;
	return 0;
}

static int Polycode_Scene_set_remapMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->remapMouse = param;
	return 0;
}

static int Polycode_Scene_set_constrainPickingToViewport(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->constrainPickingToViewport = param;
	return 0;
}

	static int Polycode_Scene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int sceneType = lua_tointeger(L, 1);
		bool virtualScene;
		if(lua_isboolean(L, 2)) {
			virtualScene = lua_toboolean(L, 2) != 0;
		} else {
			virtualScene = false;
		}
		Scene *inst = new Scene(sceneType, virtualScene);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Scene");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Scene_addEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addEntity(entity);
		return 0;
	}
	static int Polycode_Scene_addChild(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addChild(entity);
		return 0;
	}
	static int Polycode_Scene_removeEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* entity = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeEntity(entity);
		return 0;
	}
	static int Polycode_Scene_getDefaultCamera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getDefaultCamera();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Scene_getActiveCamera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getActiveCamera();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Scene_setActiveCamera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Camera* camera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setActiveCamera(camera);
		return 0;
	}
	static int Polycode_Scene_enableFog(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool enable = lua_toboolean(L, 2) != 0;
		inst->enableFog(enable);
		return 0;
	}
	static int Polycode_Scene_setFogProperties(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int fogMode = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Color color = *(Color*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number density = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number startDepth = lua_tonumber(L, 5);
		luaL_checktype(L, 6, LUA_TNUMBER);
		Number endDepth = lua_tonumber(L, 6);
		inst->setFogProperties(fogMode, color, density, startDepth, endDepth);
		return 0;
	}
	static int Polycode_Scene_setSceneType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newType = lua_tointeger(L, 2);
		inst->setSceneType(newType);
		return 0;
	}
	static int Polycode_Scene_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		inst->fixedUpdate();
		return 0;
	}
	static int Polycode_Scene_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_Scene_setVirtual(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setVirtual(val);
		return 0;
	}
	static int Polycode_Scene_isVirtual(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isVirtual());
		return 1;
	}
	static int Polycode_Scene_isEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isEnabled());
		return 1;
	}
	static int Polycode_Scene_setEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool enabled = lua_toboolean(L, 2) != 0;
		inst->setEnabled(enabled);
		return 0;
	}
	static int Polycode_Scene_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Camera* targetCamera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		RenderBuffer* targetFramebuffer = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Material* overrideMaterial = (Material*) *((PolyBase**)lua_touserdata(L, 4));
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool sendLights = lua_toboolean(L, 5) != 0;
		inst->Render(targetCamera, targetFramebuffer, overrideMaterial, sendLights);
		return 0;
	}
	static int Polycode_Scene_setOverrideMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setOverrideMaterial(material);
		return 0;
	}
	static int Polycode_Scene_projectRayFromCameraAndViewportCoordinate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Camera* camera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector2 coordinate = *(Vector2*) *((PolyBase**)lua_touserdata(L, 3));
		Ray *retInst = new Ray();
		*retInst = inst->projectRayFromCameraAndViewportCoordinate(camera, coordinate);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Ray");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Scene_addLight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SceneLight* light = (SceneLight*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addLight(light);
		return 0;
	}
	static int Polycode_Scene_removeLight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SceneLight* light = (SceneLight*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeLight(light);
		return 0;
	}
	static int Polycode_Scene_getNumLights(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumLights());
		return 1;
	}
	static int Polycode_Scene_getLight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLight(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Scene_doVisibilityChecking(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->doVisibilityChecking(val);
		return 0;
	}
	static int Polycode_Scene_doesVisibilityChecking(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene *inst = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->doesVisibilityChecking());
		return 1;
	}
	static int Polycode_delete_Scene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Scene*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneEntityInstanceResourceEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance* instance = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		SceneEntityInstanceResourceEntry *inst = new SceneEntityInstanceResourceEntry(instance);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneEntityInstanceResourceEntry");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneEntityInstanceResourceEntry_getInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getInstance();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstanceResourceEntry_reloadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstanceResourceEntry *inst = (SceneEntityInstanceResourceEntry*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadResource();
		return 0;
	}
	static int Polycode_delete_SceneEntityInstanceResourceEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneEntityInstanceResourceEntry*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneEntityInstance_get_cloneUsingReload(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->cloneUsingReload);
	return 1;
}

static int Polycode_SceneEntityInstance_get_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->fileName.c_str());
	return 1;
}

static int Polycode_SceneEntityInstance_set_cloneUsingReload(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->cloneUsingReload = param;
	return 0;
}

static int Polycode_SceneEntityInstance_set_fileName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->fileName = param;
	return 0;
}

	static int Polycode_SceneEntityInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		SceneEntityInstance *inst = new SceneEntityInstance(parentScene, fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneEntityInstance");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneEntityInstance_BlankSceneEntityInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)SceneEntityInstance::BlankSceneEntityInstance(parentScene);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneEntityInstance_reloadEntityInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadEntityInstance();
		return 0;
	}
	static int Polycode_SceneEntityInstance_clearInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearInstance();
		return 0;
	}
	static int Polycode_SceneEntityInstance_parseObjectIntoCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		BezierCurve* curve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 3));
		inst->parseObjectIntoCurve(entry, curve);
		return 0;
	}
	static int Polycode_SceneEntityInstance_loadObjectEntryIntoEntity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
		Entity* targetEntity;
		if(lua_isuserdata(L, 3)) {
			targetEntity = (Entity*) *((PolyBase**)lua_touserdata(L, 3));
		} else {
			targetEntity = NULL;
		}
		int entityFileVersion;
		if(lua_isnumber(L, 4)) {
			entityFileVersion = lua_tointeger(L, 4);
		} else {
			entityFileVersion = 1;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->loadObjectEntryIntoEntity(entry, targetEntity, entityFileVersion);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_loadFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->loadFromFile(fileName));
		return 1;
	}
	static int Polycode_SceneEntityInstance_applySceneMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ObjectEntry* entry = (ObjectEntry*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		SceneMesh* sceneMesh = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 3));
		inst->applySceneMesh(entry, sceneMesh);
		return 0;
	}
	static int Polycode_SceneEntityInstance_linkResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->linkResourcePool(pool);
		return 0;
	}
	static int Polycode_SceneEntityInstance_getNumLinkedResourePools(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumLinkedResourePools());
		return 1;
	}
	static int Polycode_SceneEntityInstance_getLinkedResourcePoolAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLinkedResourcePoolAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_unlinkResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* pool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		inst->unlinkResourcePool(pool);
		return 0;
	}
	static int Polycode_SceneEntityInstance_getResourceEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getResourceEntry();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_getTopLevelResourcePool(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTopLevelResourcePool();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_hasLayerID(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		char layerID = *(char*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushboolean(L, inst->hasLayerID(layerID));
		return 1;
	}
	static int Polycode_SceneEntityInstance_getNumLayers(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumLayers());
		return 1;
	}
	static int Polycode_SceneEntityInstance_getLayerAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLayerAtIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_removeLayer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SceneEntityInstanceLayer* layer = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeLayer(layer);
		return 0;
	}
	static int Polycode_SceneEntityInstance_createNewLayer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->createNewLayer(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneEntityInstance_getFileName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance *inst = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getFileName().c_str());
		return 1;
	}
	static int Polycode_delete_SceneEntityInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneEntityInstance*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneEntityInstanceLayer_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_SceneEntityInstanceLayer_get_layerID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->layerID;
	return 1;
}

static int Polycode_SceneEntityInstanceLayer_get_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->visible);
	return 1;
}

static int Polycode_SceneEntityInstanceLayer_get_instance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->instance) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->instance;
	}
	return 1;
}

static int Polycode_SceneEntityInstanceLayer_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_SceneEntityInstanceLayer_set_layerID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char *argInst = (char*) *((PolyBase**)lua_touserdata(L, 2));
	inst->layerID = *argInst;
	return 0;
}

static int Polycode_SceneEntityInstanceLayer_set_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->visible = param;
	return 0;
}

static int Polycode_SceneEntityInstanceLayer_set_instance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	SceneEntityInstance* *argInst = (SceneEntityInstance**) *((PolyBase**)lua_touserdata(L, 2));
	inst->instance = *argInst;
	return 0;
}

	static int Polycode_SceneEntityInstanceLayer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstance* instance = (SceneEntityInstance*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		SceneEntityInstanceLayer *inst = new SceneEntityInstanceLayer(instance, name);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneEntityInstanceLayer");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneEntityInstanceLayer_setLayerVisibility(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneEntityInstanceLayer *inst = (SceneEntityInstanceLayer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setLayerVisibility(val);
		return 0;
	}
	static int Polycode_delete_SceneEntityInstanceLayer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneEntityInstanceLayer*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		SceneImage *inst = new SceneImage(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneImage");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneImage_SceneImageWithImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Image* image = (Image*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)SceneImage::SceneImageWithImage(image);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneImage_SceneImageWithTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)SceneImage::SceneImageWithTexture(texture);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneImage_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneImage *inst = (SceneImage*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneImage_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneImage *inst = (SceneImage*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneImage_setImageCoordinates(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneImage *inst = (SceneImage*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number width = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number height = lua_tonumber(L, 5);
		Number realWidth;
		if(lua_isnumber(L, 6)) {
			realWidth = lua_tonumber(L, 6);
		} else {
			realWidth = - 1;
		}
		Number realHeight;
		if(lua_isnumber(L, 7)) {
			realHeight = lua_tonumber(L, 7);
		} else {
			realHeight = - 1;
		}
		inst->setImageCoordinates(x, y, width, height, realWidth, realHeight);
		return 0;
	}
	static int Polycode_SceneImage_getImageWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneImage *inst = (SceneImage*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getImageWidth());
		return 1;
	}
	static int Polycode_SceneImage_getImageHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneImage *inst = (SceneImage*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getImageHeight());
		return 1;
	}
	static int Polycode_delete_SceneImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneImage*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneLabel_get_positionAtBaseline(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->positionAtBaseline);
	return 1;
}

static int Polycode_SceneLabel_set_positionAtBaseline(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->positionAtBaseline = param;
	return 0;
}

	static int Polycode_SceneLabel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String text = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int size = lua_tointeger(L, 2);
		String fontName;
		if(lua_isstring(L, 3)) {
			fontName = lua_tostring(L, 3);
		} else {
			fontName = "sans";
		}
		int amode;
		if(lua_isnumber(L, 4)) {
			amode = lua_tointeger(L, 4);
		} else {
			amode = 0;
		}
		Number actualHeight;
		if(lua_isnumber(L, 5)) {
			actualHeight = lua_tonumber(L, 5);
		} else {
			actualHeight = 0.0;
		}
		bool premultiplyAlpha;
		if(lua_isboolean(L, 6)) {
			premultiplyAlpha = lua_toboolean(L, 6) != 0;
		} else {
			premultiplyAlpha = false;
		}
		luaL_checktype(L, 7, LUA_TUSERDATA);
		Color backgroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 7));
		luaL_checktype(L, 8, LUA_TUSERDATA);
		Color foregroundColor = *(Color*) *((PolyBase**)lua_touserdata(L, 8));
		SceneLabel *inst = new SceneLabel(text, size, fontName, amode, actualHeight, premultiplyAlpha, backgroundColor, foregroundColor);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneLabel");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneLabel_getText(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getText().c_str());
		return 1;
	}
	static int Polycode_SceneLabel_setLabelActualHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number actualHeight = lua_tonumber(L, 2);
		inst->setLabelActualHeight(actualHeight);
		return 0;
	}
	static int Polycode_SceneLabel_getLabelActualHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getLabelActualHeight());
		return 1;
	}
	static int Polycode_SceneLabel_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(buffer);
		return 0;
	}
	static int Polycode_SceneLabel_getTextWidthForString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String text = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->getTextWidthForString(text));
		return 1;
	}
	static int Polycode_SceneLabel_setText(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String newText = String(lua_tostring(L, 2));
		inst->setText(newText);
		return 0;
	}
	static int Polycode_SceneLabel_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLabel_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneLabel_updateFromLabel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		inst->updateFromLabel();
		return 0;
	}
	static int Polycode_SceneLabel_getLabel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLabel *inst = (SceneLabel*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getLabel();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_SceneLabel(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneLabel*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneLight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* parentScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number intensity = lua_tonumber(L, 3);
		Number constantAttenuation;
		if(lua_isnumber(L, 4)) {
			constantAttenuation = lua_tonumber(L, 4);
		} else {
			constantAttenuation = 1;
		}
		Number linearAttenuation;
		if(lua_isnumber(L, 5)) {
			linearAttenuation = lua_tonumber(L, 5);
		} else {
			linearAttenuation = 1;
		}
		Number quadraticAttenuation;
		if(lua_isnumber(L, 6)) {
			quadraticAttenuation = lua_tonumber(L, 6);
		} else {
			quadraticAttenuation = 1;
		}
		SceneLight *inst = new SceneLight(type, parentScene, intensity, constantAttenuation, linearAttenuation, quadraticAttenuation);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneLight");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneLight_getIntensity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getIntensity());
		return 1;
	}
	static int Polycode_SceneLight_setIntensity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newIntensity = lua_tonumber(L, 2);
		inst->setIntensity(newIntensity);
		return 0;
	}
	static int Polycode_SceneLight_setAttenuation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number constantAttenuation = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number linearAttenuation = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number quadraticAttenuation = lua_tonumber(L, 4);
		inst->setAttenuation(constantAttenuation, linearAttenuation, quadraticAttenuation);
		return 0;
	}
	static int Polycode_SceneLight_getConstantAttenuation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getConstantAttenuation());
		return 1;
	}
	static int Polycode_SceneLight_getLinearAttenuation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getLinearAttenuation());
		return 1;
	}
	static int Polycode_SceneLight_getQuadraticAttenuation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getQuadraticAttenuation());
		return 1;
	}
	static int Polycode_SceneLight_getType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getType());
		return 1;
	}
	static int Polycode_SceneLight_renderDepthMap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->renderDepthMap(scene);
		return 0;
	}
	static int Polycode_SceneLight_getZBufferTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getZBufferTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLight_setSpecularLightColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number a = lua_tonumber(L, 5);
		inst->setSpecularLightColor(r, g, b, a);
		return 0;
	}
	static int Polycode_SceneLight_setDiffuseLightColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		Number a;
		if(lua_isnumber(L, 5)) {
			a = lua_tonumber(L, 5);
		} else {
			a = 1.0;
		}
		inst->setDiffuseLightColor(r, g, b, a);
		return 0;
	}
	static int Polycode_SceneLight_setLightColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number r = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number g = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number b = lua_tonumber(L, 4);
		Number a;
		if(lua_isnumber(L, 5)) {
			a = lua_tonumber(L, 5);
		} else {
			a = 1.0;
		}
		inst->setLightColor(r, g, b, a);
		return 0;
	}
	static int Polycode_SceneLight_setSpotlightProperties(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number spotlightCutoff = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number spotlightExponent = lua_tonumber(L, 3);
		inst->setSpotlightProperties(spotlightCutoff, spotlightExponent);
		return 0;
	}
	static int Polycode_SceneLight_getSpotlightCutoff(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getSpotlightCutoff());
		return 1;
	}
	static int Polycode_SceneLight_getSpotlightExponent(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getSpotlightExponent());
		return 1;
	}
	static int Polycode_SceneLight_enableShadows(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		int resolution;
		if(lua_isnumber(L, 3)) {
			resolution = lua_tointeger(L, 3);
		} else {
			resolution = 256;
		}
		inst->enableShadows(val, resolution);
		return 0;
	}
	static int Polycode_SceneLight_setShadowMapFOV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number fov = lua_tonumber(L, 2);
		inst->setShadowMapFOV(fov);
		return 0;
	}
	static int Polycode_SceneLight_getShadowMapFOV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getShadowMapFOV());
		return 1;
	}
	static int Polycode_SceneLight_getShadowMapResolution(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getShadowMapResolution());
		return 1;
	}
	static int Polycode_SceneLight_areShadowsEnabled(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->areShadowsEnabled());
		return 1;
	}
	static int Polycode_SceneLight_getLightType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getLightType());
		return 1;
	}
	static int Polycode_SceneLight_setLightImportance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newImportance = lua_tointeger(L, 2);
		inst->setLightImportance(newImportance);
		return 0;
	}
	static int Polycode_SceneLight_getLightImportance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getLightImportance());
		return 1;
	}
	static int Polycode_SceneLight_setLightType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int lightType = lua_tointeger(L, 2);
		inst->setLightType(lightType);
		return 0;
	}
	static int Polycode_SceneLight_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLight_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneLight_getParentScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentScene();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLight_setParentScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParentScene(scene);
		return 0;
	}
	static int Polycode_SceneLight_getSpotlightCamera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpotlightCamera();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLight_getLightInfo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLight *inst = (SceneLight*) *((PolyBase**)lua_touserdata(L, 1));
		LightInfo *retInst = new LightInfo();
		*retInst = inst->getLightInfo();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.LightInfo");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_delete_SceneLight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneLight*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneCurve_get_renderCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->renderCurve);
	return 1;
}

static int Polycode_SceneCurve_get_curveResolution(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->curveResolution);
	return 1;
}

static int Polycode_SceneCurve_set_renderCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->renderCurve = param;
	return 0;
}

static int Polycode_SceneCurve_set_curveResolution(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->curveResolution = param;
	return 0;
}

	static int Polycode_SceneCurve(lua_State *L) {
		SceneCurve *inst = new SceneCurve();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneCurve");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneCurve_SceneCurveWithCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BezierCurve* curve = (BezierCurve*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)SceneCurve::SceneCurveWithCurve(curve);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneCurve_getWorldPointAt(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number t = lua_tonumber(L, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->getWorldPointAt(t);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneCurve_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SceneCurve_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneCurve_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneCurve_getCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneCurve *inst = (SceneCurve*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurve();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_SceneCurve(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneCurve*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneLine(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Entity* ent1 = (Entity*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* ent2 = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		SceneLine *inst = new SceneLine(ent1, ent2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneLine");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneLine_SceneLineWithPositions(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 startp = *(Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 endp = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)SceneLine::SceneLineWithPositions(startp, endp);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneLine_setStart(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 startp = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setStart(startp);
		return 0;
	}
	static int Polycode_SceneLine_setEnd(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 endp = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setEnd(endp);
		return 0;
	}
	static int Polycode_SceneLine_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneLine *inst = (SceneLine*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_delete_SceneLine(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneLine*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneManager(lua_State *L) {
		SceneManager *inst = new SceneManager();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneManager");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneManager_addScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* newScene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addScene(newScene);
		return 0;
	}
	static int Polycode_SceneManager_removeScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Scene* scene = (Scene*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeScene(scene);
		return 0;
	}
	static int Polycode_SceneManager_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SceneManager_fixedUpdate(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->fixedUpdate();
		return 0;
	}
	static int Polycode_SceneManager_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Polycode::Rectangle viewport = *(Polycode::Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(viewport);
		return 0;
	}
	static int Polycode_SceneManager_renderVirtual(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->renderVirtual();
		return 0;
	}
	static int Polycode_SceneManager_registerRenderTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->registerRenderTexture(renderTexture);
		return 0;
	}
	static int Polycode_SceneManager_unregisterRenderTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SceneRenderTexture* renderTexture = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->unregisterRenderTexture(renderTexture);
		return 0;
	}
	static int Polycode_SceneManager_setRenderer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneManager *inst = (SceneManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Renderer* renderer = (Renderer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setRenderer(renderer);
		return 0;
	}
	static int Polycode_delete_SceneManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneManager*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneMesh_get_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->lineWidth);
	return 1;
}

static int Polycode_SceneMesh_get_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->lineSmooth);
	return 1;
}

static int Polycode_SceneMesh_get_pointSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->pointSmooth);
	return 1;
}

static int Polycode_SceneMesh_get_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsMesh);
	return 1;
}

static int Polycode_SceneMesh_get_ownsSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsSkeleton);
	return 1;
}

static int Polycode_SceneMesh_get_useGeometryHitDetection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->useGeometryHitDetection);
	return 1;
}

static int Polycode_SceneMesh_get_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->alphaTest);
	return 1;
}

static int Polycode_SceneMesh_get_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->backfaceCulled);
	return 1;
}

static int Polycode_SceneMesh_get_sendBoneMatricesToMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->sendBoneMatricesToMaterial);
	return 1;
}

static int Polycode_SceneMesh_set_lineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->lineWidth = param;
	return 0;
}

static int Polycode_SceneMesh_set_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->lineSmooth = param;
	return 0;
}

static int Polycode_SceneMesh_set_pointSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->pointSmooth = param;
	return 0;
}

static int Polycode_SceneMesh_set_ownsMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsMesh = param;
	return 0;
}

static int Polycode_SceneMesh_set_ownsSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsSkeleton = param;
	return 0;
}

static int Polycode_SceneMesh_set_useGeometryHitDetection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->useGeometryHitDetection = param;
	return 0;
}

static int Polycode_SceneMesh_set_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->alphaTest = param;
	return 0;
}

static int Polycode_SceneMesh_set_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->backfaceCulled = param;
	return 0;
}

static int Polycode_SceneMesh_set_sendBoneMatricesToMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->sendBoneMatricesToMaterial = param;
	return 0;
}

	static int Polycode_SceneMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		SceneMesh *inst = new SceneMesh(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneMesh");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneMesh_SceneMeshFromMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)SceneMesh::SceneMeshFromMesh(mesh);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_SceneMeshWithType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int meshType = lua_tointeger(L, 1);
		PolyBase *ptrRetVal = (PolyBase*)SceneMesh::SceneMeshWithType(meshType);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(buffer);
		return 0;
	}
	static int Polycode_SceneMesh_getShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		ShaderPass *retInst = new ShaderPass();
		*retInst = inst->getShaderPass(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.ShaderPass");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneMesh_getNumShaderPasses(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumShaderPasses());
		return 1;
	}
	static int Polycode_SceneMesh_addShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderPass pass = *(ShaderPass*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addShaderPass(pass);
		return 0;
	}
	static int Polycode_SceneMesh_removeShaderPass(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int shaderIndex = lua_tointeger(L, 2);
		inst->removeShaderPass(shaderIndex);
		return 0;
	}
	static int Polycode_SceneMesh_getMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getMesh();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_getMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getMaterial();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_loadSkeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadSkeleton(fileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_clearMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearMaterial();
		return 0;
	}
	static int Polycode_SceneMesh_setMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Material* material = (Material*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setMaterial(material);
		return 0;
	}
	static int Polycode_SceneMesh_rebuildAttributes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildAttributes();
		return 0;
	}
	static int Polycode_SceneMesh_setMaterialByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String materialName = String(lua_tostring(L, 2));
		ResourcePool* resourcePool;
		if(lua_isuserdata(L, 3)) {
			resourcePool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 3));
		} else {
			resourcePool = NULL;
		}
		inst->setMaterialByName(materialName, resourcePool);
		return 0;
	}
	static int Polycode_SceneMesh_setMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Mesh* mesh = (Mesh*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setMesh(mesh);
		return 0;
	}
	static int Polycode_SceneMesh_setSkeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Skeleton* skeleton = (Skeleton*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSkeleton(skeleton);
		return 0;
	}
	static int Polycode_SceneMesh_getSkeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSkeleton();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_applySkeletonLocally(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		inst->applySkeletonLocally();
		return 0;
	}
	static int Polycode_SceneMesh_setLineWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newWidth = lua_tonumber(L, 2);
		inst->setLineWidth(newWidth);
		return 0;
	}
	static int Polycode_SceneMesh_getFilename(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getFilename().c_str());
		return 1;
	}
	static int Polycode_SceneMesh_setFilename(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->setFilename(fileName);
		return 0;
	}
	static int Polycode_SceneMesh_loadFromFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadFromFile(fileName);
		return 0;
	}
	static int Polycode_SceneMesh_customHitDetection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Ray ray = *(Ray*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushboolean(L, inst->customHitDetection(ray));
		return 1;
	}
	static int Polycode_SceneMesh_setForceMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool forceMaterial = lua_toboolean(L, 2) != 0;
		inst->setForceMaterial(forceMaterial);
		return 0;
	}
	static int Polycode_SceneMesh_getForceMaterial(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getForceMaterial());
		return 1;
	}
	static int Polycode_SceneMesh_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneMesh_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneMesh *inst = (SceneMesh*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_delete_SceneMesh(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneMesh*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_ScenePrimitive(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		Number v1;
		if(lua_isnumber(L, 2)) {
			v1 = lua_tonumber(L, 2);
		} else {
			v1 = 1.0f;
		}
		Number v2;
		if(lua_isnumber(L, 3)) {
			v2 = lua_tonumber(L, 3);
		} else {
			v2 = 1.0f;
		}
		Number v3;
		if(lua_isnumber(L, 4)) {
			v3 = lua_tonumber(L, 4);
		} else {
			v3 = 1.0f;
		}
		Number v4;
		if(lua_isnumber(L, 5)) {
			v4 = lua_tonumber(L, 5);
		} else {
			v4 = 1.0f;
		}
		Number v5;
		if(lua_isnumber(L, 6)) {
			v5 = lua_tonumber(L, 6);
		} else {
			v5 = 1.0f;
		}
		ScenePrimitive *inst = new ScenePrimitive(type, v1, v2, v3, v4, v5);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ScenePrimitive");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ScenePrimitive_setPrimitiveOptions(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		Number v1;
		if(lua_isnumber(L, 3)) {
			v1 = lua_tonumber(L, 3);
		} else {
			v1 = 1.0f;
		}
		Number v2;
		if(lua_isnumber(L, 4)) {
			v2 = lua_tonumber(L, 4);
		} else {
			v2 = 1.0f;
		}
		Number v3;
		if(lua_isnumber(L, 5)) {
			v3 = lua_tonumber(L, 5);
		} else {
			v3 = 1.0f;
		}
		Number v4;
		if(lua_isnumber(L, 6)) {
			v4 = lua_tonumber(L, 6);
		} else {
			v4 = 1.0f;
		}
		Number v5;
		if(lua_isnumber(L, 7)) {
			v5 = lua_tonumber(L, 7);
		} else {
			v5 = 1.0f;
		}
		inst->setPrimitiveOptions(type, v1, v2, v3, v4, v5);
		return 0;
	}
	static int Polycode_ScenePrimitive_recreatePrimitive(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		inst->recreatePrimitive();
		return 0;
	}
	static int Polycode_ScenePrimitive_getPrimitiveType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getPrimitiveType());
		return 1;
	}
	static int Polycode_ScenePrimitive_getPrimitiveParameter1(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPrimitiveParameter1());
		return 1;
	}
	static int Polycode_ScenePrimitive_getPrimitiveParameter2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPrimitiveParameter2());
		return 1;
	}
	static int Polycode_ScenePrimitive_getPrimitiveParameter3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPrimitiveParameter3());
		return 1;
	}
	static int Polycode_ScenePrimitive_getPrimitiveParameter4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPrimitiveParameter4());
		return 1;
	}
	static int Polycode_ScenePrimitive_getPrimitiveParameter5(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPrimitiveParameter5());
		return 1;
	}
	static int Polycode_ScenePrimitive_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ScenePrimitive_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ScenePrimitive *inst = (ScenePrimitive*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_delete_ScenePrimitive(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ScenePrimitive*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SceneRenderTexture_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycode_SceneRenderTexture_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

	static int Polycode_SceneRenderTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Scene* targetScene = (Scene*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Camera* targetCamera = (Camera*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int renderWidth = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int renderHeight = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TBOOLEAN);
		bool floatingPoint = lua_toboolean(L, 5) != 0;
		SceneRenderTexture *inst = new SceneRenderTexture(targetScene, targetCamera, renderWidth, renderHeight, floatingPoint);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneRenderTexture");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneRenderTexture_getTargetTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneRenderTexture_getFilterColorBufferTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getFilterColorBufferTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneRenderTexture_getFilterZBufferTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getFilterZBufferTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneRenderTexture_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Render();
		return 0;
	}
	static int Polycode_SceneRenderTexture_saveToImage(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->saveToImage();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneRenderTexture_resizeRenderTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int newWidth = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int newHeight = lua_tointeger(L, 3);
		inst->resizeRenderTexture(newWidth, newHeight);
		return 0;
	}
	static int Polycode_SceneRenderTexture_getTargetScene(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetScene();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneRenderTexture_getTargetCamera(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneRenderTexture *inst = (SceneRenderTexture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTargetCamera();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_SceneRenderTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneRenderTexture*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number referenceDistance = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number maxDistance = lua_tonumber(L, 3);
		bool directionalSound;
		if(lua_isboolean(L, 4)) {
			directionalSound = lua_toboolean(L, 4) != 0;
		} else {
			directionalSound = false;
		}
		SceneSound *inst = new SceneSound(fileName, referenceDistance, maxDistance, directionalSound);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneSound");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneSound_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SceneSound_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSound_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneSound_isDirectionalSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isDirectionalSound());
		return 1;
	}
	static int Polycode_SceneSound_setDirectionalSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setDirectionalSound(val);
		return 0;
	}
	static int Polycode_SceneSound_getSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSound();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSound_setLoopOnLoad(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setLoopOnLoad(val);
		return 0;
	}
	static int Polycode_SceneSound_getLoopOnLoad(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSound *inst = (SceneSound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getLoopOnLoad());
		return 1;
	}
	static int Polycode_delete_SceneSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneSound*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneSoundListener(lua_State *L) {
		SceneSoundListener *inst = new SceneSoundListener();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneSoundListener");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneSoundListener_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSoundListener *inst = (SceneSoundListener*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_delete_SceneSoundListener(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneSoundListener*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SceneSprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet* spriteSet = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		SceneSprite *inst = new SceneSprite(spriteSet);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SceneSprite");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SceneSprite_Clone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 3) != 0;
		PolyBase *ptrRetVal = (PolyBase*)inst->Clone(deepClone, ignoreEditorOnly);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSprite_applyClone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Entity* clone = (Entity*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool deepClone = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool ignoreEditorOnly = lua_toboolean(L, 4) != 0;
		inst->applyClone(clone, deepClone, ignoreEditorOnly);
		return 0;
	}
	static int Polycode_SceneSprite_getSpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteSet();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSprite_getCurrentSprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentSprite();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSprite_setSpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteSet* spriteSet = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSpriteSet(spriteSet);
		return 0;
	}
	static int Polycode_SceneSprite_setSpriteByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String spriteName = String(lua_tostring(L, 2));
		inst->setSpriteByName(spriteName);
		return 0;
	}
	static int Polycode_SceneSprite_setCurrentFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int frameIndex = lua_tointeger(L, 2);
		inst->setCurrentFrame(frameIndex);
		return 0;
	}
	static int Polycode_SceneSprite_getCurrentFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getCurrentFrame());
		return 1;
	}
	static int Polycode_SceneSprite_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SceneSprite_Render(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		GPUDrawBuffer* buffer = (GPUDrawBuffer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->Render(buffer);
		return 0;
	}
	static int Polycode_SceneSprite_getSpriteBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getSpriteBoundingBox();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SceneSprite_setPaused(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setPaused(val);
		return 0;
	}
	static int Polycode_SceneSprite_isPaused(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isPaused());
		return 1;
	}
	static int Polycode_SceneSprite_setSprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Sprite* spriteEntry = (Sprite*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSprite(spriteEntry);
		return 0;
	}
	static int Polycode_SceneSprite_setSpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteState* spriteState = (SpriteState*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int startingFrame = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool playOnce = lua_toboolean(L, 4) != 0;
		inst->setSpriteState(spriteState, startingFrame, playOnce);
		return 0;
	}
	static int Polycode_SceneSprite_setSpriteStateByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int startingFrame = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool playOnce = lua_toboolean(L, 4) != 0;
		inst->setSpriteStateByName(name, startingFrame, playOnce);
		return 0;
	}
	static int Polycode_SceneSprite_getCurrentSpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getCurrentSpriteState();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SceneSprite_getStartOnRandomFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getStartOnRandomFrame());
		return 1;
	}
	static int Polycode_SceneSprite_setStartOnRandomFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SceneSprite *inst = (SceneSprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->setStartOnRandomFrame(val);
		return 0;
	}
	static int Polycode_delete_SceneSprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SceneSprite*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Sprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String name = String(lua_tostring(L, 1));
		Sprite *inst = new Sprite(name);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Sprite");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Sprite_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_Sprite_setName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->setName(name);
		return 0;
	}
	static int Polycode_Sprite_addSpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteState* state = (SpriteState*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addSpriteState(state);
		return 0;
	}
	static int Polycode_Sprite_removeSpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteState* state = (SpriteState*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeSpriteState(state);
		return 0;
	}
	static int Polycode_Sprite_getNumStates(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumStates());
		return 1;
	}
	static int Polycode_Sprite_getState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getState(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Sprite_getStateByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getStateByName(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Sprite_setParentSpritSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteSet* spriteSet = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setParentSpritSet(spriteSet);
		return 0;
	}
	static int Polycode_Sprite_getParentSpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sprite *inst = (Sprite*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParentSpriteSet();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_Sprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Sprite*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ResourcePool* parentPool = (ResourcePool*) *((PolyBase**)lua_touserdata(L, 2));
		SpriteSet *inst = new SpriteSet(fileName, parentPool);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SpriteSet");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SpriteSet_setTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setTexture(texture);
		return 0;
	}
	static int Polycode_SpriteSet_getTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SpriteSet_loadTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String imageFileName = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadTexture(imageFileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SpriteSet_addSpriteEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Sprite* newEntry = (Sprite*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addSpriteEntry(newEntry);
		return 0;
	}
	static int Polycode_SpriteSet_getNumSpriteEntries(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumSpriteEntries());
		return 1;
	}
	static int Polycode_SpriteSet_getSpriteEntry(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteEntry(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SpriteSet_removeSprite(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Sprite* sprite = (Sprite*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeSprite(sprite);
		return 0;
	}
	static int Polycode_SpriteSet_loadSpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadSpriteSet(fileName);
		return 0;
	}
	static int Polycode_SpriteSet_addSpriteFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteFrame frame = *(SpriteFrame*) *((PolyBase**)lua_touserdata(L, 2));
		bool assignID;
		if(lua_isboolean(L, 3)) {
			assignID = lua_toboolean(L, 3) != 0;
		} else {
			assignID = true;
		}
		inst->addSpriteFrame(frame, assignID);
		return 0;
	}
	static int Polycode_SpriteSet_getNumFrames(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumFrames());
		return 1;
	}
	static int Polycode_SpriteSet_getSpriteFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		SpriteFrame *retInst = new SpriteFrame();
		*retInst = inst->getSpriteFrame(index);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.SpriteFrame");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SpriteSet_getSpriteFrameByID(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int frameID = lua_tointeger(L, 2);
		SpriteFrame *retInst = new SpriteFrame();
		*retInst = inst->getSpriteFrameByID(frameID);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.SpriteFrame");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SpriteSet_removeFrameByID(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int frameID = lua_tointeger(L, 2);
		inst->removeFrameByID(frameID);
		return 0;
	}
	static int Polycode_SpriteSet_setSpriteFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SpriteFrame frame = *(SpriteFrame*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSpriteFrame(frame);
		return 0;
	}
	static int Polycode_SpriteSet_clearFrames(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearFrames();
		return 0;
	}
	static int Polycode_SpriteSet_createGridFrames(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int xCount = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int yCount = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TUSERDATA);
		Vector2 defaultAnchor = *(Vector2*) *((PolyBase**)lua_touserdata(L, 4));
		inst->createGridFrames(xCount, yCount, defaultAnchor);
		return 0;
	}
	static int Polycode_SpriteSet_createFramesFromIslands(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int minDistance = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector2 defaultAnchor = *(Vector2*) *((PolyBase**)lua_touserdata(L, 3));
		inst->createFramesFromIslands(minDistance, defaultAnchor);
		return 0;
	}
	static int Polycode_SpriteSet_getSpriteByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet *inst = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String spriteName = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getSpriteByName(spriteName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_SpriteSet(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SpriteSet*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_SpriteFrame_get_coordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->coordinates;
	return 1;
}

static int Polycode_SpriteFrame_get_anchorPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->anchorPoint;
	return 1;
}

static int Polycode_SpriteFrame_get_frameID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->frameID);
	return 1;
}

static int Polycode_SpriteFrame_set_coordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Rectangle *argInst = (Rectangle*) *((PolyBase**)lua_touserdata(L, 2));
	inst->coordinates = *argInst;
	return 0;
}

static int Polycode_SpriteFrame_set_anchorPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector2 *argInst = (Vector2*) *((PolyBase**)lua_touserdata(L, 2));
	inst->anchorPoint = *argInst;
	return 0;
}

static int Polycode_SpriteFrame_set_frameID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	SpriteFrame *inst = (SpriteFrame*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->frameID = param;
	return 0;
}

	static int Polycode_delete_SpriteFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SpriteFrame*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteSet* spriteSet = (SpriteSet*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		SpriteState *inst = new SpriteState(spriteSet, name);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SpriteState");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SpriteState_setName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->setName(name);
		return 0;
	}
	static int Polycode_SpriteState_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_SpriteState_getNumFrameIDs(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumFrameIDs());
		return 1;
	}
	static int Polycode_SpriteState_getFrameIDAtIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		lua_pushinteger(L, inst->getFrameIDAtIndex(index));
		return 1;
	}
	static int Polycode_SpriteState_getMeshForFrameIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getMeshForFrameIndex(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SpriteState_insertFrame(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int frameID = lua_tointeger(L, 3);
		inst->insertFrame(index, frameID);
		return 0;
	}
	static int Polycode_SpriteState_removeFrameByIndex(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int frameIndex = lua_tointeger(L, 2);
		inst->removeFrameByIndex(frameIndex);
		return 0;
	}
	static int Polycode_SpriteState_clearFrames(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		inst->clearFrames();
		return 0;
	}
	static int Polycode_SpriteState_setPixelsPerUnit(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number ppu = lua_tonumber(L, 2);
		inst->setPixelsPerUnit(ppu);
		return 0;
	}
	static int Polycode_SpriteState_getPixelsPerUnit(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPixelsPerUnit());
		return 1;
	}
	static int Polycode_SpriteState_rebuildStateMeshes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		inst->rebuildStateMeshes();
		return 0;
	}
	static int Polycode_SpriteState_setStateFPS(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number fps = lua_tonumber(L, 2);
		inst->setStateFPS(fps);
		return 0;
	}
	static int Polycode_SpriteState_getStateFPS(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getStateFPS());
		return 1;
	}
	static int Polycode_SpriteState_getLargestFrameBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getLargestFrameBoundingBox();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SpriteState_setBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 boundingBox = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setBoundingBox(boundingBox);
		return 0;
	}
	static int Polycode_SpriteState_getBoundingBox(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getBoundingBox();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SpriteState_getSpriteOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getSpriteOffset();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_SpriteState_setSpriteOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SpriteState *inst = (SpriteState*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 offset = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSpriteOffset(offset);
		return 0;
	}
	static int Polycode_delete_SpriteState(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SpriteState*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_JSScriptInstance_get_objectRef(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JSScriptInstance *inst = (JSScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->objectRef) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->objectRef;
	}
	return 1;
}

static int Polycode_JSScriptInstance_set_objectRef(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	JSScriptInstance *inst = (JSScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->objectRef = *argInst;
	return 0;
}

	static int Polycode_delete_JSScriptInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((JSScriptInstance*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_LuaScriptInstance_get_tableRef(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LuaScriptInstance *inst = (LuaScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->tableRef);
	return 1;
}

static int Polycode_LuaScriptInstance_set_tableRef(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LuaScriptInstance *inst = (LuaScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->tableRef = param;
	return 0;
}

	static int Polycode_delete_LuaScriptInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((LuaScriptInstance*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ScriptInstance_get_script(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScriptInstance *inst = (ScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->script) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->script;
	}
	return 1;
}

static int Polycode_ScriptInstance_set_script(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ScriptInstance *inst = (ScriptInstance*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Script* *argInst = (Script**) *((PolyBase**)lua_touserdata(L, 2));
	inst->script = *argInst;
	return 0;
}

	static int Polycode_delete_ScriptInstance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ScriptInstance*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ProgramParam_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_ProgramParam_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_ProgramParam_get_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->platformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->platformData;
	}
	return 1;
}

static int Polycode_ProgramParam_get_globalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->globalParam) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->globalParam;
	}
	return 1;
}

static int Polycode_ProgramParam_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_ProgramParam_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_ProgramParam_set_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->platformData = *argInst;
	return 0;
}

static int Polycode_ProgramParam_set_globalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramParam *inst = (ProgramParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	LocalShaderParam* *argInst = (LocalShaderParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->globalParam = *argInst;
	return 0;
}

	static int Polycode_ProgramParam(lua_State *L) {
		ProgramParam *inst = new ProgramParam();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ProgramParam");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ProgramParam_createParamData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int type = lua_tointeger(L, 1);
		PolyBase *ptrRetVal = (PolyBase*)ProgramParam::createParamData(type);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_ProgramParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ProgramParam*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ProgramAttribute_get_size(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->size);
	return 1;
}

static int Polycode_ProgramAttribute_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_ProgramAttribute_get_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->platformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->platformData;
	}
	return 1;
}

static int Polycode_ProgramAttribute_set_size(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->size = param;
	return 0;
}

static int Polycode_ProgramAttribute_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_ProgramAttribute_set_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ProgramAttribute *inst = (ProgramAttribute*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->platformData = *argInst;
	return 0;
}

	static int Polycode_ProgramAttribute(lua_State *L) {
		ProgramAttribute *inst = new ProgramAttribute();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ProgramAttribute");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_ProgramAttribute(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ProgramAttribute*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ShaderRenderTarget_get_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->id.c_str());
	return 1;
}

static int Polycode_ShaderRenderTarget_get_width(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->width);
	return 1;
}

static int Polycode_ShaderRenderTarget_get_height(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->height);
	return 1;
}

static int Polycode_ShaderRenderTarget_get_sizeMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->sizeMode);
	return 1;
}

static int Polycode_ShaderRenderTarget_get_buffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->buffer) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->buffer;
	}
	return 1;
}

static int Polycode_ShaderRenderTarget_get_normalizedWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->normalizedWidth);
	return 1;
}

static int Polycode_ShaderRenderTarget_get_normalizedHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->normalizedHeight);
	return 1;
}

static int Polycode_ShaderRenderTarget_set_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->id = param;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_width(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->width = param;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_height(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->height = param;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_sizeMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->sizeMode = param;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_buffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderBuffer* *argInst = (RenderBuffer**) *((PolyBase**)lua_touserdata(L, 2));
	inst->buffer = *argInst;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_normalizedWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->normalizedWidth = param;
	return 0;
}

static int Polycode_ShaderRenderTarget_set_normalizedHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderRenderTarget *inst = (ShaderRenderTarget*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->normalizedHeight = param;
	return 0;
}

	static int Polycode_ShaderRenderTarget(lua_State *L) {
		ShaderRenderTarget *inst = new ShaderRenderTarget();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ShaderRenderTarget");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_ShaderRenderTarget(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ShaderRenderTarget*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RenderTargetBinding_get_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->id.c_str());
	return 1;
}

static int Polycode_RenderTargetBinding_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_RenderTargetBinding_get_mode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->mode);
	return 1;
}

static int Polycode_RenderTargetBinding_get_buffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->buffer) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->buffer;
	}
	return 1;
}

static int Polycode_RenderTargetBinding_set_id(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->id = param;
	return 0;
}

static int Polycode_RenderTargetBinding_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_RenderTargetBinding_set_mode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->mode = param;
	return 0;
}

static int Polycode_RenderTargetBinding_set_buffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderTargetBinding *inst = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	RenderBuffer* *argInst = (RenderBuffer**) *((PolyBase**)lua_touserdata(L, 2));
	inst->buffer = *argInst;
	return 0;
}

	static int Polycode_delete_RenderTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderTargetBinding*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Shader_get_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->numSpotLights);
	return 1;
}

static int Polycode_Shader_get_numPointLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->numPointLights);
	return 1;
}

static int Polycode_Shader_get_screenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->screenShader);
	return 1;
}

static int Polycode_Shader_get_vertexProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->vertexProgram) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->vertexProgram;
	}
	return 1;
}

static int Polycode_Shader_get_fragmentProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->fragmentProgram) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->fragmentProgram;
	}
	return 1;
}

static int Polycode_Shader_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_Shader_set_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->numSpotLights = param;
	return 0;
}

static int Polycode_Shader_set_numPointLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->numPointLights = param;
	return 0;
}

static int Polycode_Shader_set_screenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->screenShader = param;
	return 0;
}

static int Polycode_Shader_set_vertexProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderProgram* *argInst = (ShaderProgram**) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexProgram = *argInst;
	return 0;
}

static int Polycode_Shader_set_fragmentProgram(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ShaderProgram* *argInst = (ShaderProgram**) *((PolyBase**)lua_touserdata(L, 2));
	inst->fragmentProgram = *argInst;
	return 0;
}

static int Polycode_Shader_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

	static int Polycode_Shader_getType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getType());
		return 1;
	}
	static int Polycode_Shader_setName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->setName(name);
		return 0;
	}
	static int Polycode_Shader_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_Shader_getParamPointer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getParamPointer(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Shader_getAttribPointer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttribPointer(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Shader_reload(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reload();
		return 0;
	}
	static int Polycode_Shader_getExpectedParamType(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		lua_pushinteger(L, inst->getExpectedParamType(name));
		return 1;
	}
	static int Polycode_Shader_setVertexProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* vp = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setVertexProgram(vp);
		return 0;
	}
	static int Polycode_Shader_setFragmentProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Shader *inst = (Shader*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderProgram* fp = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setFragmentProgram(fp);
		return 0;
	}
	static int Polycode_delete_Shader(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Shader*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_LocalShaderParam_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_LocalShaderParam_get_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->data) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->data;
	}
	return 1;
}

static int Polycode_LocalShaderParam_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_LocalShaderParam_get_ownsPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->ownsPointer);
	return 1;
}

static int Polycode_LocalShaderParam_get_arraySize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->arraySize);
	return 1;
}

static int Polycode_LocalShaderParam_get_param(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->param) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->param;
	}
	return 1;
}

static int Polycode_LocalShaderParam_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_LocalShaderParam_set_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->data = *argInst;
	return 0;
}

static int Polycode_LocalShaderParam_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_LocalShaderParam_set_ownsPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->ownsPointer = param;
	return 0;
}

static int Polycode_LocalShaderParam_set_arraySize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->arraySize = param;
	return 0;
}

static int Polycode_LocalShaderParam_set_param(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ProgramParam* *argInst = (ProgramParam**) *((PolyBase**)lua_touserdata(L, 2));
	inst->param = *argInst;
	return 0;
}

	static int Polycode_LocalShaderParam(lua_State *L) {
		LocalShaderParam *inst = new LocalShaderParam();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.LocalShaderParam");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_LocalShaderParam_Copy(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->Copy();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_LocalShaderParam_getNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getNumber());
		return 1;
	}
	static int Polycode_LocalShaderParam_getVector2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		Vector2 *retInst = new Vector2();
		*retInst = inst->getVector2();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_LocalShaderParam_getVector3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		Vector3 *retInst = new Vector3();
		*retInst = inst->getVector3();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_LocalShaderParam_getMatrix4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		Matrix4 *retInst = new Matrix4();
		*retInst = inst->getMatrix4();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Matrix4");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_LocalShaderParam_getColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		Color *retInst = new Color();
		*retInst = inst->getColor();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Color");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_LocalShaderParam_setNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		inst->setNumber(x);
		return 0;
	}
	static int Polycode_LocalShaderParam_setVector2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 x = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setVector2(x);
		return 0;
	}
	static int Polycode_LocalShaderParam_setVector3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 x = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setVector3(x);
		return 0;
	}
	static int Polycode_LocalShaderParam_setMatrix4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Matrix4 x = *(Matrix4*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setMatrix4(x);
		return 0;
	}
	static int Polycode_LocalShaderParam_setColor(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Color x = *(Color*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setColor(x);
		return 0;
	}
	static int Polycode_LocalShaderParam_setTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setTexture(texture);
		return 0;
	}
	static int Polycode_LocalShaderParam_getTexture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTexture();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_LocalShaderParam_setCubemap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Cubemap* cubemap = (Cubemap*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setCubemap(cubemap);
		return 0;
	}
	static int Polycode_LocalShaderParam_getCubemap(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getCubemap();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_LocalShaderParam_setParamValueFromString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		LocalShaderParam *inst = (LocalShaderParam*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TSTRING);
		String pvalue = String(lua_tostring(L, 3));
		inst->setParamValueFromString(type, pvalue);
		return 0;
	}
	static int Polycode_delete_LocalShaderParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((LocalShaderParam*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ShaderProgram_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_ShaderProgram_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

	static int Polycode_ShaderProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		ShaderProgram *inst = new ShaderProgram(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ShaderProgram");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ShaderProgram_reloadProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadProgram();
		return 0;
	}
	static int Polycode_ShaderProgram_reloadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderProgram *inst = (ShaderProgram*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadResource();
		return 0;
	}
	static int Polycode_delete_ShaderProgram(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ShaderProgram*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_AttributeBinding_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycode_AttributeBinding_get_vertexData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->vertexData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->vertexData;
	}
	return 1;
}

static int Polycode_AttributeBinding_get_attribute(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->attribute) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->attribute;
	}
	return 1;
}

static int Polycode_AttributeBinding_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycode_AttributeBinding_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycode_AttributeBinding_set_vertexData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	VertexDataArray* *argInst = (VertexDataArray**) *((PolyBase**)lua_touserdata(L, 2));
	inst->vertexData = *argInst;
	return 0;
}

static int Polycode_AttributeBinding_set_attribute(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	ProgramAttribute* *argInst = (ProgramAttribute**) *((PolyBase**)lua_touserdata(L, 2));
	inst->attribute = *argInst;
	return 0;
}

static int Polycode_AttributeBinding_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AttributeBinding *inst = (AttributeBinding*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->enabled = param;
	return 0;
}

	static int Polycode_AttributeBinding(lua_State *L) {
		AttributeBinding *inst = new AttributeBinding();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.AttributeBinding");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_delete_AttributeBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((AttributeBinding*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_ShaderBinding_get_resetAttributes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->resetAttributes);
	return 1;
}

static int Polycode_ShaderBinding_get_targetShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->targetShader) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->targetShader;
	}
	return 1;
}

static int Polycode_ShaderBinding_get_accessMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->accessMutex) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->accessMutex;
	}
	return 1;
}

static int Polycode_ShaderBinding_set_resetAttributes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->resetAttributes = param;
	return 0;
}

static int Polycode_ShaderBinding_set_targetShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Shader* *argInst = (Shader**) *((PolyBase**)lua_touserdata(L, 2));
	inst->targetShader = *argInst;
	return 0;
}

static int Polycode_ShaderBinding_set_accessMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CoreMutex* *argInst = (CoreMutex**) *((PolyBase**)lua_touserdata(L, 2));
	inst->accessMutex = *argInst;
	return 0;
}

	static int Polycode_ShaderBinding(lua_State *L) {
		ShaderBinding *inst = new ShaderBinding();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.ShaderBinding");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_ShaderBinding_copyTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		ShaderBinding* targetBinding = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 2));
		inst->copyTo(targetBinding);
		return 0;
	}
	static int Polycode_ShaderBinding_addParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TSTRING);
		String name = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->addParam(type, name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_addParamPointer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int type = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TSTRING);
		String name = String(lua_tostring(L, 3));
		luaL_checktype(L, 4, LUA_TUSERDATA);
		void* ptr = (void*) *((PolyBase**)lua_touserdata(L, 4));
		PolyBase *ptrRetVal = (PolyBase*)inst->addParamPointer(type, name, ptr);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getNumLocalParams(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumLocalParams());
		return 1;
	}
	static int Polycode_ShaderBinding_getLocalParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParam(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getLocalParamByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getLocalParamByName(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_removeParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->removeParam(name);
		return 0;
	}
	static int Polycode_ShaderBinding_loadTextureForParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String paramName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->loadTextureForParam(paramName, fileName);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_setTextureForParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String paramName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Texture* texture = (Texture*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setTextureForParam(paramName, texture);
		return 0;
	}
	static int Polycode_ShaderBinding_setCubemapForParam(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String paramName = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Cubemap* cubemap = (Cubemap*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setCubemapForParam(paramName, cubemap);
		return 0;
	}
	static int Polycode_ShaderBinding_getNumAttributeBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumAttributeBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getAttributeBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttributeBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_addAttributeBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		VertexDataArray* dataArray = (VertexDataArray*) *((PolyBase**)lua_touserdata(L, 3));
		PolyBase *ptrRetVal = (PolyBase*)inst->addAttributeBinding(name, dataArray);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getAttributeBindingByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getAttributeBindingByName(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_addRenderTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderTargetBinding* binding = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addRenderTargetBinding(binding);
		return 0;
	}
	static int Polycode_ShaderBinding_removeRenderTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		RenderTargetBinding* binding = (RenderTargetBinding*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeRenderTargetBinding(binding);
		return 0;
	}
	static int Polycode_ShaderBinding_getNumRenderTargetBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumRenderTargetBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getRenderTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getRenderTargetBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getNumInTargetBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumInTargetBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getInTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getInTargetBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getNumColorTargetBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumColorTargetBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getColorTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getColorTargetBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getNumDepthTargetBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumDepthTargetBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getDepthTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDepthTargetBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_ShaderBinding_getNumOutTargetBindings(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumOutTargetBindings());
		return 1;
	}
	static int Polycode_ShaderBinding_getOutTargetBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		ShaderBinding *inst = (ShaderBinding*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getOutTargetBinding(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_delete_ShaderBinding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((ShaderBinding*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SkeletonAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String name = String(lua_tostring(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number duration = lua_tonumber(L, 2);
		SkeletonAnimation *inst = new SkeletonAnimation(name, duration);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SkeletonAnimation");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SkeletonAnimation_addBoneTrack(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		BoneTrack* boneTrack = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addBoneTrack(boneTrack);
		return 0;
	}
	static int Polycode_SkeletonAnimation_getName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getName().c_str());
		return 1;
	}
	static int Polycode_SkeletonAnimation_Play(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool once = lua_toboolean(L, 2) != 0;
		inst->Play(once);
		return 0;
	}
	static int Polycode_SkeletonAnimation_Stop(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Stop();
		return 0;
	}
	static int Polycode_SkeletonAnimation_Reset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Reset();
		return 0;
	}
	static int Polycode_SkeletonAnimation_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SkeletonAnimation_setSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number speed = lua_tonumber(L, 2);
		inst->setSpeed(speed);
		return 0;
	}
	static int Polycode_SkeletonAnimation_setWeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newWeight = lua_tonumber(L, 2);
		inst->setWeight(newWeight);
		return 0;
	}
	static int Polycode_SkeletonAnimation_getWeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getWeight());
		return 1;
	}
	static int Polycode_SkeletonAnimation_isPlaying(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SkeletonAnimation *inst = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isPlaying());
		return 1;
	}
	static int Polycode_delete_SkeletonAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SkeletonAnimation*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Skeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		Skeleton *inst = new Skeleton(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Skeleton");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Skeleton_BlankSkeleton(lua_State *L) {
		PolyBase *ptrRetVal = (PolyBase*)Skeleton::BlankSkeleton();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Skeleton_loadSkeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadSkeleton(fileName);
		return 0;
	}
	static int Polycode_Skeleton_playAnimationByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String animName = String(lua_tostring(L, 2));
		Number weight;
		if(lua_isnumber(L, 3)) {
			weight = lua_tonumber(L, 3);
		} else {
			weight = 1.0;
		}
		bool once;
		if(lua_isboolean(L, 4)) {
			once = lua_toboolean(L, 4) != 0;
		} else {
			once = false;
		}
		bool restartIfPlaying;
		if(lua_isboolean(L, 5)) {
			restartIfPlaying = lua_toboolean(L, 5) != 0;
		} else {
			restartIfPlaying = false;
		}
		inst->playAnimationByName(animName, weight, once, restartIfPlaying);
		return 0;
	}
	static int Polycode_Skeleton_playAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SkeletonAnimation* animation = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 2));
		Number weight;
		if(lua_isnumber(L, 3)) {
			weight = lua_tonumber(L, 3);
		} else {
			weight = 1.0;
		}
		bool once;
		if(lua_isboolean(L, 4)) {
			once = lua_toboolean(L, 4) != 0;
		} else {
			once = false;
		}
		bool restartIfPlaying;
		if(lua_isboolean(L, 5)) {
			restartIfPlaying = lua_toboolean(L, 5) != 0;
		} else {
			restartIfPlaying = false;
		}
		inst->playAnimation(animation, weight, once, restartIfPlaying);
		return 0;
	}
	static int Polycode_Skeleton_setBaseAnimationByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String animName = String(lua_tostring(L, 2));
		inst->setBaseAnimationByName(animName);
		return 0;
	}
	static int Polycode_Skeleton_setBaseAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SkeletonAnimation* animation = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setBaseAnimation(animation);
		return 0;
	}
	static int Polycode_Skeleton_stopAllAnimations(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		inst->stopAllAnimations();
		return 0;
	}
	static int Polycode_Skeleton_getBaseAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getBaseAnimation();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Skeleton_addAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 3));
		inst->addAnimation(name, fileName);
		return 0;
	}
	static int Polycode_Skeleton_getAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getAnimation(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Skeleton_stopAnimationByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		inst->stopAnimationByName(name);
		return 0;
	}
	static int Polycode_Skeleton_stopAnimation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		SkeletonAnimation* animation = (SkeletonAnimation*) *((PolyBase**)lua_touserdata(L, 2));
		inst->stopAnimation(animation);
		return 0;
	}
	static int Polycode_Skeleton_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_Skeleton_getBoneByName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String name = String(lua_tostring(L, 2));
		PolyBase *ptrRetVal = (PolyBase*)inst->getBoneByName(name);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Skeleton_bonesVisible(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool val = lua_toboolean(L, 2) != 0;
		inst->bonesVisible(val);
		return 0;
	}
	static int Polycode_Skeleton_getNumBones(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumBones());
		return 1;
	}
	static int Polycode_Skeleton_getBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int index = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getBone(index);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Skeleton_addBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addBone(bone);
		return 0;
	}
	static int Polycode_Skeleton_removeBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeBone(bone);
		return 0;
	}
	static int Polycode_Skeleton_getBoneIndexByBone(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Skeleton *inst = (Skeleton*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushinteger(L, inst->getBoneIndexByBone(bone));
		return 1;
	}
	static int Polycode_delete_Skeleton(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Skeleton*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_BoneTrack_get_scaleX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->scaleX) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->scaleX;
	}
	return 1;
}

static int Polycode_BoneTrack_get_scaleY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->scaleY) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->scaleY;
	}
	return 1;
}

static int Polycode_BoneTrack_get_scaleZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->scaleZ) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->scaleZ;
	}
	return 1;
}

static int Polycode_BoneTrack_get_QuatW(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->QuatW) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->QuatW;
	}
	return 1;
}

static int Polycode_BoneTrack_get_QuatX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->QuatX) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->QuatX;
	}
	return 1;
}

static int Polycode_BoneTrack_get_QuatY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->QuatY) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->QuatY;
	}
	return 1;
}

static int Polycode_BoneTrack_get_QuatZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->QuatZ) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->QuatZ;
	}
	return 1;
}

static int Polycode_BoneTrack_get_LocX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->LocX) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->LocX;
	}
	return 1;
}

static int Polycode_BoneTrack_get_LocY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->LocY) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->LocY;
	}
	return 1;
}

static int Polycode_BoneTrack_get_LocZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->LocZ) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->LocZ;
	}
	return 1;
}

static int Polycode_BoneTrack_get_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->position;
	return 1;
}

static int Polycode_BoneTrack_get_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->scale;
	return 1;
}

static int Polycode_BoneTrack_get_boneQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->boneQuat;
	return 1;
}

static int Polycode_BoneTrack_get_quatCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->quatCurve) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->quatCurve;
	}
	return 1;
}

static int Polycode_BoneTrack_get_weight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->weight);
	return 1;
}

static int Polycode_BoneTrack_set_scaleX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->scaleX = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_scaleY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->scaleY = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_scaleZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->scaleZ = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_QuatW(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatW = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_QuatX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatX = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_QuatY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatY = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_QuatZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->QuatZ = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_LocX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocX = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_LocY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocY = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_LocZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	BezierCurve* *argInst = (BezierCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->LocZ = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_position(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->position = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Vector3 *argInst = (Vector3*) *((PolyBase**)lua_touserdata(L, 2));
	inst->scale = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_boneQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Quaternion *argInst = (Quaternion*) *((PolyBase**)lua_touserdata(L, 2));
	inst->boneQuat = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_quatCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	QuaternionCurve* *argInst = (QuaternionCurve**) *((PolyBase**)lua_touserdata(L, 2));
	inst->quatCurve = *argInst;
	return 0;
}

static int Polycode_BoneTrack_set_weight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->weight = param;
	return 0;
}

	static int Polycode_BoneTrack(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Bone* bone = (Bone*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number length = lua_tonumber(L, 2);
		BoneTrack *inst = new BoneTrack(bone, length);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.BoneTrack");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_BoneTrack_Play(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
		bool once;
		if(lua_isboolean(L, 2)) {
			once = lua_toboolean(L, 2) != 0;
		} else {
			once = false;
		}
		inst->Play(once);
		return 0;
	}
	static int Polycode_BoneTrack_Stop(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Stop();
		return 0;
	}
	static int Polycode_BoneTrack_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number elapsed = lua_tonumber(L, 2);
		inst->Update(elapsed);
		return 0;
	}
	static int Polycode_BoneTrack_Reset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Reset();
		return 0;
	}
	static int Polycode_BoneTrack_setSpeed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		BoneTrack *inst = (BoneTrack*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number speed = lua_tonumber(L, 2);
		inst->setSpeed(speed);
		return 0;
	}
	static int Polycode_delete_BoneTrack(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((BoneTrack*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Sound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 1));
		Sound *inst = new Sound(fileName);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Sound");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Sound_getSampleAsNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int offset = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int channel = lua_tointeger(L, 3);
		lua_pushnumber(L, inst->getSampleAsNumber(offset, channel));
		return 1;
	}
	static int Polycode_Sound_loadFile(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		inst->loadFile(fileName);
		return 0;
	}
	static int Polycode_Sound_Play(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		bool loop;
		if(lua_isboolean(L, 2)) {
			loop = lua_toboolean(L, 2) != 0;
		} else {
			loop = false;
		}
		bool restartSound;
		if(lua_isboolean(L, 3)) {
			restartSound = lua_toboolean(L, 3) != 0;
		} else {
			restartSound = true;
		}
		inst->Play(loop, restartSound);
		return 0;
	}
	static int Polycode_Sound_Stop(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Stop();
		return 0;
	}
	static int Polycode_Sound_setVolume(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newVolume = lua_tonumber(L, 2);
		inst->setVolume(newVolume);
		return 0;
	}
	static int Polycode_Sound_getVolume(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getVolume());
		return 1;
	}
	static int Polycode_Sound_setPitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newPitch = lua_tonumber(L, 2);
		inst->setPitch(newPitch);
		return 0;
	}
	static int Polycode_Sound_getPitch(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPitch());
		return 1;
	}
	static int Polycode_Sound_isPlaying(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isPlaying());
		return 1;
	}
	static int Polycode_Sound_isLooped(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isLooped());
		return 1;
	}
	static int Polycode_Sound_setIsPositional(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool isPositional = lua_toboolean(L, 2) != 0;
		inst->setIsPositional(isPositional);
		return 0;
	}
	static int Polycode_Sound_setSoundPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSoundPosition(position);
		return 0;
	}
	static int Polycode_Sound_setSoundVelocity(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 velocity = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSoundVelocity(velocity);
		return 0;
	}
	static int Polycode_Sound_setSoundDirection(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 direction = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setSoundDirection(direction);
		return 0;
	}
	static int Polycode_Sound_setOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int offset = lua_tointeger(L, 2);
		inst->setOffset(offset);
		return 0;
	}
	static int Polycode_Sound_getFileName(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->getFileName().c_str());
		return 1;
	}
	static int Polycode_Sound_getPlaybackDuration(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPlaybackDuration());
		return 1;
	}
	static int Polycode_Sound_getPlaybackTime(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getPlaybackTime());
		return 1;
	}
	static int Polycode_Sound_seekTo(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number time = lua_tonumber(L, 2);
		inst->seekTo(time);
		return 0;
	}
	static int Polycode_Sound_getOffset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getOffset());
		return 1;
	}
	static int Polycode_Sound_getSampleLength(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getSampleLength());
		return 1;
	}
	static int Polycode_Sound_getFrequency(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getFrequency());
		return 1;
	}
	static int Polycode_Sound_setPositionalProperties(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number referenceDistance = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number maxDistance = lua_tonumber(L, 3);
		inst->setPositionalProperties(referenceDistance, maxDistance);
		return 0;
	}
	static int Polycode_Sound_setReferenceDistance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number referenceDistance = lua_tonumber(L, 2);
		inst->setReferenceDistance(referenceDistance);
		return 0;
	}
	static int Polycode_Sound_setMaxDistance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number maxDistance = lua_tonumber(L, 2);
		inst->setMaxDistance(maxDistance);
		return 0;
	}
	static int Polycode_Sound_getReferenceDistance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getReferenceDistance());
		return 1;
	}
	static int Polycode_Sound_getMaxDistance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getMaxDistance());
		return 1;
	}
	static int Polycode_Sound_loadBytes(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		char* data = (char*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int size = lua_tointeger(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		int channels = lua_tointeger(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		int freq = lua_tointeger(L, 5);
		luaL_checktype(L, 6, LUA_TUSERDATA);
		SoundFormat format = *(SoundFormat*) *((PolyBase**)lua_touserdata(L, 6));
		lua_pushboolean(L, inst->loadBytes(data, size, channels, freq, format));
		return 1;
	}
	static int Polycode_Sound_loadWAV(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->loadWAV(fileName));
		return 1;
	}
	static int Polycode_Sound_loadOGG(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String fileName = String(lua_tostring(L, 2));
		lua_pushboolean(L, inst->loadOGG(fileName));
		return 1;
	}
	static int Polycode_Sound_soundCheck(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool result = lua_toboolean(L, 2) != 0;
		luaL_checktype(L, 3, LUA_TSTRING);
		String err = String(lua_tostring(L, 3));
		inst->soundCheck(result, err);
		return 0;
	}
	static int Polycode_Sound_updateStream(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Sound *inst = (Sound*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int streamCount = lua_tointeger(L, 2);
		inst->updateStream(streamCount);
		return 0;
	}
	static int Polycode_delete_Sound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Sound*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_AudioStreamingSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int channels = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		int freq = lua_tointeger(L, 2);
		AudioStreamingSource *inst = new AudioStreamingSource(channels, freq);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.AudioStreamingSource");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_AudioStreamingSource_getNumChannels(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		AudioStreamingSource *inst = (AudioStreamingSource*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getNumChannels());
		return 1;
	}
	static int Polycode_AudioStreamingSource_getFrequency(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		AudioStreamingSource *inst = (AudioStreamingSource*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getFrequency());
		return 1;
	}
	static int Polycode_delete_AudioStreamingSource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((AudioStreamingSource*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_AudioMixer_get_globalVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AudioMixer *inst = (AudioMixer*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->globalVolume);
	return 1;
}

static int Polycode_AudioMixer_get_mixerMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AudioMixer *inst = (AudioMixer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->mixerMutex) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->mixerMutex;
	}
	return 1;
}

static int Polycode_AudioMixer_set_globalVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AudioMixer *inst = (AudioMixer*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->globalVolume = param;
	return 0;
}

static int Polycode_AudioMixer_set_mixerMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	AudioMixer *inst = (AudioMixer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	CoreMutex* *argInst = (CoreMutex**) *((PolyBase**)lua_touserdata(L, 2));
	inst->mixerMutex = *argInst;
	return 0;
}

	static int Polycode_AudioMixer(lua_State *L) {
		AudioMixer *inst = new AudioMixer();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.AudioMixer");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_AudioMixer_mixIntoBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		AudioMixer *inst = (AudioMixer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		int16_t* buffer = (int16_t*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int numSamples = lua_tointeger(L, 3);
		inst->mixIntoBuffer(buffer, numSamples);
		return 0;
	}
	static int Polycode_delete_AudioMixer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((AudioMixer*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_SoundManager(lua_State *L) {
		SoundManager *inst = new SoundManager();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.SoundManager");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_SoundManager_setListenerPosition(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 position = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setListenerPosition(position);
		return 0;
	}
	static int Polycode_SoundManager_setListenerOrientation(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 orientation = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		Vector3 upVector = *(Vector3*) *((PolyBase**)lua_touserdata(L, 3));
		inst->setListenerOrientation(orientation, upVector);
		return 0;
	}
	static int Polycode_SoundManager_recordSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int rate = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		int sampleSize = lua_tointeger(L, 3);
		lua_pushboolean(L, inst->recordSound(rate, sampleSize));
		return 1;
	}
	static int Polycode_SoundManager_stopRecording(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		bool generateFloatBuffer;
		if(lua_isboolean(L, 2)) {
			generateFloatBuffer = lua_toboolean(L, 2) != 0;
		} else {
			generateFloatBuffer = false;
		}
		PolyBase *ptrRetVal = (PolyBase*)inst->stopRecording(generateFloatBuffer);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_SoundManager_setAudioInterface(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		AudioInterface* audioInterface = (AudioInterface*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setAudioInterface(audioInterface);
		return 0;
	}
	static int Polycode_SoundManager_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_SoundManager_setGlobalVolume(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number globalVolume = lua_tonumber(L, 2);
		inst->setGlobalVolume(globalVolume);
		return 0;
	}
	static int Polycode_SoundManager_registerSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Sound* sound = (Sound*) *((PolyBase**)lua_touserdata(L, 2));
		inst->registerSound(sound);
		return 0;
	}
	static int Polycode_SoundManager_unregisterSound(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		SoundManager *inst = (SoundManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Sound* sound = (Sound*) *((PolyBase**)lua_touserdata(L, 2));
		inst->unregisterSound(sound);
		return 0;
	}
	static int Polycode_delete_SoundManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((SoundManager*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_String_get_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->contents;
	return 1;
}

static int Polycode_String_get_w_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
	*userdataPtr = (PolyBase*)&inst->w_contents;
	return 1;
}

static int Polycode_String_set_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	string *argInst = (string*) *((PolyBase**)lua_touserdata(L, 2));
	inst->contents = *argInst;
	return 0;
}

static int Polycode_String_set_w_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	wstring *argInst = (wstring*) *((PolyBase**)lua_touserdata(L, 2));
	inst->w_contents = *argInst;
	return 0;
}

	static int Polycode_String(lua_State *L) {
		String *inst = new String();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.String");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_String_size(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		size_t *retInst = new size_t();
		*retInst = inst->size();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_length(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		size_t *retInst = new size_t();
		*retInst = inst->length();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_substr(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t n = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		lua_pushstring(L, inst->substr(pos, n).c_str());
		return 1;
	}
	static int Polycode_String_rfind(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		size_t *retInst = new size_t();
		*retInst = inst->rfind(str, pos);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_find(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		size_t *retInst = new size_t();
		*retInst = inst->find(str, pos);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_find_last_of(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		size_t *retInst = new size_t();
		*retInst = inst->find_last_of(str, pos);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_find_first_of(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String str = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TUSERDATA);
		size_t pos = *(size_t*) *((PolyBase**)lua_touserdata(L, 3));
		size_t *retInst = new size_t();
		*retInst = inst->find_first_of(str, pos);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_toLowerCase(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->toLowerCase().c_str());
		return 1;
	}
	static int Polycode_String_toUpperCase(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushstring(L, inst->toUpperCase().c_str());
		return 1;
	}
	static int Polycode_String_split(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String delim = String(lua_tostring(L, 2));
		return 0;
	}
	static int Polycode_String_replace(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TSTRING);
		String what = String(lua_tostring(L, 2));
		luaL_checktype(L, 3, LUA_TSTRING);
		String withWhat = String(lua_tostring(L, 3));
		lua_pushstring(L, inst->replace(what, withWhat).c_str());
		return 1;
	}
	static int Polycode_String_NumberToString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number value = lua_tonumber(L, 1);
		int precision;
		if(lua_isnumber(L, 2)) {
			precision = lua_tointeger(L, 2);
		} else {
			precision = 2;
		}
		lua_pushstring(L, String::NumberToString(value, precision).c_str());
		return 1;
	}
	static int Polycode_String_toNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->toNumber());
		return 1;
	}
	static int Polycode_String_toInteger(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->toInteger());
		return 1;
	}
	static int Polycode_String_IntToString(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int value = lua_tointeger(L, 1);
		lua_pushstring(L, String::IntToString(value).c_str());
		return 1;
	}
	static int Polycode_String_c_str(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->c_str();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_String_getDataWithEncoding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getDataWithEncoding(encoding);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_String_getWDataWithEncoding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 2);
		PolyBase *ptrRetVal = (PolyBase*)inst->getWDataWithEncoding(encoding);
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_String_append(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		char c = *(char*) *((PolyBase**)lua_touserdata(L, 2));
		inst->append(c);
		return 0;
	}
	static int Polycode_String_getDataSizeWithEncoding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 2);
		size_t *retInst = new size_t();
		*retInst = inst->getDataSizeWithEncoding(encoding);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.size_t");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_String_setDataWithEncoding(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		char* data = (char*) *((PolyBase**)lua_touserdata(L, 2));
		luaL_checktype(L, 3, LUA_TNUMBER);
		int encoding = lua_tointeger(L, 3);
		inst->setDataWithEncoding(data, encoding);
		return 0;
	}
	static int Polycode_String_isNumber(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		String *inst = (String*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isNumber());
		return 1;
	}
	static int Polycode_delete_String(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((String*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_RenderBuffer_get_colorTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->colorTexture) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->colorTexture;
	}
	return 1;
}

static int Polycode_RenderBuffer_get_depthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->depthTexture) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->depthTexture;
	}
	return 1;
}

static int Polycode_RenderBuffer_get_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->platformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->platformData;
	}
	return 1;
}

static int Polycode_RenderBuffer_get_depthBufferPlatformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->depthBufferPlatformData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->depthBufferPlatformData;
	}
	return 1;
}

static int Polycode_RenderBuffer_set_colorTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* *argInst = (Texture**) *((PolyBase**)lua_touserdata(L, 2));
	inst->colorTexture = *argInst;
	return 0;
}

static int Polycode_RenderBuffer_set_depthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	Texture* *argInst = (Texture**) *((PolyBase**)lua_touserdata(L, 2));
	inst->depthTexture = *argInst;
	return 0;
}

static int Polycode_RenderBuffer_set_platformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->platformData = *argInst;
	return 0;
}

static int Polycode_RenderBuffer_set_depthBufferPlatformData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	void* *argInst = (void**) *((PolyBase**)lua_touserdata(L, 2));
	inst->depthBufferPlatformData = *argInst;
	return 0;
}

	static int Polycode_RenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		int width = lua_tointeger(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		int height = lua_tointeger(L, 2);
		luaL_checktype(L, 3, LUA_TBOOLEAN);
		bool attachDepthBuffer = lua_toboolean(L, 3) != 0;
		luaL_checktype(L, 4, LUA_TBOOLEAN);
		bool floatingPoint = lua_toboolean(L, 4) != 0;
		RenderBuffer *inst = new RenderBuffer(width, height, attachDepthBuffer, floatingPoint);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.RenderBuffer");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_RenderBuffer_getWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getWidth());
		return 1;
	}
	static int Polycode_RenderBuffer_getHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		RenderBuffer *inst = (RenderBuffer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getHeight());
		return 1;
	}
	static int Polycode_delete_RenderBuffer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((RenderBuffer*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Texture_get_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->clamp);
	return 1;
}

static int Polycode_Texture_get_textureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	if(!inst->textureData) {
		lua_pushnil(L);
	} else {
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst->textureData;
	}
	return 1;
}

static int Polycode_Texture_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycode_Texture_get_filteringMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->filteringMode);
	return 1;
}

static int Polycode_Texture_get_createMipmaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->createMipmaps);
	return 1;
}

static int Polycode_Texture_get_anisotropy(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushinteger(L, inst->anisotropy);
	return 1;
}

static int Polycode_Texture_get_framebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->framebufferTexture);
	return 1;
}

static int Polycode_Texture_get_depthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushboolean(L, inst->depthTexture);
	return 1;
}

static int Polycode_Texture_set_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->clamp = param;
	return 0;
}

static int Polycode_Texture_set_textureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	luaL_checktype(L, 2, LUA_TUSERDATA);
	char* *argInst = (char**) *((PolyBase**)lua_touserdata(L, 2));
	inst->textureData = *argInst;
	return 0;
}

static int Polycode_Texture_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycode_Texture_set_filteringMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->filteringMode = param;
	return 0;
}

static int Polycode_Texture_set_createMipmaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->createMipmaps = param;
	return 0;
}

static int Polycode_Texture_set_anisotropy(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	int param = lua_tointeger(L, 2);
	inst->anisotropy = param;
	return 0;
}

static int Polycode_Texture_set_framebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->framebufferTexture = param;
	return 0;
}

static int Polycode_Texture_set_depthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
	bool param = lua_toboolean(L, 2) != 0;
	inst->depthTexture = param;
	return 0;
}

	static int Polycode_Texture_reloadResource(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		inst->reloadResource();
		return 0;
	}
	static int Polycode_Texture_setImageData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Image* data = (Image*) *((PolyBase**)lua_touserdata(L, 2));
		inst->setImageData(data);
		return 0;
	}
	static int Polycode_Texture_getTextureData(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		PolyBase *ptrRetVal = (PolyBase*)inst->getTextureData();
		if(ptrRetVal == NULL) {
			lua_pushnil(L);
		} else {
			PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
			*userdataPtr = ptrRetVal;
		}
		return 1;
	}
	static int Polycode_Texture_getWidth(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getWidth());
		return 1;
	}
	static int Polycode_Texture_getHeight(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getHeight());
		return 1;
	}
	static int Polycode_Texture_setCreateMipmaps(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool createMipmapsIn = lua_toboolean(L, 2) != 0;
		inst->setCreateMipmaps(createMipmapsIn);
		return 0;
	}
	static int Polycode_Texture_getCreateMipmaps(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Texture *inst = (Texture*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->getCreateMipmaps());
		return 1;
	}
	static int Polycode_delete_Texture(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Texture*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_Timer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TBOOLEAN);
		bool triggerMode = lua_toboolean(L, 1) != 0;
		luaL_checktype(L, 2, LUA_TNUMBER);
		int msecs = lua_tointeger(L, 2);
		Timer *inst = new Timer(triggerMode, msecs);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Timer");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Timer_Pause(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TBOOLEAN);
		bool paused = lua_toboolean(L, 2) != 0;
		inst->Pause(paused);
		return 0;
	}
	static int Polycode_Timer_isPaused(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->isPaused());
		return 1;
	}
	static int Polycode_Timer_getTicks(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushinteger(L, inst->getTicks());
		return 1;
	}
	static int Polycode_Timer_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int ticks = lua_tointeger(L, 2);
		inst->Update(ticks);
		return 0;
	}
	static int Polycode_Timer_Reset(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Reset();
		return 0;
	}
	static int Polycode_Timer_hasElapsed(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushboolean(L, inst->hasElapsed());
		return 1;
	}
	static int Polycode_Timer_getElapsedf(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->getElapsedf());
		return 1;
	}
	static int Polycode_Timer_setTimerInterval(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Timer *inst = (Timer*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		int msecs = lua_tointeger(L, 2);
		inst->setTimerInterval(msecs);
		return 0;
	}
	static int Polycode_delete_Timer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Timer*) *inst);
		*inst = NULL;
		return 0;
	}

	static int Polycode_TimerManager(lua_State *L) {
		TimerManager *inst = new TimerManager();
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.TimerManager");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_TimerManager_removeTimer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Timer* timer = (Timer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->removeTimer(timer);
		return 0;
	}
	static int Polycode_TimerManager_addTimer(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Timer* timer = (Timer*) *((PolyBase**)lua_touserdata(L, 2));
		inst->addTimer(timer);
		return 0;
	}
	static int Polycode_TimerManager_Update(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		TimerManager *inst = (TimerManager*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Update();
		return 0;
	}
	static int Polycode_delete_TimerManager(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((TimerManager*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Vector2_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycode_Vector2_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycode_Vector2_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycode_Vector2_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

	static int Polycode_Vector2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number x = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		Vector2 *inst = new Vector2(x, y);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Vector2");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Vector2_set(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		inst->set(x, y);
		return 0;
	}
	static int Polycode_Vector2_distance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->distance(vec2));
		return 1;
	}
	static int Polycode_Vector2_length(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->length());
		return 1;
	}
	static int Polycode_Vector2_dot(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 u = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->dot(u));
		return 1;
	}
	static int Polycode_Vector2_crossProduct(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->crossProduct(vec2));
		return 1;
	}
	static int Polycode_Vector2_angle(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector2 vec2 = *(Vector2*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->angle(vec2));
		return 1;
	}
	static int Polycode_Vector2_Normalize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector2 *inst = (Vector2*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Normalize();
		return 0;
	}
	static int Polycode_delete_Vector2(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Vector2*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Vector3_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycode_Vector3_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycode_Vector3_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycode_Vector3_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycode_Vector3_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycode_Vector3_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

	static int Polycode_Vector3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number x = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number z = lua_tonumber(L, 3);
		Vector3 *inst = new Vector3(x, y, z);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Vector3_set(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		inst->set(x, y, z);
		return 0;
	}
	static int Polycode_Vector3_distance(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 vec2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->distance(vec2));
		return 1;
	}
	static int Polycode_Vector3_angleBetween(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 dest = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->angleBetween(dest));
		return 1;
	}
	static int Polycode_Vector3_length(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->length());
		return 1;
	}
	static int Polycode_Vector3_lengthSquared(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		lua_pushnumber(L, inst->lengthSquared());
		return 1;
	}
	static int Polycode_Vector3_setLength(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number newLength = lua_tonumber(L, 2);
		Vector3 *retInst = new Vector3();
		*retInst = inst->setLength(newLength);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Vector3_dot(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 u = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->dot(u));
		return 1;
	}
	static int Polycode_Vector3_crossProduct(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector3 vec2 = *(Vector3*) *((PolyBase**)lua_touserdata(L, 2));
		Vector3 *retInst = new Vector3();
		*retInst = inst->crossProduct(vec2);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		luaL_getmetatable(L, "Polycode.Vector3");
		lua_setmetatable(L, -2);
		*userdataPtr = (PolyBase*)retInst;
		return 1;
	}
	static int Polycode_Vector3_Normalize(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector3 *inst = (Vector3*) *((PolyBase**)lua_touserdata(L, 1));
		inst->Normalize();
		return 0;
	}
	static int Polycode_delete_Vector3(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Vector3*) *inst);
		*inst = NULL;
		return 0;
	}

static int Polycode_Vector4_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycode_Vector4_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycode_Vector4_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycode_Vector4_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycode_Vector4_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycode_Vector4_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycode_Vector4_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycode_Vector4_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TUSERDATA);
	Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

	static int Polycode_Vector4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TNUMBER);
		Number x = lua_tonumber(L, 1);
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number y = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number z = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number w = lua_tonumber(L, 4);
		Vector4 *inst = new Vector4(x, y, z, w);
		PolyBase **userdataPtr = (PolyBase**)lua_newuserdata(L, sizeof(PolyBase*));
		*userdataPtr = (PolyBase*)inst;
		luaL_getmetatable(L, "Polycode.Vector4");
		lua_setmetatable(L, -2);
		return 1;
	}
	static int Polycode_Vector4_set(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TNUMBER);
		Number x = lua_tonumber(L, 2);
		luaL_checktype(L, 3, LUA_TNUMBER);
		Number y = lua_tonumber(L, 3);
		luaL_checktype(L, 4, LUA_TNUMBER);
		Number z = lua_tonumber(L, 4);
		luaL_checktype(L, 5, LUA_TNUMBER);
		Number w = lua_tonumber(L, 5);
		inst->set(x, y, z, w);
		return 0;
	}
	static int Polycode_Vector4_dot(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		Vector4 *inst = (Vector4*) *((PolyBase**)lua_touserdata(L, 1));
		luaL_checktype(L, 2, LUA_TUSERDATA);
		Vector4 u = *(Vector4*) *((PolyBase**)lua_touserdata(L, 2));
		lua_pushnumber(L, inst->dot(u));
		return 1;
	}
	static int Polycode_delete_Vector4(lua_State *L) {
		luaL_checktype(L, 1, LUA_TUSERDATA);
		PolyBase **inst = (PolyBase**)lua_touserdata(L, 1);
		delete ((Vector4*) *inst);
		*inst = NULL;
		return 0;
	}



}
