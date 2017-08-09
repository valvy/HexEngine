#ifndef PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#define PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#include <functional>
namespace PrutEngine{

    enum class Graphics_Engine{
        OpenGL = 0,
        AppleMetal
    };
    
    namespace Data{
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
        std::function<void(std::string path, Shader_Types type, Data::Shader* shader)> loadShaderFunction;
        Graphics_Engine usedEngine;
        public:
        Graphics_Engine getCurrentGraphicsEngine() const;
        GraphicsController(const Graphics_Engine& engine);
        void preDraw();
        void loadShader(std::string path, Shader_Types type, Data::Shader* shader);

    };
}

#endif
