LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_MODULE    := OMElib
LOCAL_CFLAGS    += -std=c++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/Android.cpp \
$(SRC_PATH)/CPP/Game.cpp\
$(SRC_PATH)/CPP/Utils/Utils.cpp\


LOCAL_C_INCLUDES	:= $(SRC_PATH) \
 $(COMMON_INC_PATH) \
$(SRC_PATH)/CPP\
$(SRC_PATH)/CPP/Utils\


LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)