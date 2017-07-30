#ifndef PRUTENGINE_SHADER_HPP
#define PRUTENGINE_SHADER_HPP
#include "./AbstractResource.hpp"
#include "../platform/OpenGL.hpp"

namespace PrutEngine{
    class Shader : public AbstractResource{
    private:
        GLuint shaderData;
    public:
        Shader(std::string path,GLenum shaderType, unsigned short uniqueNumber);
        GLuint getShader() const;
        virtual ~Shader();
        
        
    };
}



#endif