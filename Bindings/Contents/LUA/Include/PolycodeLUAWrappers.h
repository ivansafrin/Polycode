#pragma once

#include <Polycode.h>

#include <PolyGLRenderer.h>

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static int Polycore_OSFILE(lua_State *L) {
	OSFILE *inst = new OSFILE();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_OSFILE_debugDump(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFILE *inst = (OSFILE*)lua_topointer(L, 1);
	inst->debugDump();
	return 0;
}

static int Polycore_OSFileEntry(lua_State *L) {
	OSFileEntry *inst = new OSFileEntry();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_OSBasics_open(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String filename = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String opts = lua_tostring(L, 3);
	lua_pushlightuserdata(L, (void*)inst->open(filename, opts));
	return 1;
}

static int Polycore_OSBasics_close(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * file = (OSFILE *)lua_topointer(L, 2);
	lua_pushinteger(L, inst->close(file));
	return 1;
}

static int Polycore_OSBasics_read(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	void * ptr = (void *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t size = *(size_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	size_t count = *(size_t*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 5);
	lua_pushinteger(L, inst->read(ptr, size, count, stream));
	return 1;
}

static int Polycore_OSBasics_write(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const void * ptr = (const void *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t size = *(size_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	size_t count = *(size_t*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 5);
	lua_pushinteger(L, inst->write(ptr, size, count, stream));
	return 1;
}

static int Polycore_OSBasics_seek(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	long int offset = *(long int*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int origin = lua_tointeger(L, 4);
	lua_pushinteger(L, inst->seek(stream, offset, origin));
	return 1;
}

static int Polycore_OSBasics_tell(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 2);
	lua_pushinteger(L, inst->tell(stream));
	return 1;
}

static int Polycore_OSBasics_parsePhysFSFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool showHidden = lua_toboolean(L, 3);
	 vector <OSFileEntry > *retInst = new  vector <OSFileEntry >();
	*retInst = inst->parsePhysFSFolder(pathString, showHidden);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_OSBasics_parseFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool showHidden = lua_toboolean(L, 3);
	 vector <OSFileEntry > *retInst = new  vector <OSFileEntry >();
	*retInst = inst->parseFolder(pathString, showHidden);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_OSBasics_isFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = lua_tostring(L, 2);
	lua_pushboolean(L, inst->isFolder(pathString));
	return 1;
}

static int Polycore_OSBasics_createFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = lua_tostring(L, 2);
	inst->createFolder(pathString);
	return 0;
}

static int Polycore_OSBasics_removeItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = lua_tostring(L, 2);
	inst->removeItem(pathString);
	return 0;
}

static int Polycore_BezierCurve(lua_State *L) {
	BezierCurve *inst = new BezierCurve();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_BezierCurve_getControlPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getControlPoint(index));
	return 1;
}

static int Polycore_BezierCurve_getNumControlPoints(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumControlPoints());
	return 1;
}

static int Polycore_BezierCurve_addControlPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
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

static int Polycore_BezierCurve_addControlPoint3dWithHandles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
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

static int Polycore_BezierCurve_addControlPoint3d(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->addControlPoint3d(x, y, z);
	return 0;
}

static int Polycore_BezierCurve_addControlPoint2dWithHandles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
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

static int Polycore_BezierCurve_addControlPoint2d(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->addControlPoint2d(x, y);
	return 0;
}

static int Polycore_BezierCurve_getHeightAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	lua_pushnumber(L, inst->getHeightAt(a));
	return 1;
}

static int Polycore_BezierCurve_getPointAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPointAt(a);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_BezierCurve_getPointBetween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number a = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	BezierPoint * bp1 = (BezierPoint *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	BezierPoint * bp2 = (BezierPoint *)lua_topointer(L, 4);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->getPointBetween(a, bp1, bp2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_BezierCurve_rebuildBuffers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	inst->rebuildBuffers();
	return 0;
}

static int Polycore_Bone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String boneName = lua_tostring(L, 1);
	Bone *inst = new Bone(boneName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Bone_enableBoneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String labelFont = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number size = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Color labelColor = *(Color*)lua_topointer(L, 5);
	inst->enableBoneLabel(labelFont, size, scale, labelColor);
	return 0;
}

static int Polycore_Bone_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getName().c_str());
	return 1;
}

static int Polycore_Bone_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_Bone_setParentBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Bone * bone = (Bone *)lua_topointer(L, 2);
	inst->setParentBone(bone);
	return 0;
}

static int Polycore_Bone_addChildBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Bone * bone = (Bone *)lua_topointer(L, 2);
	inst->addChildBone(bone);
	return 0;
}

static int Polycore_Bone_getParentBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getParentBone());
	return 1;
}

static int Polycore_Bone_getNumChildBones(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumChildBones());
	return 1;
}

static int Polycore_Bone_getChildBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getChildBone(index));
	return 1;
}

static int Polycore_Bone_getBoneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBoneMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_setBoneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setBoneMatrix(matrix);
	return 0;
}

static int Polycore_Bone_getRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getRestMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_getFullRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFullRestMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_getParentRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getParentRestMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_getFinalMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFinalMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_setRestMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setRestMatrix(matrix);
	return 0;
}

static int Polycore_Bone_setBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setBaseMatrix(matrix);
	return 0;
}

static int Polycore_Bone_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Bone_getFullBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getFullBaseMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Camera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene * parentScene = (Scene *)lua_topointer(L, 1);
	Camera *inst = new Camera(parentScene);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Camera_buildFrustrumPlanes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	inst->buildFrustrumPlanes();
	return 0;
}

static int Polycore_Camera_isSphereInFrustrum(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 pos = *(Vector3*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fRadius = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->isSphereInFrustrum(pos, fRadius));
	return 1;
}

static int Polycore_Camera_canSee(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	lua_pushboolean(L, inst->canSee(entity));
	return 1;
}

static int Polycore_Camera_setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool mode = lua_toboolean(L, 2);
	inst->setOrthoMode(mode);
	return 0;
}

static int Polycore_Camera_getOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->getOrthoMode());
	return 1;
}

static int Polycore_Camera_setFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setFOV(fov);
	return 0;
}

static int Polycore_Camera_getFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getFOV());
	return 1;
}

static int Polycore_Camera_doCameraTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	inst->doCameraTransform();
	return 0;
}

static int Polycore_Camera_setLightDepthTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->setLightDepthTexture(texture);
	return 0;
}

static int Polycore_Camera_setParentScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * parentScene = (Scene *)lua_topointer(L, 2);
	inst->setParentScene(parentScene);
	return 0;
}

static int Polycore_Camera_hasFilterShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->hasFilterShader());
	return 1;
}

static int Polycore_Camera_drawFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	inst->drawFilter();
	return 0;
}

static int Polycore_Camera_setExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number level = lua_tonumber(L, 2);
	inst->setExposureLevel(level);
	return 0;
}

static int Polycore_Camera_getExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getExposureLevel());
	return 1;
}

static int Polycore_Camera_createPostFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Material * shaderMaterial = (Material *)lua_topointer(L, 2);
	inst->createPostFilter(shaderMaterial);
	return 0;
}

static int Polycore_Camera_setPostFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderName = lua_tostring(L, 2);
	inst->setPostFilter(shaderName);
	return 0;
}

static int Polycore_Color(lua_State *L) {
	Color *inst = new Color();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Color_setColorHex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int hex = lua_tointeger(L, 2);
	inst->setColorHex(hex);
	return 0;
}

static int Polycore_Color_setColorHexRGB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int hex = lua_tointeger(L, 2);
	inst->setColorHexRGB(hex);
	return 0;
}

static int Polycore_Color_setColorHSV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number h = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number s = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number v = lua_tonumber(L, 4);
	inst->setColorHSV(h, s, v);
	return 0;
}

static int Polycore_Color_setColorRGBA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
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

static int Polycore_Color_setColorRGB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int r = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int g = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int b = lua_tointeger(L, 4);
	inst->setColorRGB(r, g, b);
	return 0;
}

static int Polycore_Color_setColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
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

static int Polycore_Color_Random(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	inst->Random();
	return 0;
}

static int Polycore_Color_getBrightness(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getBrightness());
	return 1;
}

static int Polycore_Color_getUint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getUint());
	return 1;
}

static int Polycore_Config(lua_State *L) {
	Config *inst = new Config();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Config_loadConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = lua_tostring(L, 3);
	inst->loadConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_saveConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = lua_tostring(L, 3);
	inst->saveConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_getEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = lua_tostring(L, 3);
	lua_pushlightuserdata(L, (void*)inst->getEntry(configNamespace, key));
	return 1;
}

static int Polycore_Config_setStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = lua_tostring(L, 4);
	inst->setStringValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_setNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number value = lua_tonumber(L, 4);
	inst->setNumericValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_getNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = lua_tostring(L, 3);
	lua_pushnumber(L, inst->getNumericValue(configNamespace, key));
	return 1;
}

static int Polycore_Config_getStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = lua_tostring(L, 3);
	lua_pushstring(L, inst->getStringValue(configNamespace, key).c_str());
	return 1;
}

static int Polycore_CoreInput(lua_State *L) {
	CoreInput *inst = new CoreInput();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_CoreInput_mouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 2);
	inst->mouseWheelUp(ticks);
	return 0;
}

static int Polycore_CoreInput_mouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 2);
	inst->mouseWheelDown(ticks);
	return 0;
}

static int Polycore_CoreInput_getMouseButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 2);
	lua_pushboolean(L, inst->getMouseButtonState(mouseButton));
	return 1;
}

