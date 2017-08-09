#ifndef PRUTENGINE_SHADER_HPP
#define PRUTENGINE_SHADER_HPP
#include "./AbstractResource.hpp"
#include "../platform/OpenGL.hpp"
#include "../GraphicsController.hpp"
namespace PrutEngine{
    namespace Data{
        
        
        
        class ShaderData{
            private:
            Graphics_Engine type;
            public:
            ShaderData(Graphics_Engine type);
            virtual ~ShaderData();
            Graphics_Engine getType() const;
        };
        
        
        class GLShaderData : public ShaderData{
            private:
            GLuint dat;
            public:
            GLShaderData(GLuint dat);
            GLuint getShader() const;
            virtual ~GLShaderData();
        };
        
        
        class Shader : public AbstractResource{
        private:
            std::shared_ptr<ShaderData> shaderData;
            Shader_Types shaderType;
        public:
            void setShader(ShaderData* dat);
            Shader(const std::string& path, const Shader_Types& shaderType);
            std::shared_ptr<ShaderData> getData() const;
            GLuint getShader() const;
            Shader_Types getShaderType() const;
            virtual ~Shader();
            
            
        };
    }
}



#endif
