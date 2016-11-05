#include <android/log.h>
#include <android_native_app_glue.h>
#include <time.h>
#include "Game.hpp"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "esUtil", __VA_ARGS__))


//////////////////////////////////////////////////////////////////
//
//  Private Functions
//
//

void printCommand(int32_t cmd){
   switch ( cmd ){
      case APP_CMD_INPUT_CHANGED:         LOGI("cmd: APP_CMD_INPUT_CHANGED");          break; 
      case APP_CMD_INIT_WINDOW:           LOGI("cmd: APP_CMD_INIT_WINDOW");            break; 
      case APP_CMD_TERM_WINDOW:           LOGI("cmd: APP_CMD_TERM_WINDOW");            break; 
      case APP_CMD_WINDOW_RESIZED:        LOGI("cmd: APP_CMD_WINDOW_RESIZED");         break; 
      case APP_CMD_WINDOW_REDRAW_NEEDED:  LOGI("cmd: APP_CMD_WINDOW_REDRAW_NEEDED");   break; 
      case APP_CMD_CONTENT_RECT_CHANGED:  LOGI("cmd: APP_CMD_CONTENT_RECT_CHANGED");   break; 
      case APP_CMD_GAINED_FOCUS:          LOGI("cmd: APP_CMD_GAINED_FOCUS");           break; 
      case APP_CMD_LOST_FOCUS:            LOGI("cmd: APP_CMD_LOST_FOCUS");             break; 
      case APP_CMD_CONFIG_CHANGED:        LOGI("cmd: APP_CMD_CONFIG_CHANGED");         break; 
      case APP_CMD_LOW_MEMORY:            LOGI("cmd: APP_CMD_LOW_MEMORY");             break; 
      case APP_CMD_START:                 LOGI("cmd: APP_CMD_START");                  break; 
      case APP_CMD_RESUME:                LOGI("cmd: APP_CMD_RESUME");                 break; 
      case APP_CMD_SAVE_STATE:            LOGI("cmd: APP_CMD_SAVE_STATE");             break; 
      case APP_CMD_PAUSE:                 LOGI("cmd: APP_CMD_PAUSE");                  break; 
      case APP_CMD_STOP:                  LOGI("cmd: APP_CMD_STOP");                   break; 
      case APP_CMD_DESTROY:               LOGI("cmd: APP_CMD_DESTROY");                break; 
   }
}

///
// GetCurrentTime()
//
static float GetCurrentTime()
{
   struct timespec clockRealTime;
   clock_gettime ( CLOCK_MONOTONIC, &clockRealTime );
   double curTimeInSeconds = clockRealTime.tv_sec + ( double ) clockRealTime.tv_nsec / 1e9;
   return ( float ) curTimeInSeconds;
}

///
// HandleCommand()
//
//    Android callback for onAppCmd
//
static void handleCommand ( struct android_app *pApp, int32_t cmd ){
   OME::Context *context = ( OME::Context * ) pApp->userData;
   printCommand(cmd);
   switch ( cmd ){
      case APP_CMD_INPUT_CHANGED:      break; // 0
      //______________________________________
      case APP_CMD_INIT_WINDOW:              // 1
         context->platformData = ( void * ) pApp->activity->assetManager;
         context->eglNativeDisplay = EGL_DEFAULT_DISPLAY;
         context->eglNativeWindow = pApp->window;
         // Call the main entrypoint for the app
         if ( OME::Game::StartUp ( context ) != GL_TRUE ){
            exit ( 0 ); //@TEMP better way to exit?
         }
         break;
      //______________________________________
      case APP_CMD_TERM_WINDOW:
              // Cleanup on shutdown
              if ( context->onDestroy != NULL ){
                 context->onDestroy( );
              }
              if ( context->userData != NULL ){
                  free ( context->userData );
              }
              memset ( context, 0, sizeof ( OME::Context ) );
              break;
      //______________________________________
      case APP_CMD_WINDOW_RESIZED:        break;
      //______________________________________
      case APP_CMD_WINDOW_REDRAW_NEEDED:  break;
      //______________________________________
      case APP_CMD_CONTENT_RECT_CHANGED:  break;
      //______________________________________
      case APP_CMD_GAINED_FOCUS:          break;
      //______________________________________
      case APP_CMD_LOST_FOCUS:            break;
      //______________________________________
      case APP_CMD_CONFIG_CHANGED:        break;
      //______________________________________
      case APP_CMD_LOW_MEMORY:            break;
      //______________________________________
      case APP_CMD_START:                 break;
      //______________________________________
      case APP_CMD_RESUME:                break;
      //______________________________________
      case APP_CMD_SAVE_STATE:            break;
      //______________________________________
      case APP_CMD_PAUSE:                 break;
      //______________________________________
      case APP_CMD_STOP:                  break;
      //______________________________________
      case APP_CMD_DESTROY:               break;
      //______________________________________
   }
}

