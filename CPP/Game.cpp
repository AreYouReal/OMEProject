#include "Game.hpp"

#include "ShaderProgram.hpp"

using UserData = struct{};

namespace OME {
    
     OME::Context *Game::currentCtx;
    
    int Game::StartUp(OME::Context *ctx){
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
        
        ShaderProgram program;
        program.loadShaders("basic.vert", "basic.frag");
        
        initOGL(currentCtx->width, currentCtx->height);

        
        return 1;
    }
    
    
    void Game::OnUpdate    (const float){
        
    }
    
    void Game::OnDraw(){
        glViewport(0, 0, currentCtx->width, currentCtx->height);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
    }
    
    void Game::OnTouch     (const int, const int, const int){
        
    }
    
    void Game::OnDestroy   (){
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
