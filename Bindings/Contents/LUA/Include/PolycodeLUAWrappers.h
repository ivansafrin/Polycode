#pragma once

#include <Polycode.h>

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

class LuaEventHandler : public EventHandler {
public:
	LuaEventHandler() : EventHandler() {}
	~LuaEventHandler();
	void handleEvent(Event *e) {
		lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );
		lua_getfield(L, -1, "__handleEvent");
		lua_rawgeti( L, LUA_REGISTRYINDEX, wrapperIndex );
		lua_pushlightuserdata(L, e);
		lua_call(L, 2, 0);
	}
	int wrapperIndex;
	lua_State *L;
};
static int Polycore_OSFILE_get_fileType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFILE *inst = (OSFILE*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->fileType);
	return 1;
}

static int Polycore_OSFILE_set_fileType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFILE *inst = (OSFILE*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->fileType = param;
	return 0;
}

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

static int Polycore_delete_OSFILE(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFILE *inst = (OSFILE*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_OSFileEntry_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycore_OSFileEntry_get_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->extension.c_str());
	return 1;
}

static int Polycore_OSFileEntry_get_nameWithoutExtension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->nameWithoutExtension.c_str());
	return 1;
}

static int Polycore_OSFileEntry_get_basePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->basePath.c_str());
	return 1;
}

static int Polycore_OSFileEntry_get_fullPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->fullPath.c_str());
	return 1;
}

static int Polycore_OSFileEntry_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycore_OSFileEntry_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycore_OSFileEntry_set_extension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->extension = param;
	return 0;
}

static int Polycore_OSFileEntry_set_nameWithoutExtension(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->nameWithoutExtension = param;
	return 0;
}

static int Polycore_OSFileEntry_set_basePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->basePath = param;
	return 0;
}

static int Polycore_OSFileEntry_set_fullPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->fullPath = param;
	return 0;
}

static int Polycore_OSFileEntry_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycore_OSFileEntry(lua_State *L) {
	OSFileEntry *inst = new OSFileEntry();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_OSFileEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSFileEntry *inst = (OSFileEntry*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_OSBasics_open(lua_State *L) {
	luaL_checktype(L, 2, LUA_TSTRING);
	String filename = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String opts = String(lua_tostring(L, 3));
	void *ptrRetVal = (void*)OSBasics::open(filename, opts);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_OSBasics_close(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * file = (OSFILE *)lua_topointer(L, 2);
	lua_pushinteger(L, OSBasics::close(file));
	return 1;
}

static int Polycore_OSBasics_read(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	void * ptr = (void *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t size = *(size_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	size_t count = *(size_t*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 5);
	lua_pushinteger(L, OSBasics::read(ptr, size, count, stream));
	return 1;
}

static int Polycore_OSBasics_write(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const void * ptr = (const void *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	size_t size = *(size_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	size_t count = *(size_t*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 5);
	lua_pushinteger(L, OSBasics::write(ptr, size, count, stream));
	return 1;
}

static int Polycore_OSBasics_seek(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	long int offset = *(long int*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int origin = lua_tointeger(L, 4);
	lua_pushinteger(L, OSBasics::seek(stream, offset, origin));
	return 1;
}

static int Polycore_OSBasics_tell(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * stream = (OSFILE *)lua_topointer(L, 2);
	lua_pushinteger(L, OSBasics::tell(stream));
	return 1;
}

static int Polycore_OSBasics_isFolder(lua_State *L) {
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = String(lua_tostring(L, 2));
	lua_pushboolean(L, OSBasics::isFolder(pathString));
	return 1;
}

static int Polycore_OSBasics_createFolder(lua_State *L) {
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = String(lua_tostring(L, 2));
	OSBasics::createFolder(pathString);
	return 0;
}

static int Polycore_OSBasics_removeItem(lua_State *L) {
	luaL_checktype(L, 2, LUA_TSTRING);
	String pathString = String(lua_tostring(L, 2));
	OSBasics::removeItem(pathString);
	return 0;
}

static int Polycore_delete_OSBasics(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	OSBasics *inst = (OSBasics*)lua_topointer(L, 1);
	delete inst;
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
	void *ptrRetVal = (void*)inst->getControlPoint(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	Vector3 *retInst = new Vector3();
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

static int Polycore_delete_BezierCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierCurve *inst = (BezierCurve*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Bone_get_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->parentBoneId);
	return 1;
}

static int Polycore_Bone_get_boneMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->boneMatrix);
	return 1;
}

static int Polycore_Bone_get_restMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->restMatrix);
	return 1;
}

static int Polycore_Bone_get_baseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->baseMatrix);
	return 1;
}

static int Polycore_Bone_set_parentBoneId(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->parentBoneId = param;
	return 0;
}

static int Polycore_Bone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String boneName = String(lua_tostring(L, 1));
	Bone *inst = new Bone(boneName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Bone_enableBoneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String labelFont = String(lua_tostring(L, 2));
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
	void *ptrRetVal = (void*)inst->getParentBone();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->getChildBone(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_Bone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Bone *inst = (Bone*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_Camera_setParentScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * parentScene = (Scene *)lua_topointer(L, 2);
	inst->setParentScene(parentScene);
	return 0;
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
	String shaderName = String(lua_tostring(L, 2));
	inst->setPostFilter(shaderName);
	return 0;
}

static int Polycore_Camera_removePostFilter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	inst->removePostFilter();
	return 0;
}

static int Polycore_Camera_getScreenShaderMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getScreenShaderMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Camera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Camera *inst = (Camera*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Color_get_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->r);
	return 1;
}

static int Polycore_Color_get_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->g);
	return 1;
}

static int Polycore_Color_get_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->b);
	return 1;
}

static int Polycore_Color_get_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->a);
	return 1;
}

static int Polycore_Color_set_r(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->r = param;
	return 0;
}

static int Polycore_Color_set_g(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->g = param;
	return 0;
}

static int Polycore_Color_set_b(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->b = param;
	return 0;
}

static int Polycore_Color_set_a(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->a = param;
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

static int Polycore_delete_Color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Color *inst = (Color*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->loadConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_saveConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->saveConfig(configNamespace, fileName);
	return 0;
}

static int Polycore_Config_getEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	void *ptrRetVal = (void*)inst->getEntry(configNamespace, key);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Config_setStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = String(lua_tostring(L, 4));
	inst->setStringValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_setNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number value = lua_tonumber(L, 4);
	inst->setNumericValue(configNamespace, key, value);
	return 0;
}

static int Polycore_Config_getNumericValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	lua_pushnumber(L, inst->getNumericValue(configNamespace, key));
	return 1;
}

static int Polycore_Config_getStringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String configNamespace = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String key = String(lua_tostring(L, 3));
	lua_pushstring(L, inst->getStringValue(configNamespace, key).c_str());
	return 1;
}

static int Polycore_delete_Config(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Config *inst = (Config*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_PolycodeViewBase(lua_State *L) {
	PolycodeViewBase *inst = new PolycodeViewBase();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_PolycodeViewBase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PolycodeViewBase *inst = (PolycodeViewBase*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Core_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->Update());
	return 1;
}

static int Polycore_Core_enableMouse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool newval = lua_toboolean(L, 2);
	inst->enableMouse(newval);
	return 0;
}

static int Polycore_Core_setCursor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int cursorType = lua_tointeger(L, 2);
	inst->setCursor(cursorType);
	return 0;
}

static int Polycore_Core_createThread(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Threaded * target = (Threaded *)lua_topointer(L, 2);
	inst->createThread(target);
	return 0;
}

static int Polycore_Core_lockMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CoreMutex * mutex = (CoreMutex *)lua_topointer(L, 2);
	inst->lockMutex(mutex);
	return 0;
}

static int Polycore_Core_unlockMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CoreMutex * mutex = (CoreMutex *)lua_topointer(L, 2);
	inst->unlockMutex(mutex);
	return 0;
}

static int Polycore_Core_createMutex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->createMutex();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Core_copyStringToClipboard(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	inst->copyStringToClipboard(str);
	return 0;
}

static int Polycore_Core_getClipboardString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	 String *retInst = new  String();
	*retInst = inst->getClipboardString();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Core_getServices(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getServices();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Core_getFPS(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getFPS());
	return 1;
}

static int Polycore_Core_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	inst->Shutdown();
	return 0;
}

static int Polycore_Core_isFullscreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isFullscreen());
	return 1;
}

static int Polycore_Core_getAALevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getAALevel());
	return 1;
}

static int Polycore_Core_getInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getInput();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Core_getXRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getXRes());
	return 1;
}

static int Polycore_Core_getYRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getYRes());
	return 1;
}

static int Polycore_Core_getNumVideoModes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumVideoModes());
	return 1;
}

static int Polycore_Core_createFolder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String folderPath = String(lua_tostring(L, 2));
	inst->createFolder(folderPath);
	return 0;
}

static int Polycore_Core_copyDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String destItemPath = String(lua_tostring(L, 3));
	inst->copyDiskItem(itemPath, destItemPath);
	return 0;
}

static int Polycore_Core_moveDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String destItemPath = String(lua_tostring(L, 3));
	inst->moveDiskItem(itemPath, destItemPath);
	return 0;
}

static int Polycore_Core_removeDiskItem(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String itemPath = String(lua_tostring(L, 2));
	inst->removeDiskItem(itemPath);
	return 0;
}

static int Polycore_Core_openFolderPicker(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	 String *retInst = new  String();
	*retInst = inst->openFolderPicker();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Core_setVideoModeIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool fullScreen = lua_toboolean(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int aaLevel = lua_tointeger(L, 4);
	inst->setVideoModeIndex(index, fullScreen, aaLevel);
	return 0;
}

static int Polycore_Core_setVideoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool fullScreen = lua_toboolean(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int aaLevel = lua_tointeger(L, 5);
	inst->setVideoMode(xRes, yRes, fullScreen, aaLevel);
	return 0;
}

static int Polycore_Core_resizeTo(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	inst->resizeTo(xRes, yRes);
	return 0;
}

static int Polycore_Core_doSleep(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	inst->doSleep();
	return 0;
}

static int Polycore_Core_getElapsed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getElapsed());
	return 1;
}

static int Polycore_Core_getTicks(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	 unsigned int *retInst = new  unsigned int();
	*retInst = inst->getTicks();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Core_getTicksFloat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getTicksFloat());
	return 1;
}

