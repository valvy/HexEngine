#ifndef PRUTENGINE_GL_PROGRAM_HPP
#define PRUTENGINE_GL_PROGRAM_HPP
#include "./AbstractResource.hpp"
#include <vector>
#include "../platform/OpenGL.hpp"

namespace PrutEngine{
    namespace Data{
        class Shader;

        class GLProgram : public AbstractResource{
        private:
            GLuint programData;
        public:
            GLProgram(std::string name,const std::vector<std::shared_ptr<Shader> > &shaders);
            ~GLProgram();
            GLuint getProgram() const;
            
        };
    }
}
#endif
