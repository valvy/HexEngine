#include "prutengine/data/Shader.hpp"
#include <fstream>
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/Application.hpp"
using namespace PrutEngine;
using namespace PrutEngine::Data;


ShaderData::ShaderData(Graphics_Engine type){
    this->type = type;
}
Graphics_Engine ShaderData::getType() const{
    return this->type;
}

ShaderData::~ShaderData(){
    
}

GLShaderData::~GLShaderData(){
    glDeleteShader(this->dat);
}

GLShaderData::GLShaderData(GLuint dat) : ShaderData::ShaderData(Graphics_Engine::OpenGL){
    this->dat = dat;
}

GLuint GLShaderData::getShader() const{
    return this->dat;
}

Shader::Shader(const std::string& path, const Shader_Types& shaderType) : AbstractResource(path){
    this->shaderType = shaderType;
    Application::getInstance()->getGraphicsController()->loadShader(path,shaderType,this);
}
void Shader::setShader(ShaderData* dat){
    this->shaderData = std::shared_ptr<ShaderData>(dat);
}

std::shared_ptr<ShaderData> Shader::getData() const{
    return this->shaderData;
}

Shader_Types Shader::getShaderType() const{
    return this->shaderType;
}

GLuint Shader::getShader() const{
    if(shaderData != nullptr){
        if(shaderData->getType() == Graphics_Engine::OpenGL){
            ShaderData* dat = shaderData.get();
            GLShaderData* glDat = static_cast<GLShaderData*>(dat);
            return glDat->getShader();
        }
    }
    throw Exceptions::PrutEngineException("error");
    
}

Shader::~Shader(){
    this->shaderData.reset();
   
}