static int Polycore_Core_setUserPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	void * ptr = (void *)lua_topointer(L, 2);
	inst->setUserPointer(ptr);
	return 0;
}

static int Polycore_Core_getUserPointer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getUserPointer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Core(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Core *inst = (Core*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_CoreInput(lua_State *L) {
	CoreInput *inst = new CoreInput();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_CoreInput_getMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMousePosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_CoreInput_getKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolyKEY keyCode = *(PolyKEY*)lua_topointer(L, 2);
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

static int Polycore_CoreInput_getMouseButtonState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mouseButton = lua_tointeger(L, 2);
	lua_pushboolean(L, inst->getMouseButtonState(mouseButton));
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

static int Polycore_CoreInput_setKeyState(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolyKEY keyCode = *(PolyKEY*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t code = *(wchar_t*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool newState = lua_toboolean(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int ticks = lua_tointeger(L, 5);
	inst->setKeyState(keyCode, code, newState, ticks);
	return 0;
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
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Event * event = (Event *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)CoreInput::createEvent(event);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_CoreInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreInput *inst = (CoreInput*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_CoreServices_getInstance(lua_State *L) {
	void *ptrRetVal = (void*)CoreServices::getInstance();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_setInstance(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CoreServices * _instance = (CoreServices *)lua_topointer(L, 2);
	CoreServices::setInstance(_instance);
	return 0;
}

static int Polycore_CoreServices_getRenderMutex(lua_State *L) {
	void *ptrRetVal = (void*)CoreServices::getRenderMutex();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->getRenderer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->getCore();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
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
	void *ptrRetVal = (void*)inst->getMaterialManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getScreenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getScreenManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getSceneManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getSceneManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getTimerManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTimerManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getTweenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTweenManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getResourceManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getResourceManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getSoundManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getSoundManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getFontManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getFontManager();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_CoreServices_getConfig(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getConfig();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_CoreServices(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_Cubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Cubemap *inst = (Cubemap*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	String fileName = String(lua_tostring(L, 2));
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
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 3);
	inst->setFromString(str, encoding);
	return 0;
}

static int Polycore_Data_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->saveToFile(fileName));
	return 1;
}

static int Polycore_Data_getData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Data *inst = (Data*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Entity_get_custEntityType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushstring(L, inst->custEntityType.c_str());
	return 1;
}

static int Polycore_Entity_get_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->billboardMode);
	return 1;
}

static int Polycore_Entity_get_billboardRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->billboardRoll);
	return 1;
}

static int Polycore_Entity_get_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->alphaTest);
	return 1;
}

static int Polycore_Entity_get_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->backfaceCulled);
	return 1;
}

static int Polycore_Entity_get_renderWireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->renderWireframe);
	return 1;
}

static int Polycore_Entity_get_color(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->color);
	return 1;
}

static int Polycore_Entity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Entity_get_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->visible);
	return 1;
}

static int Polycore_Entity_get_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->depthWrite);
	return 1;
}

static int Polycore_Entity_get_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->depthTest);
	return 1;
}

static int Polycore_Entity_get_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->blendingMode);
	return 1;
}

static int Polycore_Entity_get_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->colorAffectsChildren);
	return 1;
}

static int Polycore_Entity_get_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->depthOnly);
	return 1;
}

static int Polycore_Entity_get_bBox(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->bBox);
	return 1;
}

static int Polycore_Entity_get_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->ignoreParentMatrix);
	return 1;
}

static int Polycore_Entity_get_isMask(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isMask);
	return 1;
}

static int Polycore_Entity_set_custEntityType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->custEntityType = param;
	return 0;
}

static int Polycore_Entity_set_billboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->billboardMode = param;
	return 0;
}

static int Polycore_Entity_set_billboardRoll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->billboardRoll = param;
	return 0;
}

static int Polycore_Entity_set_alphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->alphaTest = param;
	return 0;
}

static int Polycore_Entity_set_backfaceCulled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->backfaceCulled = param;
	return 0;
}

static int Polycore_Entity_set_renderWireframe(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->renderWireframe = param;
	return 0;
}

static int Polycore_Entity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->enabled = param;
	return 0;
}

static int Polycore_Entity_set_visible(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->visible = param;
	return 0;
}

static int Polycore_Entity_set_depthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->depthWrite = param;
	return 0;
}

static int Polycore_Entity_set_depthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->depthTest = param;
	return 0;
}

static int Polycore_Entity_set_blendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->blendingMode = param;
	return 0;
}

static int Polycore_Entity_set_colorAffectsChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->colorAffectsChildren = param;
	return 0;
}

static int Polycore_Entity_set_depthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->depthOnly = param;
	return 0;
}

static int Polycore_Entity_set_ignoreParentMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->ignoreParentMatrix = param;
	return 0;
}

static int Polycore_Entity_set_isMask(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->isMask = param;
	return 0;
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

static int Polycore_Entity_renderChildren(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->renderChildren();
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

static int Polycore_Entity_rebuildTransformMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->rebuildTransformMatrix();
	return 0;
}

static int Polycore_Entity_updateEntityMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->updateEntityMatrix();
	return 0;
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
	void *ptrRetVal = (void*)inst->getParentEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Entity_getPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getPosition();
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

static int Polycore_Entity_getCompoundScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCompoundScale();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Entity_getScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getScale();
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

static int Polycore_Entity_rebuildRotation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->rebuildRotation();
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
	Number yaw = lua_tonumber(L, 2);
	inst->Yaw(yaw);
	return 0;
}

static int Polycore_Entity_Pitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number pitch = lua_tonumber(L, 2);
	inst->Pitch(pitch);
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

static int Polycore_Entity_getEntityProp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String propName = String(lua_tostring(L, 2));
	lua_pushstring(L, inst->getEntityProp(propName).c_str());
	return 1;
}

static int Polycore_Entity_doUpdates(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	inst->doUpdates();
	return 0;
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

static int Polycore_Entity_setRenderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Renderer * r_enderer = (Renderer *)lua_topointer(L, 2);
	inst->setRenderer(r_enderer);
	return 0;
}

static int Polycore_delete_Entity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Entity *inst = (Entity*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_Event_getDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getDispatcher();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_Event(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Event *inst = (Event*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_EventDispatcher(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventDispatcher *inst = (EventDispatcher*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_EventHandler(lua_State *L) {
	LuaEventHandler *inst = new LuaEventHandler();
	inst->wrapperIndex = luaL_ref(L, LUA_REGISTRYINDEX );
	inst->L = L;
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_EventHandler(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	EventHandler *inst = (EventHandler*)lua_topointer(L, 1);
	delete inst;
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
	void *ptrRetVal = (void*)inst->createBinding();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_FixedShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShader *inst = (FixedShader*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 3);
	inst->addTexture(name, texture);
	return 0;
}

static int Polycore_FixedShaderBinding_addCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Cubemap * cubemap = (Cubemap *)lua_topointer(L, 3);
	inst->addCubemap(name, cubemap);
	return 0;
}

static int Polycore_FixedShaderBinding_addParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String type = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = String(lua_tostring(L, 4));
	inst->addParam(type, name, value);
	return 0;
}

static int Polycore_FixedShaderBinding_getDiffuseTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getDiffuseTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_FixedShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FixedShaderBinding *inst = (FixedShaderBinding*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Font_get_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font *inst = (Font*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->loaded);
	return 1;
}

static int Polycore_Font_set_loaded(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font *inst = (Font*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->loaded = param;
	return 0;
}

static int Polycore_Font(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
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

static int Polycore_delete_Font(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font *inst = (Font*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	String fontName = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fontPath = String(lua_tostring(L, 3));
	inst->registerFont(fontName, fontPath);
	return 0;
}

static int Polycore_FontManager_getFontByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FontManager *inst = (FontManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getFontByName(fontName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_FontManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	FontManager *inst = (FontManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Image(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Image *inst = new Image(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Image_loadImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->loadImage(fileName));
	return 1;
}

static int Polycore_Image_loadPNG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
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
	String fileName = String(lua_tostring(L, 2));
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
	void *ptrRetVal = (void*)inst->getPixels();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Image(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Image *inst = (Image*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_InputEvent_get_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->mouseButton);
	return 1;
}

static int Polycore_InputEvent_get_mousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->mousePosition);
	return 1;
}

static int Polycore_InputEvent_get_key(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->key);
	return 1;
}

static int Polycore_InputEvent_get_charCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->charCode);
	return 1;
}

static int Polycore_InputEvent_get_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->timestamp);
	return 1;
}

static int Polycore_InputEvent_set_mouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->mouseButton = param;
	return 0;
}

static int Polycore_InputEvent_set_timestamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->timestamp = param;
	return 0;
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

static int Polycore_InputEvent_getMousePosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getMousePosition();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_InputEvent_getKey(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	PolyKEY *retInst = new PolyKEY();
	*retInst = inst->getKey();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_InputEvent_getMouseButton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getMouseButton());
	return 1;
}

static int Polycore_InputEvent_keyCode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->keyCode());
	return 1;
}

static int Polycore_delete_InputEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	InputEvent *inst = (InputEvent*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Font * font = (Font *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
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
	String text = String(lua_tostring(L, 2));
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
	String text = String(lua_tostring(L, 3));
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
	String text = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	int size = lua_tointeger(L, 4);
	lua_pushinteger(L, inst->getTextHeight(font, text, size));
	return 1;
}

static int Polycore_Label_getFont(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getFont();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Label(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Label *inst = (Label*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Logger(lua_State *L) {
	Logger *inst = new Logger();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Logger_log(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const char * format = (const char *)lua_topointer(L, 2);
	Logger::log(format);
	return 0;
}

static int Polycore_Logger_logw(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const char * str = (const char *)lua_topointer(L, 2);
	Logger::logw(str);
	return 0;
}

static int Polycore_delete_Logger(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Logger *inst = (Logger*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Material_get_specularValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->specularValue);
	return 1;
}

static int Polycore_Material_get_specularColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->specularColor);
	return 1;
}

static int Polycore_Material_get_diffuseColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->diffuseColor);
	return 1;
}

static int Polycore_Material_set_specularValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->specularValue = param;
	return 0;
}

