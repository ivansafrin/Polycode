#pragma once

#include <Polycode2DPhysics.h>

extern "C" {

#include <stdio.h>
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

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
	ScreenEntity * newEntity = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	Number friction;
	if(lua_isnumber(L, 4)) {
		friction = lua_tonumber(L, 4);
	} else {
		friction = 0.1;
	}
	Number density;
	if(lua_isnumber(L, 5)) {
		density = lua_tonumber(L, 5);
	} else {
		density = 1;
	}
	Number restitution;
	if(lua_isnumber(L, 6)) {
		restitution = lua_tonumber(L, 6);
	} else {
		restitution = 0;
	}
	bool isSensor;
	if(lua_isboolean(L, 7)) {
		isSensor = lua_toboolean(L, 7);
	} else {
		isSensor = false;
	}
	bool fixedRotation;
	if(lua_isboolean(L, 8)) {
		fixedRotation = lua_toboolean(L, 8);
	} else {
		fixedRotation = false;
	}
	lua_pushlightuserdata(L, (void*)inst->addPhysicsChild(newEntity, entType, friction, density, restitution, isSensor, fixedRotation));
	return 1;
}

static int Physics2D_PhysicsScreen_removePhysicsChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity * entityToRemove = (PhysicsScreenEntity *)lua_topointer(L, 2);
	inst->removePhysicsChild(entityToRemove);
	return 0;
}

static int Physics2D_PhysicsScreen_addCollisionChild(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * newEntity = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	int entType = lua_tointeger(L, 3);
	lua_pushlightuserdata(L, (void*)inst->addCollisionChild(newEntity, entType));
	return 1;
}

static int Physics2D_PhysicsScreen_destroyJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	PhysicsJoint * joint = (PhysicsJoint *)lua_topointer(L, 2);
	inst->destroyJoint(joint);
	return 0;
}

static int Physics2D_PhysicsScreen_createDistanceJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent1 = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent2 = (ScreenEntity *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool collideConnected = lua_toboolean(L, 4);
	inst->createDistanceJoint(ent1, ent2, collideConnected);
	return 0;
}

static int Physics2D_PhysicsScreen_createPrismaticJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent1 = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent2 = (ScreenEntity *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TBOOLEAN);
	bool collideConnected = lua_toboolean(L, 4);
	inst->createPrismaticJoint(ent1, ent2, collideConnected);
	return 0;
}

static int Physics2D_PhysicsScreen_createRevoluteJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent1 = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent2 = (ScreenEntity *)lua_topointer(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	Number ax = lua_tonumber(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number ay = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TBOOLEAN);
	bool enableLimit = lua_toboolean(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number lowerLimit = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TNUMBER);
	Number upperLimit = lua_tonumber(L, 8);
	luaL_checktype(L, 9, LUA_TBOOLEAN);
	bool motorEnabled = lua_toboolean(L, 9);
	luaL_checktype(L, 10, LUA_TNUMBER);
	Number motorSpeed = lua_tonumber(L, 10);
	luaL_checktype(L, 11, LUA_TNUMBER);
	Number maxTorque = lua_tonumber(L, 11);
	lua_pushlightuserdata(L, (void*)inst->createRevoluteJoint(ent1, ent2, ax, ay, enableLimit, lowerLimit, upperLimit, motorEnabled, motorSpeed, maxTorque));
	return 1;
}

static int Physics2D_PhysicsScreen_applyForce(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
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
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
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
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
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
	b2Shape * shape = (b2Shape *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getPhysicsEntityByShape(shape));
	return 1;
}

static int Physics2D_PhysicsScreen_getPhysicsEntityByFixture(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Fixture * fixture = (b2Fixture *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getPhysicsEntityByFixture(fixture));
	return 1;
}

static int Physics2D_PhysicsScreen_setVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
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
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fx = lua_tonumber(L, 3);
	inst->setVelocityX(ent, fx);
	return 0;
}