static int Polycore_CoreInput_setMouseButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool state = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->setMouseButtonState(mouseButton, state, ticks);
	return 0;
}

static int Polycore_CoreInput_setMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 4);
	inst->setMousePosition(x, y, ticks);
	return 0;
}

static int Polycore_CoreInput_getMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMousePosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_CoreInput_setKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey keyCode = *(TAUKey*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t code = *(wchar_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool newState = lua_toboolean(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 5);
	inst->setKeyState(keyCode, code, newState, ticks);
	return 0;
}

static int Polycore_CoreInput_getKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey keyCode = *(TAUKey*)lua_topointer(L, 2);
	lua_pushboolean(L, inst->getKeyState(keyCode));
	return 1;
}

static int Polycore_CoreInput_getMouseDelta(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMouseDelta();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_CoreInput_setDeltaPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->setDeltaPosition(x, y);
	return 0;
}

static int Polycore_CoreInput_createEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->createEvent(event));
	return 1;
}

static int Polycore_CoreServices_getInstance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getInstance());
	return 1;
}

static int Polycore_CoreServices_getRenderMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getRenderMutex());
	return 1;
}

static int Polycore_CoreServices_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Renderer * r_enderer = (Renderer *)lua_topointer(L, 2);
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_CoreServices_getRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getRenderer());
	return 1;
}

static int Polycore_CoreServices_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_CoreServices_setCore(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Core * core = (Core *)lua_topointer(L, 2);
	inst->setCore(core);
	return 0;
}

static int Polycore_CoreServices_getCore(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getCore());
	return 1;
}

static int Polycore_CoreServices_handleEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->handleEvent(event);
	return 0;
}

static int Polycore_CoreServices_installModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolycodeModule * module = (PolycodeModule *)lua_topointer(L, 2);
	inst->installModule(module);
	return 0;
}

static int Polycore_CoreServices_getMaterialManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getMaterialManager());
	return 1;
}

static int Polycore_CoreServices_getScreenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getScreenManager());
	return 1;
}

static int Polycore_CoreServices_getSceneManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getSceneManager());
	return 1;
}

static int Polycore_CoreServices_getTimerManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTimerManager());
	return 1;
}

static int Polycore_CoreServices_getTweenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTweenManager());
	return 1;
}

static int Polycore_CoreServices_getResourceManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getResourceManager());
	return 1;
}

static int Polycore_CoreServices_getSoundManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getSoundManager());
	return 1;
}

static int Polycore_CoreServices_getFontManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getFontManager());
	return 1;
}

static int Polycore_CoreServices_getConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getConfig());
	return 1;
}

static int Polycore_Cubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture * t0 = (Texture *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * t1 = (Texture *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * t2 = (Texture *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Texture * t3 = (Texture *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Texture * t4 = (Texture *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Texture * t5 = (Texture *)lua_topointer(L, 6);
	Cubemap *inst = new Cubemap(t0, t1, t2, t3, t4, t5);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Data(lua_State *L) {
	Data *inst = new Data();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Data_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadFromFile(fileName);
	return 0;
}

static int Polycore_Data_getAsString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushstring(L, inst->getAsString(encoding).c_str());
	return 1;
}

static int Polycore_Data_setFromString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 3);
	inst->setFromString(str, encoding);
	return 0;
}

static int Polycore_Data_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	lua_pushboolean(L, inst->saveToFile(fileName));
	return 1;
}

static int Polycore_Data_getData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getData());
	return 1;
}

static int Polycore_Entity(lua_State *L) {
	Entity *inst = new Entity();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Entity_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_Entity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Entity_transformAndRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->transformAndRender();
	return 0;
}

static int Polycore_Entity_setMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setMatrix(matrix);
	return 0;
}

static int Polycore_Entity_rebuildTransformMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->rebuildTransformMatrix();
	return 0;
}

static int Polycore_Entity_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * newChild = (Entity *)lua_topointer(L, 2);
	inst->addEntity(newChild);
	return 0;
}

static int Polycore_Entity_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * newChild = (Entity *)lua_topointer(L, 2);
	inst->addChild(newChild);
	return 0;
}

static int Polycore_Entity_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * entityToRemove = (Entity *)lua_topointer(L, 2);
	inst->removeChild(entityToRemove);
	return 0;
}

static int Polycore_Entity_updateEntityMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->updateEntityMatrix();
	return 0;
}

static int Polycore_Entity_renderChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->renderChildren();
	return 0;
}

static int Polycore_Entity_getPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setPosition(x, y, z);
	return 0;
}

static int Polycore_Entity_setPositionX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	inst->setPositionX(x);
	return 0;
}

static int Polycore_Entity_setPositionY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	inst->setPositionY(y);
	return 0;
}

static int Polycore_Entity_setPositionZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number z = lua_tonumber(L, 2);
	inst->setPositionZ(z);
	return 0;
}

static int Polycore_Entity_setScaleX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	inst->setScaleX(x);
	return 0;
}

static int Polycore_Entity_setScaleY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	inst->setScaleY(y);
	return 0;
}

static int Polycore_Entity_setScaleZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number z = lua_tonumber(L, 2);
	inst->setScaleZ(z);
	return 0;
}

static int Polycore_Entity_Translate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->Translate(x, y, z);
	return 0;
}

static int Polycore_Entity_Scale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->Scale(x, y, z);
	return 0;
}

static int Polycore_Entity_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setScale(x, y, z);
	return 0;
}

static int Polycore_Entity_getScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getScale();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getCombinedPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCombinedPosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getCombinedPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getCombinedPitch());
	return 1;
}

static int Polycore_Entity_getCombinedYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getCombinedYaw());
	return 1;
}

static int Polycore_Entity_getCombinedRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getCombinedRoll());
	return 1;
}

static int Polycore_Entity_setParentEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * entity = (Entity *)lua_topointer(L, 2);
	inst->setParentEntity(entity);
	return 0;
}

static int Polycore_Entity_getParentEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getParentEntity());
	return 1;
}

static int Polycore_Entity_rebuildRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->rebuildRotation();
	return 0;
}

static int Polycore_Entity_dirtyMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->dirtyMatrix(val);
	return 0;
}

static int Polycore_Entity_setPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number pitch = lua_tonumber(L, 2);
	inst->setPitch(pitch);
	return 0;
}

static int Polycore_Entity_setYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number yaw = lua_tonumber(L, 2);
	inst->setYaw(yaw);
	return 0;
}

static int Polycore_Entity_setRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->setRoll(roll);
	return 0;
}

static int Polycore_Entity_Roll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->Roll(roll);
	return 0;
}

static int Polycore_Entity_Yaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->Yaw(roll);
	return 0;
}

static int Polycore_Entity_Pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roll = lua_tonumber(L, 2);
	inst->Pitch(roll);
	return 0;
}

static int Polycore_Entity_getPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getPitch());
	return 1;
}

static int Polycore_Entity_getYaw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getYaw());
	return 1;
}

static int Polycore_Entity_getRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getRoll());
	return 1;
}

static int Polycore_Entity_setRotationQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
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

static int Polycore_Entity_getRotationQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->getRotationQuat();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getTransformMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getTransformMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getConcatenatedMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getConcatenatedMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getConcatenatedRollMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getConcatenatedRollMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_setTransformByMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setTransformByMatrix(matrix);
	return 0;
}

static int Polycore_Entity_setTransformByMatrixPure(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setTransformByMatrixPure(matrix);
	return 0;
}

static int Polycore_Entity_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Renderer * r_enderer = (Renderer *)lua_topointer(L, 2);
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_Entity_getCombinedColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Color *retInst = new Color();
	*retInst = inst->getCombinedColor();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_setColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
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

static int Polycore_Entity_setColorInt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
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

static int Polycore_Entity_recalculateBBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->recalculateBBox();
	return 0;
}

static int Polycore_Entity_getBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getBBoxRadius());
	return 1;
}

static int Polycore_Entity_getCompoundBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getCompoundBBoxRadius());
	return 1;
}

static int Polycore_Entity_setBBoxRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number rad = lua_tonumber(L, 2);
	inst->setBBoxRadius(rad);
	return 0;
}

static int Polycore_Entity_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newBl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(newBl_endingMode);
	return 0;
}

static int Polycore_Entity_getChildCenter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getChildCenter();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_setDepthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setDepthWrite(val);
	return 0;
}

static int Polycore_Entity_doUpdates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->doUpdates();
	return 0;
}

static int Polycore_Entity_lookAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & loc = *( Vector3 *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & upVector = *( Vector3 *)lua_topointer(L, 3);
	inst->lookAt(loc, upVector);
	return 0;
}

static int Polycore_Entity_lookAtEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * entity = (Entity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & upVector = *( Vector3 *)lua_topointer(L, 3);
	inst->lookAtEntity(entity, upVector);
	return 0;
}

static int Polycore_Entity_getLookAtMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & loc = *( Vector3 *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & upVector = *( Vector3 *)lua_topointer(L, 3);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getLookAtMatrix(loc, upVector);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_buildPositionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	 Matrix4 *retInst = new  Matrix4();
	*retInst = inst->buildPositionMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_adjustMatrixForChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->adjustMatrixForChildren();
	return 0;
}

static int Polycore_Entity_setMask(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * mask = (Entity *)lua_topointer(L, 2);
	inst->setMask(mask);
	return 0;
}

static int Polycore_Entity_clearMask(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->clearMask();
	return 0;
}