//////////////////////////////////////////////////////////////////
//
//  Public Functions
//
//

int32_t handleInput(struct android_app* pApp, AInputEvent* event) {
    OME::Context *context = ( OME::Context * ) pApp->userData;
    int32_t eventType = AInputEvent_getType(event);
    switch(eventType){
        case AINPUT_EVENT_TYPE_MOTION:
            switch(AInputEvent_getSource(event)){
                case AINPUT_SOURCE_TOUCHSCREEN:
                    int action = AKeyEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
                    switch(action){
                        // case AMOTION_EVENT_ACTION_DOWN:
                        //    if(context->onTouch != NULL) context->onTouch((int)TouchState::BEGIN, AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
                        // break;
                        // case AMOTION_EVENT_ACTION_UP:
                        //    if(context->onTouch != NULL) context->onTouch((int)TouchState::ENDED, AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
                        // break;
                        // case AMOTION_EVENT_ACTION_MOVE:
                        //    if(context->onTouch != NULL) context->onTouch((int)TouchState::MOVED, AMotionEvent_getX(event, 0), AMotionEvent_getY(event, 0));
                        // break;
                    }
                break;
            } // end switch
        break;
        case AINPUT_EVENT_TYPE_KEY:
            // handle key input...
        break;
    } // end switch
}

///
//  android_main()
//
//    Main entrypoint for Android application
//
void android_main ( struct android_app *pApp )
{

   OME::Context context;
   float lastTime;

   // Make sure glue isn't stripped.
   app_dummy();

   // Initialize the context
   memset ( &context, 0, sizeof ( OME::Context ) );

   context.platformData = ( void * ) pApp->activity->assetManager;

   pApp->onAppCmd = handleCommand;
   pApp->userData = &context;

   lastTime = GetCurrentTime();

   while ( 1 )
   {
      int ident;
      int events;
      struct android_poll_source *pSource;

      while ( ( ident = ALooper_pollAll ( 0, NULL, &events, ( void ** ) &pSource ) ) >= 0 )
      {

         if ( pSource != NULL )
         {
            pSource->process ( pApp, pSource );
         }

         if ( pApp->destroyRequested != 0 )
         {
            return;
         }

      }

      if ( context.eglNativeWindow == NULL )
      {
         continue;
      }

      // Call app update function
      if ( context.onUpdate != NULL )
      {
         float curTime = GetCurrentTime();
         float deltaTime =  ( curTime - lastTime );
         lastTime = curTime;
         context.onUpdate ( deltaTime );
      }

      if ( context.onDraw != NULL )
      {
         context.onDraw ( );
         eglSwapBuffers ( context.eglDisplay, context.eglSurface );
      }
   }
}


///
//  WinCreate()
//
//      Create Win32 instance and window
//
GLboolean WinCreate ( OME::Context *context, const char *title )
{
   // On Android, this does not need to do anything.  Everything happens from
   // android_main()
   return GL_TRUE;
}