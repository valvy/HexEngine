#include "BasicObject.hpp"
#include "BasicScene.hpp"
#include <prutengine/Camera.hpp>
#include "prutengine/Application.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include "prutengine/Application.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Math;

BasicScene::BasicScene(){

}

void BasicScene::awake(){
    this->setCamera(std::shared_ptr<Camera>(new Camera(Vector3f(0,0,9))));
    float offset = 0;
 //return;
    auto obj = std::shared_ptr<GameObject>(new BasicObject(Vector3f(0,0,0)));
    obj->rotate(Vector3f(0,90,0),50);
    this->addGameObject(obj);
    for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(std::shared_ptr<GameObject>(new BasicObject(Vector3f((x * 2.1f) -13,
                                                       (y * 2.1f) -20 + offset,
                                                       3))));
        }
        offset ++;
    }
}

void BasicScene::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);
    if(keycode == PrutEngine::KeyCodes::ESCAPE_KEY){
        Application::getInstance()->quit();
    }

   
}

void BasicScene::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}
