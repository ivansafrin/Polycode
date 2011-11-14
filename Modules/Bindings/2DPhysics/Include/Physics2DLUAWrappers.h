#pragma once

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
} // extern "C" 

#include "Polycode2DPhysics.h"
#include "PolyPhysicsScreen.h"
#include "PolyPhysicsScreenEntity.h"

namespace Polycode {

static int Physics2D_PhysicsScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TNUMBER);
	Number worldScale = lua_tonumber(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number freq = lua_tonumber(L, 2);
	PhysicsScreen *inst = new PhysicsScreen(worldScale, freq);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics2D_PhysicsScreen_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics2D_PhysicsScreen_addPhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool isStatic = lua_toboolean(L, 4);
	Number friction;
	if(lua_isnumber(L, 5)) {
		friction = lua_tonumber(L, 5);
	} else {
		friction = 0.1;
	}
	Number density;
	if(lua_isnumber(L, 6)) {
		density = lua_tonumber(L, 6);
	} else {
		density = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 7)) {
		restitution = lua_tonumber(L, 7);
	} else {
		restitution = 0;
	}
	bool isSensor;
	if(lua_isboolean(L, 8)) {
		isSensor = lua_toboolean(L, 8);
	} else {
		isSensor = false;
	}
	bool fixedRotation;
	if(lua_isboolean(L, 9)) {
		fixedRotation = lua_toboolean(L, 9);
	} else {
		fixedRotation = false;
	}
	void *ptrRetVal = (void*)inst->addPhysicsChild(newEntity, entType, isStatic, friction, density, restitution, isSensor, fixedRotation);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_removePhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity* entityToRemove = (PhysicsScreenEntity*)lua_topointer(L, 2);
	inst->removePhysicsChild(entityToRemove);
	return 0;
}

static int Physics2D_PhysicsScreen_addCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* newEntity = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	void *ptrRetVal = (void*)inst->addCollisionChild(newEntity, entType);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_destroyJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PhysicsJoint* joint = (PhysicsJoint*)lua_topointer(L, 2);
	inst->destroyJoint(joint);
	return 0;
}

static int Physics2D_PhysicsScreen_createDistanceJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool collideConnected = lua_toboolean(L, 4);
	void *ptrRetVal = (void*)inst->createDistanceJoint(ent1, ent2, collideConnected);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_createPrismaticJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TLIGHTUSERDATA);
	Vector2 worldAxis = *(Vector2*)lua_topointer(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 6);
	bool collideConnected;
	if(lua_isboolean(L, 7)) {
		collideConnected = lua_toboolean(L, 7);
	} else {
		collideConnected = false;
	}
	Number lowerTranslation;
	if(lua_isnumber(L, 8)) {
		lowerTranslation = lua_tonumber(L, 8);
	} else {
		lowerTranslation = 0;
	}
	Number upperTranslation;
	if(lua_isnumber(L, 9)) {
		upperTranslation = lua_tonumber(L, 9);
	} else {
		upperTranslation = 0;
	}
	bool enableLimit;
	if(lua_isboolean(L, 10)) {
		enableLimit = lua_toboolean(L, 10);
	} else {
		enableLimit = false;
	}
	Number motorSpeed;
	if(lua_isnumber(L, 11)) {
		motorSpeed = lua_tonumber(L, 11);
	} else {
		motorSpeed = 0;
	}
	Number motorForce;
	if(lua_isnumber(L, 12)) {
		motorForce = lua_tonumber(L, 12);
	} else {
		motorForce = 0;
	}
	bool motorEnabled;
	if(lua_isboolean(L, 13)) {
		motorEnabled = lua_toboolean(L, 13);
	} else {
		motorEnabled = false;
	}
	void *ptrRetVal = (void*)inst->createPrismaticJoint(ent1, ent2, worldAxis, ax, ay, collideConnected, lowerTranslation, upperTranslation, enableLimit, motorSpeed, motorForce, motorEnabled);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_createRevoluteJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent1 = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent2 = (ScreenEntity*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 5);
	bool collideConnected;
	if(lua_isboolean(L, 6)) {
		collideConnected = lua_toboolean(L, 6);
	} else {
		collideConnected = false;
	}
	bool enableLimit;
	if(lua_isboolean(L, 7)) {
		enableLimit = lua_toboolean(L, 7);
	} else {
		enableLimit = false;
	}
	Number lowerLimit;
	if(lua_isnumber(L, 8)) {
		lowerLimit = lua_tonumber(L, 8);
	} else {
		lowerLimit = 0;
	}
	Number upperLimit;
	if(lua_isnumber(L, 9)) {
		upperLimit = lua_tonumber(L, 9);
	} else {
		upperLimit = 0;
	}
	bool motorEnabled;
	if(lua_isboolean(L, 10)) {
		motorEnabled = lua_toboolean(L, 10);
	} else {
		motorEnabled = false;
	}
	Number motorSpeed;
	if(lua_isnumber(L, 11)) {
		motorSpeed = lua_tonumber(L, 11);
	} else {
		motorSpeed = 0;
	}
	Number maxTorque;
	if(lua_isnumber(L, 12)) {
		maxTorque = lua_tonumber(L, 12);
	} else {
		maxTorque = 0;
	}
	void *ptrRetVal = (void*)inst->createRevoluteJoint(ent1, ent2, ax, ay, collideConnected, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_applyForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->applyForce(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_applyImpulse(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->applyImpulse(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setGravity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector2 newGravity = *(Vector2*)lua_topointer(L, 2);
	inst->setGravity(newGravity);
	return 0;
}

static int Physics2D_PhysicsScreen_setTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	Vector2 pos = *(Vector2*)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 4);
	inst->setTransform(ent, pos, angle);
	return 0;
}

static int Physics2D_PhysicsScreen_getPhysicsEntityByShape(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Shape* shape = (b2Shape*)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->getPhysicsEntityByShape(shape);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_getPhysicsEntityByFixture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Fixture* fixture = (b2Fixture*)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->getPhysicsEntityByFixture(fixture);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 4);
	inst->setVelocity(ent, fx, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setVelocityX(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	inst->setVelocityX(ent, fx);
	return 0;
}

static int Physics2D_PhysicsScreen_setVelocityY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 3);
	inst->setVelocityY(ent, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setSpin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spin = lua_tonumber(L, 3);
	inst->setSpin(ent, spin);
	return 0;
}

static int Physics2D_PhysicsScreen_getVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getVelocity(ent);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics2D_PhysicsScreen_BeginContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Contact* contact = (b2Contact*)lua_topointer(L, 2);
	inst->BeginContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_EndContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Contact* contact = (b2Contact*)lua_topointer(L, 2);
	inst->EndContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_PostSolve(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Contact* contact = (b2Contact*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	b2ContactImpulse* impulse = (b2ContactImpulse*)lua_topointer(L, 3);
	inst->PostSolve(contact, impulse);
	return 0;
}

static int Physics2D_PhysicsScreen_wakeUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	inst->wakeUp(ent);
	return 0;
}

static int Physics2D_PhysicsScreen_getEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	void *ptrRetVal = (void*)inst->getEntityAtPosition(x, y);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_testEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number x = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number y = lua_tonumber(L, 4);
	lua_pushboolean(L, inst->testEntityAtPosition(ent, x, y));
	return 1;
}

