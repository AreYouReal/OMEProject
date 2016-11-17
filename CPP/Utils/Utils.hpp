#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>


#include "Shortcuts.hpp"
#include "Cache.hpp"
    
#ifdef __APPLE__

#include <OpenGLES/ES3/gl.h>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

#include "FileWrapper.h"
    
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#ifdef ANDROID
#include <android/log.h>
#include <android_native_app_glue.h>
#include <android/asset_manager.h>
//    
//#include "al.h"
//#include "alc.h"
#endif
#endif


#define WINDOW_RGB           0   /// OMCreateWindow flag - RGB color buffer
#define WINDOW_ALPHA         1   /// OMCreateWindow flag - ALPHA color buffer
#define WINDOW_DEPTH         2   /// OMCreateWindow flag - depth buffer
#define WINDOW_STENCIL       4   /// OMCreateWindow flag - stencil buffer
#define WINDOW_MULTISAMPLE   8   /// OMCreateWindow flat - multi-sample buffer



namespace OME {
    
    using OnUpdate  = void(*)(const float);
    using OnDraw    = void(*)();
    using OnTouch   = void(*)(const int, const int, const int);
    using OnDestroy = void(*)();
    
    struct Context{
        void    *platformData;
        void    *userData;
        GLint   width;
        GLint   height;
        
#ifndef __APPLE__
        EGLNativeDisplayType eglNativeDisplay;   /// Display handle
        EGLNativeWindowType  eglNativeWindow;    /// Window handle
        EGLDisplay  eglDisplay;                  /// EGL display
        EGLContext  eglContext;                  /// EGL context
        EGLSurface  eglSurface;                  /// EGL surface
#endif
    
        OnUpdate    onUpdate;
        OnDraw      onDraw;
        OnTouch     onTouch;
        OnDestroy   onDestroy;
        
    };

    struct Utils{
#pragma mark Window Create
        static GLboolean OMCreateWindow(Context *ctx, std::string title, GLint width, GLint height, GLuint flags);
        
#pragma mark Logging
        
        static void LOG(std::string formatString, ...);
        static void PRINT_GL_STRING(std::string name, GLenum s);
        static void LOG_GL_ERROR();
        
        
#pragma mark File IO
        static string modifyPath(string path);
        static string extractPath(string path);
        static string extractFilename(string path);
        
        static FILE* fileOpen(void *ioContext, string filename);
        static long getFileSize(FILE *pFile);
        static void fileClose(FILE *pFile);
        static long fileRead(FILE *pFile, long bytesToRead, void *buffer);
        
        static up<Cache> loadFile(string filename, bool relativePath);

//        static vec<unsigned char> loadRawPNGData(string fileName);
    };
    

    
}

