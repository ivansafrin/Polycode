LOCAL_PATH := $(call my-dir)
SRCDIR := ../../../../src
LIBDIR := ../../../../lib/linux/android

include $(CLEAR_VARS)
LOCAL_MODULE := Polycode3DPhysics
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../include
LOCAL_SRC_FILES := $(SRCDIR)/modules/physics3D/PolyPhysicsConstraint.cpp $(SRCDIR)/modules/physics3D/PolyPhysicsSceneEntity.cpp $(SRCDIR)/modules/physics3D/PolyPhysicsScene.cpp $(SRCDIR)/modules/physics3D/PolyCollisionSceneEntity.cpp $(SRCDIR)/modules/physics3D/PolyCollisionScene.cpp
include $(BUILD_STATIC_LIBRARY)