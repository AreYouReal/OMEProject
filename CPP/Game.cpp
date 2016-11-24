#include "Game.hpp"

#include "ShaderProgram.hpp"
#include "PngTexture2D.hpp"

#include "GameObject.hpp"

//#include "../CPP/Components/Transform/Transform.hpp"

#include "Camera.hpp"


#include "Time.hpp"

#include "Scene.hpp"

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

    int Game::StartUp(OME::Context *ctx){

        if(!initContext(ctx)){
            return 0;
        }
        
        initOGL(currentCtx->width, currentCtx->height);
        
        initCamera();

        Scene::instance()->init();
        
//        PngTexture2D pngTexture;
//        pngTexture.loadTexture("spiderman.png");


        
        return 1;
    }
    
    
    void Game::OnUpdate    (const float){
        OME::Time::update();
        Scene::instance()->update();
    }
    
    void Game::OnDraw(){
        Camera::instance()->setWindthAndHeight(currentCtx->width, currentCtx->height);        
        Scene::instance()->draw();
    }
    
    void Game::OnTouch(const int x, const int y, const int type){

    }
    
    void Game::OnDestroy   (){
        Scene::instance()->destroy();
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
    
    bool Game::initContext(OME::Context *ctx){
        ctx->userData = malloc (sizeof(UserData));
        
        if(!Utils::OMCreateWindow(ctx, "One More Engine In Action!", ctx->width, ctx->height, WINDOW_RGB | WINDOW_DEPTH)){
            Utils::LOG("Failed to create Window!");
            return false;
        }
        currentCtx = ctx;
        
        currentCtx->onUpdate   = OnUpdate;
        currentCtx->onDraw     = OnDraw;
        currentCtx->onTouch    = OnTouch;
        currentCtx->onDestroy  = OnDestroy;
        return true;
    }
    
    void Game::initCamera(){
        Camera *cam = Camera::instance();
        GameObject *camObj = cam->go;
        cam->init();
        camObj->transform()->mPosition = vec3(0, 2, 3.0f);
        cam->camInit(640, 480, 90, 0.1f, 1000.0f);
    }

}
