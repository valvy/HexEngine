#include "prutengine/AbstractScene.hpp"
#include "prutengine/Node.hpp"
#include "prutengine/Camera.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/exceptions/NotYetInitializedException.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

AbstractScene::AbstractScene(){
  
}

void AbstractScene::awake(){
    this->cam = std::shared_ptr<Camera>(new Camera(Vector<float,3>(0,0,0)));
}


void AbstractScene::update(const float& tpf){
    if(this->cam == nullptr){
        throw Exceptions::NotYetInitializedException("The camera is not yet initialized..");
    }
    this->cam->update(tpf);

	for(auto it : this->gameObjects){
        it->update(tpf);
	}
}


void AbstractScene::keyDown(const unsigned short& keycode){
    this->cam->onKeyDown(keycode);
    for(auto it : this->gameObjects){
        it->onKeyDown(keycode);
    }  
}

void AbstractScene::setCamera(std::shared_ptr<Camera> cam){
    this->cam.reset();
    this->cam = std::shared_ptr<Camera>(cam);
}

std::shared_ptr<Camera> AbstractScene::getCamera() const {
    return this->cam;
}

void AbstractScene::addGameObject(std::shared_ptr<Node> obj){
    this->gameObjects.push_back(obj);
}

void AbstractScene::removeGameObject(std::shared_ptr<Node> obj){
    
}

AbstractScene::~AbstractScene(){
    //delete gameobjects
    for(auto it : this->gameObjects){
        it.reset();
    }
    this->gameObjects.clear();
    
    //delete camera
    this->cam.reset();
}