static int Polycore_Material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
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
	void *ptrRetVal = (void*)inst->getShaderRenderTarget(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->getShader(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Material_getShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getShaderBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Material_loadMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadMaterial(fileName);
	return 0;
}

static int Polycore_delete_Material(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Material *inst = (Material*)lua_topointer(L, 1);
	delete inst;
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
	void *ptrRetVal = (void*)inst->createFramebufferTexture(width, height, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	bool clamp;
	if(lua_isboolean(L, 5)) {
		clamp = lua_toboolean(L, 5);
	} else {
		clamp = true;
	}
	int type;
	if(lua_isnumber(L, 6)) {
		type = lua_tointeger(L, 6);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	void *ptrRetVal = (void*)inst->createTexture(width, height, imageData, clamp, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_createNewTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int height = lua_tointeger(L, 3);
	bool clamp;
	if(lua_isboolean(L, 4)) {
		clamp = lua_toboolean(L, 4);
	} else {
		clamp = true;
	}
	int type;
	if(lua_isnumber(L, 5)) {
		type = lua_tointeger(L, 5);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	void *ptrRetVal = (void*)inst->createNewTexture(width, height, clamp, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_createTextureFromImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Image * image = (Image *)lua_topointer(L, 2);
	bool clamp;
	if(lua_isboolean(L, 3)) {
		clamp = lua_toboolean(L, 3);
	} else {
		clamp = true;
	}
	void *ptrRetVal = (void*)inst->createTextureFromImage(image, clamp);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_createTextureFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	bool clamp;
	if(lua_isboolean(L, 3)) {
		clamp = lua_toboolean(L, 3);
	} else {
		clamp = true;
	}
	void *ptrRetVal = (void*)inst->createTextureFromFile(fileName, clamp);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	String resourcePath = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getTextureByResourcePath(resourcePath);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_cubemapFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->cubemapFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_loadMaterialsFromFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadMaterialsFromFile(fileName);
	return 0;
}

static int Polycore_MaterialManager_materialFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->materialFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_setShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->setShaderFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_MaterialManager_createShaderFromXMLNode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	TiXmlNode * node = (TiXmlNode *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->createShaderFromXMLNode(node);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_MaterialManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	MaterialManager *inst = (MaterialManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Matrix4(lua_State *L) {
	Matrix4 *inst = new Matrix4();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
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

static int Polycore_delete_Matrix4(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Matrix4 *inst = (Matrix4*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Mesh_get_useVertexColors(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useVertexColors);
	return 1;
}

static int Polycore_Mesh_set_useVertexColors(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useVertexColors = param;
	return 0;
}

static int Polycore_Mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int meshType = lua_tointeger(L, 1);
	Mesh *inst = new Mesh(meshType);
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
	String fileName = String(lua_tostring(L, 2));
	inst->loadMesh(fileName);
	return 0;
}

static int Polycore_Mesh_saveToFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->saveToFile(fileName);
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

static int Polycore_Mesh_getPolygonCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getPolygonCount());
	return 1;
}

static int Polycore_Mesh_getVertexCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getVertexCount());
	return 1;
}

static int Polycore_Mesh_getPolygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getPolygon(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_Mesh_createVPlane(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number w = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number h = lua_tonumber(L, 3);
	inst->createVPlane(w, h);
	return 0;
}

static int Polycore_Mesh_createTorus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number tubeRadius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int rSegments = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int tSegments = lua_tointeger(L, 5);
	inst->createTorus(radius, tubeRadius, rSegments, tSegments);
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
	int numRings = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	inst->createSphere(radius, numRings, numSegments);
	return 0;
}

static int Polycore_Mesh_createCylinder(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	inst->createCylinder(height, radius, numSegments);
	return 0;
}

static int Polycore_Mesh_createCone(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number height = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number radius = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numSegments = lua_tointeger(L, 4);
	inst->createCone(height, radius, numSegments);
	return 0;
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
	void *ptrRetVal = (void*)inst->getVertexBuffer();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	bool smooth;
	if(lua_isboolean(L, 2)) {
		smooth = lua_toboolean(L, 2);
	} else {
		smooth = true;
	}
	Number smoothAngle;
	if(lua_isnumber(L, 3)) {
		smoothAngle = lua_tonumber(L, 3);
	} else {
		smoothAngle = 90.0;
	}
	inst->calculateNormals(smooth, smoothAngle);
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

static int Polycore_delete_Mesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Mesh *inst = (Mesh*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_VertexBuffer_get_verticesPerFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->verticesPerFace);
	return 1;
}

static int Polycore_VertexBuffer_get_meshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->meshType);
	return 1;
}

static int Polycore_VertexBuffer_set_verticesPerFace(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->verticesPerFace = param;
	return 0;
}

static int Polycore_VertexBuffer_set_meshType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->meshType = param;
	return 0;
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

static int Polycore_delete_VertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	VertexBuffer *inst = (VertexBuffer*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_PolycodeModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PolycodeModule *inst = (PolycodeModule*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ObjectEntry_get_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->type);
	return 1;
}

static int Polycore_ObjectEntry_get_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->name.c_str());
	return 1;
}

static int Polycore_ObjectEntry_get_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->NumberVal);
	return 1;
}

static int Polycore_ObjectEntry_get_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->intVal);
	return 1;
}

static int Polycore_ObjectEntry_get_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushstring(L, inst->stringVal.c_str());
	return 1;
}

static int Polycore_ObjectEntry_get_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->boolVal);
	return 1;
}

static int Polycore_ObjectEntry_get_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->length);
	return 1;
}

static int Polycore_ObjectEntry_set_type(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->type = param;
	return 0;
}

static int Polycore_ObjectEntry_set_name(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->name = param;
	return 0;
}

static int Polycore_ObjectEntry_set_NumberVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->NumberVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_intVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->intVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_stringVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	String param = lua_tostring(L, 2);
	inst->stringVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_boolVal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->boolVal = param;
	return 0;
}

static int Polycore_ObjectEntry_set_length(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->length = param;
	return 0;
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
	String name = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->addChild(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_ObjectEntry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ObjectEntry *inst = (ObjectEntry*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Particle_get_velVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->velVector);
	return 1;
}

static int Polycore_Particle_get_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->dirVector);
	return 1;
}

static int Polycore_Particle_get_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->deviation);
	return 1;
}

static int Polycore_Particle_get_life(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->life);
	return 1;
}

static int Polycore_Particle_get_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->lifespan);
	return 1;
}

static int Polycore_Particle_get_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->brightnessDeviation);
	return 1;
}

static int Polycore_Particle_get_perlinPosX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->perlinPosX);
	return 1;
}

static int Polycore_Particle_get_perlinPosY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->perlinPosY);
	return 1;
}

static int Polycore_Particle_get_perlinPosZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->perlinPosZ);
	return 1;
}

static int Polycore_Particle_set_life(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->life = param;
	return 0;
}

static int Polycore_Particle_set_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->lifespan = param;
	return 0;
}

static int Polycore_Particle_set_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->brightnessDeviation = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->perlinPosX = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->perlinPosY = param;
	return 0;
}

static int Polycore_Particle_set_perlinPosZ(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->perlinPosZ = param;
	return 0;
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
	Material * material = (Material *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 4);
	inst->createSceneParticle(particleType, material, particleMesh);
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

static int Polycore_delete_Particle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Particle *inst = (Particle*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Screen * particleParentScreen = (Screen *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	unsigned int numParticles = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 7);
	luaL_checktype(L, 8, LUA_TLIGHTUSERDATA);
	Vector3 gravity = *(Vector3*)lua_topointer(L, 8);
	luaL_checktype(L, 9, LUA_TLIGHTUSERDATA);
	Vector3 deviation = *(Vector3*)lua_topointer(L, 9);
	Mesh * particleMesh;
	if(lua_islightuserdata(L, 10)) {
		particleMesh = (Mesh *)lua_topointer(L, 10);
	} else {
		particleMesh = NULL;
	}
	ScreenMesh * emitter;
	if(lua_islightuserdata(L, 11)) {
		emitter = (ScreenMesh *)lua_topointer(L, 11);
	} else {
		emitter = NULL;
	}
	ScreenParticleEmitter *inst = new ScreenParticleEmitter(imageFile, particleParentScreen, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation, particleMesh, emitter);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenParticleEmitter_getEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getEmitter();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_ScreenParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenParticleEmitter *inst = (ScreenParticleEmitter*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * particleParentScene = (Scene *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	unsigned int numParticles = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 7);
	luaL_checktype(L, 8, LUA_TLIGHTUSERDATA);
	Vector3 gravity = *(Vector3*)lua_topointer(L, 8);
	luaL_checktype(L, 9, LUA_TLIGHTUSERDATA);
	Vector3 deviation = *(Vector3*)lua_topointer(L, 9);
	Mesh * particleMesh;
	if(lua_islightuserdata(L, 10)) {
		particleMesh = (Mesh *)lua_topointer(L, 10);
	} else {
		particleMesh = NULL;
	}
	SceneMesh * emitter;
	if(lua_islightuserdata(L, 11)) {
		emitter = (SceneMesh *)lua_topointer(L, 11);
	} else {
		emitter = NULL;
	}
	SceneParticleEmitter *inst = new SceneParticleEmitter(materialName, particleParentScene, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation, particleMesh, emitter);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneParticleEmitter_getEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getEmitter();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_SceneParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneParticleEmitter *inst = (SceneParticleEmitter*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ParticleEmitter_get_particleSpeedMod(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->particleSpeedMod);
	return 1;
}

static int Polycore_ParticleEmitter_get_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->brightnessDeviation);
	return 1;
}

static int Polycore_ParticleEmitter_get_deviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->deviation);
	return 1;
}

static int Polycore_ParticleEmitter_get_dirVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->dirVector);
	return 1;
}

static int Polycore_ParticleEmitter_get_gravVector(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->gravVector);
	return 1;
}

static int Polycore_ParticleEmitter_get_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->lifespan);
	return 1;
}

static int Polycore_ParticleEmitter_get_rotationFollowsPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->rotationFollowsPath);
	return 1;
}

static int Polycore_ParticleEmitter_get_scaleCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->scaleCurve);
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveR(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->colorCurveR);
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->colorCurveG);
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveB(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->colorCurveB);
	return 1;
}

static int Polycore_ParticleEmitter_get_colorCurveA(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->colorCurveA);
	return 1;
}

static int Polycore_ParticleEmitter_get_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useColorCurves);
	return 1;
}

static int Polycore_ParticleEmitter_get_useScaleCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useScaleCurves);
	return 1;
}

