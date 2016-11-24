#include "Scene.hpp"


#include "Cube.hpp"
#include "Grid.hpp"

#include "Camera.hpp"


namespace OME {

    Scene::Scene(){    }
    
    Scene::~Scene(){    }
    
    bool Scene::init(){
        
        // TODO: Wrong direction! TEMP solution
        addObject(up<GameObject>( Camera::instance()->go ));

        
        up<GameObject> go = up<GameObject>(new GameObject());
        Grid *prm = (Grid*)go->addComponent(up<Grid>(new Grid()));
        prm->init();
        
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
    
    void Scene::addObject(up<GameObject> go){
        mObjects.push_back(std::move(go));
    }
}

