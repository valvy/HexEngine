#include "BasicApplication.hpp"
#include "BasicScene.hpp"
#include <iostream>

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
    update();
}

BasicApplication::~BasicApplication(){
    std::cout << "Quitting\n";
}