static int Polycore_ParticleEmitter_set_particleSpeedMod(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->particleSpeedMod = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_brightnessDeviation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->brightnessDeviation = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_lifespan(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->lifespan = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_rotationFollowsPath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->rotationFollowsPath = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_useColorCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useColorCurves = param;
	return 0;
}

static int Polycore_ParticleEmitter_set_useScaleCurves(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useScaleCurves = param;
	return 0;
}

static int Polycore_ParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String imageFile = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * particleMesh = (Mesh *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int particleType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int emitterType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number lifespan = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	unsigned int numParticles = lua_tointeger(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 7);
	luaL_checktype(L, 8, LUA_TLIGHTUSERDATA);
	Vector3 gravity = *(Vector3*)lua_topointer(L, 8);
	luaL_checktype(L, 9, LUA_TLIGHTUSERDATA);
	Vector3 deviation = *(Vector3*)lua_topointer(L, 9);
	ParticleEmitter *inst = new ParticleEmitter(imageFile, particleMesh, particleType, emitterType, lifespan, numParticles, direction, gravity, deviation);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ParticleEmitter_createParticles(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	inst->createParticles();
	return 0;
}

static int Polycore_ParticleEmitter_setRotationSpeed(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 2);
	inst->setRotationSpeed(speed);
	return 0;
}

static int Polycore_ParticleEmitter_setParticleBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mode = lua_tointeger(L, 2);
	inst->setParticleBlendingMode(mode);
	return 0;
}

static int Polycore_ParticleEmitter_setDepthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setDepthWrite(val);
	return 0;
}

static int Polycore_ParticleEmitter_setDepthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setDepthTest(val);
	return 0;
}

static int Polycore_ParticleEmitter_setAlphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setAlphaTest(val);
	return 0;
}

static int Polycore_ParticleEmitter_enablePerlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enablePerlin(val);
	return 0;
}

static int Polycore_ParticleEmitter_setPerlinModSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number size = lua_tonumber(L, 2);
	inst->setPerlinModSize(size);
	return 0;
}

static int Polycore_ParticleEmitter_setBillboardMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool mode = lua_toboolean(L, 2);
	inst->setBillboardMode(mode);
	return 0;
}

static int Polycore_ParticleEmitter_enableEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableEmitter(val);
	return 0;
}

static int Polycore_ParticleEmitter_emitterEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->emitterEnabled());
	return 1;
}

static int Polycore_ParticleEmitter_setEmitterRadius(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 rad = *(Vector3*)lua_topointer(L, 2);
	inst->setEmitterRadius(rad);
	return 0;
}

static int Polycore_ParticleEmitter_setAllAtOnce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setAllAtOnce(val);
	return 0;
}

static int Polycore_ParticleEmitter_Trigger(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	inst->Trigger();
	return 0;
}

static int Polycore_ParticleEmitter_resetParticle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Particle * particle = (Particle *)lua_topointer(L, 2);
	inst->resetParticle(particle);
	return 0;
}

static int Polycore_ParticleEmitter_setParticleCount(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int count = lua_tointeger(L, 2);
	inst->setParticleCount(count);
	return 0;
}

static int Polycore_ParticleEmitter_addParticleBody(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Entity * particleBody = (Entity *)lua_topointer(L, 2);
	inst->addParticleBody(particleBody);
	return 0;
}

static int Polycore_ParticleEmitter_getBaseMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	 Matrix4 *retInst = new  Matrix4();
	*retInst = inst->getBaseMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_ParticleEmitter_updateEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	inst->updateEmitter();
	return 0;
}

static int Polycore_delete_ParticleEmitter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ParticleEmitter *inst = (ParticleEmitter*)lua_topointer(L, 1);
	delete inst;
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

static int Polycore_delete_Perlin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Perlin *inst = (Perlin*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Polygon_get_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useVertexNormals);
	return 1;
}

static int Polycore_Polygon_set_useVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useVertexNormals = param;
	return 0;
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
	void *ptrRetVal = (void*)inst->getVertex(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->addVertex(x, y, z);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	Polycode::Rectangle *retInst = new Polycode::Rectangle();
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

static int Polycore_delete_Polygon(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Polygon *inst = (Polycode::Polygon*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Quaternion_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Quaternion_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Quaternion_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycore_Quaternion_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycore_Quaternion_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Quaternion_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Quaternion_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycore_Quaternion_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
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
	const Matrix4 & _mat = *( Matrix4 *)lua_topointer(L, 2);
	inst->setFromMatrix(_mat);
	return 0;
}

static int Polycore_Quaternion_Slerp(lua_State *L) {
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fT = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Quaternion & rkP = *( Quaternion *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	const Quaternion & rkQ = *( Quaternion *)lua_topointer(L, 4);
	bool shortestPath;
	if(lua_isboolean(L, 5)) {
		shortestPath = lua_toboolean(L, 5);
	} else {
		shortestPath = false;
	}
	 Quaternion *retInst = new  Quaternion();
	*retInst = Quaternion::Slerp(fT, rkP, rkQ, shortestPath);
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

static int Polycore_Quaternion_normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->normalize());
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
	*retInst = Quaternion::Squad(fT, rkP, rkA, rkB, rkQ, shortestPath);
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

static int Polycore_delete_Quaternion(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Quaternion *inst = (Quaternion*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_QuaternionCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionCurve *inst = (QuaternionCurve*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Rectangle_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Rectangle_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Rectangle_get_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->w);
	return 1;
}

static int Polycore_Rectangle_get_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->h);
	return 1;
}

static int Polycore_Rectangle_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Rectangle_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Rectangle_set_w(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->w = param;
	return 0;
}

static int Polycore_Rectangle_set_h(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->h = param;
	return 0;
}

static int Polycore_Rectangle(lua_State *L) {
	Polycode::Rectangle *inst = new Polycode::Rectangle();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Rectangle_setRect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
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

static int Polycore_delete_Rectangle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Polycode::Rectangle *inst = (Polycode::Rectangle*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Renderer_get_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->ambientColor);
	return 1;
}

static int Polycore_Renderer_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->clearColor);
	return 1;
}

static int Polycore_Renderer_get_exposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->exposureLevel);
	return 1;
}

static int Polycore_Renderer_get_cameraPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->cameraPosition);
	return 1;
}

static int Polycore_Renderer_set_exposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->exposureLevel = param;
	return 0;
}

static int Polycore_Renderer_Resize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int xRes = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int yRes = lua_tointeger(L, 3);
	inst->Resize(xRes, yRes);
	return 0;
}

static int Polycore_Renderer_BeginRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->BeginRender();
	return 0;
}

static int Polycore_Renderer_EndRender(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->EndRender();
	return 0;
}

static int Polycore_Renderer_createCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * t0 = (Texture *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * t1 = (Texture *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Texture * t2 = (Texture *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Texture * t3 = (Texture *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Texture * t4 = (Texture *)lua_topointer(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Texture * t5 = (Texture *)lua_topointer(L, 7);
	void *ptrRetVal = (void*)inst->createCubemap(t0, t1, t2, t3, t4, t5);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Renderer_createTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int height = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	char * textureData = (char *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool clamp = lua_toboolean(L, 5);
	int type;
	if(lua_isnumber(L, 6)) {
		type = lua_tointeger(L, 6);
	} else {
		type = Image :: IMAGE_RGBA;
	}
	void *ptrRetVal = (void*)inst->createTexture(width, height, textureData, clamp, type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Renderer_createRenderTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * * colorBuffer = (Texture * *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * * depthBuffer = (Texture * *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int width = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int height = lua_tointeger(L, 5);
	inst->createRenderTextures(colorBuffer, depthBuffer, width, height);
	return 0;
}

static int Polycore_Renderer_createFramebufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int width = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int height = lua_tointeger(L, 3);
	void *ptrRetVal = (void*)inst->createFramebufferTexture(width, height);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Renderer_bindFrameBufferTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->bindFrameBufferTexture(texture);
	return 0;
}

static int Polycore_Renderer_unbindFramebuffers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->unbindFramebuffers();
	return 0;
}

static int Polycore_Renderer_renderToTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * targetTexture = (Texture *)lua_topointer(L, 2);
	inst->renderToTexture(targetTexture);
	return 0;
}

static int Polycore_Renderer_renderZBufferToTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * targetTexture = (Texture *)lua_topointer(L, 2);
	inst->renderZBufferToTexture(targetTexture);
	return 0;
}

static int Polycore_Renderer_setViewportSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int w = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int h = lua_tointeger(L, 3);
	Number fov;
	if(lua_isnumber(L, 4)) {
		fov = lua_tonumber(L, 4);
	} else {
		fov = 45.0f;
	}
	inst->setViewportSize(w, h, fov);
	return 0;
}

static int Polycore_Renderer_loadIdentity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->loadIdentity();
	return 0;
}

static int Polycore_Renderer_setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	Number xSize;
	if(lua_isnumber(L, 2)) {
		xSize = lua_tonumber(L, 2);
	} else {
		xSize = 0.0f;
	}
	Number ySize;
	if(lua_isnumber(L, 3)) {
		ySize = lua_tonumber(L, 3);
	} else {
		ySize = 0.0f;
	}
	inst->setOrthoMode(xSize, ySize);
	return 0;
}

static int Polycore_Renderer__setOrthoMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->_setOrthoMode();
	return 0;
}

static int Polycore_Renderer_setPerspectiveMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->setPerspectiveMode();
	return 0;
}

static int Polycore_Renderer_setTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 2);
	inst->setTexture(texture);
	return 0;
}

static int Polycore_Renderer_enableBackfaceCulling(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableBackfaceCulling(val);
	return 0;
}

static int Polycore_Renderer_setClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setClearColor(r, g, b);
	return 0;
}

static int Polycore_Renderer_setAmbientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setAmbientColor(r, g, b);
	return 0;
}

static int Polycore_Renderer_clearScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->clearScreen();
	return 0;
}

static int Polycore_Renderer_translate2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	inst->translate2D(x, y);
	return 0;
}

static int Polycore_Renderer_rotate2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 2);
	inst->rotate2D(angle);
	return 0;
}

static int Polycore_Renderer_scale2D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector2 * scale = (Vector2 *)lua_topointer(L, 2);
	inst->scale2D(scale);
	return 0;
}

static int Polycore_Renderer_setFOV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number fov = lua_tonumber(L, 2);
	inst->setFOV(fov);
	return 0;
}

