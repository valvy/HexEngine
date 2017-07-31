#include "prutengine/data/GLProgram.hpp"
#include "prutengine/data/Shader.hpp"
#include "prutengine/Application.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Data;
GLProgram::GLProgram(std::string name, const std::vector<std::shared_ptr<Shader>> &shaders) : AbstractResource(name){
    auto assetManager =  Application::getInstance()->getAssetManager();
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
    glDeleteProgram(this->programData);
}