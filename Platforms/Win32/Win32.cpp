// Includes
//
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include "Game.hpp"

#ifdef _WIN64
#define GWL_USERDATA GWLP_USERDATA
#endif

//  OMEWindowProc()
//      Main window procedure
//
LRESULT WINAPI OMEWindowProc ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ){
   LRESULT  lRet = 1;

   switch ( uMsg ){
      case WM_CREATE:
         break;

      case WM_PAINT:{
         OME::Context *ctx = ( OME::Context * ) ( LONG_PTR ) GetWindowLongPtr ( hWnd, GWL_USERDATA );

         if ( ctx && ctx->onDraw ){
            ctx->onDraw ( );
            eglSwapBuffers ( ctx->eglDisplay, ctx->eglSurface );
         }

         ValidateRect ( ctx->eglNativeWindow, NULL );
      }
      break;

      case WM_DESTROY:
         PostQuitMessage ( 0 );
         break;

      case WM_CHAR:{
         POINT      point;
         OME::Context *ctx = ( OME::Context * ) ( LONG_PTR ) GetWindowLongPtr ( hWnd, GWL_USERDATA );

         GetCursorPos ( &point );

         if ( ctx && ctx->onTouch )
            ctx->onTouch ( ( unsigned char ) wParam,
                                 ( int ) point.x, ( int ) point.y );
      }
      break;

      default:
         lRet = DefWindowProc ( hWnd, uMsg, wParam, lParam );
         break;
   }

   return lRet;
}
//  WinCreate()
//
//      Create Win32 instance and window
//
GLboolean WinCreate ( OME::Context *ctx, const char *title ){
   WNDCLASS wndclass = {0};
   DWORD    wStyle   = 0;
   RECT     windowRect;
   HINSTANCE hInstance = GetModuleHandle ( NULL );


   wndclass.style         = CS_OWNDC;
   wndclass.lpfnWndProc   = ( WNDPROC ) OMEWindowProc;
   wndclass.hInstance     = hInstance;
   wndclass.hbrBackground = ( HBRUSH ) GetStockObject ( BLACK_BRUSH );
   wndclass.lpszClassName = "opengles3.0";

   if ( !RegisterClass ( &wndclass ) ){
      return FALSE;
   }

   wStyle = WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

   // Adjust the window rectangle so that the client area has
   // the correct number of pixels
   windowRect.left = 0;
   windowRect.top = 0;
   windowRect.right = ctx->width;
   windowRect.bottom = ctx->height;

   AdjustWindowRect ( &windowRect, wStyle, FALSE );



   ctx->eglNativeWindow = CreateWindow (
                                   "opengles3.0",
                                   title,
                                   wStyle,
                                   0,
                                   0,
                                   windowRect.right - windowRect.left,
                                   windowRect.bottom - windowRect.top,
                                   NULL,
                                   NULL,
                                   hInstance,
                                   NULL );

   // Set the ESContext* to the GWL_USERDATA so that it is available to the
   // ESWindowProc
   SetWindowLongPtr (  ctx->eglNativeWindow, GWL_USERDATA, ( LONG ) ( LONG_PTR ) ctx );


   if ( ctx->eglNativeWindow == NULL ){
      return GL_FALSE;
   }

   ShowWindow ( ctx->eglNativeWindow, TRUE );

   return GL_TRUE;
}

///
//  WinLoop()
//
//      Start main windows loop
//
void WinLoop ( OME::Context *ctx ){
   MSG msg = { 0 };
   int done = 0;
   DWORD lastTime = GetTickCount();

   while ( !done ){
      int gotMsg = ( PeekMessage ( &msg, NULL, 0, 0, PM_REMOVE ) != 0 );
      DWORD curTime = GetTickCount();
      float deltaTime = ( float ) ( curTime - lastTime ) / 1000.0f;
      lastTime = curTime;

      if ( gotMsg ){
         if ( msg.message == WM_QUIT ){
            done = 1;
         } else {
            TranslateMessage ( &msg );
            DispatchMessage ( &msg );
         }
      } else {
         SendMessage ( ctx->eglNativeWindow, WM_PAINT, 0, 0 );
      }

      // Call update function if registered
      if ( ctx->onUpdate != NULL ){
         ctx->onUpdate ( deltaTime );
      }
   }
}
///
//  main()
//
//      Main entrypoint for application
//
int main ( int argc, char *argv[] ){
   OME::Context ctx;

   memset ( &ctx, 0, sizeof ( OME::Context ) );


   ctx.width = 640;
   ctx.height = 480;
   WinCreate(&ctx, "One More Engine In Action!");

   if ( !OME::Game::StartUp ( &ctx ) ){
	  return 1;
   }

   WinLoop ( &ctx );

   if ( ctx.onDestroy != NULL ){
      ctx.onDestroy ( );
   }

   if ( ctx.userData != NULL ){
      free ( ctx.userData );
   }

   return 0;
}