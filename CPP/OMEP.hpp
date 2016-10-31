#pragma once

#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

#ifdef WIN32
#define OMEPUTIL_API  __cdecl
#define OMEPCALLBACK  __cdecl
#else
#define OMEPUTIL_API
#define OMEPCALLBACK
#endif


struct OMEPContext{
    
    void       *platformData;    /// Put platform specific data here
    void       *userData;        /// Put your user data here...
    GLint       width;           /// Window width
    GLint       height;          /// Window height
    
#ifndef __APPLE__
    
    EGLNativeDisplayType eglNativeDisplay;   /// Display handle
    EGLNativeWindowType  eglNativeWindow;    /// Window handle
    EGLDisplay           eglDisplay;         /// EGL display
    EGLContext           eglContext;         /// EGL context
    EGLSurface           eglSurface;         /// EGL surface
#endif
};


class OMEP{

    
public:
    /// Callbacks
    void ( OMEPCALLBACK *drawFunc ) ( OMEPContext * );
    void ( OMEPCALLBACK *shutdownFunc ) ( OMEPContext * );
    void ( OMEPCALLBACK *keyFunc ) ( OMEPContext *, unsigned char, int, int );
    void ( OMEPCALLBACK *updateFunc ) ( OMEPContext *, float deltaTime );

};