static int Polycore_Entity_getCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCompoundScale();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getEntityProp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String propName = lua_tostring(L, 2);
	lua_pushstring(L, inst->getEntityProp(propName).c_str());
	return 1;
}

static int Polycore_Event(lua_State *L) {
	Event *inst = new Event();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Event_getEventCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getEventCode());
	return 1;
}

static int Polycore_Event_setEventCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 2);
	inst->setEventCode(eventCode);
	return 0;
}

static int Polycore_Event_getDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getDispatcher());
	return 1;
}

static int Polycore_Event_setDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	EventDispatcher * dispatcher = (EventDispatcher *)lua_topointer(L, 2);
	inst->setDispatcher(dispatcher);
	return 0;
}

static int Polycore_Event_getEventType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getEventType().c_str());
	return 1;
}

static int Polycore_EventDispatcher(lua_State *L) {
	EventDispatcher *inst = new EventDispatcher();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_EventDispatcher_removeAllHandlers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	inst->removeAllHandlers();
	return 0;
}

static int Polycore_EventDispatcher_removeAllHandlersForListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	void * listener = (void *)lua_topointer(L, 2);
	inst->removeAllHandlersForListener(listener);
	return 0;
}

static int Polycore_EventDispatcher_addEventListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	EventHandler * handler = (EventHandler *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->addEventListener(handler, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_removeEventListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	EventHandler * handler = (EventHandler *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->removeEventListener(handler, eventCode);
	return 0;
}

static int Polycore_EventDispatcher___dispatchEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->__dispatchEvent(event, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_dispatchEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->dispatchEvent(event, eventCode);
	return 0;
}

static int Polycore_EventDispatcher_dispatchEventNoDelete(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int eventCode = lua_tointeger(L, 3);
	inst->dispatchEventNoDelete(event, eventCode);
	return 0;
}

static int Polycore_EventHandler(lua_State *L) {
	EventHandler *inst = new EventHandler();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_EventHandler_secondaryHandler(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventHandler *inst = (EventHandler*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->secondaryHandler(event);
	return 0;
}

static int Polycore_EventHandler_handleEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventHandler *inst = (EventHandler*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->handleEvent(event);
	return 0;
}

static int Polycore_FixedShader(lua_State *L) {
	FixedShader *inst = new FixedShader();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_FixedShader_createBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShader *inst = (FixedShader*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->createBinding());
	return 1;
}

static int Polycore_FixedShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShader * shader = (FixedShader *)lua_topointer(L, 1);
	FixedShaderBinding *inst = new FixedShaderBinding(shader);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_FixedShaderBinding_addTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 3);
	inst->addTexture(name, texture);
	return 0;
}

static int Polycore_FixedShaderBinding_addCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Cubemap * cubemap = (Cubemap *)lua_topointer(L, 3);
	inst->addCubemap(name, cubemap);
	return 0;
}

static int Polycore_FixedShaderBinding_addParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String type = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = lua_tostring(L, 4);
	inst->addParam(type, name, value);
	return 0;
}

static int Polycore_FixedShaderBinding_getDiffuseTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getDiffuseTexture());
	return 1;
}

static int Polycore_Font(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	Font *inst = new Font(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Font_getFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font *inst = (Font*)lua_topointer(L, 1);
	FT_Face *retInst = new FT_Face();
	*retInst = inst->getFace();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Font_isValid(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font *inst = (Font*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isValid());
	return 1;
}

static int Polycore_FontManager(lua_State *L) {
	FontManager *inst = new FontManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_FontManager_registerFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FontManager *inst = (FontManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String fontPath = lua_tostring(L, 3);
	inst->registerFont(fontName, fontPath);
	return 0;
}

static int Polycore_FontManager_getFontByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FontManager *inst = (FontManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getFontByName(fontName));
	return 1;
}

static int Polycore_GenericScene(lua_State *L) {
	GenericScene *inst = new GenericScene();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_GenericScene_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_GenericScene_RenderDepthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Camera * targetCamera = (Camera *)lua_topointer(L, 2);
	inst->RenderDepthOnly(targetCamera);
	return 0;
}

static int Polycore_GenericScene_addGrid(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String gridTexture = lua_tostring(L, 2);
	inst->addGrid(gridTexture);
	return 0;
}

static int Polycore_GenericScene_readString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * inFile = (OSFILE *)lua_topointer(L, 2);
	lua_pushstring(L, inst->readString(inFile).c_str());
	return 1;
}

static int Polycore_GenericScene_loadScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadScene(fileName);
	return 0;
}

static int Polycore_GenericScene_generateLightmaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number lightMapRes = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number lightMapQuality = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numRadPasses = lua_tointeger(L, 4);
	inst->generateLightmaps(lightMapRes, lightMapQuality, numRadPasses);
	return 0;
}

static int Polycore_GenericScene_addLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneLight * light = (SceneLight *)lua_topointer(L, 2);
	inst->addLight(light);
	return 0;
}

static int Polycore_GenericScene_getNearestLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 pos = *(Vector3*)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getNearestLight(pos));
	return 1;
}

static int Polycore_GenericScene_writeEntityMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	OSFILE * outFile = (OSFILE *)lua_topointer(L, 3);
	inst->writeEntityMatrix(entity, outFile);
	return 0;
}

static int Polycore_GenericScene_writeString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	OSFILE * outFile = (OSFILE *)lua_topointer(L, 3);
	inst->writeString(str, outFile);
	return 0;
}

static int Polycore_GenericScene_saveScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->saveScene(fileName);
	return 0;
}

static int Polycore_GenericScene_getNumStaticGeometry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumStaticGeometry());
	return 1;
}

static int Polycore_GenericScene_getStaticGeometry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getStaticGeometry(index));
	return 1;
}

static int Polycore_GenericScene_loadCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool autoCollide = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int type = lua_tointeger(L, 4);
	inst->loadCollisionChild(entity, autoCollide, type);
	return 0;
}

static int Polycore_GenericScene_getNumLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumLights());
	return 1;
}

static int Polycore_GenericScene_getLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getLight(index));
	return 1;
}

static int Polycore_GenericScene_getCustomEntityByType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	GenericScene *inst = (GenericScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String type = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getCustomEntityByType(type));
	return 1;
}

static int Polycore_OpenGLCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture * t0 = (Texture *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * t1 = (Texture *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * t2 = (Texture *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Texture * t3 = (Texture *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Texture * t4 = (Texture *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Texture * t5 = (Texture *)lua_topointer(L, 6);
	OpenGLCubemap *inst = new OpenGLCubemap(t0, t1, t2, t3, t4, t5);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_OpenGLCubemap_getTextureID(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OpenGLCubemap *inst = (OpenGLCubemap*)lua_topointer(L, 1);
	GLuint *retInst = new GLuint();
	*retInst = inst->getTextureID();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Image(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	Image *inst = new Image(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Image_loadImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	lua_pushboolean(L, inst->loadImage(fileName));
	return 1;
}

static int Polycore_Image_loadPNG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	lua_pushboolean(L, inst->loadPNG(fileName));
	return 1;
}

static int Polycore_Image_createEmpty(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int height = lua_tointeger(L, 3);
	inst->createEmpty(width, height);
	return 0;
}

static int Polycore_Image_fill(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->fill(r, g, b, a);
	return 0;
}

static int Polycore_Image_setPixel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
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

static int Polycore_Image_getPixel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	Color *retInst = new Color();
	*retInst = inst->getPixel(x, y);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Image_setAAPixel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Color col = *(Color*)lua_topointer(L, 4);
	inst->setAAPixel(x, y, col);
	return 0;
}

static int Polycore_Image_swap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	int * v1 = (int *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	int * v2 = (int *)lua_topointer(L, 3);
	inst->swap(v1, v2);
	return 0;
}

static int Polycore_Image_line(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x0 = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y0 = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int x1 = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int y1 = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Color col = *(Color*)lua_topointer(L, 6);
	inst->line(x0, y0, x1, y1, col);
	return 0;
}

static int Polycore_Image_moveTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->moveTo(x, y);
	return 0;
}

static int Polycore_Image_move(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	inst->move(x, y);
	return 0;
}

static int Polycore_Image_lineTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Color col = *(Color*)lua_topointer(L, 4);
	inst->lineTo(x, y, col);
	return 0;
}

static int Polycore_Image_drawRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int x = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int y = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int w = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int h = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Color col = *(Color*)lua_topointer(L, 6);
	inst->drawRect(x, y, w, h, col);
	return 0;
}

static int Polycore_Image_perlinNoise(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int seed = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 3);
	inst->perlinNoise(seed, alpha);
	return 0;
}

static int Polycore_Image_fastBlur(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlur(blurSize);
	return 0;
}

static int Polycore_Image_fastBlurVert(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlurVert(blurSize);
	return 0;
}

static int Polycore_Image_fastBlurHor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int blurSize = lua_tointeger(L, 2);
	inst->fastBlurHor(blurSize);
	return 0;
}

static int Polycore_Image_darken(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4);
	inst->darken(amt, color, alpha);
	return 0;
}

static int Polycore_Image_lighten(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4);
	inst->lighten(amt, color, alpha);
	return 0;
}

static int Polycore_Image_multiply(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number amt = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool color = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool alpha = lua_toboolean(L, 4);
	inst->multiply(amt, color, alpha);
	return 0;
}

static int Polycore_Image_getBrushX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getBrushX());
	return 1;
}

