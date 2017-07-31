#include "BasicObject.hpp"
#include "BasicScene.hpp"
#include <prutengine/Camera.hpp>
#include "prutengine/Application.hpp"
#include "prutengine/math/Utilities.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

BasicScene::BasicScene(){


 
}

void BasicScene::awake(){
    this->setCamera(new Camera(Vector3<float>(0,0,9)));
    float offset = 0;
    BasicObject* obj = new BasicObject(Vector3<float>(0,0,0));
    obj->rotate(Vector3<float>(0,90,0),50);
    this->addGameObject(obj);
    for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(new BasicObject(Vector3<float>((x * 2.1f) -13,
                                                       (y * 2.1f) -20 + offset,
                                                       3)));
        }
        offset ++;
    }
}

void BasicScene::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);

   
}

void BasicScene::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}