static int Polycore_Renderer_setVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number a = lua_tonumber(L, 5);
	inst->setVertexColor(r, g, b, a);
	return 0;
}

static int Polycore_Renderer_pushDataArrayForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * mesh = (Mesh *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 3);
	inst->pushDataArrayForMesh(mesh, arrayType);
	return 0;
}

static int Polycore_Renderer_pushRenderDataArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	RenderDataArray * array = (RenderDataArray *)lua_topointer(L, 2);
	inst->pushRenderDataArray(array);
	return 0;
}

static int Polycore_Renderer_createRenderDataArrayForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * mesh = (Mesh *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 3);
	void *ptrRetVal = (void*)inst->createRenderDataArrayForMesh(mesh, arrayType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Renderer_createRenderDataArray(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int arrayType = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->createRenderDataArray(arrayType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Renderer_setRenderArrayData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	RenderDataArray * array = (RenderDataArray *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Number * arrayData = (Number *)lua_topointer(L, 3);
	inst->setRenderArrayData(array, arrayData);
	return 0;
}

static int Polycore_Renderer_drawArrays(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int drawType = lua_tointeger(L, 2);
	inst->drawArrays(drawType);
	return 0;
}

static int Polycore_Renderer_translate3D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 * position = (Vector3 *)lua_topointer(L, 2);
	inst->translate3D(position);
	return 0;
}

static int Polycore_Renderer_scale3D(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 * scale = (Vector3 *)lua_topointer(L, 2);
	inst->scale3D(scale);
	return 0;
}

static int Polycore_Renderer_pushMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->pushMatrix();
	return 0;
}

static int Polycore_Renderer_popMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->popMatrix();
	return 0;
}

static int Polycore_Renderer_setLineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setLineSmooth(val);
	return 0;
}

static int Polycore_Renderer_setLineSize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number lineSize = lua_tonumber(L, 2);
	inst->setLineSize(lineSize);
	return 0;
}

static int Polycore_Renderer_enableLighting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2);
	inst->enableLighting(enable);
	return 0;
}

static int Polycore_Renderer_enableFog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2);
	inst->enableFog(enable);
	return 0;
}

static int Polycore_Renderer_setFogProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int fogMode = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Color color = *(Color*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number density = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number startDepth = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number _endDepth = lua_tonumber(L, 6);
	inst->setFogProperties(fogMode, color, density, startDepth, _endDepth);
	return 0;
}

static int Polycore_Renderer_multModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 m = *(Matrix4*)lua_topointer(L, 2);
	inst->multModelviewMatrix(m);
	return 0;
}

static int Polycore_Renderer_setModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 m = *(Matrix4*)lua_topointer(L, 2);
	inst->setModelviewMatrix(m);
	return 0;
}

static int Polycore_Renderer_setCurrentModelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 m = *(Matrix4*)lua_topointer(L, 2);
	inst->setCurrentModelMatrix(m);
	return 0;
}

static int Polycore_Renderer_getCurrentModelMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getCurrentModelMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_setBlendingMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int bl_endingMode = lua_tointeger(L, 2);
	inst->setBlendingMode(bl_endingMode);
	return 0;
}

static int Polycore_Renderer_applyMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Material * material = (Material *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ShaderBinding * localOptions = (ShaderBinding *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	unsigned int shaderIndex = lua_tointeger(L, 4);
	inst->applyMaterial(material, localOptions, shaderIndex);
	return 0;
}

static int Polycore_Renderer_clearShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->clearShader();
	return 0;
}

static int Polycore_Renderer_setDepthFunction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int depthFunction = lua_tointeger(L, 2);
	inst->setDepthFunction(depthFunction);
	return 0;
}

static int Polycore_Renderer_createVertexBufferForMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Mesh * mesh = (Mesh *)lua_topointer(L, 2);
	inst->createVertexBufferForMesh(mesh);
	return 0;
}

static int Polycore_Renderer_drawVertexBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	VertexBuffer * buffer = (VertexBuffer *)lua_topointer(L, 2);
	inst->drawVertexBuffer(buffer);
	return 0;
}

static int Polycore_Renderer_setRenderMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newR_enderMode = lua_tointeger(L, 2);
	inst->setRenderMode(newR_enderMode);
	return 0;
}

static int Polycore_Renderer_getRenderMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getRenderMode());
	return 1;
}

static int Polycore_Renderer_enableDepthTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableDepthTest(val);
	return 0;
}

static int Polycore_Renderer_enableDepthWrite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableDepthWrite(val);
	return 0;
}

static int Polycore_Renderer_billboardMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->billboardMatrix();
	return 0;
}

static int Polycore_Renderer_billboardMatrixWithScale(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 scale = *(Vector3*)lua_topointer(L, 2);
	inst->billboardMatrixWithScale(scale);
	return 0;
}

static int Polycore_Renderer_setTextureFilteringMode(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int mode = lua_tointeger(L, 2);
	inst->setTextureFilteringMode(mode);
	return 0;
}

static int Polycore_Renderer_setClippingPlanes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number near = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number far = lua_tonumber(L, 3);
	inst->setClippingPlanes(near, far);
	return 0;
}

static int Polycore_Renderer_enableAlphaTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableAlphaTest(val);
	return 0;
}

static int Polycore_Renderer_clearBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool colorBuffer = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool depthBuffer = lua_toboolean(L, 3);
	inst->clearBuffer(colorBuffer, depthBuffer);
	return 0;
}

static int Polycore_Renderer_drawToColorBuffer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->drawToColorBuffer(val);
	return 0;
}

static int Polycore_Renderer_getCameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	Matrix4 *retInst = new Matrix4();
	*retInst = inst->getCameraMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_setCameraMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Matrix4 matrix = *(Matrix4*)lua_topointer(L, 2);
	inst->setCameraMatrix(matrix);
	return 0;
}

static int Polycore_Renderer_setCameraPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 pos = *(Vector3*)lua_topointer(L, 2);
	inst->setCameraPosition(pos);
	return 0;
}

static int Polycore_Renderer_drawScreenQuad(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number qx = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number qy = lua_tonumber(L, 3);
	inst->drawScreenQuad(qx, qy);
	return 0;
}

static int Polycore_Renderer_getXRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getXRes());
	return 1;
}

static int Polycore_Renderer_getYRes(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getYRes());
	return 1;
}

static int Polycore_Renderer_cullFrontFaces(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->cullFrontFaces(val);
	return 0;
}

static int Polycore_Renderer_clearLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->clearLights();
	return 0;
}

static int Polycore_Renderer_addLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int lightImportance = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Vector3 position = *(Vector3*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	int type = lua_tointeger(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Color color = *(Color*)lua_topointer(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Color specularColor = *(Color*)lua_topointer(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number constantAttenuation = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TNUMBER);
	Number linearAttenuation = lua_tonumber(L, 9);
	luaL_checktype(L, 10, LUA_TNUMBER);
	Number quadraticAttenuation = lua_tonumber(L, 10);
	luaL_checktype(L, 11, LUA_TNUMBER);
	Number intensity = lua_tonumber(L, 11);
	luaL_checktype(L, 12, LUA_TNUMBER);
	Number spotlightCutoff = lua_tonumber(L, 12);
	luaL_checktype(L, 13, LUA_TNUMBER);
	Number spotlightExponent = lua_tonumber(L, 13);
	luaL_checktype(L, 14, LUA_TBOOLEAN);
	bool shadowsEnabled = lua_toboolean(L, 14);
	luaL_checktype(L, 15, LUA_TLIGHTUSERDATA);
	Matrix4 * textureMatrix = (Matrix4 *)lua_topointer(L, 15);
	luaL_checktype(L, 16, LUA_TLIGHTUSERDATA);
	Texture * shadowMapTexture = (Texture *)lua_topointer(L, 16);
	inst->addLight(lightImportance, position, direction, type, color, specularColor, constantAttenuation, linearAttenuation, quadraticAttenuation, intensity, spotlightCutoff, spotlightExponent, shadowsEnabled, textureMatrix, shadowMapTexture);
	return 0;
}

static int Polycore_Renderer_setExposureLevel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number level = lua_tonumber(L, 2);
	inst->setExposureLevel(level);
	return 0;
}

static int Polycore_Renderer_rayTriangleIntersect(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 ray_origin = *(Vector3*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Vector3 ray_direction = *(Vector3*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Vector3 vert0 = *(Vector3*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Vector3 vert1 = *(Vector3*)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TLIGHTUSERDATA);
	Vector3 vert2 = *(Vector3*)lua_topointer(L, 6);
	luaL_checktype(L, 7, LUA_TLIGHTUSERDATA);
	Vector3 * hitPoint = (Vector3 *)lua_topointer(L, 7);
	lua_pushboolean(L, inst->rayTriangleIntersect(ray_origin, ray_direction, vert0, vert1, vert2, hitPoint));
	return 1;
}

static int Polycore_Renderer_projectRayFrom2DCoordinate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->projectRayFrom2DCoordinate(x, y);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_enableShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool flag = lua_toboolean(L, 2);
	inst->enableShaders(flag);
	return 0;
}

static int Polycore_Renderer_initOSSpecific(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->initOSSpecific();
	return 0;
}

static int Polycore_Renderer_addShaderModule(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolycodeShaderModule * module = (PolycodeShaderModule *)lua_topointer(L, 2);
	inst->addShaderModule(module);
	return 0;
}

static int Polycore_Renderer_test2DCoordinate(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Polycode::Polygon * poly = (Polycode::Polygon *)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	const Matrix4 & matrix = *( Matrix4 *)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool billboardMode = lua_toboolean(L, 6);
	lua_pushboolean(L, inst->test2DCoordinate(x, y, poly, matrix, billboardMode));
	return 1;
}

static int Polycore_Renderer_getProjectionMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	 Matrix4 *retInst = new  Matrix4();
	*retInst = inst->getProjectionMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_getModelviewMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	 Matrix4 *retInst = new  Matrix4();
	*retInst = inst->getModelviewMatrix();
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_Unproject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->Unproject(x, y);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Renderer_sortLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	inst->sortLights();
	return 0;
}

static int Polycore_Renderer_getNumAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumAreaLights());
	return 1;
}

static int Polycore_Renderer_getNumSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumSpotLights());
	return 1;
}

static int Polycore_Renderer_getNumLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumLights());
	return 1;
}

