#include "prutengine/deprecated/TestScene.hpp"
#include "prutengine/deprecated/TestObject.hpp"
#include "prutengine/Camera.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/math/Utilities.hpp"
#include <iostream>

using namespace PrutEngine;
using namespace PrutEngine::Math;

TestScene::TestScene(){
    this->setCamera(new Camera(Vector3<float>(0,0,9)));
    float offset = 0;
    TestObject* obj = new TestObject(Vector3<float>(0,0,0));
    obj->rotate(Vector3<float>(0,90,0),50);
    this->addGameObject(obj);
    for(int x = 0; x < 11; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(new TestObject(Vector3<float>((x * 2.1f) -13,
                                                       (y * 2.1f) -20 + offset,
                                                       3)));
        }
        offset ++;
    }

 
}

void TestScene::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);

   
}

void TestScene::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}
