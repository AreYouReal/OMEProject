#include "GameObject.hpp"

GameObject::GameObject(string name) : mName(name){
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
    if(mComponents.find(comp->mType) != mComponents.end()){
        returnThis = mComponents[comp->mType].get();
    }else{
        mComponents.insert(std::pair<IComponent::Type, up<IComponent>>(comp->mType, std::move(comp)));
    }
    return returnThis;
}


bool GameObject::removeComponent(IComponent::Type type){
    if(mComponents.find(type) != mComponents.end()){
        mComponents.erase(type);
        return true;
    }
    return false;
}

IComponent* GameObject::getComponent(IComponent::Type type){
    if(mComponents.find(type) != mComponents.end()){
        return mComponents[type].get();
    }
    return nullptr;
}