static int Polycore_delete_Renderer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Renderer *inst = (Renderer*)lua_topointer(L, 1);
	delete inst;
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
	String newName = String(lua_tostring(L, 2));
	inst->setResourceName(newName);
	return 0;
}

static int Polycore_Resource_setResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String path = String(lua_tostring(L, 2));
	inst->setResourcePath(path);
	return 0;
}

static int Polycore_Resource_getResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getResourcePath().c_str());
	return 1;
}

static int Polycore_delete_Resource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Resource *inst = (Resource*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	String dirPath = String(lua_tostring(L, 2));
	bool recursive;
	if(lua_isboolean(L, 3)) {
		recursive = lua_toboolean(L, 3);
	} else {
		recursive = true;
	}
	inst->addDirResource(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_addArchive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String zipPath = String(lua_tostring(L, 2));
	inst->addArchive(zipPath);
	return 0;
}

static int Polycore_ResourceManager_readFile(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	lua_pushboolean(L, inst->readFile(fileName));
	return 1;
}

static int Polycore_ResourceManager_parseTextures(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseTextures(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseMaterials(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseMaterials(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseShaders(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseShaders(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parsePrograms(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parsePrograms(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseCubemaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseCubemaps(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_parseOthers(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String dirPath = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool recursive = lua_toboolean(L, 3);
	inst->parseOthers(dirPath, recursive);
	return 0;
}

static int Polycore_ResourceManager_getResource(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int resourceType = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String resourceName = String(lua_tostring(L, 3));
	void *ptrRetVal = (void*)inst->getResource(resourceType, resourceName);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_ResourceManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ResourceManager *inst = (ResourceManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Scene_get_clearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->clearColor);
	return 1;
}

static int Polycore_Scene_get_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useClearColor);
	return 1;
}

static int Polycore_Scene_get_ambientColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->ambientColor);
	return 1;
}

static int Polycore_Scene_get_fogColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->fogColor);
	return 1;
}

static int Polycore_Scene_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Scene_set_useClearColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useClearColor = param;
	return 0;
}

static int Polycore_Scene_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->enabled = param;
	return 0;
}

static int Polycore_Scene(lua_State *L) {
	Scene *inst = new Scene();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Scene_addEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	inst->addEntity(entity);
	return 0;
}

static int Polycore_Scene_removeEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	inst->removeEntity(entity);
	return 0;
}

static int Polycore_Scene_getDefaultCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getDefaultCamera();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_enableLighting(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2);
	inst->enableLighting(enable);
	return 0;
}

static int Polycore_Scene_enableFog(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enable = lua_toboolean(L, 2);
	inst->enableFog(enable);
	return 0;
}

static int Polycore_Scene_setFogProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int fogMode = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Color color = *(Color*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number density = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number startDepth = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number _endDepth = lua_tonumber(L, 6);
	inst->setFogProperties(fogMode, color, density, startDepth, _endDepth);
	return 0;
}

static int Polycore_Scene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_Scene_setVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->setVirtual(val);
	return 0;
}

static int Polycore_Scene_isVirtual(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isVirtual());
	return 1;
}

static int Polycore_Scene_isEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->isEnabled());
	return 1;
}

static int Polycore_Scene_setEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool enabled = lua_toboolean(L, 2);
	inst->setEnabled(enabled);
	return 0;
}

static int Polycore_Scene_getNumEntities(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumEntities());
	return 1;
}

static int Polycore_Scene_getEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getEntity(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_getEntityAtScreenPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	void *ptrRetVal = (void*)inst->getEntityAtScreenPosition(x, y);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	Camera * targetCamera;
	if(lua_islightuserdata(L, 2)) {
		targetCamera = (Camera *)lua_topointer(L, 2);
	} else {
		targetCamera = NULL;
	}
	inst->Render(targetCamera);
	return 0;
}

static int Polycore_Scene_RenderDepthOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Camera * targetCamera = (Camera *)lua_topointer(L, 2);
	inst->RenderDepthOnly(targetCamera);
	return 0;
}

static int Polycore_Scene_readString(lua_State *L) {
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	OSFILE * inFile = (OSFILE *)lua_topointer(L, 2);
	lua_pushstring(L, Scene::readString(inFile).c_str());
	return 1;
}

static int Polycore_Scene_loadScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadScene(fileName);
	return 0;
}

static int Polycore_Scene_generateLightmaps(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number lightMapRes = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number lightMapQuality = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int numRadPasses = lua_tointeger(L, 4);
	inst->generateLightmaps(lightMapRes, lightMapQuality, numRadPasses);
	return 0;
}

static int Polycore_Scene_addLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneLight * light = (SceneLight *)lua_topointer(L, 2);
	inst->addLight(light);
	return 0;
}

static int Polycore_Scene_getNearestLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 pos = *(Vector3*)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->getNearestLight(pos);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_writeEntityMatrix(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	OSFILE * outFile = (OSFILE *)lua_topointer(L, 3);
	inst->writeEntityMatrix(entity, outFile);
	return 0;
}

static int Polycore_Scene_writeString(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String str = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	OSFILE * outFile = (OSFILE *)lua_topointer(L, 3);
	inst->writeString(str, outFile);
	return 0;
}

static int Polycore_Scene_saveScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->saveScene(fileName);
	return 0;
}

static int Polycore_Scene_getNumStaticGeometry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumStaticGeometry());
	return 1;
}

static int Polycore_Scene_getStaticGeometry(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getStaticGeometry(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_loadCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	bool autoCollide;
	if(lua_isboolean(L, 3)) {
		autoCollide = lua_toboolean(L, 3);
	} else {
		autoCollide = false;
	}
	int type;
	if(lua_isnumber(L, 4)) {
		type = lua_tointeger(L, 4);
	} else {
		type = 0;
	}
	inst->loadCollisionChild(entity, autoCollide, type);
	return 0;
}

static int Polycore_Scene_getNumLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumLights());
	return 1;
}

static int Polycore_Scene_getLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getLight(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Scene_getCustomEntityByType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String type = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getCustomEntityByType(type);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Scene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Scene *inst = (Scene*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneEntity_get_castShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity *inst = (SceneEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->castShadows);
	return 1;
}

static int Polycore_SceneEntity_set_castShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity *inst = (SceneEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->castShadows = param;
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

static int Polycore_delete_SceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity *inst = (SceneEntity*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fontName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TSTRING);
	String text = String(lua_tostring(L, 2));
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
	String newText = String(lua_tostring(L, 2));
	inst->setText(newText);
	return 0;
}

static int Polycore_SceneLabel_getLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getLabel();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneLabel_Render(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	inst->Render();
	return 0;
}

static int Polycore_delete_SceneLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLabel *inst = (SceneLabel*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneLight_get_specularLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->specularLightColor);
	return 1;
}

static int Polycore_SceneLight_get_lightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->lightColor);
	return 1;
}

static int Polycore_SceneLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int type = lua_tointeger(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Scene * parentScene = (Scene *)lua_topointer(L, 2);
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
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneLight_getIntensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getIntensity());
	return 1;
}

static int Polycore_SceneLight_setIntensity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newIntensity = lua_tonumber(L, 2);
	inst->setIntensity(newIntensity);
	return 0;
}

static int Polycore_SceneLight_setAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number constantAttenuation = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number linearAttenuation = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number quadraticAttenuation = lua_tonumber(L, 4);
	inst->setAttenuation(constantAttenuation, linearAttenuation, quadraticAttenuation);
	return 0;
}

static int Polycore_SceneLight_getConstantAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getConstantAttenuation());
	return 1;
}

static int Polycore_SceneLight_getLinearAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getLinearAttenuation());
	return 1;
}

static int Polycore_SceneLight_getQuadraticAttenuation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getQuadraticAttenuation());
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
	void *ptrRetVal = (void*)inst->getZBufferTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneLight_setSpecularLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
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

static int Polycore_SceneLight_setDiffuseLightColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number r = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number g = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number b = lua_tonumber(L, 4);
	inst->setDiffuseLightColor(r, g, b);
	return 0;
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
	Number a;
	if(lua_isnumber(L, 5)) {
		a = lua_tonumber(L, 5);
	} else {
		a = 1.0;
	}
	inst->setLightColor(r, g, b, a);
	return 0;
}

static int Polycore_SceneLight_setSpotlightProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number spotlightCutoff = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spotlightExponent = lua_tonumber(L, 3);
	inst->setSpotlightProperties(spotlightCutoff, spotlightExponent);
	return 0;
}

static int Polycore_SceneLight_getSpotlightCutoff(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getSpotlightCutoff());
	return 1;
}

static int Polycore_SceneLight_getSpotlightExponent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getSpotlightExponent());
	return 1;
}

static int Polycore_SceneLight_enableShadows(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	Number resolution;
	if(lua_isnumber(L, 3)) {
		resolution = lua_tonumber(L, 3);
	} else {
		resolution = 256;
	}
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

static int Polycore_SceneLight_enableDebugDraw(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 2);
	inst->enableDebugDraw(val);
	return 0;
}

static int Polycore_SceneLight_setLightImportance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int newImportance = lua_tointeger(L, 2);
	inst->setLightImportance(newImportance);
	return 0;
}

static int Polycore_SceneLight_getLightImportance(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getLightImportance());
	return 1;
}

static int Polycore_delete_SceneLight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLight *inst = (SceneLight*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_SceneLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneLine *inst = (SceneLine*)lua_topointer(L, 1);
	delete inst;
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

static int Polycore_delete_SceneManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneManager *inst = (SceneManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneMesh_get_lightmapIndex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->lightmapIndex);
	return 1;
}

static int Polycore_SceneMesh_get_showVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->showVertexNormals);
	return 1;
}

static int Polycore_SceneMesh_set_showVertexNormals(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->showVertexNormals = param;
	return 0;
}

static int Polycore_SceneMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
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
	void *ptrRetVal = (void*)inst->getLocalShaderOptions();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneMesh_getMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getMesh();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneMesh_getMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	bool clamp;
	if(lua_isboolean(L, 3)) {
		clamp = lua_toboolean(L, 3);
	} else {
		clamp = true;
	}
	inst->loadTexture(fileName, clamp);
	return 0;
}

static int Polycore_SceneMesh_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
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

