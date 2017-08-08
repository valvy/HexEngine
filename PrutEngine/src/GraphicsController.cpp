#include "prutengine/GraphicsController.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/platform/OpenGL.hpp"

using namespace PrutEngine;


GraphicsController::GraphicsController(const Graphics_Engine& engine){
    this->usedEngine = engine;
    if(engine == Graphics_Engine::OpenGL){
       this->preDrawfunction = std::function<void()>([]() -> void {
            Platform::clearAndCheckErrors();
           //std::cout << "Test\n";
       });
    }
}


Graphics_Engine GraphicsController::getCurrentGraphicsEngine() const {
    return this->usedEngine;
}

void GraphicsController::preDraw(){
    try{
        if(this->preDrawfunction != nullptr){
        this->preDrawfunction();
        }
    } catch(std::bad_function_call exception){
        throw Exceptions::AssetNotLoadedException("Draw function was not setup");
    }
}