static int Polycore_Image_getBrushY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getBrushY());
	return 1;
}

static int Polycore_Image_isLoaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isLoaded());
	return 1;
}

static int Polycore_Image_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_Image_writeBMP(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->writeBMP(fileName);
	return 0;
}

static int Polycore_Image_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getWidth());
	return 1;
}

static int Polycore_Image_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getHeight());
	return 1;
}

static int Polycore_Image_getPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getPixels());
	return 1;
}

static int Polycore_InputEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector2 mousePosition = *(Vector2*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 2);
	InputEvent *inst = new InputEvent(mousePosition, timestamp);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_InputEvent_keyCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->keyCode());
	return 1;
}

static int Polycore_Label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font * font = (Font *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int antiAliasMode = lua_tointeger(L, 4);
	Label *inst = new Label(font, text, size, antiAliasMode);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Label_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = lua_tostring(L, 2);
	inst->setText(text);
	return 0;
}

static int Polycore_Label_getText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getText().c_str());
	return 1;
}

static int Polycore_Label_getTextWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Font * font = (Font *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String text = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int size = lua_tointeger(L, 4);
	lua_pushinteger(L, inst->getTextWidth(font, text, size));
	return 1;
}

static int Polycore_Label_getTextHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Font * font = (Font *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String text = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int size = lua_tointeger(L, 4);
	lua_pushinteger(L, inst->getTextHeight(font, text, size));
	return 1;
}

static int Polycore_Label_getFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getFont());
	return 1;
}

static int Polycore_Logger(lua_State *L) {
	Logger *inst = new Logger();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Logger_log(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Logger *inst = (Logger*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const char * format = (const char *)lua_topointer(L, 2);
	inst->log(format);
	return 0;
}

static int Polycore_Logger_logw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Logger *inst = (Logger*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const char * str = (const char *)lua_topointer(L, 2);
	inst->logw(str);
	return 0;
}

static int Polycore_Material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = lua_tostring(L, 1);
	Material *inst = new Material(name);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Material_addShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Shader * shader = (Shader *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ShaderBinding * shaderBinding = (ShaderBinding *)lua_topointer(L, 3);
	inst->addShader(shader, shaderBinding);
	return 0;
}

static int Polycore_Material_getNumShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumShaders());
	return 1;
}

static int Polycore_Material_addShaderRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ShaderRenderTarget * newTarget = (ShaderRenderTarget *)lua_topointer(L, 2);
	inst->addShaderRenderTarget(newTarget);
	return 0;
}

static int Polycore_Material_getNumShaderRenderTargets(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumShaderRenderTargets());
	return 1;
}

static int Polycore_Material_getShaderRenderTarget(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getShaderRenderTarget(index));
	return 1;
}

static int Polycore_Material_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getName().c_str());
	return 1;
}

static int Polycore_Material_getShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getShader(index));
	return 1;
}

static int Polycore_Material_getShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getShaderBinding(index));
	return 1;
}

static int Polycore_Material_loadMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadMaterial(fileName);
	return 0;
}

static int Polycore_MaterialManager(lua_State *L) {
	MaterialManager *inst = new MaterialManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_MaterialManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->Update(elapsed);
	return 0;
}

static int Polycore_MaterialManager_createFramebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int type = lua_tointeger(L, 4);
	lua_pushlightuserdata(L, (void*)inst->createFramebufferTexture(width, height, type));
	return 1;
}

static int Polycore_MaterialManager_createTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	char * imageData = (char *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	int type = lua_tointeger(L, 6);
	lua_pushlightuserdata(L, (void*)inst->createTexture(width, height, imageData, clamp, type));
	return 1;
}

static int Polycore_MaterialManager_createNewTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int type = lua_tointeger(L, 5);
	lua_pushlightuserdata(L, (void*)inst->createNewTexture(width, height, clamp, type));
	return 1;
}

static int Polycore_MaterialManager_createTextureFromImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Image * image = (Image *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 3);
	lua_pushlightuserdata(L, (void*)inst->createTextureFromImage(image, clamp));
	return 1;
}

static int Polycore_MaterialManager_createTextureFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 3);
	lua_pushlightuserdata(L, (void*)inst->createTextureFromFile(fileName, clamp));
	return 1;
}

static int Polycore_MaterialManager_deleteTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->deleteTexture(texture);
	return 0;
}

static int Polycore_MaterialManager_reloadTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	inst->reloadTextures();
	return 0;
}

static int Polycore_MaterialManager_reloadProgramsAndTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	inst->reloadProgramsAndTextures();
	return 0;
}

static int Polycore_MaterialManager_reloadPrograms(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	inst->reloadPrograms();
	return 0;
}

static int Polycore_MaterialManager_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolycodeShaderModule * module = (PolycodeShaderModule *)lua_topointer(L, 2);
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_MaterialManager_getTextureByResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String resourcePath = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getTextureByResourcePath(resourcePath));
	return 1;
}

static int Polycore_MaterialManager_cubemapFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->cubemapFromXMLNode(node));
	return 1;
}

static int Polycore_MaterialManager_loadMaterialsFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadMaterialsFromFile(fileName);
	return 0;
}

static int Polycore_MaterialManager_materialFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->materialFromXMLNode(node));
	return 1;
}

static int Polycore_MaterialManager_setShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->setShaderFromXMLNode(node));
	return 1;
}

static int Polycore_MaterialManager_createShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->createShaderFromXMLNode(node));
	return 1;
}

static int Polycore_Matrix4(lua_State *L) {
	Matrix4 *inst = new Matrix4();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Matrix4_init(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	inst->init();
	return 0;
}

static int Polycore_Matrix4_identity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	inst->identity();
	return 0;
}

static int Polycore_Matrix4_rotateVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & v2 = *( Vector3 *)lua_topointer(L, 2);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->rotateVector(v2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Matrix4_getPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->getPosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Matrix4_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setPosition(x, y, z);
	return 0;
}

static int Polycore_Matrix4_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 scale = *(Vector3*)lua_topointer(L, 2);
	inst->setScale(scale);
	return 0;
}

static int Polycore_Matrix4_getEulerAngles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Number * ax = (Number *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Number * ay = (Number *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Number * az = (Number *)lua_topointer(L, 4);
	inst->getEulerAngles(ax, ay, az);
	return 0;
}

static int Polycore_Matrix4_inverse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->inverse();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Matrix4_inverseAffine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->inverseAffine();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	Mesh *inst = new Mesh(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Mesh_addPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Polycode::Polygon * newPolygon = (Polycode::Polygon *)lua_topointer(L, 2);
	inst->addPolygon(newPolygon);
	return 0;
}

static int Polycore_Mesh_loadMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadMesh(fileName);
	return 0;
}

static int Polycore_Mesh_loadFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * inFile = (OSFILE *)lua_topointer(L, 2);
	inst->loadFromFile(inFile);
	return 0;
}

static int Polycore_Mesh_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * outFile = (OSFILE *)lua_topointer(L, 2);
	inst->saveToFile(outFile);
	return 0;
}

static int Polycore_Mesh_getPolygonCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getPolygonCount());
	return 1;
}

static int Polycore_Mesh_getPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getPolygon(index));
	return 1;
}

static int Polycore_Mesh_createPlane(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number h = lua_tonumber(L, 3);
	inst->createPlane(w, h);
	return 0;
}

static int Polycore_Mesh_createBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number d = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number h = lua_tonumber(L, 4);
	inst->createBox(w, d, h);
	return 0;
}

static int Polycore_Mesh_createSphere(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number numRings = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number numSegments = lua_tonumber(L, 4);
	inst->createSphere(radius, numRings, numSegments);
	return 0;
}

static int Polycore_Mesh_addVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vertex * vertex = (Vertex *)lua_topointer(L, 2);
	inst->addVertex(vertex);
	return 0;
}

static int Polycore_Mesh_getVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getVertex(index));
	return 1;
}

static int Polycore_Mesh_getNumVertices(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumVertices());
	return 1;
}

static int Polycore_Mesh_recenterMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->recenterMesh();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Mesh_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->useVertexNormals(val);
	return 0;
}

static int Polycore_Mesh_getVertexIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vertex * vertex = (Vertex *)lua_topointer(L, 2);
	lua_pushinteger(L, inst->getVertexIndex(vertex));
	return 1;
}

static int Polycore_Mesh_setVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	VertexBuffer * buffer = (VertexBuffer *)lua_topointer(L, 2);
	inst->setVertexBuffer(buffer);
	return 0;
}

static int Polycore_Mesh_getVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getVertexBuffer());
	return 1;
}

static int Polycore_Mesh_usesFaceUV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->usesFaceUV());
	return 1;
}

static int Polycore_Mesh_getRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getRadius());
	return 1;
}

static int Polycore_Mesh_calculateNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	inst->calculateNormals();
	return 0;
}

static int Polycore_Mesh_getMeshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getMeshType());
	return 1;
}

static int Polycore_Mesh_setMeshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newType = lua_tointeger(L, 2);
	inst->setMeshType(newType);
	return 0;
}

static int Polycore_Mesh_calculateBBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->calculateBBox();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Mesh_hasVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->hasVertexBuffer());
	return 1;
}

