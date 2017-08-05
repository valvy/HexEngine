#include "prutengine/AbstractScene.hpp"
#include "prutengine/GameObject.hpp"
#include "prutengine/Camera.hpp"
#include "prutengine/Application.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

AbstractScene::AbstractScene(){
   // this->cam = std::shared_ptr<Camera>(new Camera(Vector3<float>(0,0,0)));
}

void AbstractScene::awake(){
    this->cam = std::shared_ptr<Camera>(new Camera(Vector<float,3>(0,0,0)));
}


void AbstractScene::update(float tpf){
    this->cam->update(tpf);

	for(auto it : this->gameObjects){
        it->update(tpf);
	}
    

}


void AbstractScene::keyDown(unsigned short keycode){
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

void AbstractScene::addGameObject(std::shared_ptr<GameObject> obj){
    this->gameObjects.push_back(obj);
}

void AbstractScene::removeGameObject(std::shared_ptr<GameObject> obj){
    
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