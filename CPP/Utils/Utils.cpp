#include "Utils.hpp"

#include "Game.hpp"

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
        __android_log_print(ANDROID_LOG_INFO, "OME_LOG:", "%s\n", buf);
#else
        printf("%s\n", buf);
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
    
    string Utils::modifyPath(string path){
        string pathToReturn = path;
        std::replace(pathToReturn.begin(), pathToReturn.end(), '\\', '/');
        return pathToReturn;
    }
    
    string Utils::extractPath(string path){
        string mfPath = modifyPath(path);
        int endPos = mfPath.find_last_of("/");
        if(endPos == string::npos){
            return path;
        }
        return mfPath.substr(0, endPos + 1);
    }
    string Utils::extractFilename(string path){
        string mfPath = modifyPath(path);
        int startPos =mfPath.find_last_of("/");
        if(startPos == string::npos){
            return path;
        }
        return mfPath.substr(startPos + 1, mfPath.length());
    }
    
    
    up<Cache> Utils::loadFile(string filename, bool relativePath){
        up<Cache> returnValue;
#ifdef __APPLE__
        FILE *f;
        
        if(relativePath){
            string path = Utils::extractPath(getenv("FILESYSTEM"));
            filename = path + filename;
        }
        
        f = fopen(filename.c_str(), "rb");
        
        if(!f){
            LOG("Failed to read file: %s\n", filename.c_str());
            return returnValue;
        }
        
        
        Cache *c = new Cache();
        c->name = filename;
        
        
        fseek(f, 0, SEEK_END);
        c->size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        c->content = new unsigned char[c->size + 1];;
        fread(c->content, c->size, 1, f);
        c->content[c->size] = 0;
        
        fclose(f);
        
        returnValue = up<Cache>(c);
        
#else
#ifdef ANDROID
        unzFile         uf;
        unz_file_info   fi;
        unz_file_pos    fp;
        string filePath = getenv("FILESYSTEM");
        uf = unzOpen(filePath.c_str());
        
        if(!uf){
            LOG("Failed to load file: %s\n", filePath.c_str());
            return returnValue;
        }
        
        if(relativePath){
            filename = "assets/" + filename;
        }
        
        unzGoToFirstFile(uf);
        
        Cache *c = new Cache();
        
        unzGetFilePos(uf, &fp);
        
        if(unzLocateFile(uf, filename.c_str(), 1) == UNZ_OK){
            char name[255] = {""};
            unzGetCurrentFileInfo(uf, &fi, name, 255, NULL, 0, NULL, 0);
            
            if(unzOpenCurrentFilePassword(uf, NULL) == UNZ_OK){
                c->position = 0;
                c->size = fi.uncompressed_size;
                c->content = new unsigned char[fi.uncompressed_size + 1];
                c->content[fi.uncompressed_size] = 0;
                
                while(unzReadCurrentFile(uf, c->content,fi.uncompressed_size) > 0){}
                
                unzCloseCurrentFile(uf);
                unzClose(uf);
                
                returnValue = up<Cache>(c);
            }
        }else{
            LOG("Failed to load file: %s\n", filename.c_str());
            unzClose(uf);
        }

#endif
#endif
        return returnValue;
    }
    
}

