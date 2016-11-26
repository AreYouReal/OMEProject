#include "Scene.hpp"


#include "Cube.hpp"
#include "Grid.hpp"
#include "ObjLoader.hpp"

#include "Camera.hpp"


namespace OME {

    
    ObjLoader *obj;
    
    Scene::Scene(){    }
    
    Scene::~Scene(){    }
    
    bool Scene::init(){
        
        // TODO: Wrong direction! TEMP solution
        addObject(up<GameObject>( Camera::instance()->go ));

        up<GameObject> go = up<GameObject>(new GameObject());
        
//        Grid *prm = (Grid*)go->addComponent(up<Grid>(new Grid()));
//        prm->init();
        
        obj = (ObjLoader*)go->addComponent(up<ObjLoader>(new ObjLoader()));
        obj->init();
        
        
        addObject(std::move(go));
        return true;
    }
    
    void Scene::update(){
        for(auto& go : mObjects){
            go->update();
        }
    }
    
    void Scene::draw(){
        for(auto& go : mObjects){
            go->draw();
        }
    }
    
    void Scene::destroy(){
        for(auto& go : mObjects){
            go->destroy();
        }
    }
    
    void Scene::OnTouch(){
        obj->switchModel();
    }
    
    void Scene::addObject(up<GameObject> go){
        mObjects.push_back(std::move(go));
    }
}

