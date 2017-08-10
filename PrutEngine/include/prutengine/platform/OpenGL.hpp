#ifndef PRUTENGINE_OPENGL_HPP
#define PRUTENGINE_OPENGL_HPP

#ifdef __APPLE__
#include "TargetConditionals.h"
#if TARGET_IPHONE_SIMULATOR
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif TARGET_OS_IPHONE
#include <OpenGLES/ES3/gl.h>
#include <OpenGLES/ES3/glext.h>
#elif TARGET_OS_MAC
#include <OpenGl/gl3.h>
#include <OpenGL/gl3ext.h>
#endif
#endif

#include "../GraphicsController.hpp"

#ifdef __linux__
#include <GL/glew.h>
#include <GL/glx.h>
#endif
#include <string>

#include <memory>

namespace PrutEngine{
    
    namespace Data{
        class Shader;
        class GraphicsProgram;
        class GLProgram;
    }
    
    class Renderer;
    
    namespace Platform{
        void clearAndCheckErrors();
        void loadShader(std::string path, Shader_Types type, Data::Shader* shader);
        Data::GraphicsProgram* generateProgram(const std::string& name, const std::vector<std::shared_ptr<Data::Shader>>& shaders);
        std::shared_ptr<Renderer> createRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program);
    }
}



#endif
