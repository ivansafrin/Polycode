#pragma once

#include <Polycode3DPhysics.h>

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static int Physics3D_CollisionScene(lua_State *L) {
	CollisionScene *inst = new CollisionScene();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_CollisionScene_initCollisionScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	inst->initCollisionScene();
	return 0;
}

static int Physics3D_CollisionScene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_CollisionScene_enableCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool val = lua_toboolean(L, 3);
	inst->enableCollision(entity, val);
	return 0;
}

static int Physics3D_CollisionScene_getCollisionEntityByObject(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	btCollisionObject * collisionObject = (btCollisionObject *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getCollisionEntityByObject(collisionObject));
	return 1;
}

static int Physics3D_CollisionScene_getFirstEntityInRay(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	const Vector3 & origin = *( Vector3 *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	const Vector3 & dest = *( Vector3 *)lua_topointer(L, 3);
	RayTestResult *retInst = new RayTestResult();
	*retInst = inst->getFirstEntityInRay(origin, dest);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_getCollisionByScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * ent = (SceneEntity *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getCollisionByScreenEntity(ent));
	return 1;
}

static int Physics3D_CollisionScene_testCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * ent1 = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	SceneEntity * ent2 = (SceneEntity *)lua_topointer(L, 3);
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollision(ent1, ent2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_testCollisionOnCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt1 = (CollisionSceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt2 = (CollisionSceneEntity *)lua_topointer(L, 3);
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollisionOnCollisionChild(cEnt1, cEnt2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_testCollisionOnCollisionChild_Convex(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt1 = (CollisionSceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt2 = (CollisionSceneEntity *)lua_topointer(L, 3);
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollisionOnCollisionChild_Convex(cEnt1, cEnt2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_testCollisionOnCollisionChild_RayTest(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt1 = (CollisionSceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt2 = (CollisionSceneEntity *)lua_topointer(L, 3);
	CollisionResult *retInst = new CollisionResult();
	*retInst = inst->testCollisionOnCollisionChild_RayTest(cEnt1, cEnt2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_getCollisionNormalFromCollisionEnts(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt1 = (CollisionSceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * cEnt2 = (CollisionSceneEntity *)lua_topointer(L, 3);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCollisionNormalFromCollisionEnts(cEnt1, cEnt2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_getCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * ent1 = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	SceneEntity * ent2 = (SceneEntity *)lua_topointer(L, 3);
	Vector3 *retInst = new Vector3();
	*retInst = inst->getCollisionNormal(ent1, ent2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics3D_CollisionScene_applyVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number x = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number y = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number z = lua_tonumber(L, 5);
	inst->applyVelocity(entity, x, y, z);
	return 0;
}

static int Physics3D_CollisionScene_loadCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
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

static int Physics3D_CollisionScene_enableGravity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	inst->enableGravity(entity);
	return 0;
}

static int Physics3D_CollisionScene_stopTrackingCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	inst->stopTrackingCollision(entity);
	return 0;
}

static int Physics3D_CollisionScene_addCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
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
	int group;
	if(lua_isnumber(L, 5)) {
		group = lua_tointeger(L, 5);
	} else {
		group = 0;
	}
	lua_pushlightuserdata(L, (void*)inst->addCollisionChild(newEntity, autoCollide, type, group));
	return 1;
}

static int Physics3D_CollisionScene_trackCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TBOOLEAN);
	bool autoCollide = lua_toboolean(L, 3);
	int type;
	if(lua_isnumber(L, 4)) {
		type = lua_tointeger(L, 4);
	} else {
		type = 0;
	}
	int group;
	if(lua_isnumber(L, 5)) {
		group = lua_tointeger(L, 5);
	} else {
		group = 0;
	}
	lua_pushlightuserdata(L, (void*)inst->trackCollision(newEntity, autoCollide, type, group));
	return 1;
}

static int Physics3D_CollisionScene_adjustForCollision(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity * collisionEntity = (CollisionSceneEntity *)lua_topointer(L, 2);
	inst->adjustForCollision(collisionEntity);
	return 0;
}

static int Physics3D_delete_CollisionScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionScene *inst = (CollisionScene*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics3D_CollisionSceneEntity_get_gravityEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->gravityEnabled);
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_autoCollide(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->autoCollide);
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_gravityStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->gravityStrength);
	return 1;
}

static int Physics3D_CollisionSceneEntity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Physics3D_CollisionSceneEntity_set_gravityEnabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->gravityEnabled = param;
	return 0;
}

static int Physics3D_CollisionSceneEntity_set_autoCollide(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->autoCollide = param;
	return 0;
}

static int Physics3D_CollisionSceneEntity_set_gravityStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->gravityStrength = param;
	return 0;
}

static int Physics3D_CollisionSceneEntity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->enabled = param;
	return 0;
}

static int Physics3D_CollisionSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TBOOLEAN);
	bool autoCollide = lua_toboolean(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int type = lua_tointeger(L, 3);
	CollisionSceneEntity *inst = new CollisionSceneEntity(entity, autoCollide, type);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_CollisionSceneEntity_getSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getSceneEntity());
	return 1;
}

static int Physics3D_CollisionSceneEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_CollisionSceneEntity_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Physics3D_CollisionSceneEntity_getConvexShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getConvexShape());
	return 1;
}

