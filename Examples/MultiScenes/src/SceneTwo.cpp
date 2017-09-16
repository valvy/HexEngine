#include "SceneOne.hpp"
#include "SceneTwo.hpp"
#include <prutengine/Camera.hpp>
#include "prutengine/Application.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include "prutengine/Application.hpp"
#include <iostream>
using namespace PrutEngine;
using namespace PrutEngine::Math;

SceneTwo::SceneTwo(){

}

void SceneTwo::awake(){
    Application::getInstance()->setWindowTitle("Scene Two");
    this->setCamera(std::shared_ptr<Camera>(new Camera(Vector3f(0,0,9))));
}

void SceneTwo::keyDown(unsigned short keycode){
    AbstractScene::keyDown(keycode);
    if(keycode == PrutEngine::KeyCodes::ESCAPE_KEY){
        Application::getInstance()->quit();
    }
    if(keycode == PrutEngine::KeyCodes::SPACE_BAR){
        Application::getInstance()->loadScene(std::shared_ptr<AbstractScene>(new SceneOne()));
    }

}

void SceneTwo::update(float tpf){
	AbstractScene::update(tpf);//Updates the gameobjects
}

SceneTwo::~SceneTwo(){
    std::cout << "stopping scene two\n";
}