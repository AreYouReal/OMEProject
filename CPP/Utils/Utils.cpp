#include "Utils.hpp"

namespace OME {
    
    GLboolean CreateWindow(Context *ctx, std::string title, GLint width, GLint height, GLuint flags){
#ifndef __APPLE__
        EGLConfig config;
        EGLint majorVersion;
        EGLint minorVersion;
        EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE };
        
        if ( ctx == NULL ){
            return GL_FALSE;
        }
        
#ifdef ANDROID
        // For Android, get the width/height from the window rather than what the
        // application requested.
        ctx->width = ANativeWindow_getWidth ( ctx->eglNativeWindow );
        ctx->height = ANativeWindow_getHeight ( ctx->eglNativeWindow );
#else
        ctx->width = width;
        ctx->height = height;
#endif
        
        ctx->eglDisplay = eglGetDisplay( ctx->eglNativeDisplay );
        if ( ctx->eglDisplay == EGL_NO_DISPLAY ){
            return GL_FALSE;
        }
        
        // Initialize EGL
        if ( !eglInitialize ( ctx->eglDisplay, &majorVersion, &minorVersion ) ){
            return GL_FALSE;
        }
        
        {
            EGLint numConfigs = 0;
            EGLint attribList[] = {
                EGL_RED_SIZE,       5,
                EGL_GREEN_SIZE,     6,
                EGL_BLUE_SIZE,      5,
                EGL_ALPHA_SIZE,     8,
                EGL_DEPTH_SIZE,     8,
                EGL_STENCIL_SIZE,   8,
                EGL_SAMPLE_BUFFERS, ( flags & OM_WINDOW_MULTISAMPLE ) ? 1 : 0,
                // if EGL_KHR_create_context extension is supported, then we will use
                // EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT in the attribute list
                EGL_RENDERABLE_TYPE, GetContextRenderableType ( ctx->eglDisplay ),
                EGL_NONE
            };
            
            // Choose config
            if ( !eglChooseConfig ( ctx->eglDisplay, attribList, &config, 1, &numConfigs ) ){
                return GL_FALSE;
            }
            
            if ( numConfigs < 1 ){
                return GL_FALSE;
            }
        }
        
        
#ifdef ANDROID
        // For Android, need to get the EGL_NATIVE_VISUAL_ID and set it using ANativeWindow_setBuffersGeometry
        {
            EGLint format = 0;
            eglGetConfigAttrib ( ctx->eglDisplay, config, EGL_NATIVE_VISUAL_ID, &format );
            ANativeWindow_setBuffersGeometry ( ctx->eglNativeWindow, 0, 0, format );
        }
#endif // ANDROID
        // Create a surface
        ctx->eglSurface = eglCreateWindowSurface ( ctx->eglDisplay, config,
                                                      ctx->eglNativeWindow, NULL );
        
        if ( ctx->eglSurface == EGL_NO_SURFACE ){
            return GL_FALSE;
        }
        
        // Create a GL context
        ctx->eglContext = eglCreateContext ( ctx->eglDisplay, config,
                                                EGL_NO_CONTEXT, contextAttribs );
        
        if ( ctx->eglContext == EGL_NO_CONTEXT ){
            return GL_FALSE;
        }
        
        // Make the context current
        if ( !eglMakeCurrent ( ctx->eglDisplay, ctx->eglSurface,
                              ctx->eglSurface, ctx->eglContext ) ){
            return GL_FALSE;
        }
        
#endif // #ifndef __APPLE__
        
        return GL_TRUE;

    }
    
    void LOG(std::string formatString, ...){
        va_list params;
        char buf[1024];
        va_start(params, formatString);
        vsprintf(buf, formatString.c_str(), params);
#ifdef ANDROID
        __android_log_print(ANDROID_LOG_INFO, "OME_LOG:", "%s", buf);
#else
        printf("%s", buf);
#endif
        va_end(params);
    }
    
    void PRINT_GL_STRING(std::string name, GLenum s){
        LOG("GL %s = %s\n", name.c_str(), (const char*)glGetString(s));
    }
    
    void LOG_GL_ERROR(){
        GLenum err = glGetError();
        if(err != GL_NO_ERROR){
            LOG("\n------------GL_ERROR [ %x ]--------------\n", err);
        }
    }
}