static int Polycore_VertexBuffer(lua_State *L) {
	VertexBuffer *inst = new VertexBuffer();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_VertexBuffer_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_PolycodeModule(lua_State *L) {
	PolycodeModule *inst = new PolycodeModule();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_PolycodeModule_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PolycodeModule *inst = (PolycodeModule*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_ObjectEntry(lua_State *L) {
	ObjectEntry *inst = new ObjectEntry();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ObjectEntry_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->addChild(name));
	return 1;
}

static int Polycore_Particle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool isScreenParticle = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Material * material = (Material *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 5);
	Particle *inst = new Particle(particleType, isScreenParticle, material, texture, particleMesh);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Particle_Reset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool continuious = lua_toboolean(L, 2);
	inst->Reset(continuious);
	return 0;
}

static int Polycore_Particle_createSceneParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 4);
	inst->createSceneParticle(particleType, texture, particleMesh);
	return 0;
}

static int Polycore_Particle_createScreenParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 4);
	inst->createScreenParticle(particleType, texture, particleMesh);
	return 0;
}

static int Polycore_ScreenParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenMesh * emitter = (ScreenMesh *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Screen * particleParentScreen = (Screen *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	unsigned int numParticles = lua_tointeger(L, 8);
	luaL_checktype(L, 9, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 9);
	luaL_checktype(L, 10, LUA_TLIGHTUSERDATA);
	Vector3 gravity = *(Vector3*)lua_topointer(L, 10);
	luaL_checktype(L, 11, LUA_TLIGHTUSERDATA);
	Vector3 deviation = *(Vector3*)lua_topointer(L, 11);
	ScreenParticleEmitter *inst = new ScreenParticleEmitter(imageFile, particleMesh, emitter, particleParentScreen, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * particleBody = (Entity *)lua_topointer(L, 2);
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_ScreenParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_ScreenParticleEmitter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_SceneParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	SceneMesh * emitter = (SceneMesh *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Scene * particleParentScene = (Scene *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	unsigned int numParticles = lua_tointeger(L, 8);
	luaL_checktype(L, 9, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 9);
	luaL_checktype(L, 10, LUA_TLIGHTUSERDATA);
	Vector3 gravity = *(Vector3*)lua_topointer(L, 10);
	luaL_checktype(L, 11, LUA_TLIGHTUSERDATA);
	Vector3 deviation = *(Vector3*)lua_topointer(L, 11);
	SceneParticleEmitter *inst = new SceneParticleEmitter(imageFile, particleMesh, emitter, particleParentScene, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * particleBody = (Entity *)lua_topointer(L, 2);
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_SceneParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getBaseMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_SceneParticleEmitter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Perlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int octaves = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number freq = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number amp = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int seed = lua_tointeger(L, 4);
	Perlin *inst = new Perlin(octaves, freq, amp, seed);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Perlin_Get(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Perlin *inst = (Perlin*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushnumber(L, inst->Get(x, y));
	return 1;
}

static int Polycore_Polygon(lua_State *L) {
	Polycode::Polygon *inst = new Polycode::Polygon();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Polygon_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_Polygon_getVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getVertex(index));
	return 1;
}

static int Polycore_Polygon_addVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	lua_pushlightuserdata(L, (void*)inst->addVertex(x, y, z));
	return 1;
}

static int Polycore_Polygon_removeVertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	inst->removeVertex(index);
	return 0;
}

static int Polycore_Polygon_addTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number u = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number v = lua_tonumber(L, 3);
	inst->addTexCoord(u, v);
	return 0;
}

static int Polycore_Polygon_addTexCoord2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number u = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number v = lua_tonumber(L, 3);
	inst->addTexCoord2(u, v);
	return 0;
}

static int Polycore_Polygon_getTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getTexCoord(index);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Polygon_getTexCoord2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getTexCoord2(index);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Polygon_calculateNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	inst->calculateNormal();
	return 0;
}

static int Polycore_Polygon_getFaceNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getFaceNormal();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Polygon_getBounds2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	Rectangle *retInst = new Rectangle();
	*retInst = inst->getBounds2D();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Polygon_setNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 normal = *(Vector3*)lua_topointer(L, 2);
	inst->setNormal(normal);
	return 0;
}

static int Polycore_Polygon_flipUVY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	inst->flipUVY();
	return 0;
}

static int Polycore_Polygon_setUseFaceUV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setUseFaceUV(val);
	return 0;
}

static int Polycore_Polygon_usesFaceUV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->usesFaceUV());
	return 1;
}

static int Polycore_Quaternion(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number w = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	Quaternion *inst = new Quaternion(w, x, y, z);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Quaternion_setFromMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Matrix4 & kRot = *( Matrix4 *)lua_topointer(L, 2);
	inst->setFromMatrix(kRot);
	return 0;
}

static int Polycore_Quaternion_Slerp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fT = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Quaternion & rkP = *( Quaternion *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	const Quaternion & rkQ = *( Quaternion *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool shortestPath = lua_toboolean(L, 5);
	 Quaternion *retInst = new  Quaternion();
	*retInst = inst->Slerp(fT, rkP, rkQ, shortestPath);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_Dot(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Quaternion & rkQ = *( Quaternion *)lua_topointer(L, 2);
	lua_pushnumber(L, inst->Dot(rkQ));
	return 1;
}

static int Polycore_Quaternion_Log(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Log();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_Exp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Exp();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_Norm(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->Norm());
	return 1;
}

static int Polycore_Quaternion_normalise(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->normalise());
	return 1;
}

static int Polycore_Quaternion_lookAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & D = *( Vector3 *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & upVector = *( Vector3 *)lua_topointer(L, 3);
	inst->lookAt(D, upVector);
	return 0;
}

static int Polycore_Quaternion_createFromMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->createFromMatrix(matrix);
	return 0;
}

static int Polycore_Quaternion_Squad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fT = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Quaternion & rkP = *( Quaternion *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	const Quaternion & rkA = *( Quaternion *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	const Quaternion & rkB = *( Quaternion *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	const Quaternion & rkQ = *( Quaternion *)lua_topointer(L, 6);
	luaL_checktype(L, 7, LUA_TBOOLEAN);
	bool shortestPath = lua_toboolean(L, 7);
	 Quaternion *retInst = new  Quaternion();
	*retInst = inst->Squad(fT, rkP, rkA, rkB, rkQ, shortestPath);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_Inverse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->Inverse();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_set(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
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

static int Polycore_Quaternion_inverse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->inverse();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Quaternion_InvSqrt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	lua_pushnumber(L, inst->InvSqrt(x));
	return 1;
}

static int Polycore_Quaternion_fromAxes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number az = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 4);
	inst->fromAxes(az, ay, ax);
	return 0;
}

static int Polycore_Quaternion_FromAngleAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Number & rfAngle = *( Number *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & rkAxis = *( Vector3 *)lua_topointer(L, 3);
	inst->FromAngleAxis(rfAngle, rkAxis);
	return 0;
}

static int Polycore_Quaternion_ToAngleAxis(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Number & rfAngle = *(Number *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Vector3 & rkAxis = *(Vector3 *)lua_topointer(L, 3);
	inst->ToAngleAxis(rfAngle, rkAxis);
	return 0;
}

static int Polycore_Quaternion_createFromAxisAngle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
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

static int Polycore_Quaternion_createMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->createMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_QuaternionCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve * wCurve = (BezierCurve *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	BezierCurve * xCurve = (BezierCurve *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	BezierCurve * yCurve = (BezierCurve *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	BezierCurve * zCurve = (BezierCurve *)lua_topointer(L, 4);
	QuaternionCurve *inst = new QuaternionCurve(wCurve, xCurve, yCurve, zCurve);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_QuaternionCurve_interpolate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number t = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool useShortestPath = lua_toboolean(L, 3);
	Quaternion *retInst = new Quaternion();
	*retInst = inst->interpolate(t, useShortestPath);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_QuaternionCurve_generatePointsFromCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	BezierCurve * wCurve = (BezierCurve *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	BezierCurve * xCurve = (BezierCurve *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	BezierCurve * yCurve = (BezierCurve *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	BezierCurve * zCurve = (BezierCurve *)lua_topointer(L, 5);
	inst->generatePointsFromCurves(wCurve, xCurve, yCurve, zCurve);
	return 0;
}

static int Polycore_QuaternionCurve_recalcTangents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*)lua_topointer(L, 1);
	inst->recalcTangents();
	return 0;
}

static int Polycore_Rectangle(lua_State *L) {
	Rectangle *inst = new Rectangle();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Rectangle_setRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Rectangle *inst = (Rectangle*)lua_topointer(L, 1);
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

static int Polycore_Resource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	Resource *inst = new Resource(type);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Resource_getResourceName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getResourceName().c_str());
	return 1;
}

static int Polycore_Resource_getResourceType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getResourceType());
	return 1;
}

static int Polycore_Resource_setResourceName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String newName = lua_tostring(L, 2);
	inst->setResourceName(newName);
	return 0;
}

static int Polycore_Resource_setResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = lua_tostring(L, 2);
	inst->setResourcePath(path);
	return 0;
}

static int Polycore_Resource_getResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getResourcePath().c_str());
	return 1;
}

static int Polycore_ResourceManager(lua_State *L) {
	ResourceManager *inst = new ResourceManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ResourceManager_addResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Resource * resource = (Resource *)lua_topointer(L, 2);
	inst->addResource(resource);
	return 0;
}

static int Polycore_ResourceManager_addDirResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->addDirResource(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_addArchive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String zipPath = lua_tostring(L, 2);
	inst->addArchive(zipPath);
	return 0;
}

static int Polycore_ResourceManager_readFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	lua_pushboolean(L, inst->readFile(fileName));
	return 1;
}