static int Polycore_SceneMesh_setMaterialByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String materialName = String(lua_tostring(L, 2));
	inst->setMaterialByName(materialName);
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
	void *ptrRetVal = (void*)inst->getSkeleton();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_SceneMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneMesh *inst = (SceneMesh*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScenePrimitive(lua_State *L) {
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
		v4 = 0.0f;
	}
	Number v5;
	if(lua_isnumber(L, 6)) {
		v5 = lua_tonumber(L, 6);
	} else {
		v5 = 0.0f;
	}
	ScenePrimitive *inst = new ScenePrimitive(type, v1, v2, v3, v4, v5);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_ScenePrimitive(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScenePrimitive *inst = (ScenePrimitive*)lua_topointer(L, 1);
	delete inst;
	return 0;
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
	void *ptrRetVal = (void*)inst->getTargetTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTargetScene();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_SceneRenderTexture_getTargetCamera(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTargetCamera();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_SceneRenderTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneRenderTexture *inst = (SceneRenderTexture*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	SceneSound *inst = new SceneSound(fileName, referenceDistance, maxDistance);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneSound_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneSound *inst = (SceneSound*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_SceneSound_getSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneSound *inst = (SceneSound*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getSound();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_SceneSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneSound *inst = (SceneSound*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SceneSoundListener(lua_State *L) {
	SceneSoundListener *inst = new SceneSoundListener();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SceneSoundListener_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneSoundListener *inst = (SceneSoundListener*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_delete_SceneSoundListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneSoundListener *inst = (SceneSoundListener*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Screen_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Polycore_Screen_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->enabled = param;
	return 0;
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
	void *ptrRetVal = (void*)inst->addChild(newEntity);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Screen_removeChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * entityToRemove = (ScreenEntity *)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->removeChild(entityToRemove);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	void *ptrRetVal = (void*)inst->getEntityAt(x, y);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	Number yCoordinateSize;
	if(lua_isnumber(L, 3)) {
		yCoordinateSize = lua_tonumber(L, 3);
	} else {
		yCoordinateSize = 1.0f;
	}
	inst->setNormalizedCoordinates(newVal, yCoordinateSize);
	return 0;
}

static int Polycore_Screen_setScreenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String shaderName = String(lua_tostring(L, 2));
	inst->setScreenShader(shaderName);
	return 0;
}

static int Polycore_Screen_clearScreenShader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	inst->clearScreenShader();
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
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const ScreenEntity * left = (const ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const ScreenEntity * right = (const ScreenEntity *)lua_topointer(L, 3);
	lua_pushboolean(L, Screen::cmpZindex(left, right));
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
	void *ptrRetVal = (void*)inst->getRootEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Screen_getScreenShaderMaterial(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getScreenShaderMaterial();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Screen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Screen *inst = (Screen*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_ScreenCurve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenCurve *inst = (ScreenCurve*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenEntity_get_hasFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->hasFocus);
	return 1;
}

static int Polycore_ScreenEntity_get_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->blockMouseInput);
	return 1;
}

static int Polycore_ScreenEntity_get_zindex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->zindex);
	return 1;
}

static int Polycore_ScreenEntity_get_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->snapToPixels);
	return 1;
}

static int Polycore_ScreenEntity_set_hasFocus(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->hasFocus = param;
	return 0;
}

static int Polycore_ScreenEntity_set_blockMouseInput(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->blockMouseInput = param;
	return 0;
}

static int Polycore_ScreenEntity_set_zindex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->zindex = param;
	return 0;
}

static int Polycore_ScreenEntity_set_snapToPixels(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->snapToPixels = param;
	return 0;
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
	PolyKEY key = *(PolyKEY*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->_onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity__onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolyKEY key = *(PolyKEY*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->_onKeyUp(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_onKeyDown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolyKEY key = *(PolyKEY*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	wchar_t charCode = *(wchar_t*)lua_topointer(L, 3);
	inst->onKeyDown(key, charCode);
	return 0;
}

static int Polycore_ScreenEntity_onKeyUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PolyKEY key = *(PolyKEY*)lua_topointer(L, 2);
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
	Polycode::Rectangle rect = *(Polycode::Rectangle*)lua_topointer(L, 2);
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

static int Polycore_delete_ScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity *inst = (ScreenEntity*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenEvent(lua_State *L) {
	ScreenEvent *inst = new ScreenEvent();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_ScreenEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEvent *inst = (ScreenEvent*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
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

static int Polycore_delete_ScreenImage(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenImage *inst = (ScreenImage*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenLabel(lua_State *L) {
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
	ScreenLabel *inst = new ScreenLabel(text, size, fontName, amode);
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
	String newText = String(lua_tostring(L, 2));
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
	void *ptrRetVal = (void*)inst->getLabel();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_ScreenLabel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLabel *inst = (ScreenLabel*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_ScreenLine(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenLine *inst = (ScreenLine*)lua_topointer(L, 1);
	delete inst;
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

static int Polycore_delete_ScreenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenManager *inst = (ScreenManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
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
	void *ptrRetVal = (void*)inst->getMesh();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ScreenMesh_getTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTexture();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ScreenMesh_loadTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
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

static int Polycore_delete_ScreenMesh(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenMesh *inst = (ScreenMesh*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenShape_get_strokeEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->strokeEnabled);
	return 1;
}

static int Polycore_ScreenShape_get_strokeColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->strokeColor);
	return 1;
}

static int Polycore_ScreenShape_get_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->lineSmooth);
	return 1;
}

static int Polycore_ScreenShape_set_strokeEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->strokeEnabled = param;
	return 0;
}

static int Polycore_ScreenShape_set_lineSmooth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->lineSmooth = param;
	return 0;
}

static int Polycore_ScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	int shapeType = lua_tointeger(L, 1);
	Number option1;
	if(lua_isnumber(L, 2)) {
		option1 = lua_tonumber(L, 2);
	} else {
		option1 = 0;
	}
	Number option2;
	if(lua_isnumber(L, 3)) {
		option2 = lua_tonumber(L, 3);
	} else {
		option2 = 0;
	}
	Number option3;
	if(lua_isnumber(L, 4)) {
		option3 = lua_tonumber(L, 4);
	} else {
		option3 = 0;
	}
	Number option4;
	if(lua_isnumber(L, 5)) {
		option4 = lua_tonumber(L, 5);
	} else {
		option4 = 0;
	}
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

static int Polycore_delete_ScreenShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenShape *inst = (ScreenShape*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenSoundListener(lua_State *L) {
	ScreenSoundListener *inst = new ScreenSoundListener();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenSoundListener_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSoundListener *inst = (ScreenSoundListener*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_delete_ScreenSoundListener(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSoundListener *inst = (ScreenSoundListener*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	ScreenSound *inst = new ScreenSound(fileName, referenceDistance, maxDistance);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ScreenSound_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSound *inst = (ScreenSound*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Polycore_ScreenSound_getSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSound *inst = (ScreenSound*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getSound();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_ScreenSound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSound *inst = (ScreenSound*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ScreenSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
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
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String frames = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number speed = lua_tonumber(L, 4);
	inst->addAnimation(name, frames, speed);
	return 0;
}

static int Polycore_ScreenSprite_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSprite *inst = (ScreenSprite*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
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

static int Polycore_delete_ScreenSprite(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenSprite *inst = (ScreenSprite*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Shader_get_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->numSpotLights);
	return 1;
}

static int Polycore_Shader_get_numAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->numAreaLights);
	return 1;
}

static int Polycore_Shader_set_numSpotLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->numSpotLights = param;
	return 0;
}

static int Polycore_Shader_set_numAreaLights(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	int param = lua_tointeger(L, 2);
	inst->numAreaLights = param;
	return 0;
}

static int Polycore_Shader_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Polycore_Shader_setName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->setName(name);
	return 0;
}

static int Polycore_Shader_getName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getName().c_str());
	return 1;
}

static int Polycore_Shader_createBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->createBinding();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Shader(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader *inst = (Shader*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_ShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Shader * shader = (Shader *)lua_topointer(L, 1);
	ShaderBinding *inst = new ShaderBinding(shader);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_ShaderBinding_clearTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	inst->clearTexture(name);
	return 0;
}

static int Polycore_ShaderBinding_addTexture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Texture * texture = (Texture *)lua_topointer(L, 3);
	inst->addTexture(name, texture);
	return 0;
}

static int Polycore_ShaderBinding_addParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String type = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String name = String(lua_tostring(L, 3));
	luaL_checktype(L, 4, LUA_TSTRING);
	String value = String(lua_tostring(L, 4));
	inst->addParam(type, name, value);
	return 0;
}

static int Polycore_ShaderBinding_addCubemap(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Cubemap * cubemap = (Cubemap *)lua_topointer(L, 3);
	inst->addCubemap(name, cubemap);
	return 0;
}

static int Polycore_ShaderBinding_getNumLocalParams(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumLocalParams());
	return 1;
}

static int Polycore_ShaderBinding_getLocalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getLocalParam(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ShaderBinding_getLocalParamByName(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getLocalParamByName(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ShaderBinding_addRenderTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	RenderTargetBinding * binding = (RenderTargetBinding *)lua_topointer(L, 2);
	inst->addRenderTargetBinding(binding);
	return 0;
}

static int Polycore_ShaderBinding_getNumRenderTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumRenderTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getRenderTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getRenderTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumInTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumInTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getInTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getInTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ShaderBinding_getNumOutTargetBindings(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getNumOutTargetBindings());
	return 1;
}

static int Polycore_ShaderBinding_getOutTargetBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	unsigned int index = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getOutTargetBinding(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_ShaderBinding_addLocalParam(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	void * ptr = (void *)lua_topointer(L, 3);
	inst->addLocalParam(name, ptr);
	return 0;
}

static int Polycore_delete_ShaderBinding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ShaderBinding *inst = (ShaderBinding*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SkeletonAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String name = String(lua_tostring(L, 1));
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

static int Polycore_delete_SkeletonAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SkeletonAnimation *inst = (SkeletonAnimation*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_BoneTrack_get_LocXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->LocXVec);
	return 1;
}

static int Polycore_BoneTrack_get_LocYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->LocYVec);
	return 1;
}

static int Polycore_BoneTrack_get_LocZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->LocZVec);
	return 1;
}

static int Polycore_BoneTrack_get_ScaleXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->ScaleXVec);
	return 1;
}

static int Polycore_BoneTrack_get_ScaleYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->ScaleYVec);
	return 1;
}

static int Polycore_BoneTrack_get_ScaleZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->ScaleZVec);
	return 1;
}

static int Polycore_BoneTrack_get_boneQuat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->boneQuat);
	return 1;
}

