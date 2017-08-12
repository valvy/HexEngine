#include "prutengine/platform/OpenGL.hpp"
#include "prutengine/exceptions/RenderingException.hpp"
#include "prutengine/data/Shader.hpp"
#include "prutengine/data/GraphicsProgram.hpp"
#include <fstream>
#include "prutengine/Renderer.hpp"
#include "prutengine/exceptions/AssetNotLoadedException.hpp"
#include "prutengine/math/Utilities.hpp"
#include "prutengine/math/Matrix4x4.hpp"
#include "prutengine/Transform.hpp"
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

Data::GraphicsProgram* Platform::generateProgram(const std::string& name, const std::vector<std::shared_ptr<Data::Shader>>& shaders){
    return new Data::GLProgram(name,shaders);
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

std::shared_ptr<Renderer> Platform::createRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program){
    return std::shared_ptr<Renderer>(new GLRenderer(mesh, texture, program));
}

void Platform::draw(const std::shared_ptr<Renderer>& renderer, const std::shared_ptr<Transform>& transform){
    using namespace PrutEngine::Math;
    GLRenderer* glRenderer = static_cast<GLRenderer*>(renderer.get());
    Data::GraphicsProgram* program = renderer->getProgram().get();
    Data::Mesh* mesh = glRenderer->getMesh().get();
    Data::Texture* texture = glRenderer->getTexture().get();
    
    Data::GLProgram* tmpProgram = static_cast<Data::GLProgram*>(program);
    
    glUseProgram(tmpProgram->getProgram());
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture->getTexture());
    glBindVertexArray(mesh->getVao());
    
    //Make the calculation
    Matrix4x4<float> mat = Matrix4x4<float>::identityMatrix();
    mat = Matrix4x4<float>::scale(mat,transform->getScale());
    Matrix4x4<float> pos = Matrix4x4<GLfloat>::translate(Matrix4x4<float>::identityMatrix(),transform->getPosition());
    
    mat = Matrix4x4<float>::multiply(mat,pos);
    mat = Matrix4x4<float>::multiply(mat, Quaternion<float>::quaternionToMatrix(transform->getQuaternion()));
    
    //pass it to opengl
    glUniformMatrix4fv(glRenderer->getPositionRef(), 1, GL_TRUE, &mat.getRawData()[0]);
    glEnableVertexAttribArray ( 0 );
    
    glDrawArrays ( GL_TRIANGLES, 0, mesh->getSize());
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
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