static int Polycore_ResourceManager_parseTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseTextures(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseMaterials(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseMaterials(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseShaders(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parsePrograms(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parsePrograms(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseCubemaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseCubemaps(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_getResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int resourceType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String resourceName = lua_tostring(L, 3);
	lua_pushlightuserdata(L, (void*)inst->getResource(resourceType, resourceName));
	return 1;
}

static int Polycore_ResourceManager_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolycodeShaderModule * module = (PolycodeShaderModule *)lua_topointer(L, 2);
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_SceneEntity(lua_State *L) {
	SceneEntity *inst = new SceneEntity();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneEntity_testMouseCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity *inst = (SceneEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->testMouseCollision(x, y));
	return 1;
}

static int Polycore_SceneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fontName = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int amode = lua_tointeger(L, 5);
	SceneLabel *inst = new SceneLabel(fontName, text, size, scale, amode);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneLabel_testMouseCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->testMouseCollision(x, y));
	return 1;
}

static int Polycore_SceneLabel_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String newText = lua_tostring(L, 2);
	inst->setText(newText);
	return 0;
}

static int Polycore_SceneLabel_getLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getLabel());
	return 1;
}

static int Polycore_SceneLabel_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_SceneLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number intensity = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number distance = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Scene * parentScene = (Scene *)lua_topointer(L, 4);
	SceneLight *inst = new SceneLight(type, intensity, distance, parentScene);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneLight_getIntensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getIntensity());
	return 1;
}

static int Polycore_SceneLight_getDistance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getDistance());
	return 1;
}

static int Polycore_SceneLight_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_SceneLight_renderDepthMap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * scene = (Scene *)lua_topointer(L, 2);
	inst->renderDepthMap(scene);
	return 0;
}

static int Polycore_SceneLight_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_SceneLight_getLightViewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getLightViewMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_SceneLight_getZBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getZBufferTexture());
	return 1;
}

static int Polycore_SceneLight_setLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setLightColor(r, g, b);
	return 0;
}

static int Polycore_SceneLight_enableShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number resolution = lua_tonumber(L, 3);
	inst->enableShadows(val, resolution);
	return 0;
}

static int Polycore_SceneLight_setShadowMapFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setShadowMapFOV(fov);
	return 0;
}

static int Polycore_SceneLight_areShadowsEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->areShadowsEnabled());
	return 1;
}

static int Polycore_SceneLight_getLightType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getLightType());
	return 1;
}

static int Polycore_SceneLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity * ent1 = (SceneEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * ent2 = (SceneEntity *)lua_topointer(L, 2);
	SceneLine *inst = new SceneLine(ent1, ent2);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneLine_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLine *inst = (SceneLine*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_SceneManager(lua_State *L) {
	SceneManager *inst = new SceneManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneManager_addScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * newScene = (Scene *)lua_topointer(L, 2);
	inst->addScene(newScene);
	return 0;
}

static int Polycore_SceneManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_SceneManager_UpdateVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	inst->UpdateVirtual();
	return 0;
}

static int Polycore_SceneManager_removeScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * scene = (Scene *)lua_topointer(L, 2);
	inst->removeScene(scene);
	return 0;
}

static int Polycore_SceneManager_registerRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneRenderTexture * r_enderTexture = (SceneRenderTexture *)lua_topointer(L, 2);
	inst->registerRenderTexture(r_enderTexture);
	return 0;
}

static int Polycore_SceneMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	SceneMesh *inst = new SceneMesh(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneMesh_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_SceneMesh_getLocalShaderOptions(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getLocalShaderOptions());
	return 1;
}

static int Polycore_SceneMesh_getMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getMesh());
	return 1;
}

static int Polycore_SceneMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTexture());
	return 1;
}

static int Polycore_SceneMesh_getMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getMaterial());
	return 1;
}

static int Polycore_SceneMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 3);
	inst->loadTexture(fileName, clamp);
	return 0;
}

static int Polycore_SceneMesh_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadSkeleton(fileName);
	return 0;
}

static int Polycore_SceneMesh_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->setTexture(texture);
	return 0;
}

static int Polycore_SceneMesh_setMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Material * material = (Material *)lua_topointer(L, 2);
	inst->setMaterial(material);
	return 0;
}

static int Polycore_SceneMesh_setMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * mesh = (Mesh *)lua_topointer(L, 2);
	inst->setMesh(mesh);
	return 0;
}

static int Polycore_SceneMesh_setSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Skeleton * skeleton = (Skeleton *)lua_topointer(L, 2);
	inst->setSkeleton(skeleton);
	return 0;
}

static int Polycore_SceneMesh_getSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getSkeleton());
	return 1;
}

static int Polycore_SceneMesh_renderMeshLocally(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	inst->renderMeshLocally();
	return 0;
}

static int Polycore_SceneMesh_cacheToVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool cache = lua_toboolean(L, 2);
	inst->cacheToVertexBuffer(cache);
	return 0;
}

static int Polycore_ScenePrimitive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number v1 = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number v2 = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number v3 = lua_tonumber(L, 4);
	ScenePrimitive *inst = new ScenePrimitive(type, v1, v2, v3);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene * targetScene = (Scene *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Camera * targetCamera = (Camera *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int r_enderWidth = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int r_enderHeight = lua_tointeger(L, 4);
	SceneRenderTexture *inst = new SceneRenderTexture(targetScene, targetCamera, r_enderWidth, r_enderHeight);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneRenderTexture_drawScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	inst->drawScreen();
	return 0;
}

static int Polycore_SceneRenderTexture_getTargetTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTargetTexture());
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTargetScene());
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTargetCamera());
	return 1;
}

static int Polycore_Screen(lua_State *L) {
	Screen *inst = new Screen();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Screen_addChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * newEntity = (ScreenEntity *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->addChild(newEntity));
	return 1;
}

static int Polycore_Screen_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * entityToRemove = (ScreenEntity *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->removeChild(entityToRemove));
	return 1;
}

static int Polycore_Screen_setScreenOffset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setScreenOffset(x, y);
	return 0;
}

static int Polycore_Screen_getScreenOffset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getScreenOffset();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Screen_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->Shutdown();
	return 0;
}

static int Polycore_Screen_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Screen_getEntityAt(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushlightuserdata(L, (void*)inst->getEntityAt(x, y));
	return 1;
}

static int Polycore_Screen_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_Screen_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Renderer * r_enderer = (Renderer *)lua_topointer(L, 2);
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_Screen_setNormalizedCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool newVal = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number yCoordinateSize = lua_tonumber(L, 3);
	inst->setNormalizedCoordinates(newVal, yCoordinateSize);
	return 0;
}

static int Polycore_Screen_setScreenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderName = lua_tostring(L, 2);
	inst->setScreenShader(shaderName);
	return 0;
}

static int Polycore_Screen_handleEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->handleEvent(event);
	return 0;
}

static int Polycore_Screen_getHighestZIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getHighestZIndex());
	return 1;
}

static int Polycore_Screen_sortChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->sortChildren();
	return 0;
}

static int Polycore_Screen_cmpZindex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const ScreenEntity * left = (const ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const ScreenEntity * right = (const ScreenEntity *)lua_topointer(L, 3);
	lua_pushboolean(L, inst->cmpZindex(left, right));
	return 1;
}

static int Polycore_Screen_handleInputEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	InputEvent * inputEvent = (InputEvent *)lua_topointer(L, 2);
	inst->handleInputEvent(inputEvent);
	return 0;
}

static int Polycore_Screen_hasFilterShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->hasFilterShader());
	return 1;
}

static int Polycore_Screen_drawFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->drawFilter();
	return 0;
}

static int Polycore_Screen_usesNormalizedCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->usesNormalizedCoordinates());
	return 1;
}

static int Polycore_Screen_getYCoordinateSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getYCoordinateSize());
	return 1;
}

static int Polycore_Screen_getRootEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getRootEntity());
	return 1;
}

static int Polycore_ScreenCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve * curve = (BezierCurve *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int numVertices = lua_tointeger(L, 2);
	ScreenCurve *inst = new ScreenCurve(curve, numVertices);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenEntity(lua_State *L) {
	ScreenEntity *inst = new ScreenEntity();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenEntity_setPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setPosition(x, y);
	return 0;
}

static int Polycore_ScreenEntity_setScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->setScale(x, y);
	return 0;
}

static int Polycore_ScreenEntity_setRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number roatation = lua_tonumber(L, 2);
	inst->setRotation(roatation);
	return 0;
}

static int Polycore_ScreenEntity_getRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getRotation());
	return 1;
}

static int Polycore_ScreenEntity__onMouseDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 5);
	lua_pushboolean(L, inst->_onMouseDown(x, y, mouseButton, timestamp));
	return 1;
}

static int Polycore_ScreenEntity__onMouseUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 5);
	lua_pushboolean(L, inst->_onMouseUp(x, y, mouseButton, timestamp));
	return 1;
}

static int Polycore_ScreenEntity__onMouseMove(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	inst->_onMouseMove(x, y, timestamp);
	return 0;
}

static int Polycore_ScreenEntity__onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	inst->_onMouseWheelUp(x, y, timestamp);
	return 0;
}

static int Polycore_ScreenEntity__onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int timestamp = lua_tointeger(L, 4);
	inst->_onMouseWheelDown(x, y, timestamp);
	return 0;
}

