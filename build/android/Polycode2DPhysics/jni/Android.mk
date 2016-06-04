LOCAL_PATH := $(call my-dir)
SRCDIR := ../../../../src
LIBDIR := ../../../../lib/linux/android

include $(CLEAR_VARS)
LOCAL_MODULE := Polycode2DPhysics
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../include
LOCAL_SRC_FILES := $(SRCDIR)/modules/physics2D/PolyPhysicsScreen.cpp $(SRCDIR)/modules/physics2D/PolyPhysicsScreenEntity.cpp
include $(BUILD_STATIC_LIBRARY)