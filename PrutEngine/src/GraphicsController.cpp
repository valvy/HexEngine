#include "prutengine/GraphicsController.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/platform/OpenGL.hpp"
#include "prutengine/Renderer.hpp"

using namespace PrutEngine;


GraphicsController::GraphicsController(const Graphics_Engine& engine){
    this->usedEngine = engine;
    if(engine == Graphics_Engine::OpenGL){
        this->preDrawfunction = Platform::clearAndCheckErrors;
        this->loadShaderFunction = Platform::loadShader;
        this->compileProgramfunction = Platform::generateProgram;
        this->createRendererFunction = Platform::createRenderer;
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

Data::GraphicsProgram* GraphicsController::compileProgram(const std::string& name, const std::vector<std::shared_ptr<Data::Shader>>& shaders){
    try{
        return this->compileProgramfunction(name,shaders);
    } catch(std::bad_function_call exception){
        throw Exceptions::AssetNotLoadedException("compile program is not defined");
    }
}

std::shared_ptr<Renderer> GraphicsController::createRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program){
    try{
        return this->createRendererFunction(mesh,texture,program);
    } catch(std::bad_function_call exception){
        throw Exceptions::AssetNotLoadedException("create renderer function was not setup");
    }
}

void GraphicsController::preDraw(){
    try{
        this->preDrawfunction();
    } catch(std::bad_function_call exception){
       // throw Exceptions::AssetNotLoadedException("Draw function was not setup");
    }
}


