#ifndef PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#define PRUTENGINE_GRAPHICS_CONTROLLER_HPP
#include <functional>
namespace PrutEngine{

    enum class Graphics_Engine{
        OpenGL = 0,
        AppleMetal
    } ;

    #ifdef __APPLE__
	namespace Platform{class MacRenderer; };
	#endif

    class GraphicsController{
        //friend Application;        
        #ifdef __APPLE__
        friend Platform::MacRenderer;
        #endif
        private:
        std::function<void()> preDrawfunction;
        Graphics_Engine usedEngine;
        public:
        Graphics_Engine getCurrentGraphicsEngine() const;
        
        GraphicsController(const Graphics_Engine& engine);
        void preDraw();

    };
}

#endif
