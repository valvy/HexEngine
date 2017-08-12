#include "prutengine/GameObject.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/math/Matrix.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include <iostream>
#include "prutengine/GraphicsController.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Math;

GameObject::GameObject(){
    this->transform = std::shared_ptr<Transform>(new Transform());
    this->getTransform()->setScale(Vector3f(1,1,1));
}

GameObject::~GameObject(){

}



std::shared_ptr<Renderer> GameObject::getRenderer() const{
    return this->renderer;
}

std::shared_ptr<Transform> GameObject::getTransform() const{
    return this->transform;
}

void GameObject::onKeyDown(unsigned short keyCode){
    //virtual
}

void GameObject::setRenderer(std::shared_ptr<Renderer> renderer){
    this->renderer = renderer;
}

void GameObject::update(float tpf){
    Application::getInstance()->getGraphicsController()->draw(this->renderer, this->transform);
}


