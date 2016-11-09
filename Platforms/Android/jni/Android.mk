LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

include $(SRC_PATH)/CPP/3dPart/zlib/Android.mk

LOCAL_MODULE    := OMElib
LOCAL_CFLAGS    += -std=c++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/Android.cpp \
$(SRC_PATH)/CPP/Game.cpp\
$(SRC_PATH)/CPP/Utils/Files/Cache.cpp\
$(SRC_PATH)/CPP/Utils/Shaders/ShaderProgram.cpp\
$(SRC_PATH)/CPP/Utils/Texture2D/Texture2D.cpp\
$(SRC_PATH)/CPP/Utils/Utils.cpp\


LOCAL_C_INCLUDES	:= $(SRC_PATH) \
 $(COMMON_INC_PATH) \
$(SRC_PATH)/CPP/3dPart/zlib\
$(SRC_PATH)/CPP\
$(SRC_PATH)/CPP/Utils/Files\
$(SRC_PATH)/CPP/Utils/Shaders\
$(SRC_PATH)/CPP/Utils\
$(SRC_PATH)/CPP/Utils/Texture2D\


LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)