static int Polycore_BoneTrack_get_QuatWVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->QuatWVec);
	return 1;
}

static int Polycore_BoneTrack_get_QuatXVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->QuatXVec);
	return 1;
}

static int Polycore_BoneTrack_get_QuatYVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->QuatYVec);
	return 1;
}

static int Polycore_BoneTrack_get_QuatZVec(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->QuatZVec);
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

static int Polycore_delete_BoneTrack(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BoneTrack *inst = (BoneTrack*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Skeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Skeleton *inst = new Skeleton(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Skeleton_loadSkeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	inst->loadSkeleton(fileName);
	return 0;
}

static int Polycore_Skeleton_playAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String animName = String(lua_tostring(L, 2));
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
	String name = String(lua_tostring(L, 2));
	luaL_checktype(L, 3, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 3));
	inst->addAnimation(name, fileName);
	return 0;
}

static int Polycore_Skeleton_getAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String name = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getAnimation(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	String name = String(lua_tostring(L, 2));
	void *ptrRetVal = (void*)inst->getBoneByName(name);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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
	String labelFont = String(lua_tostring(L, 2));
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
	void *ptrRetVal = (void*)inst->getBone(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Skeleton_getCurrentAnimation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getCurrentAnimation();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_delete_Skeleton(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Skeleton *inst = (Skeleton*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Sound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 1));
	Sound *inst = new Sound(fileName);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_Sound_Play(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	bool loop;
	if(lua_isboolean(L, 2)) {
		loop = lua_toboolean(L, 2);
	} else {
		loop = false;
	}
	inst->Play(loop);
	return 0;
}

static int Polycore_Sound_Stop(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	inst->Stop();
	return 0;
}

static int Polycore_Sound_setVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newVolume = lua_tonumber(L, 2);
	inst->setVolume(newVolume);
	return 0;
}

static int Polycore_Sound_setPitch(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number newPitch = lua_tonumber(L, 2);
	inst->setPitch(newPitch);
	return 0;
}

static int Polycore_Sound_setIsPositional(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool isPositional = lua_toboolean(L, 2);
	inst->setIsPositional(isPositional);
	return 0;
}

static int Polycore_Sound_setSoundPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 position = *(Vector3*)lua_topointer(L, 2);
	inst->setSoundPosition(position);
	return 0;
}

static int Polycore_Sound_setSoundVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 velocity = *(Vector3*)lua_topointer(L, 2);
	inst->setSoundVelocity(velocity);
	return 0;
}

static int Polycore_Sound_setSoundDirection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 2);
	inst->setSoundDirection(direction);
	return 0;
}

static int Polycore_Sound_setPositionalProperties(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number referenceDistance = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number maxDistance = lua_tonumber(L, 3);
	inst->setPositionalProperties(referenceDistance, maxDistance);
	return 0;
}

static int Polycore_Sound_loadWAV(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
	ALuint *retInst = new ALuint();
	*retInst = inst->loadWAV(fileName);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Sound_loadOGG(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String fileName = String(lua_tostring(L, 2));
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
	String operation = String(lua_tostring(L, 2));
	inst->checkALError(operation);
	return 0;
}

static int Polycore_Sound_soundError(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String err = String(lua_tostring(L, 2));
	inst->soundError(err);
	return 0;
}

static int Polycore_Sound_soundCheck(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool result = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TSTRING);
	String err = String(lua_tostring(L, 3));
	inst->soundCheck(result, err);
	return 0;
}

static int Polycore_delete_Sound(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Sound *inst = (Sound*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_SoundManager(lua_State *L) {
	SoundManager *inst = new SoundManager();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_SoundManager_setListenerPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 position = *(Vector3*)lua_topointer(L, 2);
	inst->setListenerPosition(position);
	return 0;
}

static int Polycore_SoundManager_setListenerOrientation(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 orientation = *(Vector3*)lua_topointer(L, 2);
	inst->setListenerOrientation(orientation);
	return 0;
}

static int Polycore_SoundManager_initAL(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	inst->initAL();
	return 0;
}

static int Polycore_SoundManager_setGlobalVolume(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number globalVolume = lua_tonumber(L, 2);
	inst->setGlobalVolume(globalVolume);
	return 0;
}

static int Polycore_delete_SoundManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SoundManager *inst = (SoundManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_String_get_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->contents);
	return 1;
}

static int Polycore_String_get_s_contents(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->s_contents);
	return 1;
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

static int Polycore_String_toUpperCase(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	lua_pushstring(L, inst->toUpperCase().c_str());
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
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	lua_pushstring(L, String::NumberToString(value).c_str());
	return 1;
}

static int Polycore_String_IntToString(lua_State *L) {
	luaL_checktype(L, 2, LUA_TNUMBER);
	int value = lua_tointeger(L, 2);
	lua_pushstring(L, String::IntToString(value).c_str());
	return 1;
}

static int Polycore_String_c_str(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->c_str();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_String_wc_str(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->wc_str();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_String_data(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->data();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_String_getDataWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	void *ptrRetVal = (void*)inst->getDataWithEncoding(encoding);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_String_getDataSizeWithEncoding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int encoding = lua_tointeger(L, 2);
	lua_pushinteger(L, inst->getDataSizeWithEncoding(encoding));
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

static int Polycore_delete_String(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	String *inst = (String*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Texture_get_scrollSpeedX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->scrollSpeedX);
	return 1;
}

static int Polycore_Texture_get_scrollSpeedY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->scrollSpeedY);
	return 1;
}

static int Polycore_Texture_get_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->clamp);
	return 1;
}

static int Polycore_Texture_set_scrollSpeedX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->scrollSpeedX = param;
	return 0;
}

static int Polycore_Texture_set_scrollSpeedY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->scrollSpeedY = param;
	return 0;
}

static int Polycore_Texture_set_clamp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->clamp = param;
	return 0;
}

static int Polycore_Texture_setTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	char * data = (char *)lua_topointer(L, 2);
	inst->setTextureData(data);
	return 0;
}

static int Polycore_Texture_recreateFromImageData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	inst->recreateFromImageData();
	return 0;
}

static int Polycore_Texture_getScrollOffsetX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getScrollOffsetX());
	return 1;
}

static int Polycore_Texture_getScrollOffsetY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->getScrollOffsetY());
	return 1;
}

static int Polycore_Texture_setImageData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Image * data = (Image *)lua_topointer(L, 2);
	inst->setImageData(data);
	return 0;
}

static int Polycore_Texture_updateScroll(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int elapsed = lua_tointeger(L, 2);
	inst->updateScroll(elapsed);
	return 0;
}

static int Polycore_Texture_setResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TSTRING);
	String newPath = String(lua_tostring(L, 2));
	inst->setResourcePath(newPath);
	return 0;
}

static int Polycore_Texture_getResourcePath(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushstring(L, inst->getResourcePath().c_str());
	return 1;
}

static int Polycore_Texture_getTextureData(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getTextureData();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Polycore_Texture_getWidth(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getWidth());
	return 1;
}

static int Polycore_Texture_getHeight(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getHeight());
	return 1;
}

static int Polycore_delete_Texture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Texture *inst = (Texture*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_Timer(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Timer *inst = (Timer*)lua_topointer(L, 1);
	delete inst;
	return 0;
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

static int Polycore_delete_TimerManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TimerManager *inst = (TimerManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Tween_get_repeat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->repeat);
	return 1;
}

static int Polycore_Tween_set_repeat(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->repeat = param;
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
	bool _repeat;
	if(lua_isboolean(L, 6)) {
		_repeat = lua_toboolean(L, 6);
	} else {
		_repeat = false;
	}
	Tween *inst = new Tween(target, easeType, startVal, _endVal, time, _repeat);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
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

static int Polycore_delete_Tween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Tween *inst = (Tween*)lua_topointer(L, 1);
	delete inst;
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
	bool _repeat;
	if(lua_isboolean(L, 5)) {
		_repeat = lua_toboolean(L, 5);
	} else {
		_repeat = false;
	}
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

static int Polycore_delete_BezierPathTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	BezierPathTween *inst = (BezierPathTween*)lua_topointer(L, 1);
	delete inst;
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
	bool _repeat;
	if(lua_isboolean(L, 8)) {
		_repeat = lua_toboolean(L, 8);
	} else {
		_repeat = false;
	}
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

static int Polycore_delete_QuaternionTween(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	QuaternionTween *inst = (QuaternionTween*)lua_topointer(L, 1);
	delete inst;
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

static int Polycore_delete_TweenManager(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	TweenManager *inst = (TweenManager*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Vector2(lua_State *L) {
	Vector2 *inst = new Vector2();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Polycore_delete_Vector2(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector2 *inst = (Vector2*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Vector3_get_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->x);
	return 1;
}

static int Polycore_Vector3_get_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->y);
	return 1;
}

static int Polycore_Vector3_get_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->z);
	return 1;
}

static int Polycore_Vector3_set_x(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->x = param;
	return 0;
}

static int Polycore_Vector3_set_y(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->y = param;
	return 0;
}

static int Polycore_Vector3_set_z(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->z = param;
	return 0;
}

static int Polycore_Vector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number x = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number y = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number z = lua_tonumber(L, 3);
	Vector3 *inst = new Vector3(x, y, z);
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
	const Vector3 & vec2 = *( Vector3 *)lua_topointer(L, 2);
	lua_pushnumber(L, inst->distance(vec2));
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
	const Vector3 & vec2 = *( Vector3 *)lua_topointer(L, 2);
	 Vector3 *retInst = new  Vector3();
	*retInst = inst->crossProduct(vec2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Polycore_Vector3_Normalize(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	inst->Normalize();
	return 0;
}

static int Polycore_delete_Vector3(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vector3 *inst = (Vector3*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Polycore_Vertex_get_restNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->restNormal);
	return 1;
}

static int Polycore_Vertex_get_restPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->restPosition);
	return 1;
}

static int Polycore_Vertex_get_normal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->normal);
	return 1;
}

static int Polycore_Vertex_get_vertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->vertexColor);
	return 1;
}

static int Polycore_Vertex_get_useVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->useVertexColor);
	return 1;
}

static int Polycore_Vertex_set_useVertexColor(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->useVertexColor = param;
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
	void *ptrRetVal = (void*)inst->getBoneAssignment(index);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
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

static int Polycore_delete_Vertex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	Vertex *inst = (Vertex*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

}