static int Physics3D_CollisionSceneEntity_createCollisionShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int type = lua_tointeger(L, 3);
	lua_pushlightuserdata(L, (void*)inst->createCollisionShape(entity, type));
	return 1;
}

static int Physics3D_delete_CollisionSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	CollisionSceneEntity *inst = (CollisionSceneEntity*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics3D_PhysicsScene(lua_State *L) {
	PhysicsScene *inst = new PhysicsScene();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_PhysicsScene_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_PhysicsScene_addPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	Number mass;
	if(lua_isnumber(L, 4)) {
		mass = lua_tonumber(L, 4);
	} else {
		mass = 0.0f;
	}
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 6)) {
		restitution = lua_tonumber(L, 6);
	} else {
		restitution = 0;
	}
	int group;
	if(lua_isnumber(L, 7)) {
		group = lua_tointeger(L, 7);
	} else {
		group = 1;
	}
	lua_pushlightuserdata(L, (void*)inst->addPhysicsChild(newEntity, type, mass, friction, restitution, group));
	return 1;
}

static int Physics3D_PhysicsScene_trackPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
	int type;
	if(lua_isnumber(L, 3)) {
		type = lua_tointeger(L, 3);
	} else {
		type = 0;
	}
	Number mass;
	if(lua_isnumber(L, 4)) {
		mass = lua_tonumber(L, 4);
	} else {
		mass = 0.0f;
	}
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 6)) {
		restitution = lua_tonumber(L, 6);
	} else {
		restitution = 0;
	}
	int group;
	if(lua_isnumber(L, 7)) {
		group = lua_tointeger(L, 7);
	} else {
		group = 1;
	}
	lua_pushlightuserdata(L, (void*)inst->trackPhysicsChild(newEntity, type, mass, friction, restitution, group));
	return 1;
}

static int Physics3D_PhysicsScene_addCharacterChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number stepSize = lua_tonumber(L, 5);
	int group;
	if(lua_isnumber(L, 6)) {
		group = lua_tointeger(L, 6);
	} else {
		group = 1;
	}
	lua_pushlightuserdata(L, (void*)inst->addCharacterChild(newEntity, mass, friction, stepSize, group));
	return 1;
}

static int Physics3D_PhysicsScene_addVehicleChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * newEntity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	int group;
	if(lua_isnumber(L, 5)) {
		group = lua_tointeger(L, 5);
	} else {
		group = 1;
	}
	lua_pushlightuserdata(L, (void*)inst->addVehicleChild(newEntity, mass, friction, group));
	return 1;
}

static int Physics3D_delete_PhysicsScene(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScene *inst = (PhysicsScene*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics3D_PhysicsSceneEntity_get_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->enabled);
	return 1;
}

