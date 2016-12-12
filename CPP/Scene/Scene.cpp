#include "Scene.hpp"


#include "Cube.hpp"
#include "Grid.hpp"
#include "ObjLoader.hpp"
#include "Loader3DS.hpp"

#include "Light.hpp"

#include "Camera.hpp"


namespace OME {

    
    ObjLoader *obj;
    
    Loader3DS *ds;
    
    Scene::Scene(){    }
    
    Scene::~Scene(){    }
    
    bool Scene::init(){
        
        // TODO: Wrong direction! TEMP solution
        GameObject *camGO = Camera::instance()->go;
        camGO->transform()->mPosition -= vec3(0, 2, 1);
        
        addObject(up<GameObject>( Camera::instance()->go ));

        up<GameObject> go = up<GameObject>(new GameObject());
        
//        Grid *prm = (Grid*)go->addComponent(up<Grid>(new Grid()));
//        prm->init();
        
        obj = (ObjLoader*)go->addComponent(up<ObjLoader>(new ObjLoader()));
        obj->init();
        
//        ds = (Loader3DS*)go->addComponent(up<Loader3DS>(new Loader3DS()));
//        ds->init();
        addObject(std::move(go));
        
        go = up<GameObject>(new GameObject());
        Light *light = (Light*)go->addComponent(up<Light>(new Light()));
        light->init();
        
        
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
        if(obj)
            obj->switchModel();
    }
    
    void Scene::addObject(up<GameObject> go){
        mObjects.push_back(std::move(go));
    }
}

