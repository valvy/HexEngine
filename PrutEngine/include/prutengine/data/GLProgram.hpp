#ifndef PRUTENGINE_GL_PROGRAM_HPP
#define PRUTENGINE_GL_PROGRAM_HPP
#include "./AbstractResource.hpp"
#include <vector>
#include "../platform/OpenGL.hpp"

namespace PrutEngine{
    class Shader;

    class GLProgram : public AbstractResource{
    private:
        GLuint programData;
    public:
        GLProgram(std::string name, unsigned short uniqueNumber,const std::vector<unsigned short> &shaders);
        ~GLProgram();
        GLuint getProgram() const;
        
    };
}
#endif