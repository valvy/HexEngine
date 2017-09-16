#include "MultiApplication.hpp"
#include "SceneOne.hpp"
#include <iostream>
#include <prutengine/exceptions/PrutEngineException.hpp>
#include <prutengine/platform/apple/MetalShaderTypes.h>

MultiSceneApplication::MultiSceneApplication(){
    setInstance(this);
    try{
        loadScene(std::shared_ptr<PrutEngine::AbstractScene>(new SceneOne()));
    }catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Could not start the program due the following exception: ";
        std::cout << exception.getMsg() << "\n";
        return;
    }
    run();
}

PrutEngine::Graphics_Engine MultiSceneApplication::setRenderer(){
    using PrutEngine::Graphics_Engine;
    if(this->canUseAppleMetal()){
        return Graphics_Engine::AppleMetal;
    }
    return Graphics_Engine::OpenGL;
}

void MultiSceneApplication::loop(){
    try{
        update();
    }catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Program crashed with following exception: ";
        std::cout << exception.getMsg() << "\n";
        this->quit();
    }
}

MultiSceneApplication::~MultiSceneApplication(){
    std::cout << "Quitting\n";
}
