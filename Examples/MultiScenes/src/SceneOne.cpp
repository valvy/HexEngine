
#include "SceneOne.hpp"
#include "SceneTwo.hpp"
#include <prutengine/Camera.hpp>
#include "prutengine/Application.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include "prutengine/Application.hpp"
#include "prutengine/PrutWindow.hpp"
#include <iostream>
#include "BasicObject.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Math;

SceneOne::SceneOne(){

}

void SceneOne::awake(){
    Application::getInstance()->getWindow()->setWindowTitle("Scene one");
    this->setCamera(std::shared_ptr<Camera>(new Camera(Vector3f(0,0,9))));
    float offset = 0;
    
    for(int x = 0; x < 200; x++){
        for(int y = 0; y < 11; y++){
            this->addGameObject(std::shared_ptr<GameObject>(new BasicObject(Vector3f((x * 2.1f) -13,
                                                        (y * 2.1f) -20 + offset,
                                                        3))));
        }
        offset ++;
    }
}

void SceneOne::keyDown(const unsigned short& keycode){
    AbstractScene::keyDown(keycode);
    if(keycode == PrutEngine::KeyCodes::ESCAPE_KEY){
        Application::getInstance()->quit();
    } else if (keycode == PrutEngine::KeyCodes::SPACE_BAR){
        Application::getInstance()->loadScene(std::shared_ptr<AbstractScene>(new SceneTwo()));
    }

}

void SceneOne::update(const float& tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}

SceneOne::~SceneOne(){
    std::cout << "stopping scene one\n";
}