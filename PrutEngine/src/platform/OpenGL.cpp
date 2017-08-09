#include "prutengine/platform/OpenGL.hpp"
#include "prutengine/exceptions/RenderingException.hpp"
#include "prutengine/data/Shader.hpp"
#include <fstream>

#include "prutengine/exceptions/AssetNotLoadedException.hpp"
using namespace PrutEngine;


constexpr GLenum convertShaderToGL(const Shader_Types& shaderType){
    switch (shaderType) {
        case Shader_Types::Vertex_Shader:
        return GL_VERTEX_SHADER;
        case Shader_Types::Fragment_Shader:
        return GL_FRAGMENT_SHADER;
        break;
    }
    throw Exceptions::PrutEngineException("Could not convert shader");
    
}


void Platform::loadShader(std::string path, Shader_Types type, Data::Shader* shader){
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
        GLuint result = glCreateShader(convertShaderToGL(type));
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
        
        shader->setShader(new Data::GLShaderData(result));
        //this->shaderData = result;
    }else{
        throw Exceptions::AssetNotLoadedException("Could not find file");
    }
}

void Platform::clearAndCheckErrors(){
    static const GLfloat background[] = { 0.0f, 0.25f, 0.0f, 1.0f };
    static const GLfloat depth = 1.0f;
    glViewport(0, 0, 600, 600);
    
    glClearBufferfv(GL_COLOR, 0, background);
    glClearBufferfv(GL_DEPTH, 0, &depth);
    
    GLenum error = glGetError();
    if(error != GL_NO_ERROR){
        Exceptions::RenderingException exception("Rendering error occured in the mainloop");
        std::string errorMsg;
        do{
            switch(error){
                case GL_INVALID_ENUM:
                errorMsg = "My first info log using default logger";
                break;
                case GL_INVALID_VALUE:
                errorMsg = "found invalid value \n";
                break;
                case GL_INVALID_OPERATION:
                errorMsg = "found invalid operation \n";
                break;
                case GL_OUT_OF_MEMORY:
                errorMsg = "Opengl experienced an out of memory exception \n";
                break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                errorMsg =  "Invalid framebuffer operation \n";
                break;
                default:
                errorMsg = "Found an error with code " + std::to_string(error);
                break;
            }
            exception.addError(errorMsg);
        }while((error = glGetError()) != GL_NO_ERROR);
        throw exception;
    }
}
