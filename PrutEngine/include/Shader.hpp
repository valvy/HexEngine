#ifndef SHADER_HPP
#define SHADER_HPP
#include "AbstractResource.hpp"
#include "OpenGL.hpp"
class Shader : public AbstractResource{
private:
    GLuint shaderData;
public:
    Shader(std::string path,GLenum shaderType, unsigned short uniqueNumber);
    GLuint getShader() const;
    virtual ~Shader();
    
    
};


#endif