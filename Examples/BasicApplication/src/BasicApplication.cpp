#include "BasicApplication.hpp"
#include "BasicScene.hpp"
#include <iostream>
#include <prutengine/exceptions/PrutEngineException.hpp>
BasicApplication::BasicApplication(){
    setInstance(this);
    loadScene(std::shared_ptr<PrutEngine::AbstractScene>(new BasicScene()));
    run();

}

PrutEngine::Graphics_Engine BasicApplication::setRenderer(){
    using PrutEngine::Graphics_Engine;
    if(this->canUseAppleMetal()){
        return Graphics_Engine::AppleMetal;
    }
    return Graphics_Engine::OpenGL;
}

void BasicApplication::loop(){
    try{
        update();
    }catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Program crashed with following exception: ";
        std::cout << exception.getMsg() << "\n";
        this->quit();
    }
}

BasicApplication::~BasicApplication(){
    std::cout << "Quitting\n";
}