static int Physics2D_PhysicsScreen_setVelocityY(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number fy = lua_tonumber(L, 3);
	inst->setVelocityY(ent, fy);
	return 0;
}

static int Physics2D_PhysicsScreen_setSpin(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number spin = lua_tonumber(L, 3);
	inst->setSpin(ent, spin);
	return 0;
}

static int Physics2D_PhysicsScreen_getVelocity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getVelocity(ent);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics2D_PhysicsScreen_BeginContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Contact * contact = (b2Contact *)lua_topointer(L, 2);
	inst->BeginContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_EndContact(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2Contact * contact = (b2Contact *)lua_topointer(L, 2);
	inst->EndContact(contact);
	return 0;
}

static int Physics2D_PhysicsScreen_wakeUp(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	inst->wakeUp(ent);
	return 0;
}

static int Physics2D_PhysicsScreen_getEntityCollisionNormal(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent1 = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent2 = (ScreenEntity *)lua_topointer(L, 3);
	Vector2 *retInst = new Vector2();
	*retInst = inst->getEntityCollisionNormal(ent1, ent2);
	lua_pushlightuserdata(L, retInst);
	return 1;
}

static int Physics2D_PhysicsScreen_areEntitiesColliding(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent1 = (ScreenEntity *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent2 = (ScreenEntity *)lua_topointer(L, 3);
	lua_pushboolean(L, inst->areEntitiesColliding(ent1, ent2));
	return 1;
}

static int Physics2D_PhysicsScreen_getEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TNUMBER);
	Number x = lua_tonumber(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number y = lua_tonumber(L, 3);
	lua_pushlightuserdata(L, (void*)inst->getEntityAtPosition(x, y));
	return 1;
}

static int Physics2D_PhysicsScreen_testEntityAtPosition(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
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
	ScreenEntity * ent = (ScreenEntity *)lua_topointer(L, 2);
	lua_pushlightuserdata(L, (void*)inst->getPhysicsByScreenEntity(ent));
	return 1;
}

static int Physics2D_PhysicsScreen_destroyMouseJoint(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2MouseJoint * mJoint = (b2MouseJoint *)lua_topointer(L, 2);
	inst->destroyMouseJoint(mJoint);
	return 0;
}

static int Physics2D_delete_PhysicsScreen(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreen *inst = (PhysicsScreen*)lua_topointer(L, 1);
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
	ScreenEntity * entity = (ScreenEntity *)lua_topointer(L, 1);
	luaL_checktype(L, 2, LUA_TLIGHTUSERDATA);
	b2World * world = (b2World *)lua_topointer(L, 2);
	luaL_checktype(L, 3, LUA_TNUMBER);
	Number worldScale = lua_tonumber(L, 3);
	luaL_checktype(L, 4, LUA_TNUMBER);
	int entType = lua_tointeger(L, 4);
	luaL_checktype(L, 5, LUA_TNUMBER);
	Number friction = lua_tonumber(L, 5);
	luaL_checktype(L, 6, LUA_TNUMBER);
	Number density = lua_tonumber(L, 6);
	luaL_checktype(L, 7, LUA_TNUMBER);
	Number restitution = lua_tonumber(L, 7);
	luaL_checktype(L, 8, LUA_TBOOLEAN);
	bool isSensor = lua_toboolean(L, 8);
	luaL_checktype(L, 9, LUA_TBOOLEAN);
	bool fixedRotation = lua_toboolean(L, 9);
	PhysicsScreenEntity *inst = new PhysicsScreenEntity(entity, world, worldScale, entType, friction, density, restitution, isSensor, fixedRotation);
	lua_pushlightuserdata(L, (void*)inst);
	return 1;
}

static int Physics2D_PhysicsScreenEntity_getScreenEntity(lua_State *L) {
	luaL_checktype(L, 1, LUA_TLIGHTUSERDATA);
	PhysicsScreenEntity *inst = (PhysicsScreenEntity*)lua_topointer(L, 1);
	lua_pushlightuserdata(L, (void*)inst->getScreenEntity());
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

}