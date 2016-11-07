LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_MODULE    := OMElib
LOCAL_CFLAGS    += -std=c++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/Android.cpp \
$(SRC_PATH)/CPP/3dPart/zlib/adler32.c\
$(SRC_PATH)/CPP/3dPart/zlib/compress.c\
$(SRC_PATH)/CPP/3dPart/zlib/crc32.c\
$(SRC_PATH)/CPP/3dPart/zlib/deflate.c\
$(SRC_PATH)/CPP/3dPart/zlib/gzio.c\
$(SRC_PATH)/CPP/3dPart/zlib/infback.c\
$(SRC_PATH)/CPP/3dPart/zlib/inffast.c\
$(SRC_PATH)/CPP/3dPart/zlib/inflate.c\
$(SRC_PATH)/CPP/3dPart/zlib/inftrees.c\
$(SRC_PATH)/CPP/3dPart/zlib/ioapi.c\
$(SRC_PATH)/CPP/3dPart/zlib/trees.c\
$(SRC_PATH)/CPP/3dPart/zlib/uncompr.c\
$(SRC_PATH)/CPP/3dPart/zlib/unzip.c\
$(SRC_PATH)/CPP/3dPart/zlib/zutil.c\
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