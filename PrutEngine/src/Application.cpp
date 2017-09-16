#include "prutengine/Application.hpp"
#include "prutengine/platform/OpenGL.hpp"

#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/platform/Input.hpp"
#include <chrono>
#include <iostream>
#include "prutengine/exceptions/NotYetInitializedException.hpp"
using namespace PrutEngine;


Application* Application::instance;

void Application::setInstance(Application* app){
    Application::instance = app;
}

Application::~Application(){
    
}


Application::Application(){

}

void Application::quit(){
    if(assetManager != nullptr){
        assetManager->clear();
    }
    currentScene.reset();
    shouldStop = true;
}



std::shared_ptr<AssetManager> Application::getAssetManager(){
    if(this->assetManager == nullptr){
        this->assetManager = std::shared_ptr<AssetManager>(new AssetManager());
    }
    return this->assetManager;
}

void Application::loadScene(std::shared_ptr<AbstractScene> scene){
    this->currentScene = scene;
}

void Application::awake(){
    this->currentScene->awake();
}

Application* Application::getInstance(){
    Exceptions::assertNotYetInitialized(instance == nullptr,"instance is null");
	return instance;
}



void Application::keyDown(unsigned short keyCode){
    Exceptions::assertNotYetInitialized(this->currentScene == nullptr,"scene is null");
    this->currentScene->keyDown(keyCode);
}

std::shared_ptr<GraphicsController> Application::getGraphicsController() const {
    Exceptions::assertNotYetInitialized(graphicsController == nullptr,"graphicscontroller is null");
    return this->graphicsController;
}

void Application::update(){

    Exceptions::assertNotYetInitialized(currentScene == nullptr,"No scene is null");
    Exceptions::assertNotYetInitialized(graphicsController == nullptr,"graphicscontroller is null");

    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_seconds;
    start = std::chrono::system_clock::now();
    
    this->graphicsController->preDraw();

    
	currentScene->update(time_per_frame);
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    this->time_per_frame = elapsed_seconds.count();
}