static int Physics2D_PhysicsScreen_Shutdown(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	inst->Shutdown();
	return 0;
}

static int Physics2D_PhysicsScreen_getPhysicsByScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity* ent = (ScreenEntity*)lua_topointer(L, 2);
	void *ptrRetVal = (void*)inst->getPhysicsByScreenEntity(ent);
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreen_destroyMouseJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2MouseJoint* mJoint = (b2MouseJoint*)lua_topointer(L, 2);
	inst->destroyMouseJoint(mJoint);
	return 0;
}

static int Physics2D_delete_PhysicsScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_get_localCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->localCollisionNormal);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_worldCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->worldCollisionNormal);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_localCollisionPoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, &inst->localCollisionPoint);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_impactStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->impactStrength);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_get_frictionStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	lua_pushnumber(L, inst->frictionStrength);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_set_impactStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->impactStrength = param;
	return 0;
}

static int Physics2D_PhysicsScreenEvent_set_frictionStrength(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	Number param = lua_tonumber(L, 2);
	inst->frictionStrength = param;
	return 0;
}

static int Physics2D_PhysicsScreenEvent(lua_State *L) {
	PhysicsScreenEvent *inst = new PhysicsScreenEvent();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics2D_PhysicsScreenEvent_getFirstEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getFirstEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreenEvent_getSecondEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getSecondEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_delete_PhysicsScreenEvent(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEvent *inst = (PhysicsScreenEvent*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics2D_PhysicsJoint(lua_State *L) {
	PhysicsJoint *inst = new PhysicsJoint();
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics2D_delete_PhysicsJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsJoint *inst = (PhysicsJoint*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

static int Physics2D_PhysicsScreenEntity_get_collisionOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	lua_pushboolean(L, inst->collisionOnly);
	return 1;
}

static int Physics2D_PhysicsScreenEntity_set_collisionOnly(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	bool param = lua_toboolean(L, 2);
	inst->collisionOnly = param;
	return 0;
}

static int Physics2D_PhysicsScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	ScreenEntity* entity = (ScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2World* world = (b2World*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number worldScale = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int entType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TBOOLEAN);
	bool isStatic = lua_toboolean(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number density = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number restitution = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TBOOLEAN);
	bool isSensor = lua_toboolean(L, 9);
	luaL_checktype(L, 10, LUA_TBOOLEAN);
	bool fixedRotation = lua_toboolean(L, 10);
	PhysicsScreenEntity *inst = new PhysicsScreenEntity(entity, world, worldScale, entType, isStatic, friction, density, restitution, isSensor, fixedRotation);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics2D_PhysicsScreenEntity_getScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	void *ptrRetVal = (void*)inst->getScreenEntity();
	if(ptrRetVal == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, ptrRetVal);
	}
	return 1;
}

static int Physics2D_PhysicsScreenEntity_applyTorque(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number torque = lua_tonumber(L, 2);
	inst->applyTorque(torque);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_applyForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector2 force = *(Vector2*)lua_topointer(L, 2);
	inst->applyForce(force);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_setTransform(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	Vector2 pos = *(Vector2*)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number angle = lua_tonumber(L, 3);
	inst->setTransform(pos, angle);
	return 0;
}

static int Physics2D_PhysicsScreenEntity_Update(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	inst->Update();
	return 0;
}

static int Physics2D_delete_PhysicsScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	delete inst;
	return 0;
}

} // namespace Polycode
