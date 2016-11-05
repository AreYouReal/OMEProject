#include "Utils.hpp"

#include "Game.hpp"

#include "../3dPart/libpng/png.h"

namespace OME {
    
#ifndef __APPLE__
    
    /** Check whether EGL_KHR_create_context extension is supported.  If so,
     return EGL_OPENGL_ES3_BIT_KHR instead of EGL_OPENGL_ES2_BIT */
    EGLint GetContextRenderableType ( EGLDisplay eglDisplay ){
#ifdef EGL_KHR_create_context
        const char *extensions = eglQueryString ( eglDisplay, EGL_EXTENSIONS );
        // check whether EGL_KHR_create_context is in the extension string
        if ( extensions != NULL && strstr( extensions, "EGL_KHR_create_context" ) ){
            return EGL_OPENGL_ES3_BIT_KHR; // extension is supported
        }
#endif
        return EGL_OPENGL_ES2_BIT;          // extension is not supported
    }
#endif

    
    GLboolean Utils::OMCreateWindow(Context *ctx, std::string title, GLint width, GLint height, GLuint flags){
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
                EGL_SAMPLE_BUFFERS, ( flags & WINDOW_MULTISAMPLE ) ? 1 : 0,
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

    void Utils::LOG(std::string formatString, ...){
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
    
    void Utils::PRINT_GL_STRING(std::string name, GLenum s){
        LOG("GL %s = %s\n", name.c_str(), (const char*)glGetString(s));
    }
    
    void Utils::LOG_GL_ERROR(){
        GLenum err = glGetError();
        if(err != GL_NO_ERROR){
            LOG("\n------------GL_ERROR [ %x ]--------------\n", err);
        }
    }
    

    omFile* Utils::fileOpen(void *ioContext, string filename){
        omFile *pFile = NULL;
#ifdef ANDROID
        if ( ioContext != NULL ){
            AAssetManager *assetManager = ( AAssetManager * ) ((OME::Context*)ioContext)->platformData;
            pFile = AAssetManager_open ( assetManager, filename.c_str(), AASSET_MODE_BUFFER );
        }
#else
#ifdef __APPLE__
        filename = GetBundleFileName ( filename.c_str() );
#endif
        pFile = fopen ( filename.c_str(), "rb" );
#endif
        return pFile;
    }
    
    long Utils::getFileSize(omFile *pFile){
#ifdef ANDROID
        long fSize = AAsset_getLength(pFile);
#else
        fseek(pFile, 0, SEEK_END);
        long fSize = ftell(pFile);
        rewind(pFile);
#endif
        return fSize;
    }
    
    void    Utils::fileClose       ( omFile *pFile ){
        if ( pFile != NULL )
        {
#ifdef ANDROID
            AAsset_close ( pFile );
#else
            fclose ( pFile );
            pFile = NULL;
#endif
        }
    }
    
    long     Utils::fileRead        ( omFile *pFile, long bytesToRead, void *buffer ){
        long bytesRead = 0;
        
        if ( pFile == NULL ) return bytesRead;
        
#ifdef ANDROID
        bytesRead = AAsset_read ( pFile, buffer, bytesToRead );
#else
        bytesRead = fread ( buffer, bytesToRead, 1, pFile );
#endif
        
        return bytesRead;
    }
    
    
    up<FileContent> Utils::readTextFile(string fileName){
        omFile *pFile;
        up<FileContent> returnValue;
        
        pFile = fileOpen(OME::Game::currentCtx, fileName.c_str());
        
        
        
        if(pFile == NULL){
            LOG("Failed open file [%s]\n", fileName.c_str());
            return returnValue;
        }
        
        long fSize = getFileSize(pFile);
        unsigned char *tempBuffer = new unsigned char[fSize + 1];
        if(fileRead(pFile, fSize, tempBuffer) == 0) return returnValue;
        
        fileClose(pFile);
        tempBuffer[fSize] = 0;
        returnValue = up<FileContent>(new FileContent(tempBuffer, fSize + 1, fileName));
        return returnValue;
    }
    
    up<FileContent> Utils::readBytesFromFile(string fileName){
        omFile *pFile;
        up<FileContent> returnValue;
        
        pFile = fileOpen(OME::Game::currentCtx, fileName.c_str());
        
        
        
        if(pFile == NULL){
            LOG("Failed open file [%s]\n", fileName.c_str());
            return returnValue;
        }
        
        long fSize = getFileSize(pFile);
        unsigned char *tempBuffer = new unsigned char[fSize];
        if(fileRead(pFile, fSize, tempBuffer) == 0) return returnValue;
        
        fileClose(pFile);
        tempBuffer[fSize] = 0;
        returnValue = up<FileContent>(new FileContent(tempBuffer, fSize, fileName));
        return returnValue;
    }
    
    vec<unsigned char> Utils::loadRawPNGData(string fileName){
        char header[8];
        
        png_structp pngPointer;
        png_infop infoPointer;
        png_byte bitDepth;
        int x, y;
        int number_of_passes;
        
        up<FileContent> imageFile = readBytesFromFile(fileName);
        memcpy(header, imageFile->content, 8);
        
        if(png_sig_cmp((png_const_bytep)header, 0, 8)){
            LOG("File is not recognized as a PNG file %s", fileName.c_str());
            return vec<unsigned char>();
        }
        
        
        LOG("PNG HEADER: %s", header);
        
        
        
        
        
        
        return vec<unsigned char>();
    }
    
}

