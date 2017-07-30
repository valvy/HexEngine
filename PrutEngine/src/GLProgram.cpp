#include "GLProgram.hpp"
#include "Shader.hpp"
#include "AssetManager.hpp"
#include <iostream>
GLProgram::GLProgram(std::string name, unsigned short uniqueNumber, const std::vector<unsigned short> &shaders) : AbstractResource(name,uniqueNumber){
    
    this->programData = glCreateProgram();
    for(auto sh : shaders){
        glAttachShader(this->programData,AssetManager::getShader(sh)->getShader());
    }

    glLinkProgram(this->programData);
}

GLuint GLProgram::getProgram() const{
    return this->programData;
}

GLProgram::~GLProgram(){
    glDeleteProgram(this->programData);
}