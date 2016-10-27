LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= ../../../CPP

include $(CLEAR_VARS)

LOCAL_MODULE    := OMElib
LOCAL_CFLAGS    += -DANDROID


LOCAL_SRC_FILES := $(SRC_PATH)/esShader.c \
				   $(SRC_PATH)/esShapes.c \
				   $(SRC_PATH)/esTransform.c \
				   $(SRC_PATH)/esUtil.c \
				   $(SRC_PATH)/Hello_Triangle.c \
				   $(SRC_PATH)/esUtil_Android.c \


LOCAL_C_INCLUDES	:= $(SRC_PATH) \
						$(SRC_PATH)/../Platforms/Android/jni \
				   
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