static int Polycore_ScreenEntity_onMouseDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseDown(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseUp(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseMove(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseMove(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseWheelUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelUp(x, y);
	return 0;
}

static int Polycore_ScreenEntity_onMouseWheelDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->onMouseWheelDown(x, y);
	return 0;
}

static int Polycore_ScreenEntity__onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey key = *(TAUKey*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->_onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity__onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey key = *(TAUKey*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->_onKeyUp(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey key = *(TAUKey*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TAUKey key = *(TAUKey*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->onKeyUp(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_hitTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushboolean(L, inst->hitTest(x, y));
	return 1;
}

static int Polycore_ScreenEntity_buildPositionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->buildPositionMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_ScreenEntity_adjustMatrixForChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->adjustMatrixForChildren();
	return 0;
}

static int Polycore_ScreenEntity_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getWidth());
	return 1;
}

static int Polycore_ScreenEntity_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getHeight());
	return 1;
}

static int Polycore_ScreenEntity_setWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	inst->setWidth(w);
	return 0;
}

static int Polycore_ScreenEntity_setHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number h = lua_tonumber(L, 2);
	inst->setHeight(h);
	return 0;
}

static int Polycore_ScreenEntity_onGainFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->onGainFocus();
	return 0;
}

static int Polycore_ScreenEntity_onLoseFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->onLoseFocus();
	return 0;
}

static int Polycore_ScreenEntity_startDrag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number xOffset = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number yOffset = lua_tonumber(L, 3);
	inst->startDrag(xOffset, yOffset);
	return 0;
}

static int Polycore_ScreenEntity_stopDrag(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->stopDrag();
	return 0;
}

static int Polycore_ScreenEntity_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newBl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(newBl_endingMode);
	return 0;
}

static int Polycore_ScreenEntity_setPositionMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newPositionMode = lua_tointeger(L, 2);
	inst->setPositionMode(newPositionMode);
	return 0;
}

static int Polycore_ScreenEntity_setDragLimits(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Rectangle rect = *(Rectangle*)lua_topointer(L, 2);
	inst->setDragLimits(rect);
	return 0;
}

static int Polycore_ScreenEntity_clearDragLimits(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->clearDragLimits();
	return 0;
}

static int Polycore_ScreenEntity_focusChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * child = (ScreenEntity *)lua_topointer(L, 2);
	inst->focusChild(child);
	return 0;
}

static int Polycore_ScreenEntity_focusNextChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	inst->focusNextChild();
	return 0;
}

static int Polycore_ScreenEntity_getPosition2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getPosition2D();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_ScreenEntity_isFocusable(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isFocusable());
	return 1;
}

static int Polycore_ScreenEvent(lua_State *L) {
	ScreenEvent *inst = new ScreenEvent();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	ScreenImage *inst = new ScreenImage(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenImage_setImageCoordinates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenImage *inst = (ScreenImage*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number width = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number height = lua_tonumber(L, 5);
	inst->setImageCoordinates(x, y, width, height);
	return 0;
}

static int Polycore_ScreenImage_getImageWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenImage *inst = (ScreenImage*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getImageWidth());
	return 1;
}

static int Polycore_ScreenImage_getImageHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenImage *inst = (ScreenImage*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getImageHeight());
	return 1;
}

static int Polycore_ScreenLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fontName = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int size = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int amode = lua_tointeger(L, 4);
	ScreenLabel *inst = new ScreenLabel(fontName, text, size, amode);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenLabel_addDropShadow(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLabel *inst = (ScreenLabel*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Color color = *(Color*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number size = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number offsetX = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number offsetY = lua_tonumber(L, 5);
	inst->addDropShadow(color, size, offsetX, offsetY);
	return 0;
}

static int Polycore_ScreenLabel_setText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLabel *inst = (ScreenLabel*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String newText = lua_tostring(L, 2);
	inst->setText(newText);
	return 0;
}

static int Polycore_ScreenLabel_getText(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLabel *inst = (ScreenLabel*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getText().c_str());
	return 1;
}

static int Polycore_ScreenLabel_getLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLabel *inst = (ScreenLabel*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getLabel());
	return 1;
}

static int Polycore_ScreenLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector2 * start = (Vector2 *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector2 * _end = (Vector2 *)lua_topointer(L, 2);
	ScreenLine *inst = new ScreenLine(start, _end);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenLine_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLine *inst = (ScreenLine*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_ScreenLine_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLine *inst = (ScreenLine*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_ScreenLine_setLineWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLine *inst = (ScreenLine*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->setLineWidth(width);
	return 0;
}

static int Polycore_ScreenManager(lua_State *L) {
	ScreenManager *inst = new ScreenManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenManager_removeScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenManager *inst = (ScreenManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Screen * screen = (Screen *)lua_topointer(L, 2);
	inst->removeScreen(screen);
	return 0;
}

static int Polycore_ScreenManager_addScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenManager *inst = (ScreenManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Screen * screen = (Screen *)lua_topointer(L, 2);
	inst->addScreen(screen);
	return 0;
}

static int Polycore_ScreenManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenManager *inst = (ScreenManager*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_ScreenManager_handleEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenManager *inst = (ScreenManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->handleEvent(event);
	return 0;
}

static int Polycore_ScreenMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	ScreenMesh *inst = new ScreenMesh(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenMesh_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_ScreenMesh_getMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getMesh());
	return 1;
}

static int Polycore_ScreenMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getTexture());
	return 1;
}

static int Polycore_ScreenMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadTexture(fileName);
	return 0;
}

static int Polycore_ScreenMesh_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->setTexture(texture);
	return 0;
}

static int Polycore_ScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int shapeType = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number option1 = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number option2 = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number option3 = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number option4 = lua_tonumber(L, 5);
	ScreenShape *inst = new ScreenShape(shapeType, option1, option2, option3, option4);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenShape_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_ScreenShape_setStrokeColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setStrokeColor(r, g, b, a);
	return 0;
}

static int Polycore_ScreenShape_setStrokeWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number width = lua_tonumber(L, 2);
	inst->setStrokeWidth(width);
	return 0;
}

static int Polycore_ScreenShape_setGradient(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r1 = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g1 = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b1 = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a1 = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number r2 = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number g2 = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number b2 = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number a2 = lua_tonumber(L, 9);
	inst->setGradient(r1, g1, b1, a1, r2, g2, b2, a2);
	return 0;
}

static int Polycore_ScreenShape_clearGradient(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	inst->clearGradient();
	return 0;
}

static int Polycore_ScreenShape_setShapeSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number newHeight = lua_tonumber(L, 3);
	inst->setShapeSize(newWidth, newHeight);
	return 0;
}

static int Polycore_ScreenShape_addShapePoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->addShapePoint(x, y);
	return 0;
}

static int Polycore_ScreenSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number spriteWidth = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spriteHeight = lua_tonumber(L, 3);
	ScreenSprite *inst = new ScreenSprite(fileName, spriteWidth, spriteHeight);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenSprite_addAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSprite *inst = (ScreenSprite*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String frames = lua_tostring(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 4);
	inst->addAnimation(name, frames, speed);
	return 0;
}

static int Polycore_ScreenSprite_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSprite *inst = (ScreenSprite*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int startFrame = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool once = lua_toboolean(L, 4);
	inst->playAnimation(name, startFrame, once);
	return 0;
}

static int Polycore_ScreenSprite_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSprite *inst = (ScreenSprite*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_SkeletonAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = lua_tostring(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number duration = lua_tonumber(L, 2);
	SkeletonAnimation *inst = new SkeletonAnimation(name, duration);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SkeletonAnimation_addBoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	BoneTrack * boneTrack = (BoneTrack *)lua_topointer(L, 2);
	inst->addBoneTrack(boneTrack);
	return 0;
}

static int Polycore_SkeletonAnimation_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getName().c_str());
	return 1;
}

static int Polycore_SkeletonAnimation_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	inst->Play();
	return 0;
}

static int Polycore_SkeletonAnimation_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	inst->Stop();
	return 0;
}

static int Polycore_SkeletonAnimation_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_SkeletonAnimation_setSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setSpeed(speed);
	return 0;
}

static int Polycore_Skeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	Skeleton *inst = new Skeleton(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Skeleton_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	inst->loadSkeleton(fileName);
	return 0;
}

static int Polycore_Skeleton_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String animName = lua_tostring(L, 2);
	inst->playAnimation(animName);
	return 0;
}

static int Polycore_Skeleton_playAnimationByIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	inst->playAnimationByIndex(index);
	return 0;
}

static int Polycore_Skeleton_addAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = lua_tostring(L, 3);
	inst->addAnimation(name, fileName);
	return 0;
}

static int Polycore_Skeleton_getAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getAnimation(name));
	return 1;
}

static int Polycore_Skeleton_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Skeleton_getBoneByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = lua_tostring(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getBoneByName(name));
	return 1;
}

static int Polycore_Skeleton_bonesVisible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->bonesVisible(val);
	return 0;
}

static int Polycore_Skeleton_enableBoneLabels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String labelFont = lua_tostring(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number size = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number scale = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Color labelColor = *(Color*)lua_topointer(L, 5);
	inst->enableBoneLabels(labelFont, size, scale, labelColor);
	return 0;
}

static int Polycore_Skeleton_getNumBones(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumBones());
	return 1;
}

static int Polycore_Skeleton_getBone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getBone(index));
	return 1;
}

static int Polycore_Skeleton_getCurrentAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getCurrentAnimation());
	return 1;
}

static int Polycore_BoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone * bone = (Bone *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number length = lua_tonumber(L, 2);
	BoneTrack *inst = new BoneTrack(bone, length);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_BoneTrack_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	inst->Play();
	return 0;
}