static int Physics3D_PhysicsSceneEntity_set_enabled(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->enabled = param;
	return 0;
}

static int Physics3D_PhysicsSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	int type = lua_tointeger(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number restitution = lua_tonumber(L, 5);
	PhysicsSceneEntity *inst = new PhysicsSceneEntity(entity, type, mass, friction, restitution);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_PhysicsSceneEntity_getSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getSceneEntity());
	return 1;
}

static int Physics3D_PhysicsSceneEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_PhysicsSceneEntity_setFriction(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 2);
	inst->setFriction(friction);
	return 0;
}

static int Physics3D_PhysicsSceneEntity_getType(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	lua_pushinteger(L, inst->getType());
	return 1;
}

static int Physics3D_delete_PhysicsSceneEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsSceneEntity *inst = (PhysicsSceneEntity*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics3D_PhysicsCharacter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number stepSize = lua_tonumber(L, 4);
	PhysicsCharacter *inst = new PhysicsCharacter(entity, mass, friction, stepSize);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_PhysicsCharacter_setWalkDirection(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 2);
	inst->setWalkDirection(direction);
	return 0;
}

static int Physics3D_PhysicsCharacter_jump(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*)lua_topointer(L, 1);
	inst->jump();
	return 0;
}

static int Physics3D_PhysicsCharacter_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_delete_PhysicsCharacter(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsCharacter *inst = (PhysicsCharacter*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics3D_PhysicsVehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number mass = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	btDefaultVehicleRaycaster * rayCaster = (btDefaultVehicleRaycaster *)lua_topointer(L, 4);
	PhysicsVehicle *inst = new PhysicsVehicle(entity, mass, friction, rayCaster);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics3D_PhysicsVehicle_addWheel(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	SceneEntity * entity = (SceneEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Vector3 connection = *(Vector3*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Vector3 direction = *(Vector3*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TLIGHTUSERDATA);
	Vector3 axle = *(Vector3*)lua_topointer(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number suspentionRestLength = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number wheelRadius = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TBOOLEAN);
	bool isFrontWheel = lua_toboolean(L, 8);
	Number suspensionStiffness;
	if(lua_isnumber(L, 9)) {
		suspensionStiffness = lua_tonumber(L, 9);
	} else {
		suspensionStiffness = 20.0f;
	}
	Number suspensionDamping;
	if(lua_isnumber(L, 10)) {
		suspensionDamping = lua_tonumber(L, 10);
	} else {
		suspensionDamping = 1.0f;
	}
	Number suspensionCompression;
	if(lua_isnumber(L, 11)) {
		suspensionCompression = lua_tonumber(L, 11);
	} else {
		suspensionCompression = 4.0f;
	}
	Number wheelFriction;
	if(lua_isnumber(L, 12)) {
		wheelFriction = lua_tonumber(L, 12);
	} else {
		wheelFriction = 10000.0f;
	}
	Number rollInfluence;
	if(lua_isnumber(L, 13)) {
		rollInfluence = lua_tonumber(L, 13);
	} else {
		rollInfluence = 0.05f;
	}
	inst->addWheel(entity, connection, direction, axle, suspentionRestLength, wheelRadius, isFrontWheel, suspensionStiffness, suspensionDamping, suspensionCompression, wheelFriction, rollInfluence);
	return 0;
}

static int Physics3D_PhysicsVehicle_applyEngineForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number force = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int wheelIndex = lua_tointeger(L, 3);
	inst->applyEngineForce(force, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_setSteeringValue(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int wheelIndex = lua_tointeger(L, 3);
	inst->setSteeringValue(value, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_setBrake(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number value = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	unsigned int wheelIndex = lua_tointeger(L, 3);
	inst->setBrake(value, wheelIndex);
	return 0;
}

static int Physics3D_PhysicsVehicle_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics3D_delete_PhysicsVehicle(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsVehicle *inst = (PhysicsVehicle*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

}