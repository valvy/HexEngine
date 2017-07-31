#include "prutengine/data/Shader.hpp"
#include <fstream>
#include "prutengine/exceptions/AssetNotLoadedException.hpp"

using namespace PrutEngine;
using namespace PrutEngine::Data;

Shader::Shader(std::string path, GLenum shaderType, unsigned short uniqueNumber) : AbstractResource(path,uniqueNumber){
    std::fstream str(path, std::ios::in);
    if(str.good()){
        std::string line;
        std::string code;
        
        //Load all data in the string
        while(!str.eof()){
            std::getline(str,line);
            code += line + '\n';
        }
        str.close();
        
        //attemt to compile the shader
        GLuint result = glCreateShader(shaderType);
        const char *c_str = code.c_str();
        glShaderSource(result,1, &c_str, nullptr);
        glCompileShader(result);
        
        
        //Check for compile errors
        GLint compiled;
        glGetShaderiv(result, GL_COMPILE_STATUS, &compiled);
        if(!compiled){
            GLint infoLen= 0;
            glGetShaderiv(result, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1){
                GLchar log[infoLen + 1];
                glGetShaderInfoLog(result, infoLen, nullptr, log);
                std::string errorMsg(log);
                 throw Exceptions::AssetNotLoadedException(errorMsg);
                // delete[] log;
                // throw std::string(errorMsg);
            }
        }
        
        this->shaderData = result;
    }else{
       throw Exceptions::AssetNotLoadedException("Could not find file");
    }
    
}

GLuint Shader::getShader() const{
    return this->shaderData;
}

Shader::~Shader(){
    glDeleteShader(this->shaderData);
}

