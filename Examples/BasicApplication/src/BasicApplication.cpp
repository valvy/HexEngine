#include "BasicApplication.hpp"
#include "BasicScene.hpp"
#include <iostream>
#include <prutengine/exceptions/PrutEngineException.hpp>
#include <prutengine/exceptions/RenderingException.hpp>
#include <prutengine/platform/apple/MetalShaderTypes.h>
#include <prutengine/GraphicsController.hpp>

BasicApplication::BasicApplication(){
    setInstance(this);
    try{
        loadScene(std::shared_ptr<PrutEngine::AbstractScene>(new BasicScene()));
    }catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Could not start the program due the following exception: ";
        std::cout << exception.getMsg() << "\n";
        return;
    }
    run();

}

PrutEngine::Graphics_Engine BasicApplication::setRenderer(){
    using PrutEngine::Graphics_Engine;

    return Graphics_Engine::OpenGL;
}

void BasicApplication::loop(){
    try{
        update();
    }
    catch( PrutEngine::Exceptions::RenderingException& exception){
        std::cout << exception.getError() << "\n";
    }
    catch(const PrutEngine::Exceptions::PrutEngineException exception){
        std::cout << "Program crashed with following exception: ";
        std::cout << exception.getMsg() << "\n";
        this->quit();
    }
}

BasicApplication::~BasicApplication(){
    std::cout << "Quitting\n";
}
