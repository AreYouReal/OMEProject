#include "GameObject.hpp"
#include "../Components/Transform/Transform.hpp"


namespace OME {

GameObject::GameObject(string name) : mName(name){
    up<Transform> transformComp = up<Transform>(new Transform());
    addComponent(std::move(transformComp));
    OME::Utils::LOG("GO Constructor!\n");
}

GameObject::~GameObject(){
    OME::Utils::LOG("GO Destructor!\n");
}

void GameObject::init(){

}

void GameObject::update(){
    if(!mActive) return;
    
    for(auto const& comp : mComponents){
        comp.second->update();
    }
}

void GameObject::draw(){
    if(!mActive) return;
    
    for(auto const& comp : mComponents){
        comp.second->draw();
    }
}

void GameObject::destroy(){
    for(auto const& comp : mComponents){
        comp.second->destroy();
    }
}


IComponent* GameObject::addComponent(up<IComponent> comp){
    IComponent* returnThis = comp.get();
    if(mComponents.find(comp->type()) != mComponents.end()){
        returnThis = mComponents[comp->type()].get();
    }else{
        mComponents.insert(std::pair<string, up<IComponent>>(comp->type(), std::move(comp)));
    }
    returnThis->go = this;
    return returnThis;
}


bool GameObject::removeComponent(string type){
    if(mComponents.find(type) != mComponents.end()){
        mComponents.erase(type);
        return true;
    }
    return false;
}

IComponent* GameObject::getComponent(string type){
    if(mComponents.find(type) != mComponents.end()){
        return mComponents[type].get();
    }
    return nullptr;
}

    Transform* GameObject::transform(){
        string transformType(typeid(Transform).name());
        return static_cast<Transform*>(getComponent(transformType));
    }

}

