#include "prutengine/data/GraphicsProgram.hpp"
#include "prutengine/data/Shader.hpp"
#include "prutengine/Application.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Data;



GraphicsProgram::GraphicsProgram(const std::string& name, const std::vector<std::shared_ptr<Shader>>& shaders) : AbstractResource(name){
    this->shaders = shaders;
}



GLProgram::GLProgram(const std::string& name, const std::vector<std::shared_ptr<Shader>> &shaders)
    : GraphicsProgram(name, shaders){
        
    auto assetManager =  Application::getInstance()->getAssetManager();
    const Graphics_Engine engine = Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    this->programData = glCreateProgram();
    for(auto sh : shaders){
        glAttachShader(this->programData,sh->getShader());
    }

    glLinkProgram(this->programData);
}

GLuint GLProgram::getProgram() const{
    return this->programData;
}

GLProgram::~GLProgram(){
    const Graphics_Engine engine = Application::getInstance()->getGraphicsController()->getCurrentGraphicsEngine();
    
    if(engine == Graphics_Engine::AppleMetal){
        return;
    }
    glDeleteProgram(this->programData);
}
