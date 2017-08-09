#ifndef PRUTENGINE_GL_PROGRAM_HPP
#define PRUTENGINE_GL_PROGRAM_HPP
#include "./AbstractResource.hpp"
#include <vector>
#include "../platform/OpenGL.hpp"

namespace PrutEngine{
    namespace Data{
        class Shader;
        
        class GraphicsProgram : public AbstractResource{
            protected:
            std::vector<std::shared_ptr<Shader>> shaders;
            public:
            GraphicsProgram(const std::string& name, const std::vector<std::shared_ptr<Shader>>& shaders);
            
        };

        class GLProgram : public GraphicsProgram{
        private:
            GLuint programData;
        public:
            GLProgram(const std::string& name,const std::vector<std::shared_ptr<Shader>> &shaders);
            ~GLProgram();
            GLuint getProgram() const;
            
        };
    }
}
#endif