static int Polycore_BoneTrack_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	inst->Stop();
	return 0;
}

static int Polycore_BoneTrack_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_BoneTrack_setSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setSpeed(speed);
	return 0;
}

static int Polycore_Sound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = lua_tostring(L, 1);
	Sound *inst = new Sound(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Sound_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool once = lua_toboolean(L, 2);
	inst->Play(once);
	return 0;
}

static int Polycore_Sound_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	inst->Stop();
	return 0;
}

static int Polycore_Sound_loadWAV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	ALuint *retInst = new ALuint();
	*retInst = inst->loadWAV(fileName);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Sound_loadOGG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = lua_tostring(L, 2);
	ALuint *retInst = new ALuint();
	*retInst = inst->loadOGG(fileName);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Sound_GenSource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ALuint buffer = *(ALuint*)lua_topointer(L, 2);
	ALuint *retInst = new ALuint();
	*retInst = inst->GenSource(buffer);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Sound_checkALError(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String operation = lua_tostring(L, 2);
	inst->checkALError(operation);
	return 0;
}

static int Polycore_Sound_soundError(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String err = lua_tostring(L, 2);
	inst->soundError(err);
	return 0;
}

static int Polycore_Sound_soundCheck(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool result = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String err = lua_tostring(L, 3);
	inst->soundCheck(result, err);
	return 0;
}

static int Polycore_SoundManager(lua_State *L) {
	SoundManager *inst = new SoundManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SoundManager_initAL(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	inst->initAL();
	return 0;
}

static int Polycore_String(lua_State *L) {
	String *inst = new String();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_String_size(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->size());
	return 1;
}

static int Polycore_String_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->length());
	return 1;
}

static int Polycore_String_getSTLString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	string *retInst = new string();
	*retInst = inst->getSTLString();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_String_getSTLWString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	wstring *retInst = new wstring();
	*retInst = inst->getSTLWString();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_String_substr(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	size_t pos = *(size_t*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t n = *(size_t*)lua_topointer(L, 3);
	lua_pushstring(L, inst->substr(pos, n).c_str());
	return 1;
}

static int Polycore_String_rfind(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const String & str = *( String *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t pos = *(size_t*)lua_topointer(L, 3);
	lua_pushinteger(L, inst->rfind(str, pos));
	return 1;
}

static int Polycore_String_find(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const String & str = *( String *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t pos = *(size_t*)lua_topointer(L, 3);
	lua_pushinteger(L, inst->find(str, pos));
	return 1;
}

static int Polycore_String_find_last_of(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const String & str = *( String *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t pos = *(size_t*)lua_topointer(L, 3);
	lua_pushinteger(L, inst->find_last_of(str, pos));
	return 1;
}

static int Polycore_String_toLowerCase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushstring(L, inst->toLowerCase().c_str());
	return 1;
}

static int Polycore_String_split(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const String & delims = *( String *)lua_topointer(L, 2);
	vector <String > *retInst = new vector <String >();
	*retInst = inst->split(delims);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_String_replace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const String & what = *( String *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const String & withWhat = *( String *)lua_topointer(L, 3);
	lua_pushstring(L, inst->replace(what, withWhat).c_str());
	return 1;
}

static int Polycore_String_NumberToString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	lua_pushstring(L, inst->NumberToString(value).c_str());
	return 1;
}

static int Polycore_String_c_str(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->c_str());
	return 1;
}

static int Polycore_String_wc_str(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->wc_str());
	return 1;
}

static int Polycore_String_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->data());
	return 1;
}

static int Polycore_String_getDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getDataWithEncoding(encoding));
	return 1;
}

static int Polycore_String_setDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	char * data = (char *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 3);
	inst->setDataWithEncoding(data, encoding);
	return 0;
}

static int Polycore_String_getDataSizeWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushinteger(L, inst->getDataSizeWithEncoding(encoding));
	return 1;
}

static int Polycore_Timer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TBOOLEAN);
	bool triggerMode = lua_toboolean(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int msecs = lua_tointeger(L, 2);
	Timer *inst = new Timer(triggerMode, msecs);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Timer_Pause(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool paused = lua_toboolean(L, 2);
	inst->Pause(paused);
	return 0;
}

static int Polycore_Timer_isPaused(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isPaused());
	return 1;
}

static int Polycore_Timer_getTicks(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getTicks());
	return 1;
}

static int Polycore_Timer_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int ticks = lua_tointeger(L, 2);
	inst->Update(ticks);
	return 0;
}

static int Polycore_Timer_Reset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	inst->Reset();
	return 0;
}

static int Polycore_Timer_hasElapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->hasElapsed());
	return 1;
}

static int Polycore_Timer_getElapsedf(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getElapsedf());
	return 1;
}

static int Polycore_TimerManager(lua_State *L) {
	TimerManager *inst = new TimerManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_TimerManager_removeTimer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TimerManager *inst = (TimerManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Timer * timer = (Timer *)lua_topointer(L, 2);
	inst->removeTimer(timer);
	return 0;
}

static int Polycore_TimerManager_addTimer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TimerManager *inst = (TimerManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Timer * timer = (Timer *)lua_topointer(L, 2);
	inst->addTimer(timer);
	return 0;
}

static int Polycore_TimerManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TimerManager *inst = (TimerManager*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Tween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Number * target = (Number *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int easeType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number startVal = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number _endVal = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number time = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool _repeat = lua_toboolean(L, 6);
	Tween *inst = new Tween(target, easeType, startVal, _endVal, time, _repeat);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Tween_handleEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	inst->handleEvent(event);
	return 0;
}

static int Polycore_Tween_interpolateTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->interpolateTween());
	return 1;
}

static int Polycore_Tween_updateCustomTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	inst->updateCustomTween();
	return 0;
}

static int Polycore_Tween_doOnComplete(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	inst->doOnComplete();
	return 0;
}

static int Polycore_Tween_Pause(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool pauseVal = lua_toboolean(L, 2);
	inst->Pause(pauseVal);
	return 0;
}

static int Polycore_Tween_Reset(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	inst->Reset();
	return 0;
}

static int Polycore_Tween_isComplete(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isComplete());
	return 1;
}

static int Polycore_Tween_setSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setSpeed(speed);
	return 0;
}

static int Polycore_BezierPathTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 * target = (Vector3 *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	BezierCurve * curve = (BezierCurve *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int easeType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number time = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool _repeat = lua_toboolean(L, 5);
	BezierPathTween *inst = new BezierPathTween(target, curve, easeType, time, _repeat);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_BezierPathTween_updateCustomTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierPathTween *inst = (BezierPathTween*)lua_topointer(L, 1);
	inst->updateCustomTween();
	return 0;
}

static int Polycore_QuaternionTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion * target = (Quaternion *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	BezierCurve * wCurve = (BezierCurve *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	BezierCurve * xCurve = (BezierCurve *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	BezierCurve * yCurve = (BezierCurve *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	BezierCurve * zCurve = (BezierCurve *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	int easeType = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number time = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TBOOLEAN);
	bool _repeat = lua_toboolean(L, 8);
	QuaternionTween *inst = new QuaternionTween(target, wCurve, xCurve, yCurve, zCurve, easeType, time, _repeat);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_QuaternionTween_updateCustomTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionTween *inst = (QuaternionTween*)lua_topointer(L, 1);
	inst->updateCustomTween();
	return 0;
}

static int Polycore_TweenManager(lua_State *L) {
	TweenManager *inst = new TweenManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_TweenManager_addTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TweenManager *inst = (TweenManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Tween * tween = (Tween *)lua_topointer(L, 2);
	inst->addTween(tween);
	return 0;
}

static int Polycore_TweenManager_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TweenManager *inst = (TweenManager*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Vector2(lua_State *L) {
	Vector2 *inst = new Vector2();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Vector3(lua_State *L) {
	Vector3 *inst = new Vector3();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Vector3_set(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->set(x, y, z);
	return 0;
}

static int Polycore_Vector3_distance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & rhs = *( Vector3 *)lua_topointer(L, 2);
	lua_pushnumber(L, inst->distance(rhs));
	return 1;
}

static int Polycore_Vector3_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->length());
	return 1;
}

static int Polycore_Vector3_dot(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 & u = *(Vector3 *)lua_topointer(L, 2);
	lua_pushnumber(L, inst->dot(u));
	return 1;
}

static int Polycore_Vector3_crossProduct(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & rkVector = *( Vector3 *)lua_topointer(L, 2);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->crossProduct(rkVector);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Vector3_Normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	inst->Normalize();
	return 0;
}

static int Polycore_Vertex(lua_State *L) {
	Vertex *inst = new Vertex();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Vertex_addBoneAssignment(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int boneID = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number boneWeight = lua_tonumber(L, 3);
	inst->addBoneAssignment(boneID, boneWeight);
	return 0;
}

static int Polycore_Vertex_getNumBoneAssignments(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumBoneAssignments());
	return 1;
}

static int Polycore_Vertex_getBoneAssignment(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getBoneAssignment(index));
	return 1;
}

static int Polycore_Vertex_normalizeWeights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	inst->normalizeWeights();
	return 0;
}

static int Polycore_Vertex_getTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getTexCoord();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Vertex_setTexCoord(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number u = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number v = lua_tonumber(L, 3);
	inst->setTexCoord(u, v);
	return 0;
}

static int Polycore_Vertex_setNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number z = lua_tonumber(L, 4);
	inst->setNormal(x, y, z);
	return 0;
}

}