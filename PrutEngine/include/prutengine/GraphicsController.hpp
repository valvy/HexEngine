#ifndef PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#define PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#include <functional>

namespace PrutEngine{

    enum class Graphics_Engine{
        OpenGL = 0,
        AppleMetal
    };
    
    class Renderer;
    
    namespace Data{
        class GraphicsProgram;
        class Shader;
    }

    enum class Shader_Types{
        Vertex_Shader = 0,
        Fragment_Shader
    };
    
    #ifdef __APPLE__
	namespace Platform{class MacFriend; };
	#endif

    class GraphicsController{
        //friend Application;        
        #ifdef __APPLE__
        friend Platform::MacFriend;
        #endif
        private:
        std::function<void()> preDrawfunction;
        std::function<void(std::string, Shader_Types, Data::Shader*)> loadShaderFunction;
        std::function<Data::GraphicsProgram*(const std::string&, const std::vector<std::shared_ptr<Data::Shader>>&)> compileProgramfunction;
       
        std::function<std::shared_ptr<Renderer>(const std::string&, const std::string&, std::shared_ptr<Data::GraphicsProgram>)> createRendererFunction;
        
        Graphics_Engine usedEngine;
        public:
        Graphics_Engine getCurrentGraphicsEngine() const;
        GraphicsController(const Graphics_Engine& engine);
        void preDraw();
        void loadShader(std::string path, Shader_Types type, Data::Shader* shader);
        Data::GraphicsProgram* compileProgram(const std::string& name, const std::vector<std::shared_ptr<Data::Shader>>& shaders);
        std::shared_ptr<Renderer> createRenderer(const std::string& mesh, const std::string& texture, std::shared_ptr<Data::GraphicsProgram> program);
    };
}

#endif
