LOCAL_PATH := $(call my-dir)
SRCDIR := ../../../../src
LIBDIR := ../../../../lib/linux/android

include $(CLEAR_VARS)
LOCAL_MODULE := PolycodeUI
LOCAL_CFLAGS += -I$(LOCAL_PATH)/../../../../include
LOCAL_SRC_FILES := $(SRCDIR)/modules/ui/PolyUIBox.cpp $(SRCDIR)/modules/ui/PolyUIButton.cpp $(SRCDIR)/modules/ui/PolyUICheckBox.cpp $(SRCDIR)/modules/ui/PolyUIColorBox.cpp $(SRCDIR)/modules/ui/PolyUIComboBox.cpp $(SRCDIR)/modules/ui/PolyUIElement.cpp $(SRCDIR)/modules/ui/PolyUIEvent.cpp $(SRCDIR)/modules/ui/PolyUIFileDialog.cpp $(SRCDIR)/modules/ui/PolyUIHScrollBar.cpp $(SRCDIR)/modules/ui/PolyUIHSizer.cpp $(SRCDIR)/modules/ui/PolyUIHSlider.cpp $(SRCDIR)/modules/ui/PolyUIIconSelector.cpp $(SRCDIR)/modules/ui/PolyUIImageButton.cpp $(SRCDIR)/modules/ui/PolyUIMenu.cpp $(SRCDIR)/modules/ui/PolyUIMenuBar.cpp $(SRCDIR)/modules/ui/PolyUIScrollContainer.cpp $(SRCDIR)/modules/ui/PolyUITextInput.cpp $(SRCDIR)/modules/ui/PolyUITree.cpp $(SRCDIR)/modules/ui/PolyUITreeContainer.cpp $(SRCDIR)/modules/ui/PolyUITreeEvent.cpp $(SRCDIR)/modules/ui/PolyUIVScrollBar.cpp $(SRCDIR)/modules/ui/PolyUIVSizer.cpp $(SRCDIR)/modules/ui/PolyUIWindow.cpp
include $(BUILD_STATIC_LIBRARY)