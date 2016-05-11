LOCAL_PATH := $(call my-dir)
SRCDIR := ../../../../src
LIBDIR := ../../../../lib/android/$(TARGET_ARCH_ABI)

include $(CLEAR_VARS)
LOCAL_MODULE := Polycore
LOCAL_SRC_FILES := ../../Polycore/obj/local/$(TARGET_ARCH_ABI)/libPolycore.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := freetype
LOCAL_SRC_FILES := $(LIBDIR)/libfreetype.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := lua
LOCAL_SRC_FILES := $(LIBDIR)/liblua.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := physfs
LOCAL_SRC_FILES := $(LIBDIR)/libphysfs.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ogg
LOCAL_SRC_FILES := $(LIBDIR)/libogg.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := vorbis
LOCAL_SRC_FILES := $(LIBDIR)/libvorbis.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := TemplateApp
LOCAL_LDLIBS := -landroid -lEGL -lGLESv2 -lOpenSLES -lz -llog
LOCAL_STATIC_LIBRARIES := Polycore freetype lua physfs
LOCAL_SHARED_LIBRARIES := ogg vorbis
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../include -DUSE_EGL -DSTRICT_OPENGLES2
LOCAL_SRC_FILES := PolycodeTemplate.cpp PolycodeTemplateApp.cpp
include $(BUILD_SHARED_LIBRARY)
