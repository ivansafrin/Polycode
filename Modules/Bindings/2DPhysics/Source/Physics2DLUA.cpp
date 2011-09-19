#include "Physics2DLUA.h"
#include "Physics2DLUAWrappers.h"
#include "PolyCoreServices.h"

using namespace Polycode;

int luaopen_Physics2D(lua_State *L) {
CoreServices *inst = (CoreServices*)lua_topointer(L, 1);
CoreServices::setInstance(inst);
	static const struct luaL_reg physics2dLib [] = {		{"PhysicsScreen", Physics2D_PhysicsScreen},
		{"PhysicsScreen_Update", Physics2D_PhysicsScreen_Update},
		{"PhysicsScreen_addPhysicsChild", Physics2D_PhysicsScreen_addPhysicsChild},
		{"PhysicsScreen_removePhysicsChild", Physics2D_PhysicsScreen_removePhysicsChild},
		{"PhysicsScreen_addCollisionChild", Physics2D_PhysicsScreen_addCollisionChild},
		{"PhysicsScreen_destroyJoint", Physics2D_PhysicsScreen_destroyJoint},
		{"PhysicsScreen_createDistanceJoint", Physics2D_PhysicsScreen_createDistanceJoint},
		{"PhysicsScreen_createPrismaticJoint", Physics2D_PhysicsScreen_createPrismaticJoint},
		{"PhysicsScreen_createRevoluteJoint", Physics2D_PhysicsScreen_createRevoluteJoint},
		{"PhysicsScreen_applyForce", Physics2D_PhysicsScreen_applyForce},
		{"PhysicsScreen_applyImpulse", Physics2D_PhysicsScreen_applyImpulse},
		{"PhysicsScreen_setGravity", Physics2D_PhysicsScreen_setGravity},
		{"PhysicsScreen_setTransform", Physics2D_PhysicsScreen_setTransform},
		{"PhysicsScreen_getPhysicsEntityByShape", Physics2D_PhysicsScreen_getPhysicsEntityByShape},
		{"PhysicsScreen_getPhysicsEntityByFixture", Physics2D_PhysicsScreen_getPhysicsEntityByFixture},
		{"PhysicsScreen_setVelocity", Physics2D_PhysicsScreen_setVelocity},
		{"PhysicsScreen_setVelocityX", Physics2D_PhysicsScreen_setVelocityX},
		{"PhysicsScreen_setVelocityY", Physics2D_PhysicsScreen_setVelocityY},
		{"PhysicsScreen_setSpin", Physics2D_PhysicsScreen_setSpin},
		{"PhysicsScreen_getVelocity", Physics2D_PhysicsScreen_getVelocity},
		{"PhysicsScreen_BeginContact", Physics2D_PhysicsScreen_BeginContact},
		{"PhysicsScreen_EndContact", Physics2D_PhysicsScreen_EndContact},
		{"PhysicsScreen_PostSolve", Physics2D_PhysicsScreen_PostSolve},
		{"PhysicsScreen_wakeUp", Physics2D_PhysicsScreen_wakeUp},
		{"PhysicsScreen_getEntityAtPosition", Physics2D_PhysicsScreen_getEntityAtPosition},
		{"PhysicsScreen_testEntityAtPosition", Physics2D_PhysicsScreen_testEntityAtPosition},
		{"PhysicsScreen_Shutdown", Physics2D_PhysicsScreen_Shutdown},
		{"PhysicsScreen_getPhysicsByScreenEntity", Physics2D_PhysicsScreen_getPhysicsByScreenEntity},
		{"PhysicsScreen_destroyMouseJoint", Physics2D_PhysicsScreen_destroyMouseJoint},
		{"delete_PhysicsScreen", Physics2D_delete_PhysicsScreen},
		{"PhysicsScreenEvent_get_localCollisionNormal", Physics2D_PhysicsScreenEvent_get_localCollisionNormal},
		{"PhysicsScreenEvent_get_worldCollisionNormal", Physics2D_PhysicsScreenEvent_get_worldCollisionNormal},
		{"PhysicsScreenEvent_get_localCollisionPoint", Physics2D_PhysicsScreenEvent_get_localCollisionPoint},
		{"PhysicsScreenEvent_get_impactStrength", Physics2D_PhysicsScreenEvent_get_impactStrength},
		{"PhysicsScreenEvent_get_frictionStrength", Physics2D_PhysicsScreenEvent_get_frictionStrength},
		{"PhysicsScreenEvent_set_impactStrength", Physics2D_PhysicsScreenEvent_set_impactStrength},
		{"PhysicsScreenEvent_set_frictionStrength", Physics2D_PhysicsScreenEvent_set_frictionStrength},
		{"PhysicsScreenEvent", Physics2D_PhysicsScreenEvent},
		{"PhysicsScreenEvent_getFirstEntity", Physics2D_PhysicsScreenEvent_getFirstEntity},
		{"PhysicsScreenEvent_getSecondEntity", Physics2D_PhysicsScreenEvent_getSecondEntity},
		{"delete_PhysicsScreenEvent", Physics2D_delete_PhysicsScreenEvent},
		{"PhysicsJoint", Physics2D_PhysicsJoint},
		{"delete_PhysicsJoint", Physics2D_delete_PhysicsJoint},
		{"PhysicsScreenEntity_get_collisionOnly", Physics2D_PhysicsScreenEntity_get_collisionOnly},
		{"PhysicsScreenEntity_set_collisionOnly", Physics2D_PhysicsScreenEntity_set_collisionOnly},
		{"PhysicsScreenEntity", Physics2D_PhysicsScreenEntity},
		{"PhysicsScreenEntity_getScreenEntity", Physics2D_PhysicsScreenEntity_getScreenEntity},
		{"PhysicsScreenEntity_applyTorque", Physics2D_PhysicsScreenEntity_applyTorque},
		{"PhysicsScreenEntity_applyForce", Physics2D_PhysicsScreenEntity_applyForce},
		{"PhysicsScreenEntity_setTransform", Physics2D_PhysicsScreenEntity_setTransform},
		{"PhysicsScreenEntity_Update", Physics2D_PhysicsScreenEntity_Update},
		{"delete_PhysicsScreenEntity", Physics2D_delete_PhysicsScreenEntity},
		{NULL, NULL}
	};
	luaL_openlib(L, "Physics2D", physics2dLib, 0);
	return 1;
}