LOCAL_PATH			:= $(call my-dir)
SRC_PATH			:= $(LOCAL_PATH)/../../..

include $(CLEAR_VARS)

LOCAL_MODULE    := OME
LOCAL_CFLAGS    += -std=c++11

LOCAL_SRC_FILES := $(LOCAL_PATH)/Android.cpp \
$(SRC_PATH)/CPP/3dPart/glm/detail/dummy.cpp\
$(SRC_PATH)/CPP/3dPart/glm/detail/glm.cpp\
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
$(SRC_PATH)/CPP/Components/Camera/Camera.cpp\
$(SRC_PATH)/CPP/Components/Mesh/Mesh.cpp\
$(SRC_PATH)/CPP/Components/Primitives/Cube.cpp\
$(SRC_PATH)/CPP/Components/Primitives/Grid.cpp\
$(SRC_PATH)/CPP/Components/Primitives/Primitives.cpp\
$(SRC_PATH)/CPP/Components/Transform/Transform.cpp\
$(SRC_PATH)/CPP/Game.cpp\
$(SRC_PATH)/CPP/GameObject/GameObject.cpp\
$(SRC_PATH)/CPP/Utils/Files/Cache.cpp\
$(SRC_PATH)/CPP/Utils/Shaders/ShaderProgram.cpp\
$(SRC_PATH)/CPP/Utils/Texture2D/PngTexture2D.cpp\
$(SRC_PATH)/CPP/Utils/Texture2D/Texture2D.cpp\
$(SRC_PATH)/CPP/Utils/Time.cpp\
$(SRC_PATH)/CPP/Utils/Utils.cpp\


LOCAL_C_INCLUDES	:= $(SRC_PATH) \
 $(COMMON_INC_PATH) \
$(SRC_PATH)/CPP/3dPart/glm\
$(SRC_PATH)/CPP/3dPart/glm/detail\
$(SRC_PATH)/CPP/3dPart/glm/gtc\
$(SRC_PATH)/CPP/3dPart/glm/gtx\
$(SRC_PATH)/CPP/3dPart/glm/simd\
$(SRC_PATH)/CPP/3dPart/libpng\
$(SRC_PATH)/CPP/3dPart/zlib\
$(SRC_PATH)/CPP/Components/Camera\
$(SRC_PATH)/CPP/Components\
$(SRC_PATH)/CPP/Components/Mesh\
$(SRC_PATH)/CPP/Components/Primitives\
$(SRC_PATH)/CPP/Components/Transform\
$(SRC_PATH)/CPP\
$(SRC_PATH)/CPP/GameObject\
$(SRC_PATH)/CPP/Utils/Files\
$(SRC_PATH)/CPP/Utils/Shaders\
$(SRC_PATH)/CPP/Utils\
$(SRC_PATH)/CPP/Utils/Texture2D\


LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv3

LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_CPP_FEATURES := rtti exceptions

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)