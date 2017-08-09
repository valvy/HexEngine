#include "prutengine/GraphicsController.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/platform/OpenGL.hpp"

using namespace PrutEngine;


GraphicsController::GraphicsController(const Graphics_Engine& engine){
    this->usedEngine = engine;
    if(engine == Graphics_Engine::OpenGL){
       this->preDrawfunction = std::function<void()>([]() -> void {
            Platform::clearAndCheckErrors();
       });
        this->loadShaderFunction = std::function<void(std::string path, Shader_Types type, Data::Shader* shader)>([](std::string path, Shader_Types type, Data::Shader* shader)->void{
            Platform::loadShader(path, type, shader);
        });
    }
}


Graphics_Engine GraphicsController::getCurrentGraphicsEngine() const {
    return this->usedEngine;
}

void GraphicsController::loadShader(std::string path, Shader_Types type, Data::Shader* shader){
    try{
        this->loadShaderFunction(path,type,shader);
    } catch(std::bad_function_call exception){
        throw Exceptions::AssetNotLoadedException("Load shader is not defined");
    }
}

void GraphicsController::preDraw(){
    try{
        this->preDrawfunction();
    } catch(std::bad_function_call exception){
       // throw Exceptions::AssetNotLoadedException("Draw function was not setup");
    }
}

