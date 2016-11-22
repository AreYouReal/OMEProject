#include "Game.hpp"

#include "ShaderProgram.hpp"
#include "PngTexture2D.hpp"

#include "GameObject.hpp"

//#include "../CPP/Components/Transform/Transform.hpp"

#include "Camera.hpp"


#include "Primitives.hpp"

#ifdef __APPLE__
#define VERTEX_SHADER "basic.vert"
#define FRAGMENT_SHADER "basic.frag"
#else
#define VERTEX_SHADER "shaders/basic.vert"
#define FRAGMENT_SHADER "shaders/basic.frag"
#endif

using UserData = struct{};

namespace OME {
    
     OME::Context *Game::currentCtx;
    
    GameObject *camObj;
    
    GameObject *primGO;
    Primitives *prm;
    
    int Game::StartUp(OME::Context *ctx){
        
        Camera *cam = Camera::instance();
        camObj = cam->go;
        cam->init();
        camObj->transform()->mPosition = vec3(0, 0, 1.5f);
        cam->camInit(640, 480, 90, 0.1f, 1000.0f);
        
        primGO = new GameObject();
        prm = (Primitives*)primGO->addComponent(up<Primitives>(new Primitives()));
        prm->init();
        
        ctx->userData = malloc (sizeof(UserData));
        
        if(!Utils::OMCreateWindow(ctx, "One More Engine In Action!", ctx->width, ctx->height, WINDOW_RGB | WINDOW_DEPTH)){
            Utils::LOG("Failed to create Window!");
            return 0;
        }
        currentCtx = ctx;
        
        currentCtx->onUpdate   = OnUpdate;
        currentCtx->onDraw     = OnDraw;
        currentCtx->onTouch    = OnTouch;
        currentCtx->onDestroy  = OnDestroy;
        
        PngTexture2D pngTexture;
        pngTexture.loadTexture("spiderman.png");

               

        OME::Utils::LOG("Typeid:  %s", typeid(Camera).name());
        
        
        initOGL(currentCtx->width, currentCtx->height);
        
        return 1;
    }
    
    
    void Game::OnUpdate    (const float){
        
    }
    
    void Game::OnDraw(){
        Camera::instance()->setWindthAndHeight(currentCtx->width, currentCtx->height);
        glViewport(0, 0, currentCtx->width, currentCtx->height);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
        
        prm->draw();
    }
    
    void Game::OnTouch     (const int x, const int y, const int type){
        if(prm != nullptr){
            if(type == 0){
                prm->primitive++;
                prm->primitive = prm->primitive%7;
            }

        }
    }
    
    void Game::OnDestroy   (){
        if(camObj){
            delete camObj;
        }
        
        if(primGO){
            delete primGO;
        }
        Utils::LOG("OnDestroy!");
    }
    
    void Game::initOGL(const float w, const float h){
        Utils::PRINT_GL_STRING("Version",        GL_VERSION);
        Utils::PRINT_GL_STRING("Vendor",         GL_VENDOR);
        Utils::PRINT_GL_STRING("Renderer",       GL_RENDERER);
//        OME::PRINT_GL_STRING("Extensions",     GL_EXTENSIONS);
//        OME::PRINT_GL_STRING("GLSL version",   GL_SHADING_LANGUAGE_VERSION);
        
        glViewport ( 0, 0, w, h );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_CULL_FACE  );
    }

}
