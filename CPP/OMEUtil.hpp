#pragma once

#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGLES/ES3/gl.h>
#else
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#endif

///
//  Macros
//
#ifdef WIN32
#define ESUTIL_API  __cdecl
#define ESCALLBACK  __cdecl
#else
#define ESUTIL_API
#define ESCALLBACK
#endif


/// esCreateWindow flag - RGB color buffer
#define ES_WINDOW_RGB           0
/// esCreateWindow flag - ALPHA color buffer
#define ES_WINDOW_ALPHA         1
/// esCreateWindow flag - depth buffer
#define ES_WINDOW_DEPTH         2
/// esCreateWindow flag - stencil buffer
#define ES_WINDOW_STENCIL       4
/// esCreateWindow flat - multi-sample buffer
#define ES_WINDOW_MULTISAMPLE   8


///
// Types
//
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

typedef struct
{
   GLfloat   m[4][4];
} ESMatrix;

typedef struct ESContext ESContext;

struct ESContext
{

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

   /// Callbacks
   void ( ESCALLBACK *drawFunc ) ( ESContext * );
   void ( ESCALLBACK *shutdownFunc ) ( ESContext * );
   void ( ESCALLBACK *keyFunc ) ( ESContext *, unsigned char, int, int );
   void ( ESCALLBACK *updateFunc ) ( ESContext *, float deltaTime );
};


///
//  Public Functions
//

//
/// \brief Create a window with the specified parameters
/// \param esContext Application context
/// \param title Name for title bar of window
/// \param width Width in pixels of window to create
/// \param height Height in pixels of window to create
/// \param flags Bitfield for the window creation flags
///         ES_WINDOW_RGB     - specifies that the color buffer should have R,G,B channels
///         ES_WINDOW_ALPHA   - specifies that the color buffer should have alpha
///         ES_WINDOW_DEPTH   - specifies that a depth buffer should be created
///         ES_WINDOW_STENCIL - specifies that a stencil buffer should be created
///         ES_WINDOW_MULTISAMPLE - specifies that a multi-sample buffer should be created
/// \return GL_TRUE if window creation is succesful, GL_FALSE otherwise
GLboolean ESUTIL_API esCreateWindow ( ESContext *esContext, const char *title, GLint width, GLint height, GLuint flags );

void ESUTIL_API esRegisterDrawFunc ( ESContext *esContext, void ( ESCALLBACK *drawFunc ) ( ESContext * ) );

void ESUTIL_API esRegisterShutdownFunc ( ESContext *esContext, void ( ESCALLBACK *shutdownFunc ) ( ESContext * ) );

void ESUTIL_API esRegisterUpdateFunc ( ESContext *esContext, void ( ESCALLBACK *updateFunc ) ( ESContext *, float ) );

void ESUTIL_API esRegisterKeyFunc ( ESContext *esContext,
                                    void ( ESCALLBACK *drawFunc ) ( ESContext *, unsigned char, int, int ) );

void ESUTIL_API esLogMessage ( const char *formatStr, ... );

GLuint ESUTIL_API esLoadShader ( GLenum type, const char *shaderSrc );

GLuint ESUTIL_API esLoadProgram ( const char *vertShaderSrc, const char *fragShaderSrc );

int ESUTIL_API esGenSphere ( int numSlices, float radius, GLfloat **vertices, GLfloat **normals,
                             GLfloat **texCoords, GLuint **indices );

int ESUTIL_API esGenCube ( float scale, GLfloat **vertices, GLfloat **normals,
                           GLfloat **texCoords, GLuint **indices );

int ESUTIL_API esGenSquareGrid ( int size, GLfloat **vertices, GLuint **indices );

char *ESUTIL_API esLoadTGA ( void *ioContext, const char *fileName, int *width, int *height );

void ESUTIL_API esScale ( ESMatrix *result, GLfloat sx, GLfloat sy, GLfloat sz );

void ESUTIL_API esTranslate ( ESMatrix *result, GLfloat tx, GLfloat ty, GLfloat tz );

void ESUTIL_API esRotate ( ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z );

void ESUTIL_API esFrustum ( ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ );

void ESUTIL_API esPerspective ( ESMatrix *result, float fovy, float aspect, float nearZ, float farZ );

void ESUTIL_API esOrtho ( ESMatrix *result, float left, float right, float bottom, float top, float nearZ, float farZ );

void ESUTIL_API esMatrixMultiply ( ESMatrix *result, ESMatrix *srcA, ESMatrix *srcB );

void ESUTIL_API esMatrixLoadIdentity ( ESMatrix *result );

void ESUTIL_API
esMatrixLookAt ( ESMatrix *result,
                 float posX,    float posY,    float posZ,
                 float lookAtX, float lookAtY, float lookAtZ,
                 float upX,     float upY,     float upZ );


