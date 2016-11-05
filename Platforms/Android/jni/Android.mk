LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_MODULE    := OME
LOCAL_CFLAGS    += -std=c++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/Android.cpp \
$(SRC_PATH)/CPP/3dPart/libpng/png.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngerror.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngget.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngmem.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngpread.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngread.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngrio.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngrtran.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngrutil.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngset.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngtest.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngtrans.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngwio.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngwrite.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngwtran.c\
$(SRC_PATH)/CPP/3dPart/libpng/pngwutil.c\
$(SRC_PATH)/CPP/Game.cpp\
$(SRC_PATH)/CPP/Utils/Shaders/ShaderProgram.cpp\
$(SRC_PATH)/CPP/Utils/Texture2D/Texture2D.cpp\
$(SRC_PATH)/CPP/Utils/Utils.cpp\


LOCAL_C_INCLUDES	:= $(SRC_PATH) \
 $(COMMON_INC_PATH) \
$(SRC_PATH)/CPP/3dPart/libpng\
$(SRC_PATH)/CPP\
$(SRC_PATH)/CPP/Utils/Files\
$(SRC_PATH)/CPP/Utils/Shaders\
$(SRC_PATH)/CPP/Utils\
$(SRC_PATH)/CPP/Utils/Texture2D\


LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3 -lz

LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)